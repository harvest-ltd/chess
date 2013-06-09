#include "rook.hh"
#include "board.hh"
#include "position.hh"
#include "move.hh"

Rook::Rook(Board* board, ePieceColor color) :
  Piece(board, color, rook) {
}

Rook::~Rook() {
}

bool Rook::isFieldAttacked(Field* checkedField) {
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
 
  if (checkedPosition.col != position.col && checkedPosition.row != position.row) {
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

  return false;
}

bool Rook::isMoveValid(Move* move) {
  return isFieldAttacked(move->getToField());
}
