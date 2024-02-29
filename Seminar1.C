#include <stdio.h>

int square_reverse(double *x, double *y, const int len){
    int total_value = 0;
    for (int i = 0; i < len; i++)
    {
            total_value += *(x+i);
            *(y+len-1-i) = *(x+i) * *(x+i);
    }
        
    return total_value;
}

main(){
	double in[] = {-11.0, 20.0, 100.0};
	double out[3];
	int sum = square_reverse(&in, &out, 3);
	printf("%d\n", sum);
	printf("1: %lf\n2: %lf\n3: %lf\n", out[0], out[1], out[2]);
	return 0;
}