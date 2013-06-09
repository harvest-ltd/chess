#include "move.hh"

#include "stddef.h"

Move::Move(Field* fromField, Field* toField) :
  fromField(fromField),
  toField(toField),
  castling(false),
  rookFromFieldDuringCastling(NULL),
  rookToFieldDuringCastling(NULL)
{
}

Move::~Move() {
}
  
Field* Move::getFromField() {
  return fromField;
}

Field* Move::getToField() {
  return toField;
}

void Move::setCastling() {
  castling = true;
}

bool Move::isCastling() {
  return castling;
}

void Move::setRookFieldsDuringCastling(Field* fromField, Field* toField) {
  rookFromFieldDuringCastling = fromField;
  rookToFieldDuringCastling = toField;
}

Field* Move::getRookFromFieldDuringCastling() {
  return rookFromFieldDuringCastling;
}

Field* Move::getRookToFieldDuringCastling() {
  return rookToFieldDuringCastling;
}
