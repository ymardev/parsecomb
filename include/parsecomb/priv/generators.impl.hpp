#include "parsecomb/generators.hpp"
#include "parsecomb/ParserIO.hpp"
#include <type_traits>



template <typename T>
auto TokenParser(T token) -> Parser<T>
{
    return [token=std::move(token)](ParserIO<T> const& input)
        -> ParserIO<T>
    {
        if (!input.is_empty()) {
            if (input[0] == token) {
                return input.succeed(1);
            }
        }
        return input.fail();
    };
}



template <typename T, typename Comp>
auto RangeParser(T beg, T end) -> Parser<T>
{
    return [beg=std::move(beg), end=std::move(end)](ParserIO<T> const& input)
        -> ParserIO<T>
    {
        if (!input.is_empty())
        {
            Comp less;

            auto const& elem = input[0];

            if (!less(elem,beg) && !less(end,elem)) {
                return input.succeed(1);
            }
        }
        return input.fail();
    };
}



template <typename T, typename U>
auto ConvertParser(Parser<U> p) -> Parser<T>
{
    return [p=std::move(p)](ParserIO<T> const& input) -> ParserIO<T>
    {
        if (!input.is_empty())
        {
            auto const out = p(input[0]);

            if (out.is_success() && out.is_empty()) {
                return input.succeed(1);
            }
        }
        return input.fail();
    };
}
