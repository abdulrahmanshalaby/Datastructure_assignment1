#include <iostream>
using namespace std;

class Student{
public:
    string Name;
    int ID;
    float GPA;

};
class StudentNode{
public:
    Student Info;
    StudentNode* next;
public:
    StudentNode(Student item, StudentNode *next=0) : Info(item), next(next) {}

    ~StudentNode() {
delete next;
    }
};

class StudentList{
    StudentNode* Head,*Tail;

public:
    StudentList(){Head=Tail=nullptr;}
    ~StudentList(){delete Head;delete Tail;}
    void Insertion(Student Item) {
        if (!Head || Item.ID < Head->Info.ID) {
            StudentNode* node = new StudentNode(Item);
            node->next = Head;
            Head = node;
            if (!Tail) {
                Tail = node; // Set Tail if the list was previously empty
            }
        }
        else {
            StudentNode* current = Head;
            while (current->next && Item.ID > current->next->Info.ID) {
                current = current->next;
            }
            auto* n = new StudentNode(Item);
            n->next = current->next;
            current->next = n;
            if (!n->next) {
                Tail = n; // Update Tail if we inserted at the end
            }
        }
    }

    void Display() {
        StudentNode* ptr = Head;
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
        StudentNode* current = Head;

        while (current->next) {
            if (current->next->Info.ID == Id) {
                StudentNode* toDelete = current->next;
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
        StudentNode* current = Head;

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
            StudentNode*current=Head;
            size=1;
            while (current->next){
               size++;
                current = current->next;
            }
            return size;
        }


    }
};

class DoublyLinkedList
{
private:
    struct Node
    {
        char data;
        Node *prev;
        Node *next;
        Node(char ch) : data(ch), prev(nullptr), next(nullptr) {}
    };

    Node *head;
    Node *tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Function to initialize the list from a string
    void initialize(const string &str);

    // Function to insert a character at a specified position
    void insertChar(char ch, int pos);

    // Function to delete a character at a specified position
    void deleteChar(int pos);

    // Function to concatenate another list to this list
    void concat(const DoublyLinkedList &other);

    // Function to extract a substring
    string extractSubstring(int startIdx, int length);

    // Function to search for a substring and return the first index
    int searchSubstring(const string &substring);

    // Function to replace occurrences of a substring with another substring
    void replaceSubstring(const string &target, const string &replacement);

    // Function to reverse the list
    void reverse();

    // Utility function to print the list as a string
    void printList();
};

void DoublyLinkedList::initialize(const string &str)
{
    // Clear the current list
    while (head)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;

    // Add new characters
    for (char ch : str)
    {
        Node *newNode = new Node(ch);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = nullptr;
            tail = newNode;
        }
    }
}

void DoublyLinkedList::insertChar(char ch, int pos)
{
    Node *newNode = new Node(ch);
    if (pos == -1) {
        if (!head) {  // If the list is empty, new node becomes both head and tail
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        return;
    }
    if (pos == 0)
    {
        newNode->next = head;
        if (head)
            head->prev = newNode;
        head = newNode;
        if (!tail)
            tail = newNode;
        return;
    }

    Node *current = head;
    for (int i = 0; current && i < pos - 1; i++)
    {
        current = current->next;
    }
    if (!current)
        return;

    newNode->next = current->next;
    newNode->prev = current;
    if (current->next)
        current->next->prev = newNode;
    current->next = newNode;
    if (newNode->next == nullptr)
        tail = newNode;
}

void DoublyLinkedList::deleteChar(int pos)
{
    if (!head)
        return;

    Node *current = head;
    if (pos == 0)
    {
        head = head->next;
        if (head)
            head->prev = nullptr;
        delete current;
        if (!head)
            tail = nullptr;
        return;
    }

    for (int i = 0; current && i < pos; i++)
    {
        current = current->next;
    }
    if (!current)
        return;

    current->prev->next = current->next;
    if (current->next)
        current->next->prev = current->prev;
    else
        tail = current->prev;
    delete current;
}

void DoublyLinkedList::concat(const DoublyLinkedList &other)
{
    Node *current = other.head;
    while (current)
    {
        insertChar(current->data, -1); // Insert each character at the end
        current = current->next;
    }
}

string DoublyLinkedList::extractSubstring(int startIdx, int length)
{
    Node *current = head;
    for (int i = 0; current && i < startIdx; i++)
    {
        current = current->next;
    }
    if (!current)
        return "";

    string result;
    for (int i = 0; current && i < length; i++)
    {
        result += current->data;
        current = current->next;
    }
    return result;
}

int DoublyLinkedList::searchSubstring(const string &substring)
{
    if (!head || substring.empty())
        return -1;

    Node *current = head;
    int index = 0;
    while (current)
    {
        Node *temp = current;
        bool found = true;
        for (char ch : substring)
        {
            if (!temp || temp->data != ch)
            {
                found = false;
                break;
            }
            temp = temp->next;
        }
        if (found)
            return index;
        current = current->next;
        index++;
    }
    return -1;
}

void DoublyLinkedList::replaceSubstring(const string &target, const string &replacement)
{
    int pos;
    while ((pos = searchSubstring(target)) != -1)
    {
        for (int i = 0; i < target.length(); i++)
        {
            deleteChar(pos);
        }
        for (int i = 0; i < replacement.length(); i++)
        {
            insertChar(replacement[i], pos + i);
        }
    }
}

void DoublyLinkedList::reverse()
{
    Node *current = head;
    Node *temp = nullptr;
    while (current)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp)
        head = temp->prev;
}

void DoublyLinkedList::printList()
{
    Node *current = head;
    while (current)
    {
        cout << current->data;
        current = current->next;
    }
    cout << endl;
}

int main()
{
    cout<<"Task 1 or Task 2:\n";
    int c;
    cin>>c;
    switch (c) {
        case 1:{
            Student s1("Ahmed",2019001,3.4);
            Student s2("menna",20190010,3.5);
            Student s3("yousef",2019003,1.4);
            StudentList list;
            list.Insertion(s1);
            list.Insertion(s2);
            list.Insertion(s3);
            list.Deletation(20190010);
            list.Display();
            cout<< "list size :"<<list.Size();
            return 0;}
          case 2:
            DoublyLinkedList list1, list2;
            string input, target, replacement;
            int choice, pos, length;
            char ch;

            while (true)
            {
                cout << "\nChoose an option:\n";
                cout << "1. Initialize List\n";
                cout << "2. Insert Character\n";
                cout << "3. Delete Character\n";
                cout << "4. Concatenate Lists\n";
                cout << "5. Extract Substring\n";
                cout << "6. Search Substring\n";
                cout << "7. Replace Substring\n";
                cout << "8. Reverse List\n";
                cout << "9. Display List\n";
                cout << "0. Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                    case 1:
                        cout << "Enter a string to initialize: ";
                        cin >> input;
                        list1.initialize(input);
                        cout << "List initialized.\n";
                        break;

                    case 2:
                        cout << "Enter character to insert: ";
                        cin >> ch;
                        cout << "Enter position to insert at: ";
                        cin >> pos;
                        list1.insertChar(ch, pos);
                        cout << "Character inserted.\n";
                        break;

                    case 3:
                        cout << "Enter position to delete from: ";
                        cin >> pos;
                        list1.deleteChar(pos);
                        cout << "Character deleted.\n";
                        break;

                    case 4:
                        cout << "Enter a second string to concatenate: ";
                        cin >> input;
                        list2.initialize(input);
                        list1.concat(list2);
                        cout << "Lists concatenated.\n";
                        break;

                    case 5:
                        cout << "Enter starting index and length for substring: ";
                        cin >> pos >> length;
                        cout << "Extracted substring: " << list1.extractSubstring(pos, length) << "\n";
                        break;

                    case 6:
                        cout << "Enter substring to search for: ";
                        cin >> input;
                        pos = list1.searchSubstring(input);
                        if (pos != -1)
                        {
                            cout << "Substring found at index: " << pos << "\n";
                        }
                        else
                        {
                            cout << "Substring not found.\n";
                        }
                        break;

                    case 7:
                        cout << "Enter substring to replace: ";
                        cin >> target;
                        cout << "Enter replacement substring: ";
                        cin >> replacement;
                        list1.replaceSubstring(target, replacement);
                        cout << "Substring replaced.\n";
                        break;

                    case 8:
                        list1.reverse();
                        cout << "List reversed.\n";
                        break;

                    case 9:
                        cout << "Current List: ";
                        list1.printList();
                        break;

                    case 0:
                        cout << "Exiting...\n";
                        return 0;

                    default:
                        cout << "Invalid choice. Please try again.\n";
                }
            }
    }


}
