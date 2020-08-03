#include <cgol/cursor_control.hpp>
#include <cgol/cursor_movement.hpp>
#include <cgol/grid.hpp>
#include <cgol/rle_parser.hpp>
#include <chrono>
#include <random>
#include <string>
#include <thread>
using namespace cgol;

std::random_device rd;  // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator
std::uniform_int_distribution<> distr(0, 1); // define the range

template <size_t R, size_t C> void fill_grid_random(cgol::grid<R, C> &grid) {
  for (size_t i = 0; i < R; i++) {
    for (size_t j = 0; j < C; j++) {
      grid[i][j] = distr(gen) > 0 ? 1 : 0;
    }
  }
}

int main() {
    cgol::show_console_cursor(false);

    std::string rle_string = R"(
#N Gosper glider gun (glider destruction)
#O Dean Hickerson
#C Complete destruction of Gosper glider gun with two gliders
#C Glider destruction of the Gosper glider gun.
#C http://www.conwaylife.com/wiki/Gosper_glider_gun
#C http://www.conwaylife.com/patterns/gosperglidergungliderdestruction.rle
x = 47, y = 26, rule = B3/S23
bo$2bo$3o6$15bo$15b4o$16b4o10b2o$5b2o9bo2bo9bobo$5b2o9b4o8b3o8b2o$15b
4o8b3o9b2o$15bo12b3o$29bobo$30b2o7$45b2o$44b2o$46bo!
    )";
    cgol::rle_parser parser(rle_string);

  //   // Stable
  //   {
  //     cgol::grid<4, 4> grid;
  //     grid[1][1] = 1;
  //     grid[1][2] = 1;
  //     grid[2][1] = 1;
  //     grid[2][2] = 1;
  //     while (true) {
  //       grid.print();
  //       std::this_thread::sleep_for(std::chrono::milliseconds(50));
  //       move_up(grid.rows);
  //       grid.tick();
  //     }
  //   }

  // // Glider
  // {
  //   cgol::grid<20, 20> grid;
  //   size_t x = 1, y = 1;
  //   grid[x + 0][y + 1] = 1;
  //   grid[x + 1][y + 2] = 1;
  //   grid[x + 2][y + 0] = grid[x + 2][y + 1] = grid[x + 2][y + 2] = 1;
  //   while (true) {
  //     grid.print();
  //     std::this_thread::sleep_for(std::chrono::milliseconds(50));
  //     move_up(grid.rows);
  //     grid.tick_with_wrap_around();
  //   }
  // }

  // // Lightweight Spaceship
  // {
  //   cgol::grid<10, 10> grid;
  //   grid[1][1] = grid[1][2] = grid[1][3] = 1;
  //   grid[2][0] = grid[2][3] = 1;
  //   grid[3][3] = 1;
  //   grid[4][3] = 1;
  //   grid[5][0] = grid[5][2] = 1;
  //   while (true) {
  //     grid.print();
  //     std::this_thread::sleep_for(std::chrono::milliseconds(50));
  //     move_up(grid.rows);
  //     grid.tick();
  //   }
  // }

  //   // Glider Gun
  //   {
  //       cgol::grid<39, 15> grid;

  //       // TODO: add x offset, y offset to move this pattern in a larger
  //       board size_t x = 1, y = 0; grid[x + 1][y + 3] = grid[x + 1][y + 4] =
  //       grid[x + 2][y + 3] = grid[x + 2][y + 4] = 1;

  //       grid[x + 12][y + 1] = grid[x + 12][y + 2] = grid[x + 12][y + 6] =
  //       grid[x + 12][y + 7] = 1; grid[x + 14][y + 2] = grid[x + 14][y + 6] =
  //       1; grid[x + 15][y + 3] = grid[x + 15][y + 4] = grid[x + 15][y + 5] =
  //       1; grid[x + 16][y + 3] = grid[x + 16][y + 4] = grid[x + 16][y + 5] =
  //       1;

  //       grid[x + 19][y + 6] = 1;
  //       grid[x + 20][y + 5] = grid[x + 20][y + 6] = grid[x + 20][y + 7] = 1;
  //       grid[x + 21][y + 4] = grid[x + 21][y + 8] = 1;
  //       grid[x + 22][y + 6] = 1;
  //       grid[x + 23][y + 3] = grid[x + 23][y + 9] = 1;
  //       grid[x + 24][y + 3] = grid[x + 24][y + 9] = 1;
  //       grid[x + 25][y + 4] = grid[x + 25][y + 8] = 1;
  //       grid[x + 26][y + 5] = grid[x + 26][y + 6] = grid[x + 26][y + 7] = 1;

  //       grid[x + 35][y + 5] = grid[x + 35][y + 6] = grid[x + 36][y + 5] =
  //       grid[x + 36][y + 6] = 1;

  //       while (true) {
  //         grid.print();
  //         std::this_thread::sleep_for(std::chrono::milliseconds(50));
  //         move_up(grid.rows);
  //         grid.tick();
  //       }
  //   }

//   // Random Grid
//   {
//     cgol::grid<50, 100> grid;
//     fill_grid_random(grid);

//     while (true) {
//       grid.print();
//       std::this_thread::sleep_for(std::chrono::milliseconds(10));
//       move_up(grid.rows);
//       grid.tick();
//     }
//   }

  cgol::show_console_cursor(true);
}