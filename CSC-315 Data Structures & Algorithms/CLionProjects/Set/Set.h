//
// Created by Jonah Morgan on 9/12/2022.
//

#ifndef SET_SET_H
#define SET_SET_H
#include <iostream>

// Node structure defintion.
struct node{
    int value;
    node* next;
};

// Definitions for functions.
void insert(node* &headptr, int val);
void remove(node* &headptr, int val);
bool isMember(int val, node* &headptr);
int size(node* headptr);
void displaySet(node* &headptr);


// Functions with implementation.
void insert(node* &headptr, int val){
    // Checks if the member is already in the set.
    if( isMember(val, headptr )){
        return;
    }

    // Creation of the node.
    node* newNode = new (std::nothrow) node;
    if(newNode == NULL){
        std::cout<<"Could not create the new node." << std::endl;
    }

    // New node is now the new first link in the set.
    newNode->value = val;
    newNode->next = headptr;
    headptr = newNode;
}


void remove(node* &headptr, int val){

}


bool isMember(int val, node* &headptr){
    // Traverse set with a temporary node to find value.
    node* temp = headptr;
    while(temp != nullptr){
        if(temp->value == val){
            return true;
        }
        temp = temp->next;
    }
    return false;
}


int size(node* headptr){
    int setSize = 0;

    // Traverse set to count amount of nodes.
    node* temp = headptr;
    while(temp != nullptr){
        setSize++;
        temp = temp->next;
    }
    return setSize;
}


void displaySet(node* &headptr){
    node* temp = headptr;
    std::cout << "{";
    while (temp != nullptr){
        std::cout << temp->value;
        temp = temp->next;
        if(temp != nullptr){
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
}

#endif //SET_SET_H
