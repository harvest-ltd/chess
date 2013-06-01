#pragma once

#include "piece.hh"
#include "field.hh"

class Knight : public Piece {
public:
  Knight(Board* board, ePieceColor color);
  virtual ~Knight();

  bool isFieldAttacked(Field* checkedField);
  bool isMoveValid(Position toPos);

private:

};
