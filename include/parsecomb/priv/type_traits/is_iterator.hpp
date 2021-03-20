#pragma once
#include "remove_cvref.hpp"
#include <iterator>
#include <type_traits>



template <typename T,typename>
struct is_iterator_or_pointer;


template <typename T, typename>
struct is_iterator;



////////////////////////////////////////////////////////////////////////////////
template <typename T, typename = std::void_t<>>
struct is_iterator_or_pointer
{
    constexpr static bool value = false;
};



template <typename T>
struct is_iterator_or_pointer<T,
    std::void_t<typename std::iterator_traits<remove_cvref_t<T>>::value_type>>
{
    constexpr static bool value = true;
};



////////////////////////////////////////////////////////////////////////////////
template <typename T, typename = std::void_t<>>
struct is_iterator
{
    constexpr static bool value = false;
};



template <typename T>
struct is_iterator<T, std::void_t<typename remove_cvref_t<T>::value_type>>
{
    constexpr static bool value = true;
};



////////////////////////////////////////////////////////////////////////////////
template <typename T>
constexpr bool is_iterator_or_pointer_v = is_iterator_or_pointer<T>::value;



template <typename T>
constexpr bool is_iterator_v = is_iterator<T>::value;
