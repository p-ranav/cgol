#include <cgol/cursor_control.hpp>
#include <cgol/cursor_movement.hpp>
#include <cgol/grid.hpp>
#include <cgol/rle_parser.hpp>
#include <cgol/terminal_size.hpp>
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

  const auto terminal_size = cgol::terminal_size();

  size_t rows = terminal_size.first - 2, cols = (terminal_size.second) / 2;

  cgol::grid grid(argv[1], rows, cols);

  while (true) {
    grid.print();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    move_up(grid.rows());
    grid.tick();
  }

  cgol::show_console_cursor(true);
}