#pragma once

#include "position.hh"
#include "moves.hh"

class Board;

class Visual {
public:
  Visual(Board& board, Moves& moves);
  virtual ~Visual();

  void drawBoard();

private:
  void getFieldSymbol(Position position, char* symbol);

  Board& board;
  Moves& moves;
};
