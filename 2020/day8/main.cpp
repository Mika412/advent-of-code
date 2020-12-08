

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
  Solution(vector<pair<string, int>> &instructions) {}

  pair<int, bool> part1(vector<pair<string, int>> instructions) {

    int count = 0;
    int pnt = 0;
    vector<int> visited;
    bool finished = false;
    while (find(visited.begin(), visited.end(), pnt) == visited.end()) {
      if (pnt >= instructions.size()) {
        finished = true;
        break;
      }
      pair<string, int> cur_instr = instructions.at(pnt);
      visited.push_back(pnt);
      if (cur_instr.first == "nop") {
        pnt += 1;
      } else if (cur_instr.first == "acc") {
        count += cur_instr.second;
        pnt += 1;
      } else if (cur_instr.first == "jmp") {
        pnt += cur_instr.second;
      }
    }
    return make_pair(count, finished);
  }

  int part2(vector<pair<string, int>> instructions) {
    int final_count = 0;
    for (int i = 0; i < instructions.size(); i++) {
      vector<pair<string, int>> instr_copy;
      instr_copy.assign(instructions.begin(), instructions.end());

      pair<string, int> cur_instr = instr_copy.at(i);

      if (cur_instr.first == "nop") {
        cur_instr = make_pair("jmp", cur_instr.second);
      } else if (cur_instr.first == "jmp") {
        cur_instr = make_pair("nop", cur_instr.second);
      } else {
        continue;
      }

      instr_copy[i] = cur_instr;
      pair<int, bool> result = part1(instr_copy);
      if (result.second) {
        final_count = result.first;
        break;
      }
    }
    return final_count;
  }
};

vector<string> split(const string &str, const string &delim) {
  vector<string> tokens;
  size_t prev = 0, pos = 0;
  do {
    pos = str.find(delim, prev);
    if (pos == string::npos)
      pos = str.length();
    string token = str.substr(prev, pos - prev);
    if (!token.empty())
      tokens.push_back(token);
    prev = pos + delim.length();
  } while (pos < str.length() && prev < str.length());
  return tokens;
}

pair<string, int> parse_instruction(string instr_str) {
  vector<string> spl = split(instr_str, " ");
  string instr = spl[0];
  int number;
  stringstream(spl[1]) >> number;
  return make_pair(instr, number);
}

int main(int argc, char *argv[]) {
  ifstream input;

  input.open("./input.txt");

  vector<pair<string, int>> instructions;

  string tmp_line;
  while (getline(input, tmp_line)) {
    pair<string, int> parsed_instr = parse_instruction(tmp_line);
    instructions.push_back(parsed_instr);
  }
  input.close();

  Solution *solver = new Solution(instructions);
  cout << "Part 1: " << solver->part1(instructions).first << endl;
  cout << "Part 2: " << solver->part2(instructions) << endl;

  return 0;
}
