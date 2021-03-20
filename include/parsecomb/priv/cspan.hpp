#pragma once
#include <array>
#include <cstddef>
#include <iterator>
#include <tuple>
#include <type_traits>



namespace impl
{
    template <typename U>
    using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<U>>;
}



template <typename T>
class cspan
{
public:
    using value_type             = impl::remove_cvref_t<T>;
    using pointer                = value_type const*;
    using const_pointer          = value_type const*;
    using iterator               = const_pointer;
    using const_iterator         = iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using reference              = value_type const&;
    using const_reference        = value_type const&;
    using size_type              = std::size_t;

private:
    pointer     _begin;
    size_type   _size;

public:
    constexpr cspan(pointer, size_type) noexcept;
    constexpr cspan(pointer, pointer) noexcept;

    template <size_t Sz>
    constexpr cspan(T(&array)[Sz]) noexcept;

    template <size_t Sz>
    constexpr cspan(T const(&array)[Sz]) noexcept;

    template <size_t Sz>
    constexpr cspan(std::array<T, Sz>) noexcept;

    template <template <class,class...> typename C, typename U, typename...Ts>
    constexpr cspan(C<U,Ts...> const& c) noexcept;

    constexpr auto size()     const -> size_type;
    constexpr auto empty()    const -> bool;

    constexpr auto operator[](size_type) const -> const_reference;

    constexpr auto first(size_type) const -> cspan;
    constexpr auto last(size_type)  const -> cspan;

    constexpr auto begin()    const -> const_iterator;
    constexpr auto end()      const -> const_iterator;
    constexpr auto cbegin()   const -> const_iterator;
    constexpr auto cend()     const -> const_iterator;
    constexpr auto rbegin()   const -> const_reverse_iterator;
    constexpr auto rend()     const -> const_reverse_iterator;
    constexpr auto crbegin()  const -> const_reverse_iterator;
    constexpr auto crend()    const -> const_reverse_iterator;
};



////////////////////////////////////////////////////////////////////////////////
template <typename T>
cspan(T, size_t)        -> cspan<typename std::iterator_traits<T>::value_type>;

template <typename T>
cspan(T, T)             -> cspan<typename std::iterator_traits<T>::value_type>;

template <typename T, size_t Sz>
cspan(T(&array)[Sz])    -> cspan<impl::remove_cvref_t<T>>;

template <typename T, size_t Sz>
cspan(std::array<T,Sz>) -> cspan<impl::remove_cvref_t<T>>;

template <template <class,class...> typename C, typename T, typename...Ts>
cspan(C<T,Ts...> const&)-> cspan<impl::remove_cvref_t<T>>;



////////////////////////////////////////////////////////////////////////////////
template <typename T, typename...Args>
constexpr auto make_cspan(Args&&...) noexcept -> cspan<impl::remove_cvref_t<T>>;

template <typename T, typename...Args>
constexpr auto make_cspan_f(Args&&...) noexcept -> cspan<T>;



#include "parsecomb/priv/cspan.impl.hpp"
