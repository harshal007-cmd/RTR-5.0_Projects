#include<stdio.h>

#define MY_PI 3.1415926535
#define AMC_STRING "Astromedicomp RTR"

enum {
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

enum
{
	JANUARY=1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

enum Numbers {
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE=5,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN
};

enum Boolean {
	TRUE=1,
	FALSE=0
};

int main(void)
{
	const double epsilon = 0.000001;

	printf("\n\n");
	printf("Local const Epsion = %lf\n\n", epsilon);
	
	printf("Sunday is day number = %d\n", SUNDAY);
	printf("Monday is day number = %d\n", MONDAY);
	printf("Tuesday is day number = %d\n", TUESDAY);
	printf("Wednesday is day number = %d\n", WEDNESDAY);
	printf("Thursday is day number = %d\n", THURSDAY);
	printf("Friday is day number = %d\n", FRIDAY);
	printf("Saturday is day number = %d\n\n", SATURDAY);
	

	printf("One is Enum number = %d\n", ONE);
	printf("Two is Enum number = %d\n", TWO);
	printf("Three is Enum number = %d\n", THREE);
	printf("Four is Enum number = %d\n", FOUR);
	printf("Five is Enum number = %d\n", FIVE);
	printf("Six is Enum number = %d\n", SIX);
	printf("Seven is Enum number = %d\n", SEVEN);
	printf("Eight is Enum number = %d\n", EIGHT);
	printf("Nine is Enum number = %d\n", NINE);
	printf("Ten is Enum number = %d\n\n", TEN);

	printf("January is Month number = %d\n", JANUARY);
	printf("February is Month number = %d\n", FEBRUARY);
	printf("March is Month number = %d\n", MARCH);
	printf("April is Month number = %d\n", APRIL);
	printf("May is Month number = %d\n", MAY);
	printf("June is Month number = %d\n", JUNE);
	printf("July is Month number = %d\n", JULY);
	printf("August is Month number = %d\n", AUGUST);
	printf("September is Month number = %d\n", SEPTEMBER);
	printf("October is Month number = %d\n", OCTOBER);
	printf("November is Month number = %d\n", NOVEMBER);
	printf("December is Month number = %d\n\n", DECEMBER);

	printf("Value of True is = %d\n", TRUE);
	printf("Value of False is = %d\n\n", FALSE);

	printf("MY_PI Macro value = %0.6lf\n", MY_PI);
	printf("Area of Circle of Radius 2 units = %f\n\n", (MY_PI * 2.0f * 2.0f));

	printf("\n\n");

	printf(AMC_STRING);
	printf("\n\n");
	printf("AMC_STRING is : %s\n", AMC_STRING);
	printf("\n\n");



	return 0;

}










