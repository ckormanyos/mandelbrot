///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <charconv>
#include <regex>
#include <string>

auto mandelbrot_discovery_cmd_itr(const std::string& str_cmd, unsigned& iter, std::string& str_cmd_result) -> bool
{
  const bool
    cmd_is_itr
    {
         (str_cmd.find("itr", static_cast<std::string::size_type>(UINT8_C(0))) == static_cast<std::string::size_type>(UINT8_C(0)))
      && (str_cmd.length() > static_cast<std::string::size_type>(UINT8_C(3)))
    };

  bool result_cmd_itr_is_ok { false };

  if(cmd_is_itr)
  {
    unsigned local_iter { };

    const auto result_of_iter_from_chars =
      std::from_chars
      (
        str_cmd.c_str() + static_cast<std::string::size_type>(UINT8_C(3)),
        str_cmd.c_str() + str_cmd.length(),
        local_iter
      );

    const auto err_code = result_of_iter_from_chars.ec;

    if(err_code == std::errc())
    {
      iter = local_iter;

      str_cmd_result = "new max. iterations: " + std::to_string(local_iter) + "\n";

      result_cmd_itr_is_ok = true;
    }
  }

  return result_cmd_itr_is_ok;
}

auto mandelbrot_discovery_cmd_res(const std::string& str_cmd, int& frac2, std::string& str_cmd_result) -> bool
{
  const bool
    cmd_is_res
    {
         (str_cmd.find("res", static_cast<std::string::size_type>(UINT8_C(0))) == static_cast<std::string::size_type>(UINT8_C(0)))
      && (str_cmd.length() > static_cast<std::string::size_type>(UINT8_C(3)))
    };

  bool result_cmd_res_is_ok { false };

  if(cmd_is_res)
  {
    // Parse strings of the form: res, res1, res1/2, res1/4, res1/8, res1/16.
    // See also code at GodBolt at: https://godbolt.org/z/Wq5nran4o

    if((str_cmd == "res") || (str_cmd == "res1"))
    {
      frac2 = 1;

      str_cmd_result = "new resolution having fraction: 1/1\n";

      result_cmd_res_is_ok = true;
    }
    else
    {
      // Regex pattern to match the required strings.
      std::string pattern_str = "res(1)?(/(2|4|8|16))?";
      std::regex pattern(pattern_str);

      std::smatch match;

      if (std::regex_match(str_cmd, match, pattern))
      {
        if((match[1].matched) && (match[3].matched))
        {
          const std::string str_frac { match[3].str() };

          int local_frac2 { };

          const auto result_of_iter_from_chars =
            std::from_chars
            (
              str_frac.data(),
              str_frac.data() + str_frac.length(),
              local_frac2
            );

          const auto err_code = result_of_iter_from_chars.ec;

          if(err_code == std::errc())
          {
            frac2 = local_frac2;

            result_cmd_res_is_ok = true;
          }
        }
      }
    }
  }

  return result_cmd_res_is_ok;
}
