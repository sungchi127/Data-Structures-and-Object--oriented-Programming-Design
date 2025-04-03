#include <iostream>
#include <algorithm>
#include <deque>
#include <ctime>
using namespace std;

deque<int> LandingQueue[5], TakeoffQueue[5];
int choose[5], LandingNumber, TakeoffNumber, LandingPlane[5], TakeoffPlane[5], LandingID = 1, TakeoffID = 0, oil[10005], Fuel = 0, WaitingTime = 0, TotalLandingPlane = 0, TotalTakeoffPlane = 0;


int rand_num() {
  return rand() % 4;
}

int rand_oil() {
    return rand() % 10 + 1;
}

void printqueue() {
    for (int i = 1; i <= 4; i++) {
        cout << "Runway" << i << "(" << choose[i] << ")" << endl;
        cout << "L1:";
        for (int j = 0; j < LandingQueue[i].size(); j++) {
            cout << "(" << LandingQueue[i][j] << "," << oil[LandingQueue[i][j]] << "), ";
        }
        cout << endl;
        cout << "L2:" << endl;
        cout << "T:" << endl;
        for (int j = 0; j < TakeoffQueue[i].size(); j++) {
            cout << "(" << TakeoffQueue[i][j] << "), ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

void print() {
    cout << "Step 1:" << endl;
    cout << "Landing plane:";
    for (int i = 1; i <= LandingNumber; i++) {
        cout << "(" << LandingPlane[i] << "," << oil[LandingPlane[i]] << ")";
    }
    cout << endl;
    for (int i = 1; i <= 4; i++) choose[i] = -1;
    for (int i = 2; i <= 1 + LandingNumber; i++) {
        LandingQueue[i].push_back(LandingPlane[i - 1]);
    }
    printqueue();

    cout << "Step 2:" << endl;
    cout << "Takeoff plane:";
    for (int i = 1; i <= TakeoffNumber; i++) {
        cout << "(" << TakeoffPlane[i] << "), ";
    }
    cout << endl;
    if (TakeoffNumber >= 1) {
        TakeoffQueue[1].push_back(TakeoffPlane[TakeoffNumber]);
        TakeoffNumber--;
    }
    for (int i = 4; i >= 1; i--) {
        if (TakeoffNumber == 0) break;
        TakeoffQueue[i].push_back(TakeoffPlane[TakeoffNumber]);
        TakeoffNumber--;
    }
    printqueue();

    cout << "Step 3:" << endl;
    cout << "emergency plane:" << endl;
    printqueue();

    cout << "Step 4:" << endl;
    for (int i = 1; i <= 4; i++) {
        if (LandingQueue[i].size()) {
            choose[i] = LandingQueue[i].front();
            LandingQueue[i].pop_front();
        }
        else if (TakeoffQueue[i].size()) {
            choose[i] = TakeoffQueue[i].front();
            TakeoffQueue[i].pop_front();
        }
    }
    printqueue();
    for (int i = 1; i <= 4; i++) {
        WaitingTime += TakeoffQueue[i].size();
    }
}

void run() {
    LandingNumber = rand_num(), TakeoffNumber = rand_num();
    TotalLandingPlane += LandingNumber;
    TotalTakeoffPlane += TakeoffNumber;
    for (int i = 1; i <= LandingNumber; i++) {
        LandingPlane[i] = LandingID;
        oil[LandingID] = rand_oil();
        Fuel += oil[LandingID];
        LandingID += 2;
    }
    for (int i = 1; i <= TakeoffNumber; i++) {
        TakeoffPlane[i] = TakeoffID;
        TakeoffID += 2;
    }
    print();
}

int main() {
  srand(time(NULL));
  int time = 5;

  cout << "Simulation Time: " << time << endl
       << endl;

  for (int i = 1; i <= time; i++)
  {
    run();
    
    cout << "How Many time Unit You Want to Simulate: " << time << endl;
    cout << "average landing waiting time: 0.000(s)\n";
    cout << "average takeoff waiting time: " << WaitingTime / (double)(TotalTakeoffPlane) << endl;
    cout << "average fuel saved: " << Fuel / (double)(TotalLandingPlane) << endl;
    cout << "total plane in emergency:" << 0 << endl;
    cout << "total plane crased:" << 0 << endl;

}