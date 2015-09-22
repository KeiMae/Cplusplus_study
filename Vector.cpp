#include <iostream>
#include "Vector.h"

//copy constructor
Vector::Vector(const Vector& copy_vec){
  max_row = copy_vec.max_row;
  for(int r = 0; r < max_row; r++){
    vec[r] = copy_vec.vec[r];
  }
}

//Substitution constructor
Vector& Vector::operator=(const Vector& x){
  if (&x != this){
    if(max_row != x.max_row){
      delete[] vec;
      max_row = x.max_row;
      vec = new double[max_row];
    }
    for(int r = 0; r < max_row; r++){
      vec[r] = x.vec[r];
    }
  }
  return *this;
}

Vector Vector::operator-() const {
  Vector tmp(max_row);
  for(int i = 0; i < max_row; i++){
    tmp[i] = -vec[i];
  }
  return tmp;
}

Vector& Vector::operator+=(const Vector& vec2) {
  if(equal_size(vec2)){
    for(int i = 0; i < max_row; i++){
      vec[i] += vec2.vec[i];
    }
  }
  return *this;
}

Vector& Vector::operator-=(const Vector& vec2) {
  if(equal_size(vec2)){
    for(int i = 0; i < max_row; i++){
      vec[i] -= vec2.vec[i];
    }
  }
  return *this;
}

Vector Vector::operator+(const Vector& vec2) const{
  Vector tmp(max_row);
  tmp += vec2;
  return tmp;
}

Vector Vector::operator-(const Vector& vec2) const{
  Vector tmp(max_row);
  tmp -= vec2;
  return tmp;
}


double Vector::operator*(const Vector& vec2) const{
  double tmp = 0.0;
  for(int k = 0; k < max_row; k++){
    tmp += vec[k] * vec2.vec[k];
  }
  return tmp;
}


///----friend function----///
Vector operator*(const double i, const Vector& vec2) {
  Vector tmp(vec2.max_row);
  for(int k = 0; k < vec2.max_row; k++){
    tmp[k] = i * vec2.vec[k];
  }
  return tmp;
}

Vector operator*(const Vector& vec2, const double i) {
  Vector tmp(vec2.max_row);
  for(int k = 0; k < vec2.max_row; k++){
    tmp[k] = i * vec2.vec[k];
  }
  return tmp;
}
/*
double operator*(const Vector& vec2, const Vector& vec3) {
   double tmp = 0;
  for(int k = 0; k < vec2.max_row; k++){
    tmp = vec3.vec[k] * vec2.vec[k];
  }
  return tmp;
}
*/
//---method
void Vector::PrintVec() const {
  for(int r = 0; r < max_row; r++){
    std::cout << vec[r] <<" ";
  }
  std::cout << "\n";
}

double Vector::mean() {
  double temp = 0;
  for(int i = 0; i < max_row; i++){
    temp += vec[i];
  }
  return temp / max_row;
}

double Vector::variance() {
  double temp = 0;
  for(int i = 0; i < max_row; i++){
    temp += vec[i] * vec[i];
  }
  return temp / max_row;
}
