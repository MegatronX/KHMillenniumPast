#ifndef __MATHGRAMMAR_H__
#define __MATHGRAMMAR_H__

#include <boost/spirit/include/classic.hpp>
using namespace BOOST_SPIRIT_CLASSIC_NS;

class MathFormula;

/**
 * Grammatic describing simple math expressions (using +, -, *, / operators and parentheses).
 */
class MathGrammar : public grammar<MathGrammar>
{
public:
    /**
     * Definition of productions.
     * This is internal structure required by Spirit functionality.
     */
    template <typename ScannerT>
    struct definition
    {
        // production definition
        definition( MathGrammar const& self )
        {
            expr    = term >> *( ( '+' >> term )[ self._doAdd ] | ( '-' >> term )[ self._doSub ] )
                      ;
            term    = fact >> *( ( '*' >> fact )[ self._doMul ] | ( '/' >> fact )[ self._doDiv ] )
                      ;
            fact    = real_p[ self._doConst ] |
                      ch_p('x')[ self._doArg ] |
                      group
                      ;
            group   = '(' >> expr >> ')'
                      ;
        }

        // non-terminals used in productions
        rule<ScannerT> expr, term, fact, group;

        // define starting non-terminal
        rule<ScannerT> const& start() const { return expr; }
    };

    /** 
     * C-tor.
     * @param formula pointer to MathFormula object where shell-code will be emitted.
     */
    MathGrammar( MathFormula *formula );

protected:

private:
    class AddFunctor
    {
    public:
        AddFunctor( MathGrammar *grammar );
        void operator()( const char*, const char* ) const;

    private:
        MathGrammar *_grammar;
    };

    class SubFunctor
    {
    public:
        SubFunctor( MathGrammar *grammar );
        void operator()( const char*, const char* ) const;

    private:
        MathGrammar *_grammar;
    };

    class MulFunctor
    {
    public:
        MulFunctor( MathGrammar *grammar );
        void operator()( const char*, const char* ) const;

    private:
        MathGrammar *_grammar;
    };

    class DivFunctor
    {
    public:
        DivFunctor( MathGrammar *grammar );
        void operator()( const char*, const char* ) const;

    private:
        MathGrammar *_grammar;
    };

    class ArgFunctor
    {
    public:
        ArgFunctor( MathGrammar *grammar );
        void operator()( char ) const;

    private:
        MathGrammar *_grammar;
    };

    class ConstFunctor
    {
    public:
        ConstFunctor( MathGrammar *grammar );
        void operator()( double ) const;

    private:
        MathGrammar *_grammar;
    };

    MathFormula *_formula;          // pointer to MathFormula object
    AddFunctor _doAdd;              // addition callback functor
    SubFunctor _doSub;              // subtraction callback functor
    MulFunctor _doMul;              // multiplication callback functor
    DivFunctor _doDiv;              // division callback functor
    ArgFunctor _doArg;              // argument callback functor
    ConstFunctor _doConst;          // constant value callback functor
};

#endif
