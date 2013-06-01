#include "board.hh"
#include "position.hh"
#include "piece.hh"

#include <vector>

class Test {
public:
  Test();
  virtual ~Test();

  void run();

private:
  // board
  void resetBoard();
  void cleanBoard();

	// piece
  void addPieceToBoard();
  void movePieceToEmptyField();
  void movePieceToNotEmptyField();
  void movePieceFromEmptyField();
  void pieceVectors();

  // move
	void pawnShortOpening();
	void pawnLongOpening();
  void pawnLongMoveAfterOpening();
  void pawnStep();
  void pawnInvalidAttackMove();
  void pawnKillsLongOpeningPawn();

  // attack
  void whitePawnAttack();
  void blackPawnAttack();
  void pawnAttackOnTheEdge();

  void rookAttackOnEmptyBoard();
  void rookAttackWithBlocking();
  void rookAttackWithTotalBlocking();

	void knightAttack();

	void bishopAttackOnEmptyBoard();
  void bishopAttackWithBlocking();
  void bishopAttackWithTotalBlocking();

  void queenAttackOnEmptyBoard();
  void queenAttackWithBlocking();
  void queenAttackWithTotalBlocking();

  void kingAttack();

  void boardAttackAfterBoardReset();

  void checkAttackedPositions(Board& board, std::vector<Position>& attackedPositions, ePieceColor attackColor);

};
