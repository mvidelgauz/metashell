#ifndef METASHELL_COLOR_HPP
#define METASHELL_COLOR_HPP

// Metashell - Interactive C++ template metaprogramming shell
// Copyright (C) 2015, Abel Sinkovics (abel@sinkovics.hu)
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

namespace metashell
{
  namespace data
  {
    enum class color
    {
      black,
      red,
      bright_red,
      green,
      bright_green,
      yellow,
      bright_yellow,
      blue,
      bright_blue,
      magenta,
      bright_magenta,
      cyan,
      bright_cyan,
      gray,
      white
    };
  }
} // namespace metashell

#endif
