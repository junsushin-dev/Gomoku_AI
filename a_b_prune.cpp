#include "a_b_prune.h"
#include <iostream>

pair<int, int> Iter_Pruning(State* state, chrono::system_clock::time_point timelimit)
{
	int depth = 1;
	pair<int, int> result;
	pair<int, int> temp;
	while (chrono::system_clock::now() < timelimit)
	{
		temp = Pruning(depth, state, timelimit);
		if (temp.first < 20 && temp.second < 20) 
		{
			result = temp;
			//std::cout << "depth reached: " << depth << endl;
			//std::cout << "Pruning Result: " << result.first << ", " <<  result.second << endl;
			depth++;
		}
		
	}
	std::cout << "Final ply reached: " << depth - 1<< endl;
	return result;
}

pair<int,int> Pruning(int max_depth, State* state, chrono::system_clock::time_point timelimit)
{
	pair<int, int> result;
	if (state->player == 1)
	{
		result = First_Max(state, -999999, +999999, max_depth, 0, timelimit);
	}
	else if (state->player == -1)
	{
		result = First_Min(state, -999999, +999999, max_depth, 0, timelimit);
	}
	if (chrono::system_clock::now() < timelimit) 
	{
		return result;
	}
	return make_pair(20,20);
}

int Max_Value(State* state, int alpha, int beta, int max_depth, int depth, chrono::system_clock::time_point timelimit)
{
	if (Terminal_check(state)) return -999999+depth;
	if (depth == max_depth || (chrono::system_clock::now() > timelimit)) 
	{
		//cout << "returned utility: ";
		//cout << state->state_value << endl;
		return state->state_value;
	}
	int v = -999999;
	pair<int, int> next_action;
	queue<pair<int, int>>  possible_actions = restricted_actions(state);
	while (possible_actions.empty() == false && (chrono::system_clock::now() < timelimit))
	{
		next_action = possible_actions.front();
		possible_actions.pop();
		v = max(v, Min_Value(change_state(state, next_action), alpha, beta, max_depth, depth+1, timelimit));
		if (v >= beta)
		{
			return v;
		}
		alpha = max(alpha, v);
	}
	//std::cout << "max value is: " << v << endl;
	//print_board(state);
	return v;
}

int Min_Value(State* state, int alpha, int beta, int max_depth, int depth, chrono::system_clock::time_point timelimit)
{
	if (Terminal_check(state)) return 999999-depth;
	if (depth == max_depth || (chrono::system_clock::now() > timelimit))
	{
		//cout << "returned utility: ";
		//cout << state->state_value << endl;
		return state->state_value;
	}
	int v = 999999;
	pair<int, int> next_action;
	queue<pair<int, int>>  possible_actions = actions(state);
	while (possible_actions.empty() == false && (chrono::system_clock::now() < timelimit))
	{
		next_action = possible_actions.front();
		possible_actions.pop();
		v = min(v, Max_Value(change_state(state, next_action), alpha, beta, max_depth, depth + 1, timelimit));
		if (v <= alpha)
		{
			return v;
		}
		beta = min(beta, v);
	}
	//std::cout << "min value is: " << v << endl;
	//print_board(state);
	return v;
}

pair<int,int> First_Max(State *state, int alpha, int beta, int max_depth, int depth, chrono::system_clock::time_point timelimit)
{
	//std::cout << "First_max" << endl;
	int v = -999999;
	int new_val;
	pair<int, int> next_action;
	pair<int, int> best_action;
	action_queue  possible_actions = restricted_actions(state);
	//std::cout << possible_actions.front().first << possible_actions.front().second << endl;
	while (possible_actions.empty() == false && (chrono::system_clock::now() < timelimit))
	{
		next_action = possible_actions.front();
		//std::cout << "considering move..." << next_action.first << ", " <<next_action.second << endl;
		possible_actions.pop();
		new_val =  max(v, Min_Value(change_state(state, next_action), alpha, beta, max_depth, depth + 1, timelimit));
		if (v < new_val)
		{
			best_action = next_action;
			v = new_val;
			//std::cout << "improved value..." << new_val << endl;
		}
		alpha = max(alpha, v);
	}
	return best_action;
}

pair<int, int> First_Min(State* state, int alpha, int beta, int max_depth, int depth, chrono::system_clock::time_point timelimit)
{
	//std::cout << "First_min" << endl;
	int v = 999999;
	int new_val;
	pair<int, int> next_action;
	pair<int, int> best_action;
	action_queue  possible_actions = actions(state);
	//std::cout << possible_actions.front().first << possible_actions.front().second << endl;
	while (possible_actions.empty() == false && (chrono::system_clock::now() < timelimit))
	{
		next_action = possible_actions.front();
		//std::cout << "considering move..." << next_action.first << ", " << next_action.second << endl;
		possible_actions.pop();
		new_val = min(v, Max_Value(change_state(state, next_action), alpha, beta, max_depth, depth + 1, timelimit));
		if (v > new_val)
		{
			best_action = next_action;
			v = new_val;
			//std::cout << "improved value..." << new_val << endl;
		}
		beta = min(beta, v);
	}
	return best_action;
}
