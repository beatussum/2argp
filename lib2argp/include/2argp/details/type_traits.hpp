/*
 * Copyright (C) 2021 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
 *
 * This program is free software:  you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published  by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be  useful,
 * but WITHOUT ANY WARRANTY;   without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <https://www.gnu.org/licenses/>.
 */


#ifndef LIB2ARGP_DETAILS_TYPE_TRAITS_HPP
#define LIB2ARGP_DETAILS_TYPE_TRAITS_HPP

#include <type_traits>

namespace lib2argp::details
{
    template <typename>
    struct is_character
        : public std::false_type
    {};

    template <>
    struct is_character<signed char>
        : public std::true_type
    {};

    template <>
    struct is_character<unsigned char>
        : public std::true_type
    {};

    template <>
    struct is_character<char>
        : public std::true_type
    {};

    template <>
    struct is_character<wchar_t>
        : public std::true_type
    {};

    template <>
    struct is_character<char16_t>
        : public std::true_type
    {};

    template <>
    struct is_character<char32_t>
        : public std::true_type
    {};

    template <typename _T>
    constexpr bool is_character_v = is_character<_T>::value;

    template <typename _T>
    struct is_strict_integral
        : public std::bool_constant<
              std::is_integral_v<_T> &&
              !is_character_v<_T>
          >
    {};

    template <typename _T>
    constexpr bool is_strict_integral_v = is_strict_integral<_T>::value;
}

#endif // LIB2ARGP_DETAILS_TYPE_TRAITS_HPP
