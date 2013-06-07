#include "king.hh"
#include "board.hh"
#include "position.hh"

#include <stdlib.h>

King::King(Board* board, ePieceColor color) :
  Piece(board, color, king) {
}

King::~King() {
}

bool King::isFieldAttacked(Field* checkedField) {
  Position checkedPosition = checkedField->getPosition();
  Position position = field->getPosition();

  if (checkedPosition == position) {
    return false;
  }

  if (!checkedField->isEmpty()) {
    if (checkedField->getPiece()->getColor() == color) {
      return false;
    }
  }

  if (abs(checkedPosition.col - position.col) <= 1 && abs(checkedPosition.row - position.row) <= 1) { 
    return true;
  }

  return false;
}

bool King::isMoveValid(Position toPos) {
  return isFieldAttacked(board->getField(toPos));
}
