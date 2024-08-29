#include <iostream>
#include <vector>

class Course {
public:
    std::string name;
    double grade;
    double creditHours;

    Course(std::string name, double grade, double creditHours) 
        : name(name), grade(grade), creditHours(creditHours) {}
};

class Student {
private:
    std::vector<Course> courses;

public:
    void addCourse(const std::string& name, double grade, double creditHours) {
        courses.emplace_back(name, grade, creditHours);
    }

    void showGrades() const {
        std::cout << "\nCourse Grades:\n";
        for (const auto& course : courses) {
            std::cout << "Course: " << course.name 
                      << " | Grade: " << course.grade 
                      << " | Credit Hours: " << course.creditHours 
                      << std::endl;
        }
    }

    double calculateGPA() const {
        double totalGradePoints = 0;
        double totalCredits = 0;
        
        for (const auto& course : courses) {
            totalGradePoints += course.grade * course.creditHours;
            totalCredits += course.creditHours;
        }
        
        return totalGradePoints / totalCredits;
    }

    void showCGPA() const {
        double cgpa = calculateGPA();
        std::cout << "\nCumulative Grade Point Average (CGPA): " << cgpa << std::endl;
    }
};

int main() {
    Student student;
    int numberOfCourses;
    
    std::cout << "Enter the number of courses: ";
    std::cin >> numberOfCourses;

    for (int i = 0; i < numberOfCourses; ++i) {
        std::string courseName;
        double grade, creditHours;

        std::cout << "\nEnter details for Course " << i+1 << ":\n";
        std::cout << "Course Name: ";
        std::cin.ignore();
        std::getline(std::cin, courseName);
        std::cout << "Grade: ";
        std::cin >> grade;
        std::cout << "Credit Hours: ";
        std::cin >> creditHours;

        student.addCourse(courseName, grade, creditHours);
    }

    student.showGrades();
    student.showCGPA();

    return 0;
}
