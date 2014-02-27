// proj1001.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include<stdio.h>

#include "main.h"


/*numStr1(n1 bit num) multiply numStr2(n2 bit num) equals numStrResult(n3 bit num)*/
char* mul(char* numStr1, char* numStr2, char* numStrResult)
{
	int n1 = strlen(numStr1);
	int n2 = strlen(numStr2);
	int i = 0;
	int j = 0;
	int point = 0;
	int point1 = 0;
	int point2 = 0;
	int leftborder;
	int rightborder;
	int length;

	//倒装，低位在字符串低位，高位在字符串高位,并去掉小数点，记录小数位数。
	if (numStr1 == numStr2)
	{
		char *p = strchr(numStr1,'.');
		if (p)
		{
			point1 = n1 - 1 - (p - numStr1);
			point2 = point1;
			strcpy(p, p + 1);
			numStr1 = strrev(numStr1);
			numStr2 = numStr1;
			n1 = strlen(numStr1);
			n2 = n1;
		}
		else
		{
			point = 0;
			numStr1 = strrev(numStr1);
		}
	} 
	else
	{
		char *p = strchr(numStr1,'.');
		if (p)
		{
			point1 = n1 - 1 - (p - numStr1);
			strcpy(p, p + 1);
			numStr1 = strrev(numStr1);
			n1 = strlen(numStr1);
		}
		else
		{
			point = 0;
			numStr1 = strrev(numStr1);
		}
		
		p = strchr(numStr2,'.');
		if (p)
		{
			point2 = n2 - 1 - (p - numStr2);
			strcpy(p, p + 1);
			numStr2 = strrev(numStr2);
			n2 = strlen(numStr2);
		} 
		else
		{
			point = 0;
			numStr2 = strrev(numStr2);
		}
	}


	// first -- multiply bit by bit concering about the overflow
	for(i = 0; i < n1; i ++)
	{
		for(j = 0; j < n2; j ++)
		{
			numStrResult[i + j] += (numStr1[i] - '0') * (numStr2[j] - '0');
			if (numStrResult[i + j] >= 10)
			{
				numStrResult[i + j + 1] += numStrResult[i + j] / 10;
				numStrResult[i + j] = numStrResult[i + j] % 10;
			}
		}
	}

	//second -- insert the xiaoshudian, and rev
	point = point1 + point2;
	if (point != 0)
	{
		i = LEN - 1;
		while(numStrResult[i] == 0)
		{
			i ++;
		}
		rightborder = i;
		j = 0;
		while(j < point)
		{
			while(numStrResult[j] == 0)
			{
				j ++;
			}
			break;
		}
		leftborder = j;
		char* temp = (char*)malloc(rightborder - leftborder);
		for (i = 0; i < point; i ++)
		{
			temp[i] = numStrResult[i + leftborder] + '0';
		}
		for (i = point + 1; i <= rightborder - leftborder ; i ++)
		{
			temp[i] = numStrResult[i + leftborder -1] + '0';
		}
		temp[point] = '.';
		return temp;
	}
	else
	{
		for (i = 0; i < LEN; i ++)
		{
			numStrResult[i] += '0';
		}
		return numStrResult;
	}
}

/*numStr multiply to numStr for N times*/
int pows(char*numStr, int N, char*numStrResult)
{
	return 0;
}

int main()
{
	//read numbers from the std
    int point = 0;
	int mux;
	int len1;
	int i;
	int leftStart;
	int rightStart;

	char str1[LEN] = {0};	//前端输入，有限制
	char *num1;
	char *num2;

	while(scanf("%s%d",str1,&mux) == 2)
	{
		//开辟结果缓存区
		char* num = (char*)malloc(LEN);
		memset(num,0,LEN);
		num = mul(str1,str1,num);
		for (i = 0;i < 20;i ++)
		{
			printf("%c",num[i]);
		}
	}
	return 0;
}