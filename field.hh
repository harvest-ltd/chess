#pragma once

#include "piece.hh"
#include "position.hh"

class Field {
public:
  Field();
  virtual ~Field();

  void init(Piece *newPiece);
  void setPiece(Piece *newPiece);
  Piece* getPiece();

  void setPosition(Position newPosition);
  Position getPosition();

  void removePiece();
  bool isEmpty();

private:
  Piece *piece;
  Position position;
};
