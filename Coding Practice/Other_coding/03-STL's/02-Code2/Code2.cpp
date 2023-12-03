#include<iostream>
#include<map>
#include<vector>

using namespace std;

class A {
private:
	std::map<int, string> myMap;
	std::vector<int> vec;

public:
	void addData(int key, const string& value)
	{
		myMap[key] = value;
	}
	
	string getElement(int key)
	{
		auto it = myMap.find(key);
		if (it != myMap.end())
		{
			return it->second;
		}
		else
			return "key not found\n";
	}

	bool keyExist(int key)
	{
		return myMap.find(key) != myMap.end();
	}

	void printMap()
	{
		for (auto& pair : myMap)
		{
			cout << "Key : " << pair.first << ", Value : " << pair.second << "\n";
		}
	}

	void keyPrint()
	{
		for (auto& pair : myMap) {
			vec.push_back(pair.first);
		}

		for (int key : vec)
		{
			cout << key << " " << "\n";
		}
	}
};

int main()
{
	A aClass;

	cout << "\n\n";
	aClass.addData(1, "one");
	aClass.addData(2, "two");
	aClass.addData(3, "three");

	cout << "Map Element\n" << "\n";
	aClass.printMap();

	//access element
	cout << "Value for key 2: " << aClass.getElement(2) << "\n";
	aClass.keyPrint();

	cout << "\n\n";

	return 0;
}

