#include <stdlib.h>
#include <stdio.h>
#include <math.h>


// the range(x cordinate value) for a radar installation
// on the coast for the island to be covered
typedef struct{
    float left;
    float right;
}islandRange;

// island num
int islandNum;
// maximum islands
#define ISLAND_MAX_NUM 1001
// islands range of radar array
islandRange islands[ISLAND_MAX_NUM];

// maximum cases
#define ISLAND_MAX_CASE_NUM 1001
// radar num array of each case
int radarNum[ISLAND_MAX_CASE_NUM];


// compare function for qsort
int cmp(const void* a, const void* b){
    return ((islandRange*)a)->left < ((islandRange*)b)->left ? -1 : 1;
}


// greed method to solve radar num
int greedMethod(islandRange islands[], int iNum){
    int i;
    int rNum = 1;
    float cur = islands[0].right;

    for (i = 1; i < iNum; ++i){
        // if "next" range is totally outside of "current" range
        if (islands[i].left - cur > 1e-5){
            rNum ++;
            cur = islands[i].right;
        } else {
            // if "next" range is inside "current" range
            if (islands[i].right - cur < 1e-5) {
                cur = islands[i].right;
            }
        }
    }

    return rNum;
}


int main()
{
    int i;                    // normal counter
    int x,y;                  // input x & y coordinate
    double offset;            // intermidiate value
    int caseCount = 0;        // case counter
    int solutionPossible;     // solution possible flag
    int radarDistance;        // radar distance

    // input all the island location compounds cases
    while (scanf("%d %d", &islandNum, &radarDistance) == 2
           && !((islandNum == radarDistance) && (radarDistance == 0))){

        // mark as solution possible
        solutionPossible = 1;

        for (i = 0; i < islandNum; ++i) {
            scanf("%d %d", &x, &y);

            // when input of y is below, meaning no solution
            if (y > radarDistance || y < 0) {
                solutionPossible = 0;
                continue;
            }

            // calculate the range
            offset = sqrtf(radarDistance * radarDistance - y * y);
            islands[i].left = x - offset;
            islands[i].right = x + offset;
        }

        // one case is read
        if (!solutionPossible) {    // if no solution
            radarNum[caseCount] = -1;
        } else {                    // if has solution
            // qsort the range compositions
            qsort(islands, islandNum, sizeof(islandRange), cmp);
            // use greed
            radarNum[caseCount] = greedMethod(islands, islandNum);
        }

        caseCount ++;
    }

    printf("\n");
    // output the result of all cases
    for (i = 0; i < caseCount; ++i) {
        printf("case %d: %d\n", i + 1, radarNum[i]);
    }


    return 0;
}

