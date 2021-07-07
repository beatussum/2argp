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

#include "2argp/details/type_traits.hpp"

#include <string>
#include <vector>

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

    // TODO: try to use a static-sized container for keywords.
    template <>
    class cli_parser<bool>
    {
    public:
        using keywords_t = std::vector<std::string>;
    public:
        cli_parser( keywords_t __no = {"no", "off"}
                  , keywords_t __yes = {"yes", "on"})
            : m_no_(std::move(__no))
            , m_yes_(std::move(__yes))
        {}

        bool operator()(const std::string&) const;
    private:
        keywords_t m_no_;
        keywords_t m_yes_;
    };

    // TODO: see what to do for other character types
    template <>
    class cli_parser<char>
    {
    public:
        char operator()(const std::string&) const;
    };
}

#include "2argp/details/ipp/cli_parser.ipp"

#endif // LIB2ARGP_CLI_PARSER_HPP
