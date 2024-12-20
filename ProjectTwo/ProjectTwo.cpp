//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Tremaine Rayner
// Version     : 1.0
// Description : 7-1 Submit Project Two
// Date        : 12/15/2024
//============================================================================


#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Define a structure for a Course
struct Course {
    string number; // Course number
    string name; // Course name
    vector<string> prerequisites; // List of prerequisite courses
};

// Data structure to store courses
unordered_map<string, Course> courseTable; // Stores courses using course number as key
vector<Course> sortedCourses; // Vector to store courses in sorted order

// Function prototypes
void printMenu(); // Function to print the menu
bool loadCoursesFromFile(const string& fileName); // Function to load courses from a file
Course parseCourseLine(const string& line); // Function to parse a line of course data
void sortCourses(); // Function to sort courses alphanumerically
void printAllCourses(); // Function to print all courses
void searchCourse(const string& courseNumber); // Function to search for a specific course

int main() {
    string fileName;
    int choice;

    cout << "Welcome to the Course Management System!" << endl;

    while (true) {
        printMenu(); // Menu is displayed
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            // Input validation to handle non-integer inputs
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            // Option to load data into the data structure
            cout << "Please enter the file name containing course data: ";
            cin >> fileName;
            if (!loadCoursesFromFile(fileName)) {
                cout << "Error loading file. Please try again." << endl;
            }
            else {
                cout << "File loaded successfully!" << endl;
            }
            break;
        case 2:
            // Option to display all courses
            printAllCourses();
            break;
        case 3: {
            // Option to search for a specific course
            string courseNumber;
            cout << "Enter the course number to search: ";
            cin >> courseNumber;
            searchCourse(courseNumber);
            break;
        }
        case 9:
            // Option to exit the program
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

void printMenu() {
    // Function to print the menu options
    cout << "\nMenu:" << endl;
    cout << "1. Load data into the data structure" << endl;
    cout << "2. Display all courses" << endl;
    cout << "3. Search for a specific course" << endl;
    cout << "9. Exit" << endl;
}

bool loadCoursesFromFile(const string& fileName) {
    // Function to load courses from a file
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: File cannot be opened." << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        Course course = parseCourseLine(line); // Parse each line into a Course object
        courseTable[course.number] = course; // Store the course in the global course table
    }

    file.close();
    return true;
}

Course parseCourseLine(const string& line) {
    // Function to parse a line of course data into a Course object
    stringstream ss(line);
    string courseNumber, courseName, prereq;

    getline(ss, courseNumber, ',');
    getline(ss, courseName, ',');

    Course course;
    course.number = courseNumber;
    course.name = courseName;

    while (getline(ss, prereq, ',')) {
        course.prerequisites.push_back(prereq); // Add prerequisites to the course
    }

    return course;
}

void sortCourses() {
    // Function to sort courses alphanumerically
    sortedCourses.clear();
    for (const auto& pair : courseTable) {
        sortedCourses.push_back(pair.second); // Add courses to the sortedCourses vector
    }

    sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& a, const Course& b) {
        return a.number < b.number; // Sort courses by course number
        });
}

void printAllCourses() {
    // Function to print all courses
    if (courseTable.empty()) {
        cout << "No courses available." << endl;
        return;
    }

    sortCourses(); // Sort the courses before printing

    for (const auto& course : sortedCourses) {
        cout << "Course Number: " << course.number << endl;
        cout << "Course Name: " << course.name << endl;
        if (course.prerequisites.empty()) {
            cout << "Prerequisites: None" << endl;
        }
        else {
            cout << "Prerequisites: ";
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                cout << course.prerequisites[i];
                if (i < course.prerequisites.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        cout << "-----------------------------------" << endl;
    }
}

void searchCourse(const string& courseNumber) {
    // Function to search for a specific course
    auto it = courseTable.find(courseNumber);
    if (it == courseTable.end()) {
        cout << "Error: Course " << courseNumber << " not found." << endl;
        return;
    }

    const Course& course = it->second;
    cout << "Course Number: " << course.number << endl;
    cout << "Course Name: " << course.name << endl;
    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}
