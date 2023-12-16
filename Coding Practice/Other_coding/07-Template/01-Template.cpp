#include<iostream>
#include<string>
using namespace std;

template <class T1, class T2>

class Templates
{
private:
	T1 first;
	T2 second;

public:
	Templates(const T1& f, const T2& s) :first(f), second(s) {}

	T1 getFirst()
	{
		return first;
	}

	T2 getSecond() {
		return second;

	}
};


int main()
{
	Templates<int, double> temp1(10, 20.20);
	Templates<string, char> temp2("Harshal", 'S');

	cout << "Temp1 : " << temp1.getFirst() << "," << temp1.getSecond() << endl;
	cout << "Temp2 : " << temp2.getFirst() << "," << temp2.getSecond() << endl;

	return 0;
}
