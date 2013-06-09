#include "field.hh"
#include "debug.hh"

#include "stddef.h"

Field::Field() :
  piece(NULL),
  position() {
  
}

Field::~Field() {
  delete(piece);
}

void Field::init(Piece *newPiece) {
  DEBUGLINE("init field (" << (int)position.col << ", " << (int)position.row << ") with " << newPiece->getColorName() << " " << newPiece->getName());

  piece = newPiece;
  piece->setField(this);
  piece->setMoved(false);  
}

void Field::setPiece(Piece *newPiece) {
  DEBUGLINE("set " << newPiece->getColorName() << " " << newPiece->getName() << " to (" << (int)position.col << ", " << (int)position.row << ") ");

  piece = newPiece;
  piece->setField(this);
  piece->setMoved(true);  
}

Piece* Field::getPiece() {
  return piece;
}

void Field::setPosition(Position newPosition) {
  position = newPosition;
}

Position Field::getPosition() {
  return position;
}

void Field::removePiece() {
  DEBUGLINE("remove " << piece->getColorName() << " " << piece->getName() << " from (" << (int)position.col << ", " << (int)position.row << ") ");

  piece = NULL;
}

bool Field::isEmpty() {
  return (piece == NULL);
}

