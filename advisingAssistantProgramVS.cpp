#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

// implement a binary search tree
class BinarySearchTree {
private:
    Node* root;
    void addNode(Node* node, Course course);
    void inOrder(Node* node);
public :
    BinarySearchTree();
    void InOrder();
    void Insert(Course course);
    Course Search(string courseNumber);
};

// Default constructor
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}
void BinarySearchTree::InOrder() {
    this->inOrder(root);
}

//Insert a course
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        this->addNode(root, course);
    }
}
// Search for a course
Course BinarySearchTree::Search(string courseNumber) {
    Node* currentNode = root;
    while (currentNode != nullptr) {
        // if a match is found return current course
        if (currentNode->course.courseNumber == courseNumber) {
            return currentNode->course;
        }
        else if (currentNode->course.courseNumber > courseNumber) {
            // traverse the left side
            currentNode = currentNode->left;
        }
        else {
            //traverse the right side
            currentNode = currentNode->right;
        }
    }
    Course course;
    return course;
}
// add course
void BinarySearchTree::addNode(Node* node, Course course) {
    //if the node is larger add to the left
    if (course.courseNumber < node->course.courseNumber) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            //recurse down left node
            this->addNode(node->left, course);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            this->addNode(node->right, course);
        }
    }
}
void displayCourse(Course course) {
    cout << course.courseNumber << ", " << course.courseTitle;
    if (course.prerequisites.empty()) {
        cout << "";
    }
    else {
        for (const auto& prerequisites : course.prerequisites) {
            cout << prerequisites << ", ";
        }
    }
}
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->course.courseNumber << ", "
            << node->course.courseTitle;
        if (node->course.prerequisites.size() > 0) {
            cout << ", ";
            for (const auto& prerequisites : node->course.prerequisites) {
                cout << prerequisites << ", ";
            }
        }
        inOrder(node->right);
    }
}

// load data structure with csv file
void loadBinarySearchTree(const string& fileName, BinarySearchTree* bst) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "File cannot be opened: " << fileName << endl;
        return;
    }
    string fileLine;
    while (getline(file,fileLine)) {
        Course course;
        size_t pos = fileLine.find(",");
        course.courseNumber = fileLine.substr(0, pos);
        fileLine.erase(0, pos + 1);
        pos = fileLine.find(",");
        course.courseTitle = fileLine.substr(0, pos);
        fileLine.erase(0, pos + 1);
        while (!fileLine.empty()) {
            string prereq;
            pos = fileLine.find(",");
            prereq = fileLine.substr(0, pos);
            course.prerequisites.push_back(prereq);
            if (pos == string::npos) break;
            fileLine.erase(0, pos + 1);
        }

        bst->Insert(course);
    }
    file.close();
}

int main()
{
    string fileName;
    int userChoice = 0;
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;
    string courseNumber;

    cout << "Welcome to the course planner" << endl;
    while (userChoice != 9) {
        cout << "   1. Load Data Structure" << endl;
        cout << "   2. Print Course List" << endl;
        cout << "   3. Print A Course" << endl;
        cout << "   9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do?" << endl;
        cin >> userChoice;

        switch (userChoice) {
        case 1:
            cout << "Please Enter a File Name: " << endl;
            cin >> fileName;
            cout << "Loading courses..." << endl;
            loadBinarySearchTree(fileName, bst);
            break;
        case 2:
            bst->InOrder();
            break;

        case 3:
            cout << "What course do you want to know about?" << endl;
            cin >> courseNumber;
            course = bst->Search(courseNumber);
            if (!course.courseNumber.empty()) {
                displayCourse(course);
            }
            else {
                cout << "Course number " << courseNumber << " not found..." << endl;
            }
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;

        default:
            cout << userChoice << " is not a valid option" << endl;

        }

    return 0;

    }

}
