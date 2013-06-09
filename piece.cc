#include "piece.hh"
#include <stdio.h>

const char* Piece::names[] = { "Pawn", "Rook", "Bishop", "Knight", "Queen", "King" };

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

const char* Piece::getName() {
  return Piece::names[type];
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
    sprintf(symbol, "\033[7m%c\033[0m", letter);
  }
}
