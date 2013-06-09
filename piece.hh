#pragma once

#include "position.hh"

enum ePieceColor {
  white,
  black
};

enum ePieceType {
  pawn,
  rook,
  bishop,
  knight,
  queen,
  king
};

class Board;
class Field;

class Piece {
public:
  Piece(Board* board, ePieceColor color, ePieceType type);
  virtual ~Piece();

  ePieceColor getColor();
  ePieceType getType();
  const char* getName();

  void setField(Field* newField);
  Field* getField();

  void setMoved(bool moved);
  bool isMoved();
  bool isOnBoard();
  void removeFromBoard();

  virtual bool isFieldAttacked(Field* field) = 0;
  virtual bool isMoveValid(Position toPos) = 0;

  void getSymbol(char* symbol);

protected:
  Board* board;

  ePieceColor color;  
  ePieceType type;

  Field* field;

  bool moved;

private:
  static const char* names[];

};
