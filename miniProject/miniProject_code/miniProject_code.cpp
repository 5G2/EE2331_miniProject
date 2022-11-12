//Authors: Ng Chi To(55742115) and Lam Chun (55237159)

#include <iostream>
#include<fstream>
#include <string>
#include<vector>
#include <regex>

using namespace std;


struct Node
{
    Node(int sidT,string majorT,double gradeT,string aTypeT, int yearT) : sid(sidT), major(majorT), grade(gradeT), aType(aTypeT),year(yearT), left(NULL), right(NULL) {}
    int sid;
    string major;
    double grade;
    string aType;
    int year;
    Node* left;
    Node* right;

};

void insert(Node* root, Node* data) {
    Node* curr = root;
    if (data->sid < root->sid) {
        if (!root->left) {
            root->left = data;
        }
        else {
            insert(root->left, data);
        }
    }
    else {
        if (!root->right) {
            root->right = data;
        }
        else {
            insert(root->right, data);
        }
    }
}


void search(Node* root, int sid) {
    if (root == NULL) {
        cout << "This ID does not exit";
        return;
    }
    else if (sid == root->sid) {
        cout << "THe student with ID "<<root->sid<<" has the following information:"<<root->major<<" "<<root->grade<<" "<<root->aType<<" "<<root->year<<endl;
    }
    else if (sid > root->sid) {
        search(root->right, sid);
    }
    else if (sid < root->sid) {
        search(root->left, sid);
    }
}


void search(Node* root) {
    int id;
    cout << "Your input is <search>. Please input the student ID";
    cin >> id;
    if (id < 1000000 || id>99999999) {
        cout << "This ID does not exist";
        return;
    }
    search(root, id);


}

void insert(Node* root) {
    int count = 0;
    char line[50];
    int sid;
    string major;
    double grade;
    string aType;
    int year;

    cin.ignore();
    cout << "Your input is <insert>. Please input the student's record";
    cin.getline(line,50);

    char sep[] = " ";
    char* tokenInBuffer=NULL;
    char* temp= strtok_s(line, sep,&tokenInBuffer);
    vector<char*> input;
    input.push_back(temp);

    while (temp!=NULL)
    {
        cout << input[0] << endl; // print the string token  
        temp = strtok_s(NULL, sep, &tokenInBuffer);
        input.push_back(temp);
        count++;
    }
    if (count != 5) {
        cout << "Wrong format"<<endl;
        return;
    }


    regex check0("(^[0-9]{8}$)");
    regex check1("(4-year)");
    regex check2("(ASI)");
    regex check3("(ASII)");
    regex check4("(^[0-9]{4}$)");
    if (!regex_search(input[0], check0)) {
        cout << "Wrong format" << endl;
        return;
    }
    if (!regex_search(input[3], check1)&& !regex_search(input[3], check2)&& !regex_search(input[3], check3)) {
        cout << "Wrong format" << endl;
        return;
    }
    if (!regex_search(input[4], check4)) {
        cout << "Wrong format" << endl;
        return;
    }

    sid = atoi(input[0]);
    major = input[1];
    grade = stod(input[2]);
    aType = input[3];
    year = atoi(input[4]);

    if (sid < 1000000 || sid>99999999) {
        cout << "Wrong format" << endl;
        return;
    }

    Node* tempNode = new Node(sid, major, grade, aType, year);
    insert(root, tempNode);


}
void deletion(Node* root) {
    int sid;
    cout << "Your input is <delete>. Please input the student ID";
    cin >> sid;
    if (root == NULL) {
        cout << "This ID does not exit";
        return;
    }
    else if (sid == root->sid) {
        root->aType = "";
        root->grade = NULL;
        root->major = "";
        root->sid = NULL;
        root->year = NULL;
        cout << "The student with ID " << sid << " is deleted"<<endl;
    }
    else if (sid > root->sid) {
        search(root->right, sid);
    }
    else if (sid < root->sid) {
        search(root->left, sid);
    }
}
int main()
{
    string fileName;
    cout << "Please input the file name: " << endl;
    cin >> fileName;
    ifstream fin(fileName);
    if (!fin) {
        cout << "Can't open the file!" << endl;
        return 0;
    }
    int sid;
    string major;
    double grade;
    string aType;
    int year;

    fin >> sid;
    fin >> major;
    fin >> grade;
    fin >> aType;
    fin >> year;
    Node* root = new Node(sid, major, grade, aType, year);
    while (fin >> sid && !fin.eof()) {
        fin >> major;
        fin >> grade;
        fin >> aType;
        fin >> year;
        Node* temp = new Node(sid, major, grade, aType, year);
        insert(root, temp);
    }
    int input = 0;
    while (input != 4) {
        cout << "*****Please inputone of the following operations: serach, insert, delete, over*****";
        cin >> input;
        switch (input) {
        case 1:
            search(root);
            break;
        case 2: 
            insert(root);
            break;
        case 3:
            deletion(root);
            break;
        case 4: 
            break;
        }
    
    
    }


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
