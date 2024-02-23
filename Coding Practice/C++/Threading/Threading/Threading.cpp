// Threading.cpp : Defines the entry point for the application.
//

#include "Threading.h"

using namespace std;

void func1()
{
	for (int i = 0;i < 300;++i)
	{
		cout << "In func1 = "<<i<<endl;
	}
}

void func2(int num)
{
	cout << "In thread func2 = " << num << endl;
}

vector<thread> tvec;

int main()
{
	//thread t1{func1};
	//thread t2{ func2,10 };
	for (int i = 0;i <= 10;++i)
	{
		thread t{ func2,i };
		tvec.push_back(move(t));
	}

	for_each(tvec.begin(), tvec.end(), [](thread& t) 
		{ assert(t.joinable()); t.join();	});


	return 0;
}
