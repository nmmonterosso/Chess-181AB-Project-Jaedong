#ifndef SPACE_H_
#define SPACE_H_

#define WHITE 0xF
#define BLACK 0x7

#define KING	0
#define QUEEN	1	
#define ROOK	2
#define BISHOP	3
#define KNIGHT	4
#define PAWN	5
#define EMPTY 0xF


typedef struct{
	//type includes: color, and the type of piece: 1 = white 0 = black
	//{000}	== KING
	//{001} == Queen
	//{010} == ROOK
	//{011} == BISHOP
	//{100} == KNIGHT
	//{101} == PAWN
	//{111} == EMPTY (Might be unnecessary)
	char boardposition;		// Space number identifier on the board {6 BITS}
	char isOccupied;		// 1 if occupied, 0 if unoccupied		{1 BIT }
	char pieceType;			// type of piece occupying the space	{4 BITS}
	//TODO CHECK ENUM for string types:	
} space;


char getboardposition(space *board);	//returns boardposition
char getisOccupied(space *board);		//returns 1 if occupied, 0 if not
char getpieceType(space *board);		

#endif //SPACE_H