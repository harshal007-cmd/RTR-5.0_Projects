/*
#include <iostream>

class StringOperations {
private:
    char* str;

public:
    StringOperations(const char* input) {
        int length = 0;
        while (input[length] != '\0') {
            length++;
        }

        str = new char[length + 1];

        for (int i = 0; i < length; i++) {
            str[i] = input[i];
        }
        str[length] = '\0';
    }

    const char* getOriginalString() const {
        return str;
    }

    const char* reverseString() {
        int i = 0, j = 0;

        while (str[j] != '\0') {
            j++;
        }
        j--;

        while (i < j) {
            std::swap(str[i], str[j]);
            i++;
            j--;
        }

        return str;
    }

    bool isPalindrome() const {
        int i = 0, j = 0;

        while (str[j] != '\0') {
            j++;
        }
        j--;

        while (i < j) {
            if (str[i] != str[j]) {
                return false;
            }
            i++;
            j--;
        }

        return true;
    }

    int countWords() const {
        int count = 0;
        int i = 0;

        while (str[i] != '\0') {
            if (str[i] == ' ') {
                count++;
            }
            i++;
        }

        return count + 1;  // Adding 1 to account for the last word
    }

    int findSubstring(const char* sub) const {
        int i = 0, j = 0;
        int subLength = 0;

        while (sub[subLength] != '\0') {
            subLength++;
        }

        while (str[i] != '\0') {
            if (str[i] == sub[j]) {
                i++;
                j++;
                if (j == subLength) {
                    return i - j;
                }
            } else {
                i = i - j + 1;
                j = 0;
            }
        }

        return -1;
    }

    void printCharacterFrequency() const {
        int count[26] = {0};

        int i = 0;
        while (str[i] != '\0') {
            if (std::isalpha(str[i])) {
                count[std::tolower(str[i]) - 'a']++;
            }
            i++;
        }

        for (char c = 'a'; c <= 'z'; ++c) {
            if (count[c - 'a'] > 0) {
                std::cout << c << ": " << count[c - 'a'] << ", ";
            }
        }

        std::cout << std::endl;
    }

    ~StringOperations() {
        delete[] str;
    }
};

int main() {
    const char* input = "The quick brown fox jumps over the lazy dog";
    StringOperations stringOps(input);

    std::cout << "Original: " << stringOps.getOriginalString() << std::endl;
    std::cout << "Reversed: " << stringOps.reverseString() << std::endl;
    std::cout << "\"" << stringOps.getOriginalString() << "\" is " << (stringOps.isPalindrome() ? "" : "not ") << "a palindrome." << std::endl;
    std::cout << "Word count: " << stringOps.countWords() << std::endl;

    const char* substring = "fox";
    int index = stringOps.findSubstring(substring);
    std::cout << "Substring \"" << substring << "\" found at index: " << index << std::endl;

    stringOps.printCharacterFrequency();

    return 0;
}
*/

#include <iostream>
using namespace std;
class StringOp
{
private:
	char* str;

public:
	StringOp(const char* input)
	{
		int len=0;
		while(input[len]!='\0')
			len++;

		str=new char[len+1];

		for(int i=0;i<len;++i)
		{
			str[i]=input[i];
		}
		str[len]='\0';
	}
    
    const char* getOriginal()
    {
    	return str;
    }   

	void strRev()
	{
		int len=0,i,j;
		char* str2;
		while(str[len]!='\0')
			len++;
		str2=new char[len+1];


		for(i=0,j=len-1;i<len;i++,j--)
			str2[i]=str[j];
        
        str2[i]='\0';
		cout<<"Reversed str is :"<<str2<<endl;
				
	}
};

int main()
{
	char* input="This is string";
	StringOp strop(input);

	cout<<"Original string is "<<strop.getOriginal()<<endl;
	strop.strRev();

	return 0;
}























