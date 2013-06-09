#pragma once

#include "piece.hh"

class Move;

class King : public Piece {
public:
  King(Board* board, ePieceColor color);
  virtual ~King();

  bool isFieldAttacked(Field* checkedField);
  bool isMoveValid(Move* move);

private:

};
