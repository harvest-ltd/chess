#pragma once

#include "piece.hh"
#include "field.hh"

class Pawn : public Piece {
public:
  Pawn(Board* board, ePieceColor color);
  virtual ~Pawn();

  bool isFieldAttacked(Field* checkedField);
  bool isMoveValid(Position toPos);

private:


};
