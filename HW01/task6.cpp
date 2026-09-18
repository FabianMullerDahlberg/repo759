#include <iostream>
using namespace std;


int main(int argc, char *argv[]) {
    int N = std::atoi(argv[1]);
    for (int i = 0; i <= N; i++) {
        cout << i << " ";  
    }cout << endl;
    for (int i = N; i >= 0; i--) {
        cout << i << " ";  
    }cout<< endl;
    
}
//g++ task6.cpp -Wall -O3 -std=c++17 -o task6