#include <fstream>
#include <iostream>
#include <math.h>
#include <regex>

using namespace std;

class Solution {

public:
  Solution() {}
  int gcd(int a, int b) {
    if (b == 0)
      return a;
    return gcd(b, a % b);
  }
  int part1(int arrival, vector<pair<int, int>> busses) {
    int best_bus_time = numeric_limits<int>::max();
    int best_bus_id = 0;
    for (auto bus : busses) {
      int bus_val = bus.second - (arrival % bus.second);
      if (arrival % bus.second == 0) {
        return 0;
      } else if (bus_val < best_bus_time) {
        best_bus_time = bus_val;
        best_bus_id = bus.second;
      }
    }
    return best_bus_id * best_bus_time;
  }

  long long int part2(int arrival, vector<pair<int, int>> busses) {
    long long int time = 0;
    long long int step = 1;
    vector<long long int> visited_steps;
    bool found = false;
    while (!found) {
      time += step;
      found = true;
      for (auto bus : busses) {
        if ((time + bus.first) % bus.second != 0) {
          found = false;
          break;
        } else if (find(visited_steps.begin(), visited_steps.end(),
                        bus.second) == visited_steps.end()) {
          visited_steps.push_back(bus.second);
          step = floor(bus.second * step / this->gcd(bus.second, step));
        }
      }
    }
    return time;
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
int main(int argc, char *argv[]) {
  ifstream input;

  input.open("./input.txt");

  vector<pair<int, int>> busses;
  int arrival;
  input >> arrival;
  string tmp_str;
  input >> tmp_str;
  vector<string> busses_str = split(tmp_str, ",");

  int offset = -1;
  for (string bus_str : busses_str) {
    offset++;
    if (bus_str == "x") {
      continue;
    }
    busses.push_back(make_pair(offset, stoi(bus_str)));
  }
  input.close();

  Solution *solver = new Solution();
  cout << "Part 1: " << solver->part1(arrival, busses) << endl;
  cout << "Part 2: " << solver->part2(arrival, busses) << endl;

  return 0;
}
