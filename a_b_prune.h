#pragma once
#include "Utility.h"
#include <iostream>
#include <chrono>
using namespace std;

pair<int, int> Iter_Pruning(State *state, chrono::system_clock::time_point timelimit);
pair<int, int> Pruning(int max_depth, State *state, chrono::system_clock::time_point timelimit);
int Max_Value(State *state, int alpha, int beta, int max_depth, int depth, chrono::system_clock::time_point timelimit);
int Min_Value(State *state, int alpha, int beta, int max_depth, int depth, chrono::system_clock::time_point timelimit);
pair<int, int> First_Max(State *state, int alpha, int beta, int max_depth, int depth, chrono::system_clock::time_point timelimit);
pair<int, int> First_Min(State *state, int alpha, int beta, int max_depth, int depth, chrono::system_clock::time_point timelimit);