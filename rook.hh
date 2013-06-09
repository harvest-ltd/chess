#pragma once

#include "piece.hh"
#include "field.hh"

class Move;

class Rook : public Piece {
public:
  Rook(Board* board, ePieceColor color);
  virtual ~Rook();

  bool isFieldAttacked(Field* checkedField);
  bool isMoveValid(Move* move);

private:

};
