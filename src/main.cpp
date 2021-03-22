#include "parsecomb/combinators.hpp"
#include "parsecomb/generators.hpp"
#include "parsecomb/Parser.hpp"
#include "parsecomb/parsers.hpp"
#include "parsecomb/test_parser.hpp"
#include "util/echo.hpp"
#include <iostream>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>



using Token = std::string;
using Char = char;



auto char_range(char b, char e) -> Parser<Char>
{
    return [b,e](ParserIO<Char> const& input) -> ParserIO<char>
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



auto char_range(char b) -> Parser<Char>
{
    return char_range(b,b);
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



////////////////////////////////////////////////////////////////////////////////
int main()
{
    std::boolalpha(std::cout);
    using namespace std::string_view_literals;

    {
        std::vector<Token> const tokens1 {"hello", "world", "!"};
        std::vector<Token> const tokens2 {"hello", "hello", "world", "!"};
        std::vector<Token> const tokens3 {"hello", "hello", "hello", "world", "!"};

        auto const hello  = TokenParser(Token{"hello"});
        auto const hello2 = Exactly(2, hello);
        auto const e3     = Exactly<Token>(3);
        auto const ne2    = Not(Exactly<Token>(2));
        auto const n2h    = ne2(hello);

        test_parser(n2h, tokens1);
        test_parser(n2h, tokens2);
        test_parser(n2h, tokens3);
    }
    {
        auto const tp     = &TokenParser<Token>;

        auto const parens = NestedBetween(tp({"("}), tp({")"}));
        auto const hello  = tp("hello");

        auto const not_parens = Not(parens);

        std::vector<Token> const tokens1 {"(", "hello", ")", "(", "world", ")", "!"};
        std::vector<Token> const tokens2 {"hello", "world", "!"};

        test_parserw(32, parens(hello), tokens1);
        test_parserw(32, parens(hello), tokens2);
        test_parserw(32, not_parens(hello), tokens1);
        test_parserw(32, not_parens(hello), tokens2);
    }

    return 0;
}



////////////////////////////////////////////////////////////////////////////////
int main_archive()
{
    std::boolalpha(std::cout);
    using namespace std::string_view_literals;


    std::vector<Token> const tokens {"1_a", "a1", "abc123", "123abc"};

    auto const _     = char_range('_');
    auto const alpha = char_range('A', 'z');
    auto const digit = char_range('0', '9');

    auto const id_chars =
        Sequence(
            FirstMatch(alpha,_),
            Optional(OneOrMore(FirstMatch(alpha,FirstMatch(_,digit))))
        );

    auto const id       = make_token_parser(id_chars);

    auto const hello = TokenParser(Token{"hello"});
    auto const world = TokenParser(Token{"world"});
    auto const excl  = TokenParser(Token{"!"});

    std::vector<Token> const tokens2 {
        "(", "(", "hello", ")", ")", "(", "world", ")", "!"
    };

    auto const sentence = Sequence(hello, Sequence(world, excl));

    auto const l = TokenParser(Token{"("});
    auto const r = TokenParser(Token{")"});

    auto const grp = NestedBetween(l,r);

    auto const gh = grp(hello);
    ECHO_LN(gh(tokens2).is_success());
    ECHO_LN(gh(tokens2).size());

    return 0;
}
