
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Solution {

public:
  vector<string> seats_instr;
  Solution(vector<string> &seat_instr) { this->seats_instr = seat_instr; }

  int calculate_seat(string code) {

    int low_row = 0;
    int high_row = 127;
    for (int i = 0; i < 7; i++) {
      if (code.at(i) == 'F') {
        high_row = low_row + (high_row - low_row) / 2.0f;
      } else {
        low_row = 1 + low_row + (high_row - low_row) / 2.0f;
      }
    }

    int low_col = 0;
    int high_col = 7;

    for (int i = 7; i < 10; i++) {
      if (code.at(i) == 'L') {
        high_col = low_col + (high_col - low_col) / 2.0f;
      } else {
        low_col = 1 + low_col + (high_col - low_col) / 2.0f;
      }
    }
    return low_row * 8 + low_col;
  }
  int part1() {
    int highest_id = 0;

    for (auto st : seats_instr) {
      int id = calculate_seat(st);
      if (id > highest_id) {
        highest_id = id;
      }
    }
    return highest_id;
  }

  int part2() {
    vector<int> seats;
    int lowest_id = numeric_limits<int>::infinity();
    int highest_id = -numeric_limits<int>::infinity();

    for (auto st : seats_instr) {
      int id = calculate_seat(st);
      seats.push_back(id);
      if (id < lowest_id)
        lowest_id = id;

      if (id > highest_id)
        highest_id = id;
    }

    vector<int> open_seats;
    for (int i = lowest_id; i <= highest_id; i++) {
      if (find(seats.begin(), seats.end(), i) == seats.end()) {
        open_seats.push_back(i);
      }
    }

    for (int seat : open_seats) {

      if (find(seats.begin(), seats.end(), seat - 1) != seats.end() &&
          find(seats.begin(), seats.end(), seat + 1) != seats.end()) {
        return seat;
      }
    }
  }
};

int main(int argc, char *argv[]) {
  ifstream input;

  input.open("./input.txt");

  vector<string> seat_instr;

  string tmp_line;
  while (getline(input, tmp_line)) {
    seat_instr.push_back(tmp_line);
  }
  input.close();

  Solution *solver = new Solution(seat_instr);
  cout << "Part 1: " << solver->part1() << endl;
  cout << "Part 2: " << solver->part2() << endl;

  return 0;
}
