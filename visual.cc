#include "visual.hh"
#include "board.hh"

#include <iostream>
#include <stdio.h>

Visual::Visual(Board& board, Moves& moves) :
  board(board),
  moves(moves)
{
}

Visual::~Visual() {
}

void Visual::drawBoard() {
  char symbol[30];

  std::cout << std::endl;

  Position position;
  for (position.row = 8; position.row >= 1; --position.row) {
    std::cout << (int)position.row << " ";
    for (position.col = 1; position.col <= 8; ++position.col) {
      getFieldSymbol(position, symbol);
      std::cout << " " << symbol;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  std::cout << "   A B C D E F G H" << std::endl;
  std::cout << std::endl;

  std::cout << "move count: " << moves.getMoveCount() << std::endl;

  for (unsigned char pieceIndex = 0; pieceIndex < board.removedPieces.size(); ++pieceIndex) {
    board.removedPieces[pieceIndex]->getSymbol(symbol);
    std::cout << " " << symbol;
  }
  std::cout << std::endl << std::endl;
  
}

void Visual::getFieldSymbol(Position position, char* symbol) {
  Field *field = board.getField(position);

  if (field->isEmpty()) {
    sprintf(symbol, ".");
    return; 
  }
  
  field->getPiece()->getSymbol(symbol);
}
