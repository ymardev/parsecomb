#pragma once
#include "parsecomb/priv/type_traits/remove_cvref.hpp"
#include "parsecomb/priv/type_traits/is_iterator.hpp"
#include "parsecomb/priv/type_traits/iterator_to_value.hpp"
#include <array>
#include <cstddef>
#include <iterator>
#include <type_traits>



template <typename T>
class cspan
{
public:
    using value_type             = remove_cvref_t<T>;
    using pointer                = value_type const*;
    using const_pointer          = pointer;
    using iterator               = const_pointer;
    using const_iterator         = iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using reference              = value_type const&;
    using const_reference        = reference;
    using size_type              = std::size_t;

private:
    pointer     _begin;
    size_type   _size;

public:
    constexpr cspan() = default;
    constexpr cspan(pointer, size_type) noexcept;
    constexpr cspan(pointer, pointer) noexcept;

    template <typename It, typename =std::enable_if_t<is_iterator_v<It>>>
    constexpr cspan(It, It) noexcept;

    template <typename It, typename =std::enable_if_t<is_iterator_v<It>>>
    constexpr cspan(It, size_type) noexcept;

    template <size_t Sz>
    constexpr cspan(T(&array)[Sz]) noexcept;

    template <size_t Sz>
    constexpr cspan(T const(&array)[Sz]) noexcept;

    template <size_t Sz>
    constexpr cspan(std::array<T, Sz> const&) noexcept;

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
template <typename It>
cspan(It, size_t)           -> cspan<iterator_to_value_type<It>>;

template <typename It>
cspan(It, It)               -> cspan<iterator_to_value_type<It>>;

template <typename T, size_t Sz>
cspan(T(&array)[Sz])        -> cspan<remove_cvref_t<T>>;

template <typename T, size_t Sz>
cspan(std::array<T,Sz>)     -> cspan<remove_cvref_t<T>>;

template <template <class,class...> typename C, typename T, typename...Ts>
cspan(C<T,Ts...> const&)    -> cspan<T>;



////////////////////////////////////////////////////////////////////////////////
template <typename T, typename...Args>
constexpr auto make_cspan(Args&&...) noexcept
    -> cspan<remove_cvref_t<T>>;

template <typename T, typename...Args>
constexpr auto make_cspan(Args&&...) noexcept
    -> std::invoke_result_t<cspan<T>, Args...>;

template <typename T, typename...Args>
constexpr auto make_cspan_f(Args&&...) noexcept -> cspan<T>;

template <template <class,class...> typename C, typename T, typename...Ts>
constexpr auto make_cspan(C<T,Ts...> const& c) noexcept
    -> cspan<remove_cvref_t<T>>;

template <typename It, typename = std::enable_if_t<is_iterator_v<It>>>
constexpr auto make_cspan(It, It) noexcept -> cspan<iterator_to_value_type<It>>;

template <typename It, typename = std::enable_if_t<is_iterator_v<It>>>
constexpr auto make_cspan(It, size_t) noexcept -> cspan<iterator_to_value_type<It>>;



#include "cspan.impl.hpp"
