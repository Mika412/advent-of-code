#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Solution {

public:
  vector<int> nums;
  Solution(vector<int> &nums) { this->nums = nums; }

  int part1(int target = 2020, int start_at = 0) {
    for (int i = start_at; i < nums.size() - 1; i++) {
      for (int j = i + 1; j < nums.size(); j++) {
        if (nums.at(i) + nums.at(j) == target)
          return nums.at(i) * nums.at(j);
      }
    }
    return -1;
  }

  int part2(int target) {
    for (int i = 0; i < nums.size() - 2; i++) {
      int mult = part1(target - nums.at(i), i + 1);
      if (mult != -1) {
        return mult * nums.at(i);
      }
    }
    return -1;
  }
};

int main(int argc, char *argv[]) {
  ifstream input;

  input.open("./input.txt");

  vector<int> nums;

  int tmp_num;
  while (!input.eof()) {
    input >> tmp_num;
    nums.push_back(tmp_num);
  }

  input.close();

  Solution *solver = new Solution(nums);

  cout << "Part 1: " << solver->part1(2020) << endl;
  cout << "Part 2: " << solver->part2(2020) << endl;

  return 0;
}
