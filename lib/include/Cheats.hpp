#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <array>
#include <deque>
#include <optional>

namespace ms_pacman {

enum class Cheat {
  SuperSpeed
};

using Code = sf::Keyboard::Key;

struct CheatCode : std::array<Code, 3> {
  static constexpr auto length = 3;
};

constexpr CheatCode SUPER_SPEED = {{ Code::F, Code::O, Code::X }};

class Cheats {
public:
  
  std::optional<Cheat> add_cheat(Code key) {
    std::optional<Cheat> cheat;

    keys.push_back(key);

    if (keys.size() == CheatCode::length) {
      auto cheat_code = create_cheat_code();

      if (cheat_code == SUPER_SPEED)
        cheat = Cheat::SuperSpeed;

      if (cheat)
        keys.clear();
      else
        keys.pop_front();
    }

    return cheat;
  }

private:
  CheatCode create_cheat_code() {
    return keys.size() == 3 ? CheatCode{{ keys[0], keys[1], keys[2] }} : CheatCode{};
  }
  
  std::deque<Code> keys;
};

} // namespace ms_pacman