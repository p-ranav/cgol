#include <cgol/cursor_control.hpp>
#include <cgol/cursor_movement.hpp>
#include <cgol/grid.hpp>
#include <cgol/rle_parser.hpp>
#include <chrono>
#include <random>
#include <thread>
using namespace cgol;

std::random_device rd;  // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator
std::uniform_int_distribution<> distr(0, 1); // define the range

int main(int argc, char *argv[]) {
  cgol::show_console_cursor(false);

  if (argc < 2) {
    std::cout << "Usage: ./main <pattern>.rle\n";
    return EXIT_FAILURE;
  }

  size_t rows = 0, cols = 0;
  if (argc > 3) {
      rows = std::stoi(argv[2]);
      cols = std::stoi(argv[3]);
  }

  cgol::grid grid(argv[1], rows, cols);

  while (true) {
    grid.print();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    move_up(grid.rows());
    grid.tick();
  }

  cgol::show_console_cursor(true);
}