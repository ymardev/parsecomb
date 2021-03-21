#pragma once
#include "parsecomb/Parser.hpp"


template <typename T>
auto Something(ParserIO<T> const&) -> ParserIO<T>;

template <typename T>
auto Nothing(ParserIO<T> const&) -> ParserIO<T>;

template <typename T>
auto Anything(ParserIO<T> const&) -> ParserIO<T>;



#include "parsecomb/priv/parsers.impl.hpp"
