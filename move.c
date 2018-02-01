#include "stdafx.h"
#include "board.h"
#include "move.h"

//Summary: Calculates each possible move a bishop can move to when given a starting space
//Assumes Board is empty so this result must check to see if spaces in the path are occupied
//to determine captures or movement blocking.
void setBishopMoves(Board * board, int i, int j, Move * move)
{
	int x, y, k;

	for (x = 0; x < 13; x++) 
		move->bishopMoves[i][j][x] = -1;
	//NOTE: We can break this function up into smaller easier to read subroutines:
	k = 0;
	y = i;
	x = j;
	//SetTopRightDirection:
	while((x + 1 < 8) && (y + 1 < 8)) {
		x++; y++;		
		move->bishopMoves[i][j][k] = board->boardSpaces[y][x].boardposition;		
		k++;
	}//endWhile	
	y = i;
	x = j;
	//SetBotRightDirection:
	while ((x + 1 < 8) && (y - 1 >= 0)) {
		x++; y--;
		move->bishopMoves[i][j][k] = board->boardSpaces[y][x].boardposition;
		k++;
	}//endWhileBotRight		
	y = i;
	x = j;
	//SetBotleftDirection:
	while ((x - 1 >= 0) && (y - 1 >= 0)) {
		x--; y--;
		move->bishopMoves[i][j][k] = board->boardSpaces[y][x].boardposition;
		k++;
	}//endWhileBotRight
	
	y = i;
	x = j;
	//SetTopLeftDirection:
	while ((x - 1 >= 0) && (y + 1 < 8)) {
		x--; y++;
		move->bishopMoves[i][j][k] = board->boardSpaces[y][x].boardposition;
		k++;
	}//endWhileBotRight
}//setBishopMoves


//Summary: Calculates each possible movement a knight can move given a starting space
//Assumes Board is empty so this result must check to see if the space is occupied to make captures
//and to see if the occupied piece is friendly or hostile to determine the actual moveset:
//Checks moves counterclockwise:
void setKnightMoves(Board *board, int i, int j, Move *move) {
	int x, k = 0; //initializing variables
	//Initializes all values in the moves to -1 by default (-1 signifies end of moveset)
	for (x = 0; x < 8; x++)
		move->knightMoves[i][j][x] = -1;
		
	for (x = 0; x < 8; x++) {
		switch (x) {
		case 0: if ((i + 2 < 8) && (j + 1 < 8)) {//Check UP -> Right Position:
					move->knightMoves[i][j][k] = board->boardSpaces[i + 2][j + 1].boardposition;
					k++;
				}//endif
				break;

		case 1:	if ((i + 1 < 8) && (j + 2 < 8)) {//Check Right -> UP Position:
					move->knightMoves[i][j][k] = board->boardSpaces[i + 1][j + 2].boardposition;
					k++;
				}//endif			
				break;

		case 2:	if ((i - 1 >= 0) && (j + 2 < 8)) {//Check Right -> DOWN Position:
					move->knightMoves[i][j][k] = board->boardSpaces[i - 1][j + 2].boardposition;
					k++;
				}//endif			
				break;

		case 3:	if ((i - 2 >= 0) && (j + 1 < 8)) {//Check DOWN -> RIGHT Position:
					move->knightMoves[i][j][k] = board->boardSpaces[i - 2][j + 1].boardposition;
					k++;
				}//endif			
				break;

		case 4:	if ((i - 2 >= 0) && (j - 1 >= 0)) {//Check DOWN -> LEFT Position:
					move->knightMoves[i][j][k] = board->boardSpaces[i - 2][j - 1].boardposition;
					k++;
				}//endif			
				break;

		case 5:	if ((i - 1 >= 0) && (j - 2 >= 0)) {//Check LEFT -> DOWN Position:
				move->knightMoves[i][j][k] = board->boardSpaces[i - 1][j - 2].boardposition;
				k++;
				}//endif			
				break;
				
		case 6:	if ((i + 1 < 8) && (j - 2 >= 0)) {//Check LEFT -> UP Position:
				move->knightMoves[i][j][k] = board->boardSpaces[i + 1][j - 2].boardposition;
				k++;
				}//endif			
				break;
				
		case 7:	if ((i + 2 < 8) && (j - 1 >= 0)) {//Check UP -> LEFT Position:
				move->knightMoves[i][j][k] = board->boardSpaces[i + 2][j - 1].boardposition;
				k++;
				}//endif			
				break;

		default:break;
		}//endSwitch
	}//endFor
}//setKnightMoves

//Summary: Calculates each possible movement a rook can move given a starting space.
//Stores the destination board positions as a result. 
//Assumes the Board is empty so this result must be compared to the current boardstate
//before making decisions.
void setRookMoves(Board *board, int i, int j, Move *move)
{
	int x, y, k;			
	for (k = 0; k < 14; k++) {
		move->rookMoves[i][j][k] = 0; //Initialize array to 0 
	}//End FOR initialization
	k = 0;
	//Calculating horizontal +X direction (RIGHT)
	for(x = j + 1; x < 8; x++) {
		move->rookMoves[i][j][k] = board->boardSpaces[i][x].boardposition; //Sets the boardPosition for the valid move:
		k++;
	}//end FOR +X RIGHT	
	 //Calculating horizontal -X direction LEFT	
	for (x = j - 1; x >= 0; x--) {
		move->rookMoves[i][j][k] = board->boardSpaces[i][x].boardposition; //Sets the boardPosition for the valid move:
		k++;
	}//end FOR -X LEFT
	 //Calculating vertical +y direction: UP	
	for (y = i + 1; y < 8; y++) {
		move->rookMoves[i][j][k] = board->boardSpaces[y][j].boardposition;
		k++;
	}//end FOR +Y

	 //Calculating vertical -y direction: Down
	for (y = i - 1; y >= 0; y--) {
		move->rookMoves[i][j][k] = board->boardSpaces[y][j].boardposition;
		k++;
	}//end FOR -Y
}//verticalHorizontal_move


//Summary: Passes the board and arguments to preconfigure the board movement.
//All movement in this board is assumed to be on an empty board and must be compared
//to the present board state to determine obstacle collisions.
void setMoves(Board *board, Move *move) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			//printf("boardInt = [%d]", boardInt);			
			setRookMoves(board, i, j, move);
			setKnightMoves(board, i, j, move);
			setBishopMoves(board, i, j, move);
			//TODO SET PAWN MOVES?
			//SET QUEEN MOVES
		}//end for j
	}//end for i
}//setMoves