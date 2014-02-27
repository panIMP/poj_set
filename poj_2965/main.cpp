#include <iostream>
#include <string>

using namespace std;


// mapping of the handles
// "0x4040" stands for
// 0100     -+--
// 0000     ----
// 0000     ----
// 0100     -+--
int handleMap;
// mapping of the switch mask for each handle
// handleMap xor(^) with SWITCH_MASK[x], means switch the xth handle of the door
const int SWITCH_MASK[16] = {
    0xf888, 0xf444, 0xf222, 0xf111,
    0x8f88, 0x4f44, 0x2f22, 0x1f11,
    0x88f8, 0x44f4, 0x22f2, 0x11f1,
    0x888f, 0x444f, 0x222f, 0x111f,
};
// switched sequence -- record which handles has been flipped
int switchSequence;
// totally switched times to open the door
int minSwitchTimes;
// door open conditon
const int DOOR_OPEN = 0x0000;


// read the input and set initial state
void initialize() {
    handleMap = 0x0000;
    switchSequence = 0x0000;
    minSwitchTimes = 17;
    char inputState;
    for (int i = 0; i < 16; ++i) {
        cin >> inputState;
        if (inputState == '+') {
            handleMap = handleMap | (0x0001 << (15 - i));
        }
    }
}


// switch the handle at position x
bool switchHandle(int x) {
    // use xor on bits
    handleMap ^= SWITCH_MASK[x];

    if (handleMap == DOOR_OPEN) {
        return true;
    } else {
        return false;
    }
}


// enumerate all the possible compounds -- "0x0000 --> 0xffff"
void enumerateSwitch() {
    // current switch sequence
    int curSequence = 0;
    // position of the current switch handle in current switch sequence
    int curPos = 0;
    // record the switch time of current sequence
    int switchTimes = 0;
    int initHandleMap = handleMap;
    for (int i = 0; i < 0xffff; ++i) {
        switchSequence = curSequence = i;
        while (curPos < 16) {
            if (curSequence & 0x8000) {
                switchTimes ++;
                if (switchHandle(curPos)) {
                    if (switchTimes < minSwitchTimes) {
                        minSwitchTimes = switchTimes;
                    }
                    return;
                }
            }
            curSequence = curSequence << 1;
            curPos ++;
        }
        curPos = 0;
        switchTimes = 0;
        handleMap = initHandleMap;
    }
}


int main() {

    initialize();

    enumerateSwitch();

    if (minSwitchTimes < 17) {
        cout << endl << minSwitchTimes << endl;
        for (int i = 0; i < 16; ++i) {
            if (switchSequence & 0x8000) {
                cout << i /4 + 1 << "  " << i % 4 + 1 << endl;
            }
            switchSequence <<= 1;
        }
    }

    return 0;
}

