#pragma once

#include <array>
#include <type_traits>


namespace cpplang::detail
{
    template<typename ... Ts>
    constexpr auto make_array(Ts ... values)
    {
        return std::array<std::common_type_t<Ts...>, sizeof...(Ts)> { std::forward<Ts>(values) ... };
    }
}
