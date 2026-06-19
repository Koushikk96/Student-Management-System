#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Student {
    int rollNo;
    char name[50];
    int age;
    float marks;
};

void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    cout << "\nEnter Roll Number: ";
    cin >> s.rollNo;

    cin.ignore();
    cout << "Enter Name: ";
    cin.getline(s.name, 50);

    cout << "Enter Age: ";
    cin >> s.age;

    cout << "Enter Marks: ";
    cin >> s.marks;

    file.write((char*)&s, sizeof(s));
    file.close();

    cout << "\nStudent Added Successfully!\n";
}

void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    cout << "\n----- Student Records -----\n";

    while (file.read((char*)&s, sizeof(s))) {
        cout << "\nRoll No: " << s.rollNo;
        cout << "\nName: " << s.name;
        cout << "\nAge: " << s.age;
        cout << "\nMarks: " << s.marks;
        cout << "\n--------------------------";
    }

    file.close();
}

void searchStudent() {
    Student s;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Search: ";
    cin >> roll;

    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.rollNo == roll) {
            cout << "\nStudent Found";
            cout << "\nRoll No: " << s.rollNo;
            cout << "\nName: " << s.name;
            cout << "\nAge: " << s.age;
            cout << "\nMarks: " << s.marks;
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nStudent Not Found!\n";
}

void updateStudent() {
    Student s;
    int roll;
    bool found = false;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Roll Number to Update: ";
    cin >> roll;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.rollNo == roll) {
            cout << "\nEnter New Name: ";
            cin.ignore();
            cin.getline(s.name, 50);

            cout << "Enter New Age: ";
            cin >> s.age;

            cout << "Enter New Marks: ";
            cin >> s.marks;

            int pos = file.tellg();
            file.seekp(pos - sizeof(s));

            file.write((char*)&s, sizeof(s));

            found = true;
            cout << "\nRecord Updated Successfully!\n";
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nStudent Not Found!\n";
}

void deleteStudent() {
    Student s;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.rollNo != roll) {
            temp.write((char*)&s, sizeof(s));
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "\nRecord Deleted Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n\n===== Student Management System =====";
        cout << "\n1. Add Student";
        cout << "\n2. Display Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";
        cout << "\nEnter Choice: ";
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
                cout << "\nExiting Program...\n";
                break;
            default:
                cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}