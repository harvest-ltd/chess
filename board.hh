#pragma once

#include "field.hh"
#include "piece.hh"
#include "position.hh"
#include "move.hh"
#include "visual.hh"

#include <vector>

#define NUM_OF_FIELDS 64

enum eResult {
  eOk,
  eFieldIsEmpty,
  eFieldIsNotEmpty,
  eInvalidMove
};

class Board {
public:
  Board();
  virtual ~Board();

  void clear();
  void reset();

  eResult addPieceToBoard(ePieceType type, ePieceColor color, Position position);
  eResult applyMove(Move* move);

  bool isFieldAttacked(Field* field, ePieceColor attackColor);

  Field* getField(Position pos);

  unsigned char getWhitePieceCount();
  Piece* getWhitePiece(unsigned char index);
  unsigned char getBlackPieceCount();
  Piece* getBlackPiece(unsigned char index);
  unsigned char getRemovedPieceCount();
  Piece* getRemovedPiece(unsigned char index);

  Move* getLastMove();

private:
  Field fields[NUM_OF_FIELDS];
  std::vector<Piece*> whitePieces;
  std::vector<Piece*> blackPieces;
  std::vector<Piece*> removedPieces;

  Move* lastMove;

  friend void Visual::drawBoard();

  void removePieceFromBoard(Piece* piece);
};
