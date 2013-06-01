#include "field.hh"
#include "stddef.h"

Field::Field() :
  piece(NULL),
  position() {
  
}

Field::~Field() {
  delete(piece);
}

void Field::init(Piece *newPiece) {
  piece = newPiece;
  piece->setField(this);
  piece->setMoved(false);  
}

void Field::setPiece(Piece *newPiece) {
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
  piece = NULL;
}

bool Field::isEmpty() {
  return (piece == NULL);
}

