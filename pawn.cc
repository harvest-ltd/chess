#include "pawn.hh"
#include "board.hh"
#include "position.hh"

#include <stdlib.h>

Pawn::Pawn(Board* board, ePieceColor color) :
  Piece(board, color, pawn) {
}

Pawn::~Pawn() {
}

bool Pawn::isFieldAttacked(Field* checkedField) {
  Position checkedPosition = checkedField->getPosition();
  Position position = field->getPosition();

  if (abs(position.col - checkedPosition.col) == 1) {
    char step = (color == white) ? 1 : -1;
    if (position.row + step == checkedPosition.row) {
      return true;
    }
  }

  return false;
}

bool Pawn::isMoveValid(Position toPos) {
  Position position = field->getPosition();

  char colDiff = toPos.col - position.col;
  char rowDiff = toPos.row - position.row;

  if (abs(rowDiff) > 2 || abs(colDiff) > 1) {
    return false;
  }

  char stepDirection = (color == white) ? 1 : -1;

  Piece* toPiece = board->getField(toPos)->getPiece();
  if (!toPiece) {
    if (board->previousMoveWasLongPawnOpening) {
      if (board->previousMoveToPosition.col == toPos.col &&
	        board->previousMoveToPosition.row == toPos.row - stepDirection) {
        toPiece = board->getField(board->previousMoveToPosition)->getPiece();
        if (color != toPiece->getColor()) {
          board->attackPreviousLongPawnOpening = true;
          return true;
        }
      }
    }
  }

  if (!toPiece) {
    if (colDiff != 0) {
      return false;
    }
    if (rowDiff == stepDirection * 2) {
      return !moved;
    }
  } else {
    if (abs(colDiff) != 1 || rowDiff != stepDirection) {
      return false;
    }
    if (color == toPiece->getColor()) {
      return false;
    }
  }

  return true;
}
