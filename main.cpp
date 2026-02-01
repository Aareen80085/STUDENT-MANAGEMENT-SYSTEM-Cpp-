#include <iostream>
#include <fstream>
using namespace std;

class Student {
private:
    int rollNo;
    string name;
    int age;
    string course;

public:
    void setData() {
        cin.ignore();   

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Roll Number: ";
        cin >> rollNo;

        cout << "Enter Age: ";
        cin >> age;

        cin.ignore();   
        cout << "Enter Course: ";
        getline(cin, course);
    }

    void setDataDirect(int r, string n, int a, string c) {
        rollNo = r;
        name = n;
        age = a;
        course = c;
    }

    void displayData() {
        cout << rollNo << "\t" << name << "\t" << course << "\t" << age << endl;
    }

    int getRoll() { return rollNo; }
    string getName() { return name; }
    int getAge() { return age; }
    string getCourse() { return course; }

    void updateData() {
        cin.ignore();

        cout << "Enter New Name: ";
        getline(cin, name);

        cout << "Enter New Roll No: ";
        cin >> rollNo;

        cout << "Enter New Age: ";
        cin >> age;

        cin.ignore();
        cout << "Enter New Course: ";
        getline(cin, course);
    }
};

const int MAX = 100;
Student students[MAX];
int countStudents = 0;

void saveToFile() {
    ofstream out("students.txt");

    out << countStudents << endl;

    for (int i = 0; i < countStudents; i++) {
        out << students[i].getRoll() << endl;
        out << students[i].getName() << endl;
        out << students[i].getAge() << endl;
        out << students[i].getCourse() << endl;
    }

    out.close();
}

void loadFromFile() {
    ifstream in("students.txt");
    if (!in) return;

    in >> countStudents;
    in.ignore();

    for (int i = 0; i < countStudents; i++) {
        int roll, age;
        string name, course;

        in >> roll;
        in.ignore();
        getline(in, name);

        in >> age;
        in.ignore();
        getline(in, course);

        students[i].setDataDirect(roll, name, age, course);
    }

    in.close();
}

void addStudent() {
    if (countStudents >= MAX) return;

    students[countStudents].setData();
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
    cout << "---------------------------------\n";

    for (int i = 0; i < countStudents; i++)
        students[i].displayData();
}

void searchStudent() {
    int roll;
    cout << "Enter Roll Number: ";
    cin >> roll;

    for (int i = 0; i < countStudents; i++) {
        if (students[i].getRoll() == roll) {
            cout << "\nStudent Found:\n";
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
            for (int j = i; j < countStudents - 1; j++)
                students[j] = students[j + 1];

            countStudents--;
            saveToFile();
            cout << "Student Deleted Successfully!\n";
            return;
        }
    }

    cout << "Student Not Found!\n";
}

void showMenu() {
    cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
    cout << "1. Add Student\n";
    cout << "2. Display Students\n";
    cout << "3. Search Student\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Exit\n";
    cout << "Enter Choice: ";
}

int main() {
    loadFromFile();

    int choice;
    do {
        showMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
        case 1: addStudent(); break;
        case 2: displayStudents(); break;
        case 3: searchStudent(); break;
        case 4: updateStudent(); break;
        case 5: deleteStudent(); break;
        case 6:
            saveToFile();
            cout << "Exiting Program...\n";
            break;
        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}
