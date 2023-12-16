#include<iostream>
#include<thread>
#include<mutex>

using namespace std;
class Demo
{
private:
	int num;
	mutex mux_var;
public:
	Demo() {}

	void thFun1()
	{
		for (int i = 0;i < 500;++i)
		{
			lock_guard<mutex> lock(mux_var);
			cout<<"In thread ---> 1 "<<i<<endl;
			
		}
	}

	void thFun2()
	{
		for (int i = 0;i < 500;++i)
		{
			lock_guard<mutex> lock(mux_var);
			cout<<"In thread ---> 2 "<<i<<endl;
			
		}
	}
};

int main()
{
	Demo d;

	thread t1(&Demo::thFun1,&d);
	t1.join();
	thread t2(&Demo::thFun2,&d);

	
	t2.join();

	return 0;
}


