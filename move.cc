#include "move.hh"

#include "stddef.h"

Move::Move(Field* fromField, Field* toField) :
  fromField(fromField),
  toField(toField)
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
