#include "king.hh"
#include "board.hh"
#include "position.hh"
#include "move.hh"

#include "debug.hh"

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

  if (abs(checkedPosition.col - position.col) <= 1 &&
      abs(checkedPosition.row - position.row) <= 1) { 
    return true;
  }

  return false;
}

bool King::isMoveValid(Move* move) {
  if (isFieldAttacked(move->getToField())) {
    return true;
  }

  // check castling
  DEBUGLINE("check castling move");  

  move->setCastling();

  if (moved) {
    DEBUGLINE("king already moved");  
    return false;
  }

  Position position = field->getPosition();
  Position toPos = move->getToField()->getPosition();
  char colDiff = toPos.col - position.col;
  if (toPos.row != position.row || abs(colDiff) != 2) {
    DEBUGLINE("not castling move");  
    return false;
  }

  char step = (colDiff == 2) ? 1 : -1;
  unsigned char numberOfEmptyFields = (step == 1) ? 2 : 3;

  for (unsigned char index = 1; index <= numberOfEmptyFields; ++index) {
    Position emptyPosition(position);
    emptyPosition.col = position.col + step * index;
    Field* emptyField = board->getField(emptyPosition);
    if (!emptyField->isEmpty()) {
      DEBUGLINE("fields aren't empty between king and rook");  
      return false;
    }
  }

  Position rookPosition(position);
  rookPosition.col = position.col + step * (numberOfEmptyFields + 1);
  Field* rookFromField = board->getField(rookPosition);
  if (rookFromField->isEmpty()) {
    DEBUGLINE("rook field is empty");  
    return false;
  }
  Piece* rookPiece = rookFromField->getPiece();
  if (rookPiece->getColor() != this->color || rookPiece->getType() != rook) {
    DEBUGLINE("no proper rook");  
    return false;
  }
  if (rookPiece->isMoved()) {
    DEBUGLINE("rook already moved");  
    return false;
  }

  rookPosition.col = position.col + step;
  Field* rookToField = board->getField(rookPosition);

  move->setRookFieldsDuringCastling(rookFromField, rookToField);

  return true;
}
