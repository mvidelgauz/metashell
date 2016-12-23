#ifndef METASHELL_TYPE_SHELL_CONSTANT_HPP
#define METASHELL_TYPE_SHELL_CONSTANT_HPP

// Metashell - Interactive C++ template metaprogramming shell
// Copyright (C) 2016, Abel Sinkovics (abel@sinkovics.hu)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <metashell/iface/type_shell.hpp>

namespace metashell
{
  class type_shell_constant : public iface::type_shell
  {
  public:
    explicit type_shell_constant(data::result result_);

    virtual data::result eval(const iface::environment&,
                              const boost::optional<std::string>&,
                              bool) override;

    virtual data::result validate_code(const std::string&,
                                       const data::config&,
                                       const iface::environment&,
                                       bool) override;

    virtual void
    generate_precompiled_header(const boost::filesystem::path&) override;

  private:
    data::result _result;
  };
}

#endif
