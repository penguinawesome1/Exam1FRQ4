#include "StudentDatabase.hpp"
#include <fstream>
#include <iostream>

StudentDatabase::~StudentDatabase() {
  for (Student *student : students_) {
    delete student;
  }
}

StudentDatabase::StudentDatabase(const StudentDatabase &other) {
  size_t other_students_size = other.students_.size();

  for (size_t i = 0; i < other_students_size; i++) {
    Student *student = students_[i];
    Student *other_student = other.students_[i];

    Student *temp = new Student(*other_student);
    student = temp;
  }
}

StudentDatabase &StudentDatabase::operator=(const StudentDatabase &other) {
  if (this == &other) {
    return *this;
  }

  size_t other_students_size = other.students_.size();

  for (size_t i = 0; i < other_students_size; i++) {
    Student *student = students_[i];
    Student *other_student = other.students_[i];

    Student *temp = new Student(*other_student);
    delete student;
    student = temp;
  }

  return *this;
}

StudentDatabase::StudentDatabase(const StudentDatabase &&other) noexcept {
  size_t other_students_size = other.students_.size();

  for (size_t i = 0; i < other_students_size; i++) {
    Student *student = students_[i];
    Student *other_student = other.students_[i];

    Student *temp = new Student(*other_student);
    student = temp;

    delete other_student;
    other_student = nullptr;
  }
}

StudentDatabase &
StudentDatabase::operator=(const StudentDatabase &&other) noexcept {
  if (this == &other) {
    return *this;
  }

  size_t other_students_size = other.students_.size();

  for (size_t i = 0; i < other_students_size; i++) {
    Student *student = students_[i];
    Student *other_student = other.students_[i];

    Student *temp = new Student(*other_student);
    delete student;
    student = temp;

    delete other_student;
    other_student = nullptr;
  }

  return *this;
}

void StudentDatabase::addStudent(const Student &s) {
  size_t students_size = students_.size();

  for (size_t i = 0; i < students_size; i++) {
    Student *student = students_[i];

    if (!student) {
      *student = s;
      return;
    }
  }
}

Student *StudentDatabase::findById(int id) {
  size_t students_size = students_.size();

  for (size_t i = 0; i < students_size; i++) {
    Student *student = students_[i];

    if (student && student->getId() == id) {
      return student;
    }
  }
}

void StudentDatabase::saveToFile(const std::string &filename) {
  std::ofstream out(filename);

  for (Student *student : students_) {
    if (!student) {
      continue;
    }

    out << student->getId() << " " << student->getName() << " ";

    for (int score : student->getScores()) {
      out << score << " ";
    }
  }
}

void StudentDatabase::loadFromFile(const std::string &filename) {
  std::ifstream in(filename);

  if (!in) {
    std::cerr << "Invalid filename passed into loadFromFile\n";
    return;
  }

  int last_num = 0;
  Student *last_student = nullptr;

  while (!in.eof()) {
    char *str = nullptr;
    in.getline(str, ' ');

    int num = 0;

    try {
      num = std::stoi(str);

      if (last_student) {
        last_student->addScore(last_num);
      }

      last_num = num;
    } catch (...) { // given a str for name
      if (last_student) {
        addStudent(*last_student);
        last_student = nullptr;
      }

      Student *student = new Student(str, last_num);
      last_student = student;
      student = nullptr;
    }
  }
}