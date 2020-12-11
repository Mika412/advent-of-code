#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <regex>
#include <sched.h>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Solution {

public:
  Solution() {}

  int part1(int rows, int cols, vector<string> seats) {
    vector<string> seats_copy;
    seats_copy.assign(seats.begin(), seats.end());
    while (true) {
      bool changed = false;
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          char seat = seats_copy.at(i).at(j);
          if (seat == '.') {
            continue;
          }
          int occupied = 0;
          vector<pair<int, int>> adjacent{
              make_pair(i, j + 1),     make_pair(i, j - 1),
              make_pair(i + 1, j),     make_pair(i - 1, j),
              make_pair(i + 1, j + 1), make_pair(i + 1, j - 1),
              make_pair(i - 1, j + 1), make_pair(i - 1, j - 1),
          };
          for (auto adj : adjacent) {
            if (0 > adj.first || adj.first >= rows || 0 > adj.second ||
                adj.second >= cols) {
              continue;
            }
            occupied += seats.at(adj.first).at(adj.second) == '#';
          }
          if (seat == 'L' && occupied == 0) {
            seats_copy.at(i).at(j) = '#';
            changed = true;
          } else if (seat == '#' && occupied >= 4) {
            seats_copy.at(i).at(j) = 'L';
            changed = true;
          }
        }
      }
      if (!changed) {
        break;
      }

      seats.assign(seats_copy.begin(), seats_copy.end());
    }

    int n_seats = 0;
    for (auto line : seats) {
      n_seats += count(line.begin(), line.end(), '#');
    }
    return n_seats;
  }

  int part2(int rows, int cols, vector<string> seats) {
    vector<string> seats_copy;
    seats_copy.assign(seats.begin(), seats.end());
    while (true) {
      bool changed = false;
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          char seat = seats_copy.at(i).at(j);
          if (seat == '.') {
            continue;
          }
          int occupied = 0;
          vector<pair<int, int>> directions{
              make_pair(0, 1),  make_pair(0, -1),  make_pair(1, 0),
              make_pair(-1, 0), make_pair(1, 1),   make_pair(1, -1),
              make_pair(-1, 1), make_pair(-1, -1),
          };
          for (auto dir : directions) {
            int cur_row = i + dir.first;
            int cur_col = j + dir.second;
            while (0 <= cur_row && cur_row < rows && 0 <= cur_col &&
                   cur_col < cols) {

              char adj_seat = seats.at(cur_row).at(cur_col);
              if (adj_seat == '#' || adj_seat == 'L') {
                occupied += adj_seat == '#';
                break;
              }

              cur_row += dir.first;
              cur_col += dir.second;
            }
          }
          if (seat == 'L' && occupied == 0) {
            seats_copy.at(i).at(j) = '#';
            changed = true;
          }

          if (seat == '#' && occupied >= 5) {
            seats_copy.at(i).at(j) = 'L';
            changed = true;
          }
        }
      }
      if (!changed) {
        break;
      }

      seats.assign(seats_copy.begin(), seats_copy.end());
    }

    int n_seats = 0;
    for (auto line : seats) {
      n_seats += count(line.begin(), line.end(), '#');
    }
    return n_seats;
  }
};

int main(int argc, char *argv[]) {
  ifstream input;

  input.open("./input.txt");

  vector<string> lines;

  int rows = 0;
  int cols = 0;
  string tmp_str;

  while (getline(input, tmp_str)) {
    lines.push_back(tmp_str);
    rows++;
    cols = tmp_str.length();
  }

  input.close();

  Solution *solver = new Solution();
  cout << "Part 1: " << solver->part1(rows, cols, lines) << endl;
  cout << "Part 2: " << solver->part2(rows, cols, lines) << endl;

  return 0;
}
