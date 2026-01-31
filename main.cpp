#include <iostream>
using namespace std;

class Student {
private:
  // int rollNo = 21;
  // string Name = "Aareen";
  // int age = 20;
  // string course = "Btech";

  int rollNo;
  string Name;
  int age;
  string course;

public:
  void setData(int rollNo, string Name, int age, string course) {

    cout << "Enter Name: ";
    cin >> Name;

    cout << "Enter Roll Number: ";
    cin >> rollNo;

    cout << "Enter age";
    cin >> age;

    cout << "Enter Course: ";
    cin >> course;
  };

  void displayData() {
    cout << rollNo << "\t" << Name << "\t" << course << "\t" << age << course
         << endl;
  }
  int getRoll() { return rollNo; }

  void updateData() {
    cout << "Enter New Name: ";
    cin >> Name;

    cout << "Enter New Roll no: ";
    cin >> rollNo;

    cout << "Enter New Age: ";
    cin >> age;

    cout << "Enter New Course: ";
    cin >> course;
  }
};

// Global array to store students and count
const int MAX_STUDENTS = 100;
Student students[MAX_STUDENTS];
int countStudents = 0;

// Operations
void addStudent() {
  if (countStudents >= MAX_STUDENTS) {
    cout << "Cannot add more students!\n";
    return;
  }
  students[countStudents].setData(0, "", 0, "");
  countStudents++;
  cout << "Student Added Successfully!\n";
}

void displayStudents() {
  if (countStudents == 0) {
    cout << "No records found!\n";
    return;
  }

  cout << "\nRoll\tName\tCourse\tMarks\n";
  for (int i = 0; i < countStudents; i++) {
    students[i].displayData();
  }
}

void searchStudent() {
  int roll;
  cout << "Enter Roll Number to Search: ";
  cin >> roll;

  for (int i = 0; i < countStudents; i++) {
    if (students[i].getRoll() == roll) {
      cout << "Student Found:\n";
      students[i].displayData();
      return;
    }
  }
  cout << "Student Not Found!\n";
}

void updateStudent() {
  int roll;
  cout << "Enter Roll Number to Update: ";
  cin >> roll;

  for (int i = 0; i < countStudents; i++) {
    if (students[i].getRoll() == roll) {
      students[i].updateData();
      cout << "Student Updated Successfully!\n";
      return;
    }
  }
  cout << "Student Not Found!\n";
}

void deleteStudent() {
  int roll;
  cout << "Enter Roll Number to Delete: ";
  cin >> roll;

  for (int i = 0; i < countStudents; i++) {
    if (students[i].getRoll() == roll) {
      for (int j = i; j < countStudents - 1; j++) {
        students[j] = students[j + 1];
      }
      countStudents--;
      cout << "Student Deleted Successfully!\n";
      return;
    }
  }
  cout << "Student Not Found!\n";
}

// Menu
void showMenu() {
  cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
  cout << "1. Add Student\n";
  cout << "2. Display All Students\n";
  cout << "3. Search Student\n";
  cout << "4. Update Student\n";
  cout << "5. Delete Student\n";
  cout << "6. Exit\n";
  cout << "Enter your choice: ";
}

// Main Function
int main() {
  int choice;
  do {
    showMenu();
    cin >> choice;

    switch (choice) {
    case 1:
      addStudent();
      break;
    case 2:
      displayStudents();
      break;
    case 3:
      searchStudent();
      break;
    case 4:
      updateStudent();
      break;
    case 5:
      deleteStudent();
      break;
    case 6:
      cout << "Data Saved. Exiting Program...\n";
      break;
    default:
      cout << "Invalid Choice!\n";
    }
  } while (choice != 6);

  return 0;
}