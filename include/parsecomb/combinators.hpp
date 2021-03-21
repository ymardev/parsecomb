#pragma once
#include "parsecomb/Parser.hpp"


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



#include "parsecomb/priv/combinators.impl.hpp"
