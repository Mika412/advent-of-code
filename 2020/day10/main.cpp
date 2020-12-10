

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

  int factorial(int n) {
    if (n == 0) {
      return 1;
    } else {
      return n * factorial(n - 1);
    }
  }

  int nChoosek(int n, int r) {
    if (r > n)
      return 0;
    if (r * 2 > n)
      r = n - r;
    if (r == 0)
      return 1;

    int result = n;
    for (int i = 2; i <= r; ++i) {
      result *= (n - i + 1);
      result /= i;
    }
    return result;
  }

  int part1(vector<int> jolts) {
    vector<int> jolts_copy;
    jolts_copy.assign(jolts.begin(), jolts.end());
    sort(jolts_copy.begin(), jolts_copy.end());

    int last_jolt = 0;
    int one_jolts = 0;
    int three_jolts = 0;

    for (auto jolt : jolts_copy) {
      one_jolts += (jolt - last_jolt == 1);
      three_jolts += (jolt - last_jolt == 3);
      last_jolt = jolt;
    }

    return one_jolts * (three_jolts + 1);
  }

  long int part2(vector<int> jolts) {
    vector<int> jolts_copy;
    jolts_copy.assign(jolts.begin(), jolts.end());
    sort(jolts_copy.begin(), jolts_copy.end());
    jolts_copy.push_back(jolts_copy.back() + 3);

    long int combinations = 1;

    int hole = 0;
    int last_jolt = 0;
    for (auto jolt : jolts_copy) {
      if ((jolt - last_jolt) == 1) {
        hole += 1;
      } else if (hole > 0) {
        combinations *= nChoosek(hole, 2) + 1;
        hole = 0;
      }
      last_jolt = jolt;
    }

    return combinations;
  }
};

int main(int argc, char *argv[]) {
  ifstream input;

  input.open("./input.txt");

  vector<int> jolts;

  int tmp_num;
  while (input >> tmp_num) {
    jolts.push_back(tmp_num);
  }
  input.close();

  Solution *solver = new Solution();
  cout << "Part 1: " << solver->part1(jolts) << endl;
  cout << "Part 2: " << solver->part2(jolts) << endl;

  return 0;
}
