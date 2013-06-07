#pragma once

#include "board.hh"
#include "moves.hh"
#include "position.hh"

#include "visual.hh"

class Game {
public:
  Game();
  virtual ~Game();

  void start();

private:
  bool readMove(Move*& move);
  bool getPosFromInput(unsigned char fieldInput[2], Position& pos);

  Board board;
  Moves moves;

  Visual* visual;
};
