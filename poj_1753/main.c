#include <stdio.h>
const int MAP[16] = { 0x0013, 0x0027, 0x004E, 0x008C,
                      0x0131, 0x0272, 0x04E4, 0x08C8,
                      0x1310, 0x2720, 0x4E40, 0x8C80,
                      0x3100, 0x7200, 0xE400, 0xC800};
const int END_STATE_1 = 0x0000;
const int END_STATE_2 = 0xFFFF;

int read(){
    int i;
    char c;
    int initState;
    for(i = 0; i < 16; i++){
        c = getchar();
        if(c == 'b'){
            initState = (initState << 1) | 1;
        }else if(c == 'w'){
            initState = initState << 1;
        }else{
            i --;
        }
    }
    return initState;
}

int flipCard(int cardPos, int* curState){
    *curState = *curState ^ MAP[cardPos];
    if(*curState == END_STATE_1 || *curState == END_STATE_2){
        return 1;
    }else{
        return 0;
    }
}

int enumeration(int* initState){
    int i;
    int testEnum;
    int cardPos = 0;
    int flipTimes = 0;
    int minFlipTimes = 17;
    int curState = *initState;

    for(i = 1; i <= 0xFFFF; i++){
        testEnum = i;
        while(cardPos < 16){
            if(testEnum & 0x0001){
                flipTimes ++;
                if(flipCard(cardPos, &curState)){
                    if(minFlipTimes > flipTimes)
                        minFlipTimes = flipTimes;
                }
            }
            testEnum = testEnum >> 1;
            cardPos ++;
        }
        curState = *initState;
        cardPos = 0;
        flipTimes = 0;
    }

    return minFlipTimes;
}

int main(void){
    int minFlipTimes = 0;
    int initState = 0;

    initState = read();
    if(initState == END_STATE_1 || initState == END_STATE_2){
        printf("%d",0);
        return 0;
    }

    minFlipTimes = enumeration(&initState);
    if(minFlipTimes == 17)
        printf("Impossible");
    else
        printf("%d", minFlipTimes);


    return 0;
}



