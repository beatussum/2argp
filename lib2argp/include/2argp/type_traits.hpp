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


#ifndef LIB2ARGP_TYPE_TRAITS_HPP
#define LIB2ARGP_TYPE_TRAITS_HPP

#include <type_traits>

namespace std
{
    template <class, class>
    class deque;

    template <class, class>
    class forward_list;

    template <class, class>
    class list;

    template <class, class>
    class vector;

    template <class, class, class, class>
    class map;

    template <class, class, class, class>
    class multimap;

    template <class, class, class>
    class set;

    template <class, class, class>
    class multiset;

    template <class, class, class, class, class>
    class unordered_map;

    template <class, class, class, class, class>
    class unordered_multimap;

    template <class, class, class, class>
    class unordered_set;

    template <class, class, class, class>
    class unordered_multiset;
}

namespace lib2argp
{
    template <class>
    struct is_dynamic_sized_container
        : public std::false_type
    {};

    template <class _T, class _Allocator>
    struct is_dynamic_sized_container<std::deque<_T, _Allocator>>
        : std::true_type
    {};

    template <class _T, class _Allocator>
    struct is_dynamic_sized_container<std::forward_list<_T, _Allocator>>
        : std::true_type
    {};

    template <class _T, class _Allocator>
    struct is_dynamic_sized_container<std::list<_T, _Allocator>>
        : std::true_type
    {};

    template <class _T, class _Allocator>
    struct is_dynamic_sized_container<std::vector<_T, _Allocator>>
        : std::true_type
    {};

    template <class _Key, class _T, class _Compare, class _Allocator>
    struct is_dynamic_sized_container<
        std::map<_Key, _T, _Compare, _Allocator
    >>
        : public std::true_type
    {};

    template <class _Key, class _T, class _Compare, class _Allocator>
    struct is_dynamic_sized_container<
        std::multimap<_Key, _T, _Compare, _Allocator
    >>
        : public std::true_type
    {};

    template <class _Key, class _Compare, class _Allocator>
    struct is_dynamic_sized_container<std::set<_Key, _Compare, _Allocator>>
        : public std::true_type
    {};

    template <class _Key, class _Compare, class _Allocator>
    struct is_dynamic_sized_container<
        std::multiset<_Key, _Compare, _Allocator
    >>
        : public std::true_type
    {};

    template <class _Key, class _T, class _Hash, class _KeyEqual, class _Allocator>
    struct is_dynamic_sized_container<
        std::unordered_map<_Key, _T, _Hash, _KeyEqual, _Allocator
    >>
        : public std::true_type
    {};

    template <class _Key, class _T, class _Hash, class _KeyEqual, class _Allocator>
    struct is_dynamic_sized_container<
        std::unordered_multimap<_Key, _T, _Hash, _KeyEqual, _Allocator
    >>
        : public std::true_type
    {};

    template <class _Key, class _Hash, class _KeyEqual, class _Allocator>
    struct is_dynamic_sized_container<
        std::unordered_set<_Key, _Hash, _KeyEqual, _Allocator
    >>
        : public std::true_type
    {};

    template <class _Key, class _Hash, class _KeyEqual, class _Allocator>
    struct is_dynamic_sized_container<
        std::unordered_multiset<_Key, _Hash, _KeyEqual, _Allocator
    >>
        : public std::true_type
    {};

    template <class _T>
    constexpr bool is_dynamic_sized_container_v =
        is_dynamic_sized_container<_T>::value;
}

#endif // LIB2ARGP_TYPE_TRAITS_HPP
