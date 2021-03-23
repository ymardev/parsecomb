#include "parsecomb/parsecomb.hpp"
#include "parsecomb/test_parser.hpp"
#include "sample/parser_conversion_sample.hpp"
#include "sample/combinators_sample.hpp"
#include "util/echo.hpp"
#include <iostream>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>



int main()
{
    parser_conversion_sample();
    combinators_sample();
}
