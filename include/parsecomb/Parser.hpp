#pragma once
#include "parsecomb/ParserIO.hpp"
#include <functional>
#include <type_traits>


template <typename T>
class Parser
{
public:
    using ParserIO      = ParserIO<T>;
    using function_type = std::function<ParserIO(ParserIO const&)>;

private:
    function_type m_function;

public:
    Parser() = default;

    template <typename Fn,
        typename =std::enable_if_t<std::is_convertible_v<Fn, function_type>>>
    Parser(Fn) noexcept;

    auto operator()(ParserIO const&) const -> ParserIO;
    auto operator()(Parser const&)   const -> Parser;

};



#include "parsecomb/priv/Parser.impl.hpp"
