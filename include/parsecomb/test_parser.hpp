/*

test_parser.hpp


Output information about a parsing operation.
The API suggested by this file consists of the two following macros:

test_parser(parser, input)
test_parserw(description_field_width, parser, input)


`input` should be convertible to ParserIO<T>, where T is the same as in the
`parser` parameter of type Parser<T>.

The second function does some formatting and expects the caller to pass the
desired width in characters of the first field, i.e. the name of the parser and
of the object used as input.

*/
#pragma once
#include "parsecomb/Parser.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string_view>



////////////////////////////////////////////////////////////////////////////////
template <typename T, typename InputType>
auto _test_parser(
    std::string_view  parser_name,
    Parser<T> const&  parser,
    std::string_view  input_name,
    InputType&&       input
);



template <typename T, typename InputType>
auto _test_parser_w(
    size_t            field_width,
    std::string_view  parser_name,
    Parser<T> const&  parser,
    std::string_view  input_name,
    InputType&&       input
);



////////////////////////////////////////////////////////////////////////////////
#define test_parser(TP_PARSER, TP_INPUT) \
    _test_parser(#TP_PARSER, TP_PARSER, #TP_INPUT, TP_INPUT)



#define test_parserw(TP_FIELD_WIDTH, TP_PARSER, TP_INPUT) \
    _test_parser_w(TP_FIELD_WIDTH, #TP_PARSER, TP_PARSER, #TP_INPUT, TP_INPUT)



// impl.
////////////////////////////////////////////////////////////////////////////////
template <typename T, typename InputType>
auto _test_parser(
    std::string_view  parser_name,
    Parser<T> const&  parser,
    std::string_view  input_name,
    InputType&&       input
){
    auto const cout_flags = std::cout.flags();
    auto const output = parser(std::forward<InputType>(input));

    std::ostringstream result;
    result.setf(result.boolalpha);
    result << output.is_success() << ',';

    std::cout
        << parser_name << " <- "
        << input_name  << " [ "
        << std::left << std::setw(7) << result.str()
        << output.size()
        << " ]\n";

    std::cout.flags(cout_flags);
}



template <typename T, typename InputType>
auto _test_parser_w(
    size_t            field_width,
    std::string_view  parser_name,
    Parser<T> const&  parser,
    std::string_view  input_name,
    InputType&&       input
){
    auto const cout_flags = std::cout.flags();
    auto const output = parser(std::forward<InputType>(input));

    std::ostringstream description;
    description << parser_name << " <- " << input_name;

    std::ostringstream result;
    result.setf(result.boolalpha);
    result << output.is_success() << ',';

    std::cout
        << std::left << std::setw(field_width)
        << description.str() << " [ "
        << std::setw(7) << result.str()
        << std::right << std::setw(4) << output.size()
        << " ]\n";

    std::cout.flags(cout_flags);
}
