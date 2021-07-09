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
#include "2argp/details/details.hpp"

namespace lib2argp
{
    /*********************/
    /* FUNDAMENTAL TYPES */
    /*********************/

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

    /***************/
    /* OTHER TYPES */
    /***************/

    template <class _T0, class _T1>
    std::pair<_T0, _T1> cli_parser<std::pair<_T0, _T1>>::operator()(const std::string& __s) const
    {
        using exceptions::bad_parsing;
        using details::contains;

        std::pair<_T0, _T1> ret;

        const auto i = std::find(__s.cbegin(), __s.cend(), m_sep_);

        if (i != __s.cend()) {
            if (contains(i + 1, __s.cend(), *i)) {
                throw bad_parsing(
                    __s, "the `std::pair` contains more than two elements"
                );
            }

            ret = std::make_pair(
                m_first_val_parser_({__s.cbegin(), i}),
                m_second_val_parser_({i + 1, __s.cend()})
            );
        } else if (__s.size() != 0) {
            throw bad_parsing(
                __s, "the `std::pair` has only one element"
            );
        }

        return ret;
    }

    // TODO: find a better implementation
    template <class _T>
    _T cli_parser<_T, std::enable_if_t<is_dynamic_sized_container_v<_T>>>::operator()(const std::string& __s) const
    {
        _T ret;

        auto i = std::find(__s.cbegin(), __s.cend(), m_sep_);
        char sep = (i != __s.cend()) ? *i : char();

        for (auto first = __s.cbegin(); ; ) {
            ret.insert(m_val_parser_({first, i}));

            if (i == __s.cend()) {
                break;
            } else {
                i = std::find((first = i + 1), __s.cend(), sep);
            }
        }

        return ret;
    }
}
