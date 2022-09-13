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
bool isSubset(node* &headOne, node* &headTwo);
bool isEqual(node* &headOne, node* &headTwo);
bool isEmpty(node* &headptr);
node* setUnion(node* &headOne, node* &headTwo);
node* setIntersection(node* &headOne, node* &headTwo);
node* setDifference(node* &headOne, node* &headTwo);


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
    // If the element provided isn't in the set.
    if(!isMember(val, headptr) || size(headptr) == 0){
        return;
    }

    // The case that the headptr contains the element to be removed.
    if(headptr->value == val){
        node* temp = headptr;
        headptr = headptr->next;
        delete temp;
        return;
    }

    // The case that the headptr doesn't contain the element. We must traverse.
    node* prev = headptr;
    node* curr = headptr->next;

    while(curr != nullptr && curr->value != val){
        prev = curr;
        curr = curr->next;
    }

    if(curr->value == val){
        prev->next = curr->next;
        delete curr;
    }
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


bool isSubset(node* &headOne, node* &headTwo){
    // The empty set is always a subset.
    if(headOne == nullptr){
        return true;
    }

    node* tempOne = headOne;
    node* tempTwo = headTwo;

    while(tempOne != nullptr){
        if(!isMember(tempOne->value, headTwo)){
            return false;
        }
        tempOne = tempOne->next;
    }
    return true;
}


bool isEqual(node* &headOne, node* &headTwo){
    // Both sets must be a subset of one another to be equal
    if(isSubset(headOne, headTwo) && isSubset(headTwo, headOne)){
        return true;
    }
    return false;
}


bool isEmpty(node* &headptr){
    if(size(headptr) == 0){
        return true;
    }
    return false;
}


node* setUnion(node* &headOne, node* &headTwo){
    node* newSet = nullptr;

    node* temp = headOne;
    while(temp != nullptr){
        insert(newSet, temp->value);
        temp = temp->next;
    }

    temp = headTwo;
    while(temp != nullptr){
        insert(newSet, temp->value);
        temp = temp->next;
    }

    return newSet;
}


node* setIntersection(node* &headOne, node* &headTwo){
    node* newSet = nullptr;

    node* temp = headOne;
    while(temp != nullptr){
        if(isMember(temp->value,headTwo)){
            insert(newSet, temp->value);
        }
        temp = temp->next;
    }

    return newSet;
}


node* setDifference(node* &headOne, node* &headTwo){
    node* newSet = nullptr;

    node* temp = headOne;
    while(temp != nullptr){
        if(!isMember(temp->value, headTwo)){
            insert(newSet,temp->value);
        }
        temp = temp->next;
    }

    return newSet;
}

#endif //SET_SET_H
