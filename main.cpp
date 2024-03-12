#include <assert.h>

#include <cctype>
#include <iostream>
#include <utility>
#include <vector>

class StudentGradesInfo {
 private:
  std::string studentId;
  std::vector<double> grades;
  std::vector<std::string> coursesNames;

  const double MAX_GRADE_PER_COURSE = 100.0;

  static int statisticsTotalPrints;

  std::string toLowerCase(const std::string& str) const {
    std::string result;

    for (int i = 0; i < str.size(); i++) {
      result += tolower(str[i]);
    }

    return result;
  }

  double adjustGrade(double grade) const {
    if (grade < 0) {
      return 0;
    } else if (grade > this->MAX_GRADE_PER_COURSE) {
      return this->MAX_GRADE_PER_COURSE;
    }

    return grade;
  }

 public:
  StudentGradesInfo(std::string id) : studentId(id) {}

  bool addGrade(double grade, const std::string& courseName) {
    grade = this->adjustGrade(grade);

    for (int i = 0; i < (int)this->coursesNames.size(); i++) {
      if (this->toLowerCase(courseName) == this->toLowerCase(this->coursesNames[i])) {
        return false;
      }
    }

    this->coursesNames.push_back(courseName);
    this->grades.push_back(grade);

    return true;
  }

  void printAllCourses() const {
    StudentGradesInfo::statisticsTotalPrints++;

    std::cout << "Grades for student id: " << this->studentId << "\n";

    for (int i = 0; i < (int)this->coursesNames.size(); i++) {
      std::cout << "\t Course name: " << coursesNames[i] << "\t Grade: " << this->grades[i] << "\n";
    }
  }

  bool getCourseGradesInfo(int pos, std::pair<std::string, double>& gradesInfo) const {
    if (pos < 0 || pos >= (int)this->coursesNames.size()) {
      gradesInfo = std::make_pair("", -1);
      return false;
    }

    gradesInfo = std::make_pair(this->coursesNames[pos], this->grades[pos]);
    return true;
  }

  std::pair<double, double> getTotalGradesSum() const {
    double sum = 0, total = 0;

    for (int i = 0; i < (int)this->coursesNames.size(); i++) {
      sum += this->grades[i];
      total += this->MAX_GRADE_PER_COURSE;
    }

    return std::make_pair(sum, total);
  }

  std::string getStudentId() const { return this->studentId; }

  int getTotalCoursesCount() const { return this->coursesNames.size(); }
};

int StudentGradesInfo::statisticsTotalPrints = 0;

class StudentGradesInfoBlackBoxTesting {
 private:
  const int MAX_GRADE_PER_COURSE = 100;

 public:
  void testGetTotalCoursesCount() const {
    StudentGradesInfo student("S001");

    assert(student.getTotalCoursesCount() == 0);

    student.addGrade(80, "Math");
    student.addGrade(90, "Programming1");

    assert(student.getTotalCoursesCount() == 2);

    student.addGrade(90, "Programming1");
    student.addGrade(90, "Programming1");
    student.addGrade(90, "Database");

    assert(student.getTotalCoursesCount() == 3);

    std::cout << "Get total courses count passed test.\n";
  }

  void testGetTotalGradesSum() const {
    StudentGradesInfo student("S002");
    std::pair<double, double> totalGradesSum = student.getTotalGradesSum();

    assert(totalGradesSum.first == 0);
    assert(totalGradesSum.second == 0);

    student.addGrade(200, "Math 1");
    totalGradesSum = student.getTotalGradesSum();

    assert(totalGradesSum.first == MAX_GRADE_PER_COURSE);
    assert(totalGradesSum.second == MAX_GRADE_PER_COURSE);

    student.addGrade(70, "Programming 1");
    totalGradesSum = student.getTotalGradesSum();

    assert(totalGradesSum.first == 70 + MAX_GRADE_PER_COURSE);
    assert(totalGradesSum.second == 2 * MAX_GRADE_PER_COURSE);

    student.addGrade(60, "Programming 1");
    totalGradesSum = student.getTotalGradesSum();

    assert(totalGradesSum.first == 70 + MAX_GRADE_PER_COURSE);
    assert(totalGradesSum.second == 2 * MAX_GRADE_PER_COURSE);

    student.addGrade(80, "Programming 2");
    totalGradesSum = student.getTotalGradesSum();

    assert(totalGradesSum.first == 80 + 70 + MAX_GRADE_PER_COURSE);
    assert(totalGradesSum.second == 3 * MAX_GRADE_PER_COURSE);

    student.addGrade(30, "PROGramming 2");
    totalGradesSum = student.getTotalGradesSum();

    assert(totalGradesSum.first == 80 + 70 + MAX_GRADE_PER_COURSE);
    assert(totalGradesSum.second == 3 * MAX_GRADE_PER_COURSE);

    std::cout << "Get total grades sum passed test.\n";
  }
};

int main() {
  StudentGradesInfoBlackBoxTesting blackBoxTesting;

  blackBoxTesting.testGetTotalCoursesCount();
  blackBoxTesting.testGetTotalGradesSum();

  return 0;
}