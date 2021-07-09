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


#ifndef LIB2ARGP_CLI_PARSER_HPP
#define LIB2ARGP_CLI_PARSER_HPP

#include "2argp/type_traits.hpp"
#include "2argp/details/type_traits.hpp"

#include <string>

// TODO: try to use `std::string_view`
namespace lib2argp
{
    template <class, typename = void>
    class cli_parser;

    template <typename _T>
    class cli_parser<_T, std::enable_if_t<details::is_strict_integral_v<_T>>>
    {
    public:
        cli_parser(int __base = 10) noexcept
            : m_base_(__base)
        {}

        _T operator()(const std::string&) const;
    private:
        int m_base_;
    };

    template <typename _T>
    class cli_parser<_T, std::enable_if_t<std::is_floating_point_v<_T>>>
    {
    public:
        _T operator()(const std::string&) const;
    };

    template <>
    class cli_parser<bool>
    {
    public:
        cli_parser( std::string __no = "no"
                  , std::string __yes = "yes")
            : m_no_(std::move(__no))
            , m_yes_(std::move(__yes))
        {}

        bool operator()(const std::string&) const;
    private:
        std::string m_no_;
        std::string m_yes_;
    };

    // TODO: see what to do for other character types
    // TODO: see what to do for `std::*int8_t`
    template <>
    class cli_parser<char>
    {
    public:
        char operator()(const std::string&) const;
    };

    template <>
    class cli_parser<std::string>
    {
    public:
        std::string operator()(const std::string& __s) const { return __s; }
    };

    template <class _T0, class _T1>
    class cli_parser<std::pair<_T0, _T1>>
    {
    public:
        using first_value_parser_type = cli_parser<_T0>;
        using second_value_parser_type = cli_parser<_T1>;
    public:
        cli_parser( char __separator = '='
                  , first_value_parser_type __first = {}
                  , second_value_parser_type __second = {})
            : m_sep_(__separator)
            , m_first_val_parser_(std::move(__first))
            , m_second_val_parser_(std::move(__second))
        {}

        std::pair<_T0, _T1> operator()(const std::string&) const;
    private:
        char m_sep_;
        first_value_parser_type m_first_val_parser_;
        second_value_parser_type m_second_val_parser_;
    };

    template <class _T>
    class cli_parser<_T, std::enable_if_t<is_dynamic_sized_container_v<_T>>>
    {
    public:
        using value_parser_type = cli_parser<typename _T::value_type>;
    public:
        cli_parser(char __separator = ',', value_parser_type __p = {})
            : m_sep_(__separator)
            , m_val_parser_(std::move(__p))
        {};

        _T operator()(const std::string&) const;
    private:
        char m_sep_;
        value_parser_type m_val_parser_;
    };
}

#include "2argp/details/ipp/cli_parser.ipp"

#endif // LIB2ARGP_CLI_PARSER_HPP
