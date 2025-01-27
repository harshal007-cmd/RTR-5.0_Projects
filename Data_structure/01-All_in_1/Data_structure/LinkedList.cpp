#include"LinkedList.h"

LinkedList::LinkedList(): head(nullptr){}

LinkedList::~LinkedList()
{
    
    Node* current = head;
    while(current != nullptr)
    {
        Node* next =  current->next;
        free(current);
        current = next;
    }
     
}

void LinkedList::add(int value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = nullptr;
    
    if(head==nullptr)
    {
        head = newNode;
    }
    else{
        Node* current = head;
        while(current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }
    
}

void LinkedList::addAt()
{
    int x,value;
    cout<<"Enter location at which you need to add element = ";
    cin>>x;
    cout<<"\n";
    
    cout<<"Enter data you want to add = ";
    cin>>value;
    cout<<"\n";
    Node* node = (Node*)malloc(sizeof(Node));
    Node* current = head;
    
    if(x<=0)
    {
        cout<<"Cannot add at this location\n";
        return;
    }
    
    if(x == 1)
    {
        node->data = value;
        node->next = head;
        head = node;
        return;
    }
    for(int i = 1; current != nullptr && i < x - 1; i++)
    {
        current = current->next;
    }
    node->data = value;
    node->next = current->next;
    current->next = node;
    
    
    
}

void LinkedList::removeFirst()
{
    if(head==nullptr)
    {
        cout<<"Linked list is empty----\n\n";
        return;
    }
    
    Node* temp = head;
    head = head->next;
    cout<<"Removed first element is = "<<temp->data<<"\n";
    free(temp);
}

void LinkedList::removeLast()
{
    if(head==nullptr)
    {
        cout<<"Linked list is empty----\n\n";
        return;
    }
    
    Node* current = head;
    while(current->next->next != nullptr)
    {
        current = current->next;
    }
    cout<<"Removed last data from linked list is = "<<current->next->data<<"\n";
    free(current->next);
    current->next=nullptr;
    
}

void LinkedList::removeAt()
{
    int x;
    cout<<"Enter position to delete from linked list = ";
    cin>>x;
    
    if(x == 0)
    {
        cout<<"Checking in x == 0\n\n";
        removeFirst();
        return;
    }
    
    if(x < 0 || head == nullptr)
    {
        cout<<"Linked list is empty----\n\n";
        return;
    }
    
    Node* current = head;
    for(int i = 1 ; current != nullptr && i < x - 1; i++)
    {
        current =  current->next;
       
    }
    
    if(current == nullptr || current->next == nullptr)
    {
        return;
    
    }
        
    Node* temp = current->next;
    cout<<"Removed data at "<<x<<" position from linked list is = "<<temp->data<<"\n\n";
    current->next = current->next->next;
    free(temp);
}

void LinkedList::showList()
{
    Node* current =  head;
    int x=0;
    while(current != nullptr)
    {
        cout<<current->data<<"->";
        current = current->next;
        x++;
    }
    cout<<"showlist x = "<<x<<"\n";
    cout<<endl;
}

void LinkedList::main_LinkedList()
{
    int choice;
    
    cout<<"Select operations to perform on LinkedList\n\n";
    while(1)
    {
        cout<<"1. Add in linked list\n";
        cout<<"2. Print linked list data\n";
        cout<<"3. Remove first from linked list data\n";
        cout<<"4. Remove last from linked list data\n";
        cout<<"5. Remove from location in linked list data\n";
        cout<<"6. Add data at location in linked list data\n";
        cout<<"0. Exit\n\n";
        cin>>choice;
        
        switch (choice) {
            case 1:
                int x;
                cout<<"Enter data to add in linked list = ";
                cin>>x;
                cout<<"\n";
                add(x);
                break;
            case 2:
                cout<<"Data in linked list = ";
                showList();
                break;
            case 3:
                removeFirst();
                break;
            case 4:
                removeLast();
                break;
            case 5:
                removeAt();
                break;
            case 6:
                addAt();
                break;
           
            case 0:
                exit(0);
                break;
            default:
                break;
        }
    }
}











