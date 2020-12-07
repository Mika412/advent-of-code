
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

class Solution {

public:
  map<string, vector<pair<string, int>>> bags;
  Solution(map<string, vector<pair<string, int>>> &bags) { this->bags = bags; }
  
  int get_total_sum(string my_bag){
    int total_count = 0;
    vector<pair<string,int>> inner_bags = bags[my_bag];
    for(auto inner_bag : inner_bags){
      total_count += inner_bag.second;
    }
    return total_count;
  }
  int get_value(string my_bag){
    int total_count = 0;
    vector<pair<string,int>> inner_bags = bags[my_bag];
    for(auto inner_bag : inner_bags){
      /*if(inner_bag.first == "shiny gold"){
        return get_total_sum(my_bag);
      }*/
        total_count += inner_bag.second* get_value(inner_bag.first) + inner_bag.second;
      
    }
    return total_count;
  }

  int part1(string my_bag) {
    int possible_bags = 0;
    int total_bag_count = 0;
    stack<string> to_check;
    vector<string> seen;
    to_check.push(my_bag);
    while(!to_check.empty()){
      string current_bag = to_check.top();
      to_check.pop();

      for (const auto& kv : bags) {
        vector<pair<string, int>> inner_bags = kv.second;
        int tmp_bag_count = 0;
        for( auto bag : inner_bags){
          tmp_bag_count+= bag.second;
          if(bag.first == current_bag && find(seen.begin(), seen.end(), kv.first) == seen.end()){
            to_check.push(kv.first);
            possible_bags++;
            seen.push_back(kv.first);
            total_bag_count +=tmp_bag_count;
          }
        }
        cout << possible_bags << " " << total_bag_count<< endl;
      }
    }
    /*for (auto tmp:seen){
      cout << tmp << endl;
      cout << get_value(tmp) << endl;
    }*/
    cout << get_value("shiny gold") << endl;
    return possible_bags;
  }
  /*
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
  }*/
};

vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

int main(int argc, char *argv[]) {
  ifstream input;

  input.open("./input.txt");

  map<string, vector<pair<string, int>>> bags;

  map<char, int> answer_count;
  int n_people = 0;
  string tmp_line;
  while (getline(input, tmp_line)) {
    vector<string> contains_split = split(tmp_line, " bags contain");
    string main_color_bag = contains_split[0];
    contains_split.erase(contains_split.begin());

    for(auto &inner_bags_str : contains_split){
      vector<string> inner_bags = split(inner_bags_str, ",");
      vector<pair<string, int>> inner_vector_bags;
      for(auto &bag_str : inner_bags){
        vector<string> bag = split(bag_str," ");
        int num_bags = 0;
        if(bag[0] == "no"){
          continue;
        }
        num_bags = atoi(bag[0].c_str());
        cout << num_bags << endl;
        inner_vector_bags.push_back(make_pair(bag[1] +" " + bag[2], num_bags));
      }
      //cout << inner_bag << endl;
      bags[main_color_bag] =inner_vector_bags;
    }

    //cout << contains_split[0] << endl; 
  }
  input.close();
  /*
  for (const auto& kv : bags) {
      vector<pair<string, int>> inner_bags = kv.second;
      cout << kv.first << " Contains Available:" << endl;
      for( auto bag : inner_bags){
        cout << bag.first << endl;
      }
      cout << "\n" << endl;
    }
    */

  Solution *solver = new Solution(bags);
  cout << "Part 1: " << solver->part1("shiny gold") << endl;
 // //cout << "Part 2: " << solver->part2() << endl;

  return 0;
}
