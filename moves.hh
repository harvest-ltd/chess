#pragma once

#include "move.hh"

#include <vector>

class Moves {
public:
  Moves();
  virtual ~Moves();

  void addMove(Move* move);
  int getMoveCount();

private:
  std::vector<Move*> moves;

};
