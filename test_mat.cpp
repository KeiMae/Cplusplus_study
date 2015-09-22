#include <iostream>
#include "Matrix.h"

using namespace std;

int main(){
  Matrix x(10,1);
  Matrix y(10,1);
  double a[10][1] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0};
  double b[10][1] = {1.1,1.8,3.1,4.3,5.1,5.8,7.0,8.2,8.9,10.2};
  x.set_matrix(*a);
  y.set_matrix(*b);

  Matrix x_est(10,2);
  Matrix ones(10,1);
  for(int k = 0; k < 10; k++){
    ones[k][0] = 1.0;
  }
  x_est = ones.ljoint(x);
  cout << "x_est\n";
  x_est.print();

  Matrix z = (x_est.t() * x_est).inverse();
  cout << "z\n";
  z.print();
  Matrix zz = x_est.t() * y;
  cout << "zz\n";
  zz.print();
  Matrix zzz = z * zz;
  cout << "zzz\n";
  zzz.print();


}
