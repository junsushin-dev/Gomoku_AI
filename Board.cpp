#include "Board.h"
#include "Utility.h"
using namespace std;

// initialize spots on the board to be 0(empty)
Board::Board()
{
	for (int i=0; i<19 ; i++) 
	{
		for (int j = 0; j < 19; j++)
		{
			board[i][j] = 0;
		}
	}
}

bool Board::spot_available(int i, int j)
{
	if (i < 0 || i >18 || j < 0 || j>18)
	{
		return false;
	}
	if (board[i][j] == 0) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool Board::spot_taken(int i, int j)
{
	if (i < 0 || i >18 || j < 0 || j>18)
	{
		return false;
	}
	if (board[i][j] != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// check whether there is a stone in the adjacent 8 areas(including diagonal)
bool Board::check_adj(int a, int b)
{
	int max_distance = 1;
	for (int distance = 1; distance <= max_distance; distance++)
	{
		for (int i = b - distance; i <= b + distance; i++)
		{
			if (spot_taken(a - distance, i))
			{
				return true;
			}
			if (spot_taken(a + distance, i))
			{
				return true;
			}
		}
		for (int j = a - distance + 1; j <= a + distance - 1; j++)
		{
			if (spot_taken(j, b - distance))
			{
				return true;
			}
			if (spot_taken(j, b + distance))
			{
				return true;
			}
		}
	}
	return false;
}

void Board::put_stone(int player, int i, int j)
{
	board[i][j] = player;
	return;
}

void Board::del_stone(int i, int j)
{
	board[i][j] = 0;
	return;
}

// 5 sequential stones
table terminal_state =
{
	{makevector(1,1,1,1,1), make_pair(true, 1)},
	{makevector(-1,-1,-1,-1,-1), make_pair(true, 1)}
};

// Check if 5 sequential stones exist
bool Terminal_check(State* statep)
{	
	int row = statep->lastmove.first;
	int col = statep->lastmove.second;
	//cout << "Terminal Check" << endl;
	return (Terminal_Check_Horizontal(statep->board, row) || Terminal_Check_Vertical(statep->board, col) || Terminal_Check_Diagonal(statep->board, row, col));
}

bool Terminal_Check_Horizontal(Board board, int row)
{
	int result = 0;
	vec tocompare;
	for (int len = 5; len > 4; len--)
	{
		pair<int, int> search_range = Get_Search_Range_Horizontal(board, row);
		int start = search_range.first;
		int move = 0;
		while (start < search_range.second - len + 2)
		{
			tocompare.clear();
			for (int l = 0; l < len; l++)
			{
				tocompare.push_back(board.board[row][start + l]);
			}
			if (terminal_state.count(tocompare) == 0)
			{
				move = 1;
			}
			else
			{
				return true;
			}
			start += move;
		}
	}
	return false;
}

bool Terminal_Check_Vertical(Board board, int col)
{
	int result = 0;
	vec tocompare;
	for (int len = 5; len > 4; len--)
	{
		pair<int, int> search_range = Get_Search_Range_Vertical(board, col);
		int start = search_range.first;
		int move = 0;
		while (start < search_range.second - len + 2)
		{
			tocompare.clear();
			for (int l = 0; l < len; l++)
			{
				tocompare.push_back(board.board[start + l][col]);
			}
			if (terminal_state.count(tocompare) == 0)
			{
				move = 1;
			}
			else
			{
				return true;
			}
			start += move;
		}
	}
	return false;
}

bool Terminal_Check_Diagonal(Board board, int row, int col)
{
	int result = 0;
	vec tocompare;
	if (row + col <= 18)
	{
		int t1 = row + col;
		for (int len = 5; len > 4; len--)
		{
			if (t1 + 1 < len) continue;
			int start = 0;
			int move = 0;
			while (start < (t1 + 1 - len))
			{
				tocompare.clear();
				for (int l = 0; l < len; l++)
				{
					tocompare.push_back(board.board[t1 - start - l][start + l]);
				}
				if (terminal_state.count(tocompare) == 0)
				{
					move = 1;
				}
				else
				{
					return true;
				}
				start += move;
			}
		}
	}
	else
	{
		int t1 = col - (18 - row);
		for (int len = 5; len > 4; len--)
		{
			if (19 - t1 < len) continue;
			int start = 0;
			int move = 0;
			while (start < (20 - t1 - len))
			{
				tocompare.clear();
				for (int l = 0; l < len; l++)
				{
					tocompare.push_back(board.board[18 - start - l][t1 + start + l]);
				}
				if (terminal_state.count(tocompare) == 0)
				{
					move = 1;
				}
				else
				{
					return true;
				}
				start += move;
			}
		}
	}
	if (row <= col)
	{
		int t2 = row + (18 - col);
		for (int len = 5; len > 4; len--)
		{
			if (t2 + 1 < len) continue;
			int start = 0;
			int move = 0;
			while (start < (t2 + 1 - len))
			{
				tocompare.clear();
				for (int l = 0; l < len; l++)
				{
					tocompare.push_back(board.board[t2 - start - l][18 - start - l]);
				}
				if (terminal_state.count(tocompare) == 0)
				{
					move = 1;
				}
				else
				{
					return true;
				}
				start += move;
			}
		}
	}
	else
	{
		int t2 = col + (18 - row);
		for (int len = 5; len > 4; len--)
		{
			if (t2 - 1 < len) continue;
			int start = 0;
			int move = 0;
			while (start < (t2 - len + 2))
			{
				tocompare.clear();
				for (int l = 0; l < len; l++)
				{
					tocompare.push_back(board.board[18 - start - l][t2 - start - l]);
				}
				if (terminal_state.count(tocompare) == 0)
				{
					move = 1;
				}
				else
				{
					return true;
				}
				start += move;
			}
		}
	}
	return false;
}

// queues up possible options for the AI, starting from spots close to the last move
// options have adj stones
queue<pair<int,int>> actions(State *state)
{
	queue<pair<int, int>> result;
	int max_distance = max(max(state->lastmove.first, 18 - state->lastmove.first), max(state->lastmove.second, 18 - state->lastmove.second));
	for (int distance = 1; distance <= max_distance ; distance++)
	{
		for (int i = state->lastmove.second - distance; i <= state->lastmove.second + distance; i++)
		{
			if (state->board.spot_available(state->lastmove.first-distance, i) && state->board.check_adj(state->lastmove.first - distance, i))
			{
				result.push(make_pair(state->lastmove.first - distance, i));
			}
			if ((state->board.spot_available(state->lastmove.first + distance, i)) && state->board.check_adj(state->lastmove.first + distance, i))
			{
				result.push(make_pair(state->lastmove.first + distance, i));
			}
		}
		for (int j = state->lastmove.first - distance + 1; j <= state->lastmove.first + distance - 1; j++)
		{
			if ((state->board.spot_available(j, state->lastmove.second - distance)) && state->board.check_adj(j, state->lastmove.second - distance))
			{
				result.push(make_pair(j, state->lastmove.second - distance));
			}
			if ((state->board.spot_available(j, state->lastmove.second + distance)) && state->board.check_adj(j, state->lastmove.second + distance))
			{
				result.push(make_pair(j, state->lastmove.second + distance));
			}
		}
	}
	return result;
}

// just for checking adj
queue<pair<int, int>> restricted_actions(State* state)
{
		queue<pair<int, int>> result;
	int max_distance = max(max(state->lastmove.first, 18 - state->lastmove.first), max(state->lastmove.second, 18 - state->lastmove.second));
	for (int distance = 1; distance <= max_distance ; distance++)
	{
		for (int i = state->lastmove.second - distance; i <= state->lastmove.second + distance; i++)
		{
			if ((!Check_Forbidden(state, make_pair(state->lastmove.first-distance, i))) && state->board.check_adj(state->lastmove.first - distance, i))
			{
				result.push(make_pair(state->lastmove.first - distance, i));
			}
			if ((!Check_Forbidden(state, make_pair(state->lastmove.first + distance, i))) && state->board.check_adj(state->lastmove.first + distance, i))
			{
				result.push(make_pair(state->lastmove.first + distance, i));
			}
		}
		for (int j = state->lastmove.first - distance + 1; j <= state->lastmove.first + distance - 1; j++)
		{
			if ((!Check_Forbidden(state, make_pair(j, state->lastmove.second - distance))) && state->board.check_adj(j, state->lastmove.second - distance))
			{
				result.push(make_pair(j, state->lastmove.second - distance));
			}
			if ((!Check_Forbidden(state, make_pair(j, state->lastmove.second + distance))) && state->board.check_adj(j, state->lastmove.second + distance))
			{
				result.push(make_pair(j, state->lastmove.second + distance));
			}
		}
	}
	return result;
}

State::State()
{
	player = 1;
	prev_state = nullptr;
	state_value = 0;
	next_states = {};
}

// makes a new state with the move executed, returns the pointer to the new state
State* change_state(State* old_state, pair<int, int> move)
{
	// fetch the previously made state if it exists
	if (old_state->next_states.count(move) != 0)
	{
		//cout << "fetched previous calculated state" << endl;
		return old_state->next_states[move];
	}
	State* new_state = new State;
	new_state->board = old_state->board;
	new_state->board.put_stone(old_state->player, move.first, move.second);
	new_state->player = (old_state->player) * -1;
	new_state->lastmove = move;
	//cout << "Utility Check" << endl;
	new_state->computer = old_state->computer;
	new_state->state_value = (old_state->state_value) + Spot_Utility(*new_state, move, new_state->computer) - Spot_Utility(*old_state, move, old_state->computer);
	new_state->prev_state = old_state;
	old_state->next_states.insert(pair<pair<int, int>, State*>(move, new_state)); //adds the next state to the option map of old state
	return new_state;
}

void print_board(State* state)
{
	if (state->player == 1)
	{
		cout << "당신의 돌은... X" << endl;
	}
	else
	{
		cout << "당신의 돌은... O" << endl;
	}
	cout << endl;
	cout.width(1);
	cout << "";
	for (int i = 0; i < 10; i++)
	{
		cout.width(2);
		cout << i;
	}
	cout.width(1);
	cout << " ";
	for (int i = 10; i < 19; i++)
	{
		cout.width(2);
		cout << i;

	}
	cout << endl;
	for (int i = 0; i < 19; i++)
	{
		cout.width(2);
		cout << i;
		for (int j = 0; j < 19; j++)
		{
			print_stone(state->board.board[i][j]);
		}
		cout << endl;
	}
}

// translates 1, 0, -1 into @, O, - (empty spot)
void print_stone(int input)
{
	if (input == 1)
	{
		//cout.width(2);
		cout<< "●";
		cout.width(2);
	}
	else if (input == -1)
	{
		//cout.width(2);
		cout<< "○";
		cout.width(2);
	}
	else
	{
		cout<< "┼";
		cout.width(3);
	}
	return;
}

 void Recursive_Destoryer(State* statep)
 {
	 while (!statep->next_states.empty())
	 {
		 map<pair<int, int>, State *>::iterator temp = statep->next_states.begin();
		 Recursive_Destoryer(temp->second);
		 statep->next_states.erase(temp);
	 }
	 delete(statep);
	 return;
 }