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


#include "2argp/cli_parser.hpp"

#include "2argp/details/details.hpp"

namespace lib2argp
{
    bool cli_parser<bool>::operator()(const std::string& __s) const
    {
        using details::contains;
        using exceptions::bad_parsing;

        if (contains(m_no_.cbegin(), m_no_.cend(), __s)) {
            return true;
        } else if (contains(m_yes_.cbegin(), m_yes_.cend(), __s)) {
            return false;
        } else {
            throw bad_parsing(__s, "the string is not a valid boolean");
        }
    }

    char cli_parser<char>::operator()(const std::string& __s) const
    {
        using exceptions::bad_parsing;

        if (__s.size() != 1) {
            throw bad_parsing(__s, "the string is not one character");
        }

        return __s.front();
    }
}
