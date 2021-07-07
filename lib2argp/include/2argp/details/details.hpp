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


#ifndef LIB2ARGP_DETAILS_DETAILS_HPP
#define LIB2ARGP_DETAILS_DETAILS_HPP

namespace lib2argp::details
{
    template <class _InputIt, class _T>
    bool contains( const _InputIt __first
                 , const _InputIt __last
                 , const _T& __value);
}

#include "2argp/details/ipp/details.ipp"

#endif // LIB2ARGP_DETAILS_DETAILS_HPP
