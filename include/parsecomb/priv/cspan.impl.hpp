#include "parsecomb/priv/cspan.hpp"



template <typename T, typename...Args>
constexpr auto make_cspan(Args&&...args) noexcept -> cspan<impl::remove_cvref_t<T>>
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
    -> cspan<impl::remove_cvref_t<T>>
{
    return {std::begin(c).operator->(), std::size(c)};
}



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
    _begin {
([&c]() -> pointer {
    if constexpr(std::is_same_v<pointer,typename C<U,Ts...>::const_iterator>) {
        return std::begin(c);
    } else {
        return std::begin(c).operator->();
    }
})()},
    _size {std::size(c)}
{}



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
constexpr auto cspan<T>::first(size_type sz) const -> cspan
{
    return {_begin, sz};
}



template <typename T>
constexpr auto cspan<T>::last(size_type sz) const -> cspan
{
    return {_begin+size()-sz, sz};
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
