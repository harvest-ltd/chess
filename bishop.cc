#include "bishop.hh"
#include "board.hh"
#include "position.hh"
#include "move.hh"

#include <stdlib.h>

Bishop::Bishop(Board* board, ePieceColor color) :
  Piece(board, color, bishop) {
}

Bishop::~Bishop() {
}

bool Bishop::isFieldAttacked(Field* checkedField) {
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

  if (abs(checkedPosition.col - position.col) != abs(checkedPosition.row - position.row)) {
    return false;
  }

  char colStep = (checkedPosition.col - position.col) < 0 ? -1 : 1;
  char rowStep = (checkedPosition.row - position.row) < 0 ? -1 : 1;
  Position stepPosition = position;
  do {
    stepPosition.col += colStep;
    stepPosition.row += rowStep;
    if (stepPosition.col == checkedPosition.col) {
      return true;
    }

    if (!board->getField(stepPosition)->isEmpty()) {
      return false;
    }
  } while (true);

  return false;
}

bool Bishop::isMoveValid(Move* move) {
  return isFieldAttacked(move->getToField());
}
