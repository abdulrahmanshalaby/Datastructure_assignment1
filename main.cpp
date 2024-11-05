#include <iostream>
using namespace std;

class Student{
public:
    string Name;
    int ID;
    float GPA;

};
class IntNode{
public:
    Student Info;
    IntNode* next;
public:
    IntNode( Student item, IntNode *next=0) : Info(item), next(next) {}

    ~IntNode() {
delete next;
    }
};

class StudentList{
    IntNode* Head,*Tail;

public:
    StudentList(){Head=Tail=nullptr;}
    ~StudentList(){delete Head;delete Tail;}
    void Insertion(Student Item) {
        if (!Head || Item.ID < Head->Info.ID) {
            IntNode* node = new IntNode(Item);
            node->next = Head;
            Head = node;
            if (!Tail) {
                Tail = node; // Set Tail if the list was previously empty
            }
        }
        else {
            IntNode* current = Head;
            while (current->next && Item.ID > current->next->Info.ID) {
                current = current->next;
            }
            auto* n = new IntNode(Item);
            n->next = current->next;
            current->next = n;
            if (!n->next) {
                Tail = n; // Update Tail if we inserted at the end
            }
        }
    }

    void Display() {
        IntNode* ptr = Head;
        int count = 1;

        cout << "Student List:\n";
        while (ptr) {
            cout << count << ". "
                 << "Name: " << ptr->Info.Name << "   "
                 << "GPA: " << ptr->Info.GPA << endl;
            ptr = ptr->next;
            count++;
        }
    }

    void Deletation(int Id) {
        if (!Head) return; // Handle empty list

        // Case 1: Deleting nodes with the head matching the Id
        while (Head && Head->Info.ID == Id) {
            Head = Head->next; // Move Head to the next node
             // Free memory
        }

        // If the list is empty after deleting head nodes, update Tail
        if (!Head) {
            Tail = nullptr; // List becomes empty, update Tail
            return; // Exit if the list is empty
        }

        // Case 2: Deleting nodes other than the head
        IntNode* current = Head;

        while (current->next) {
            if (current->next->Info.ID == Id) {
                IntNode* toDelete = current->next;
                current->next = toDelete->next; // Bypass the node to delete
                delete toDelete; // Free memory

                // Check if we are deleting the last node
                if (!current->next) {
                    Tail = current; // Update Tail if we deleted the last node
                }
            } else {
                current = current->next; // Only move to the next node if we didn't delete
            }
        }
    }

    void SearchAndPrint(int Id) {
        IntNode* current = Head;

        // Traverse the list until we find the node or reach the end
        while (current) {
            if (current->Info.ID == Id) {
                // Node with the given ID found, print its information
                cout << "Student Found:\n";
                cout << "ID: " << current->Info.ID << "\n"
                     << "Name: " << current->Info.Name << "\n"
                     << "GPA: " << current->Info.GPA << endl;
                return; // Exit the function after printing
            }
            current = current->next;
        }

        // If the node is not found, print a message
        cout << "Student with ID " << Id << " not found." << endl;
    }
    int Size(){
        int size=0;
        if(!Head)
            return size;
        else {
            IntNode*current=Head;
            size=1;
            while (current->next){
               size++;
                current = current->next;
            }
            return size;
        }


    }
};

int main() {
    Student s1("yousef",2022109,3.0);
    Student s2("mena",2022109,3.0);
    Student s3("hani",2022110,3.0);
    Student s4("ff",2022111,3.0);
    Student s5("44",2022112,3.0);
    StudentList list;
   list.Insertion(s1);
   list.Insertion(s2);
   // list.Insertion(s3);
    //list.Insertion(s4);
    //list.Insertion(s5);

 //   list.Display();
   list.Deletation(2022109);
    list.Display();
    //list.Deletation(2);

   //list.Deletation(5);
    cout<<list.Size();

    return 0;
}
