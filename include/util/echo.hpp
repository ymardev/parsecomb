#pragma once
#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>



constexpr auto _echo_lambda = [](std::string_view label,auto&& value,size_t w=0)
{
    using value_type = decltype(value);

    if (w != 0) {
        std::cout << std::left << std::setw(w) << label;
    }
    else {
        std::cout << label;
    }

    if constexpr (std::is_convertible_v<std::decay_t<value_type>, std::string>)
    {
        std::cout << " : \""<<(std::forward<decltype(value)>(value))<<"\"";
    }
    else
    {
        std::cout << " : " << (std::forward<decltype(value)>(value));
    }
};



/**
 *  Print expression, then evaluate it and print result.
 */
#define ECHO(ECHO_MACRO_PARAM)                                  \
    (_echo_lambda(#ECHO_MACRO_PARAM, ECHO_MACRO_PARAM))


#define ECHOW(ECHOW_MACRO_PARAM_W, ECHOW_MACRO_PARAM)           \
    (_echo_lambda(#ECHOW_MACRO_PARAM, ECHOW_MACRO_PARAM, ECHOW_MACRO_PARAM_W))



/**
 *  Print expression, evaluate it and print result, then print a new line.
 */
#define ECHO_LN(ECHO_LN_MACRO_PARAM)                                \
    ([](std::string_view label, auto&& value) {                     \
        _echo_lambda(label, std::forward<decltype(value)>(value));  \
        std::cout << std::endl;                                     \
    })(#ECHO_LN_MACRO_PARAM, ECHO_LN_MACRO_PARAM)



#define ECHOW_LN(ECHOW_LN_MACRO_PARAM_W, ECHOW_LN_MACRO_PARAM)          \
    ([w=ECHOW_LN_MACRO_PARAM_W](std::string_view label, auto&& value) { \
        _echo_lambda(label, std::forward<decltype(value)>(value),w);    \
        std::cout << std::endl;                                         \
    })(#ECHOW_LN_MACRO_PARAM, ECHOW_LN_MACRO_PARAM)



/**
 *  Print a new line
 */
#define NL(Stream)                                      \
    ([](std::ostream& os = std::cout) {                 \
        os << "\n";                                     \
    }(Stream))
