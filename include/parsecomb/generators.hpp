#pragma once
#include "parsecomb/Parser.hpp"
#include <type_traits>



template <typename T>
auto TokenParser(T) -> Parser<T>;



#include "parsecomb/priv/generators.impl.hpp"
