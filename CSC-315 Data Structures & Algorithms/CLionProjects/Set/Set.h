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
node* setUnion(node* &headOne, node* &headTwo);
node* setIntersection(node* &headOne, node* &headTwo);
node* setDifference(node* &headOne, node* &headTwo);
node* symDiff(node* &headOne, node* &headTwo);
void displaySetFuncs(node* &headOne, node* &headTwo);


// Functions with implementation.
void insert(node* &headptr, int val){
    // Checks if the member is already in the set.
    if( isMember(val, headptr )){
        return;
    }

    // Creation of the node.
    node* newNode = new (std::nothrow) node;
    if(newNode == nullptr){
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


node* symDiff(node* &headOne, node* &headTwo){
    node* setDiffOne  = setDifference(headOne,headTwo);
    node* setDiffTwo  = setDifference(headTwo, headOne);
    return setUnion(setDiffOne, setDiffTwo);
}


void displaySetFuncs(node* &headOne, node* &headTwo){

    node* unionSet = setUnion(headOne, headTwo);
    node* intersectionSet = setIntersection(headOne, headTwo);
    node* differenceSet = setDifference(headOne, headTwo);
    node* symDiffSet = symDiff(headOne, headTwo);

    std::cout << "A: ";
    displaySet(headOne);
    std::cout << "B: ";
    displaySet(headTwo);

    if(isMember(5, headTwo)){
        std::cout << "5 is a member of B\n";
    }
    else {
        std::cout << "5 is not a member of B\n";
    }

    if(isMember(11, headOne)){
        std::cout << "11 is a member of A\n";
    }
    else {
        std::cout << "11 is not a member of A\n";
    }

    std::cout << "Size of B is " << size(headTwo);

    if(size(headOne) != size(headTwo)){
        std::cout << "\nA and B are not the same size!\n";
    }
    else {
        std::cout << "\nA and B are the same size!\n";
    }

    if(isSubset(headTwo, headOne)){
        std::cout << "B is a subset of A\n";
    }
    else{
        std::cout << "B is not a subset of A\n";
    }

    if(isEqual(headOne, headTwo)){
        std::cout << "A and B are equal!\n";
    }
    else{
        std::cout << "A and B are not equal!\n";
    }

    std::cout << "Union of A and B (A U B): ";
    displaySet(unionSet);

    std::cout << "Intersection of A and B (A n B): ";
    displaySet(intersectionSet);

    std::cout << "Difference of A and B (A - B): ";
    displaySet(differenceSet);

    std::cout << "Symmetric Difference of A and B (A delta B): ";
    displaySet(symDiffSet);

    std::cout << "(A-B) u B: ";
    node* newUnion = setUnion(differenceSet, headTwo);
    displaySet(newUnion);

    if(isEqual(unionSet, newUnion)){
        std::cout << "(A U B) and (A - B) U B are equal!\n";
    }
    else{
        std::cout << "(A U B) and (A - B) U B are not equal!\n";
    }

    node* baDiff = setDifference(headTwo, headOne);
    node* unionDiffs = setUnion(baDiff, differenceSet);
    std::cout << "(A-B) U (B-A): ";
    displaySet(unionDiffs);

    if(isEqual(symDiffSet, unionDiffs)){
        std::cout << "(A delta B) and (A-B) U (B-A) are equal!\n";
    }
    else {
        std::cout << "(A delta B) and (A-B) U (B-A) are not equal!\n";
    }
}


#endif //SET_SET_H
