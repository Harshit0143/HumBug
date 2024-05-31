#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <unordered_set>
#include <list>
#include <iterator>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <bitset>
#include <random>
#include <map>
#include <unordered_map>
#include <stdio.h>
#include <complex>
#include <math.h>
#include <cstring>
#include <chrono>
#include <string>

using namespace std;

#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL)
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nline "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define fo(i, a, b) for (int i = a; i < b; ++i)
#define max_(a, b, c) max(max(a, b), c)

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

vector <string> all_paths;


void show_grid(vector<vector<int>> &vec)
{
    cout << "showing grid...\n";
    for (int i = 0 ; i < vec.size() ; i++)
    {
        for (int j = 0 ; j < vec[0].size() ; j++)
        {
            cout << vec[i][j] << ' ';
        }
    cout << '\n';
    }
}
void show_grid(vector<vector<bool>> &vec)
{
    for (int i = 0 ; i < vec.size() ; i++)
    {
        for (int j = 0 ; j < vec[0].size() ; j++)
        {
            cout << vec[i][j] << ' ';
        }
    cout << '\n';
    }
}

void show_list(vector <pair<pair<int,int>,char>> &moves)
{
    // cout << "found path!\n";
    string ans = "";
    for (int i = 0 ; i < moves.size() ; i++)
        ans += "(" + to_string(moves[i].first.first) + "," + to_string(moves[i].first.second) + ") -> " + moves[i].second + "\n";
    all_paths.push_back(ans);
    // cout << "______end_path______\n";
}
string show_best(vector <string> &vec)
{

    if (vec.size() == 0)
        return "not possible!";

    int min_len = INT32_MAX;
    for (string &s : vec)
        min_len = min(min_len , (int)s.size());
    for (string &s : vec)
        if (s.size() == min_len)
            return s;
    
    return "never reaching here!";
}


class Bug{

    public:
        string type;
        int pos_x , pos_y , step_size;
        bool is_flying = false;
        vector <string> flying {"grasshopper" , "honeybee" , "butterfly"};
        map <string , int> step_sizes {
            {"snail", 1},
            {"spider", INT32_MAX},
            {"grasshopper", 1},
            {"ladybug", 2},
            {"honeybee", 2},
            {"butterfly", 3}
        };

    Bug(string &name , int pos_x , int pos_y)
    {   
        this->type = name;
        this->pos_x = pos_x , this->pos_y = pos_y;
        this->step_size = step_sizes[name];
        auto it = find(flying.begin() , flying.end() , name);
        if (it != flying.end())
            is_flying = true;
    }

};

class Board{

    public:
        int n , m , gold_cnt = 0;
        vector <vector<bool>> is_land , is_free , is_gold;
        vector<vector<vector<char>>> board_walls;
        vector <pair<pair<int,int>,char>> all_moves;
        vector <Bug> board_bugs;
        vector <bool> is_present;
        map <char,int>  dx = {
            {'L' , 0},
            {'R' , 0},
            {'U' , -1},
            {'D' , +1}
        };
        map <char,int>  dy = {
            {'L' , -1},
            {'R' , +1},
            {'U' , 0},
            {'D' , 0}
        }; 
        map <char , char> opp_dir = {
            {'L' , 'R'},
            {'R' , 'L'},
            {'U' , 'D'},
            {'D' , 'U'}
        };
        map <int, string>  char_to_type = {
            {3 , "snail"},
            {4 , "grasshopper"},
            {5 , "ladybug"},
            {6 , "honeybee"},
            {7 , "spider"},
            {8 , "butterfly"}
        };
        map <string , int> step_size {
            {"snail", 1},
            {"spider", INT32_MAX},
            {"grasshopper", 1},
            {"ladybug", 2},
            {"honeybee", 2},
            {"butterfly", 3}
        };

        void fill_land_free(vector<vector<int>> &board)
        {
            for (int i = 0 ; i < n ; i++)
                for (int j = 0 ; j < m ; j++)
                {
                    if (board[i][j] != 0)
                    {
                        is_land[i][j] = true;
                        if (board[i][j] == 2)
                        {
                            gold_cnt++;
                            is_gold[i][j] = true;
                            continue;
                        }
                        else if (board[i][j] != 1)
                        {
                            is_free[i][j] = false;
                            Bug this_bug = Bug(char_to_type[board[i][j]] , i , j);
                            board_bugs.push_back(this_bug);
                            is_present.push_back(true);
                        }
                    }   

                }
        }
        void fill_board_obstacles(vector<pair<pair<int , int> , char>> &walls)
        {
            for (pair<pair<int,int>,char> &wall : walls)
            {
                int cell_x = wall.first.first , cell_y = wall.first.second;
                char wall_dir = wall.second;
                board_walls[cell_x][cell_y].push_back(wall_dir);
            }

        }
        bool is_valid(int x , int y)
        {
            return (0 <= x) and (x < n) and (0 <= y) and (y < m) and (is_land[x][y]);
        }


        void assert_wall_placement()
        {
            for (int x = 0 ; x < n ; x++)
                for (int y = 0 ; y < m ; y++)
                {
                    for (char dir : board_walls[x][y])
                    {
                        int nbr_x = x + dx[dir] , nbr_y = y + dy[dir];
                        if (is_valid(nbr_x , nbr_y))
                        {
                            char nbr_dir = opp_dir[dir];
                            auto it = find(board_walls[nbr_x][nbr_y].begin() , board_walls[nbr_x][nbr_y].end() , nbr_dir);
                            if (it == board_walls[nbr_x][nbr_y].end()) 
                                throw runtime_error("mismatch found in walls!");

                        }   
                    }
                
                }
        }

        bool is_legal_flying(int idx , int dir)
        {
            int pos_x = board_bugs[idx].pos_x , pos_y = board_bugs[idx].pos_y;            
            pos_x += board_bugs[idx].step_size * dx[dir] , pos_y += board_bugs[idx].step_size * dy[dir];
            if (!is_valid(pos_x , pos_y))
                return false;
            while (!is_free[pos_x][pos_y])
            {
                pos_x += dx[dir] , pos_y += dy[dir];
                if (!is_valid(pos_x , pos_y))
                    return false;
            }
            return true;
            
        }

        bool is_land_blocked(int pos_x , int pos_y , char dir){
            int fin_x = pos_x + dx[dir] , fin_y = pos_y + dy[dir];
            auto it = find(board_walls[pos_x][pos_y].begin() , board_walls[pos_x][pos_y].end() , dir);
            if (it != board_walls[pos_x][pos_y].end())
                return true;
            if (!is_valid(fin_x , fin_y))
                return false;
            if (!is_free[fin_x][fin_y])
                return true;
            return false;
        }

        bool is_legal_walking(int idx , int dir)
        {   
            int pos_x = board_bugs[idx].pos_x , pos_y = board_bugs[idx].pos_y;

            if (is_land_blocked(pos_x , pos_y , dir))
                return false;

            for (int i = 0 ; i < board_bugs[idx].step_size ; i++)
            {
                pos_x += dx[dir] , pos_y += dy[dir];
                if (!is_valid(pos_x , pos_y))
                    return false;
                if (is_land_blocked(pos_x , pos_y , dir))
                    return true;
            }
        
            return true;
            
        }

        bool is_legal_move(int idx , char dir)
        {
            if (board_bugs[idx].is_flying)
                return  is_legal_flying(idx , dir);
            return is_legal_walking(idx , dir);


        } 
        pair<int,int> walk_fwd(int idx , char dir)
        {
            int pos_x = board_bugs[idx].pos_x , pos_y = board_bugs[idx].pos_y;
            is_free[pos_x][pos_y] = true;
            for (int i = 0 ; i < board_bugs[idx].step_size ; i++)
            {
                pos_x += dx[dir] , pos_y += dy[dir];
                if (is_land_blocked(pos_x , pos_y , dir))
                    break;
            }

            board_bugs[idx].pos_x = pos_x , board_bugs[idx].pos_y = pos_y;
            
            if (is_gold[pos_x][pos_y])
            {
                gold_cnt--;
                is_gold[pos_x][pos_y] = false;
                is_present[idx] = false;
                is_free[pos_x][pos_y] = true;
                return make_pair(pos_x , pos_y);             

            }
            is_free[pos_x][pos_y] = false;
            return make_pair(pos_x , pos_y);             
        }

        pair<int,int> fly_fwd(int idx , int dir)
        {
            int pos_x = board_bugs[idx].pos_x , pos_y = board_bugs[idx].pos_y;
            is_free[pos_x][pos_y] = true;
            pos_x += board_bugs[idx].step_size * dx[dir] , pos_y += board_bugs[idx].step_size * dy[dir];


            while (!is_free[pos_x][pos_y])
                pos_x += dx[dir] , pos_y += dy[dir];


            
            board_bugs[idx].pos_x = pos_x , board_bugs[idx].pos_y = pos_y;

            if (is_gold[pos_x][pos_y])
            {
                gold_cnt--;
                is_gold[pos_x][pos_y] = false;
                is_present[idx] = false;;
                is_free[pos_x][pos_y] = true;
                return make_pair(pos_x , pos_y);

            }
            
            is_free[pos_x][pos_y] = false;
            return make_pair(pos_x , pos_y);  
        }

 

        pair<int,int> move_dir_fwd(int idx , char dir)
        {  
            pair<int,int> init_pos(board_bugs[idx].pos_x , board_bugs[idx].pos_y);
            all_moves.push_back(make_pair(init_pos , dir));
            pair<int, int> pos;
            if (board_bugs[idx].is_flying)
                pos = fly_fwd(idx , dir);
            else
                pos = walk_fwd(idx , dir);

            if (gold_cnt == 0)
                show_list(all_moves);
            return pos;

        }

        
        void undo_move(int idx , int new_x , int new_y , int old_x , int old_y)
        {

            if (!is_present[idx])
            {
                gold_cnt++;
                is_gold[new_x][new_y] = true;
                is_present[idx] = true;
            }
            board_bugs[idx].pos_x = old_x , board_bugs[idx].pos_y = old_y;
            all_moves.pop_back();
            is_free[old_x][old_y] = false;
            is_free[new_x][new_y] = true;

        }



        void show_board()
        {   
            int wall_cnt = 0;
            for (int i = 0 ; i < n ; i++)
                for (int j = 0 ; j < m ; j++)
                    wall_cnt += board_walls[i][j].size();

            cout << "num_walls: " << wall_cnt << '\n';
            cout << "gold_count: " << gold_cnt << '\n';
            cout << "bug count: " << board_bugs.size() << '\n';


            cout << "showing is_land..\n";
            show_grid(is_land);

            cout << "showing is_free..\n";
            show_grid(is_free);

            cout << "showing is_gold..\n";
            show_grid(is_gold);
        }

        Board(vector<vector<int>> &board , vector<pair<pair<int,int>,char>> &walls)
        {
            cout << "building board....." << '\n';
            n = board.size() , m = board[0].size();
            is_land.resize(n , vector<bool>(m , false));
            is_free.resize(n , vector<bool>(m , true));
            is_gold.resize(n , vector<bool>(m , false));
            board_walls.resize(n , vector<vector<char>> (m , vector <char> ()));
            fill_land_free(board);
            fill_board_obstacles(walls);
            assert_wall_placement();
            cout << "finished building board!" << '\n';

        }
};



void solve_further(Board &board , int moves)
{   
    if (board.gold_cnt == 0)
    {   
        show_list(board.all_moves);
        return; 
    }
    if (moves == 0)
        return;


    vector <char> directions{'R' , 'L' , 'U' , 'D'};
    for (int idx = 0 ; idx < board.board_bugs.size() ; idx++)
    {   
        if (!board.is_present[idx])
            continue;
        for (char dir : directions)
        {
            // cout << "in_dirn: " << dir<< '\n';
            if (not board.is_legal_move(idx , dir))
                continue;
            // cout << "ot_dirn: " << dir << '\n';
            
            int old_x = board.board_bugs[idx].pos_x ,  old_y = board.board_bugs[idx].pos_y; 
            pair<int, int> new_pos = board.move_dir_fwd(idx , dir);
            solve_further(board , moves - 1);
            board.undo_move(idx , new_pos.first , new_pos.second , old_x , old_y);
        }
    }
}



// g++ -std=c++20 -o main main.cpp && ./main
int main()
{
    vector<string> bugs = {"snail", "spider", "grasshopper", "ladybug", "honeybee", "butterfly"};
    fastio;
    ifstream file("levels/level_i40.txt");
    
    int rows , cols;
    file >> rows >> cols;
    cout << "rows: " << rows << " cols: " << cols <<'\n'; 
    vector<vector<int>> grid(rows, vector<int>(cols));
    for (int i = 0 ; i < rows ; ++i)
        for (int j = 0; j < cols; ++j) {
            file >> grid[i][j];
        }

    int num_walls;
    file >> num_walls;
    vector<pair<pair<int,int>,char>> walls;
    for (int i = 0 ; i < num_walls ; i++)
    {
        int x , y;
        char dir;
        file >> x >> y >> dir;
        walls.push_back(make_pair(make_pair(x , y) , dir));
    }

    int max_moves;
    file >> max_moves;
    cout << "max_moves: " << max_moves << '\n';
    file.close();
    Board board = Board(grid , walls);
    board.show_board();
    solve_further(board , max_moves);
    cout << show_best(all_paths);
    return 0;
}