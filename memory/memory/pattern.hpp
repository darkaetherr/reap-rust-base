#pragma once
#include "memory/address.hpp"

#include <algorithm>
#include <cstdint>
#include <type_traits>

namespace memory {
    namespace detail {
        constexpr std::uint8_t parse_hex(char c) {
            if (c >= '0' && c <= '9')
                return c - '0';
            if ((c | 32) >= 'a' && (c | 32) <= 'f')
                return (c | 32) - 'a' + 10;
            if (c == '?')
                return 0;

            static_assert("invalid hex char");
            __assume(0);
        }

        template <char Hi, char Lo>
        struct pattern_entry : std::integral_constant<std::uint8_t, parse_hex(Hi) * 16 + parse_hex(Lo)> { };

        constexpr std::size_t pow2floor(std::size_t num, std::size_t cur = 2) {
            return num == 0 ? 0 : (cur > num ? cur / 2 : pow2floor(num, cur * 2));
        }

        template <std::size_t S>
        struct uint_ {
            using type = std::uint8_t;
        };
        template <>
        struct uint_<2> {
            using type = std::uint16_t;
        };
        template <>
        struct uint_<4> {
            using type = std::uint32_t;
        };
        template <>
        struct uint_<8> {
            using type = std::uint64_t;
        };

        template <class... Bs>
        class pattern {
            constexpr static std::size_t _find_wildcard(std::size_t cur_idx) {
                // @todo: @es3n1n: add support for '?' entries in sig, only '??' supported by default
                constexpr bool is_wildcard[]{std::is_same_v<Bs, pattern_entry<'?', '?'>>...};
                for (std::size_t i = cur_idx; i != sizeof...(Bs); ++i)
                    if (is_wildcard[i])
                        return i - cur_idx;
                return sizeof...(Bs) - cur_idx;
            }
        public:
            template <std::size_t I = 0>
            __forceinline static bool compare(const std::uint8_t* bytes) noexcept {
                if constexpr (I < sizeof...(Bs)) {
                    constexpr std::size_t cmp_size = pow2floor(std::min<std::size_t>(_find_wildcard(I), 8));

                    using cmp_type = const typename uint_<cmp_size>::type*;
                    constexpr std::uint8_t values[]{Bs::value...};

                    if constexpr (cmp_size != 0)
                        if (*reinterpret_cast<cmp_type>(bytes + I) != *reinterpret_cast<cmp_type>(values + I))
                            return false;

                    return compare<I + std::max<std::size_t>(cmp_size, 1u)>(bytes);
                } else
                    return true;
            }

            __forceinline static const std::uint8_t* find(const std::uint8_t* first, const std::uint8_t* const last) noexcept {
                if (!first || !last || !size())
                    return nullptr;

                for (const auto new_last = last - sizeof...(Bs); first < new_last; ++first) {
                    if (compare(first))
                        return first;
                }
                return nullptr;
            }

            constexpr static std::size_t size() {
                return sizeof...(Bs);
            }
        };

        template <class P>
        auto parse_pattern(P) -> P;

        template <char Space, char Hi, char Lo, char... Rest, class... Bs>
        auto parse_pattern(pattern<Bs...>) -> decltype(parse_pattern<Rest...>(pattern<Bs..., pattern_entry<Hi, Lo>>{}));

        namespace ct {
            template <class T, T... Cs>
            struct String { };

            template <class char_type, class lambda_t, size_t... I>
            constexpr auto make_cx_string(lambda_t lambda [[maybe_unused]], std::index_sequence<I...>) {
                return String<char_type, lambda()[I]...>{};
            }
        } // namespace ct

        template <class CharT, CharT... Cs>
        auto _make_pattern(ct::String<CharT, Cs...>) -> decltype(parse_pattern<' ', Cs...>(pattern<>{})) {
            return {};
        }
    } // namespace detail

    __forceinline address_t find_ida_sig(auto&& sig, address_t begin, address_t end) noexcept {
        return address_t{sig.find(begin.cast<uint8_t*>(), end.cast<uint8_t*>())};
    }
} // namespace memory

#define _MAKE_CX_STRING(str) \
    (memory::detail::ct::make_cx_string<char>([]() constexpr { return (str); }, std::make_index_sequence<sizeof(str) / sizeof(char) - 1>{}))
#define make_sig(string) memory::detail::_make_pattern(_MAKE_CX_STRING(string))
