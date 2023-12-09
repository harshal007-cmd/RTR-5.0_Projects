#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

class Threads
{
private:
	int i;
	mutex mux1, mux2;
public:
	Threads() {}
	Threads(int a) :i(a) {}

	void tFun1()
	{
		for (int j = 0;j < 1000;++j)
		{
			cout << "In thread fun1 J = " << j << endl;
		}
	}

	void tFun2()
	{
		for (int k = 0;k < 1000;++k)
		{
			cout << "In thread fun2 K = " << k << endl;
		}
	}

	void forMutex1()
	{
		mux1.lock();
		mux2.lock();
		cout <<"In for Mux 1\n"<< endl;
		mux1.unlock();
		mux2.unlock();
	}
	void forMutex2()
	{
		int x = try_lock(mux1, mux2);
		if (x == -1)
		{
			cout << "In for Mux 2\n"<<endl;
		}
	}

};

int main()
{
	Threads th;
	int cnt;
	//thread t1(&Threads::tFun1, &th);
	//thread t2(&Threads::tFun2, &th);
	cout << "Enter cnt : ";
	cin >> cnt;
	thread t1(&Threads::forMutex1, &th);
	thread t2(&Threads::forMutex1, &th);
	t1.join();
	t2.join();


	return 0;
}
















