#pragma once

#include "piece.hh"
#include "field.hh"

class Bishop : public Piece {
public:
  Bishop(Board* board, ePieceColor color);
  virtual ~Bishop();

  bool isFieldAttacked(Field* checkedField);
  bool isMoveValid(Position toPos);

private:


};
