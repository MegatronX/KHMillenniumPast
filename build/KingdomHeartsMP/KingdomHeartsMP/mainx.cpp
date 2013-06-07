#include <boost/python.hpp>
#include <scripting/Python/ScriptHelpers.h>
using namespace boost::python;




template<class Copyable, class Base>
object
	base_class_generic__deepcopy__(object copyable, dict memo)
{
	object copyMod = import("copy");
	object deepcopy = copyMod.attr("deepcopy");

	Copyable *newCopyable(new Copyable(extract<const Copyable
		&>(copyable)));
	//object result(boost::python::detail::new_reference(managingPyObject(newCopyable)));

	//object result(extract<const Copyable &>(copyable)());

	//const Copyable & tmp = extract<const Copyable &>(copyable);
	//object result(tmp);

	Base tmp = boost::python::extract<Base const &>(copyable);
	object result(tmp);

	// HACK: copyableId shall be the same as the result of id(copyable)
	//in Python -
	// please tell me that there is a better way! (and which ;-p)
	int copyableId = (int)(copyable.ptr());
	memo[copyableId] = result;

	extract<dict>(result.attr("__dict__"))().update(
		deepcopy(extract<dict>(copyable.attr("__dict__"))(),
		memo));

	return result;
}


class BaseClass
{
public:
	typedef boost::shared_ptr<BaseClass> ClonePtr;
	BaseClass() : ID(++IDCounter)
	{

	}
	BaseClass(const BaseClass& cp) : ID(++IDCounter)
	{

	}
	virtual boost::shared_ptr<BaseClass> Clone()
	{
		return boost::shared_ptr<BaseClass>(new BaseClass(*this));
	}
	virtual int GetID() const
	{
		return ID;
	}
	virtual void Test()
	{
		std::cout << "C++ side ID: " << ID << "\n";
	}
protected:
	int ID;
private:
	static int IDCounter;
};

class BaseClassExt : public BaseClass
{
public:
	virtual void Test() override
	{
		std::cout << "In Base Class Ext Test\n";
	}

	virtual void ExtTest() 
	{
		std::cout << "In Base Class Ext Ext Test\n";
	}
};

class BaseClassWrap : public BaseClass
{
public:
	BaseClassWrap(PyObject* self_) : self(self_)
	{

	}
	BaseClassWrap(PyObject* self_, const BaseClass& cp) : self(self_), BaseClass(cp)
	{

	}
	BaseClassWrap(PyObject* self_, const BaseClassWrap& cp) : self(self_), BaseClass(cp)
	{

	}

	virtual int GetID() const override
	{
		return call_method<int>(self, "GetID");
	}
	virtual void Test()
	{
		call_method<void>(self, "Test");
	}
	void TestDefault()
	{
		BaseClass::Test();
	}
	int GetIDDefault() const
	{
		return BaseClass::GetID();
	}

	boost::shared_ptr<BaseClass> Clone() override
	{
		return call_method<ClonePtr>(self, "Clone");
	}
	boost::shared_ptr<BaseClass> CloneDefault() const
	{
		return boost::shared_ptr<BaseClass>(new BaseClassWrap(*this));
	}
	PyObject* self;
private:
};

class BaseClassExtWrap : public BaseClassExt
{
public:
	BaseClassExtWrap(PyObject* self_) : self(self_)
	{}

	BaseClassExtWrap(PyObject* self_, const BaseClassExtWrap& cp) : self(self_), BaseClassExt(cp)
	{
	}

	PyObject* self;
};

object bc_copy(object copyable, dict memo)
{
	object copyMod = import("copy");
	object deepcopy = copyMod.attr("deepcopy");

	BaseClassWrap *newCopyable(new BaseClassWrap(extract<const BaseClassWrap
		&>(copyable)));

	BaseClass tmp = boost::python::extract<BaseClass const &>(copyable);
	object result(tmp);

	int copyableId = (int)(copyable.ptr());
	memo[copyableId] = result;

	extract<dict>(result.attr("__dict__"))().update(
		deepcopy(extract<dict>(copyable.attr("__dict__"))(),
		memo));

	return result;
}

BOOST_PYTHON_MODULE(TestModule)
{
	class_<BaseClass, boost::shared_ptr<BaseClassWrap> >("BaseClass", init<>())
		.def(init<const BaseClass&>())
		.def(init<const BaseClassWrap&>())
		.def("GetID", &BaseClass::GetID, &BaseClassWrap::GetIDDefault)
		.def("Clone", &BaseClassWrap::CloneDefault)
		.def("Test", &BaseClass::Test, &BaseClassWrap::TestDefault)
		.def("__copy__", &generic__copy__< BaseClass >)
		.def("__deepcopy__", &bc_copy)
		;
}

//boost::unordered_map<std::string, boost::shared_ptr<

int BaseClass::IDCounter = 0;


int mainx()
{
	PyImport_AppendInittab("TestModule", initTestModule);
	Py_Initialize();

	try
	{
		auto EngineModule = object( (handle<>(PyImport_ImportModule("TestModule"))) );
		auto MainModule = object((handle<>(borrowed(PyImport_AddModule("__main__")))));
		auto MainNamespace = MainModule.attr("__dict__");
		MainNamespace["TestModule"] = EngineModule;

		object result = exec_file("D:\\FinalReport\\Test.py", MainNamespace, MainNamespace);

		object test = MainNamespace["test"];

		boost::shared_ptr<BaseClass> basec = extract<boost::shared_ptr<BaseClass> >(test());

		if (basec.get() != nullptr)
		{
			auto cl = basec->Clone();
			basec->Test();
			cl->Test();
			std::cout << "Original ID " << basec->GetID() << "\n";
			std::cout << "Original Test \n"; 
			basec->Test();
			std::cout << "\n";
			std::cout << "Clone ID " << cl->GetID() << "\n";
			std::cout << "Clone Test  \n"; 
			cl->Test();
			std::cout << "\n";
		}
	}
	catch (boost::python::error_already_set)
	{
		PyErr_Print();
	}


	return 0;
}