#include<stdio.h>

int main()
{
	int hvs_a;
	int hvs_b;
	int hvs_c;
	int h_result;

	printf("\n\n");

	printf("Enter 1st Integer: ");
	scanf("%d", &hvs_a);

	printf("\n");

	printf("Enter 2nd Integer: ");
	scanf("%d", &hvs_b);
	printf("\n");
	printf("Enter 3rd Integer: ");
	scanf("%d", &hvs_c);

	printf("\n\n");

	printf("IF answer is 0 it is 'False'\n ");
	printf("IF answer is 1 it is 'True'\n ");

	h_result = (hvs_a <= hvs_b) && (hvs_b!=hvs_c);
	printf("LOGICAL AND (&&): Answer is TRUE (1) If And Only If Both Conditions are True. The Answer is FALSE (0), if Any One Or Both Conditions are False\n\n");
	printf("hvs_a = %d Is Less than or Equal to hvs_b = %d AND hvs_b = %d Is Not Equal to hvs_c = %d    \tAnswer = %d\n\n", hvs_a, hvs_b, hvs_b, hvs_c, h_result);

	h_result = (hvs_b >= hvs_a) || (hvs_a == hvs_c);
	printf("LOGICAL OR (||): Answer is FALSE (0) If And Only If Both Conditions are FALSE. The Answer is TRUE (1), if Any One Or Both Conditions are TRUE\n\n");
	printf("Either hvs_b = %d is Greater than Or Equal to hvs_a = %d OR hvs_a = %d is Equal to hvs_c = %d    \tAnswer = %d\n\n", hvs_b, hvs_a, hvs_a, hvs_c, h_result);


	h_result = !hvs_a;
	printf("hvs_a = %d Using logical NOT (!) operator on a Given h_result = %d\n\n", hvs_a, h_result);

	h_result = !hvs_b;
	printf("hvs_b = %d Using logical NOT (!) operator on a Given h_result = %d\n\n", hvs_b, h_result);

	h_result = !hvs_c;
	printf("hvs_c = %d Using logical NOT (!) operator on a Given h_result = %d\n\n", hvs_c, h_result);

	h_result = (!(hvs_a <= hvs_b) && !(hvs_b != hvs_c));
	printf("Using Logical NOT (!) on (hvs_a <= hvs_b) And also on (hvs_b != hvs_c) and then ANDing then afterwards given h_result = %d\n\n", h_result);

	h_result = !((hvs_b <= hvs_a) || (hvs_a == hvs_c));
	printf("Using Logical NOT (!) on Entire logical expression (hvs_b <= hvs_a) || (hvs_a == hvs_c) gives h_result = %d\n\n", h_result);

	return 0;

}
