#include <iostream>
using namespace std;;

class Original
{

private:
	int a;
public:
	Original(int x):a(x){}

	void show()
	{
		cout<<"In Original class = "<<a<<endl;
	}

	//copy constructor
	Original(const Original &org):a(org.a)
	{
		cout<<"In copy constructor = "<<a<<endl;
	}

	~Original(){
		cout<<"Destructor"<<endl;
	}
};


int main()
{
	Original org(10);

	Original copy(org);


	cout<<"Original\n";
	org.show();
	cout<<"Copy\n";
	copy.show();
	return 0;
}








