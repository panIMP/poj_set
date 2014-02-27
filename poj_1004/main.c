#include <stdio.h>

int main(void)
{
    int i;
    float balances[12];
    float sum = 0.0;
    for(i = 0; i < 12; i++){
        scanf("%f", &balances[i]);
        sum += balances[i];
    }
    printf("$%.2f", sum/12.0);

    return 0;
}

