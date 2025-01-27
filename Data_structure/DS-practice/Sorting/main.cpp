#include<iostream>
#include<vector>

using namespace std;

void bubbleSort(vector<int>& arr)
{
	int n = arr.size();
	bool swapping;

	for (int i = 0; i < n - 1; ++i)
	{
		swapping = false;
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
				swapping = true;
			}
		}

		if (!swapping)
			break;
	}
}


int partitian(vector<int>& arr, int low, int high)
{
	int pivote = arr[high];
	int i = low - 1;

	for (int j = low; j < high ; ++j)
	{
		//cout << arr[j] << " ";
		if (arr[j] < pivote)
		{
			i++;
			swap(arr[i], arr[j]);
		}
		
	}
	swap(arr[i + 1], arr[high]);

	return i + 1;


}

void quick(vector<int>& arr, int low, int high)
{
	int i = low;
	int j = high;
	int pi = 0;
	if (i < j)
	{
		pi = partitian(arr, i, j);

		quick(arr, low, pi - 1);
		quick(arr, pi + 1, high);
	}
}

void printArray(vector<int>& arr)
{
	for (int num : arr)
	{
		cout << num << " ";
	}
	cout << endl;
}

int main()
{
	vector<int> arr = { 12,34,54,10,23,65,93,11,31,45,67,1,65,9,41 };
	cout << arr.size()<<"\n";
	//bubbleSort(arr);
	//quick(arr, 0, arr.size() - 1);
	
	printArray(arr);
	return 0;
}
