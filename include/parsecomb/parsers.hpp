#pragma once
#include "parsecomb/Parser.hpp"


template <typename T>
auto Any(ParserIO<T> const&) -> ParserIO<T>;

template <typename T>
auto Empty(ParserIO<T> const&) -> ParserIO<T>;

template <typename T>
auto AnyOrEmpty(ParserIO<T> const&) -> ParserIO<T>;



#include "parsecomb/priv/parsers.impl.hpp"
