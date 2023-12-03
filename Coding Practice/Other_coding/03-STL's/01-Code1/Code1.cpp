#include<iostream>
#include<vector>

using namespace std;

class A {
private:
	std::vector<int> vec;

public:
	void addData(int data)
	{
		vec.push_back(data);
	}
	
	void removeData()
	{
		vec.pop_back();
	}
	
	int getElement(int index)
	{
		if (index >= 0 && index <= vec.size())
		{
			return vec[index];
		}
		else
		{
			cerr << "Index out of bounds\n";
			return -1;
		}
	}

	size_t getSize()
	{
		return vec.size();
	}

	size_t getCapacity()
	{
		return vec.capacity();
	}

	void printVector()
	{
		for (const auto& element : vec)
		{
			cout << element << " ";
		}
	}
};

int main()
{
	A aClass;

	cout << "\n\n";

	aClass.addData(10);
	aClass.addData(20);
	aClass.addData(30);

	//print
	aClass.printVector();

	//access
	cout << "Elements at Index 2 : " << aClass.getElement(2) << "\n";

	//capacity
	cout << "Size and Capacity of Vector : " << aClass.getSize() << " " << aClass.getCapacity() << "\n";

	cout << "\n\n";

	return 0;
}













