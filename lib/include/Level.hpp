#pragma once
#include "Board.hpp"
#include "Mazes.hpp"
#include <array>
#include <optional>
#include <string_view>
#include <tuple>

namespace ms_pacman {

template<typename T, std::size_t Rows, std::size_t Columns>
using array2d = std::array<std::array<T, Columns>, Rows>;

template<typename T>
inline constexpr auto array_extent = std::tuple<>{};

template<typename T, std::size_t N>
constexpr auto array_extent<std::array<T, N>> = std::tuple_cat(std::tuple<size_t>(N), array_extent<T>);

struct Level {
  std::string_view background;
  array2d<int, ROWS, COLUMNS> maze_data;
  int num_pellets = 0;

  enum class Cell {
    WALL = 0,
    PELLET = 1,
    PATH = 2,
    PEN_DOOR = 3,
    SUPER_PELLET = 4,
    PEN = 5,
    PORTAL1 = 6,
    PORTAL2 = 7
  };

  constexpr auto create_board() const {
    using B = Board<COLUMNS, ROWS>;
    B b;
    std::array<std::optional<GridPosition>, 4> portals;
    std::size_t idx = 0;

    for (std::size_t x = 0; x < COLUMNS; x++) {
      for (std::size_t y = 0; y < ROWS; y++) {
        switch (maze_data[y][x]) {
          case static_cast<int>(Cell::WALL):
            b[y][x] = Wall{};
            break;
          case static_cast<int>(Cell::PELLET):
            b[y][x] = Pellet{};
            break;
          case static_cast<int>(Cell::PATH):
            b[y][x] = Walkable{};
            break;
          case static_cast<int>(Cell::PEN_DOOR):
            b[y][x] = PenDoor{};
            break;
          case static_cast<int>(Cell::SUPER_PELLET):
            b[y][x] = SuperPellet{};
            break;
          case static_cast<int>(Cell::PEN):
            b[y][x] = Pen{};
            break;
          case static_cast<int>(Cell::PORTAL1):
            b[y][x] = Portal{ 0 };
            portals[idx++] = { x, y };
            break;
          case static_cast<int>(Cell::PORTAL2):
            b[y][x] = Portal{ 1 };
            portals[idx++] = { x, y };
            break;
        }
      }
    }

    auto getPortal = [&](GridPosition position) -> Portal & {
      return std::get<Portal>(b[position.y][position.x]);
    };

    for (auto && portal_position : portals) {
      if (!portal_position)
        break;

      Portal & portal = getPortal(portal_position.value());
      for (auto && other_position : portals) {
        if (!other_position)
          break;
        if (portal_position == other_position)
          continue;
        Portal & other_portal = getPortal(other_position.value());
        if (portal.id != other_portal.id)
          continue;
        portal.target_position = *other_position;
      }
    }
    return b;
  }

  static constexpr int count_pellets(auto maze_data) {
    int pellets = 0;
    for (std::size_t x = 0; x < COLUMNS; x++) {
      for (std::size_t y = 0; y < ROWS; y++) {
        if (maze_data[y][x] == static_cast<int>(Cell::PELLET) || maze_data[y][x] == static_cast<int>(Cell::SUPER_PELLET))
          pellets++;
      }
    }
    return pellets;
  }

  constexpr int getNumPellets() const {
    return num_pellets;
  }
};

constexpr std::array levels = {
  Level{ "maze1.png", maze1_data, Level::count_pellets(maze1_data) },
  Level{ "maze2.png", maze2_data, Level::count_pellets(maze2_data) },
  Level{ "maze3.png", maze3_data, Level::count_pellets(maze3_data) },
  Level{ "maze4.png", maze4_data, Level::count_pellets(maze4_data) }
};

constexpr Level getLevel(std::size_t n) {
  switch (n) {
    case 0:
    case 1:
      return levels[0];
    case 2:
    case 3:
    case 4:
      return levels[1];
    default:
      // alternate between each of the last 2 maps every 4 levels
      return levels[((n - 5) % 8) < 4 ? 2 : 3];
  }
}

} // namespace ms_pacman
