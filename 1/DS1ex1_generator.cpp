// 黃乙家
#include "testlib.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#define down 1
#define right 2
#define left 4
#define up 8

struct MazeGenerator {
  int n, m;
  vector<vector<char>> maze;

  vector<pair<int, int>> obstacles;
  vector<int> direct;
  int cur_x, cur_y;
  int PushNearObstacle() {
    int cnt = 0;
    if (cur_x + 1 < n) {
      obstacles.push_back(make_pair(cur_x + 1, cur_y));
      direct.push_back(down);
      ++cnt;
    }
    if (cur_x - 1 >= 1) {
      obstacles.push_back(make_pair(cur_x - 1, cur_y));
      direct.push_back(up);
      ++cnt;
    }
    if (cur_y + 1 < m) {
      obstacles.push_back(make_pair(cur_x, cur_y + 1));
      direct.push_back(right);
      ++cnt;
    }
    if (cur_y - 1 > 1) {
      obstacles.push_back(make_pair(cur_x, cur_y - 1));
      direct.push_back(left);
      ++cnt;
    }

    return cnt;
  }
  void Init() {
    maze.resize(n + 2);

    for (int i = 0; i < n + 1; ++i) {
      maze[i].resize(m + 2);
    }

    for (int i = 0; i < n + 1; ++i) {
      for (int j = 0; j < m + 1; ++j) {
        maze[i][j] = 'O';
      }
    }

    cur_x = cur_y = 0;
    maze[cur_x][cur_y] = 'E';
  }

  void generate() {
    Init();

    PushNearObstacle();

    maze[cur_x][cur_y] = 'E';
    while (obstacles.size()) {
      long long num = obstacles.size();
      assert((long long)num - 1 >= 0);
      long long idx = rnd.next(0LL, (long long)num - 1);

      // cout << idx << " ";
      cur_x = obstacles[idx].first, cur_y = obstacles[idx].second;
      // cout << cur_x << " " << cur_y << endl;
      int d = direct[idx];
      switch (d) {
      case down: {
        cur_x = obstacles[idx].first + 1;
        cur_y = obstacles[idx].second;
        break;
      }
      case right: {
        cur_x = obstacles[idx].first;
        cur_y = obstacles[idx].second + 1;
        break;
      }
      case left: {
        cur_x = obstacles[idx].first;
        cur_y = obstacles[idx].second - 1;
        break;
      }
      case up: {
        cur_x = obstacles[idx].first - 1;
        cur_y = obstacles[idx].second;
        break;
      }
      }
      if (maze[cur_x][cur_y] == 'O') {
        maze[obstacles[idx].first][obstacles[idx].second] = 'E';
        maze[cur_x][cur_y] = 'E';
        PushNearObstacle();
      }
      obstacles.erase(obstacles.begin() + idx);
      direct.erase(direct.begin() + idx);
    }
  }

  void Print() {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << maze[i][j];
      }
      cout << endl;
    }
  }
};

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  bool help = opt<bool>("h", false);

  if (help) {
    cout << "\n---Maze Generator---" << endl;
    cout << "Usage: ./DS1ex1_generator " << endl;
    cout << "\t[-t <number of test cases>] [-s <start index>] [-h] [-v] [-x "
            "<row size>] [-y <column size>] "
            "[-g <goals>] "
         << endl;
    cout << "Options:" << endl;
    cout << "\t-t <number of test cases> : number of test cases to generate, "
            "if not specified, "
            "it will be 1"
         << endl;
    cout << "\t-s <start index> : start index of test cases, if not specified, "
            "it will be 0"
         << endl;
    cout << "\t-h : print this help" << endl;
    cout << "\t-v : Show generating details" << endl;
    cout << "\t-x <row size> : row size of maze, if not specified, it will be "
            "random"
         << endl;
    cout << "\t-y <column size> : column size of maze, if not specified, it "
            "will be random"
         << endl;
    cout
        << "\t-g <goals> : number of goals, if not specified, it will be random"
        << endl;
    cout << "\nMade by: CompileErr0r(YiJia), Github: ja-errorpro" << endl;
    cout << "--------------------\n" << endl;

    return 0;
  }

  int start = opt<int>("s", 0);

  int N = opt<int>("t", 1);
  if (N < 1) {
    cout << "Number of test cases must be positive!" << endl;
    return 0;
  }
  if (N > 100) {
    cout << "Too many test cases!" << endl;
    return 0;
  }

  bool printMaze = opt<bool>("v", false);
  for (int file = 0; file < N; ++file) {
    ofstream fout("input" + to_string(file + start) + ".txt");
    if (printMaze) {
      println("\nGenerating: input" + to_string(file + start) + ".txt");
    }
    long long x = rnd.next(3LL, 50LL);
    x = max(opt<int>("x", x), 1);
    long long y = rnd.next(3LL, 50LL);
    y = max(opt<int>("y", y), 1);
    if (printMaze) {
      println("\nx =", x, "y =", y);
    }
    fout << y << " " << x << endl;
    MazeGenerator maze;
    maze.n = x - 1;
    maze.m = y - 1;
    maze.generate();
    long long goals = rnd.wnext(0LL, x * y - 1, -10);
    goals = max(opt<int>("g", goals), 0);

    if (goals > x * y) {
      cout << "Too many goals! Set to x * y - 1" << endl;
      goals = x * y - 1;
    }
    if (printMaze) {
      println("goals =", goals);
    }

    vector<pair<int, int>> emptys;
    for (int i = 0; i < x; ++i) {
      for (int j = 0; j < y; ++j) {
        if (maze.maze[i][j] == 'E') {
          emptys.push_back(make_pair(i, j));
        }
      }
    }

    assert(emptys.size() != 0);

    for (int i = 0; i < goals; ++i) {
      int idx = rnd.next(0, (int)emptys.size() - 1);
      if (emptys[idx].first == 0 && emptys[idx].second == 0) {
        --i;
        continue;
      }
      maze.maze[emptys[idx].first][emptys[idx].second] = 'G';
      emptys.erase(emptys.begin() + idx);
    }

    for (int i = 0; i < x; ++i) {
      for (int j = 0; j < y; ++j) {
        if (printMaze) {
          cout << maze.maze[i][j];
        }
        fout << maze.maze[i][j];
      }

      if (printMaze) {
        cout << endl;
      }

      fout << endl;
    }

    if (printMaze) {
      cout << endl;
    }
    /*
        ofstream in("input" + to_string(file + start) + ".in");
        long long mode = rnd.next(1LL, 2LL);
        if (printMaze) {
          println("mode =", mode);
        }
        in << mode << endl;
        in << to_string(file + start) << endl;
        if (mode == 2) {
          long long rndGoals = rnd.next(1LL, goals + 1);
          if (printMaze) {
            println("rndGoals =", rndGoals);
          }
          in << rndGoals << endl;
        }
        in << 0 << endl;*/

    if (printMaze) {
      println("\n--------------------");
    }
  }
  cout << "\nDone!" << endl;
  return 0;
}