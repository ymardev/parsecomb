#include "parsecomb/priv/struct/cspan.hpp"
#include "parsecomb/ParserIO.hpp"
#include "util/echo.hpp"
#include <iostream>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>



using Token = std::string;


auto consume_token_io_1(ParserIO<Token> const& input) -> ParserIO<Token>
{
    return input.succeed(1);
}




int main()
{
    std::boolalpha(std::cout);
    std::vector<Token> const tokens {"hello", "world", "howdy", "today"};

    auto const it = tokens.begin();

    auto const* ptr = &tokens[0];

    ECHO_LN(is_iterator_v<decltype(ptr)>);
    ECHO_LN(is_iterator_v<decltype(tokens.begin())>);


    auto const s1 = cspan{&tokens[0], tokens.size()};
    auto const s2 = cspan{&tokens[0], &tokens[2]};
    auto const s3 = cspan{tokens.begin().operator->(), tokens.end().operator->()};
    auto const s4 = cspan{std::string_view{"tokens[0]"}};
    auto const s5 = cspan{"hello!"};

    int ri[3] {1,2,3};
    auto const s6 = cspan{ri};

    for (auto const& t : s4) {
        ECHO_LN(t);
    }

    auto const io1 = ParserIO{s1};
    auto const io2 = ParserIO<Token>{std::string_view{"hello"}};

    auto const out1 = consume_token_io_1(io1);
    auto const out2 = consume_token_io_1(out1);
    ECHO_LN(out1.size());
    ECHO_LN(out2.size());

    cspan const s7 {tokens};

    auto const s7e = s7.last(0);
    for (auto const& t : s7e) {
        ECHO_LN(t);
    }
    ECHO_LN(s7e.size());
    ECHO_LN(s7e.empty());

    ParserIO<Token> out = s7;
    do {
        ECHO_LN(out.tokens()[0]);
        ECHO_LN(out.size());
        out = consume_token_io_1(out);
    } while (!out.is_empty());

}
