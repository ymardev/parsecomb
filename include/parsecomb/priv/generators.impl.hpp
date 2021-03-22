#include "parsecomb/generators.hpp"
#include <type_traits>



template <typename T>
auto TokenParser(T token) -> Parser<T>
{
    return [token=std::move(token)](ParserIO<T> const& input)
        -> ParserIO<T>
    {
        if (!input.is_empty()) {
            if (input[0] == token) {
                return input.succeed(1);
            }
        }
        return input.fail();
    };
}
