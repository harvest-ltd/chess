#pragma once

#include "piece.hh"

class King : public Piece {
public:
  King(Board* board, ePieceColor color);
  virtual ~King();

  bool isFieldAttacked(Field* checkedField);
  bool isMoveValid(Position toPos);

private:

};
