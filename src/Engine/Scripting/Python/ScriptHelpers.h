#pragma once
#ifndef _PYTHONSCRIPTHELPERS_H_
#define _PYTHONSCRIPTHELPERS_H_


#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/python.hpp>
using namespace boost::python;

	template < class T >
	T* GetPointer(T& t)
	{
		return &t;
	}
#define PYTHON_ERROR(TYPE, REASON) \
	{ \
	PyErr_SetString(TYPE, REASON); \
	throw error_already_set(); \
	}

	template<class T>
	inline PyObject * managingPyObject(T *p)
	{
		return typename manage_new_object::apply<T *>::type()(p);
	}

	/*template<class Copyable>
	object
		generic__copy__(object copyable)
	{
		Copyable *newCopyable(new Copyable(extract<const Copyable
			&>(copyable)));
		//object result(boost::python::detail::new_reference(managingPyObject(newCopyable)));

		//object result(extract<const Copyable &>(copyable)());

		const Copyable & tmp = extract<const Copyable &>(copyable);
		object result(tmp);

		extract<dict>(result.attr("__dict__"))().update(
			copyable.attr("__dict__"));

		return result;
	}

	template<class Copyable>
	object
		generic__deepcopy__(object copyable, dict memo)
	{
		object copyMod = import("copy");
		object deepcopy = copyMod.attr("deepcopy");

		Copyable *newCopyable(new Copyable(extract<const Copyable
			&>(copyable)));
		//object result(boost::python::detail::new_reference(managingPyObject(newCopyable)));

		//object result(extract<const Copyable &>(copyable)());

		const Copyable & tmp = extract<const Copyable &>(copyable);
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
	}*/

	template<class Copyable>
	object
		generic__copy__(object copyable)
	{
		Copyable *newCopyable(new Copyable(extract<const Copyable
			&>(copyable)));
		object
			result(boost::python::detail::new_reference(managingPyObject(newCopyable)));

		extract<dict>(result.attr("__dict__"))().update(
			copyable.attr("__dict__"));

		return result;
	}

	template<class Copyable>
	object
		generic__deepcopy__(object copyable, dict memo)
	{
		object copyMod = import("copy");
		object deepcopy = copyMod.attr("deepcopy");

		Copyable *newCopyable(new Copyable(extract<const Copyable
			&>(copyable)));
		object
			result(boost::python::detail::new_reference(managingPyObject(newCopyable)));

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
	

	template <class Container> 
	class vector_ptr_indexing_suite 
		: public vector_indexing_suite<Container, true, 
		vector_ptr_indexing_suite<Container> > 
	{ 
	public: 
		typedef boost::python::iterator<Container, return_value_policy<reference_existing_object>> 
			def_iterator; 

		template <class Class> 
		static void 
			extension_def(Class & cl) 
		{ 
			vector_indexing_suite<Container, true, 
				vector_ptr_indexing_suite<Container>>::extension_def(cl); 

			cl.def("__iter__", def_iterator()); 
		} 
	}; 



#endif