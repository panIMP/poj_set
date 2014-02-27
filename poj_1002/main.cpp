#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdio.h>

using namespace std;

typedef struct _Type_Node{
    long num;
    long tp;
}typeNode;

void teleParse(string& teleStr);

char mapList[25] = {'2','2','2','3','3','3','4','4','4','5','5','5','6','6','6','7','7','7','7','8','8','8','9','9','9'};

int main()
{
    // get the telephone number length
    long numList;
    cin >> dec >> numList;
    getchar();

    // get the telephone number and translate them into uniform format: 487-3279
    vector<long> srcLongIntList;
    vector<typeNode> parsedLongIntList;
    vector<typeNode> :: iterator cmpPos;
    bool dupState = false;   // inital the duplicate state as false

    // iterate over the telephone number list
    for(long i = 0; i < numList; i++){
        //getline(cin, srcList[i]);   // get each line -- the input string
        string tempStr;
        getline(cin,tempStr);
        teleParse(tempStr);  // translate string
        //srcList.push_back(tempStr);
        srcLongIntList.push_back(atol(tempStr.c_str()));
    }

    // sort the string list in dict mode
    sort(srcLongIntList.begin(), srcLongIntList.end());

    // count the duplicate telephone number
    long tempLongInt;
    typeNode tempNode;
    for(long i = 0; i < numList; i++){
        tempLongInt = srcLongIntList[i];
        // mark the duplicated string and their duplicate times
        for(cmpPos = parsedLongIntList.begin(); cmpPos != parsedLongIntList.end(); ++cmpPos){
            if((*cmpPos).tp == tempLongInt){
                (*cmpPos).num ++;
                dupState = true;
                break;
            }
        }
        if(cmpPos == parsedLongIntList.end()){
            tempNode.num = 1;
            tempNode.tp = tempLongInt;
            parsedLongIntList.push_back(tempNode);
        }
    }

    // output the filter result, first judge the dupState
    if(dupState == true){
        string tempStr;
        long tempNum;
        long tempLongIntStr;
        for(cmpPos = parsedLongIntList.begin(); cmpPos != parsedLongIntList.end(); ++cmpPos){
            tempNum = (*cmpPos).num;
            tempLongIntStr = (*cmpPos).tp;
            if(tempNum != 1){
                stringstream strstream;
                strstream << tempLongIntStr;
                tempStr = (strstream.str()).insert(3, "-");
                strstream.str("");
                cout << tempStr << " " << tempNum << endl;
            }
        }
    }else{
        cout << "No duplicates." << endl;
    }

    return 0;
}

// parse the string into all number ones, no "-" added here
void teleParse(string& teleStr){
    string::iterator delPos;
    for(delPos = teleStr.begin(); delPos != teleStr.end(); ++delPos){
        char tempChar = *delPos;
        if(tempChar == '-'){
            teleStr.erase(delPos);
            delPos --;
        }
        else{
            if(tempChar >= 'A'){
                *delPos = mapList[tempChar - 65];
            }
        }
    }
}
