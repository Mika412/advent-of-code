#include <fstream>
#include <iostream>
#include <math.h>
#include <regex>
using namespace std;

class Instruction {

public:
  char dir;
  int value;
  Instruction(char dir, int value) {
    this->dir = dir;
    this->value = value;
  }
};
class Solution {

public:
  Solution() {}
  int part1(vector<Instruction *> &instructions) {
    int lat = 0;
    int lon = 0;
    int direction = 90;
    for (auto instr : instructions) {
      if (instr->dir == 'R') {
        direction = (direction + instr->value) % 360;
      } else if (instr->dir == 'L') {
        direction = (direction - instr->value) % 360;
      } else if (instr->dir == 'F') {
        if (direction == 0) {
          lat += instr->value;
        } else if (direction == 90) {
          lon += instr->value;
        } else if (direction == 180) {
          lat -= instr->value;
        } else if (direction == 270) {
          lon -= instr->value;
        }
      } else if (instr->dir == 'N') {
        lat += instr->value;
      } else if (instr->dir == 'E') {
        lon += instr->value;
      } else if (instr->dir == 'S') {
        lat -= instr->value;
      } else if (instr->dir == 'W') {
        lon -= instr->value;
      }
    }
    return abs(lat) + abs(lon);
  }
  int calc_lon(float rad, int lat, int lon) {
    return round(double(cos(rad) * lon - sin(rad) * lat));
  }

  int calc_lat(float rad, int lat, int lon) {
    return round(double(sin(rad) * lon + cos(rad) * lat));
  }
  int part2(vector<Instruction *> &instructions) {

    int lat = 0;
    int lon = 0;
    int way_lat = 1;
    int way_lon = 10;
    float radians = 0;
    for (auto instr : instructions) {
      if (instr->dir == 'R') {
        radians = float(-1 * instr->value * (M_PI / 180));
        int tmp_lon = way_lon;
        int tmp_lat = way_lat;
        way_lon = calc_lon(radians, tmp_lat, tmp_lon);
        way_lat = calc_lat(radians, tmp_lat, tmp_lon);
      } else if (instr->dir == 'L') {
        radians = float(instr->value * (M_PI / 180));
        int tmp_lon = way_lon;
        int tmp_lat = way_lat;
        way_lon = calc_lon(radians, tmp_lat, tmp_lon);
        way_lat = calc_lat(radians, tmp_lat, tmp_lon);
      } else if (instr->dir == 'F') {
        lat += way_lat * instr->value;
        lon += way_lon * instr->value;
      } else if (instr->dir == 'N') {
        way_lat += instr->value;
      } else if (instr->dir == 'E') {
        way_lon += instr->value;
      } else if (instr->dir == 'S') {
        way_lat -= instr->value;
      } else if (instr->dir == 'W') {
        way_lon -= instr->value;
      }
    }
    return abs(lat) + abs(lon);
  }
};

int main(int argc, char *argv[]) {
  ifstream input;

  input.open("./input.txt");

  vector<Instruction *> instructions;

  string tmp_str;
  while (getline(input, tmp_str)) {
    char dir = tmp_str.at(0);
    tmp_str.erase(tmp_str.begin());
    int value = stoi(tmp_str);
    instructions.push_back(new Instruction(dir, value));
  }

  input.close();

  Solution *solver = new Solution();
  cout << "Part 1: " << solver->part1(instructions) << endl;
  cout << "Part 2: " << solver->part2(instructions) << endl;

  return 0;
}
