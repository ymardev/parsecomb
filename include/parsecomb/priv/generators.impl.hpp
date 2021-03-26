#include "parsecomb/generators.hpp"
#include "parsecomb/ParserIO.hpp"
#include "parsecomb/priv/util/forward_capture.hpp"



template <typename T, typename Equal>
auto TokenParser(T token, Equal&& is_equal) -> Parser<T>
{
    return [token=std::move(token), fwdcap(is_equal)](ParserIO<T> const& input)
        -> ParserIO<T>
    {
        if (!input.is_empty()) {
            if ((*is_equal)(input[0], token)) {
                return input.succeed(1);
            }
        }
        return input.fail();
    };
}



template <typename T, typename Less>
auto RangeParser(T beg, T end, Less&& is_less) -> Parser<T>
{
    return [beg=std::move(beg), end=std::move(end), fwdcap(is_less)]
        (ParserIO<T> const& input) -> ParserIO<T>
    {
        if (!input.is_empty())
        {
            auto const& elem = input[0];

            if (!(*is_less)(elem,beg) && !(*is_less)(end,elem)) {
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



template <typename T, typename Fn, typename U>
auto ConvertParser(Fn convert, Parser<U> p) -> Parser<T>
{
    return [p=std::move(p),convert=std::move(convert)](ParserIO<T> const& input)
        -> ParserIO<T>
    {
        if (!input.is_empty())
        {
            auto const out = p(convert(input[0]));

            if (out.is_success() && out.is_empty()) {
                return input.succeed(1);
            }
        }
        return input.fail();
    };
}
