#include <iostream>
#include <iomanip>
#include <cmath>
#include "Matrix.h"

// default constructor
Matrix::Matrix(){
  row = 1;
  column = 1;
  ptr = new double[ 1 * 1 ];
  ptr[0] = 0;
};

//constructor
Matrix::Matrix(int r,int c):row(r > 0 ? r : 1),column(c > 0 ? c : 1)
{
  ptr = new double[row * column];
  for(int i = 0; i < row; i++){
    for(int j = 0; j < column; j++){
      (*this)[i][j] = 0;
    }
  }
}

//copy constructor
Matrix::Matrix(const Matrix& mat){
  if(this != &mat){
    row = mat.row;
    column = mat.column;
    ptr = new double[row * column];
    for(int i = 0; i < row; i++){
      for(int j = 0; j < column; j++){
        (*this)[i][j] = mat[i][j];
      }
    }
  }
}

Matrix::Matrix(Matrix& mat){
  if(this != &mat){
    row = mat.row;
    column = mat.column;
    ptr = new double[row * column];
    for(int i = 0; i < row; i++){
      for(int j = 0; j < column; j++){
        (*this)[i][j] = mat[i][j];
      }
    }
  }
}

//call operator
Matrix Matrix::operator()(){
  Matrix mat(row, column);
return mat;
}

//Substitution
Matrix& Matrix::operator=(const Matrix& mat){
  if(&mat != this && equal_size(mat)){
    for(int i = 0; i < row; i++){
      for(int j = 0; j < column; j++){
        (*this)[i][j] = mat[i][j];
      }
    }
  }
  return *this;
}

//negative operator-
Matrix Matrix::operator-() const{
  Matrix temp(row,column);
  for(int i = 0; i < row; i++){
    for(int j = 0; j < column; j++){
      temp[i][j] = -(*this)[i][j];
    }
  }
  return temp;
}

Matrix& Matrix::operator+=(const Matrix& mat){
  if(equal_size(mat)){
    for(int i = 0; i < row; i++){
      for(int j = 0; j < column; j++){
        (*this)[i][j] += mat[i][j];
      }
    }
  }
  return *this;
}
Matrix& Matrix::operator-=(const Matrix& mat){
  if(equal_size(mat)){
    for(int i = 0; i < row; i++){
      for(int j = 0; j < column; j++){
        (*this)[i][j] -= mat[i][j];
      }
    }
  }
  return *this;
}

//Adding operator +
Matrix Matrix::operator+(const Matrix& mat) const{
  Matrix temp(*this);
  temp += mat;
  return temp;
}
//Substruction -
Matrix Matrix::operator-(const Matrix& mat) const{
  Matrix temp(*this);
  temp -= mat;
  return temp;
}
//Mutiplication  operator *
Matrix Matrix::operator*(const Matrix& mat) const{
  if(column != mat.row){
    return *this;
  }
  Matrix temp(row,mat.column);
  for(int i = 0; i < row; i++){
    for(int j = 0; j < mat.column; j++){
      for(int k = 0; k < column; k++){
        temp[i][j] += (*this)[i][k] * mat[k][j];
      }
    }
  }
  return temp;
}

//setter
void Matrix::set_matrix(double* x){
  for(int i = 0; i < row; i++){
    for(int j = 0; j < column; j++){
       (*this)[i][j] = x[ i * column + j ];
    }
  }
}

//--- method ---
void Matrix::print(int w) const {
  for(int i = 0; i < row; i++){
    for(int j = 0; j < column; j++){
      std::cout << std::setw(w) << (*this)[i][j]<<" ";
    }
    std::cout << "\n";
  }
}

Matrix Matrix::inverse() const {
  if((*this).row != (*this).column){
    return *this;
  }
  double buf;
  Matrix temp((*this).row,(*this).row);
  Matrix a((*this).row,(*this).row);
  a = *this;
  for(int i = 0; i < a.row; i++){
    for(int j = 0; j < a.row; j++){
      temp[i][j] = (i==j) ? 1:0;
    }
  }
  for(int i = 0; i < a.row; i++){
    buf = 1 / a[i][i];
    for(int j = 0; j < a.row; j++){
       a[i][j] *= buf;
       temp[i][j] *= buf;
    }
    for(int j=0; j < a.row; j++){
      if(i != j){
        buf = a[j][i];
        for(int k = 0; k < a.row; k++){
        a[j][k] -= a[i][k] * buf;
        temp[j][k] -= temp[i][k] * buf;
        }
      }
    }
  }
  return temp;
}

Matrix Matrix::t() const{
  Matrix tmp((*this).column,(*this).row);
  for(int i = 0; i < (*this).row; i++){
    for(int j = 0; j < (*this).column; j++){
      tmp[j][i] = (*this)[i][j];
    }
  }
  return tmp;
}

Matrix Matrix::ljoint(const Matrix& mat1){
  if( mat1.row != row ){return *this;}
  int new_column = mat1.column + column;
  Matrix tmp(mat1.row, new_column);
  for(int i = 0; i < row; i++){
    for(int j = 0; j < new_column; j++){
      if(j < column){
        tmp[i][j] = (*this)[i][j];
      }
      else{tmp[i][j] = mat1[i][ j - column ];}
    }
  }
  return tmp;
}

double Matrix::mean(int c){
  double sum = 0;
  for(int i = 0; i < row; i++){
    sum += (*this)[i][c];
  }
  return sum / row;
}

double Matrix::variance(int c){
  double sum = 0;
  for(int i = 0; i < row; i++){
    sum += pow(((*this)[i][c] - (*this).mean(c)), 2);
  }
  return sum /( row - 1);
}

double Matrix::sum(int c){
  double sum = 0;
  for(int i = 0; i < row; i++){
    sum += (*this)[i][c] ;
  }
  return sum;
}
