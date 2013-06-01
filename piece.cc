#include "piece.hh"
#include <stdio.h>

Piece::Piece(Board* board, ePieceColor color, ePieceType type) :
  board(board),
  color(color),
  type(type),
  field(NULL),
  moved(false) {
}

Piece::~Piece() {
}

ePieceColor Piece::getColor() {
  return color;
}

ePieceType Piece::getType() {
  return type;
}

void Piece::setField(Field* newField) {
  field = newField;
  moved = true;
}

Field* Piece::getField() {
  return field;
}

void Piece::setMoved(bool moved) {
  this->moved = moved;
}

bool Piece::isMoved() {
  return moved;
}

bool Piece::isOnBoard() {
  return field;
}

void Piece::removeFromBoard() {
  field = NULL;
}

void Piece::getSymbol(char* symbol) {
  unsigned char letter = 0;

  switch(type) {
    case pawn:   letter = 'P'; break;
    case rook:   letter = 'R'; break;
    case bishop: letter = 'B'; break;
    case knight: letter = 'N'; break;
    case queen:  letter = 'Q'; break;
    case king:   letter = 'K'; break;
  }

  if (color == white) {
    sprintf(symbol, "%c", letter);
  } else {
    sprintf(symbol, "%c[%d;%d;%dm%c%c[%dm", 27, 0, 37, 40, letter, 27, 0);
  }
}
