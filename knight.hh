#pragma once

#include "piece.hh"

class Move;

class Knight : public Piece {
public:
  Knight(Board* board, ePieceColor color);
  virtual ~Knight();

  bool isFieldAttacked(Field* checkedField);
  bool isMoveValid(Move* move);

private:

};
