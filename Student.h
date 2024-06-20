// Jacob Zamore
// Header file for a Student class
#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <sstream>
using namespace std;
class Student {
    public:
        Student();
        Student(int ID, string name, string level, string major, double gpa, int advisor);
        ~Student();
        // Getters
        int getID();
        string getName();
        string getLevel();
        string getMajor();
        double getGPA();
        int getAdvisor();
        // Setters
        void setID(int ID);
        void setName(string name);
        void setLevel(string level);
        void setMajor(string major);
        void setGPA(double gpa);
        void setAdvisor(int advisor);
        void printInfo();
        string toString() const; 
    private:
        int m_ID;
        string m_name;
        string m_level;
        string m_major;
        double m_gpa;
        int m_advisor;
};
#endif