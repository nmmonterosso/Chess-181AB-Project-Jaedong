#ifndef BOARD_H_
#define BOARD_H_

#include "space.h"


typedef struct {

	space boardSpaces[8][8];
	char  turn; //1 if white turn, 0 if black;

}Board;



typedef struct {

	char rookMoves[8][8][14]; //8x8 array of 14 long array. (3D array). Exactly 14 destinations exist for each rook.
	char knightMoves[8][8][8]; //Knights can move at max 8 different locations
	char bishopMoves[8][8][13]; //Bishops can move at maximum 8 locations
	char blackSpaces[16][2];	//Stores the type and locations for each Move white can make
	char whiteSpaces[16][2];	//Stores the type and locations for each Move Black can make (IE NE4 = Knight E4):
								//TODO Put Pawn Moves as well:

}Move;

typedef struct {
	//ALL PARAMETERS INITIALIZED TO -1:
	char piece;
	char startLocation;
	char endLocation;
	char capturedPiece;

}MoveList;

typedef struct {

	MoveList Moves[100];
	int		 count; //used to index the moves array between function calls

}MoveGen;



void initializePositions(Move *move);
void makeBoard(Board *board, Move *move, MoveGen *movegen);
void printBoard(Board *board);
void setSpace(Board *board, unsigned int i, unsigned int j);

#endif // !
#pragma once

