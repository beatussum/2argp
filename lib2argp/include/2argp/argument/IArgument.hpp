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


#ifndef LIB2ARGP_ARGUMENT_IARGUMENT_HPP
#define LIB2ARGP_ARGUMENT_IARGUMENT_HPP

#include <memory>
#include <string>

namespace lib2argp::argument
{
    class Command;

    class IArgument
    {
        friend class Command;
    public:
        IArgument( std::shared_ptr<const Command> __parent
                 , std::string __id
                 , std::string __name
                 , std::string __desc = {})
            : m_parent_(std::move(__parent))
            , m_id_(std::move(__id))
            , m_name_(std::move(__name))
            , m_desc_(std::move(__desc))
        {};

        IArgument( std::string __id
                 , std::string __name
                 , std::string __desc)
            : m_parent_()
            , m_id_(std::move(__id))
            , m_name_(std::move(__name))
            , m_desc_(std::move(__desc))
        {};

        IArgument( std::shared_ptr<const Command> __parent
                 , std::string __id
                 , std::string __desc)
            : m_parent_(std::move(__parent))
            , m_id_(std::move(__id))
            , m_name_()
            , m_desc_(std::move(__desc))
        {}

        IArgument(std::string __id, std::string __desc)
            : m_parent_()
            , m_id_(std::move(__id))
            , m_name_()
            , m_desc_(std::move(__desc))
        {}

        explicit operator std::string() const noexcept { return m_id_; }
    public:
        std::string get_id() const noexcept { return m_id_; }

        std::string get_name() const noexcept;
        void set_name(std::string __s) { m_name_ = std::move(__s); }

        std::string get_desc() const noexcept { return m_desc_; }
        void set_desc(std::string __s) { m_desc_ = std::move(__s); }
    public:
        virtual void parse() = 0;
    private:
        std::shared_ptr<const Command> m_parent_;
        const std::string m_id_;
        std::string m_name_;
        std::string m_desc_;
    };
}

#endif // LIB2ARGP_ARGUMENT_IARGUMENT_HPP

