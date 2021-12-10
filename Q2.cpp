#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

// class for a doubly linked list node
class Node
{
public:
    int val;
    Node *next;
    Node *prev;

    Node()
    {
        val = 0;
        prev = next = NULL;
    }
    Node(int val)
    {
        this->val = val;
        prev = next = NULL;
    }
    Node(int val, Node *next)
    {
        this->val = val;
        this->next = next;
        prev = NULL;
    }
    Node(int val, Node *next, Node *prev)
    {
        this->val = val;
        this->next = next;
        this->prev = prev;
    }
};

// class to contain all functions
class ListNode : private Node
{
    Node *first;

public:
    ListNode()
    {
        first = NULL;
    }
    // functions
    void Display();
    int Length();
    void insertAtLast(int val);
    void insertAtBegin(int val);
    void insertAtIndex(int val, int index);
    void DeleteFromBegin();
    void DeleteFromEnd();
    void DeleteFromIndex(int index);
    void UpdateValue(int index, int val);
    void Reverse();
    void removeDuplicates();
    void splitLL(ListNode &a, ListNode &b);
};

// Exception classes

class InvalidIndex_Exception : public exception
{
public:
    const char *what() const throw()
    {
        return "Exception: Index is invalid\n";
    }
};

class Memory_Exception : public exception
{
public:
    const char *what() const throw()
    {
        return "Exception: Object couldn't be created\n";
    }
};

class NothingInMemory_Exception : public exception
{
public:
    const char *what() const throw()
    {
        return "Exception: Nothing to delete\n";
    }
};

// Function to display the link list
void ListNode::Display()
{
    Node *p = first;
    while (p)
    {
        cout << p->val;
        p = p->next;
        if (p)
            cout << " -> ";
    }
    cout << endl;
}

// function to count the length of link list
int ListNode::Length()
{
    int length = 0;
    Node *t = first;
    while (t)
    {
        t = t->next;
        length++;
    }
    return length;
}

// Function to insert value at last
void ListNode::insertAtLast(int val)
{
    if (!first)
    {
        first = new Node(val);
        if (!first)
        {
            // Throwing exception if unable to create Node in heap
            Memory_Exception ex;
            throw ex;
        }
        return;
    }
    Node *p = first;
    while (p->next)
        p = p->next;
    p->next = new Node(val);
    if (!p->next)
    {
        // Throwing exception if unable to create Node in heap
        Memory_Exception ex;
        throw ex;
    }
    p->next->prev = p;
}

// Function to insert Node at beginning
void ListNode::insertAtBegin(int val)
{
    Node *n = new Node(val, first);
    if (first)
        first->prev = n;
    if (!n)
    {
        // Throwing exception if unable to create Node in heap
        Memory_Exception ex;
        throw ex;
    }
    first = n;
}

// Function to insert node at a middle index
void ListNode::insertAtIndex(int val, int index)
{
    if (index == 0)
    {
        insertAtBegin(val);
        return;
    }
    if (index < 0 or index > Length())
    {
        // Exception if the index is less the 0 or greater than current length
        InvalidIndex_Exception ex;
        throw ex;
    }
    Node *p = first;
    for (int i = 0; i < index - 1; i++)
        p = p->next;
    Node *n = new Node(val, p->next, p);
    if (!n)
    {
        // Throwing exception if unable to create Node in heap
        Memory_Exception ex;
        throw ex;
    }
    p->next = n;
    if (n->next)
        n->next->prev = n;
}

// Function to delete node from beginning
void ListNode::DeleteFromBegin()
{
    if (!first)
    {
        // exception if no node is in the memory
        NothingInMemory_Exception ex;
        throw ex;
    }
    Node *t = first;
    first = first->next;
    first->prev = NULL;
    delete t;
}

// Function to delete node from end
void ListNode::DeleteFromEnd()
{
    if (!first)
    {
        // exception if no node is in the memory
        NothingInMemory_Exception ex;
        throw ex;
    }
    Node *p = first;
    while (p->next)
        p = p->next;
    if (p != first)
        p->prev->next = NULL;
    delete p;
}

// Function to delete node in a middle index
void ListNode::DeleteFromIndex(int index)
{
    if (index == 0)
    {
        DeleteFromBegin();
        return;
    }
    if (index < 0 or index > Length() - 1)
    {
        // Exception if the index is less the 0 or greater than current length
        InvalidIndex_Exception ex;
        throw ex;
    }
    Node *p = first;
    for (int i = 0; i < index; i++)
        p = p->next;
    if (p->next)
        p->next->prev = p->prev;
    if (p->prev)
        p->prev->next = p->next;
    delete p;
}

// Function to update value of a node
void ListNode::UpdateValue(int index, int val)
{
    if (index < 0 or index > Length() - 1)
    {
        // Exception if the index is less the 0 or greater than current length
        InvalidIndex_Exception ex;
        throw ex;
    }
    Node *p = first;
    for (int i = 0; i < index; i++)
        p = p->next;
    p->val = val;
}

//Function to Reverse Doubly Linked List
void ListNode::Reverse()
{
    if (!first)
    {
        // exception if no node is in the memory
        NothingInMemory_Exception ex;
        throw ex;
    }
    Node *temp = NULL;
    Node *current = first;

    /* swap next and prev for all nodes of
    doubly linked list */
    while (current != NULL)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    /* Before changing the head, check for the cases like empty
        list and list with only one node */
    if (temp != NULL)
        first = temp->prev;
}

//Function to Remove Duplicates
void ListNode::removeDuplicates()
{
    // if DLL is empty or if it contains only
    // a single node
    if ((first) == NULL ||
        (first)->next == NULL)
        return;

    Node *ptr1, *ptr2;
    int n, n1 = 0;

    // pick elements one by one
    for (ptr1 = first; ptr1 != NULL; ptr1 = ptr1->next)
    {
        ptr2 = ptr1->next;
        n = n1 + 1;
        // Compare the picked element with the
        // rest of the elements
        while (ptr2 != NULL)
        {
            // if duplicate, then delete it
            if (ptr1->val == ptr2->val)
            {

                // store pointer to the node next to 'ptr2'
                Node *next = ptr2->next;

                // delete node pointed to by 'ptr2'
                DeleteFromIndex(n);

                // update 'ptr2'
                ptr2 = next;
            }

            // else simply move to the next node
            else
                ptr2 = ptr2->next;
            n++;
        }
        n1++;
    }
}

void ListNode::splitLL(ListNode &a, ListNode &b)
{
    if (!first)
    {
        // exception if no node is in the memory
        NothingInMemory_Exception ex;
        throw ex;
    }
    int n = Length();
    a.first = this->first;
    if (n == 1)
        return;

    Node *p = first;
    for (int i = 0; i < n / 2; i++)
        p = p->next;
    b.first = p;
    p->prev->next = NULL;
    p->prev = NULL;
    cout << "First LL: ";
    a.Display();
    cout << "Second LL: ";
    b.Display();
}

int main()
{
    ListNode LL;
    int val, index;
    while (true)
    {
        cout << "1. Insert at begin" << endl
             << "2. Insert at end" << endl
             << "3. Insert at index" << endl
             << "4. Display" << endl
             << "5. Delete from begin" << endl
             << "6. Delete from end" << endl
             << "7. Delete from index" << endl
             << "8. Update value" << endl
             << "9. Reverse" << endl
             << "10. Remove Duplicates" << endl
             << "11. Split the linked list" << endl
             << "12. Exit" << endl
             << endl;
        int menu;
        cout << "Select option: ";
        cin >> menu;
        //system("CLS");
        switch (menu)
        {
        case 1:
        {
            cout << "Enter value: ";
            cin >> val;
            try
            {
                LL.insertAtBegin(val);
            }
            catch (exception &e)
            {
                cerr << e.what() << endl;
            }
            cout << "Inserted" << endl;
            break;
        }
        case 2:
        {
            cout << "Enter value: ";
            cin >> val;
            try
            {
                LL.insertAtLast(val);
            }
            catch (exception &e)
            {
                cerr << e.what() << endl;
            }
            cout << "Inserted" << endl;
            break;
        }
        case 3:
        {
            cout << "Enter value: ";
            cin >> val;
            cout << "Enter index: ";
            cin >> index;
            try
            {
                LL.insertAtIndex(val, index);
            }
            catch (exception &e)
            {
                cout << e.what() << endl;
            }
            cout << "Inserted" << endl;
            break;
        }
        case 4:
        {
            LL.Display();
            break;
        }
        case 5:
        {
            try
            {
                LL.DeleteFromBegin();
            }
            catch (exception &e)
            {
                cerr << e.what() << endl;
            }
            cout << "Deleted" << endl;
            break;
        }
        case 6:
        {
            try
            {
                LL.DeleteFromEnd();
            }
            catch (exception &e)
            {
                cerr << e.what() << endl;
            }
            cout << "Deleted" << endl;
            break;
        }
        case 7:
        {
            cout << "Enter index: ";
            cin >> index;
            try
            {
                LL.DeleteFromIndex(index);
            }
            catch (exception &e)
            {
                cerr << e.what() << endl;
            }
            cout << "Deleted" << endl;
            break;
        }
        case 8:
        {
            cout << "Enter index: ";
            cin >> index;
            cout << "Enter new value: ";
            cin >> val;
            try
            {
                LL.UpdateValue(index, val);
            }
            catch (exception &e)
            {
                cerr << e.what() << endl;
            }
            break;
        }
        case 9:
        {
            try
            {
                LL.Reverse();
            }
            catch (exception &e)
            {
                cerr << e.what() << endl;
            }
            break;
        }
        case 10:
        {
            try
            {
                LL.removeDuplicates();
            }
            catch (exception &e)
            {
                cerr << e.what() << endl;
            }
            break;
        }
        case 11:
        {
            ListNode a, b;
            try
            {
                LL.splitLL(a, b);
            }
            catch (exception &e)
            {
                cerr << e.what() << endl;
            }
            break;
        }
        case 12:
        {
            return 0;
        }
        default:
        {
            cout << "Wrong menu!" << endl;
        }
        }
        cout << endl
             << endl;
    }

    return 0;
}