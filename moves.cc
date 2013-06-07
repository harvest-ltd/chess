#include "moves.hh"

Moves::Moves() {
}

Moves::~Moves() {
  for(std::vector<Move*>::iterator it = moves.begin(); it != moves.end(); ++it) {
    delete(*it);
  }
}

void Moves::addMove(Move* move) {
  moves.push_back(move);
}

int Moves::getMoveCount() {
  return moves.size();
}
