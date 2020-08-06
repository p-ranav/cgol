#include <cgol/cursor_control.hpp>
#include <cgol/cursor_movement.hpp>
#include <cgol/grid.hpp>
#include <cgol/rle_parser.hpp>
#include <cgol/terminal_size.hpp>
#include <chrono>
#include <thread>
#include <csignal>
using namespace cgol;

int main(int argc, char *argv[]) {
  std::signal(SIGINT, [](int){ cgol::show_console_cursor(true); std::exit(0); });
  // Hide console cursor
  cgol::show_console_cursor(false);

  if (argc < 2) {
    std::cout << "Usage: ./main <pattern>.rle\n";
    return EXIT_FAILURE;
  }

  // Get terminal size and use as bounding box for game of life grid
  const auto terminal_size = cgol::terminal_size();
  size_t rows = terminal_size.first - 2, cols = (terminal_size.second) / 2;

  // Initiali grid with dimensions {rows, cols}
  cgol::grid grid(argv[1], {rows, cols});

  while (true) {
    grid.print();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    move_up(grid.rows());
    grid.tick();
  }

  cgol::show_console_cursor(true);
  return 0;
}
