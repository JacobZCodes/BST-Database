// Jacob Zamore
// Driver file that implements LazyBST into a database mgmt system
#include "LazyBST.h"
#include "Student.h"
#include <iostream>
#include <typeinfo>
#include <fstream>
using namespace std;
int main() {
    // Populate studentTable
    LazyBST<Student*> studentTable;
    Student* student1 = new Student(8743562, "Alice", "Junior", "Computer Science", 3.9, 8274615); 
    Student* student2 = new Student(5467890, "Bob", "Sophomore", "Engineering", 3.5, 8274615);
    Student* student3 = new Student(1234789, "Charlie", "Senior", "Mathematics", 3.8, 3492867);
    Student* student4 = new Student(9876543, "David", "Freshman", "Biology", 3.2, 3492867);
    Student* student5 = new Student(2345678, "Eva", "Junior", "History", 3.6, 5729384);
    Student* student6 = new Student(8901234, "Frank", "Senior", "Psychology", 3.7, 5729384);
    Student* student7 = new Student(5432109, "Grace", "Sophomore", "Chemistry", 3.6, 6842091);
    Student* student8 = new Student(6472109, "Henry", "Junior", "Physics", 3.8, 6842091);

    studentTable.insert(student1);
    studentTable.insert(student2);
    studentTable.insert(student3);
    studentTable.insert(student4);
    studentTable.insert(student5);
    studentTable.insert(student6);
    // Populate facultyTable
    LazyBST<Faculty*> facultyTable;
    DblList<int>* advisees1 = new DblList<int>();
    DblList<int>* advisees2 = new DblList<int>();
    DblList<int>* advisees3 = new DblList<int>();
    DblList<int>* advisees4 = new DblList<int>();
    // Update advisees list which will auto-sort based on ascending ID
    advisees1->addFront(student1->getID());
    advisees1->addFront(student2->getID());
    advisees2->addFront(student3->getID());
    advisees2->addFront(student4->getID());
    advisees3->addFront(student5->getID());
    advisees3->addFront(student6->getID());
    advisees4->addFront(student7->getID());
    advisees4->addFront(student8->getID());

    Faculty* faculty1 = new Faculty(8274615, "Dr. Smith", "Professor", "Computer Science", advisees1);
    Faculty* faculty2 = new Faculty(3492867, "Dr. Johnson", "Associate Professor", "Engineering", advisees2);
    Faculty* faculty3 = new Faculty(5729384, "Dr. Davis", "Professor", "Mathematics", advisees3);
    Faculty* faculty4 = new Faculty(6842091, "Dr. Wilson", "Assistant Professor", "Biology", advisees4);

    facultyTable.insert(faculty2);
    facultyTable.insert(faculty3);
    facultyTable.insert(faculty4);
    facultyTable.insert(faculty1);

    // Declarations must be made outside of switch cases to appease compiler
    int choice;
    int stuID;
    int facID;
    int id;
    string name;
    string level;
    string major;
    string dept;
    double gpa;
    int advisorID;
    int studentToUpdate;
    int newAdvisor;

    do {
        // Display the menu
        cout << "Menu:" << endl;
        cout << "1. Print students" << endl;
        cout << "2. Print faculty" << endl;
        cout << "3. Get Student (ID)" << endl;
        cout << "4. Get Faculty (ID)" << endl;
        cout << "5. Add Student" << endl;
        cout << "6. Delete Student (ID)" << endl;
        cout << "7. Add Faculty" << endl;
        cout << "8. Delete Faculty (ID)" << endl;
        cout << "9. Change a student’s advisor given the student id and the new faculty id" << endl;
        cout << "10. Remove an advisee from a faculty member given the ids" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your choice (1-11): ";
        // More declarations outside switch cases
        IDQueue<Student*> studentIDs(true);
        TreeNode<Student*>* studentNode;
        TreeNode<Student*>* targetStudentNode;
        Student* defaultStudent = new Student();

        IDQueue<Faculty*> facultyIDs(true);
        TreeNode<Faculty*>* facultyNode;
        TreeNode<Faculty*>* targetFacultyNode;
        Faculty* defaultFaculty = new Faculty();

        int newAdvisor;
        int oldAdvisor;
        TreeNode<Faculty*>* newFacultyAdvisor;
        bool found = false;


        // Read user choice
        cin >> choice;

        
        switch (choice) {
            case 1:
                // Print students
                while (!studentTable.getNodes()->isEmpty()) {
                    studentNode = studentTable.getNodes()->remove();
                    studentNode->getData()->printInfo();
                    studentIDs.add(studentNode);
                }
                while (!studentIDs.isEmpty()) {
                    studentTable.getNodes()->add(studentIDs.remove());
                }
                break;
            case 2:
                // Print faculty
                while (!facultyTable.getNodes()->isEmpty()) {
                    facultyNode = facultyTable.getNodes()->remove();
                    facultyNode->getData()->printInfo();
                    facultyIDs.add(facultyNode);
                }
                while (!facultyIDs.isEmpty()) {
                    facultyTable.getNodes()->add(facultyIDs.remove());
                }
                break;
            case 3:
                // Find and display student information given id
                cout << "Find Student by ID: " << endl;
                cin >> stuID;
                if (!studentTable.getNodes()->contains(stuID)) {
                    cerr << "ERROR: Could not find this student" << endl;
                }
                else {
                studentNode = studentTable.getNodeGivenID(stuID);
                studentNode->getData()->printInfo();
                }
                break;
            case 4:
                // Find and display faculty information given id
                cout << "Find Faculty by ID: " << endl;
                cin >> facID;
                if (!facultyTable.getNodes()->contains(facID)) {
                    cerr << "ERROR: Could not find this faculty" << endl;
                }
                else {
                facultyNode = facultyTable.getNodeGivenID(facID);
                facultyNode->getData()->printInfo();
                }
                break;
            case 5:
                // Add student
                studentNode = new TreeNode<Student*>(defaultStudent);
                cout << "Student ID: " << endl;
                cin >> id;
                if (studentTable.getNodes()->contains(id)) {
                    cerr << "ERROR: This student already exists" << endl;
                    break;
                    
                }
                else {
                cout << "Student Name: " << endl;
                cin.ignore(); // Add this line to clear the newline character
                getline(cin, name);

                cout << "Student Level: " << endl;
                getline(cin, level);

                cout << "Student Major: " << endl;
                getline(cin, major);

                cout << "Student GPA: " << endl;
                cin >> gpa;

                cout << "Student's Advisor ID: " << endl;
                cin >> advisorID;
                }
                if (!facultyTable.getNodes()->contains(advisorID)) {
                    cerr << "ERROR: This advisor does not exist." << endl;
                }
                else {
                studentNode->getData()->setAdvisor(advisorID);
                studentNode->getData()->setID(id);
                studentNode->getData()->setName(name);
                studentNode->getData()->setLevel(level);
                studentNode->getData()->setMajor(major);
                studentNode->getData()->setGPA(gpa);
                studentNode->getData()->printInfo();
                studentTable.insert(studentNode->getData());
                facultyNode = facultyTable.getNodeGivenID(advisorID);
                facultyNode->getData()->getAdvisees()->addFront(id);
                }
                break;
            case 6:
                // Delete a student given id
                cout << "Student to Delete (ID): " << endl;
                cin >> stuID;
                if (!studentTable.getNodes()->contains(stuID)) {
                    cerr << "ERROR: This student does not exist" << endl;
                }
                else {
                while (!studentTable.getNodes()->isEmpty()) {
                    studentNode = studentTable.getNodes()->remove();
                    if (stuID == studentNode->getData()->getID()) {
                        targetStudentNode = studentNode;
                    }
                    studentIDs.add(studentNode);
                }
                while (!studentIDs.isEmpty()) {
                    studentTable.getNodes()->add(studentIDs.remove());
                }
                advisorID = targetStudentNode->getData()->getAdvisor();
                facultyNode = facultyTable.getNodeGivenID(advisorID);
                facultyNode->getData()->getAdvisees()->removeByValue(stuID);
                studentTable.remove(targetStudentNode->getData());
                }
                break;
            case 7:
                // Add faculty
                facultyNode = new TreeNode<Faculty*>(defaultFaculty);
                cout << "Faculty ID: " << endl;
                cin >> id;
                if (facultyTable.getNodes()->contains(id)) {
                    cerr << "ERROR: This faculty already exists" << endl;
                    break;
                }
                facultyNode->getData()->setID(id);

                cout << "Faculty Name: " << endl;
                cin.ignore(); // Add this line to clear the newline character
                getline(cin, name);
                facultyNode->getData()->setName(name);

                cout << "Faculty Level: " << endl;
                getline(cin, level);
                facultyNode->getData()->setLevel(level);

                cout << "Faculty Dept: " << endl;
                getline(cin, dept);
                facultyNode->getData()->setDept(dept);
                facultyTable.insert(facultyNode->getData());


                break;
            case 8:
                // Delete a faculty member given id
                cout << "Faculty Member to Delete (ID): " << endl;
                cin >> facID;
                if (!facultyTable.getNodes()->contains(facID)) {
                    cerr << "ERROR: This faculty does not exist" << endl;
                    break;
                }
                facultyNode = facultyTable.getNodeGivenID(facID);
                while (!facultyNode->getData()->getAdvisees()->isEmpty()) {
                    studentNode = studentTable.getNodeGivenID(facultyNode->getData()->getAdvisees()->removeFront());
                    studentNode->getData()->setAdvisor(0);
                }
                facultyTable.remove(facultyNode->getData());
                break;
            case 9:
                // Change a student’s advisor given stu-id + new fac id
                // We need to remove the student from their current advisor's advisees linked list, add them to their new advisor's advisees,
                // and finally update the value of the student's m_advisor
                cout << "Student to Update (ID): " << endl;
                cin >> stuID;
                if (!studentTable.getNodes()->contains(stuID)) {
                    cerr << "ERROR: Student not found" << endl;
                    break;
                }
                cout << "New Advisor ID: " << endl;
                cin >> newAdvisor;
                if (!facultyTable.getNodes()->contains(newAdvisor)) {
                    cerr << "ERROR: Advisor not found" << endl;
                    break;
                }
                // Grab the student object via their ID
                studentNode = studentTable.getNodeGivenID(stuID);
                oldAdvisor = studentNode->getData()->getAdvisor();
                // Grab the faculty member via the newly found advisor ID
                facultyNode = facultyTable.getNodeGivenID(oldAdvisor);
                // Remove the student's ID from facultyNode's advisees
                facultyNode->getData()->getAdvisees()->removeByValue(stuID);
                // Add student's ID to newAdvisor's linked list
                newFacultyAdvisor = facultyTable.getNodeGivenID(newAdvisor);
                newFacultyAdvisor->getData()->getAdvisees()->addFront(stuID);
                break;
            case 10:
                // Remove an advisee from a faculty member given stu and fac id
                cout << "Advisor: " << endl;
                cin >> facID;
                if (!facultyTable.getNodes()->contains(facID)) {
                    cerr << "ERROR: Advisor not found" << endl;
                    break;
                }
                cout << "Student to Remove: " << endl;
                cin >> stuID;
                if (!studentTable.getNodes()->contains(stuID)) {
                    cerr << "ERROR: Student not found" << endl;
                    break;
                }
                facultyNode = facultyTable.getNodeGivenID(facID);         
                facultyNode->getData()->getAdvisees()->removeByValue(stuID);
                studentNode = studentTable.getNodeGivenID(stuID);
                studentNode->getData()->setAdvisor(0);
                facultyNode->getData()->printInfo();
                break;
case 11: {
    cout << "Exiting the program and saving logs to runLog.txt." << endl;

    // Open a file stream to write
    ofstream outFile("runLog.txt");

    // Check if the file stream is open
    if (outFile.is_open()) {
        // Write student information to the file
        outFile << "Student Information:" << endl;
        while (!studentTable.getNodes()->isEmpty()) {
            studentNode = studentTable.getNodes()->remove();
            outFile << studentNode->getData()->toString() << endl;
            studentIDs.add(studentNode);
        }
        while (!studentIDs.isEmpty()) {
            studentTable.getNodes()->add(studentIDs.remove());
        }

        outFile << "\n---------------------------------\n";

        // Write faculty information to the file
        outFile << "Faculty Information:" << endl;
        while (!facultyTable.getNodes()->isEmpty()) {
            facultyNode = facultyTable.getNodes()->remove();
            outFile << facultyNode->getData()->toString() << endl;
            facultyIDs.add(facultyNode);
        }
        while (!facultyIDs.isEmpty()) {
            facultyTable.getNodes()->add(facultyIDs.remove());
        }

        // Close the file stream
        outFile.close();
    } else {
        cerr << "ERROR: Unable to open file runLog.txt" << endl;
    }
    break;
}
            default:
                cout << "Invalid choice. Please enter a valid option (1-11)." << endl;
                break;
        }
    } while (choice != 11);
    return 0;
}