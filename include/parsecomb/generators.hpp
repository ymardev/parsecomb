#pragma once
#include "parsecomb/Parser.hpp"
#include <functional>



template <typename T>
auto TokenParser(T) -> Parser<T>;


template <typename T, typename Comp = std::less<T>>
auto RangeParser(T, T) -> Parser<T>;


template <typename T, typename U>
auto ConvertParser(Parser<U>) -> Parser<T>;


template <typename T, typename Fn, typename U>
auto ConvertParser(Fn conversion_function, Parser<U>) -> Parser<T>;



#include "parsecomb/priv/generators.impl.hpp"
