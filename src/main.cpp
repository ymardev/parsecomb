#include "parsecomb/combinators.hpp"
#include "parsecomb/Parser.hpp"
#include "parsecomb/parsers.hpp"
#include "util/echo.hpp"
#include <iostream>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>



using Token = std::string;
using Char = char;



#define PARSER_TYPE_AND_CAPTURE_BLOCK(PD_TYPE, PD_CAPTURE...) \
    [PD_CAPTURE](ParserIO<PD_TYPE> const& input) -> ParserIO<PD_TYPE>


#define PARSER_PARSE_INPUT_BLOCK  \
    if (!input.is_empty())


#define PARSER_FAIL_INPUT       \
    return input.fail();



auto char_range(char b, char e) -> Parser<Char>
{
    // return PARSER_TYPE_AND_CAPTURE_BLOCK(Char, b, e)
    // {
    //     PARSER_PARSE_INPUT_BLOCK
    //     {
    //         auto const c = input.tokens()[0];
    //         ECHO_LN(c);
    //         if (!(c<b||c>e)) {
    //             return input.succeed(1);
    //         }
    //     }
    //     PARSER_FAIL_INPUT
    // };
    return [b,e](ParserIO<Char> const& input) -> ParserIO<char>
    {
        if (!input.is_empty()) {
            auto const c = *input.tokens().cbegin();
            if (!(c<b||c>e)) {
                return input.succeed(1);
            }
        }
        return input.fail();
    };
}

auto char_range(char b) -> Parser<Char> {return char_range(b,b);}



auto make_token_parser(std::string_view word) -> Parser<Token>
{
    return [word=std::string{word}](ParserIO<Token> const& input)
        -> ParserIO<Token>
    {
        if (!input.is_empty())
        {
            if (input.tokens()[0] == word) {
                return input.succeed(1);
            }
        }
        return input.fail();
    };
}



auto make_token_parser(Parser<Char> cp) -> Parser<Token>
{
    return [cp=std::move(cp)](ParserIO<Token> const& input) -> ParserIO<Token>
    {
        if (!input.is_empty())
        {
            auto const token_string = input[0];
            auto const char_out = cp(token_string);
            if (char_out.is_success() && char_out.is_empty()) {
                return input.succeed(1);
            }
        }
        return input.fail();
    };
}



int main()
{
    std::boolalpha(std::cout);
    using namespace std::string_view_literals;

    std::vector<Token> const tokens {"1_a", "a1", "abc123", "123abc"};

    auto const _     = char_range('_');
    auto const alpha = char_range('A', 'z');
    auto const digit = char_range('0', '9');

    auto const id_chars = Sequence(FirstMatch(alpha,_), OneOrMore(FirstMatch(alpha,FirstMatch(_,digit))));
    auto const id = make_token_parser(id_chars);

    auto const hello = make_token_parser("hello");
    auto const world = make_token_parser("world");
    auto const excl  = make_token_parser("!");

    std::vector<Token> const tokens2 {"hello", "world", "!"};
    auto const sentence = Sequence(hello, Sequence(world, excl));

    auto const out1 = sentence(tokens2);
    ECHO_LN(out1.is_success());
    ECHO_LN(out1.size());

    auto const outc1 = id_chars("1_a"sv);
    auto const outc2 = id_chars("a1"sv);
    auto const outc3 = id_chars("abc123"sv);
    auto const outc4 = id_chars("123abc"sv);

    ECHO_LN(outc1.is_success());
    ECHO_LN(outc1.size());
    std::cout << "outc1: ";
    for (auto const c : outc1.tokens()) {
        std::cout << c;
    }NL();
    ECHO_LN(outc2.is_success());
    ECHO_LN(outc2.size());
    std::cout << "outc2: ";
    for (auto const c : outc2.tokens()) {
        std::cout << c;
    }NL();
    ECHO_LN(outc3.is_success());
    ECHO_LN(outc3.size());
    std::cout << "outc3: ";
    for (auto const c : outc3.tokens()) {
        std::cout << c;
    }NL();
    ECHO_LN(outc4.is_success());
    ECHO_LN(outc4.size());
    std::cout << "outc4: ";
    for (auto const c : outc4.tokens()) {
        std::cout << c;
    }NL();


    // for (auto const& token : tokens)
    // {
    //     ECHO_LN(id(token).is_success());
    // }
    // ECHO_LN(id(tokens[0]).is_success());
    // ECHO_LN(id(tokens[1]).is_success());
    // ECHO_LN(id(tokens[2]).is_success());
    // ECHO_LN(id(tokens[3]).is_success());

    cspan const tokens_span {tokens};
    // for (auto const& token : tokens_span) {
    //     ECHO_LN(token);
    // }
    // for (auto const& token : tokens_span)
    // {
    //     ECHO_LN(id(token).is_success());
    // }
    ECHO_LN(id(tokens_span).is_success());
    ECHO_LN(id(cspan{tokens_span.cbegin(),   tokens_span.cend()}).is_success());
    ECHO_LN(id(cspan{tokens_span.cbegin()+1, tokens_span.cend()}).is_success());
    ECHO_LN(id(cspan{tokens_span.cbegin()+2, tokens_span.cend()}).is_success());
    ECHO_LN(id(cspan{tokens_span.cbegin()+3, tokens_span.cend()}).is_success());

    cspan const ts0 {&tokens[0], 1};
    cspan const ts1 {&tokens[1], 1};
    cspan const ts2 {&tokens[2], 1};
    cspan const ts3 {&tokens[3], 1};

    ECHO_LN(id(ts0).is_success());
    ECHO_LN(id(ts1).is_success());
    ECHO_LN(id(ts2).is_success());
    ECHO_LN(id(ts3).is_success());
}
