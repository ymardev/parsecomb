#include "parsecomb/priv/tcb/span.hpp"
#include "parsecomb/priv/cspan.hpp"
#include "parsecomb/ParserIO.hpp"
#include "util/echo.hpp"
#include <iostream>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>
#include <cstring>



using Token = std::string;


auto consume_token_io_1(ParserIO<Token> const& input) -> ParserIO<Token>
{
    return input.succeed(1);
}




int main()
{
    using tcb::span;
    std::vector<Token> const tokens {"hello", "world"};

    auto const it = tokens.begin();

    auto const* ptr = &tokens[0];

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

    // auto const io = ParserIO{s1};
    // auto const out1 = consume_token_io_1(io);
    // ECHO_LN(out1.size());
}
