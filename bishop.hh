#pragma once

#include "piece.hh"
#include "field.hh"

class Move;

class Bishop : public Piece {
public:
  Bishop(Board* board, ePieceColor color);
  virtual ~Bishop();

  bool isFieldAttacked(Field* checkedField);
  bool isMoveValid(Move* move);

private:


};
