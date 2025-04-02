#include<iostream>
#include<unordered_set>
#include<string>
#include<vector>

using namespace std;


int subString1(string str)//optimized 1
{
	if (str.size() == 0)
		return 0;

	int maxLen = 0;

	unordered_set<int> uSet;
	int l = 0, r = 0;

	for (r = 0; r < str.length(); ++r)//travel the string
	{
		if (uSet.find(str[r]) != uSet.end())  //if duplicate element is found
		{
			while (l < r && uSet.find(str[r]) != uSet.end())
			{
				uSet.erase(str[l]);
				l++;
			}
		}
		uSet.insert(str[r]);
		maxLen = max(maxLen, r - l + 1);
		
	}
	
	return maxLen;
}

int subString2(string str)//more optimized
{
	int left = 0, right = 0;
	vector<int> mpp(256, -1);
	int n = str.size();
	int len = 0;

	while (right < n)
	{
		if (mpp[str[right]] != -1)
		{
			left = max(mpp[str[right]] + 1, left);
		}


		mpp[str[right]] = right;
		len = max(len, right - left + 1);
		right++;
	}

	return len;
}

int main()
{
	string str = "asdfgfdlavxzva";
	cout<<"Longest subString len = "<<subString1(str)<<"\n";
	cout<<"Longest subString len = "<<subString1(str)<<"\n";


	return 0;
}