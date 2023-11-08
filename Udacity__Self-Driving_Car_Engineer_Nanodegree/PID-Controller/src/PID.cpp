#include "PID.h"
#include <limits>
#include <iostream>
#include <vector>
#include <numeric>

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * Initialize PID coefficients (and errors, if needed)
   */
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;

  d_error = 0;
  i_error = 0;
  p_error = std::numeric_limits<double>::max();
  
  error = 0;
  avg_error = 0;
  
}

void PID::UpdateError(double cte) {
  /**
   * Update PID errors based on cte.
   */
  
  if (p_error == std::numeric_limits<double>::max()) {
    p_error = cte;
  }
  
  d_error = cte - p_error;
  i_error += cte;
  p_error = cte;
  
  avg_error = i_error / iter;
}

double PID::TotalError() {
  /**
   * Calculate and return the total error
   */
  
//   return -Kp * p_error - Ki * i_error - Kd * d_error;
  return Kp * p_error + Ki * i_error + Kd * d_error;
}

void PID::Twiddle() {
  /**
   * Twiddle params
   */
  double sum = dp[0] + dp[1] + dp[2];
  std::cout << "Sum of dp coeff: " << sum << std::endl;
  if (sum > tol) {
    std::cout << "Iterations: " << iter << std::endl;
    std::cout << "param_ind: " << param_ind << std::endl;
    std::cout << "Kp: " << Kp<< "Ki: " << Ki<< "Kd: " << Kd << std::endl;
    if (iter == 0) {
      p[param_ind] += dp[param_ind];
      best_err = std::numeric_limits<double>::max();
      std::cout << "best_err in the beginning: " << best_err << std::endl;
      increase = true;
    }
    else {
      //     increase coefficients
      if (increase) {
        std::cout << "best_err in the increasing: " << best_err << std::endl;
        std::cout << "TotalError in the increasing: " << TotalError()  << std::endl;
        if (TotalError() > 0 && TotalError() < best_err) {
          best_err = TotalError();
          dp[param_ind] *= 1.1;
          param_ind = (param_ind + 1) % 3;
          p[param_ind] += dp[param_ind];
          increase = true;
        }
        else {
          p[param_ind] -= 2 * dp[param_ind];
          increase = false;
        }    
    
    //     decrease coefficients
      } else {
        std::cout << "best_err in the decreasing: " << best_err << std::endl;
        std::cout << "TotalError in the increasing: " << TotalError()  << std::endl;
        if (TotalError() > 0 && TotalError() < best_err) {
          best_err = TotalError();
          dp[param_ind] *= 1.1;
          param_ind = (param_ind + 1) % 3;
          p[param_ind] += dp[param_ind];
          increase = true;
        }
        else {
          p[param_ind] += dp[param_ind];
          dp[param_ind] *= 0.9;  
          param_ind = (param_ind + 1) % 3;
          p[param_ind] += dp[param_ind];
          increase = true;
        }
      }
    }
    
  }
 Init(p[0], p[1], p[2]);
 iter += 1;    
}