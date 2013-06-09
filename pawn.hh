#pragma once

#include "piece.hh"
#include "field.hh"

class Move;

class Pawn : public Piece {
public:
  Pawn(Board* board, ePieceColor color);
  virtual ~Pawn();

  bool isFieldAttacked(Field* checkedField);
  bool isMoveValid(Move* move);

private:


};
