#ifndef __MATHFORMULA_H__
#define __MATHFORMULA_H__

#define MAX_NO_OF_CONSTANTS 256                         // maximum number of constants used in program

/**
 * Class encapsulating fast polymorphic math parser.
 * Usage: just create new object using constructor with given input string and
 * call overloaded () operator to perform math formula evaluation.
 */
class MathFormula
{
    friend class MathGrammar;                           // MathGrammar calls this class' methods

public:
    /**
     * Default c-tor.
     * When object is created using this c-tor, later it must be initialized with Init method.
     */
    MathFormula();

    /**
     * C-tor.
     * @param str input string containing math expression.
     */
    MathFormula( const char* str );

    /**
     * De-tor.
     */
    ~MathFormula();

    /**
     * Init MathFormula object.
     * This method duplicates must be invoked when object was created with usage of default c-tor.
     * @param str input string containing math expression.
     */
    void Init( const char* str );

    /**
     * Dispose used resources.
     * This method is called in de-tor.
     */
    void Dispose();

    /**
     * Overloaded () operator.
     * This operator should be invoked for evaluation of parsed math expression.
     * @param x function argument.
     * @return calculated value
     */
    float operator()( float x ) const;

protected:

private:
    void *_code;                                        // pointer to code segment
    size_t _codeSize;                                   // used size of code segment
    char *_emitPtr;                                     // pointer at the end of emitted code
    float ( __cdecl *_fun )( float );                   // pointer to code segment in cdecl function format

    float _constTable[ MAX_NO_OF_CONSTANTS ];           // table of constants used in function
    size_t _constTableSize;                             // number of used constant in constant's table

    void startEmission();                               // start emission process
    void stopEmission();                                // stop emission process
    void emitCode( const void *ptr, size_t size );      // append given data to code segment
    void emitHeader();                                  // emit standard function start.
    void emitFooter();                                  // emit standard function ending.
    void emitArg();                                     // emit argument load
    void emitAddition();                                // emit add operation
    void emitSubstraction();                            // emit sub operation
    void emitMultiplication();                          // emit mul operation
    void emitDivision();                                // emit div operation
    void emitConstant( float constant );                // emit constant load
};

#endif
