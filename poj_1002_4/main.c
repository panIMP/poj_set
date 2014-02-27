#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int teleStrInt[100000];

int cmp (const void* a , const void* b){
    return *(int*)a - *(int*)b;
}

void int2Str(int curNum, char* curNumStr){
    int counter = 1;
    int i = 0;
    char str[9] = {};
    char str2[9] = {};
    memset(curNumStr, 0, 9);
    sprintf(str, "%d", curNum);

    while(curNum /= 10){
        counter ++;
    }
    for(i = 0; i < counter; i++){
        curNumStr[i + 7 - counter] = str[i];
    }
    for(i = 0; i < 7 -counter; i++){
        curNumStr[i] = '0';
    }

    strcpy(str2, curNumStr);
    curNumStr[3] = '-';
    for(i = 3; i < 8; i ++){
        curNumStr[i + 1] = str2[i];
    }
}

int main(void)
{
    int i,j,k;
    char dupFlag;
    char buf[300];
    char tempStr[9] = {};
    char tempChar;
    int ti;
    int ti_1;
    int tempNum = 1;
    int teleNum;
    char map[26] = {'2', '2', '2', '3', '3', '3', '4', '4', '4','5','5','5',
                   '6', '6', '6', '7', 0, '7', '7', '8', '8', '8', '9', '9', '9', 0};


    scanf("%d", &teleNum);

    for(i = 0; i < teleNum; ++ i){
        scanf("%s", buf);
        k = 0;
        for(j = 0; (tempChar = buf[j]); j ++){
            if(tempChar == '-')
                continue;
            else{
                if((tempChar >= 'A') && (tempChar < 'Z')){
                    tempStr[k ++] = map[tempChar - 'A'];
                }else{
                    tempStr[k ++] = tempChar;
                }
            }
        }
        teleStrInt[i] = atoi(tempStr);
    }

    qsort(teleStrInt, teleNum, sizeof(teleStrInt[0]), cmp);

    for(i = 1; i < teleNum; i ++){
        ti = teleStrInt[i];
        ti_1 = teleStrInt[i - 1];
        if(ti !=  ti_1){
            if(tempNum > 1){
                int2Str(ti_1, tempStr);
                printf("%s %d\n", tempStr, tempNum);
                dupFlag = 1;
                tempNum = 1;
            }
        }else{
            tempNum ++;
        }
    }
    if(tempNum > 1){
        int2Str(ti_1, tempStr);
        printf("%s %d\n", tempStr, tempNum);
        dupFlag = 1;
    }

    if(!dupFlag)
        printf("No duplicates.\n");

    return 0;
}


