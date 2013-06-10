#pragma once

#include "field.hh"

class Move {
public:
  Move(Field* fromField, Field* toField);
  virtual ~Move();

  Field* getFromField();
  Field* getToField();

  void setCastling();
  bool isCastling();
  void setRookFieldsDuringCastling(Field* fromField, Field* toField);
  Field* getRookFromFieldDuringCastling();
  Field* getRookToFieldDuringCastling();

  void setLongPawnOpening();
  bool isLongPawnOpening();

  void setAttackOfPreviousLongOpenedPawn();
  bool isAttackOfPreviousLongOpenedPawn();

private:
  Field* fromField;
  Field* toField;

  bool castling;
  Field* rookFromFieldDuringCastling;
  Field* rookToFieldDuringCastling;

  bool longPawnOpening;
  bool attackOfPreviousLongOpenedPawn;
};
