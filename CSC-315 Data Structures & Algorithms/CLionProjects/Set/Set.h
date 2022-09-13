//
// Created by jonah on 9/12/2022.
//

#ifndef SET_SET_H
#define SET_SET_H
#include <iostream>


struct node{
    int value;
    node* next;
};


void insert(node* &headptr, int val);
bool isMember(int val, node* &headptr);
void displaySet(node* &headptr);


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

    newNode->value = val;
    newNode->next = headptr;
    headptr = newNode;

}


bool isMember(int val, node* &headptr){
    node* temp = headptr;
    while(temp != nullptr){
        if(temp->value == val){
            return true;
        }
        temp = temp->next;
    }
    return false;
}


void displaySet(node* &headptr){
    node* temp = headptr;
    while (temp != nullptr){
        std::cout << temp->value << std::endl;
        temp = temp->next;
    }
}

#endif //SET_SET_H
