#pragma once
#include "parsecomb/Parser.hpp"
#include <functional>



template <typename T, typename Equal= std::equal_to<T>>
auto TokenParser(T, Equal&& =Equal()) -> Parser<T>;


template <typename T, typename Less = std::less<T>>
auto RangeParser(T, T, Less&& =Less()) -> Parser<T>;


template <typename T, typename U>
auto ConvertParser(Parser<U>) -> Parser<T>;


template <typename T, typename Fn, typename U>
auto ConvertParser(Fn convert, Parser<U>) -> Parser<T>;



#include "parsecomb/priv/generators.impl.hpp"
