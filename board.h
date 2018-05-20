#ifndef BOARD_H_
#define BOARD_H_

#include "space.h"

typedef struct {

	space boardSpaces[8][8];
	char  turn;				//1 if white turn, 0 if black;
	char  castlingRights;	//KQkq
	char  epSquare;			//en passant square:
	char  halfMoveClock;	// 50 move counter for draws
	char  turnCount;		//Full number of moves in the game
	int   PerftNodeCounter; // used for debugging nodes
	int   PerftCaptureCounter; //used for perft debugging
	int   PerftCastleCounter; //used to figure out # of castling:
	int   PerftEPCapture;		// Used for perft Debugging # of En passants
	int	  PerftPromotionCounter;
	int	  hashtablehitcounter;
	int   hashtablemisscounter;
	int   whiteKingCoordinates[2]; //used for checking when moving other pieces results in check inadvertantly
	int   blackKingCoordinates[2]; //used for checking when moving other pieces results in check inadvertantly for illegal moves.
}Board;



typedef struct {
	//PRECOMPILED MOVES BY TYPE
	char rookMoves[8][8][14]; //8x8 array of 14 long array. (3D array). Exactly 14 destinations exist for each rook.
	char knightMoves[8][8][8]; //Knights can move at max 8 different locations
	char bishopMoves[8][8][13]; //Bishops can move at maximum 8 locations

								//Actual List of active controlled spaces/pieces:
	char blackSpaces[16][2];	//Stores the type and locations for each Move black can make
	char whiteSpaces[16][2];	//Stores the type and locations for each Move white can make (IE NE4 = Knight E4):
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

typedef struct {

	MoveGen MoveTreeNode[MAXDEPTH + 1]; //Array of Moves/Nodes/Leaves Generated by MoveTree function:

}MoveTree;


typedef struct {
	short int pruneBoardVal;
	short int currentBoardVal;
	MoveList pruneMove;
	MoveGen prunePath;
	MoveList currentMove;
	MoveGen currentPath;
	short int tempAlpha;
	short int tempBeta;
	short int alphaVal;
	short int betaVal;
} Prunes;

//Transposition Hash Table;
typedef struct {
	unsigned long long zobrist;
	int depth;
	int flag; //ALPHA PRUNING / BETA PRUNING:
	int eval;
	MoveList move; //BEST MOVE: 
}ht_item;

typedef struct {
	int size;
	int count;
	ht_item** items;
}ht_hash_table;


void initializePositions(Move *move);
void makeBoard(Board *board, Move *move, MoveGen *movegen, MoveGen *movehistory);
void printBoard(Board *board);
void setSpace(Board *board, unsigned int i, unsigned int j);
void resetDebugCounters(Board *board);
void clearMoveTree(MoveTree *movetree);

void clearMoveGen(MoveGen *movegen);
void setBoard(Board *board, Move *move, char command[]); //Sets current boardstate based on the command:
void setPiece(Board *board, char piece, int row, int col);
void setWhiteSpaces(Board *board, int number, int row, int col);
void setColorSpaces(Board *board, Move *move);
//Hash table functions:

static ht_item* ht_new_item(const unsigned long long zobrist, int depth, int flag, int eval, MoveList move);
ht_hash_table* ht_new();
static void ht_del_item(ht_item *i);
void ht_del_hash_table(ht_hash_table* ht);
void setMove(MoveList *dest, MoveList source);

//Hash Table Functions:
int ht_read(ht_hash_table * ht, volatile unsigned long long *zobrist, int depth);
void ht_write(ht_hash_table *ht, volatile unsigned long long *zobrist, int depth, int flag, int eval, MoveList move);
ht_item* get_ht_item(ht_hash_table* ht, volatile unsigned long long *zobrist);
int isInTable(ht_item *item, volatile unsigned long long *zobrist, int depth);
//Hash Table Zobrist Functions:
void init_zobrist();
void set_zobrist_value(Board *board, volatile unsigned long long *zobrist);
void update_zobrist(MoveList move, volatile unsigned long long *zobrist);
void update_zobrist_castling(MoveList move, volatile unsigned long long *zobrist);
void update_zobrist_promotion(MoveList move, volatile unsigned long long *zobrist);

#endif // !
#pragma once