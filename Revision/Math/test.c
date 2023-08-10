#include <stdio.h>
#include "MyMath.h"

int main(int argc,char* argv[]){

    vec2 v0,v1,v2,result;

    vec2_create(&v0, 2.0, 3.0f);
    vec2_create(&v1, 1.0, -1.0f);
    vec2_create(&v2, 3.0, 4.0f);

    printf("v0 x = %.1f y = %.1f\n",v0.data[0],v0.data[1]);
    printf("v1 x = %.1f y = %.1f\n",v1.data[0],v1.data[1]);
    printf("v2 x = %.1f y = %.1f\n",v2.data[0],v2.data[1]);

    vec2_add(&result, &v0, &v1); // 3,2
    printf("v0 + v1 = %.1f %.1f\n",result.data[0],result.data[1]);

    vec2_substract(&result, &v0, &v1);// 1,4
    printf("v0 - v1 = %.1f %.1f\n",result.data[0],result.data[1]);

    vec2_multiple(&result, &v0, 2.0f); // 4,6
    printf("v0 * 2.0f = %.1f %.1f\n",result.data[0],result.data[1]);

    vec2_divide(&result, &v0, 2.0f); // 1, 1.5
    printf("v0 / 2.0f = %.1f %.1f\n",result.data[0],result.data[1]);

    vec2_normalize(&result, &v0); // 0.55,0.83
    printf("Normalized V0 = %.1f %.1f\n",result.data[0],result.data[1]);

    printf("Dot Product of V0 & V2 = %.1f\n",vec2_dot(&v0, &v2)); // 18

    printf("Length Of V1 = %.1f\n",vec2_length(&v1)); // 1.41

    printf("Distance Between V0 & V2 = %.1f \n",vec2_distance(&v0, &v2)); // 1.41
    return 0;
}
