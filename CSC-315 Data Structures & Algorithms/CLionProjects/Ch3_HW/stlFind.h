//
// Created by 7503314 on 9/7/2022.
//

#ifndef CH3_HW_STLFIND_H
#define CH3_HW_STLFIND_H
#include <iterator>

template <typename Iterator, typename Object>
auto find( Iterator start, Iterator end, const Object &x){
    while(start != end){
        if (*start == x)
            return start;

        start++;
    }
    return end;
}


#endif //CH3_HW_STLFIND_H
