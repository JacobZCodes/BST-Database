// Jacob Zamore
// Implementation file for a Faculty class
#include <sstream>
#include "Faculty.h"
Faculty::Faculty() {
    // Default professor
    M_ID = 101010101;
    m_name = "Elizabeth Stevens";
    m_level = "Professor";
    m_dept = "Fowler School of Engineering";
    m_advisees = new DblList<int>();
}

Faculty::Faculty(int ID, string name, string level, string dept, DblList<int>* advisees){
    M_ID = ID;
    m_name = name;
    m_level = level;
    m_dept = dept;
    m_advisees = advisees;
}

Faculty::~Faculty() {
    
}

// Getters
int Faculty::getID(){
    return M_ID;
}

string Faculty::getName() {
    return m_name;
}

string Faculty::getLevel() {
    return m_level;
}

string Faculty::getDept() {
    return m_dept;
}

DblList<int>* Faculty::getAdvisees() {
    return m_advisees;
}

// Setters

void Faculty::setID(int id_num) {
    M_ID = id_num;
}

void Faculty::setName(string name) {
    m_name = name;
}

void Faculty::setLevel(string level) {
    m_level = level;
}

void Faculty::setDept(string dept) {
    m_dept = dept;
}

void Faculty::setAdvisees(DblList<int>* advisees) {
    m_advisees = advisees;
}

void Faculty::printInfo() {
    cout << "~~~~~~~~ Faculty Info ~~~~~~~~~" << endl;
    cout << "ID: " << M_ID << endl;
    cout << "Name: " << m_name << endl;
    cout << "Level: " << m_level << endl;
    cout << "Dept: " << m_dept << endl;
    cout << "Advisees: "  << endl;
    m_advisees->printInfo();
}

std::string Faculty::toString() const {
    std::ostringstream oss; 
    oss << "~~~~~~~~ Faculty Info ~~~~~~~~~\n";
    oss << "ID: " << M_ID << "\n";
    oss << "Name: " << m_name << "\n";
    oss << "Level: " << m_level << "\n";
    oss << "Dept: " << m_dept << "\n";
    oss << "Advisees:\n";
    // Iterate over the linked list of advisees
    ListNode<int>* current = m_advisees->getFront();
    while (current != nullptr) {
        oss << "  " << current->m_data << "\n"; // Append each advisee ID
        current = current->m_next; // Move to the next node
    }
    return oss.str(); 
}
