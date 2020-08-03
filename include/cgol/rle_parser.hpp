#pragma once
#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>
#include <streambuf>
#include <string>
#include <vector>

namespace cgol {

class rle_parser {
  std::string rle_string_;
  std::string name_;
  std::vector<std::string> comments_;
  std::string author_;
  size_t size_x_;
  size_t size_y_;
  std::vector<size_t> rule_birth_;
  std::vector<size_t> rule_survival_;
  std::string pattern_raw_;
  std::vector<std::vector<char>> pattern_2d_array;

  static std::string read_file(const std::string &filename) {
    std::ifstream stream(filename);
    if (stream.fail()) {
      throw std::runtime_error("Error: Could not open file " + filename);
    }
    return std::string((std::istreambuf_iterator<char>(stream)),
                       std::istreambuf_iterator<char>());
  }

  static std::vector<std::string> split_string(const std::string &str,
                                               const std::string &delimiter) {
    std::vector<std::string> strings;

    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != std::string::npos) {
      strings.push_back(str.substr(prev, pos - prev));
      prev = pos + delimiter.size();
    }

    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(str.substr(prev));

    return strings;
  }

  static bool starts_with(const std::string &string,
                          const std::string &substring) {
    return string.rfind(substring, 0) == 0;
  }

  // trim from start (in place)
  static void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    [](int ch) { return !std::isspace(ch); }));
  }

  // trim from end (in place)
  static void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](int ch) { return !std::isspace(ch); })
                .base(),
            s.end());
  }

  // trim from both ends (in place)
  static void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
  }

  // trim from start (copying)
  static std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
  }

  // trim from end (copying)
  static std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
  }

  // trim from both ends (copying)
  static std::string trim_copy(std::string s) {
    trim(s);
    return s;
  }

  // trim white spaces from the left end of an input string
  std::string strip_left(const std::string &input_string,
                         const std::string &chars) {
    std::string result = input_string;
    result.erase(result.begin(),
                 std::find_if(result.begin(), result.end(), [&chars](int ch) {
                   return !std::isspace(ch) and
                          (chars.find(ch) == std::string::npos);
                 }));
    return result;
  }

  // trim white spaces from right end of an input string
  std::string strip_right(const std::string &input_string,
                          const std::string &chars) {
    std::string result = input_string;
    result.erase(std::find_if(result.rbegin(), result.rend(),
                              [&chars](int ch) {
                                return !std::isspace(ch) and
                                       (chars.find(ch) == std::string::npos);
                              })
                     .base(),
                 result.end());
    return result;
  }

  static size_t parse_digit_from_char(char c) {
    size_t result;
    std::stringstream str;
    str << c;
    str >> result;
    return result;
  }

  void populate_attributes() {
    const auto lines = split_string(rle_string_, "\n");
    for (const auto &line : lines) {
      // Name of the pattern
      if (starts_with(line, "#N")) {
        name_ = strip_left(line, "#N ");
      }
      // Comments accompanying the pattern
      else if (starts_with(line, "#C") or starts_with(line, "#c")) {
        const auto comment = strip_left(line, "#Cc ");
        comments_.push_back(comment);
      }
      // Authorship of the pattern
      else if (starts_with(line, "#O")) {
        author_ = strip_left(line, "#O ");
      }
      // Grid sizes and rules
      else if (starts_with(line, "x")) {
        auto data = split_string(line, ",");
        for (auto &d : data) {
          trim(d);
          // Grid sizes
          if (starts_with(d, "x")) {
            auto kvpair = split_string(d, "=");
            if (size_x_ == 0)
              size_x_ = std::stoi(kvpair[1]);
          } else if (starts_with(d, "y")) {
            auto kvpair = split_string(d, "=");
            if (size_y_ == 0)
              size_y_ = std::stoi(kvpair[1]);
          }
          // Rules
          else if (starts_with(d, "rule")) {
            auto kvpair = split_string(d, "=");
            auto rule = kvpair[1];
            trim(rule);
            for (auto r : split_string(rule, "/")) {
              if (starts_with(r, "B")) {
                auto digits = strip_left(r, "B");
                for (const auto &digit : digits) {
                  rule_birth_.push_back(parse_digit_from_char(digit));
                }
              }
              if (starts_with(r, "S")) {
                auto digits = strip_left(r, "S");
                for (const auto &digit : digits) {
                  rule_survival_.push_back(parse_digit_from_char(digit));
                }
              }
            }
          }
        }
      }
      // Pattern line
      else {
        pattern_raw_ += strip_right(line, " \n\r\t");
      }
    }
  }

  void populate_pattern() {
    auto pattern_rows = split_string(strip_right(pattern_raw_, "!"), "$");
    for (size_t y = 0; y < pattern_rows.size(); y++) {
      pattern_2d_array.push_back({});
      std::string tmp_num_str = "";
      for (auto c : pattern_rows[y]) {
        if (isdigit(c)) {
          tmp_num_str += c;
        } else {
          size_t num_cells = 0;
          if (tmp_num_str == "") {
            num_cells = 1;
          } else {
            num_cells = static_cast<size_t>(std::stoi(tmp_num_str));
          }
          for (size_t n = 0; n < num_cells; n++) {
            pattern_2d_array[y].push_back(c);
          }
          // Reset count until another number is encountered
          tmp_num_str = "";
        }
      }
      // Fill in empty spaces at end of each row
      for (size_t i = pattern_2d_array[y].size(); i < size_x_; i++) {
        pattern_2d_array[y].push_back('b');
      }
    }
    // Fill in empty lines till size_y_
    for (size_t i = pattern_rows.size(); i < size_y_; i++) {
      pattern_2d_array.push_back({});
      for (size_t j = 0; j < size_x_; j++) {
        pattern_2d_array[i].push_back('b');
      }
    }
  }

public:
  rle_parser() {}

  void open(const std::string &rle_string, size_t rows = 0, size_t cols = 0) {
    rle_string_ = read_file(rle_string);
    size_y_ = rows;
    size_x_ = cols;
    populate_attributes();
    populate_pattern();
  }

  void print() const {
    for (auto line : pattern_2d_array) {
      for (auto c : line) {
        std::cout << c;
      }
      std::cout << "\n";
    }
  }

  size_t rows() const { return size_y_; }

  size_t cols() const { return size_x_; }

  std::vector<std::vector<char>> pattern() const { return pattern_2d_array; }
};

} // namespace cgol