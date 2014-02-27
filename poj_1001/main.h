#ifndef _MAIN_H
#define _MAIN_H
#endif



#define LEN 200
#define LEN1 5
#define LEN2 5


/************************************************************************
multiply
number has been transfered into str -- numStr1 & numStr2, 
with each has n1 numbers and n2 numbers
note:n3 >= n1 + n2
************************************************************************/
char* mul(char* numStr1, char* numStr2, char* numStrResult);


/************************************************************************
Power
number has been transfered into str numStr,
times has been transfered into str N
************************************************************************/
int pows(char*numStr, int N, char*numStrResult);