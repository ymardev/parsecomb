#include "parsecomb/priv/struct/cspan.hpp"



////////////////////////////////////////////////////////////////////////////////
template <typename T, typename...Args>
constexpr auto make_cspan(Args&&...args) noexcept
    -> cspan<remove_cvref_t<T>>
{
    return {std::forward<Args>(args)...};
}



template <typename T, typename...Args>
constexpr auto make_cspan(Args&&... args) noexcept
    -> std::invoke_result_t<cspan<T>, Args...>
{
    return {std::forward<Args>(args)...};
}



template <typename T, typename...Args>
constexpr auto make_cspan_f(Args&&...args) noexcept -> cspan<T>
{
    return {std::forward<Args>(args)...};
}



template <template <class,class...> typename C, typename T, typename...Ts>
constexpr auto make_cspan(C<T,Ts...> const& c) noexcept
    -> cspan<remove_cvref_t<T>>
{
    return {std::begin(c), std::size(c)};
}



template <typename It, typename>
constexpr auto make_cspan(It b, It e) noexcept
    -> cspan<iterator_to_value_type<It>>
{
    return {iterator_to_pointer(b), iterator_to_pointer(e)};
}



template <typename It, typename>
constexpr auto make_cspan(It b, size_t sz) noexcept
    -> cspan<iterator_to_value_type<It>>
{
    return {iterator_to_pointer(b), sz};
}



// constructors
////////////////////////////////////////////////////////////////////////////////
template <typename T>
constexpr cspan<T>::cspan(pointer b, size_type sz) noexcept:
    _begin {b},
    _size  {sz}
{
}



template <typename T>
constexpr cspan<T>::cspan(pointer b, pointer e) noexcept:
    _begin {b},
    _size  {size_type(e-b)}
{
}



template <typename T> template <typename It, typename>
constexpr cspan<T>::cspan(It b, It e) noexcept:
    cspan {pointer(iterator_to_pointer(b)), pointer(iterator_to_pointer(e))}
{
}



template <typename T> template <typename It, typename>
constexpr cspan<T>::cspan(It b, size_type sz) noexcept:
    cspan {pointer(iterator_to_pointer(b)), sz}
{
}



template <typename T> template <size_t Sz>
constexpr cspan<T>::cspan(std::array<T, Sz> const& array) noexcept:
    cspan {iterator_to_pointer(std::begin(array)), std::size(array)}
{
}



template <typename T> template <size_t Sz>
constexpr cspan<T>::cspan(T(&array)[Sz]) noexcept:
    _begin {pointer(&array)},
    _size  {Sz}
{
}



template <typename T> template <size_t Sz>
constexpr cspan<T>::cspan(T const(&array)[Sz]) noexcept:
    _begin {pointer(&array)},
    _size  {Sz}
{
}



template <typename T>
template <template <class,class...> typename C, typename U, typename...Ts>
constexpr cspan<T>::cspan(C<U,Ts...> const& c) noexcept:
    _begin{pointer(iterator_to_pointer(std::cbegin(c)))},
    _size {std::size(c)}
{
}



// other methods
////////////////////////////////////////////////////////////////////////////////
template <typename T>
constexpr auto cspan<T>::size() const -> size_type
{
    return _size;
}



template <typename T>
constexpr auto cspan<T>::empty() const -> bool
{
    return 0==_size;
}



template <typename T>
constexpr auto cspan<T>::operator[](size_type idx) const -> const_reference
{
    return *(_begin+idx);
}



////////////////////////////////////////////////////////////////////////////////
template <typename T>
constexpr auto cspan<T>::first(size_type elem_count) const -> cspan
{
    return {_begin, elem_count};
}



template <typename T>
constexpr auto cspan<T>::last(size_type elem_count) const -> cspan
{
    auto const offset = _size-elem_count;
    return {_begin+offset, elem_count};
}



////////////////////////////////////////////////////////////////////////////////
template <typename T>
constexpr auto cspan<T>::begin() const -> const_iterator
{
    return _begin;
}



template <typename T>
constexpr auto cspan<T>::end() const -> const_iterator
{
    return _begin+size();
}



template <typename T>
constexpr auto cspan<T>::cbegin() const -> const_iterator
{
    return _begin;
}



template <typename T>
constexpr auto cspan<T>::cend() const -> const_iterator
{
    return _begin+size();
}



template <typename T>
constexpr auto cspan<T>::rbegin() const -> const_reverse_iterator
{
    return std::reverse_iterator(end());
}



template <typename T>
constexpr auto cspan<T>::rend() const -> const_reverse_iterator
{
    return std::reverse_iterator(begin());
}



template <typename T>
constexpr auto cspan<T>::crbegin() const -> const_reverse_iterator
{
    return std::reverse_iterator(end());
}



template <typename T>
constexpr auto cspan<T>::crend() const -> const_reverse_iterator
{
    return std::reverse_iterator(begin());
}
