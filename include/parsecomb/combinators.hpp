#pragma once
#include "parsecomb/Parser.hpp"
#include <functional>



template <typename T>
using CombinatorUnary  = std::function<Parser<T>(Parser<T> const&)>;

template <typename T>
using CombinatorBinary = std::function<Parser<T>(Parser<T> const&, Parser<T> const&)>;



////////////////////////////////////////////////////////////////////////////////
template <typename T>
auto Not(Parser<T> const&) -> Parser<T>;

template <typename T>
auto Sequence(Parser<T> const&, Parser<T> const&) -> Parser<T>;

template <typename T>
auto FirstMatch(Parser<T> const&, Parser<T> const&) -> Parser<T>;

template <typename T>
auto BestMatch(Parser<T> const&, Parser<T> const&) -> Parser<T>;

template <typename T>
auto Optional(Parser<T> const&) -> Parser<T>;

template <typename T>
auto OneOrMore(Parser<T> const&) -> Parser<T>;

template <typename T>
auto Several(Parser<T> const&) -> Parser<T>;

template <typename T>
auto Exactly(size_t, Parser<T> const&) -> Parser<T>;

template <typename T>
auto Between(Parser<T> const&, Parser<T> const&) -> CombinatorUnary<T>;

template <typename T>
auto NestedBetween(Parser<T> const&, Parser<T> const&) -> CombinatorUnary<T>;



#include "parsecomb/priv/combinators.impl.hpp"
