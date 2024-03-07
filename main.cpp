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

  double addjustGrade(double grade) const {
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
    grade = this->addjustGrade(grade);

    for (int i = 0; i < (int)this->coursesNames.size(); i++) {
      if (courseName == this->coursesNames[i]) {
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
    double sum, total;

    for (int i = 0; i < (int)this->coursesNames.size(); i++) {
      sum += this->grades[i];
      total += this->MAX_GRADE_PER_COURSE;
    }

    return std::make_pair(sum, total);
  }
};

int StudentGradesInfo::statisticsTotalPrints = 0;

int main() {
  StudentGradesInfo stduent1("S001");

  stduent1.addGrade(80.0, "Programming 1");
  stduent1.addGrade(60.0, "Data Structures");
  stduent1.addGrade(70.0, "Algorithms");
  stduent1.addGrade(90.0, "Database");

  stduent1.printAllCourses();

  std::pair<double, double> totalGradesSum = stduent1.getTotalGradesSum();

  std::cout << totalGradesSum.first << "/" << totalGradesSum.second << "\n";

  return 0;
}