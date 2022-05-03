#include <string>
#include <iostream>
using namespace std;
int main() {
  for (int i = 0; i < 60; i++){
    cout << "\"";
    if (i < 10){
      cout << "0";
    }
    cout << i << "\",";
  }
}