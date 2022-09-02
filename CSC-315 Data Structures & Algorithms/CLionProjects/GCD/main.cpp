#include <iostream>
#include <vector>


int gcd(int a, int b);


int main() {
    std::vector<int> nums = {84, 132, 642, 246, 107, 41,
                             10, 10, 1, 1, 32, 15, 0, 0};
    int size = nums.size();

    for(int i = 0; i < size; i+=2){
        std::cout << nums[i] << ", " << nums[i + 1] << std::endl;
        std::cout << "gcd(" << nums[i] << "," << nums[i+1] << ") = " <<
            gcd(nums[i], nums[i+1]) << "\n\n";
    }

    return 0;
}


int gcd(int a, int b){
    if (a == 0) {
        return b;
    }

    else if (b == 0) {
        return a;
    }

    return gcd(b, a % b);
}