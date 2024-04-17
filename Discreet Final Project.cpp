#include<iostream>
#include<string>
using namespace std;
class SET {
public:
    class Node {
    public:
        string data;
        Node* next;
        Node(string value) {
            data = value;
            next = NULL;
        }
    };
    Node* head;
public:
    SET() {
        head = NULL;
    }
    void insert(string value) {
        Node* n = new Node(value);
        Node* temp = head;
        if (head == NULL) {
            head = n;
        }
        else {
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = n;
        }
        return;
    }
    int countSetElements() {
        int mycount = 0;
        Node* temp = head;
        while (temp != NULL) {
            mycount = mycount + 1;
            temp = temp->next;
        }
        return mycount;
    }
    void displaySET() {
        Node* temp = head;
        cout << "{";
        while (temp != NULL) {
            cout << temp->data << ",";
            temp = temp->next;
        }
        cout << "}";
        cout << endl;
    }
};

class Relation {
public:
    class Node {
    public:
        string first;
        string second;
        Node* next;
        Node(string f, string s) {
            first = f;
            second = s;
            next = NULL;
        }
    };
    Node* head;
public:
    Relation() {
        head = NULL;
    }
    void insertR(string a, string b)
    {
        Node* n = new Node(a, b);
        if (head == NULL)
        {
            head = n;
            return;
        }
        Node* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = n;
    }

    void makingRelation(SET& A, SET& B) {
        Node* temp = head;
        SET::Node* tempA = A.head;
        SET::Node* tempB = B.head;
        while (tempA != NULL) {
            while (tempB != NULL) {
                Node* n = new Node(tempA->data, tempB->data);
                if (head == NULL) {
                    head = n;
                    temp = head;
                }
                else {
                    temp->next = n;
                    temp = temp->next;
                }
                tempB = tempB->next;
            }
            tempA = tempA->next;
            tempB = B.head;
        }
    }

    void displayRelation(int num) {
        Node* temp = head;
        int count = 0;
        cout << "{";
        while (temp != NULL) {
            count++;
            cout << "(" << temp->first << "," << temp->second << ") ";
            if (count == num) {
                cout << endl;
                count = 0;
            }
            temp = temp->next;
        }
        cout << "}";
        cout << endl;
    }

    int countNodes()
    {
        Node* temp = head;
        int count = 0;
        while (temp != NULL)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }
};
//here are our functions
//number of relations
void NumberOfRelations(int A, int B) {//1
    cout << "Number of Relations are :" << pow(2, A * B);
    cout << endl;
}
Relation checkReflexive(Relation R, SET A, SET B) {
    bool condition = false;
    int count = 0;
    Relation tempR;
    tempR.head = R.head;
    SET tempA;
    tempA.head = A.head;
    SET tempB;
    tempB.head = B.head;

    Relation whyNotTemp, reflexive;
    cout << "Reflexive in Set A: {";
    while (tempA.head != NULL) {
        condition = false;
        tempR.head = R.head;

        while (tempR.head != NULL) {
            if (tempR.head->first == tempA.head->data && tempR.head->second == tempA.head->data) {
                count++;
                cout << "(" << tempR.head->first << "," << tempR.head->second << "),";
                reflexive.insertR(tempR.head->first, tempR.head->second);
                condition = true;
            }
            tempR.head = tempR.head->next;
        }

        if (condition == false)
            whyNotTemp.insertR(tempA.head->data, tempA.head->data);
        tempA.head = tempA.head->next;
    }

    while (tempB.head != NULL) {
        condition = false;
        tempR.head = R.head;

        while (tempR.head != NULL) {
            if (tempR.head->first == tempB.head->data && tempR.head->second == tempB.head->data) {
                count++;
                cout << "(" << tempR.head->first << "," << tempR.head->second << "),";
                condition = true;
            }
            tempR.head = tempR.head->next;
        }

        if (condition == false)
            whyNotTemp.insertR(tempB.head->data, tempB.head->data);
        tempB.head = tempB.head->next;
    }
    cout << "}";
    if (whyNotTemp.head != NULL)
    {
        cout << "\nNot Reflexive because these pairs are missing: ";
        whyNotTemp.displayRelation(10);
        cout << endl;
        return whyNotTemp;
    }
    else {
        cout << "\nOur Relation is Reflexive." << endl;
        return whyNotTemp;
    }
}
Relation checkSymmetricRelations(Relation R) {
    Relation tempR;
    tempR.head = R.head;
    Relation tempR2;
    tempR2.head = R.head;
    Relation whyNotTemp;
    Relation symmetric;
    bool condition = false;

    while (tempR.head != NULL) {
        condition = false;
        while (tempR2.head != NULL) {
            if (tempR.head->first == tempR2.head->second && tempR.head->second == tempR2.head->first) {
                condition = true;
                symmetric.insertR(tempR.head->first, tempR.head->second);
                symmetric.insertR(tempR.head->second, tempR.head->first);
                break;
            }
            tempR2.head = tempR2.head->next;
        }

        if (condition == false) {
            whyNotTemp.insertR(tempR.head->second, tempR.head->first);
        }

        tempR.head = tempR.head->next;
        tempR2.head = R.head;
    }

    if (whyNotTemp.head != NULL) {
        cout << "\nNot Symmetric because these pairs are missing: ";
        whyNotTemp.displayRelation(10);
        cout << endl;
        return whyNotTemp;
    }
    else {
        cout << "\nOur Relation is Symmetric.";
        symmetric.displayRelation(10);
        cout << endl;
        return whyNotTemp;
    }
}

bool checkAntiSymmetricRelation(Relation& R) {
    Relation anti_symmetric;
    Relation::Node* tempR = R.head;

    while (tempR != NULL) {
        bool condition = true;
        Relation::Node* tempR2 = R.head;

        while (tempR2 != NULL) {
            if (tempR->first == tempR2->second && tempR->second == tempR2->first) {
                if (tempR->first != tempR->second) {
                    return false;
                }
            }
            tempR2 = tempR2->next;
        }
        tempR = tempR->next;
    }

    return true;
}
int main()
{
    SET setA, setB;
    //For set A insertion and assign
    int c;
    do {
        cout << "How many Elements u wanna Enter in set A (Minimum 3) : ";
        cin >> c;
    } while (c < 3);
    string* temp = new string[c];
    for (int i = 0; i < c; i++)
    {
        cout << "Input Element number " << i + 1 << " in set A :";
        cin >> temp[i];
    }
    for (int i = 0; i < c; i++) {
        setA.insert(temp[i]);
    }
    cout << "A=";
    setA.displaySET();
    //For set B insertion and assign
    c = 0;
    do {
        cout << "How many Elements u wanna Enter in set B (Minimum 3) : ";
        cin >> c;
    } while (c < 3);
    string *temp2 = new string[c];
    for (int i = 0; i < c; i++)
    {
        cout << "Input Element number " << i + 1 << " in set B :";
        cin >> temp2[i];
    }
 
    for (int i = 0; i < c; i++) {
        setB.insert(temp2[i]);
    }
    cout << "B=";
    setB.displaySET();
    //other parts
    Relation R, checksymmetric, checkantisymmetric, checkreflexive;
    R.makingRelation(setA, setB);
    R.displayRelation(3);
    int choice;
    bool condition = 0;
    do {
        cout << "\n\nMenu:\n";
        cout << "1. Total number of relations\n";
        cout << "2. Reflexive Relations\n";
        cout << "3. Symmetric Relations\n";
        cout << "4. Anti-Symmetric Relations\n";
        cout << "5. Both Reflexive and Symmetric Relations\n";
        cout << "6. Both Symmetric and Anti-symmetric Relations\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            NumberOfRelations(setA.countSetElements(), setB.countSetElements());
            break;
        case 2:
            checkreflexive = checkReflexive(R, setA, setB);
            break;
        case 3:
            checksymmetric = checkSymmetricRelations(R);
            break;
        case 4:
            if (condition = checkAntiSymmetricRelation(R)) {
                cout << "Yes Our Relation is Anti Symmetric.\n";
            }
            else {
                cout << "No ! Our Relation is Not Anti Symmetric.\n";
            }
            break;
        case 5:
            checkreflexive = checkReflexive(R, setA, setB);
            checksymmetric = checkSymmetricRelations(R);
            if (checkreflexive.head == NULL && checksymmetric.head == NULL) {
                cout << "Given Relations are BOTH REFLEXIVE AND SYMMETRIC" << endl;
            }
            else {
                cout << "Reflexive and Symmetric Conditions not met" << endl;
            }
            break;
        case 6:
            checksymmetric = checkSymmetricRelations(R);
            condition= checkAntiSymmetricRelation(R);
            if (checksymmetric.head == NULL && condition==true) {
                cout << "Given Relations are BOTH ANTI-SYMMETRIC AND SYMMETRIC" << endl;
            }
            else {
                cout << "Anti-Symmetric and Symmetric Conditions not met" << endl;
            }
            break;
        case 7:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 7);

    return 0;
}