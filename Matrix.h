#ifndef ___Class_Matrix
#define ___Class_Matrix

#include <iostream>

class Matrix{
  int row;
  int column;
  double* ptr;
public:
  Matrix();
  //constructor
   explicit  Matrix(int row,int column);
  //copy constructor
  Matrix(const Matrix&);
  Matrix(Matrix&);
  ~Matrix(){ delete[] ptr ;}
  double* operator[](int idx) const {return ptr + idx * column;}

  //whether size is same?
  bool equal_size(const Matrix& mat) const{
    return row == mat.row && column == mat.column;
  }
  //call
  Matrix operator()();
  //Substitution
  Matrix& operator=(const Matrix&);
  //positive operator+
  Matrix operator+() const{ return *this; }
  //negative operator-
  Matrix operator-() const;
  Matrix& operator+=(const Matrix&);
  Matrix& operator-=(const Matrix&);

  //Adding operator +
  Matrix operator+(const Matrix&) const;
  //Substruction operator -
  Matrix operator-(const Matrix&) const;
  //Mutiplication  operator *
  Matrix operator*(const Matrix&) const;

  //getter
  int get_row() const { return row; }
  int get_column() const { return column; }
  double* get_ptr() const{ return ptr;}
  //setter
  void set_matrix(double*);
  //method
  void print(int w = 0) const;
  Matrix inverse() const;
  Matrix t() const;
  Matrix ljoint (const Matrix&);
  double mean (int);
  double variance(int);
  double sum(int);
};

#endif
