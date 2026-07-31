#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Student
{
    int id;
    char name[50];
    int age;
    char course[50];
};

vector<Student> students;

void loadData()
{
    students.clear();

    ifstream file("students.dat", ios::binary);

    Student s;

    while (file.read((char*)&s, sizeof(Student)))
    {
        students.push_back(s);
    }

    file.close();
}

void saveData()
{
    ofstream file("students.dat", ios::binary);

    for (Student s : students)
    {
        file.write((char*)&s, sizeof(Student));
    }

    file.close();
}

void addStudent()
{
    Student s;

    cout << "\nEnter Student ID: ";
    cin >> s.id;

    cin.ignore();

    cout << "Enter Name: ";
    cin.getline(s.name, 50);

    cout << "Enter Age: ";
    cin >> s.age;

    cin.ignore();

    cout << "Enter Course: ";
    cin.getline(s.course, 50);

    students.push_back(s);

    saveData();

    cout << "\nStudent Added Successfully.\n";
}

void displayStudents()
{
    if (students.empty())
    {
        cout << "\nNo Records Found.\n";
        return;
    }

    cout << "\n-------------------------------------------------------------\n";
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(10) << "Age"
         << setw(20) << "Course" << endl;
    cout << "-------------------------------------------------------------\n";

    for (Student s : students)
    {
        cout << left << setw(10) << s.id
             << setw(20) << s.name
             << setw(10) << s.age
             << setw(20) << s.course << endl;
    }
}

void searchStudent()
{
    int id;

    cout << "\nEnter Student ID: ";
    cin >> id;

    for (Student s : students)
    {
        if (s.id == id)
        {
            cout << "\nStudent Found\n";
            cout << "ID : " << s.id << endl;
            cout << "Name : " << s.name << endl;
            cout << "Age : " << s.age << endl;
            cout << "Course : " << s.course << endl;
            return;
        }
    }

    cout << "\nStudent Not Found.\n";
}

void updateStudent()
{
    int id;

    cout << "\nEnter Student ID to Update: ";
    cin >> id;

    cin.ignore();

    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].id == id)
        {
            cout << "Enter New Name: ";
            cin.getline(students[i].name, 50);

            cout << "Enter New Age: ";
            cin >> students[i].age;

            cin.ignore();

            cout << "Enter New Course: ";
            cin.getline(students[i].course, 50);

            saveData();

            cout << "\nRecord Updated Successfully.\n";
            return;
        }
    }

    cout << "\nStudent Not Found.\n";
}

void deleteStudent()
{
    int id;

    cout << "\nEnter Student ID to Delete: ";
    cin >> id;

    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].id == id)
        {
            students.erase(students.begin() + i);

            saveData();

            cout << "\nRecord Deleted Successfully.\n";
            return;
        }
    }

    cout << "\nStudent Not Found.\n";
}

int main()
{
    loadData();

    int choice;

    do
    {
        cout << "\n==============================\n";
        cout << " STUDENT MANAGEMENT SYSTEM\n";
        cout << "==============================\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
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
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice.\n";
        }

    } while (choice != 6);

    return 0;
}