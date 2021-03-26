#include "parsecomb/parsecomb.hpp"
#include "parsecomb/test_parser.hpp"
#include <string>
#include <vector>


using StringToken = std::string;



void combinators_sample()
{
    auto const hello       = TokenParser<StringToken>("hello");
    auto const world       = TokenParser<StringToken>("world");
    auto const paren_left  = TokenParser<StringToken>("(");
    auto const paren_right = TokenParser<StringToken>(")");
    auto const in_parens   = Between(paren_left, paren_right);
    auto const no_parens   = Not(in_parens);

    std::vector<StringToken> const tokens1 {
        "hello", "world", "!"
    };

    std::vector<StringToken> const tokens2 {
        "(", "hello", ")", "(", "world", ")", "!"
    };


    test_parserw(56, Sequence(hello, world), tokens1);
    test_parserw(56, Sequence(hello, world), tokens2);
    test_parserw(56, Sequence(in_parens(hello), in_parens(world)), tokens1);
    test_parserw(56, Sequence(in_parens(hello), in_parens(world)), tokens2);
    test_parserw(56, Sequence(no_parens(hello), no_parens(world)), tokens1);
    test_parserw(56, Sequence(no_parens(hello), no_parens(world)), tokens2);

}
