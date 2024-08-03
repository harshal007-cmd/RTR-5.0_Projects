#pragma once
#include<iostream>
using namespace std;

struct Node {
    int data;
    struct Node* next;
};

class LinkedList
{
private:
    Node* head;
public:
    LinkedList();
    ~LinkedList();
    
    void add(int value);
    void addLast();
    void addAt();
    void showList();
    void removeFirst();
    void removeLast();
    void removeAt();
    void main_LinkedList();
    
};
