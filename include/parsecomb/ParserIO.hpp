#pragma once
#include "parsecomb/priv/struct/cspan.hpp"
#include <type_traits>



template <typename T>
class ParserIO
{
    enum Status {Failure,Success} m_status;
    cspan<T>                      m_tokens_span;

public:
    ParserIO(cspan<T>) noexcept;

    template <typename...Args>
    ParserIO(Args&&... args) noexcept;

    auto fail()          const -> ParserIO;
    auto succeed(size_t) const -> ParserIO;

    auto tokens()        const -> cspan<T> const&;
    auto size()          const -> size_t;
    auto is_success()    const -> bool;
    auto is_empty()      const -> bool;

private:
    ParserIO(Status, cspan<T>) noexcept;

};



#include "parsecomb/priv/ParserIO.impl.hpp"
