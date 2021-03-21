#pragma once
#include "parsecomb/priv/struct/cspan.hpp"
#include <type_traits>



template <typename T>
class ParserIO
{
    enum Status {Failure,Success} m_status;
    cspan<T>                      m_tokens_span;

public:
    using token_type = T;

public:
    ParserIO(cspan<token_type>) noexcept;

    template <typename U,
        typename = std::enable_if_t<std::is_convertible_v<U,cspan<T>>>>
    ParserIO(U&&) noexcept;

    auto fail()             const -> ParserIO;
    auto succeed(size_t)    const -> ParserIO;

    auto tokens()           const -> cspan<token_type> const&;
    auto size()             const -> size_t;
    auto is_success()       const -> bool;
    auto is_empty()         const -> bool;
    auto operator[](size_t) const -> token_type const&;


private:
    ParserIO(Status, cspan<token_type>) noexcept;

};



#include "parsecomb/priv/ParserIO.impl.hpp"
