#include <cgol/grid.hpp>
using namespace cgol;

grid::grid(const std::string &rle_filename, const std::pair<size_t, size_t>& grid_size)
    : rows_{grid_size.first}, cols_{grid_size.second}, parser_{} {
  parser_.open(rle_filename, {rows_, cols_});
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

size_t grid::rows() const { return rows_; }

void grid::print(std::ostream &os) const {
  os << termcolor::bold;
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < cols_; j++) {
      const auto cell = grid_[i][j];
      if (cell == 1) {
        os << "██";
      } else {
        os << "  ";
      }
    }
    os << "\n";
  }
  os << termcolor::reset;
}

void grid::tick() {
  auto result = grid_;

  const int rows = static_cast<int>(rows_);
  const int cols = static_cast<int>(cols_);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
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

      if (j + 1 < cols) {
        neighbours += grid_[i][j + 1];
        if ((i - 1) >= 0) {
          neighbours += grid_[i - 1][j + 1];
        }
        if ((i + 1) < rows) {
          neighbours += grid_[i + 1][j + 1];
        }
      }

      if (i - 1 >= 0) {
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