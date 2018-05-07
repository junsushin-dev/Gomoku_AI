#include "Utility.h"

pair<int, int> makepair(int value, int nextsearchstart) {
	return pair<int, int>(value, nextsearchstart);
}

vector<int> makevector(int a, int b, int c, int d, int e, int f) {
	vector<int> result;
	result.push_back(a);
	result.push_back(b);
	result.push_back(c);
	result.push_back(d);
	result.push_back(e);
	result.push_back(f);
	return result;
}

vector<int> makevector(int a, int b, int c, int d, int e) {
	vector<int> result;
	result.push_back(a);
	result.push_back(b);
	result.push_back(c);
	result.push_back(d);
	result.push_back(e);
	return result;
}

vector<int> makevector(int a, int b, int c, int d) {
	vector<int> result;
	result.push_back(a);
	result.push_back(b);
	result.push_back(c);
	result.push_back(d);
	return result;
}

// vector form, <num_type of stones, next search starting point>
table symbols_6_firstplayer =
{
	{ makevector(0,1,1,1,1,0), makepair(1000, 5)},
	{ makevector(-1,1,1,1,1,0), makepair(90, 5)},
	{ makevector(0,1,1,1,1,-1), makepair(90, 5)},
	{ makevector(0,1,1,0,1,0), makepair(90, 3) },
	{ makevector(0,1,0,1,1,0), makepair(90, 5) },
{ makevector(0,-1,-1,-1,-1,0), makepair(-1100, 5) },
{ makevector(1,-1,-1,-1,-1,0), makepair(-110, 5) },
{ makevector(0,-1,-1,-1,-1,1), makepair(-110, 5) },
{ makevector(0,-1,-1,0,-1,0), makepair(-90,3) },
{ makevector(0,-1,0,-1,-1,0), makepair(-90,5) }
};

table symbols_5_firstplayer =
{
	{ makevector(1,1,1,1,1), makepair(10000, 4) },
	{ makevector(-1,1,1,1,0), makepair(10, 4) },
	{ makevector(0,1,1,1,-1), makepair(10, 3) },
	{ makevector(0,1,1,1,0), makepair(100, 4) },
	{ makevector(0,1,0,1,0), makepair(10, 2) },
{ makevector(-1,-1,-1,-1,-1), makepair(-11000, 4) },
{ makevector(1,-1,-1,-1,0), makepair(-10, 4) },
{ makevector(0,-1,-1,-1,1), makepair(-10, 3) },
{ makevector(0,-1,-1,-1,0), makepair(-110, 4) },
{ makevector(0,-1,0,-1,0), makepair(-10, 2) }
};

table symbols_4_firstplayer =
{
	{ makevector(0,1,1,0), makepair(10, 3) },
	{ makevector(0,-1,-1,0), makepair(-10, 3) }
};

//point tables for AI playing first
map<int, table> symbols_firstplayer = 
{
	{6, symbols_6_firstplayer },
	{5, symbols_5_firstplayer },
	{4, symbols_4_firstplayer }
};

// vector form, <num_type of stones, next search starting point>
table symbols_6_secondplayer =
{
	{ makevector(0,1,1,1,1,0), makepair(1200, 5) },
{ makevector(-1,1,1,1,1,0), makepair(120, 5) },
{ makevector(0,1,1,1,1,-1), makepair(120, 5) },
{ makevector(0,1,1,0,1,0), makepair(95, 3) },
{ makevector(0,1,0,1,1,0), makepair(95, 5) },
{ makevector(0,-1,-1,-1,-1,0), makepair(-1000, 5) },
{ makevector(1,-1,-1,-1,-1,0), makepair(-100, 5) },
{ makevector(0,-1,-1,-1,-1,1), makepair(-100, 5) },
{ makevector(0,-1,-1,0,-1,0), makepair(-90,3) },
{ makevector(0,-1,0,-1,-1,0), makepair(-90,5) }
};

table symbols_5_secondplayer =
{
	{ makevector(1,1,1,1,1), makepair(12000, 4) },
{ makevector(-1,1,1,1,0), makepair(10, 4) },
{ makevector(0,1,1,1,-1), makepair(10, 3) },
{ makevector(0,1,1,1,0), makepair(120, 4) },
{ makevector(0,1,0,1,0), makepair(10, 2) },
{ makevector(-1,-1,-1,-1,-1), makepair(-10000, 4) },
{ makevector(1,-1,-1,-1,0), makepair(-10, 4) },
{ makevector(0,-1,-1,-1,1), makepair(-10, 3) },
{ makevector(0,-1,-1,-1,0), makepair(-100, 4) },
{ makevector(0,-1,0,-1,0), makepair(-10, 2) }
};

table symbols_4_secondplayer =
{
	{ makevector(0,1,1,0), makepair(10, 3) },
{ makevector(0,-1,-1,0), makepair(-10, 3) }
};

//point tables for AI playing second
map<int, table> symbols_secondplayer = 
{
	{ 6, symbols_6_secondplayer },
{ 5, symbols_5_secondplayer },
{ 4, symbols_4_secondplayer }
};

//determines point tables for the AI to use throughout the game
map<int, table>* symbols_select(int player)
{
	map<int, table>* s1 = &symbols_firstplayer;
	map<int, table>* s2 = &symbols_secondplayer;
	if (player == 1)
	{
		//cout << "using table 1..." << endl;
		return s1;
	}
	else if (player==2)
	{
		//cout << "using table 2..." << endl;
		return s2;
	} 
}

// calculates the utility_sum of 4 lines the spot is included in
int Spot_Utility(State state, pair<int, int> spot, int computer) 
{
	int result = 0;
	int row_target = spot.first;
	int col_target = spot.second;
	result += Single_Check_Horizontal(state.board, row_target, computer);
	result += Single_Check_Vertical(state.board, col_target, computer);
	result += Single_Check_Diagonal(state.board, row_target, col_target, computer);
	return result;
}

// vector form, <num_type of stones, next search starting point>
table forbidden_symbols_5 = 
{
	{makevector(0,1,1,1,0), make_pair(3, 3) },
	{makevector(1,1,1,0,1), make_pair(4, 3) },
	{makevector(1,0,1,1,1), make_pair(4, 2) },
	{makevector(1,1,0,1,1), make_pair(4, 3) },
};

table forbidden_symbols_6 =
{
	{ makevector(0,1,1,0,1,0), make_pair(3 ,5) },
	{ makevector(0,1,0,1,1,0), make_pair(3, 5) },
	{ makevector(0,1,1,1,1,0), make_pair(4, 5) },
	{ makevector(-1,1,1,1,1,0), make_pair(4, 5) },
	{ makevector(0,1,1,1,1,-1), make_pair(4, 5) },
	{ makevector(1,1,1,1,1,1), make_pair(6, 6) }
};

// for evaluating the forbidden moves of first player 
map<int, table> forbidden_symbols=
{
	{5, forbidden_symbols_5},
	{6, forbidden_symbols_6}
};

// checks the lines the move is included in, counting number types 3 4 6
// if the number of 3 or 4 increments by >=2 or there is a 6 pattern the move is forbidden for the first player
bool Check_Forbidden(State* state, pair<int, int> move)
{
	if (state->player == -1)
	{
		return false;
	}
	if (!state->board.spot_available(move.first, move.second))
	{
		return true;
	}
	int old_num_3, old_num_4, new_num_3, new_num_4, num_6;
	tuple<int, int, int> old_tuple = Check_346_Spot(state->board, move.first, move.second);
	old_num_3 = get<0>(old_tuple);
	old_num_4 = get<1>(old_tuple);
	state->board.put_stone(1, move.first, move.second);
	tuple<int, int, int> new_tuple = Check_346_Spot(state->board, move.first, move.second);
	new_num_3 = get<0>(new_tuple);
	new_num_4 = get<1>(new_tuple);
	num_6 = get<2>(new_tuple);
	state->board.del_stone(move.first, move.second);
	if (new_num_3 - old_num_3 > 1 || new_num_4 - old_num_4 > 1  || num_6 > 0)
	{
		/* for test log output
		cout << "old_num_3: " << old_num_3 << endl;
		cout << "old_num_4: " << old_num_4 << endl;
		cout << "new_num_3: " << new_num_3 << endl;
		cout << "new_num_4: " << new_num_4 << endl;
		cout << "num_6: " << num_6 << endl;
		*/
		return true;
	}
	else
	{
		return false;
	}
}

tuple<int, int, int> Check_346_Spot(Board board, int row, int col)
{
	int num_3 = 0;
	int num_4 = 0;
	int num_6 = 0;
	//cout << "Checking 346" << endl;
	tuple<int, int, int> temp1 = Check_346_Horizontal(board, row);
	tuple<int, int, int> temp2 = Check_346_Vertical(board, col);
	tuple<int, int, int> temp3 = Check_346_Diagonal(board, row, col);
	num_3 += get<0>(temp1);
	num_3 += get<0>(temp2);
	num_3 += get<0>(temp3);
	num_4 += get<1>(temp1);
	num_4 += get<1>(temp2);
	num_4 += get<1>(temp3);
	num_6 += get<2>(temp1);
	num_6 += get<2>(temp2);
	num_6 += get<2>(temp3);
	return make_tuple(num_3, num_4, num_6);
}

tuple<int, int, int> Check_346_Horizontal(Board board, int row)
{
	int num_3 = 0;
	int num_4 = 0;
	int num_6 = 0;
	int num_type;
	vec tocompare;
	pair<int, int> search_range = Get_Search_Range_Horizontal(board, row);
	int start = search_range.first;
	for (int len = 6; len > 4; len--)
	{
		int move = 0;
		while (start < search_range.second - len + 2)
		{
			tocompare.clear();
			for (int l = 0; l < len; l++)
			{
				tocompare.push_back(board.board[row][start + l]);
			}
			if (forbidden_symbols[len].count(tocompare) == 0)
			{
				move = 1;
			}
			else
			{
				num_type = forbidden_symbols[len][tocompare].first;
				if (num_type == 3) { num_3++; }
				else if (num_type == 4) { num_4++; }
				else if (num_type == 6) { num_6++; }
				move = forbidden_symbols[len][tocompare].second;
			}
			start += move;
		}
	}
	/* for test log output
	cout << "H_num_3: " << num_3 << endl;
	cout << "H_num_4: " << num_4 << endl;
	cout << "H_num_6: " << num_6 << endl;
	*/
	return make_tuple(num_3, num_4, num_6);
}

tuple<int, int, int> Check_346_Vertical(Board board, int col)
{
	int num_3 = 0;
	int num_4 = 0;
	int num_6 = 0;
	int num_type;
	vec tocompare;
	pair<int, int> search_range = Get_Search_Range_Vertical(board, col);
	int start = search_range.first;
	for (int len = 6; len > 4; len--)
	{
		int move = 0;
		while (start < search_range.second - len + 2)
		{
			tocompare.clear();
			for (int l = 0; l < len; l++)
			{
				tocompare.push_back(board.board[start + l][col]);
			}
			if (forbidden_symbols[len].count(tocompare) == 0)
			{
				move = 1;
			}
			else
			{
				num_type = forbidden_symbols[len][tocompare].first;
				if (num_type == 3) { num_3++; }
				else if (num_type == 4) { num_4++; }
				else if (num_type == 6) { num_6++; }
				move = forbidden_symbols[len][tocompare].second;
			}
			start += move;
		}
	}
	/* for test log output
	cout << "V_num_3: " << num_3 << endl;
	cout << "V_num_4: " << num_4 << endl;
	cout << "V_num_6: " << num_6 << endl;
	*/
	return make_tuple(num_3, num_4, num_6);
}

tuple<int, int, int> Check_346_Diagonal(Board board, int row, int col)
{
	int num_3 = 0;
	int num_4 = 0;
	int num_6 = 0;
	int num_type;
	vec tocompare;
	if (row + col <= 18)
	{
		int t1 = row + col;
		for (int len = 6; len > 4; len--)
		{
			if (t1 + 1 < len) continue;
			pair<int, int> search_range = Get_Search_Range_UpRightDiagonal(board, row, col);
			int start = search_range.first;
			int move = 0;
			while (start < search_range.second - len + 2)
			{
				tocompare.clear();
				for (int l = 0; l < len; l++)
				{
					tocompare.push_back(board.board[t1 - start - l][start + l]);
					//cout << "[" << t1 - start - l << ", " << start + l << "]";
				}
				//cout << "end of vector" << endl;
				if (forbidden_symbols[len].count(tocompare) == 0)
				{
					move = 1;
				}
				else
				{
					num_type = forbidden_symbols[len][tocompare].first;
					if (num_type == 3) { num_3++; }
					else if (num_type == 4) { num_4++; }
					else if (num_type == 6) { num_6++; }
					move = forbidden_symbols[len][tocompare].second;
				}
				start += move;
			}
		}
	}
	else
	{
		int t1 = col - (18 - row);
		for (int len = 6; len > 4; len--)
		{
			if (19 - t1 < len) continue;
			pair<int, int> search_range = Get_Search_Range_UpRightDiagonal(board, row, col);
			int start = search_range.first;
			int move = 0;
			while (start < search_range.second - len + 2)
			{
				tocompare.clear();
				for (int l = 0; l < len; l++)
				{
					tocompare.push_back(board.board[18 - start - l][t1 + start + l]);
					//cout << "[" << 18 - start - l << ", " << t1 + start + l << "]";
				}
				//cout << "end of vector" << endl;
				if (forbidden_symbols[len].count(tocompare) == 0)
				{
					move = 1;
				}
				else
				{
					num_type = forbidden_symbols[len][tocompare].first;
					if (num_type == 3) num_3++;
					else if (num_type == 4) num_4++;
					else if (num_type == 6) num_6++;
					move = forbidden_symbols[len][tocompare].second;
				}
				start += move;
			}
		}
	}
	if (row <= col)
	{
		int t2 = row + (18 - col);
		for (int len = 6; len > 4; len--)
		{
			if (t2 + 1 < len) continue;
			pair<int, int> search_range = Get_Search_Range_UpLeftDiagonal(board, row, col);
			int start = search_range.first;
			int move = 0;
			while (start < search_range.second - len + 2)
			{
				tocompare.clear();
				for (int l = 0; l < len; l++)
				{
					tocompare.push_back(board.board[t2 - start - l][18 - start - l]);
					//cout << "[" << t2 - start - l << ", " << 18 - start - l << "]";
				}
				//cout << "end of vector" << endl;
				if (forbidden_symbols[len].count(tocompare) == 0)
				{
					move = 1;
				}
				else
				{
					num_type = forbidden_symbols[len][tocompare].first;
					if (num_type == 3) num_3++;
					else if (num_type == 4) num_4++;
					else if (num_type == 6) num_6++;
					move = forbidden_symbols[len][tocompare].second;
				}
				start += move;
			}
		}
	}
	else
	{
		int t2 = col + (18 - row);
		for (int len = 6; len > 4; len--)
		{
			if (t2 - 1 < len) continue;
			pair<int, int> search_range = Get_Search_Range_UpLeftDiagonal(board, row, col);
			int start = search_range.first;
			int move = 0;
			while (start < search_range.second - len + 2)
			{
				tocompare.clear();
				for (int l = 0; l < len; l++)
				{
					tocompare.push_back(board.board[18 - start - l][t2 - start - l]);
					//cout << "[" << 18 - start - l << ", " <<  t2 - start - l << "]";
				}
				//cout << "end of vector" << endl;
				if (forbidden_symbols[len].count(tocompare) == 0)
				{
					move = 1;
				}
				else
				{
					num_type = forbidden_symbols[len][tocompare].first;
					if (num_type == 3) num_3++;
					else if (num_type == 4) num_4++;
					else if (num_type == 6) num_6++;
					move = forbidden_symbols[len][tocompare].second;
				}
				start += move;
			}
		}
	}
	/* for test log output
	cout << "D_num_3: " << num_3 << endl;
	cout << "D_num_4: " << num_4 << endl;
	cout << "D_num_6: " << num_6 << endl;
	*/
	return make_tuple(num_3, num_4, num_6);
}

// gets value for each line including the move
int Single_Check_Horizontal(Board board, int row, int computer)
{
	int result = 0;
	vec tocompare;
	map<int, table>* symbols = nullptr;
	symbols = symbols_select(computer);
	for (int len = 6; len > 3; len--)
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
			if ((*symbols)[len].count(tocompare) == 0)
			{
				move = 1;
			}
			else
			{
				result += (*symbols)[len][tocompare].first;
				move = (*symbols)[len][tocompare].second;
			}
			start += move;
		}
	}
	return result;
}

int Single_Check_Vertical(Board board, int col, int computer)
{
	int result = 0;
	vec tocompare;
	map<int, table>* symbols = nullptr;
	symbols = symbols_select(computer);
	for (int len = 6; len > 3; len--)
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
				if ((*symbols)[len].count(tocompare) == 0)
				{
					move = 1;
				}
				else
				{
					result += (*symbols)[len][tocompare].first;
					move = (*symbols)[len][tocompare].second;
				}
				start += move;
			}
		}
	return result;
}

int Single_Check_Diagonal(Board board, int row, int col, int computer)
{
	int result = 0;
	vec tocompare;
	map<int, table>* symbols = nullptr;
	symbols = symbols_select(computer);
	if (row + col <= 18)
	{
		int t1 = row + col;
		for (int len = 6; len > 3; len--)
		{
			if (t1 + 1 < len) continue;
			pair<int, int> search_range = Get_Search_Range_UpRightDiagonal(board, row, col);
			int start = search_range.first;
			int move = 0;
			while (start < search_range.second - len + 2)
			{
				tocompare.clear();
				for (int l = 0; l < len; l++)
				{
					tocompare.push_back(board.board[t1 - start - l][start + l]);
				}
				if ((*symbols)[len].count(tocompare) == 0)
				{
					move = 1;
				}
				else
				{
					result += (*symbols)[len][tocompare].first;
					move = (*symbols)[len][tocompare].second;
				}
				start += move;
			}
		}
	}
	else
	{
		int t1 = col - (18 - row);
		for (int len = 6; len > 3; len--)
		{
			if (19 - t1 < len) continue;
			pair<int, int> search_range = Get_Search_Range_UpRightDiagonal(board, row, col);
			int start = search_range.first;
			int move = 0;
			while (start < search_range.second - len + 2)
			{
				tocompare.clear();
				for (int l = 0; l < len; l++)
				{
					tocompare.push_back(board.board[18 - start - l][t1 + start + l]);
				}
				if ((*symbols)[len].count(tocompare) == 0)
				{
					move = 1;
				}
				else
				{
					result += (*symbols)[len][tocompare].first;
					move = (*symbols)[len][tocompare].second;
				}
				start += move;
			}
		}
	}
	if (row <= col)
	{
		int t2 = row + (18 - col);
		for (int len = 6; len > 3; len--)
		{
			if (t2 + 1 < len) continue;
			pair<int, int> search_range = Get_Search_Range_UpLeftDiagonal(board, row, col);
			int start = search_range.first;
			int move = 0;
			while (start < search_range.second - len + 2)
			{
				tocompare.clear();
				for (int l = 0; l < len; l++)
				{
					tocompare.push_back(board.board[t2 - start - l][18 - start - l]);
				}
				if ((*symbols)[len].count(tocompare) == 0)
				{
					move = 1;
				}
				else
				{
					result += (*symbols)[len][tocompare].first;
					move = (*symbols)[len][tocompare].second;
				}
				start += move;
			}
		}
	}
	else
	{
		int t2 = col + (18 - row);
		for (int len = 6; len > 3; len--)
		{
			if (t2 - 1 < len) continue;
			pair<int, int> search_range = Get_Search_Range_UpLeftDiagonal(board,row,  col);
			int start = search_range.first;
			int move = 0;
			while (start < search_range.second - len + 2)
			{
				tocompare.clear();
				for (int l = 0; l < len; l++)
				{
					tocompare.push_back(board.board[18 - start - l][t2 - start - l]);
				}
				if ((*symbols)[len].count(tocompare) == 0)
				{
					move = 1;
				}
				else
				{
					result += (*symbols)[len][tocompare].first;
					move = (*symbols)[len][tocompare].second;
				}
				start += move;
			}
		}
	}
	return result;
}

// shortens the search range by removing the empty area towards the wall
// sequentially checks for zero, returns the points where !zero to be min_range and max_range
pair<int, int> Get_Search_Range_Horizontal(Board board, int row) // Returns search range for horizontal line
{
	int min_range = 19;
	int max_range = -1;
	for (int col = 0; col < 19; col++)
	{
		if (board.board[row][col] != 0)
		{
			min_range = col - 1;
			for (int col = 18; col >= 0; col--)
			{
				if (board.board[row][col] != 0)
				{
					max_range = col + 1;
					break;
				}
			}
			break;
		}
	}
	//cout << "returned Hsearch range: " << min_range << " - " << max_range << endl;
	return make_pair(min_range, max_range);
}

pair<int, int> Get_Search_Range_Vertical(Board board, int col)
{
	int min_range = 19;
	int max_range = -1;
	for (int row = 0; row < 19; row++)
	{
		if (board.board[row][col] != 0)
		{
			min_range = row - 1;
			for (int row = 18; row >= 0; row--)
			{
				if (board.board[row][col] != 0)
				{
					max_range = row + 1;
					break;
				}
			}
			break;
		}
	}
	//cout << "returned Vsearch range: " << min_range << " - " << max_range << endl;
	return make_pair(min_range, max_range);
}

pair<int, int> Get_Search_Range_UpRightDiagonal(Board board, int row, int col)
{
	int max_range = -1;
	int min_range = 19;
	if (row + col <= 18)
	{
		int t1 = row + col;
		for (int l = 0; l < t1 + 1; l++)
		{
			if (board.board[t1 - l][l] != 0)
			{
				if (l == 0) min_range = 0;
				else min_range = l - 1;
				for (int l = t1; l >= 0; l--)
				{
					if (board.board[t1 - l][l] != 0)
					{
						if (l == t1) max_range = t1;
						else max_range = l + 1;
						break;
					}
				}
				break;
			}
		}
	}
	else
	{
		int t1 = row + col - 18;
		for (int l = 0; l < 19 - t1; l++)
		{
			if (board.board[18 - l][t1 + l] != 0)
			{
				if (l == 0) min_range = 0;
				else min_range = l - 1;
				for (int l = 18 - t1; l >= 0; l--)
				{
					if (board.board[18 - l][t1 + l] != 0)
					{
						if (l == 18 - t1) max_range = 18 - t1;
						else max_range = l + 1;
						break;
					}
				}
				break;
			}
		}
	}
	//cout << "returned URD search range: " << min_range << " - " << max_range << endl;
	return make_pair(min_range, max_range);
}

pair<int, int> Get_Search_Range_UpLeftDiagonal(Board board, int row, int col) 
{
	int max_range = -1;
	int min_range = 19;
	if (row <= col)
	{
		int t2 = row + (18 - col);
		for (int l = 0; l <= t2 ; l++)
		{
			if (board.board[t2 - l][18 - l] != 0)
			{
				if (l == 0) min_range = 0;
				else min_range = l - 1;
				for (int l = t2; l >= 0; l--)
				{
					if (board.board[t2 - l][18 - l] != 0)
					{
						if (l == t2) max_range = l;
						else max_range = l + 1;
						break;
					}
				}
				break;
			}
		}
	}
	else
	{
		int t2 = col + (18 - row);
		for (int l = 0; l < t2 + 1; l++)
		{
			if (board.board[18 - l][t2 - l] != 0)
			{
				if (l == 0) min_range = 0;
				else min_range = l - 1;
				for (int l = t2; l >= 0; l--)
				{
					if (board.board[18 - l][t2 - l] != 0)
					{
						if (l == t2) max_range = l;
						else max_range = l + 1;
						break;
					}
				}
				break;
			}
		}
	}
	//cout << "returned ULD search range: " << min_range << " - " << max_range << endl;
	return make_pair(min_range, max_range);
}
