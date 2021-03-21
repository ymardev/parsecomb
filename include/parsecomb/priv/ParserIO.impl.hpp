#include "parsecomb/ParserIO.hpp"



template <typename T>
ParserIO<T>::ParserIO(cspan<token_type> tokens) noexcept:
    m_status     {Status::Failure},
    m_token_span {std::move(tokens)}
{
}



template <typename T>
template <typename U, typename>
ParserIO<T>::ParserIO(U&& arg) noexcept:
    m_status     {Failure},
    m_token_span {std::forward<U>(arg)}
{
}



// private ctor
template <typename T>
ParserIO<T>::ParserIO(Status stat, cspan<token_type> tokens) noexcept:
    m_status     {stat},
    m_token_span {std::move(tokens)}
{
}



////////////////////////////////////////////////////////////////////////////////
template <typename T>
auto ParserIO<T>::fail() const -> ParserIO
{
    return {Status::Failure, m_token_span};
}



template <typename T>
auto ParserIO<T>::succeed(size_t consume_count) const -> ParserIO
{
    if (consume_count >= size()) {
        return {Status::Success, {}};
    }
    long long const keep_count = size()-consume_count;
    return {Status::Success, m_token_span.last(keep_count)};
}



////////////////////////////////////////////////////////////////////////////////
template <typename T>
auto ParserIO<T>::tokens() const -> cspan<token_type> const&
{
    return m_token_span;
}



template <typename T>
auto ParserIO<T>::size() const -> size_t
{
    return m_token_span.size();
}



template <typename T>
auto ParserIO<T>::is_success() const -> bool
{
    return (m_status==Status::Success);
}



template <typename T>
auto ParserIO<T>::is_empty() const -> bool
{
    return m_token_span.empty();
}



template <typename T>
auto ParserIO<T>::operator[](size_t idx) const -> token_type const&
{
    return m_token_span[idx];
}
