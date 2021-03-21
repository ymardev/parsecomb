#include "parsecomb/ParserIO.hpp"
#include <cassert>



template <typename T>
ParserIO<T>::ParserIO(cspan<token_type> tokens) noexcept:
    m_status     {Status::Failure},
    m_tokens_span{std::move(tokens)}
{
}



template <typename T>
template <typename U, typename>
ParserIO<T>::ParserIO(U&& arg) noexcept:
    m_status {Failure},
    m_tokens_span {std::forward<U>(arg)}
{
}



// private ctor
template <typename T>
ParserIO<T>::ParserIO(Status stat, cspan<token_type> tokens) noexcept:
    m_status     {stat},
    m_tokens_span{std::move(tokens)}
{
}



////////////////////////////////////////////////////////////////////////////////
template <typename T>
auto ParserIO<T>::fail() const -> ParserIO
{
    return {Status::Failure, m_tokens_span};
}



template <typename T>
auto ParserIO<T>::succeed(size_t consume_count) const -> ParserIO
{
    auto const keep_count = m_tokens_span.size()-consume_count;
    // assert(keep_count <= m_tokens_span.size());
    if (keep_count > m_tokens_span.size()) {
        return {Status::Success, {}};
    }
    return {Status::Success, m_tokens_span.last(keep_count)};
}



////////////////////////////////////////////////////////////////////////////////
template <typename T>
auto ParserIO<T>::tokens() const -> cspan<token_type> const&
{
    return m_tokens_span;
}



template <typename T>
auto ParserIO<T>::size() const -> size_t
{
    return m_tokens_span.size();
}



template <typename T>
auto ParserIO<T>::is_success() const -> bool
{
    return (m_status==Status::Success);
}



template <typename T>
auto ParserIO<T>::is_empty() const -> bool
{
    return m_tokens_span.empty();
}



template <typename T>
auto ParserIO<T>::operator[](size_t idx) const -> token_type const&
{
    return m_tokens_span[idx];
}
