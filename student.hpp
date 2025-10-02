#pragma once

#include <string>
#include <vector>

class Student {
public:
  Student(std::string name, int id) : name_(name), id_(id){};
  void addScore(int score);
  double average() const;
  const std::string &getName() const;
  int getId() const;
  std::vector<int> &getScores();

private:
  std::string name_;
  int id_;
  std::vector<int> scores_;
};