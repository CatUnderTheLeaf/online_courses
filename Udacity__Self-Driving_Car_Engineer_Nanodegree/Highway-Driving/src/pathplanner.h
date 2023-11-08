#ifndef PATHPLANNER_H
#define PATHPLANNER_H

#include "spline.h"
#include "json.hpp"
#include <string>
#include <vector>

// for convenience
using nlohmann::json;
using std::string;
using std::vector;

struct NextVals
{
  vector<double> next_x_vals;
  vector<double> next_y_vals;
};

struct Vehicle
{
  double x;
  double y;
  double s;
  double d;
  double vx;
  double vy;
  double yaw;
  double speed;
  int lane;
};


class PathPlanner {
 public:  
  PathPlanner();
  virtual ~PathPlanner();
  //   initialize planner with waypoints
  void Init(vector<double>& waypoints_x, vector<double>& waypoints_y, vector<double>& waypoints_s,
            vector<double>& waypoints_dx, vector<double>& waypoints_dy);
  // Update Planner with all car variables
  void UpdatePlanner(const std::vector<nlohmann::json>& prev_path_x, const std::vector<nlohmann::json>& prev_path_y, 
                     double& path_s, double& path_d, double& c_x, double& c_y, 
                  double& c_s, double& c_d, double& c_yaw, double& c_speed, const nlohmann::json& sens_fusion);

  void FillFromPreviousPath(int path_size);
  vector<double> setSpline(int path_size);
  float calculate_cost(const int& lane);
  float speed_cost(const int& lane);
  float safety_cost(const int& lane);
  float change_lane_cost(const int& lane);
  float lane_speed(const int& lane);
  
  vector <int> getLanes();
  void SenseCars(int path_size);
//   plan path
  void PlanPath();
  
//   path values
  NextVals nextVals;
//   car lane
  int target_lane = 1;
  double ref_vel = 0.1;
  double vel_max = 49.5;
  string state = "KL";
  bool is_at_vel_max = false;
  
 private:
  vector<double> map_waypoints_x;
  vector<double> map_waypoints_y;
  vector<double> map_waypoints_s;
  vector<double> map_waypoints_dx;
  vector<double> map_waypoints_dy;
  
  Vehicle car;
  vector<Vehicle> other_cars;

  // Previous path data given to the Planner
  std::vector<nlohmann::json> previous_path_x;
  std::vector<nlohmann::json> previous_path_y;
  // Previous path's end s and d values 
  double end_path_s;
  double end_path_d;

  // Sensor Fusion Data, a list of all other cars on the same side 
  //   of the road.
  nlohmann::json sensor_fusion;
  double dt = 0.02;  
  tk::spline spl;
  bool too_close = false;
  double safe_dist = 30;
};



#endif  // PATHPLANNER_H