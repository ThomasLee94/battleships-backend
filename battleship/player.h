#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

#include "board.h"

namespace battleship {

class Player {
  public:
    Player(const std::string name);
    virtual const int * GetBoardSize() const;
    virtual const int * GetShipCoords(const Board& board) const;
    virtual const int * GetMissileCoords(const Board& board) const;

  private:
    const std::string name_;
};  // class Player

class RandomPlayer : public Player {
  public:
    RandomPlayer(const std::string name);
    virtual const int * GetBoardSize() const;
    virtual const int * GetShipCoords(const Board& board) const;
    virtual const int * GetMissileCoords(const Board& board) const;
  private:
    const std::string name_;
};

}  // namespace battleship

#endif  // PLAYER_H_
