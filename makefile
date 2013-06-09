CC = g++
PRG = chess
OBJS = chess.o board.o field.o piece.o pawn.o rook.o bishop.o knight.o queen.o king.o visual.o test.o move.o moves.o game.o
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

$(PRG): $(OBJS) 
	$(CC) $(LFLAGS) $(OBJS) -o $(PRG) 

chess.o: chess.cc board.hh test.hh
	$(CC) $(CFLAGS) chess.cc

board.o: board.cc board.hh field.hh piece.hh pawn.hh rook.hh bishop.hh king.hh queen.hh king.hh debug.hh
	$(CC) $(CFLAGS) board.cc

field.o: field.cc field.hh
	$(CC) $(CFLAGS) field.cc

piece.o: piece.cc piece.hh
	$(CC) $(CFLAGS) piece.cc

pawn.o: pawn.cc pawn.hh board.hh piece.hh
	$(CC) $(CFLAGS) pawn.cc
	
rook.o: rook.cc rook.hh board.hh piece.hh
	$(CC) $(CFLAGS) rook.cc

bishop.o: bishop.cc bishop.hh board.hh piece.hh
	$(CC) $(CFLAGS) bishop.cc

knight.o: knight.cc knight.hh board.hh piece.hh
	$(CC) $(CFLAGS) knight.cc

queen.o: queen.cc queen.hh board.hh piece.hh
	$(CC) $(CFLAGS) queen.cc

king.o: king.cc king.hh board.hh piece.hh
	$(CC) $(CFLAGS) king.cc

visual.o: visual.cc visual.hh board.hh
	$(CC) $(CFLAGS) visual.cc

move.o: move.cc move.hh field.hh
	$(CC) $(CFLAGS) move.cc

moves.o: moves.cc moves.hh move.hh
	$(CC) $(CFLAGS) moves.cc

game.o: game.cc game.hh board.hh moves.hh visual.hh
	$(CC) $(CFLAGS) game.cc

test.o: test.cc test.hh board.hh pawn.hh rook.hh bishop.hh king.hh queen.hh king.hh
	$(CC) $(CFLAGS) test.cc

clean:
	\rm *.o *~ $(PRG)
