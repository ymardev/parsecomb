#pragma once
#include "parsecomb/parsecomb.hpp"
#include "parsecomb/test_parser.hpp"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>


// Say we have a source code in an imaginary PL, this would be the type of all
// tokens, like 'hello', '{', '&&', etc.
using StringToken = std::string;


// This is another type of tokens. The thing is, in our project it is type of
// tokens that we can find *inside* our 'main' type of tokens (StringToken). We
// can look inside a string and treat it as a contiguous range of CharToken
// tokens.
using CharToken = char;


// This is a parser generator. It returns a parser that just looks at the next
// character in the input string, and consumes it successfully if it is included
// in the range defined by the parameters to the function.
auto char_range(char b, char e) -> Parser<CharToken>
{
    return [b,e](ParserIO<CharToken> const& input) -> ParserIO<char>
    {
        if (!input.is_empty()) {
            auto const c = input[0];
            if (!(c<b||c>e)) {
                return input.succeed(1);
            }
        }
        return input.fail();
    };
}


// A shorthand for making a parser matching one single character.
auto char_range(char b) -> Parser<CharToken>
{
    return char_range(b,b);
}


// Here we'll tie it together.
void parser_conversion_sample()
{
    // We define some primitive ranges of characters by creating actual parsers
    // for them.
    auto const _     = TokenParser('_');
    auto const alpha = RangeParser('A', 'z');
    auto const digit = RangeParser('0', '9');


    // We use combinators to specify what an identifier is allowed to be in our
    // grammar. Here, it must begin with an underscore or an alpha character,
    // but then it can have any number of either of those and digits.
    auto const identifier_char_parser =
        Sequence(
            FirstMatch(alpha, _),
            Optional(OneOrMore(FirstMatch(alpha, FirstMatch(_, digit))))
        );


    // Combinators only work with a single type of parsers, we cannot mix a
    // Parser<CharToken> with a Parser<StringToken> in a combination. But it
    // just happens that a StringToken is a collection of CharTokens, so we can
    // call a Parser<CharToken> with a StringToken, that will be used as an
    // array of characters - the input to the parser. So we can convert the
    // parser.
    auto const identifier_token_parser
        = ConvertParser<StringToken>(identifier_char_parser);


    // A collection of tokens: the input.
    std::vector<StringToken> const tokens {"ab_cd", "_abcd", "1abcd"};


    // We can now use this parser to validate (or not) a token as an identifier.
    test_parser(identifier_token_parser, tokens[0]); // OK
    test_parser(identifier_token_parser, tokens[1]); // OK
    test_parser(identifier_token_parser, tokens[2]); // Wrong, begins with digit

}
