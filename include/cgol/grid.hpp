#pragma once
#include <cgol/rle_parser.hpp>
#include <cgol/termcolor.hpp>
#include <string>
#include <vector>
#include <utility>

namespace cgol {

class grid {
  std::vector<std::vector<unsigned char>> grid_;
  size_t rows_;
  size_t cols_;
  rle_parser parser_;

public:
  explicit grid(const std::string & rle_filename, std::pair<size_t, size_t> grid_size);

  size_t rows() const;

  size_t cols() const;

  void print(std::ostream& stream = std::cout) const;

  void tick_with_wrap_around();

  void tick();
};

} // namespace cgol