#pragma once
#include <cgol/rle_parser.hpp>
#include <cgol/termcolor.hpp>
#include <string>
#include <utility>
#include <vector>

namespace cgol {

class grid {
  std::vector<std::vector<unsigned char>> grid_; // Underlying 2D grid, 1 = alive, 0 = dead
  size_t rows_;                                  // Number of rows in the grid
  size_t cols_;                                  // Number of cols in the grid
  rle_parser parser_;                            // RLE parser to parse pattern files

public:
  // Construct a Game of Life grid from an .rle pattern file
  // The grid size is used to establish the dimensions of the play area
  explicit grid(const std::string &rle_filename, const std::pair<size_t, size_t> &grid_size);

  // Returns the number of rows
  // Used in main.cpp to move cursor up `rows_` times before printing again
  size_t rows() const;

  // Prints the Game of Life grid
  void print(std::ostream &stream = std::cout) const;

  // Updates the Game of Life grid
  void tick();
};

} // namespace cgol