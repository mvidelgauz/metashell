#ifndef METASHELL_DATA_STRING_HPP
#define METASHELL_DATA_STRING_HPP

// Metashell - Interactive C++ template metaprogramming shell
// Copyright (C) 2019, Abel Sinkovics (abel@sinkovics.hu)
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

#include <metashell/data/constraint/any.hpp>

#include <algorithm>
#include <iosfwd>
#include <string>
#include <type_traits>

namespace metashell
{
  namespace data
  {
    namespace impl
    {
      std::string c_escape(int);

      std::string to_string(const std::string&);

      template <class CharT, class Traits, class Allocator>
      auto c_str(const std::basic_string<CharT, Traits, Allocator>& s_)
      {
        return s_.c_str();
      }

      template <class CharT, class Traits, class Allocator>
      auto empty(const std::basic_string<CharT, Traits, Allocator>& s_)
      {
        return s_.empty();
      }

      template <class CharT, class Traits, class Allocator>
      void clear(std::basic_string<CharT, Traits, Allocator>& s_)
      {
        s_.clear();
      }

      template <class CharT, class Traits, class Allocator>
      auto size(const std::basic_string<CharT, Traits, Allocator>& s_)
      {
        return s_.size();
      }

      template <class CharT, class Traits, class Allocator, class... Args>
      auto find(const std::basic_string<CharT, Traits, Allocator>& s_,
                Args&&... args_)
      {
        return s_.find(std::forward<Args>(args_)...);
      }

      template <class CharT, class Traits, class Allocator>
      auto substr(
          const std::basic_string<CharT, Traits, Allocator>& s_,
          typename std::basic_string<CharT, Traits, Allocator>::size_type pos_ =
              0,
          typename std::basic_string<CharT, Traits, Allocator>::size_type len_ =
              std::basic_string<CharT, Traits, Allocator>::npos)
      {
        return s_.substr(pos_, len_);
      }

      void throw_(const std::string&);

      bool isspace(int);
    }

    template <class Derived,
              bool AllowEmpty = true,
              class NonFirstCharConstraints = constraint::any,
              class FirstCharConstraints = NonFirstCharConstraints,
              class String = std::string>
    class string
    {
    public:
      string() : _value{}
      {
        static_assert(AllowEmpty, "Empty values are disabled.");

        check_invariant(_value);
      }

      template <class Str,
                class = std::enable_if_t<std::is_constructible_v<String, Str>>>
      explicit string(Str value_) : _value{std::move(value_)}
      {
        check_invariant(_value);
      }

      template <class InputIterator>
      string(InputIterator begin_, InputIterator end_) : _value{begin_, end_}
      {
        check_invariant(_value);
      }

      const String& value() const { return _value; }

      friend auto c_str(const Derived& s_)
      {
        using impl::c_str;
        return c_str(s_.value());
      }

      friend auto empty(const Derived& s_)
      {
        using impl::empty;
        return empty(s_.value());
      }

      friend void clear(Derived& s_)
      {
        using impl::clear;
        clear(const_cast<String&>(s_.value()));
      }

      friend auto size(const Derived& s_)
      {
        using impl::size;
        return size(s_.value());
      }

      template <class... Args>
      friend auto find(const Derived& s_, Args&&... args_)
      {
        using impl::find;
        return find(s_.value(), std::forward<Args>(args_)...);
      }

      // requires requires { Derived(String()); };
      friend auto substr(const Derived& s_,
                         std::string::size_type pos_ = 0,
                         std::string::size_type len_ = std::string::npos)
      {
        using impl::substr;
        return Derived(substr(s_.value(), pos_, len_));
      }

      friend Derived& operator+=(Derived& lhs_, const Derived& rhs_)
      {
        const_cast<String&>(lhs_.value()) += rhs_.value();
        return lhs_;
      }

      template <class Container>
      friend typename std::enable_if<
          std::is_base_of<Derived, typename Container::value_type>::value,
          Derived>::type
      join(const Container& c_, const Derived& separator_)
      {
        Derived result;
        bool first = true;
        for (const Derived& s : c_)
        {
          if (first)
          {
            first = false;
          }
          else
          {
            result += separator_;
          }
          result += s;
        }
        return result;
      }

      friend std::string to_string(const Derived& s_)
      {
        using impl::to_string;
        return to_string(s_.value());
      }

      friend std::ostream& operator<<(std::ostream& o_, const Derived& s_)
      {
        return o_ << s_.value();
      }

      friend auto begin(const Derived& s_)
      {
        using std::begin;
        return begin(s_.value());
      }

      friend auto end(const Derived& s_)
      {
        using std::end;
        return end(s_.value());
      }

      friend bool operator==(const Derived& lhs_, const Derived& rhs_)
      {
        return lhs_.value() == rhs_.value();
      }

      friend bool operator<(const Derived& lhs_, const Derived& rhs_)
      {
        return lhs_.value() < rhs_.value();
      }

      friend bool operator!=(const Derived& lhs_, const Derived& rhs_)
      {
        return !(lhs_ == rhs_);
      }

      friend bool operator<=(const Derived& lhs_, const Derived& rhs_)
      {
        return !(rhs_ < lhs_);
      }

      friend bool operator>(const Derived& lhs_, const Derived& rhs_)
      {
        return rhs_ < lhs_;
      }

      friend bool operator>=(const Derived& lhs_, const Derived& rhs_)
      {
        return !(lhs_ < rhs_);
      }

      template <size_t Len>
      friend bool operator==(const char (&lhs_)[Len], const Derived& rhs_)
      {
        return lhs_ == rhs_.value();
      }

      template <size_t Len>
      friend bool operator==(const Derived& lhs_, const char (&rhs_)[Len])
      {
        return rhs_ == lhs_;
      }

      friend Derived operator+(const Derived& lhs_, const Derived& rhs_)
      {
        Derived lhs(lhs_);
        return lhs += rhs_;
      }

      friend std::string operator+(const Derived& lhs_, const std::string& rhs_)
      {
        return lhs_.value() + rhs_;
      }

      friend std::string operator+(const std::string& lhs_, const Derived& rhs_)
      {
        return lhs_ + rhs_.value();
      }

      friend bool starts_with(const Derived& input_, const Derived& test_)
      {
        using impl::size;
        using std::begin;

        const auto len = size(test_.value());
        return size(input_.value()) >= len &&
               std::equal(begin(input_.value()), begin(input_.value()) + len,
                          begin(test_.value()));
      }

      friend bool ends_with(const Derived& input_, const Derived& test_)
      {
        using impl::size;
        using std::begin;
        using std::end;

        const auto len = size(test_.value());
        return size(input_.value()) >= len &&
               std::equal(end(input_.value()) - len, end(input_.value()),
                          begin(test_.value()));
      }

      friend Derived trim_copy(const Derived& s_)
      {
        using std::begin;
        using std::end;

        const auto spc = [](auto c_) {
          using impl::isspace;
          return isspace(c_);
        };

        auto e = end(s_.value());

        const auto b = std::find_if_not(begin(s_.value()), e, spc);
        if (b != e)
        {
          --e;
          while (e != b && spc(*e))
          {
            --e;
          }
          ++e;
        }

        return Derived(String(b, e));
      }

      template <class UnaryPredicate>
      friend auto count_if(const Derived& s_, UnaryPredicate p_)
      {
        using std::begin;
        using std::end;

        return std::count_if(begin(s_.value()), end(s_.value()), p_);
      }

      template <class T>
      friend auto count(const Derived& s_, T c_)
      {
        using std::begin;
        using std::end;

        return std::count(begin(s_.value()), end(s_.value()), c_);
      }

    private:
      String _value;

      static void check_invariant(const String& s_)
      {
        if (!AllowEmpty && empty(s_))
        {
          impl::throw_("Empty " + std::string{Derived::name_of_type()} +
                       " value");
        }

        bool first = true;
        for (auto c : s_)
        {
          if ((first && !FirstCharConstraints::allowed_char(c)) ||
              (!first && !NonFirstCharConstraints::allowed_char(c)))
          {
            impl::throw_("Invalid character in " +
                         std::string{Derived::name_of_type()} + ": " +
                         impl::c_escape(c));
          }
          first = false;
        }
      }
    };
  }
}

#endif
