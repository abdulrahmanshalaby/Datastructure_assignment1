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

    ~IntNode(){delete next;}
};

class StudentList{
    IntNode* Head,*Tail;

public:
    StudentList(){Head=Tail=nullptr;}
    ~StudentList(){delete Head;delete Tail;}
    void Insertion( Student Item){
        if(!Head||Item.ID<Head->Info.ID){
          IntNode* node=new IntNode(Item);
            node->next = Head;
            Head = node;
        }


        else{
            IntNode*current=Head;
           while(Item.ID>current->Info.ID&&current->next) {
               current=current->next;
           }
           auto*n=new IntNode(Item);
           n->next=current->next;
           current->next=n;
            if (!n->next) {
                Tail = n;
            }
        }

    }
    void Display(){
        int count=1;
        IntNode*ptr;
        for (ptr = Head;  ptr->next ; ptr=ptr->next,count++) {
            cout<<count;cout<< +".";cout<<ptr->Info.Name+"   ";cout<<ptr->Info.GPA<<endl;
        }
        cout<<count;cout<< +".";cout<<ptr->Info.Name+"   ";cout<<ptr->Info.GPA<<endl;
    }
};

int main() {
    Student s1("yousef",2022109,3.0);
    Student s2("mena",2022108,3.0);
    Student s3("hani",2022110,3.0);
    StudentList list;
    list.Insertion(s1);
    list.Insertion(s2);
    list.Insertion(s3);
    list.Display();
    return 0;
}
