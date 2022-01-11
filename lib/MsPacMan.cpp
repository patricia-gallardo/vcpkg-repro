#include "MsPacMan.hpp"
#include <cmath>

namespace ms_pacman {

GridPosition MsPacMan::currentSprite() const {
  return dead ? pacManAnimation.deathAnimationFrame() : pacManAnimation.animationFrame(direction);
}

Position MsPacMan::position() const {
  return pos;
}

GridPosition MsPacMan::positionInGrid() const {
  return positionToGridPosition(pos);
}

void MsPacMan::die() {
  if (dead)
    return;

  dead = true;
}

void MsPacMan::reset() {
  dead = false;
  direction = Direction::NONE;
  desired_direction = Direction::NONE;
  pos = initialPacManPosition();
}

void MsPacMan::update(std::chrono::milliseconds time_delta, Direction input_direction, const DefaultBoard & board) {
  if (dead) {
    updateAnimationPosition(time_delta, false);
    return;
  }

  if (input_direction != Direction::NONE)
    desired_direction = input_direction;

  const auto old = pos;
  updateMazePosition(time_delta, board);
  const bool paused = pos == old;
  updateAnimationPosition(time_delta, paused);
}

void MsPacMan::updateAnimationPosition(std::chrono::milliseconds time_delta, bool paused) {
  if (paused) {
    pacManAnimation.pause();
  } else {
    pacManAnimation.updateAnimationPosition(time_delta, dead);
  }
}

void MsPacMan::updateMazePosition(std::chrono::milliseconds time_delta, const DefaultBoard & board) {
  if (isPortal(board, positionInGrid(), direction)) {
    pos = gridPositionToPosition(teleport(positionInGrid()));
    return;
  }

  const double position_delta = 0.004 * double(time_delta.count());
  const auto pacman_size = 1;

  auto moveToPosition = [position_delta](Position point, Direction move_direction) {
    switch (move_direction) {
      case Direction::LEFT:
        return GridPosition{ size_t(point.x - position_delta), size_t(point.y) };
      case Direction::RIGHT:
        return GridPosition{ size_t(point.x + pacman_size), size_t(point.y) };
      case Direction::UP:
        return GridPosition{ size_t(point.x), size_t(point.y - position_delta) };
      case Direction::DOWN:
        return GridPosition{ size_t(point.x), size_t(point.y + pacman_size) };
      case Direction::NONE:
      default:
        return positionToGridPosition(point);
    }
  };

  auto canGo = [&moveToPosition, &board, this](Direction move_direction) {
    return isWalkableForPacMan(board, moveToPosition(pos, move_direction));
  };

  if (desired_direction != direction && canGo(desired_direction)) {
    direction = desired_direction;
  }

  if (!canGo(direction)) {
    return;
  }

  switch (direction) {
    case Direction::LEFT:
      pos.x -= position_delta;
      pos.y = std::floor(pos.y);
      break;
    case Direction::RIGHT:
      pos.x += position_delta;
      pos.y = std::floor(pos.y);
      break;
    case Direction::UP:
      pos.x = std::floor(pos.x);
      pos.y -= position_delta;
      break;
    case Direction::DOWN:
      pos.x = std::floor(pos.x);
      pos.y += position_delta;
      break;
    case Direction::NONE:
    default:
      break;
  }
}

} // namespace pacman
