#pragma once

#include "Student.hpp"
#include <array>

class StudentDatabase {
public:
  StudentDatabase();
  ~StudentDatabase();
  explicit StudentDatabase(const StudentDatabase &other);
  StudentDatabase &operator=(const StudentDatabase &other);
  explicit StudentDatabase(const StudentDatabase &&other) noexcept;
  StudentDatabase &operator=(const StudentDatabase &&other) noexcept;

  void addStudent(const Student &s);
  Student *findById(int id);
  void saveToFile(const std::string &filename);
  void loadFromFile(const std::string &filename);

private:
  std::array<Student *, 100> students_;
};