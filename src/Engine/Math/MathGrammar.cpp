#include "MathGrammar.h"
#include "MathFormula.h"
#include <boost/spirit/include/classic.hpp>

#ifdef _MSC_VER
#   pragma warning( disable : 4355 )
#endif

using namespace BOOST_SPIRIT_CLASSIC_NS;

MathGrammar::MathGrammar( MathFormula *formula ) :
    _formula( formula ),
    _doAdd( this ),
    _doSub( this ),
    _doMul( this ),
    _doDiv( this ),
    _doArg( this ),
    _doConst( this )
{
}

MathGrammar::AddFunctor::AddFunctor( MathGrammar *grammar ) : 
    _grammar( grammar ) 
{
}

void MathGrammar::AddFunctor::operator()( const char*, const char* ) const
{
    if ( NULL != _grammar && NULL != _grammar->_formula )
        _grammar->_formula->emitAddition();
}

MathGrammar::SubFunctor::SubFunctor( MathGrammar *grammar ) : 
    _grammar( grammar )
{
}

void MathGrammar::SubFunctor::operator()( const char*, const char* ) const
{
    if ( NULL != _grammar && NULL != _grammar->_formula )
        _grammar->_formula->emitSubstraction();
}

MathGrammar::MulFunctor::MulFunctor( MathGrammar *grammar ) : 
    _grammar( grammar ) 
{
}

void MathGrammar::MulFunctor::operator()( const char*, const char* ) const
{
    if ( NULL != _grammar && NULL != _grammar->_formula )
        _grammar->_formula->emitMultiplication();
}

MathGrammar::DivFunctor::DivFunctor( MathGrammar *grammar ) : 
    _grammar( grammar ) 
{
}

void MathGrammar::DivFunctor::operator()( const char*, const char* ) const
{
    if ( NULL != _grammar && NULL != _grammar->_formula )
        _grammar->_formula->emitDivision();
}

MathGrammar::ArgFunctor::ArgFunctor( MathGrammar *grammar ) : 
    _grammar( grammar ) 
{
}

void MathGrammar::ArgFunctor::operator()( char ) const
{
    if ( NULL != _grammar && NULL != _grammar->_formula )
        _grammar->_formula->emitArg();
}

MathGrammar::ConstFunctor::ConstFunctor( MathGrammar *grammar ) : 
    _grammar( grammar ) 
{
}

void MathGrammar::ConstFunctor::operator()( double constant ) const
{
    if ( NULL != _grammar && NULL != _grammar->_formula )
        _grammar->_formula->emitConstant( (float)constant );
}
