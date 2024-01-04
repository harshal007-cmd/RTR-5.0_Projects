#include<iostream>
#include<vector>
using namespace std;

class Vector
{
public:
	vector<int> vec;

	void add(int data)
	{
		vec.push_back(data);
	}

	void show()
	{
		cout << "\n";
		for (auto num : vec)
		{
			cout << num << " ";
		}
		cout << "\n";
	}
};


int main()
{
	Vector v;

	for (int i = 0; i <= 10; ++i)
	{
		v.add(i);

	}
	v.show();
	return 0;
}