#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


void printSquare(int x) {
    std::cout << x * x << " ";
}

int main() {
    std::vector<long long> numbers = { 112312, 3432, 34343, 3434, 34345 };

    // Using std::for_each with a function pointer
    std::for_each(numbers.begin(), numbers.end(), [](long long x) {cout << x * x << " ";});
    cout << endl;
    return 0;
}