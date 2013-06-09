#include "queen.hh"
#include "board.hh"
#include "position.hh"
#include "move.hh"

#include <stdlib.h>

Queen::Queen(Board* board, ePieceColor color) :
  Piece(board, color, queen) {
}

Queen::~Queen() {
}

bool Queen::isFieldAttacked(Field* checkedField) {
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

  if (checkedPosition.col != position.col && checkedPosition.row != position.row && 
    abs(checkedPosition.col - position.col) != abs(checkedPosition.row - position.row)) {
    return false;
  }

  if (checkedPosition.col == position.col) {
    char diff = checkedPosition.row - position.row;
    char step = diff < 0 ? -1 : 1;
    Position stepPosition = position;
    do {
      stepPosition.row += step;
      if (stepPosition.row == checkedPosition.row) {
        return true;
      }
      if (!board->getField(stepPosition)->isEmpty()) {
        return false;
      }
    } while (true);
  }

  if (checkedPosition.row == position.row) {
    char diff = checkedPosition.col - position.col;
    char step = diff < 0 ? -1 : 1;
    Position stepPosition = position;
    do {
      stepPosition.col += step;
      if (stepPosition.col == checkedPosition.col) {
        return true;
      }
      if (!board->getField(stepPosition)->isEmpty()) {
        return false;
      }
    } while (true);
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

bool Queen::isMoveValid(Move* move) {
  return isFieldAttacked(move->getToField());
}
