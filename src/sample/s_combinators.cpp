#include "parsecomb/parsecomb.hpp"
#include "parsecomb/test_parser.hpp"
#include <string>
#include <vector>


using Token = std::string;



void combinators_sample()
{
    auto const hello       = TokenParser<Token>("hello");
    auto const world       = TokenParser<Token>("world");
    auto const paren_left  = TokenParser<Token>("(");
    auto const paren_right = TokenParser<Token>(")");
    auto const in_parens   = Between(paren_left, paren_right);
    auto const no_parens   = Not(in_parens);

    std::vector<Token> const tokens1 {
        "hello", "world", "!"
    };

    std::vector<Token> const tokens2 {
        "(", "hello", ")", "(", "world", ")", "!"
    };


    test_parserw(56, Sequence(hello, world), tokens1);
    test_parserw(56, Sequence(hello, world), tokens2);
    test_parserw(56, Sequence(in_parens(hello), in_parens(world)), tokens1);
    test_parserw(56, Sequence(in_parens(hello), in_parens(world)), tokens2);
    test_parserw(56, Sequence(no_parens(hello), no_parens(world)), tokens1);
    test_parserw(56, Sequence(no_parens(hello), no_parens(world)), tokens2);

}
