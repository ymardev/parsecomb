#include "parsecomb/Parser.hpp"



template <typename T>
template <typename Fn, typename>
Parser<T>::Parser(Fn fn) noexcept:
    m_function {std::move(fn)}
{
}



////////////////////////////////////////////////////////////////////////////////
template <typename T>
auto Parser<T>::operator()(ParserIO const& input) const -> ParserIO
{
    return m_function(input);
}



template <typename T>
auto Parser<T>::operator()(Parser const& other_parser) const -> Parser
{
    auto const& this_function  = m_function;
    auto const& other_function = other_parser.m_function;
    return Parser {
        [this_function,other_function](ParserIO const& input) -> ParserIO
        {
            return other_function(this_function(input));
        }
    };
}
