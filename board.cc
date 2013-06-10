#include "board.hh"
#include "piece.hh"
#include "pawn.hh"
#include "rook.hh"
#include "bishop.hh"
#include "knight.hh"
#include "queen.hh"
#include "king.hh"
#include "debug.hh"

#include <iostream>
#include <stdlib.h>

Board::Board() :
  previousMoveWasLongPawnOpening(false),
  attackPreviousLongPawnOpening(false),
  lastMove(NULL)
{
  Position position;
  for (unsigned char index = 0; index < NUM_OF_FIELDS; ++index) {
    position.col = index % 8 + 1;
    position.row = (int)(index / 8) + 1;
    fields[index].setPosition(position);
  }
}

Board::~Board() {
  clear();
}

void Board::clear() {
  ENTER();
  unsigned char index;

  for (index = 0; index < whitePieces.size(); ++index) {
    delete(whitePieces[index]);
    whitePieces[index]->getField()->removePiece();
  }
  whitePieces.clear();

  for (index = 0; index < blackPieces.size(); ++index) {
    delete(blackPieces[index]);
    blackPieces[index]->getField()->removePiece();
  }
  blackPieces.clear();

  for (index = 0; index < removedPieces.size(); ++index) {
    delete(removedPieces[index]);  
  }
  removedPieces.clear();

  previousMoveWasLongPawnOpening = false;
  attackPreviousLongPawnOpening = false;
  RETURN();
}

void Board::reset() {
  ENTER();
  clear();
  
  Position pos;

  for (pos.col = 1; pos.col <= 8; ++pos.col) {
    pos.row = 2;
    addPieceToBoard(pawn, white, pos);
    
    pos.row = 7;
    addPieceToBoard(pawn, black, pos);
  }
  
  pos.row = 1;
  pos.col = 1; addPieceToBoard(rook, white, pos);
  pos.col = 2; addPieceToBoard(knight, white, pos);
  pos.col = 3; addPieceToBoard(bishop, white, pos);
  pos.col = 4; addPieceToBoard(queen, white, pos);
  pos.col = 5; addPieceToBoard(king, white, pos);
  pos.col = 6; addPieceToBoard(bishop, white, pos);
  pos.col = 7; addPieceToBoard(knight, white, pos);
  pos.col = 8; addPieceToBoard(rook, white, pos);

  pos.row = 8;
  pos.col = 1; addPieceToBoard(rook, black, pos);
  pos.col = 2; addPieceToBoard(knight, black, pos);
  pos.col = 3; addPieceToBoard(bishop, black, pos);
  pos.col = 4; addPieceToBoard(queen, black, pos);
  pos.col = 5; addPieceToBoard(king, black, pos);
  pos.col = 6; addPieceToBoard(bishop, black, pos);
  pos.col = 7; addPieceToBoard(knight, black, pos);
  pos.col = 8; addPieceToBoard(rook, black, pos);

  RETURN();
}

eResult Board::addPieceToBoard(ePieceType type, ePieceColor color, Position position) {
  Field* field = getField(position);

  if (!field->isEmpty()) {
    ERROR("Field is not empty");
    return eFieldIsNotEmpty;
  }

  Piece* piece;

  switch(type) {
    case pawn:   piece = new Pawn(this, color);   break;
    case rook:   piece = new Rook(this, color);   break; 
    case knight: piece = new Knight(this, color); break;
    case bishop: piece = new Bishop(this, color); break;
    case king:   piece = new King(this, color);   break;
    case queen:  piece = new Queen(this, color);  break;
  }

  field->init(piece);

  if (color == white) {
    whitePieces.push_back(piece);
  } else {
    blackPieces.push_back(piece);
  }

  return eOk;
}

eResult Board::movePiece(Position fromPos, Position toPos) {
  Field* fromField = getField(fromPos);
  Field* toField = getField(toPos);

  Move move(fromField, toField);
  return applyMove(&move);
}

eResult Board::applyMove(Move* move) {
  if (move->getFromField()->isEmpty()) {
    ERROR("Field is empty");
    return eFieldIsEmpty;
  }

  Piece* fromPiece = move->getFromField()->getPiece();
  Piece* toPiece = move->getToField()->getPiece();

  DEBUGLINE("move " << fromPiece->getName() << " from (" << (int)move->getFromField()->getPosition().col << ", " << (int)move->getFromField()->getPosition().row << ") " << 
                                                  "to (" << (int)move->getToField()->getPosition().col << ", " << (int)move->getToField()->getPosition().row << ")");

  if (!fromPiece->isMoveValid(move)) {
    INFO("Invalid move");
    return eInvalidMove;
  }

  move->getFromField()->removePiece();

  checkAttackPreviousLongPawnOpening();

  if (toPiece != NULL) {
    removePieceFromBoard(toPiece);
  }

  move->getToField()->setPiece(fromPiece);

  if (move->isCastling()) {
    Piece* rookPiece = move->getRookFromFieldDuringCastling()->getPiece();
    move->getRookFromFieldDuringCastling()->removePiece();
    move->getRookToFieldDuringCastling()->setPiece(rookPiece);
  }

  lastMove = move;

  storeMove(fromPiece, move->getFromField()->getPosition(), move->getToField()->getPosition());

  return eOk;
}

bool Board::isFieldAttacked(Field* field, ePieceColor attackColor) {
  if (!field) {
    return false;
  }

  if (attackColor == white) {
    for (unsigned char index = 0; index < whitePieces.size(); ++index) {
      if (whitePieces[index]->isFieldAttacked(field)) {
        return true;
      }
    }
  } else {
    for (unsigned char index = 0; index < blackPieces.size(); ++index) {
      if (blackPieces[index]->isFieldAttacked(field)) {
        return true;
      }
    }
  }

  return false;
}

Field* Board::getField(Position pos) {
  if (!pos.isValid()) {
    return NULL;
  }
  return &fields[(pos.row - 1) * 8 + (pos.col - 1)];
}

unsigned char Board::getWhitePieceCount() {
  return whitePieces.size();
}

Piece* Board::getWhitePiece(unsigned char index) {
  if (index == 0 || index > whitePieces.size()) {
    return NULL;
  }
  return whitePieces[index - 1];
}

unsigned char Board::getBlackPieceCount() {
  return blackPieces.size();
}

Piece* Board::getBlackPiece(unsigned char index) {
  if (index == 0 || index > blackPieces.size()) {
    return NULL;
  }
  return blackPieces[index - 1];
}

unsigned char Board::getRemovedPieceCount() {
  return removedPieces.size();
}

Piece* Board::getRemovedPiece(unsigned char index) {
  if (index == 0 || index > removedPieces.size()) {
    return NULL;
  }
  return removedPieces[index - 1];
}

void Board::removePieceFromBoard(Piece* piece) {
  if (!piece->getField()) {
    ERROR("piece->getField() is NULL");
    return;
  }
  piece->getField()->removePiece();
  piece->removeFromBoard();

  if (piece->getColor() == white) {
    for (unsigned char index = 0; index < whitePieces.size(); ++index) {
      if (whitePieces[index] == piece) {
        whitePieces.erase(whitePieces.begin() + index);
      }
    }
  } else {
    for (unsigned char index = 0; index < blackPieces.size(); ++index) {
      if (blackPieces[index] == piece) {
        blackPieces.erase(blackPieces.begin() + index);
      }
    }
  }

  removedPieces.push_back(piece);
}

void Board::storeMove(Piece* movedPiece, Position fromPos, Position toPos) {
  previousMoveToPosition = toPos;

  previousMoveWasLongPawnOpening = false;
  if (movedPiece->getType() == pawn) {
    if (abs(fromPos.row - toPos.row) == 2) {
      previousMoveWasLongPawnOpening = true;
    }
  }
}

void Board::checkAttackPreviousLongPawnOpening() {
  if (attackPreviousLongPawnOpening) {
    Field* previousMoveToField = getField(previousMoveToPosition);
    if (previousMoveToField) {
      removePieceFromBoard(previousMoveToField->getPiece());
    }
  }
  attackPreviousLongPawnOpening = false;
}
