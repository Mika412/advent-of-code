#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Password {

public:
  int min_instances;
  int max_instances;
  char target_letter;
  string password;
  Password(int min, int max, char target, string password) {
    this->min_instances = min;
    this->max_instances = max;
    this->target_letter = target;
    this->password = password;
  }
};

class Solution {

public:
  vector<Password *> passwords;
  Solution(vector<Password *> &passwords) { this->passwords = passwords; }

  int part1() {
    int valid_count = 0;
    for (auto &psw_obj : passwords) {
      int count_num = count(psw_obj->password.begin(), psw_obj->password.end(),
                            psw_obj->target_letter);
      valid_count += count_num >= psw_obj->min_instances &&
                     count_num <= psw_obj->max_instances;
    }
    return valid_count;
  }

  int part2() {
    int valid_count = 0;
    for (auto &psw_obj : passwords) {
      bool first_letter = psw_obj->password.at(psw_obj->min_instances - 1) ==
                          psw_obj->target_letter;
      bool second_letter = psw_obj->password.at(psw_obj->max_instances - 1) ==
                           psw_obj->target_letter;

      valid_count += first_letter != second_letter;
    }
    return valid_count;
  }
};

int main(int argc, char *argv[]) {
  ifstream input;

  input.open("./input.txt");

  vector<Password *> passwords;

  string tmp_range, tmp_target, tmp_password;
  while (input >> tmp_range >> tmp_target >> tmp_password) {
    int tmp_min = atoi((tmp_range.substr(0, tmp_range.find("-"))).c_str());
    int tmp_max =
        atoi((tmp_range.substr(tmp_range.find("-") + 1, tmp_range.length()))
                 .c_str());

    Password *password =
        new Password(tmp_min, tmp_max, tmp_target.at(0), tmp_password);
    passwords.push_back(password);
  }
  input.close();

  Solution *solver = new Solution(passwords);
  cout << "Part 1: " << solver->part1() << endl;
  cout << "Part 2: " << solver->part2() << endl;

  return 0;
}
