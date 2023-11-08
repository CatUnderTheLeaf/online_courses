#include "pathplanner.h"
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <algorithm>
#include "json.hpp"
#include "Eigen-3.3/Eigen/Core"
#include "Eigen-3.3/Eigen/QR"
#include "helpers.h"
#include "spline.h"
using nlohmann::json;

PathPlanner::PathPlanner() {}

PathPlanner::~PathPlanner() {}

//   initialize planner with waypoints
void PathPlanner::Init(vector<double>& waypoints_x, vector<double>& waypoints_y, vector<double>& waypoints_s,
            vector<double>& waypoints_dx, vector<double>& waypoints_dy) {
  
   map_waypoints_x = waypoints_x;
   map_waypoints_y = waypoints_y;
   map_waypoints_s = waypoints_s;
   map_waypoints_dx = waypoints_dx;
   map_waypoints_dy = waypoints_dy;

}

// Update Planner with all car variables
void PathPlanner::UpdatePlanner(const std::vector<nlohmann::json>& prev_path_x, const std::vector<nlohmann::json>& prev_path_y, 
                     double& path_s, double& path_d, double& c_x, double& c_y, 
                  double& c_s, double& c_d, double& c_yaw, double& c_speed, const nlohmann::json& sens_fusion) {
  car.x = c_x;
  car.y = c_y;
  car.s = c_s;
  car.d = c_d;
  car.yaw = c_yaw;
  car.speed = c_speed;
  car.lane = get_d(car.d);

  // Previous path data given to the Planner
  previous_path_x = prev_path_x;
  previous_path_y = prev_path_y;
  // Previous path's end s and d values 
  end_path_s = path_s;
  end_path_d = path_d;

  // Fill Sensor Fusion Data, a list of all other cars on the same side 
  //   of the road.
  other_cars.clear();
  sensor_fusion = sens_fusion;
  for (int i = 0; i < sensor_fusion.size(); ++i) {
    Vehicle another_car;
    another_car.x = sensor_fusion[i][1];
    another_car.y = sensor_fusion[i][2];
    another_car.vx = sensor_fusion[i][3];
    another_car.vy = sensor_fusion[i][4];
    another_car.s = sensor_fusion[i][5];
    another_car.d = sensor_fusion[i][6];
    another_car.speed = sqrt(another_car.vx*another_car.vx + another_car.vy*another_car.vy);
    another_car.lane = get_d(another_car.d);    
    other_cars.push_back(another_car);
  }
}

//  Fill nextVals with values from previous path
void PathPlanner::FillFromPreviousPath(int path_size) {
 for (int i = 0; i < path_size; i++) {
   nextVals.next_x_vals.push_back(previous_path_x[i]);
   nextVals.next_y_vals.push_back(previous_path_y[i]);
 }
}

//   set spline for new trajectory
vector<double> PathPlanner::setSpline(int path_size) {
  double pos_x = car.x;
  double pos_y = car.y;  
  double angle = deg2rad(car.yaw);
  
  std::vector<double> X, Y;
  
  if (path_size < 2) {
    double pos_x2 = pos_x - cos(car.yaw);
    double pos_y2 = pos_y - sin(car.yaw);
    X.push_back(pos_x2);
    X.push_back(car.x);
  
    Y.push_back(pos_y2);
    Y.push_back(car.y);
  } else {
    pos_x = previous_path_x[path_size-1];
    pos_y = previous_path_y[path_size-1];

    double pos_x2 = previous_path_x[path_size-2];
    double pos_y2 = previous_path_y[path_size-2];
    angle = atan2(pos_y-pos_y2,pos_x-pos_x2);
    
    X.push_back(pos_x2);
    X.push_back(pos_x);
  
    Y.push_back(pos_y2);
    Y.push_back(pos_y);
  }
  
  vector<double> wp1 = getXY((car.s+50), (2 + 4*target_lane), map_waypoints_s, map_waypoints_x, map_waypoints_y);
  vector<double> wp2 = getXY((car.s+70), (2 + 4*target_lane), map_waypoints_s, map_waypoints_x, map_waypoints_y);
  vector<double> wp3 = getXY((car.s+90), (2 + 4*target_lane), map_waypoints_s, map_waypoints_x, map_waypoints_y);
  
  X.push_back(wp1[0]);
  X.push_back(wp2[0]);
  X.push_back(wp3[0]);
  
  Y.push_back(wp1[1]);
  Y.push_back(wp2[1]);
  Y.push_back(wp3[1]);
  
  for (int i = 0; i < X.size(); ++i) {
    double shift_x = X[i] - pos_x;
    double shift_y = Y[i] - pos_y;
    
    X[i] = shift_x*cos(0-angle) - shift_y*sin(0-angle);
    Y[i] = shift_x*sin(0-angle) + shift_y*cos(0-angle);
  }
  
  spl.set_points(X, Y);
  
  return {pos_x, pos_y, angle};
}

vector <int> PathPlanner::getLanes() {
  switch (car.lane) {
        case 0: return {0, 1};
        case 1: return {0, 1, 2};
        case 2: return {1, 2};
        default: return {car.lane};
    }
}
  
//   get speed of a lane in some distance range around our car
float PathPlanner::lane_speed(const int& lane) {
  double avg_speed = 0;
  int num = 0;
  for (int i = 0; i < other_cars.size(); ++i) {
//     another car is in visible range with our car, and in target lane 
    if ((other_cars[i].lane) == lane && (fabs(other_cars[i].s - car.s) < safe_dist)) {
      avg_speed += other_cars[i].speed;
      ++num;
    }
  }
  if (num) {
    return avg_speed/num;
  } else {
    // Found no vehicle in the lane
    return vel_max;
  }
  
}  

  // Cost becomes higher for lanes 
  //   that have traffic slower than vehicle's target speed.
float PathPlanner::speed_cost(const int& lane) {

  float final_speed = lane_speed(lane);
  float cur_speed = lane_speed(car.lane);
  float cost = (2.0*vel_max - cur_speed - final_speed)/vel_max;

  return cost;
}   

// cost for gap between cars
float PathPlanner::safety_cost(const int& lane) {
  double cost = 0.0;
  int path_size = previous_path_x.size();    
  for (int i = 0; i < other_cars.size(); ++i) {
    //     another car is in unsafe range with our car in target lane
    double check_car_s = other_cars[i].s + ((double)path_size*dt*other_cars[i].speed);
//     if ((other_cars[i].lane == lane) && (fabs(check_car_s - car.s) < safe_dist * vel_max / ref_vel)) {
    if ((other_cars[i].lane == lane) && (fabs(other_cars[i].s - car.s) < safe_dist)) {
//       cost += 1.0;
//       cost is higher when other car is closer to our car
      cost = std::max(cost, (safe_dist-fabs(other_cars[i].s - car.s))/safe_dist);
    }
  }
  return cost;
}

// cost for changing lanes
float PathPlanner::change_lane_cost(const int& lane) {
  if (car.lane == lane) {
     return 0;
  } else {
    return 1;
  }
}

// Sum weighted cost functions to get total cost
float PathPlanner::calculate_cost(const int& lane) {
  // Sum weighted cost functions to get total cost for trajectory.
  float cost = 0.0;

  std::cout << ", cost to go: speed: " << speed_cost(lane) << ", safety: " << safety_cost(lane)  << ", change_lane: " << change_lane_cost(lane) << std::endl;
  cost += speed_cost(lane) + safety_cost(lane) + change_lane_cost(lane);

  return cost;
}  
  
//   analize data from Sensor Fusion and make decisions
void PathPlanner::SenseCars(int path_size) {
  if (path_size > 0) {
    car.s = end_path_s;
  }
  too_close = false;
  if (state == "KL") {
    //      get all possible lanes for our car movement
    vector <int> lanes = getLanes();
    //      for each possible lane calculate costs and select best lane
    int best_lane = car.lane;
    float min_cost = 999999;
    for (int j = 0; j < lanes.size(); ++j) {
      std::cout << lanes[j];
      float cost = calculate_cost(lanes[j]);

      if (cost < min_cost) {
        min_cost = cost;
        best_lane = lanes[j];
      }
    }
    std::cout << std::endl; 
    target_lane = best_lane; 
    std::cout << "target_lane" << target_lane << std::endl; 
    if (target_lane == car.lane) {
      state = "KL";
    } else {
      state = "ChL";
    }
  }
  //       if state == "ChL"
  else {
    if (target_lane == car.lane) {
      state = "KL";
      too_close = true;
    } else {
      state = "ChL";
    }
  }
  
  for (int i = 0; i < other_cars.size(); ++i) {
    double check_car_s = other_cars[i].s + ((double)path_size*dt*other_cars[i].speed);
//     if a car is in our lane, is ahead in some range and is slower then our carwe should slow down
    if ((car.lane == other_cars[i].lane) && (check_car_s > car.s) && ((check_car_s - car.s) < safe_dist) && (other_cars[i].speed < car.speed)) {
      
      too_close = true;
    }
  }

}

//   plan path
void PathPlanner::PlanPath() {
  nextVals.next_x_vals.clear();
  nextVals.next_y_vals.clear();
  int path_size = previous_path_x.size();

  vector<double> poses = setSpline(path_size);
  double pos_x = poses[0];;
  double pos_y = poses[1];  
  double angle = poses[2];

  if (is_at_vel_max) {
    SenseCars(path_size);
  }
  
  if (too_close) {
    ref_vel -= .224;
  } else if (ref_vel < vel_max) {
    ref_vel += .224;
    if ((is_at_vel_max == false) && (ref_vel > vel_max)) {
      is_at_vel_max = true;
    }
  } 
 //  Fill nextVals with values from previous path 
  FillFromPreviousPath(path_size);
  
  double target_x = 30.0;
  double target_y = spl(target_x);
  double target_dist = sqrt(target_x*target_x + target_y*target_y);
  
  double x_add_on = 0;
 
  for (int i = 0; i < 50-path_size; i++) {
    double N = target_dist/(dt*ref_vel/2.24);
    double x_point = x_add_on + (target_x)/N;
    double y_point = spl(x_point);

    x_add_on = x_point;

    double x_ref = x_point;
    double y_ref = y_point;

    x_point = x_ref*cos(angle) - y_ref*sin(angle);
    y_point = x_ref*sin(angle) + y_ref*cos(angle);

    x_point += pos_x;
    y_point += pos_y;

    nextVals.next_x_vals.push_back(x_point);
    nextVals.next_y_vals.push_back(y_point);
      
  }
 
}