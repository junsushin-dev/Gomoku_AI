#pragma once

#ifndef _CLASS_HEADER_H_
#define _CLASS_HEADER_H_
#include <stdio.h>
#include <string>
#include <iostream>
#include <map>
#include <queue>
#include "stdlib.h"
using namespace std;

typedef queue<pair<int, int>> action_queue;

class Board
{
public:
	Board();
	int board[19][19];
	bool spot_available(int i, int j);
	bool spot_taken(int i, int j);
	bool check_adj(int a, int b);
	void put_stone(int player, int i, int j);
	void del_stone(int i, int j);
};

class  State
{
public: 
	State();
	int player; // 1=black, -1=white //  the next one to play
	int computer; // 1=first, 2=second // initial turn of AI
	Board board;
	pair<int, int> lastmove;
	State* prev_state;
	int state_value;
	map<pair<int, int>, State *> next_states;
};

void print_board(State* state);
State* change_state(State* state, pair<int, int>);
void print_stone(int input);
queue<pair<int, int>> actions(State *state);
queue<pair<int, int>> restricted_actions(State* state);

bool Terminal_check(State* statep);
bool Terminal_Check_Horizontal(Board board, int row);
bool Terminal_Check_Vertical(Board board, int col);
bool Terminal_Check_Diagonal(Board board, int row, int col);

void Recursive_Destoryer(State* statep);

#endif