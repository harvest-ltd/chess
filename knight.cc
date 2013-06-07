#include "knight.hh"
#include "board.hh"
#include "position.hh"

#include <stdlib.h>

Knight::Knight(Board* board, ePieceColor color) :
  Piece(board, color, knight) {
}

Knight::~Knight() {
}

bool Knight::isFieldAttacked(Field* checkedField) {
  Position checkedPosition = checkedField->getPosition();
  Position position = field->getPosition();

  if (!checkedField->isEmpty()) {
    if (checkedField->getPiece()->getColor() == color) {
      return false;
    }
  }

  if ((abs(position.col - checkedPosition.col) == 2 && abs(position.row - checkedPosition.row) == 1) ||
      (abs(position.col - checkedPosition.col) == 1 && abs(position.row - checkedPosition.row) == 2)) {
    return true;
  }

  return false;
}

bool Knight::isMoveValid(Position toPos) {
  return isFieldAttacked(board->getField(toPos));
}
