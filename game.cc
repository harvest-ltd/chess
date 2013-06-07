#include "game.hh"

#include "stddef.h"
#include <iostream>

Game::Game() {
  visual = new Visual(board, moves);
}

Game::~Game() {
  delete (visual);
}

void Game::start() {
  board.reset();
  visual->drawBoard();

  Move* move = NULL;
  do {
    if (!readMove(move)) {
      break;
    }
    if (move) {
      if (board.applyMove(move) == eOk) {
        moves.addMove(move);
      }
      visual->drawBoard();
    }
  } while (true);
}

bool Game::readMove(Move*& move) {
  move = NULL;

  unsigned char from[2];
  unsigned char to[2];

  std::cout << "Move from: ";
  std::cin >> from;
  std::cin.clear();
  std::cin.ignore(100, '\n');

  std::cout << "Move to: ";
  std::cin >> to;
  std::cin.clear();
  std::cin.ignore(100, '\n');

  Position fromPos;
  Position toPos;

  if (!getPosFromInput(from, fromPos) || !getPosFromInput(to, toPos)) {
    return false;
  }

  Field* fromField = board.getField(fromPos);
  Field* toField = board.getField(toPos);

  move = new Move(fromField, toField);

  return true;
}

bool Game::getPosFromInput(unsigned char input[2], Position& pos) {
  if (input[0] < 97 || 104 < input[0] || input[1] < 49 || 56 < input[1]) {
    return false;
  }

  pos.col = input[0] - 96;
  pos.row = input[1] - 48;

  return true;
}
