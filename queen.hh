#pragma once

#include "piece.hh"

class Move;

class Queen : public Piece {
public:
  Queen(Board* board, ePieceColor color);
  virtual ~Queen();

  bool isFieldAttacked(Field* checkedField);
  bool isMoveValid(Move* move);

private:

};
