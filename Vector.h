#ifndef ___Class_Vector
#define ___Class_Vector

class Vector {
  int max_row;
  double* vec; //The pointer for the  first elements of array
public:
  //--constructor--
  explicit Vector( int row):max_row(row)
  {vec = new double[max_row];}
  //copy constructor
  Vector(const Vector& copy_vec);
  //Destructor
  ~Vector(){ delete[] vec; }
  //Substitution
  Vector& operator = (const Vector& x);

  bool equal_size(const Vector& vec) const{
    return max_row == vec.max_row;
  }

  double& operator[](int i) { return vec[i]; }

  Vector operator+() const { return *this; }
  Vector operator-() const;

  Vector& operator+=(const Vector&) ;
  Vector& operator-=(const Vector&) ;
  Vector operator+(const Vector&) const;
  Vector operator-(const Vector&) const;
  double operator*(const Vector&) const;

  friend Vector operator*(const double, const Vector&);
  friend Vector operator*(const Vector&, const double);
  //friend double operator*(const Vector&, const Vector&);

  //method
  void PrintVec() const;
  int size_of() const{ return max_row; }
  double mean();
  double variance();

};

#endif
