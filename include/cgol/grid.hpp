#pragma once
#include <cgol/rle_parser.hpp>
#include <cgol/termcolor.hpp>
#include <random>
#include <string>
#include <vector>

namespace cgol {

class grid {
  std::vector<std::vector<unsigned char>> grid_;
  size_t rows_;
  size_t cols_;
  rle_parser parser_;

public:
  explicit grid(const std::string & rle_filename) : rows_{0}, cols_{0}, parser_{} {
    parser_.open(rle_filename);
    rows_ = parser_.rows();
    cols_ = parser_.cols();
    const auto pattern = parser_.pattern();

    for (size_t i = 0; i < rows_; i++) {
      grid_.push_back({});
      for (size_t j = 0; j < cols_; j++) {
        if (pattern[i][j] == 'o') {
          grid_[i].push_back(1);
        } else if (pattern[i][j] == 'b') {
          grid_[i].push_back(0);
        }
      }
    }
  }

  explicit grid(const std::string & rle_filename, size_t rows, size_t cols) : rows_{rows}, cols_{cols}, parser_{} {
    parser_.open(rle_filename, rows_, cols_);
    rows_ = parser_.rows();
    cols_ = parser_.cols();
    const auto pattern = parser_.pattern();

    for (size_t i = 0; i < rows_; i++) {
      grid_.push_back({});
      for (size_t j = 0; j < cols_; j++) {
        if (pattern[i][j] == 'o') {
          grid_[i].push_back(1);
        } else if (pattern[i][j] == 'b') {
          grid_[i].push_back(0);
        }
      }
    }
  }

  size_t rows() const { return rows_; }

  size_t cols() const { return cols_; }

  std::vector<unsigned char> &operator[](size_t row_index) {
    return grid_[row_index];
  }

  void print() const {
    std::cout << termcolor::bold << termcolor::white;
    for (size_t i = 0; i < rows_; i++) {
      for (size_t j = 0; j < cols_; j++) {
        const auto cell = grid_[i][j];
        if (cell == 1) {
          std::cout << "⬜"; // ██";
        } else {
          std::cout << "  ";
        }
      }
      std::cout << "\n";
    }
    std::cout << termcolor::reset;
  }

  void tick_with_wrap_around() {
    auto result = grid_;

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        result[i][j] = grid_[i][j];
        const auto neighbours =
            (grid_[i][(j - 1) % cols_] + grid_[i][(j + 1) % cols_] +
             grid_[(i - 1) % rows_][j] + grid_[(i + 1) % rows_][j] +
             grid_[(i - 1) % rows_][(j - 1) % cols_] +
             grid_[(i - 1) % rows_][(j + 1) % cols_] +
             grid_[(i + 1) % rows_][(j - 1) % cols_] +
             grid_[(i + 1) % rows_][(j + 1) % cols_]);
        if (grid_[i][j] == 1) {
          // Cell is alive
          if (neighbours < 2 or neighbours > 3) {
            // Any live cell with fewer than two live neighbours dies, as if by
            // underpopulation. Any live cell with more than three live
            // neighbours dies, as if by overpopulation.
            result[i][j] = 0;
          } else {
            // Any live cell with two or three live neighbours lives on to the
            // next generation.
          }
        } else {
          // Cell is dead
          if (neighbours == 3) {
            // Any dead cell with exactly three live neighbours becomes a live
            // cell, as if by reproduction.
            result[i][j] = 1;
          }
        }
      }
    }
    grid_ = result;
  }

  void tick() {
    auto result = grid_;

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        size_t neighbours = 0;

        if (j - 1 >= 0) {
            neighbours += grid_[i][j - 1];
            if (i - 1 >= 0) {
                neighbours += grid_[i - 1][j - 1];
            }
            if (i + 1 < rows_) {
                neighbours += grid_[i + 1][j - 1];
            }
        }

        if (j + 1 < cols_) {
            neighbours += grid_[i][j + 1];
            if ((i - 1) >= 0) {
                neighbours += grid_[i - 1][j + 1];
            }
            if ((i + 1) < rows_) {
                neighbours += grid_[i + 1][j + 1];
            }
        }

        if (i - 1 >= 0) {
            neighbours += grid_[i - 1][j];
        }

        if (i + 1 < rows_) {
            neighbours += grid_[i + 1][j];
        }
        
        if (grid_[i][j] == 1) {
          // Cell is alive
          if (neighbours < 2 or neighbours > 3) {
            // Any live cell with fewer than two live neighbours dies, as if by
            // underpopulation. Any live cell with more than three live
            // neighbours dies, as if by overpopulation.
            result[i][j] = 0;
          } else {
            // Any live cell with two or three live neighbours lives on to the
            // next generation.
          }
        } else {
          // Cell is dead
          if (neighbours == 3) {
            // Any dead cell with exactly three live neighbours becomes a live
            // cell, as if by reproduction.
            result[i][j] = 1;
          }
        }
      }
    }
    grid_ = result;
  }
};

} // namespace cgol