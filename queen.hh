#pragma once

#include "piece.hh"

class Queen : public Piece {
public:
  Queen(Board* board, ePieceColor color);
  virtual ~Queen();

  bool isFieldAttacked(Field* checkedField);
  bool isMoveValid(Position toPos);

private:

};
