#ifndef PID_H
#define PID_H
#include <vector>

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();
  
// Twiddle PID params
  void Twiddle();
  
 private:
  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;

  /**
   * PID Coefficients
   */ 
  double Kp;
  double Ki;
  double Kd;
  
//   Twiddle params
  std::vector<double> p = {0, 0, 0};
  std::vector<double> dp = {1, 1, 1};
  int iter = 0;
  double tol = 0.2;
  int param_ind = 0;
  double error;
  double avg_error;
  double best_err;
//   flag for increasing or decreasing Coefficients
  bool increase = false;
};

#endif  // PID_H