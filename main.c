﻿// Chess2.cpp : Defines the entry point for the console application.
//Nicholas Monterosso
//Main for Chess project

#include "stdafx.h" //comment out this line or add your own #include stdio, etc.
#include <stdio.h>
#include "piece.h"
#include "space.h"
#include "board.h"
#include "move.h"
#include "movegen.h"
//void makeBoard(space *board[8][8]);
//MACROS IN SPACE.H



int main()
{
	//Initialize board		
	Board *board = malloc(sizeof(Board));
	Move  *move = malloc(sizeof(Move));
	MoveGen *movegen = malloc(sizeof(MoveGen));
	MoveGen *movehistory = malloc(sizeof(MoveGen));

	makeBoard(board, move, movegen, movehistory);	// Initializes board state and pieces. Precompiles all moves:
	MoveGenFunction(board, move, movegen);
	printBoard(board);  //Prints Board into Console:
	printf("Hello World!\n");
	makeMove(board, movegen->Moves[5], movehistory);
	printBoard(board); //Prints Second board:
	//REALLOCATE
	//MoveGen *movegen = realloc(movegen, sizeof(MoveGen));
	movegen->count = 0;// pseudo reset
	//Calculate Black Moves:
	MoveGenFunction(board, move, movegen);	
	printBoard(board);
	
	while (1) {		
		//MoveGeneration Function:
		//BoardEvaluation Function:
	}
	return 0;
}




