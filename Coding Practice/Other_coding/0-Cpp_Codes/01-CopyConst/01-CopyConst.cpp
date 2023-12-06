#include <iostream>
using namespace std;
/*
class Complex {
private:
	double real;
	double imag;

public:
	Complex() : real(0), imag(0) {}

	// Corrected parameterized constructor
	Complex(double r, double i) : real(r), imag(i) {}

	// Overloading the + operator
	Complex operator+(const Complex& obj) const {
		Complex result;
		result.real = real + obj.real;
		result.imag = imag + obj.imag;
		return result;
	}

	// Display function
	void display() const {
		std::cout << "Real: " << real << ", Imaginary: " << imag << std::endl;
	}
};

int main() {
	// Creating two complex numbers
	Complex num1(2.5, 3.0);
	Complex num2(1.5, 2.5);

	// Using the overloaded + operator
	Complex sum = num1 + num2;

	// Displaying the result
	std::cout << "Sum of the complex numbers: ";
	sum.display();

	return 0;
}
*/




/*
#include <iostream>
using namespace std;

class C1
{
private:
	int a,b;

public:
	C1()
	{
		cout<<"In C1 class\n";
	}

	C1(int x, int y):a(x),b(y)
	{
		cout<<"Constructure with Parameter a and b\n";
	}

	//copy const
	C1(const C1 &obj)
	{
		a=obj.a;
		b=obj.b;

		cout<<"In copy Constructure\n";
	}


	void display()
	{
		cout<<"a = "<<a<<" b = "<<b<<endl;
	}

};
 */
class Complex
{
private:
	float real;
	float imag;

public:
	Complex(): real(0), imag(0) {}

	Complex(float a, float b) : real(a), imag(b){}
	//Complex opeartor ()

	Complex operator+(const Complex& obj) const {
	
		Complex temp;
		temp.real=real+obj.real;
		temp.imag=imag+obj.imag;

		return temp;
	}
	void display2()
	{
		cout<<"Real = "<<real<<"Imag = "<<imag<<endl;
	}
};


int main()
{
	/*
	C1 c1;
	C1 c2(10, 20);
    C1 c3=c2;

    cout<<"Copy Constructure section : "endl;
    cout<<"Usign C1\n";
    c1.display();

	cout<<"Usign C2\n";
    c2.display();

	cout<<"Usign C3\n\n";
    c3.display();
    cout<<"Copy Constructure section Ends - - - - - - - -: "<<endl;
//    */

    Complex comp1(2.2,4.4);
    Complex comp2(3.3,5.5);
	
	Complex sum = comp1 + comp2;
    //sum = comp1+comp2;
    sum.display2();



	cout<<"Opeartor overloading section Ends - - - - - - - -: "<<endl;
    
    cout<<endl;

	return 0;
}
//*/

