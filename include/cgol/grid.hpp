#pragma once
#include <array>
#include <cgol/termcolor.hpp>
#include <random>
#include <string>

namespace cgol {

template <size_t R, size_t C> class grid {
  std::array<std::array<unsigned char, C>, R> grid_{{0}};

public:
  constexpr static size_t columns = C;
  constexpr static size_t rows = R;

  std::array<unsigned char, columns> &operator[](size_t row_index) {
    return grid_[row_index];
  }

  void print() const {
    std::cout << termcolor::bold << termcolor::white;
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < columns; j++) {
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
    std::array<std::array<unsigned char, C>, R> result{{0}};
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        result[i][j] = grid_[i][j];
        const auto neighbours =
            (grid_[i][(j - 1) % columns] + grid_[i][(j + 1) % columns] +
             grid_[(i - 1) % rows][j] + grid_[(i + 1) % rows][j] +
             grid_[(i - 1) % rows][(j - 1) % columns] +
             grid_[(i - 1) % rows][(j + 1) % columns] +
             grid_[(i + 1) % rows][(j - 1) % columns] +
             grid_[(i + 1) % rows][(j + 1) % columns]);
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
    std::array<std::array<unsigned char, C>, R> result{{0}};
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        result[i][j] = grid_[i][j];
        size_t neighbours = 0;

        if (j - 1 >= 0) {
            neighbours += grid_[i][j - 1];
            if (i - 1 >= 0) {
                neighbours += grid_[i - 1][j - 1];
            }
            if (i + 1 < rows) {
                neighbours += grid_[i + 1][j - 1];
            }
        }

        if (j + 1 < columns) {
            neighbours += grid_[i][j + 1];
            if (i - 1 >= 0) {
                neighbours += grid_[i - 1][j + 1];
            }
            if (i + 1 < rows) {
                neighbours += grid_[i + 1][j + 1];
            }
        }

        if (i - i >= 0) {
            neighbours += grid_[i - 1][j];
        }
        if (i + 1 < rows) {
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