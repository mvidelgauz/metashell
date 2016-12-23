#ifndef METASHELL_TEMPLATE_TRACER_CLANG_HPP
#define METASHELL_TEMPLATE_TRACER_CLANG_HPP

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

#include <metashell/iface/template_tracer.hpp>

#include <metashell/clang_binary.hpp>

#include <boost/filesystem/path.hpp>

namespace metashell
{
  class template_tracer_clang : public iface::template_tracer
  {
  public:
    template_tracer_clang(const boost::filesystem::path& internal_dir_,
                          const boost::filesystem::path& env_filename_,
                          clang_binary clang_binary_);

    virtual data::result
    eval(const iface::environment& env_,
         const boost::optional<std::string>& tmp_exp_,
         bool use_precompiled_headers_,
         const boost::filesystem::path& templight_dump_path_) override;

  private:
    clang_binary _clang_binary;
    boost::filesystem::path _env_path;
  };
}

#endif
