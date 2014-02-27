#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <time.h>

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
    string tempStr;
    long srcLongList[100000];
    vector<typeNode> parsedList;
    vector<typeNode> :: iterator cmpPos;
    bool dupState = false;   // inital the duplicate state as false

    // iterate over the telephone number list
    for(long i = 0; i < numList; i++){
        getline(cin, tempStr);   // get each line -- the input string
        teleParse(tempStr);  // translate string
        srcLongList[i] = atol(tempStr.c_str());
    }

    clock_t start = clock();

    // sort the string list in dict mode
    sort(srcLongList, srcLongList + numList - 1);

    // count the duplicate telephone number
    long tempLong;
    typeNode tempNode;
    for(long i = 0; i < numList; i++){
        tempLong = srcLongList[i];
        // mark the duplicated string and their duplicate times
        for(cmpPos = parsedList.begin(); cmpPos != parsedList.end(); ++cmpPos){
            if((*cmpPos).tp == tempLong){
                (*cmpPos).num ++;
                dupState = true;
                break;
            }
        }
        if(cmpPos == parsedList.end()){
            tempNode.num = 1;
            tempNode.tp = tempLong;
            parsedList.push_back(tempNode);
        }
    }

    // output the filter result, first judge the dupState
    if(dupState == true){
        long tempLong;
        long tempNum;
        stringstream ss;
        for(cmpPos = parsedList.begin(); cmpPos != parsedList.end(); ++cmpPos){
            tempNum = (*cmpPos).num;
            if(tempNum != 1){
                tempLong = (*cmpPos).tp;
                ss << tempLong;
                cout << (ss.str()).insert(3, "-") << " " << tempNum << endl;
                ss.str("");
            }
        }
    }else{
        cout << "No duplicates." << endl;
    }

    clock_t finish = clock();
    cout << (finish - start) / CLOCKS_PER_SEC << endl;

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
            if((tempChar >= 'A') && (tempChar < 'Z')){
                *delPos = mapList[tempChar - 65];
            }
        }
    }
}
