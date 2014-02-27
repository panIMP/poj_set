#include <stdio.h>

const int MAP[16] = { 0x0013, 0x0027, 0x004E, 0x008C,
                      0x0131, 0x0272, 0x04E4, 0x08C8,
                      0x1310, 0x2720, 0x4E40, 0x8C80,
                      0x3100, 0x7200, 0xE400, 0xC800};
const int END_STATE_1 = 0x0000;
const int END_STATE_2 = 0xFFFF;
//const int arr[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
#define ARR_LEN 16
int initNum = 0;
//int initArr[ARR_LEN] = {0};
int result[ARR_LEN] = {0};

void read(){
    int i;
    char c;
    for(i = 0; i < 16; i++){
        c = getchar();
        if(c == 'b'){
            initNum = (initNum << 1) | 1;
            //initArr[i] = 1;
        }else if(c == 'w'){
            initNum = initNum << 1;
            //initArr[i] = 0;
        }else{
            i --;
        }
    }
}

int combine_list_hp(int result[], int left, int targetPickLen, int curTargetPickLen, int* minFlipTimes){
    int i = 0;
    int j = 0;
    int temp = initNum;

    if(curTargetPickLen > ARR_LEN - left){
        return -1;
    }

    if(*minFlipTimes)
        return 0;

    for(i = left; i < ARR_LEN; i ++){
        if(*minFlipTimes)
            return 0;

        result[targetPickLen - curTargetPickLen] = i;
        if(curTargetPickLen - 1 == 0){
            for(j = 0; j < targetPickLen; j ++){
                temp = temp ^ MAP[result[j]];
            }
            if(temp == END_STATE_1 || temp == END_STATE_2){
                *minFlipTimes = targetPickLen;
                return 0;
            }else{
                temp = initNum;
            }
        }else{
            combine_list_hp(result, i + 1, targetPickLen, curTargetPickLen - 1, minFlipTimes);
        }
    }

    return 0;
}

int main(void){
    int i = 0;
    int minFlipTimes = 0;

    read();

    if(initNum == END_STATE_1 || initNum == END_STATE_2){
        printf("%d",0);
        return 0;
    }

    for(i = 1; i <= ARR_LEN; i ++){
        combine_list_hp(result, 0, i, i, &minFlipTimes);
        if(minFlipTimes){
            printf("%d", minFlipTimes);
            return 0;
        }
    }

    printf("Impossible");

    return 0;
}
