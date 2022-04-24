#include <iostream>
#include <fstream>
#include <vector>
//Maya Neely

using namespace std;

//Define Course
struct Course{
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

//Split string into list of strings
vector<string> splitstring(string s, string del = " ") {
    vector<string> tokens;
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        tokens.push_back(s.substr (start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    tokens.push_back(s.substr(start, end - start));
    return tokens;
}

//Function to Load data structure
vector<Course>LoadDataStructure() {
    //Open file
    ifstream fin("abcu.txt", ios::in);

    vector<Course> courses;
    string line;

    while(1) {
        getline(fin,line);
        //if end of file reached
        if(line=="-1") {
            break;
        }
        Course course;

        //Get token data seperated by commas
        vector<string>tokenData=splitstring(line, ",");

        //Store information on the course structure
        course.courseNumber=tokenData[0];
        course.name=tokenData[1];

        //For classes with prerequisties
        for(int i=2; i<tokenData.size(); i++) {
            course.prerequisites.push_back(tokenData[i]);
        }
        //append course to list of courses
        courses.push_back(course);
    }
    //close file
    fin.close();
    return courses;
}
//Print course information
void printCourse(Course course) {
    string courseNumber = course.courseNumber;
    string name = course.name;
    vector<string>prerequisites = course.prerequisites;
    cout << courseNumber << ", " << name << endl;
    for(int i=0; i < prerequisites.size(); i++) {
        cout << prerequisites[i] << " " << endl;
    }
}
//Print course List
void printCourseList(vector<Course> courses) {
    int n = courses.size();

    //Sort list
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(courses[j].courseNumber > courses[j+1].courseNumber) {
                swap(courses[j+1], courses[j]);
            }
        }
    }
    //Traverse course to print
    for(int i=0; i<n; i++) {
        printCourse(courses[i]);
    }
}
//Search for course number
void searchCourse(vector<Course> courses) {
    int n = courses.size();
    string courseNumber;
    int m = 0;

    //Get user input
    cout << "What course do you want to know about?";
    cin >> courseNumber;

    for(int i=0; i<n; i++) {
        //If course is found
        if(courses[i].courseNumber == courseNumber) {
            m=1;
            //print course
            printCourse(courses[i]);
            break;
        }
    }
    //If course not found
    if(m==0) {
        //Print error message
        cout << "That is not a valid input." << endl;
    }
}
int main(int argc, char **argv) {
    vector<Course> courses;

    //Print menu
    cout << "Welcome to the course planner.\n\n";
    cout << "1. Load Data Structure.\n";
    cout << "2. Print Course List.\n";
    cout << "3. Print Course.\n";
    cout << "4. Exit\n";

    int choice;
    do{
        //Get user input
        cout << "What would you like to do? ";
        cin >> choice;

        //Switch statement
        switch(choice) {
            case 1: courses = LoadDataStructure();
            break;

            case 2: printCourseList(courses);
            break;

            case 3: searchCourse(courses);
            break;

            case 4: cout << "Thank you for using the course planner!" << endl;
            break;

            default: cout << choice << " is not a valid option." << endl;
        }
    }
    while(choice != 4);
        return 0;
    
}