#include<iostream>
#include"Queue.h"
#include"LinkedList.h"
using namespace std;

int main()
{
    cout << "All Data structure codes :\n" << endl;
    int choice = 0;

    while (1)
    {
        cout << "Select any one of following data strutrue to use\n" << endl;
        cout << "1. Queue\n";
        cout << "2. Singly Linked List\n";
        cout << "0. Exit\n";
 

        cout << "Enter your choice\n";
        cin >> choice;
            
        //All object initializations
        Queue* q = nullptr;
        LinkedList l;
        ///-------------------
        switch (choice)
        {
        case 1:
            cout << "Set length of Queue\n";
            int x;
            cin >> x;
            q = new Queue(x);
            q->main_Queue();
            break;
        case 2:
                l.main_LinkedList();
                break;
        case 0:
            exit(0);
            break;
        default:
            cout << "Enter correct choice\n";
            break;
        }
    }

    return 0;
}
