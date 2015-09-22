#include <iostream>
#include "Vector.h"


int main(){
  Vector a(3);
  for(int i = 0; i<3; i++){
    a[i] = double(i * 2.2);
  }
  a.PrintVec();
  Vector b(3);
  for(int i = 0; i<3; i++){
    b[i] = double(i + 2.6);
  }
  std::cout<<"\n";
  std::cout << a * b <<"\n";
}
