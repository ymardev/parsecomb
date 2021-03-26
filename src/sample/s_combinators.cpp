#include "parsecomb/parsecomb.hpp"
#include "parsecomb/test_parser.hpp"
#include <string>
#include <vector>


using Token = std::string;



void combinators_sample()
{
    // define parsers of type Parser<Token>
    auto const hello       = TokenParser<Token>("hello");
    auto const world       = TokenParser<Token>("world");
    auto const paren_left  = TokenParser<Token>("(");
    auto const paren_right = TokenParser<Token>(")");


    // define combinators
    auto const in_parens   = Between(paren_left, paren_right);
    auto const no_parens   = Not(in_parens);


    // two sets of input
    std::vector<Token> const tokens1 {
        "hello", "world", "!"
    };

    std::vector<Token> const tokens2 {
        "(", "hello", ")", "(", "world", ")"
    };


    // Combine the above parsers into sequences.
    // Output of test_parser is of format:  [is_success, remaining_count]
    test_parserw(56, Sequence(hello, world), tokens1);
    test_parserw(56, Sequence(hello, world), tokens2);
    test_parserw(56, Sequence(in_parens(hello), in_parens(world)), tokens1);
    test_parserw(56, Sequence(in_parens(hello), in_parens(world)), tokens2);
    test_parserw(56, Sequence(no_parens(hello), no_parens(world)), tokens1);
    test_parserw(56, Sequence(no_parens(hello), no_parens(world)), tokens2);


    // Parse both "hello" and "(hello)"
    test_parserw(56, FirstMatch(hello, in_parens(hello)), tokens1);
    test_parserw(56, FirstMatch(hello, in_parens(hello)), tokens2);


    // Consume several Tokens, each being between parentheses
    test_parserw(56, Several(in_parens(Some<Token>)), tokens1);
    test_parserw(56, Several(in_parens(Some<Token>)), tokens2);

}
