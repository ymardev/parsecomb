#pragma once
#include "remove_cvref.hpp"
#include <iterator>
#include <type_traits>



template <typename It>
using iterator_to_value_type = typename std::iterator_traits<remove_cvref_t<It>>::value_type;


template <typename It>
using iterator_to_pointer_type = typename std::iterator_traits<remove_cvref_t<It>>::pointer;



template <typename It>
constexpr auto iterator_to_pointer(It it) -> iterator_to_pointer_type<It>
{
    using pointer_type = iterator_to_pointer_type<It>;

    if constexpr (std::is_convertible_v<remove_cvref_t<It>, pointer_type>)
    {
        return static_cast<pointer>(it);
    }
    else
    {
        return it.operator->();
    }
}
