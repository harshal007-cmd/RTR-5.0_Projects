#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;


void printSquare(int x) {
    std::cout << x * x << " ";
}

int main() 
{
    std::vector<int> numbers = { 3,5,1,10,8,9,11,13,43,23,65,78,90,100,111,21 };
    string str = "This string is used as example";

    cout << endl;
    // Using std::for_each with a function pointer
    cout << "For_each output: \n";
    std::for_each(numbers.begin(), numbers.end(), [](long long x) {cout << x * x << " ";});

    cout << "\ncount stl is used here, Count spaces : \n";
    auto cnt = count(str.begin(), str.end(), ' ');
    cout << "Output of count STL = " << cnt << " " << endl;

        
    cout << "\n\nSorting stl is used : \n";
    sort(numbers.begin(), numbers.end());
    for (const auto& sNum : numbers)
        cout << sNum << " ";
    cout << endl;


    cout << endl;
    return 0;
}







