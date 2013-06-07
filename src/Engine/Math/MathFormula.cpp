#include "MathFormula.h"
#include "MathGrammar.h"
#include <boost/spirit/include/classic.hpp>
#include <windows.h>
#include <string>

#define MEM_SEG_SIZE 256                          // maximum code segment size use in program

using namespace BOOST_SPIRIT_CLASSIC_NS;

MathFormula::MathFormula() : 
    _code( NULL ),
    _emitPtr( NULL ),
    _codeSize( 0 ),
    _constTableSize( 0 )
{
}

MathFormula::MathFormula( const char* str ) :
    _code( NULL ),
    _emitPtr( NULL ),
    _codeSize( 0 ),
    _constTableSize( 0 )
{
    // perform initializations
    this->Init( str );
}

MathFormula::~MathFormula()
{
    // dispose resources
    this->Dispose();
}

float MathFormula::operator()( float arg ) const
{
    // call generated shell-code
    return _fun( arg );
}

void MathFormula::Init( const char* str )
{
    std::string inputStr( str );                  
    MathGrammar calc( this );

    // remove all spaces from input string
    for ( size_t i = 0 ; i < inputStr.length(); i++ )
        if ( inputStr[ i ] == ' ' ) 
        {
            inputStr.erase( i, 1 );
            i--;
        }

    // dispose allocated reasources, if there were any
    this->Dispose();

    // start emission
    this->startEmission();

    // perform string parsing
    if ( false == parse( inputStr.c_str(), calc ).full )
        throw std::exception( "Formula parse error!" );

    // end emission
    this->stopEmission();
}

void MathFormula::Dispose()
{
    // deallocate memory segment
    if ( _code != NULL )
    {
        BOOL res = ::VirtualFree( _code, 0, MEM_RELEASE );
        if ( FALSE == res )
            throw std::exception( "VirtualFree error, memory deallocation failed!" );
    }

    // reset variables
    _code = NULL;
    _codeSize = 0;
    _emitPtr = NULL;
    _fun = NULL;
    _constTableSize = 0;
}

void MathFormula::startEmission()
{
    // ensure that memory segment is not allocated
    this->Dispose();

    // allocate memory segment with read/write access
    _code = ::VirtualAlloc( NULL, MEM_SEG_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
    if ( NULL == _code )
        throw std::exception( "VirtualAlloc error, memory allocation failed!" );

    // reset used variables
    _emitPtr = (char*)_code;
    _codeSize = 0;
    _constTableSize = 0;
    _fun = ( float (*)( float ) )_code;

    // emit header
    this->emitHeader();
}

void MathFormula::stopEmission()
{
    // emit footer
    this->emitFooter();

    // change access protection for memory segment to execute only
    DWORD oldProtect;
    BOOL res = ::VirtualProtect( _code, MEM_SEG_SIZE, PAGE_EXECUTE, &oldProtect );
    if ( FALSE == res )
        throw std::exception( "VirtualProtect error, cannot change memory access rights!" );
}

void MathFormula::emitCode( const void *ptr, size_t size )
{
    if ( NULL != _emitPtr && NULL != ptr )
    {
        // check if there isn't code memory overflow
        if ( _codeSize + size > MEM_SEG_SIZE )
            throw std::exception( "Emitted shell-code is too large!" );

        // append code fragment to the code segment
        ::memcpy( _emitPtr, ptr, size );
        _emitPtr += size;
        _codeSize += size;
    }
}

void MathFormula::emitHeader()
{
    // opcode - PUSH ebp
    char opcode_PUSH[] = { '\x55' };

    // opcode - MOV ebp, esp
    char opcode_MOV[] = { '\x8B', '\xEC' };

    // emit code
    emitCode( opcode_PUSH, sizeof( opcode_PUSH ) );
    emitCode( opcode_MOV, sizeof( opcode_MOV ) );
}

void MathFormula::emitFooter()
{
    // opcode - POP ebp
    char opcode_POP[] = { '\x5D' };

    // opcode - RET
    char opcode_RET[] = { '\xC3' };

    // emit code
    emitCode( opcode_POP, sizeof( opcode_POP ) );
    emitCode( opcode_RET, sizeof( opcode_RET ) );
}

void MathFormula::emitArg()
{
    // opcode - FLD dword ptr [ebp+8]
    char opcode_FLD[] = { '\xD9', '\x45', '\x08' };

    // emit code
    emitCode( opcode_FLD, sizeof( opcode_FLD ) );
}

void MathFormula::emitAddition()
{
    // opcode - FADDP st(1), st(0)
    char opcode_FADDP[] = { '\xDE', '\xC1' };

    // emit code
    emitCode( opcode_FADDP, sizeof( opcode_FADDP ) );
}

void MathFormula::emitSubstraction()
{
    // opcode - FSUBP st(1), st(0)
    char opcode_FSUBP[] = { '\xDE', '\xE9' };

    // emit code
    emitCode( opcode_FSUBP, sizeof( opcode_FSUBP ) );
}

void MathFormula::emitMultiplication()
{
    // opcode - FMULP st(1), st(0)
    char opcode_FMULP[] = { '\xDE', '\xC9' };

    // emit code
    emitCode( opcode_FMULP, sizeof( opcode_FMULP ) );
}

void MathFormula::emitDivision()
{
    // opcode - FDIVP st(1), st(0)
    char opcode_FDIVP[] = { '\xDE', '\xF9' };

    // emit code
    emitCode( opcode_FDIVP, sizeof( opcode_FDIVP ) );
}

void MathFormula::emitConstant( float constant )
{
    // check if there is free space in constant table
    if ( _constTableSize + 1 > MAX_NO_OF_CONSTANTS )
        throw std::exception( "Number of constants exceeded!" );

    // opcode FLD [mem32]
    char opcode_FLD[] = { '\xD9', '\x05' };

    // emit code
    emitCode( opcode_FLD, sizeof( opcode_FLD ) );

    // add constant to constant table
    _constTable[ _constTableSize ] = constant;
    _constTableSize++;

    // emit argument for FLD [mem32] opcode
    float *constPtr = _constTable + _constTableSize - 1;
    emitCode( &constPtr, sizeof( float ) );
}
