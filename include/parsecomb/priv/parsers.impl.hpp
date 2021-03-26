#include "parsecomb/parsers.hpp"
#include "parsecomb/combinators.hpp"



template <typename T>
auto Some(ParserIO<T> const& input) -> ParserIO<T>
{
    if (!input.is_empty()) {
        return input.succeed(1);
    }
    return input.fail();
}



template <typename T>
auto No(ParserIO<T> const& input) -> ParserIO<T>
{
    if (input.is_empty()) {
        return input.succeed(0);
    }
    return input.fail();
}



template <typename T>
auto Any(ParserIO<T> const& input) -> ParserIO<T>
{
    if (input.is_empty()) {
        return input.succeed(0);
    } else {
        return input.succeed(1);
    }
}
