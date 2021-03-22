#include "parsecomb/combinators.hpp"
#include "parsecomb/ParserIO.hpp"



template <typename T>
auto Not(Parser<T> const& p) -> Parser<T>
{
    return [p](ParserIO<T> const& input) -> ParserIO<T>
    {
        if (!p(input).is_success()) {
            return input.succeed(1);
        }
        return input.fail();
    };
}



template <typename T>
auto Not(CombinatorUnary<T> const& c) -> CombinatorUnary<T>
{
    return [c](Parser<T> const& p) -> Parser<T>
    {
        return Not(c(p));
    };
}



template <typename T>
auto Not(CombinatorBinary<T> const& c) -> CombinatorBinary<T>
{
    return [c](Parser<T> const& p1, Parser<T> const& p2) -> Parser<T>
    {
        return Not(c(p1,p2));
    };
}



template <typename T>
auto Sequence(Parser<T> const& p1, Parser<T> const& p2) -> Parser<T>
{
    return [p1,p2](ParserIO<T> const& input) -> ParserIO<T>
    {
        auto const out1 = p1(input);
        if (out1.is_success()) {
            auto const out2 = p2(out1);
            if (out2.is_success()) {
                return out2;
            }
        }
        return input.fail();
    };
}



template <typename T>
auto FirstMatch(Parser<T> const& p1, Parser<T> const& p2) -> Parser<T>
{
    return [p1,p2](ParserIO<T> const& input) -> ParserIO<T>
    {
        auto const out1 = p1(input);
        return out1.is_success() ? out1 : p2(input);
    };
}



template <typename T>
auto BestMatch(Parser<T> const& p1, Parser<T> const& p2) -> Parser<T>
{
    return [p1,p2](ParserIO<T> const& input) -> ParserIO<T>
    {
        auto const out1 = p1(input);
        auto const out2 = p2(input);
        if (out1.is_success() && out2.is_success()) {
            return (out1.size() < out2.size()) ? out1 : out2;
        }
        else if (out1.is_succss()) {
            return out1;
        }
        else if (out2.is_succss()) {
            return out2;
        }
        return input.fail();
    };
}



template <typename T>
auto Optional(Parser<T> const& p) -> Parser<T>
{
    return [p](ParserIO<T> const& input) -> ParserIO<T>
    {
        return p(input).succeed(0);
    };
}



template <typename T>
auto OneOrMore(Parser<T> const& p) -> Parser<T>
{
    return [p](ParserIO<T> const& input) -> ParserIO<T>
    {
        auto out = p(input);
        if (!out.is_success()) {
            return input.fail();
        }
        while (out.is_success() && !out.is_empty())
        {
            out = p(out);
        }
        return out.succeed(0);
    };
}



template <typename T>
auto Several(Parser<T> const& p) -> Parser<T>
{
    return Sequence(p, OneOrMore(p));
}



template <typename T>
auto Exactly(size_t n, Parser<T> const& p) -> Parser<T>
{
    return [n,p](ParserIO<T> const& input) -> ParserIO<T>
    {
        size_t count = 0;
        auto out = input;

        while (count < n)
        {
            out = p(out);

            if (!out.is_success() || out.is_empty()) {
                break;
            }

            ++count;
        }

        if (n == count)
        {
            if (!out.is_empty() && !p(out).is_success())
            {
                return input.succeed(n);
            }
        }
        return input.fail();
    };
}



template <typename T>
auto Exactly(size_t n) -> CombinatorUnary<T>
{
    return [n](Parser<T> const& p) -> Parser<T>
    {
        return Exactly(n, p);
    };
}



template <typename T>
auto Between(Parser<T> const& pl, Parser<T> const& pr) -> CombinatorUnary<T>
{
    return [pl,pr](Parser<T> const& pm) -> Parser<T>
    {
        return Sequence(pl, Sequence(pm, pr));
    };
}



template <typename T>
auto NestedBetween(Parser<T> const& pl, Parser<T> const& pr)->CombinatorUnary<T>
{
    return [pl,pr](Parser<T> const& pm) -> Parser<T>
    {
        return [pl,pr,pm](ParserIO<T> const& input) -> ParserIO<T>
        {
            auto const out_l = pl(input);

            if (out_l.is_success())
            {
                auto const out_flat = Sequence(pm, pr)(out_l);

                if (out_flat.is_success()) {
                    return out_flat;
                }

                return Between(pl,pr)(NestedBetween(pl,pr)(pm))(input);
            }

            return input.fail();
        };
    };
}
