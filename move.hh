#pragma once

#include "field.hh"

class Move {
public:
  Move(Field* fromField, Field* toField);
  virtual ~Move();

  Field* getFromField();
  Field* getToField();

private:
  Field* fromField;
  Field* toField;
};
