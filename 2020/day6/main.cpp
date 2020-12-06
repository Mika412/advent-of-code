
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Group {

public:
  map<char, int> answer_count;
  int n_people;
  Group(map<char, int> answer_count, int n_people) {
    this->answer_count = answer_count;
    this->n_people = n_people;
  }
};

class Solution {

public:
  vector<Group *> groups;
  Solution(vector<Group *> &groups) { this->groups = groups; }

  int part1() {
    int group_answers = 0;
    for (Group *group : groups) {
      group_answers += group->answer_count.size();
    }
    return group_answers;
  }

  int part2() {
    int group_answers = 0;
    for (Group *group : groups) {
      int answered_questions = 0;

      for (const auto &kv : group->answer_count) {
        answered_questions += kv.second == group->n_people;
      }
      group_answers += answered_questions;
    }
    return group_answers;
  }
};

int main(int argc, char *argv[]) {
  ifstream input;

  input.open("./input.txt");

  vector<Group *> groups;

  map<char, int> answer_count;
  int n_people = 0;
  string tmp_line;
  while (getline(input, tmp_line)) {
    if (tmp_line.empty()) {
      groups.push_back(new Group(answer_count, n_people));
      answer_count.clear();
      answer_count = *(new map<char, int>);
      n_people = 0;
      continue;
    }
    for (char &character : tmp_line) {
      if (answer_count.find(character) == answer_count.end()) {
        answer_count[character] = 1;
      } else {

        answer_count[character]++;
      }
    }
    n_people++;
  }
  input.close();

  Solution *solver = new Solution(groups);
  cout << "Part 1: " << solver->part1() << endl;
  cout << "Part 2: " << solver->part2() << endl;

  return 0;
}
