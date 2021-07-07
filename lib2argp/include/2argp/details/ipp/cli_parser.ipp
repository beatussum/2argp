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


#include "2argp/exceptions.hpp"

namespace lib2argp
{
    template <typename _T>
    _T cli_parser<_T, std::enable_if_t<details::is_strict_integral_v<_T>>>::operator()(const std::string& __s) const
    {
        using exceptions::bad_parsing;

        std::size_t pos;
        _T ret;

        if constexpr (std::is_same_v<_T, long long>) {
            ret = std::stoll(__s, &pos, m_base_);
        } else if constexpr (std::is_same_v<_T, long>) {
            ret = std::stol(__s, &pos, m_base_);
        } else {
            ret = std::stoi(__s, &pos, m_base_);
        }

        if (pos != __s.size()) {
            throw bad_parsing(__s, "the string is not a valid integer");
        }

        return ret;
    }

    template <typename _T>
    _T cli_parser<_T, std::enable_if_t<std::is_floating_point_v<_T>>>::operator()(const std::string& __s) const
    {
        using exceptions::bad_parsing;

        std::size_t pos;
        _T ret;

        if constexpr (std::is_same_v<_T, float>) {
            ret = std::stof(__s, &pos);
        } else if constexpr (std::is_same_v<_T, double>) {
            ret = std::stod(__s, &pos);
        } else {
            ret = std::stold(__s, &pos);
        }

        if (pos != __s.size()) {
            throw bad_parsing(__s, "the string is not a valid floating point");
        }

        return ret;
    }
}
