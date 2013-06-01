#pragma once

#include "position.hh"

class Board;

class Visual {
public:
  Visual(Board& board);
  virtual ~Visual();

  void drawBoard();

private:
  void getFieldSymbol(Position position, char* symbol);

  Board& board;

};
