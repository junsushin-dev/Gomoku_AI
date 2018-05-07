#include "Board.h"
#include <iostream>
#include <queue>
#include <map>
using namespace std;

typedef vector<int> vec;
typedef map<vec, pair<int, int>> table;

map<int, table>* symbols_select(int player);

pair<int, int> makepair(int value, int nextsearchstart);
vec makevector(int a, int b, int c, int d, int e, int f);
vec makevector(int a, int b, int c, int d, int e);
vec makevector(int a, int b, int c, int d);
int Spot_Utility(State state, pair<int, int> spot, int computer);
int Single_Check_Horizontal(Board board, int row, int computer);
int Single_Check_Vertical(Board board, int col, int computer);
int Single_Check_Diagonal(Board board, int row, int col, int computer);
pair<int, int> Get_Search_Range_Horizontal(Board board, int row);
pair<int, int> Get_Search_Range_Vertical(Board board, int col);
pair<int, int> Get_Search_Range_UpRightDiagonal(Board board, int row, int col);
pair<int, int> Get_Search_Range_UpLeftDiagonal(Board board, int row, int col);

bool Check_Forbidden(State* state, pair<int, int> move);
tuple<int, int, int> Check_346_Spot(Board board, int row, int col);
tuple<int, int, int> Check_346_Horizontal(Board board, int row);
tuple<int, int, int> Check_346_Vertical(Board board, int col);
tuple<int, int, int> Check_346_Diagonal(Board board, int row, int col);