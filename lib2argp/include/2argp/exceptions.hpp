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


#ifndef LIB2ARGP_EXCEPTIONS_HPP
#define LIB2ARGP_EXCEPTIONS_HPP

#include <stdexcept>

namespace lib2argp::exceptions
{
    class lib2argp_exception : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };

    class bad_parsing : public lib2argp_exception
    {
    public:
        bad_parsing( const std::string& __str
                   , const std::string& __msg)
            : lib2argp_exception("The string `" + __str + "` cannot be parsed "
                                 "correctly: " + __msg + '.')
        {};

        bad_parsing(const std::string& __str)
            : lib2argp_exception("The string `" + __str + "` cannot be parsed "
                                 "correctly.")
        {};
    };
}

#endif // LIB2ARGP_EXCEPTIONS_HPP

