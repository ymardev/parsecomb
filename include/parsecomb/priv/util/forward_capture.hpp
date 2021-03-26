/*

Forward capture for lambdas.

This file declares:
    class forward_capture<T>
    macro fwdcap

Usage:
    auto long_form  = [variable=forward_capture(variable)]() { ... };
    auto short_form = [fwdcap(variable)]() { ... };


*/
#pragma once
#include <tuple>




////////////////////////////////////////////////////////////////////////////////
#define fwdcap(MP_CAPTURE_VAR) MP_CAPTURE_VAR = forward_capture(MP_CAPTURE_VAR)



////////////////////////////////////////////////////////////////////////////////
template <typename T>
class forward_capture
{
    std::tuple<T> m_data;

public:
    constexpr forward_capture(T&& data) noexcept;

    constexpr T const& operator*()  const noexcept;
    constexpr T&       operator*()        noexcept;

    constexpr T const& operator->() const noexcept;
    constexpr T&       operator->()       noexcept;

};



template <typename T>
forward_capture(T&&) -> forward_capture<T>;




// inline impl.
////////////////////////////////////////////////////////////////////////////////
template <typename T>
constexpr forward_capture<T>::forward_capture(T&& data) noexcept:
    m_data {std::forward<T>(data)}
{
}



template <typename T>
constexpr T& forward_capture<T>::operator*() noexcept
{
    return std::get<0>(m_data);
}



template <typename T>
constexpr T const& forward_capture<T>::operator*() const noexcept
{
    return std::get<0>(m_data);
}



template <typename T>
constexpr T& forward_capture<T>::operator->() noexcept
{
    return *(*this);
}



template <typename T>
constexpr T const& forward_capture<T>::operator->() const noexcept
{
    return *(*this);
}
