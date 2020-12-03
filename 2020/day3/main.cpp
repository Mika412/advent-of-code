
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Solution {

public:
  map<pair<int, int>, bool> tree_map;
  int total_rows;
  int total_cols;
  Solution(map<pair<int, int>, bool> tree_map, int total_rows, int total_cols) {
    this->tree_map = tree_map;
    this->total_rows = total_rows;
    this->total_cols = total_cols;
  }

  int part1(int row_step, int col_step) {
    int cur_row = 0;
    int cur_col = 0;
    int tree_count = 0;
    while (cur_row <= total_rows) {
      cur_row += row_step;
      cur_col = (cur_col + col_step) % (total_cols + 1);

      tree_count +=
          !(tree_map.find(make_pair(cur_row, cur_col)) == tree_map.end());
    }
    return tree_count;
  }

  long int part2() {
    return (long int)(part1(1, 1)) * (long int)part1(1, 3) *
           (long int)part1(1, 5) * (long int)part1(1, 7) *
           (long int)part1(2, 1);
  }
};

int main(int argc, char *argv[]) {
  ifstream input;

  input.open("./input.txt");

  map<pair<int, int>, bool> tree_map;

  int cur_row = 0;
  int cur_char = 0;
  string tmp_line;
  while (input >> tmp_line) {
    cur_char = 0;
    for (char const &c : tmp_line) {
      if (c == '#') {
        tree_map[make_pair(cur_row, cur_char)] = true;
      }
      cur_char++;
    }
    cur_row++;
  }
  input.close();

  Solution *solver = new Solution(tree_map, cur_row - 1, cur_char - 1);
  cout << "Part 1: " << solver->part1(1, 3) << endl;
  cout << "Part 2: " << solver->part2() << endl;

  return 0;
}
