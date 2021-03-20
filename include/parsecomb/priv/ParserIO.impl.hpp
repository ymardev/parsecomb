#include "parsecomb/ParserIO.hpp"
#include <cassert>



template <typename T>
ParserIO<T>::ParserIO(cspan<T> tokens) noexcept:
    m_status     {Status::Failure},
    m_tokens_span{std::move(tokens)}
{
}



template <typename T>
template <typename...Args>
ParserIO<T>::ParserIO(Args&&... args) noexcept:
    m_status {Failure},
    m_tokens_span {std::forward<Args>(args)...}
{
}



// private ctor
template <typename T>
ParserIO<T>::ParserIO(Status stat, cspan<T> tokens) noexcept:
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
    assert(keep_count < m_tokens_span.size());
    return {Status::Success, m_tokens_span.last(keep_count)};
}



template <typename T>
auto ParserIO<T>::tokens() const -> cspan<T> const&
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
