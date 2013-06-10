#include "test.hh"
#include "pawn.hh"
#include "rook.hh"
#include "knight.hh"
#include "bishop.hh"
#include "queen.hh"
#include "king.hh"

#include <iostream>
#include <stdlib.h>
#include <assert.h>

#define PRINT_TESTCASE(testcase) { \
  std::cout << "  " << testcase << std::endl; \
}

#define PRINT_TESTSUITE(testsuite) { \
  std::cout << std::endl << "Testsuite: " << testsuite << std::endl; \
}

#define ASSERT(condition) { \
  if (!(condition)) { \
    std::cerr << "ASSERT FAILED: " << __FILE__ << " (" << __LINE__ << ") " << #condition << std::endl; \
    exit(-1); \
  } \
}

#define ASSERT_EQUAL(left, right) { \
  if (left != right) { \
    std::cerr << "ASSERT FAILED: " << __FILE__ << " (" << __LINE__ << ") " << #left << " != " << #right << " -> " << left << " != " << right << std::endl; \
    exit(-1); \
  } \
}

#define ASSERT_FIGURE(piece, type, color) { \
  ASSERT(piece); \
  ASSERT(piece->getType() == type); \
  ASSERT(piece->getColor() == color); \
}

#define ASSERT_FIELD_ATTACK(condition, pos, shouldBeAttacked) { \
  if (!(condition)) { \
    std::cerr << "ASSERT FAILED: field at position: (" << (int)pos.col << ", " << (int)pos.row << ") "; \
    if (shouldBeAttacked) { \
      std::cerr << " should be attacked"; \
    } else { \
      std::cerr << " shouldn't be attacked"; \
    } \
    std::cerr << std::endl; \
  } \
  ASSERT(condition); \
}

Test::Test() {
}

Test::~Test() {
}

void Test::run() {

  PRINT_TESTSUITE("Board");
  resetBoard(); 
  cleanBoard();

  PRINT_TESTSUITE("Piece");
  addPieceToBoard();
  movePieceToEmptyField();
  movePieceToNotEmptyField();
  movePieceFromEmptyField();
  pieceVectors();

  PRINT_TESTSUITE("Move");
  pawnShortOpening();
  pawnLongOpening();
  pawnLongMoveAfterOpening();
  pawnStep();
  pawnInvalidAttackMove();
  pawnKillsLongOpeningPawn();

  kingCastling();
  kingCastlingBlockedByOtherPiece();
  kingCastlingKingAlreadyMoved();
  kingCastlingRookAlreadyMoved();
  kingCastlingRookHasDifferentColor();

  PRINT_TESTSUITE("Attack");
  whitePawnAttack();
  blackPawnAttack();
  pawnAttackOnTheEdge();

  rookAttackOnEmptyBoard();
  rookAttackWithBlocking();
  rookAttackWithTotalBlocking();

  knightAttack();

  bishopAttackOnEmptyBoard();
  bishopAttackWithBlocking();
  bishopAttackWithTotalBlocking();

  queenAttackOnEmptyBoard();
  queenAttackWithBlocking();
  queenAttackWithTotalBlocking();

  kingAttack();

  totalAttackAfterBoardReset();

  std::cout << std::endl << "All tests ok!" << std::endl << std::endl;
}

void Test::resetBoard() {
  PRINT_TESTCASE("resetBoard");

  Board board;
  board.reset();

  Position pos;

  ePieceType pieces[] = { rook, knight, bishop, queen, king, bishop, knight, rook };
  
  for (pos.col = 1; pos.col <= 8; ++pos.col) {
    pos.row = 1;
    ASSERT_FIGURE(board.getField(pos)->getPiece(), pieces[pos.col - 1], white);

    pos.row = 2;
    ASSERT_FIGURE(board.getField(pos)->getPiece(), pawn, white);

    pos.row = 7;
    ASSERT_FIGURE(board.getField(pos)->getPiece(), pawn, black);

    pos.row = 8;
    ASSERT_FIGURE(board.getField(pos)->getPiece(), pieces[pos.col - 1], black);
  }

  for (pos.row = 3; pos.row <= 6; ++pos.row) {
    for (pos.col = 1; pos.col <= 8; ++pos.col) {
      ASSERT(board.getField(pos)->getPiece() == NULL);
    }
  }

  ASSERT(board.getWhitePieceCount() == 16);
  ASSERT(board.getBlackPieceCount() == 16);
  ASSERT(board.getRemovedPieceCount() == 0);
}

void Test::cleanBoard() {
  PRINT_TESTCASE("cleanBoard");

  Board board;
  board.reset();
  board.clear();
 
  ASSERT(board.getWhitePieceCount() == 0);
  ASSERT(board.getBlackPieceCount() == 0);
  ASSERT(board.getRemovedPieceCount() == 0);

  Position pos;
  for (pos.row = 1; pos.row <= 8; ++pos.row) {
    for (pos.col = 1; pos.col <= 8; ++pos.col) {
      ASSERT(board.getField(pos)->getPiece() == NULL);
    }
  }
}

void Test::addPieceToBoard() {
  PRINT_TESTCASE("addPieceToBoard");

  Board board;

  Position position(2, 2);

  ASSERT(board.getField(position)->getPiece() == NULL);

  ASSERT(board.addPieceToBoard(pawn, white, position) == eOk);
  ASSERT(board.addPieceToBoard(pawn, white, position) == eFieldIsNotEmpty);

  ASSERT_FIGURE(board.getField(position)->getPiece(), pawn, white);
  ASSERT(board.getField(position)->getPiece()->getField()->getPosition() == position);
}

void Test::movePieceToEmptyField() {
  PRINT_TESTCASE("movePieceToEmptyField");

  Board board;

  Position fromPos(2, 2);
  Position toPos(2, 3);

  Field* fromField = board.getField(fromPos);
  Field* toField = board.getField(toPos);
  Move move(fromField, toField);

  board.addPieceToBoard(pawn, white, fromPos);

  ASSERT_FIGURE(board.getField(fromPos)->getPiece(), pawn, white);
  ASSERT(board.getField(toPos)->getPiece() == NULL);

  ASSERT(board.applyMove(&move) == eOk);

  ASSERT(board.getField(fromPos)->getPiece() == NULL);
  ASSERT_FIGURE(board.getField(toPos)->getPiece(), pawn, white);
  ASSERT(board.getField(toPos)->getPiece()->getField()->getPosition() == toPos);
}

void Test::movePieceToNotEmptyField() {
  PRINT_TESTCASE("movePieceToNotEmptyField");

  Board board;

  Position fromPos(2, 2);
  Position toPos(3, 3);

  Field* fromField = board.getField(fromPos);
  Field* toField = board.getField(toPos);
  Move move(fromField, toField);

  board.addPieceToBoard(pawn, white, fromPos);
  board.addPieceToBoard(rook, black, toPos);

  ASSERT_FIGURE(board.getField(fromPos)->getPiece(), pawn, white);
  ASSERT_FIGURE(board.getField(toPos)->getPiece(), rook, black);

  ASSERT(board.applyMove(&move) == eOk);

  ASSERT(board.getField(fromPos)->getPiece() == NULL);
  ASSERT_FIGURE(board.getField(toPos)->getPiece(), pawn, white);
}

void Test::movePieceFromEmptyField() {
  PRINT_TESTCASE("movePieceFromEmptyField");

  Board board;

  Position fromPos(2, 2);
  Position toPos(3, 3);

  Field* fromField = board.getField(fromPos);
  Field* toField = board.getField(toPos);
  Move move(fromField, toField);

  board.addPieceToBoard(rook, black, toPos);

  ASSERT(board.applyMove(&move) == eFieldIsEmpty);

  ASSERT(board.getField(fromPos)->getPiece() == NULL);
  ASSERT_FIGURE(board.getField(toPos)->getPiece(), rook, black);
}

void Test::pieceVectors() {
  PRINT_TESTCASE("pieceVectors");

  Board board;

  Position fromPos(2, 2);
  Position toPos(3, 3);

  Field* fromField = board.getField(fromPos);
  Field* toField = board.getField(toPos);
  Move move(fromField, toField);

  board.addPieceToBoard(pawn, white, fromPos);
  board.addPieceToBoard(rook, black, toPos);

  ASSERT(board.getWhitePieceCount() == 1);
  ASSERT(board.getWhitePiece(0) == NULL); 
  ASSERT_FIGURE(board.getWhitePiece(1), pawn, white); 
  ASSERT(board.getWhitePiece(2) == NULL); 

  ASSERT(board.getBlackPieceCount() == 1);
  ASSERT(board.getBlackPiece(0) == NULL); 
  ASSERT_FIGURE(board.getBlackPiece(1), rook, black); 
  ASSERT(board.getBlackPiece(2) == NULL); 

  ASSERT(board.getRemovedPieceCount() == 0);
  ASSERT(board.getRemovedPiece(1) == NULL); 

  ASSERT(board.applyMove(&move) == eOk);

  ASSERT(board.getWhitePieceCount() == 1);
  ASSERT_FIGURE(board.getWhitePiece(1), pawn, white); 

  ASSERT(board.getBlackPieceCount() == 0);
  ASSERT(board.getBlackPiece(1) == NULL); 

  ASSERT(board.getRemovedPieceCount() == 1);
  ASSERT(board.getRemovedPiece(0) == NULL); 
  ASSERT_FIGURE(board.getRemovedPiece(1), rook, black); 
  ASSERT(board.getRemovedPiece(2) == NULL); 
}

void Test::pawnShortOpening() {
  PRINT_TESTCASE("pawnShortOpening");

  Board board;

  Position fromPos(2, 2);
  Position toPos(2, 3);

  Field* fromField = board.getField(fromPos);
  Field* toField = board.getField(toPos);
  Move move1(fromField, toField);

  board.addPieceToBoard(pawn, white, fromPos);

  ASSERT(board.applyMove(&move1) == eOk); 
 
  fromPos.row = 7;
  toPos.row = 6;

  fromField = board.getField(fromPos);
  toField = board.getField(toPos);
  Move move2(fromField, toField);

  board.addPieceToBoard(pawn, black, fromPos);

  ASSERT(board.applyMove(&move2) == eOk); 
}

void Test::pawnLongOpening() {
  PRINT_TESTCASE("pawnLongOpening");

  Board board;
  eResult result;

  Position fromPos(2, 2);
  Position toPos(2, 4);

  Field* fromField = board.getField(fromPos);
  Field* toField = board.getField(toPos);
  Move move1(fromField, toField);

  board.addPieceToBoard(pawn, white, fromPos);

  result = board.applyMove(&move1);
  ASSERT_EQUAL(result, eOk); 

  fromPos.row = 7;
  toPos.row = 5;

  fromField = board.getField(fromPos);
  toField = board.getField(toPos);
  Move move2(fromField, toField);

  board.addPieceToBoard(pawn, black, fromPos);

  result = board.applyMove(&move2);
  ASSERT_EQUAL(result, eOk); 
}

void Test::pawnLongMoveAfterOpening() {
  PRINT_TESTCASE("pawnLongMoveAfterOpening");

  Board board;
  eResult result;

  Position fromPos(2, 2);
  Position toPos1(2, 3);
  Position toPos2(2, 5);

  Field* fromField = board.getField(fromPos);
  Field* toField1 = board.getField(toPos1);
  Field* toField2 = board.getField(toPos2);
  Move move1(fromField, toField1);
  Move move2(toField1, toField2);

  board.addPieceToBoard(pawn, white, fromPos);

  result = board.applyMove(&move1);
  ASSERT_EQUAL(result, eOk); 
  result = board.applyMove(&move2);
  ASSERT_EQUAL(result, eInvalidMove); 

  fromPos.row = 7;
  toPos1.row = 6;
  toPos2.row = 4;
  fromField = board.getField(fromPos);
  toField1 = board.getField(toPos1);
  toField2 = board.getField(toPos2);

  Move move3(fromField, toField1);
  Move move4(toField1, toField2);

  board.addPieceToBoard(pawn, black, fromPos);

  result = board.applyMove(&move3);
  ASSERT_EQUAL(result, eOk); 
  result = board.applyMove(&move4);
  ASSERT_EQUAL(result, eInvalidMove); 
}

void Test::pawnStep() {
  PRINT_TESTCASE("pawnStep");

  Board board;
  eResult result;

  Position whiteFromPos(2, 5);
  Position whiteToPos(2, 6);

  Field* fromField = board.getField(whiteFromPos);
  Field* toField = board.getField(whiteToPos);
  Move move1(fromField, toField);

  board.addPieceToBoard(pawn, white, whiteFromPos);

  result = board.applyMove(&move1);
  ASSERT_EQUAL(result, eOk); 

  Position blackFromPos(4, 7);
  Position blackToPos(4, 6);

  fromField = board.getField(blackFromPos);
  toField = board.getField(blackToPos);
  Move move2(fromField, toField);

  board.addPieceToBoard(pawn, black, blackFromPos);

  result = board.applyMove(&move2);
  ASSERT_EQUAL(result, eOk); 
}

void Test::pawnInvalidAttackMove() {
  PRINT_TESTCASE("pawnInvalidAttackMove");

  Board board;
  eResult result;

  Position whiteFromPos(2, 5);
  Position whiteToPos(3, 6);

  Field* fromField = board.getField(whiteFromPos);
  Field* toField = board.getField(whiteToPos);
  Move move1(fromField, toField);

  board.addPieceToBoard(pawn, white, whiteFromPos);

  result = board.applyMove(&move1);
  ASSERT_EQUAL(result, eInvalidMove); 

  Position blackFromPos(4, 7);
  Position blackToPos(5, 6);

  fromField = board.getField(blackFromPos);
  toField = board.getField(blackToPos);
  Move move2(fromField, toField);

  board.addPieceToBoard(pawn, black, blackFromPos);

  result = board.applyMove(&move2);
  ASSERT_EQUAL(result, eInvalidMove); 
}

void Test::pawnKillsLongOpeningPawn() {
  PRINT_TESTCASE("pawnKillsLongOpeningPawn");

  Board board;
  eResult result;

  Position blackFromPos(3, 7);
  Position blackToPos(3, 5);

  Field* blackFromField = board.getField(blackFromPos);
  Field* blackToField = board.getField(blackToPos);
  Move move1(blackFromField, blackToField);

  board.addPieceToBoard(pawn, black, blackFromPos);

  Position whiteFromPos(2, 5);
  Position whiteToPos(3, 6);

  Field* whiteFromField = board.getField(whiteFromPos);
  Field* whiteToField = board.getField(whiteToPos);
  Move move2(whiteFromField, whiteToField);

  board.addPieceToBoard(pawn, white, whiteFromPos);

  result = board.applyMove(&move1);
  ASSERT_EQUAL(result, eOk); 

  result = board.applyMove(&move2);
  ASSERT_EQUAL(result, eOk); 

  ASSERT(board.getField(blackToPos)->getPiece() == NULL);

  whiteFromPos.col = 2;
  whiteFromPos.row = 2;
  whiteToPos.col = 2;
  whiteToPos.row = 4;

  whiteFromField = board.getField(whiteFromPos);
  whiteToField = board.getField(whiteToPos);
  Move move3(whiteFromField, whiteToField);

  board.addPieceToBoard(pawn, white, whiteFromPos);

  blackFromPos.col = 3;
  blackFromPos.row = 4;
  blackToPos.col = 2;
  blackToPos.row = 3;

  blackFromField = board.getField(blackFromPos);
  blackToField = board.getField(blackToPos);
  Move move4(blackFromField, blackToField);

  board.addPieceToBoard(pawn, black, blackFromPos);

  result = board.applyMove(&move3);
  ASSERT_EQUAL(result, eOk); 

  result = board.applyMove(&move4);
  ASSERT_EQUAL(result, eOk); 

  ASSERT(board.getField(whiteToPos)->getPiece() == NULL);
}

void Test::kingCastling() {
  PRINT_TESTCASE("kingCastling");

  Board board;
  eResult result;

  // short castling
  Position kingFromPos(5, 1);
  Position kingToPos(7, 1);

  Field* kingFromField = board.getField(kingFromPos);
  Field* kingToField = board.getField(kingToPos);
  Move move1(kingFromField, kingToField);

  Position rookFromPos(8, 1);
  Position rookToPos(6, 1);

  board.addPieceToBoard(king, white, kingFromPos);
  board.addPieceToBoard(rook, white, rookFromPos);

  result = board.applyMove(&move1);
  ASSERT_EQUAL(result, eOk); 

  ASSERT(board.getField(rookFromPos)->getPiece() == NULL);
  ASSERT_FIGURE(board.getField(rookToPos)->getPiece(), rook, white);

  // long castling
  board.clear();

  kingToPos.col = 3;

  kingFromField = board.getField(kingFromPos);
  kingToField = board.getField(kingToPos);
  Move move2(kingFromField, kingToField);

  rookFromPos.col = 1;
  rookToPos.col = 4;

  board.addPieceToBoard(king, white, kingFromPos);
  board.addPieceToBoard(rook, white, rookFromPos);
  
  result = board.applyMove(&move2);
  ASSERT_EQUAL(result, eOk); 

  ASSERT(board.getField(rookFromPos)->getPiece() == NULL);
  ASSERT_FIGURE(board.getField(rookToPos)->getPiece(), rook, white);
}

void Test::kingCastlingBlockedByOtherPiece() {
  PRINT_TESTCASE("kingCastlingBlockedByOtherPiece");

  Board board;
  eResult result;

  Position kingFromPos(5, 1);
  Position kingToPos(7, 1);

  Field* kingFromField = board.getField(kingFromPos);
  Field* kingToField = board.getField(kingToPos);
  Move move(kingFromField, kingToField);

  Position rookPos(8, 1);
  Position pawnPos(6, 1);

  board.addPieceToBoard(king, white, kingFromPos);
  board.addPieceToBoard(rook, white, rookPos);
  board.addPieceToBoard(pawn, white, pawnPos);

  result = board.applyMove(&move);
  ASSERT_EQUAL(result, eInvalidMove); 
}

void Test::kingCastlingKingAlreadyMoved() {
  PRINT_TESTCASE("kingCastlingKingAlreadyMoved");

  Board board;
  eResult result;

  Position kingFromPos(5, 1);
  Position kingToPos(6, 1);

  Field* kingFromField = board.getField(kingFromPos);
  Field* kingToField = board.getField(kingToPos);
  Move move1(kingFromField, kingToField);
  Move move2(kingToField, kingFromField);

  Position rookPos(8, 1);

  board.addPieceToBoard(king, white, kingFromPos);
  board.addPieceToBoard(rook, white, rookPos);

  result = board.applyMove(&move1);
  ASSERT_EQUAL(result, eOk); 
  result = board.applyMove(&move2);
  ASSERT_EQUAL(result, eOk); 

  kingToPos.col = 7;
  kingFromField = board.getField(kingFromPos);
  kingToField = board.getField(kingToPos);
  Move move3(kingFromField, kingToField);

  result = board.applyMove(&move3);
  ASSERT_EQUAL(result, eInvalidMove); 
}

void Test::kingCastlingRookAlreadyMoved() {
  PRINT_TESTCASE("kingCastlingRookAlreadyMoved");

  Board board;
  eResult result;

  Position rookFromPos(8, 1);
  Position rookToPos(8, 2);

  Field* rookFromField = board.getField(rookFromPos);
  Field* rookToField = board.getField(rookToPos);
  Move move1(rookFromField, rookToField);
  Move move2(rookToField, rookFromField);

  Position kingFromPos(5, 1);
  Position kingToPos(7, 1);

  Field* kingFromField = board.getField(kingFromPos);
  Field* kingToField = board.getField(kingToPos);
  Move move3(kingFromField, kingToField);

  board.addPieceToBoard(king, white, kingFromPos);
  board.addPieceToBoard(rook, white, rookFromPos);

  result = board.applyMove(&move1);
  ASSERT_EQUAL(result, eOk); 
  result = board.applyMove(&move2);
  ASSERT_EQUAL(result, eOk); 

  result = board.applyMove(&move3);
  ASSERT_EQUAL(result, eInvalidMove); 
}

void Test::kingCastlingRookHasDifferentColor() {
  PRINT_TESTCASE("kingCastlingRookHasDifferentColor");

  Board board;
  eResult result;

  Position kingFromPos(5, 1);
  Position kingToPos(7, 1);

  Field* kingFromField = board.getField(kingFromPos);
  Field* kingToField = board.getField(kingToPos);
  Move move(kingFromField, kingToField);

  Position rookPos(8, 1);

  board.addPieceToBoard(king, white, kingFromPos);
  board.addPieceToBoard(rook, black, rookPos);

  result = board.applyMove(&move);
  ASSERT_EQUAL(result, eInvalidMove); 
}

void Test::whitePawnAttack() {
  PRINT_TESTCASE("whitePawnAttack");

  Board board;

  Position position(2, 2);
  board.addPieceToBoard(pawn, white, position);

  std::vector<Position> attackedPositions;
  attackedPositions.push_back(Position(position.col - 1, position.row + 1));
  attackedPositions.push_back(Position(position.col + 1, position.row + 1));
  
  checkAttackedPositions(board, attackedPositions, white);
}

void Test::blackPawnAttack() {
  PRINT_TESTCASE("blackPawnAttack");

  Board board;

  Position position(2, 2);
  board.addPieceToBoard(pawn, black, position);

  std::vector<Position> attackedPositions;
  attackedPositions.push_back(Position(position.col - 1, position.row - 1));
  attackedPositions.push_back(Position(position.col + 1, position.row - 1));
  
  checkAttackedPositions(board, attackedPositions, black);
}

void Test::pawnAttackOnTheEdge() {
  PRINT_TESTCASE("pawnAttackOnTheEdge");

  Board board;

  Position position1(1, 2);
  Position position2(8, 2);
  board.addPieceToBoard(pawn, white, position1);
  board.addPieceToBoard(pawn, white, position2);

  std::vector<Position> attackedPositions;
  attackedPositions.push_back(Position(position1.col + 1, position1.row + 1));
  attackedPositions.push_back(Position(position2.col - 1, position2.row + 1));
  
  checkAttackedPositions(board, attackedPositions, white);
}

void Test::rookAttackOnEmptyBoard() {
  PRINT_TESTCASE("rookAttackOnEmptyBoard");

  Board board;

  Position position(4, 4);
  board.addPieceToBoard(rook, white, position);

  std::vector<Position> attackedPositions;
  for (unsigned char index = 1; index <= 8; ++index) {
    if (index != position.col) {
      attackedPositions.push_back(Position(index, position.row));
    }
    if (index != position.row) {
      attackedPositions.push_back(Position(position.col, index));
    }
  }
  
  checkAttackedPositions(board, attackedPositions, white);
}

void Test::rookAttackWithBlocking() {
  PRINT_TESTCASE("rookAttackWithBlocking");

  Board board;

  Position position(4, 4);
  board.addPieceToBoard(rook, white, position);
  board.addPieceToBoard(pawn, black, Position(position.col, position.row - 2));
  board.addPieceToBoard(pawn, black, Position(position.col, position.row + 2));
  board.addPieceToBoard(pawn, black, Position(position.row - 2, position.row));
  board.addPieceToBoard(pawn, black, Position(position.row + 2, position.row));

  std::vector<Position> attackedPositions;
  for (unsigned char index = position.col - 2; index <= position.col + 2; ++index) {
    if (index != position.col) {
      attackedPositions.push_back(Position(index, position.row));
    }
    if (index != position.row) {
      attackedPositions.push_back(Position(position.col, index));
    }
  }
  
  checkAttackedPositions(board, attackedPositions, white);
}

void Test::rookAttackWithTotalBlocking() {
  PRINT_TESTCASE("rookAttackWithTotalBlocking");

  Board board;

  Position position(4, 4);
  board.addPieceToBoard(rook, white, position);

  std::vector<Position> attackedPositions;
  attackedPositions.push_back(Position(position.col, position.row - 1));
  attackedPositions.push_back(Position(position.col, position.row + 1));
  attackedPositions.push_back(Position(position.col - 1, position.row));
  attackedPositions.push_back(Position(position.col + 1, position.row));

  for (unsigned char index = 0; index < attackedPositions.size(); ++index) {
    board.addPieceToBoard(pawn, black, attackedPositions[index]);
  }

  checkAttackedPositions(board, attackedPositions, white);
}

void Test::knightAttack() {
  PRINT_TESTCASE("knightAttack");

  Board board;

  Position position(4, 4);
  board.addPieceToBoard(knight, white, position);

  std::vector<Position> attackedPositions;
  attackedPositions.push_back(Position(position.col - 1, position.row - 2));
  attackedPositions.push_back(Position(position.col - 1, position.row + 2));
  attackedPositions.push_back(Position(position.col + 1, position.row - 2));
  attackedPositions.push_back(Position(position.col + 1, position.row + 2));
  attackedPositions.push_back(Position(position.col - 2, position.row - 1));
  attackedPositions.push_back(Position(position.col - 2, position.row + 1));
  attackedPositions.push_back(Position(position.col + 2, position.row - 1));
  attackedPositions.push_back(Position(position.col + 2, position.row + 1));
  
  checkAttackedPositions(board, attackedPositions, white);
}

void Test::bishopAttackOnEmptyBoard() {
  PRINT_TESTCASE("bishopAttackOnEmptyBoard");

  Board board;

  Position position(4, 4);
  board.addPieceToBoard(bishop, white, position);

  std::vector<Position> attackedPositions;
  for (unsigned char index = 1; index <= 8; ++index) {
    if (index != position.col) {
      attackedPositions.push_back(Position(index, index));
    }
  }
  for (unsigned char index = 1; index <= 7; ++index) {
    if (index != position.col) {
      attackedPositions.push_back(Position(index, 8 - index));
    }
  }
  
  checkAttackedPositions(board, attackedPositions, white);
}

void Test::bishopAttackWithBlocking() {
  PRINT_TESTCASE("bishopAttackWithBlocking");

  Board board;

  Position position(4, 4);
  board.addPieceToBoard(bishop, white, position);
  board.addPieceToBoard(pawn, black, Position(position.col - 2, position.row - 2));
  board.addPieceToBoard(pawn, black, Position(position.col - 2, position.row + 2));
  board.addPieceToBoard(pawn, black, Position(position.col + 2, position.row - 2));
  board.addPieceToBoard(pawn, black, Position(position.col + 2, position.row + 2));

  std::vector<Position> attackedPositions;
  for (unsigned char index = position.col - 2; index <= position.col + 2; ++index) {
    if (index != position.col) {
      attackedPositions.push_back(Position(index, index));
      attackedPositions.push_back(Position(index, 8 - index));
    }
  }
  
  checkAttackedPositions(board, attackedPositions, white);
}

void Test::bishopAttackWithTotalBlocking() {
  PRINT_TESTCASE("bishopAttackWithTotalBlocking");

  Board board;

  Position position(4, 4);
  board.addPieceToBoard(bishop, white, position);

  std::vector<Position> attackedPositions;
  attackedPositions.push_back(Position(position.col - 1, position.row - 1));
  attackedPositions.push_back(Position(position.col - 1, position.row + 1));
  attackedPositions.push_back(Position(position.col + 1, position.row - 1));
  attackedPositions.push_back(Position(position.col + 1, position.row + 1));

  for (unsigned char index = 0; index < attackedPositions.size(); ++index) {
    board.addPieceToBoard(pawn, black, attackedPositions[index]);
  }

  checkAttackedPositions(board, attackedPositions, white);
}

void Test::queenAttackOnEmptyBoard() {
  PRINT_TESTCASE("queenAttackOnEmptyBoard");

  Board board;

  Position position(4, 4);
  board.addPieceToBoard(queen, white, position);

  std::vector<Position> attackedPositions;
  for (unsigned char index = 1; index <= 8; ++index) {
    if (index != position.col) {
      attackedPositions.push_back(Position(index, position.row));
    }
    if (index != position.row) {
      attackedPositions.push_back(Position(position.col, index));
    }
  }

  for (unsigned char index = 1; index <= 8; ++index) {
    if (index != position.col) {
      attackedPositions.push_back(Position(index, index));
    }
  }
  for (unsigned char index = 1; index <= 7; ++index) {
    if (index != position.col) {
      attackedPositions.push_back(Position(index, 8 - index));
    }
  }
  
  checkAttackedPositions(board, attackedPositions, white);
}

void Test::queenAttackWithBlocking() {
  PRINT_TESTCASE("queenAttackWithBlocking");

  Board board;

  Position position(4, 4);
  board.addPieceToBoard(queen, white, position);
  board.addPieceToBoard(pawn, black, Position(position.col, position.row - 2));
  board.addPieceToBoard(pawn, black, Position(position.col, position.row + 2));
  board.addPieceToBoard(pawn, black, Position(position.row - 2, position.row));
  board.addPieceToBoard(pawn, black, Position(position.row + 2, position.row));

  std::vector<Position> attackedPositions;
  for (unsigned char index = position.col - 2; index <= position.col + 2; ++index) {
    if (index != position.col) {
      attackedPositions.push_back(Position(index, position.row));
    }
    if (index != position.row) {
      attackedPositions.push_back(Position(position.col, index));
    }
  }

  board.addPieceToBoard(pawn, black, Position(position.col - 2, position.row - 2));
  board.addPieceToBoard(pawn, black, Position(position.col - 2, position.row + 2));
  board.addPieceToBoard(pawn, black, Position(position.col + 2, position.row - 2));
  board.addPieceToBoard(pawn, black, Position(position.col + 2, position.row + 2));

  for (unsigned char index = position.col - 2; index <= position.col + 2; ++index) {
    if (index != position.col) {
      attackedPositions.push_back(Position(index, index));
      attackedPositions.push_back(Position(index, 8 - index));
    }
  }
  
  checkAttackedPositions(board, attackedPositions, white);
}

void Test::queenAttackWithTotalBlocking() {
  PRINT_TESTCASE("queenAttackWithTotalBlocking");

  Board board;

  Position position(4, 4);
  board.addPieceToBoard(queen, white, position);

  std::vector<Position> attackedPositions;
  attackedPositions.push_back(Position(position.col, position.row - 1));
  attackedPositions.push_back(Position(position.col, position.row + 1));
  attackedPositions.push_back(Position(position.col - 1, position.row));
  attackedPositions.push_back(Position(position.col + 1, position.row));

  attackedPositions.push_back(Position(position.col - 1, position.row - 1));
  attackedPositions.push_back(Position(position.col - 1, position.row + 1));
  attackedPositions.push_back(Position(position.col + 1, position.row - 1));
  attackedPositions.push_back(Position(position.col + 1, position.row + 1));

  for (unsigned char index = 0; index < attackedPositions.size(); ++index) {
    board.addPieceToBoard(pawn, black, attackedPositions[index]);
  }

  checkAttackedPositions(board, attackedPositions, white);
}

void Test::kingAttack() {
  PRINT_TESTCASE("kingAttack");

  Board board;

  Position position(4, 4);
  board.addPieceToBoard(king, white, position);

  std::vector<Position> attackedPositions;
  attackedPositions.push_back(Position(position.col, position.row - 1));
  attackedPositions.push_back(Position(position.col, position.row + 1));
  attackedPositions.push_back(Position(position.col - 1, position.row));
  attackedPositions.push_back(Position(position.col + 1, position.row));

  attackedPositions.push_back(Position(position.col - 1, position.row - 1));
  attackedPositions.push_back(Position(position.col - 1, position.row + 1));
  attackedPositions.push_back(Position(position.col + 1, position.row - 1));
  attackedPositions.push_back(Position(position.col + 1, position.row + 1));

  for (unsigned char index = 0; index < attackedPositions.size(); ++index) {
    board.addPieceToBoard(pawn, black, attackedPositions[index]);
  }

  checkAttackedPositions(board, attackedPositions, white);
}

void Test::totalAttackAfterBoardReset() {
  PRINT_TESTCASE("totalAttackAfterBoardReset");

  Board board;

  board.reset();

  Position position(1, 3);
  std::vector<Position> attackedPositions;
  // white pawns
  for (position.col = 1; position.col <= 8; ++position.col) {
    attackedPositions.push_back(Position(position.col, position.row));
  }
  // white knights
  attackedPositions.push_back(Position(1, 3));
  attackedPositions.push_back(Position(3, 3));
  attackedPositions.push_back(Position(6, 3));
  attackedPositions.push_back(Position(8, 3));


  checkAttackedPositions(board, attackedPositions, white);

  position.row = 6;
  attackedPositions.clear();
  // black pawns
  for (position.col = 1; position.col <= 8; ++position.col) {
    attackedPositions.push_back(Position(position.col, position.row));
  }
  // black knights
  attackedPositions.push_back(Position(1, 6));
  attackedPositions.push_back(Position(3, 6));
  attackedPositions.push_back(Position(6, 6));
  attackedPositions.push_back(Position(8, 6));

  checkAttackedPositions(board, attackedPositions, black);
}

void Test::checkAttackedPositions(Board& board, std::vector<Position>& attackedPositions, ePieceColor attackColor) {
  Position checkedPos;
  for (checkedPos.row = 1; checkedPos.row <= 8; ++checkedPos.row) {
    for (checkedPos.col = 1; checkedPos.col <= 8; ++checkedPos.col) {
      bool positionShouldBeAttacked = false;
      for (unsigned char attackedIndex = 0; attackedIndex < attackedPositions.size(); ++attackedIndex) {
        Position& attackedPos = attackedPositions[attackedIndex];
        if (attackedPos == checkedPos) {
          positionShouldBeAttacked = true;
        }
        if (positionShouldBeAttacked) {
          break;
        }
      }
      bool isFieldAttacked = board.isFieldAttacked(board.getField(checkedPos), attackColor);
      if (positionShouldBeAttacked) {
        ASSERT_FIELD_ATTACK(isFieldAttacked, checkedPos, positionShouldBeAttacked);
      } else {
        ASSERT_FIELD_ATTACK(!isFieldAttacked, checkedPos, positionShouldBeAttacked);
      }
    }
  }
}
