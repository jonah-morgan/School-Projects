//
// Created by 7503314 on 9/14/2022.
//

#ifndef SET_CLASS__SET_H
#define SET_CLASS__SET_H
#include <iostream>

class Set{
public:
    Set();
    ~Set();
    bool insert(int value);
    bool remove(int value);
    bool isMember(int value);
    void display();
    int getSize();
    bool isSubset(Set &rhs);
    bool isEqual(Set &rhs);
    Set Union(Set& rhs);
    Set Intersection(Set& rhs);
    Set Difference(Set& rhs);
    Set SymmetricDifference(Set &rhs);

private:
    struct node{
        int value;
        node* next;
    };
    node* headptr;
};


Set::Set() {
    headptr = nullptr;
}


Set::~Set(){
    while(headptr != nullptr){
        node* temp = headptr;
        headptr = headptr->next;
        delete temp;
    }
}


bool Set::insert(int value) {
    // Checks if the member is already in the set.
    if( isMember(value)){
        return false;
    }

    // Creation of the node.
    node* newNode = new (std::nothrow) node;
    if(newNode == nullptr){
        std::cout<<"Could not create the new node." << std::endl;
    }

    // New node is now the new first link in the set.
    newNode->value = value;
    newNode->next = headptr;
    headptr = newNode;
    return true;
}


bool Set::remove(int value) {
    // If the element provided isn't in the set.
    if(!isMember(value) || this->getSize() == 0){
        return false;
    }

    // The case that the headptr contains the element to be removed.
    if(headptr->value == value){
        node* temp = headptr;
        headptr = headptr->next;
        delete temp;
        return true;
    }

    // The case that the headptr doesn't contain the element. We must traverse.
    node* prev = headptr;
    node* curr = headptr->next;

    while(curr != nullptr && curr->value != value){
        prev = curr;
        curr = curr->next;
    }

    if(curr->value == value){
        prev->next = curr->next;
        delete curr;
    }
    return true;
}


bool Set::isMember(int value) {
    // Traverse set with a temporary node to find value.
    node* temp = headptr;
    while(temp != nullptr){
        if(temp->value == value) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}


void Set::display(){
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


int Set::getSize() {
    int setSize = 0;

    // Traverse set to count amount of nodes.
    node* temp = headptr;
    while(temp != nullptr){
        setSize++;
        temp = temp->next;
    }
    return setSize;
}


bool Set::isSubset(Set &rhs) {
    // The empty set is always a subset.
    if(headptr == nullptr){
        return true;
    }

    node* tempOne = headptr;
    while(tempOne != nullptr){
        if(!rhs.isMember(tempOne->value)){
            return false;
        }
        tempOne = tempOne->next;
    }
    return true;
}


bool Set::isEqual(Set &rhs) {
    // Both sets must be a subset of one another to be equal
    if(this->isSubset(rhs) && rhs.isSubset(*this)){
        return true;
    }
    return false;
}


Set Set::Union(Set &rhs) {
    Set newSet = Set();   //say newSet is k

    node* temp = headptr; //n is this set
    while(temp != nullptr){
        newSet.insert(temp->value);
        temp = temp->next;
    }

    temp = rhs.headptr;  //m is the right hand set
    while(temp != nullptr){
        newSet.insert(temp->value);
        temp = temp->next;
    }

    return newSet;
}


Set Set::Intersection(Set &rhs) {
    Set newSet = Set();

    node* temp = headptr;
    while(temp != nullptr){
        if(rhs.isMember(temp->value)){
            newSet.insert(temp->value);
        }
        temp = temp->next;
    }

    return newSet;
}


Set Set::Difference(Set &rhs) {
    Set newSet = Set();

    node* temp = headptr;
    while(temp != nullptr){
        if(!rhs.isMember(temp->value)){
            newSet.insert(temp->value);
        }
        temp = temp->next;
    }

    return newSet;
}


Set Set::SymmetricDifference(Set &rhs) {
    Set setDiffOne = this->Difference(rhs);
    Set setDiffTwo = rhs.Difference(*this);
    return setDiffOne.Union(setDiffTwo);
}


void displaySetFuncs(Set &headOne, Set &headTwo){

    Set unionSet = headOne.Union(headTwo);
    Set intersectionSet = headOne.Intersection(headTwo);
    Set differenceSet = headOne.Difference(headTwo);
    Set symDiffSet = headOne.SymmetricDifference(headTwo);

    std::cout << "A: ";
    headOne.display();
    std::cout << "B: ";
    headTwo.display();

    if(headTwo.isMember(5)){
        std::cout << "5 is a member of B\n";
    }
    else {
        std::cout << "5 is not a member of B\n";
    }

    if(headOne.isMember(11)){
        std::cout << "11 is a member of A\n";
    }
    else {
        std::cout << "11 is not a member of A\n";
    }

    std::cout << "Size of B is " << headTwo.getSize();

    if(headOne.getSize() != headTwo.getSize()){
        std::cout << "\nA and B are not the same size!\n";
    }
    else {
        std::cout << "\nA and B are the same size!\n";
    }

    if(headTwo.isSubset(headOne)){
        std::cout << "B is a subset of A\n";
    }
    else{
        std::cout << "B is not a subset of A\n";
    }

    if(headOne.isEqual(headTwo)){
        std::cout << "A and B are equal!\n";
    }
    else{
        std::cout << "A and B are not equal!\n";
    }

    std::cout << "Union of A and B (A U B): ";
    unionSet.display();

    std::cout << "Intersection of A and B (A n B): ";
    intersectionSet.display();

    std::cout << "Difference of A and B (A - B): ";
    differenceSet.display();

    std::cout << "Symmetric Difference of A and B (A delta B): ";
    symDiffSet.display();


    std::cout << "(A-B) u B: ";
    Set newUnion = differenceSet.Union(headTwo);
    newUnion.display();

    if(unionSet.isEqual(newUnion)){
        std::cout << "(A U B) and (A - B) U B are equal!\n";
    }
    else{
        std::cout << "(A U B) and (A - B) U B are not equal!\n";
    }
    Set baDiff = headTwo.Difference(headOne);
    Set unionDiffs = baDiff.Union(differenceSet);
    std::cout << "(A-B) U (B-A): ";
    unionDiffs.display();

    if(symDiffSet.isEqual(unionDiffs)){
        std::cout << "(A delta B) and (A-B) U (B-A) are equal!\n";
    }
    else {
        std::cout << "(A delta B) and (A-B) U (B-A) are not equal!\n";
    }
}

#endif //SET_CLASS__SET_H
