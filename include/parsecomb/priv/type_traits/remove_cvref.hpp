#pragma once
#include <type_traits>



template <typename T>
struct remove_cvref
{
    using type = typename std::remove_cv<std::remove_reference<T>>::type;
};


template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;
