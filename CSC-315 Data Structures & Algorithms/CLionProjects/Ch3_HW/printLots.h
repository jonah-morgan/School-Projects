//
// Created by 7503314 on 9/7/2022.
//

#ifndef CH3_HW_PRINTLOTS_H
#define CH3_HW_PRINTLOTS_H
#include <iostream>


// this is an O(n) function.
template <class Container>
void printLots(Container &L, Container &P){
    auto itrA = L.begin();
    auto itrP = P.begin();
    int idx = 0;

    while(itrA != L.end() && itrP != P.end()){
        if(*itrP != idx){
            itrA++;
            idx++;
        }
        else {
            std::cout << *itrA << std::endl;
            itrP++;
        }
    }
}


#endif //CH3_HW_PRINTLOTS_H
