#include "pawn.hh"
#include "board.hh"
#include "position.hh"
#include "move.hh"

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

bool Pawn::isMoveValid(Move* move) {
  Position position = field->getPosition();
  Position toPos = move->getToField()->getPosition();

  char colDiff = toPos.col - position.col;
  char rowDiff = toPos.row - position.row;

  if (abs(rowDiff) > 2 || abs(colDiff) > 1) {
    return false;
  }

  char stepDirection = (color == white) ? 1 : -1;

  Piece* toPiece = board->getField(toPos)->getPiece();
  if (!toPiece) {
    Move* lastMove = board->getLastMove();
    if (lastMove && lastMove->isLongPawnOpening()) {
      Position previousMoveToPosition = lastMove->getToField()->getPosition();
      if (previousMoveToPosition.col == toPos.col &&
	        previousMoveToPosition.row == toPos.row - stepDirection) {
        toPiece = board->getField(previousMoveToPosition)->getPiece();
        if (color != toPiece->getColor()) {
          move->setAttackOfPreviousLongOpenedPawn();
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
      if (!moved) {
        move->setLongPawnOpening();
      }
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
