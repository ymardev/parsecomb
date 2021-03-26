#include "parsecomb/parsecomb.hpp"
#include "parsecomb/test_parser.hpp"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>


// A token may contain other information beside its value, for instance position
// in source. But here we'll just have string value.
struct Token
{
    std::string value;

    Token(const char* val): value {val} {}
};


// This program will work with two different Parser types :
// Parser<Token> and Parser<char>.
// char is another type of token too, because we can treat the value of 'Token',
// which is string, as a collection of char.
void parser_conversion_sample()
{
    // We define some primitive ranges, building blocks.
    Parser<char> const _ = TokenParser<char>('_');
    auto const alpha     = RangeParser<char>('A', 'z');     // A-Z, a-z
    auto const digit     = RangeParser<char>('0', '9');


    // We use combinators to specify what an identifier is allowed to look like.
    // Here, it must begin with an underscore or an alpha character, but then
    // it can have any number of either of those and digits.
    Parser<char> const identifier_char_parser =
        Sequence(
            FirstMatch(alpha, _),
            Optional(OneOrMore(FirstMatch(alpha, FirstMatch(_, digit))))
        );


    // Combinators only work with a single type of parsers, we cannot mix a
    // Parser<char> with a Parser<Token> in a combination.
    // But, it turns out that we can call a Parser<char> with a Token's value
    // as input.
    // We just need to tell the Parser<char> how to get its input from a Token.
    Parser<Token> const identifier_parser =
        ConvertParser<Token>(
            [](Token const& token) {return token.value;},
            identifier_char_parser
        );


    // The input: a collection of tokens.
    std::vector<Token> const tokens {"ab_cd", "_abcd", "1abcd"};


    // We can now use the Parser<Token> to validate (or not) input as identifier.
    test_parser(identifier_parser, tokens[0]); // OK
    test_parser(identifier_parser, tokens[1]); // OK
    test_parser(identifier_parser, tokens[2]); // Wrong, begins with digit

    // If we want to consume as many identifiers we can from the input:
    test_parser(OneOrMore(identifier_parser), tokens); // success: 2, remains: 1

}
