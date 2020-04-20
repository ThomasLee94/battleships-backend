#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

#include "board.h"

namespace battleship {

class Player {
  public:
    Player(const std::string name);
    const int * GetBoardSize() const;
    const int * GetShipCoords(const Board& board) const;
    const int * GetMissileCoords(const Board& board) const;

  private:
    const std::string name_;
};  // class Player

}  // namespace battleship

#endif  // PLAYER_H_
