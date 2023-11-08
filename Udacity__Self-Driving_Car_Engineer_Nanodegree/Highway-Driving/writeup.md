# **Highway Driving** 

## Writeup

---
[//]: # (Image References)
[video1]: ./video.mp4 "Video"


The goals / steps of this project are the following:
* To design a path planner that is able to create smooth, safe paths for the car to follow along a 3 lane highway with traffic.
* A successful path planner will be able to keep inside its lane, avoid hitting other cars, and pass slower moving traffic all by using localization, sensor fusion, and map data.
* Summarize the results with a written report


[//]: # (Image References)


## Rubric Points
### Here I will consider the [rubric points](https://review.udacity.com/#!/rubrics/1971/view) individually and describe how I addressed each point in my implementation.  

---
### Compilation

#### 1. The code compiles correctly. Code must compile without errors with cmake and make.

Yes, the code compiles without errors.

### Valid Trajectories

#### 1. The car is able to drive at least 4.32 miles without incident. The top right screen of the simulator shows the current/best miles driven without incident. Incidents include exceeding acceleration/jerk/speed, collision, and driving outside of the lanes. Each incident case is also listed below in more detail.

Yes, the car is able to drive at least 4.32 miles without incident. Here's a [link to my video result](./video.mp4)


#### 2. The car drives according to the speed limit. The car doesn't drive faster than the speed limit. Also the car isn't driving much slower than speed limit unless obstructed by traffic.

Yes, the car drives according to the speed limit. Almost always the car drives with maximum allowed speed, it slowes down to avoid collisions. 


#### 3. Max Acceleration and Jerk are not Exceeded. The car does not exceed a total acceleration of 10 m/s^2 and a jerk of 10 m/s^3.

Yes, max Acceleration and Jerk are not Exceeded. A car starts with null velocity and than slowly accelerates. During changing lines Jerk is not exceeded.


#### 4. Car does not have collisions. The car must not come into contact with any of the other cars on the road.

Yes, the car does not collide with other cars on the road.


#### 5. The car stays in its lane, except for the time between changing lanes. The car doesn't spend more than a 3 second length out side the lane lanes during changing lanes, and every other time the car stays inside one of the 3 lanes on the right hand side of the road.

Yes, the car stays in its lane, except for the time between changing lanes.


#### 6. The car is able to change lanes. The car is able to smoothly change lanes when it makes sense to do so, such as when behind a slower moving car and an adjacent lane is clear of other traffic.

Yes, when the car is behind a slower moving car and an adjacent lane is clear of other traffic the car is able to smoothly change lanes


### Reflection

#### 1. There is a reflection on how to generate paths. The code model for generating paths is described in detail. 

Path is generated in `void PathPlanner::PlanPath()` function in 'pathplanner.cpp'. My pipeline is:
1. Initialize Pathplanner with map waypoints.
2. Every timestamp update it with data from simulator.
3. Clear previous path.
4. At the beginning the car only accelerates till max velocity and stays in the middle lane.
5. Pathplanner is initialised with state "KL" (keep lane).
6. If we are in "KL" state we analize data from Sensor Fusion and make decision `bool PathPlanner::SenseCars(int path_size)`. Here we get a target lane id our car should move or stay in. For current lane we get all possible lanes our car can move in. Decision is made using cost functions:
  * `safety_cost` which penalizes for unsafe gaps, the smaller distance - the bigger cost;
  * `speed_cost` which penalizes for lower speed;
  * `change_lane_cost` which penalizes for changing lanes.
7. If we are in "ChL" (change lanes) state we just wait till our car will finally get to the target lane.
8. In both cases if the car is too close to the car moving ahead we just decrease the velocity.
9. Fill new path with points from the previous path, if there are any. `void PathPlanner::FillFromPreviousPath(int path_size)`.
10. Initialize spline object in function `vector<double> PathPlanner::setSpline(int path_size)` with 2 points from the last path and 3 waypoints in front of the car in target lane.
11. The path is generated using spline object and this code cares that a car moves with reference speed and without exceeding jerk and total acceleration.
