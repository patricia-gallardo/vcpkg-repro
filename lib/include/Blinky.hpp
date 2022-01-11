#pragma once

#include "Ghost.hpp"

namespace ms_pacman {

class Blinky final : public Ghost {
public:
  Blinky();
  void setTarget(const DefaultBoard& board, Position pacManPos);

protected:
  double speed() const override;
  Position initialPosition() const override;

private:
  Position scatterTarget() const;
};

} // namespace pacman
