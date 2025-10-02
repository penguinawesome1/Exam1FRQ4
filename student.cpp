#include "Student.hpp"

void Student::addScore(int score) { scores_.push_back(score); }

double Student::average() const {
  double total = 0;

  for (int score : scores_) {
    total += score;
  }

  return total / static_cast<double>(scores_.size());
}

const std::string &Student::getName() const { return name_; }

int Student::getId() const { return id_; }

std::vector<int> &Student::getScores() { return scores_; }