#include <iostream>
#include <fstream>
#include <limits>
using namespace std;
-
/* ================= STUDENT CLASS ================= */

class Student {
private:
    int rollNo;
    string name;
    int age;
    string course;

public:
    void input() {
        cout << "Enter Roll Number: ";
        cin >> rollNo;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Course: ";
        getline(cin, course);
    }

    void display() const {
        cout << rollNo << "\t" << name << "\t"
             << course << "\t" << age << endl;
    }

    int getRoll() const {
        return rollNo;
    }

    void update() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter New Name: ";
        getline(cin, name);

        cout << "Enter New Age: ";
        cin >> age;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter New Course: ";
        getline(cin, course);
    }

    void write(ofstream &out) {
        out << rollNo << endl;
        out << name << endl;
        out << age << endl;
        out << course << endl;
    }

    void read(ifstream &in) {
        in >> rollNo;
        in.ignore();

        getline(in, name);

        in >> age;
        in.ignore();

        getline(in, course);
    }
};

/* ================= GLOBAL DATA ================= */

const int MAX = 100;
Student students[MAX];
int countStudents = 0;

/* ================= FILE HANDLING ================= */

void saveToFile() {
    ofstream out("students.txt");

    out << countStudents << endl;

    for (int i = 0; i < countStudents; i++) {
        students[i].write(out);
    }

    out.close();
}

void loadFromFile() {
    ifstream in("students.txt");
    if (!in) return;

    in >> countStudents;

    for (int i = 0; i < countStudents; i++) {
        students[i].read(in);
    }

    in.close();
}

/* ================= OPERATIONS ================= */

void addStudent() {
    if (countStudents >= MAX) {
        cout << "Student limit reached!\n";
        return;
    }

    students[countStudents].input();
    countStudents++;

    saveToFile();
    cout << "Student Added Successfully!\n";
}

void displayStudents() {
    if (countStudents == 0) {
        cout << "No Records Found!\n";
        return;
    }

    cout << "\nRoll\tName\tCourse\tAge\n";
    cout << "--------------------------------\n";

    for (int i = 0; i < countStudents; i++) {
        students[i].display();
    }
}

void searchStudent() {
    int roll;
    cout << "Enter Roll Number: ";
    cin >> roll;

    for (int i = 0; i < countStudents; i++) {
        if (students[i].getRoll() == roll) {
            students[i].display();
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
            students[i].update();
            saveToFile();
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
            saveToFile();
            cout << "Student Deleted Successfully!\n";
            return;
        }
    }

    cout << "Student Not Found!\n";
}

/* ================= MENU ================= */

void menu() {
    cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
    cout << "1. Add Student\n";
    cout << "2. Display Students\n";
    cout << "3. Search Student\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Exit\n";
    cout << "Enter Choice: ";
}

/* ================= MAIN ================= */

int main() {
    loadFromFile();

    int choice;

    do {
        menu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Enter number only.\n";
            continue;
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting Program...\n"; break;
            default: cout << "Invalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}
