// Jacob Zamore
// Implementation file for a Student class

#include "Student.h"
#include <iostream>
#include <sstream>
Student::Student() {
    // Default student will be me
    m_ID = 2423782;
    m_name = "Jacob Zamore";
    m_level = "Sophomore";
    m_major = "Software Engineering";
    m_gpa = 3.7;
    m_advisor = 1234567;
}

Student::Student(int ID, string name, string level, string major, double gpa, int advisor) {
    m_ID = ID;
    m_name = name;
    m_level = level;
    m_major = major;
    m_gpa = gpa;
    m_advisor = advisor;
}

Student::~Student() {
    
}

// Getters
int Student::getID(){
    return m_ID;
}

string Student::getName() {
    return m_name;
}

string Student::getLevel() {
    return m_level;
}

string Student::getMajor() {
    return m_major;
}

double Student::getGPA() {
    return m_gpa;
}

int Student::getAdvisor() {
    return m_advisor;
}

// Setters

void Student::setID(int ID) {
    m_ID = ID;
}

void Student::setName(string name) {
    m_name = name;
}

void Student::setLevel(string level) {
    m_level = level;
}

void Student::setMajor(string major) {
    m_major = major;
}

void Student::setGPA(double gpa) {
    m_gpa = gpa;
}

void Student::setAdvisor(int advisor) {
    m_advisor = advisor;
}

void Student::printInfo() {
    cout << "~~~~~~~~ Student Info ~~~~~~~~~" << endl;
    cout << "ID: " << m_ID << endl;
    cout << "Name: " << m_name << endl;
    cout << "Level: " << m_level << endl;
    cout << "Major: " << m_major << endl;
    cout << "GPA: " << m_gpa << endl;
    cout << "Advisor ID: " << m_advisor << endl;

}

std::string Student::toString() const {
    std::ostringstream oss; 
    oss << "~~~~~~~~ Student Info ~~~~~~~~~\n";
    oss << "ID: " << m_ID << "\n";
    oss << "Name: " << m_name << "\n";
    oss << "Level: " << m_level << "\n";
    oss << "Major: " << m_major << "\n";
    oss << "GPA: " << m_gpa << "\n";
    oss << "Advisor ID: " << m_advisor << "\n";
    return oss.str(); 
}
