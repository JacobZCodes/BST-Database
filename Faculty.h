// Jacob Zamore
// Header file for a Faculty class

#ifndef FACULTY_H
#define FACULTY_H
#include "DblList.h"
#include <string>
using namespace std;
class Faculty {
    public:
        Faculty();
        Faculty(int ID, string name, string level, string dept, DblList<int>* advisees);
        ~Faculty();
        // Getters
        int getID();
        string getName();
        string getLevel();
        string getDept();
        DblList<int>* getAdvisees();
        // Setters
        void setID(int id_num);
        void setName(string name);
        void setLevel(string level);
        void setDept(string dept);
        void setAdvisees(DblList<int>* advisees);
        void printInfo();
        string toString() const;
        
    private:
        int M_ID;
        string m_name;
        string m_level;
        string m_dept;
        DblList<int>* m_advisees;
};
#endif