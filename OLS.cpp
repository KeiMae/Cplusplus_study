#include <iostream>
#include <cmath>
#include "matrix.h"

class OLS{
  Matrix x;
  Matrix y;
  Matrix y_hat;
  Matrix beta;
  Matrix tval_mat;
  Matrix pval_mat;
  Matrix residual;
  Matrix std_error_mat; //standard errors of the coefficients
  double R2;
  double ajusted_R2;
  double resid_var;
public:

  OLS(Matrix x1, Matrix y1):x(x1),y(y1)
                           ,beta(x1.get_column()+1, y1.get_column())
                           ,residual(y1.get_row(), y1.get_column())
                           ,tval_mat(1, x1.get_column() + 1 )
                           ,pval_mat(1, x1.get_column() + 1 )
                           ,std_error_mat(1, x1.get_column() + 1)
                           ,y_hat(y.get_row(), y.get_column())
  {
    if (x.get_row() != y.get_row()){
      std::cout << "被説明係数と説明変数の数は一致していなければなリません。\n";
      std::cout << "被説明変数数：" << y.get_row() << "説明変数数：" << x.get_row() << "\n";
    }

    Matrix x_est(x1.get_row(), x1.get_column()+1);
    Matrix ones(x1.get_row(),1);
    for(int k = 0; k < x1.get_row(); k++){
      ones[k][0] = 1.0;
    }
    x_est = ones.ljoint(x);
    Matrix beta1 = (x_est.t() * x_est).inverse();
    Matrix beta2 = x_est.t() * y;
    beta = beta1 * beta2;
    y_hat = x_est * beta;
    residual = y - y_hat;
    resid_var = calc_resid_var();
    std_error_mat = calc_std_error_mat(x_est);
    std::cout << "finish calc std error\n";
    R2 = calc_R2();
    ajusted_R2 = calc_ajusted_R2();
    tval_mat = calc_tval_mat();
    std::cout << "finish calc tval\n";
    pval_mat = calc_pval_mat('l');
  }

  //getters
  Matrix get_beta(){ return beta; }
  Matrix get_x(){ return x; }
  Matrix get_y(){ return y; }
  Matrix get_y_hat(){ return y_hat; }
  Matrix get_std_error_mat(){ return std_error_mat; }
  Matrix get_tval_mat(){ return tval_mat; }
  Matrix get_pval_mat(){ return pval_mat; }


  double get_residual_var(){ return resid_var; }
  double get_R2(){ return R2; }
  double get_ajusted_R2(){ return ajusted_R2; }


  //member functions
  double calc_resid_var(){
    Matrix tmp(y.get_column(),1);
    tmp = residual.t() * residual;
    return tmp[0][0] / ( y.get_row() - x.get_column() -1 );
  }

  Matrix calc_std_error_mat(Matrix& x_est){
    Matrix tmp(1,x_est.get_column());
    Matrix tmp2(x_est.get_column(),x_est.get_column());
    tmp2 = (x_est.t() * x_est).inverse();
    for(int i = 0; i < x_est.get_column(); i++){
      tmp[0][i] =sqrt( resid_var * tmp2[i][i] );
    }
    return tmp;
   }

   double calc_R2() {
    double denomi = 0;
    double neume = 0;
    for(int r = 0; r < y.get_row(); r++){
      denomi += pow(y[r][0] - y.mean(0),2);
      neume += pow(y_hat[r][0] - y.mean(0),2);
    }
    double tmp =  neume / denomi;
    return tmp;
   }

   double calc_ajusted_R2() {
     double tmp;
     double tmp1, tmp2;
     tmp = x.get_row() - x.get_column();
     tmp1 = (x.get_row() - 1) / tmp;
     tmp2 = (1 - R2) * tmp1;
     return 1 - tmp2;
   }

   Matrix calc_tval_mat(){
     Matrix tmp_(1, beta.get_row());
     for(int c = 0; c < beta.get_row(); c++){
       tmp_[0][c] = beta[c][0] / std_error_mat[0][c];
     }
     return tmp_;
   }

   double gamma_func(double z){ // using starling's fomula
     double t = 0;
     double temp = 0;
     double span = 1;
     while(t < 100){
       temp += (pow(t,z-1) * exp(-t)) * span;
       t += span;
     }
     return temp;
   }

   double t_dist_func(double t, double freedom){
     double first = gamma_func((freedom + 1)/2) ;
     double second = pow((1 + (pow(t,2) / freedom)), -(freedom + 1)/2);
     double denomi = (sqrt(freedom * M_PI)) * gamma_func(freedom/2);
     return (first * second) / denomi;

   }

    Matrix calc_pval_mat(char typ){
     Matrix tmp(1,tval_mat.get_column());
     double freedom = double(x.get_row() - x.get_column() - 1);
     double span = 0.1;
     for(int c = 0; c < tval_mat.get_column(); c++){
       if(typ == 'l'){//integration initial
         double i = -20;
         while(i < tval_mat[0][c])
         {
           tmp[0][c] += t_dist_func(i, freedom) * span;
           i += span;
         }
       }
       else if(typ == 'b'){
         double i = -20;
         double integ = 0;
         while(i < tval_mat[0][c]){
           integ += t_dist_func(i, freedom) * span;
           if(integ > 0.25){ tmp[0][c] += t_dist_func(i, freedom) * span;}
           i += span;
         }
       }
       else{std::cout<<"検定のタイプを入れてください。両側->b 左側->l\n";}
     }
     return tmp;

   }



};

int main(){
  Matrix x(10,1);
  Matrix x2(10,2);
  Matrix y(10,1);
  double a[10][1] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0};
  double a2[10][2] = {
                      {1.0,0.2},
                      {2.0,2.1},
                      {3.0,2.9},
                      {4.0,3.5},
                      {5.0,4.7},
                      {6.0,3.5},
                      {7.0,2.1},
                      {8.0,4.5},
                      {9.0,5.7},
                      {10.0,8.1}};
  double b[10][1] = {1.1,1.8,3.1,4.3,5.1,5.8,7.0,8.2,8.9,10.2};
  x.set_matrix(*a);
  x2.set_matrix(*a2);
  y.set_matrix(*b);

  OLS result( x , y );
  std::cout << "in the Matrix\n";
  result.get_x().print();
  result.get_y().print();
    result.get_y_hat().print();
  std::cout << "\n";
  result.get_beta().print();
  std::cout << "\n";
  std::cout << "\n";
  std::cout << result.get_residual_var();
  std::cout << "\n";
  result.get_std_error_mat().print();
  std::cout << "\n";
  std::cout << result.get_R2();
  std::cout << "\n";
  std::cout << result.get_ajusted_R2();
  std::cout << "\n";
  result.get_tval_mat().print();
  std::cout << "\n";
  result.get_pval_mat().print();
  std::cout << "\n";
}
