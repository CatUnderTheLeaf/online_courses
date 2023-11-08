# Writeup

The goal of this project is:
* write a home_service.sh file that will run all the nodes in this project;
* load a Gazebo world with a robot and RVIZ;
* show the marker at the pickup zone;
* hide the marker once the robot reaches the pickup zone;
* wait 5 seconds to simulate a pickup;
* show the marker at the drop off zone once the robot reaches it.

## Rubric Points

Here I will consider the [rubric points](https://review.udacity.com/#!/rubrics/2396/view) individually and describe how I addressed each point in my implementation.  

---
### Basic Requirements

I submitted all required files: ROS packages and Shell scripts. Scripts should be launched from the `scripts` folder. `map` and `rvizConfig` directories were moved to `my_robot` package.


### Simulation Setup

My simulation world and robot could properly load in Gazebo.


### Mapping

1. I wrote a test_slam.sh script file and launched it to manually test SLAM. For this task I used ROS `gmapping` package which provides laser-based SLAM. It creates a 2-D occupancy grid map from laserscan and pose data.

2. I created a functional map of the environment which would be used for localization and navigation tasks. Map is stored in `my_robot/map` directory. Map was saved with the `map_saver` command-line utility `rosrun map_server map_saver -f gmap`.


### Localization and Navigation

1. I created a test_navigation.sh script file to launch it for manual navigation test. My robot could navigate in the environment after a 2D Nav Goal command is issued. For localisation I used ROS package `amcl` that implements the adaptive Monte Carlo localization approach, which uses a particle filter to track the pose of a robot against a known map.

2. I created a pick_objects.sh file that will send multiple goals for the robot to reach. The robot travels to the desired pickup zone, displays a message that it reached its destination, waits 5 seconds, travels to the desired drop off zone, and displays a message that it reached the drop off zone.


### Home Service Functions

1. I wrote a add_marker.sh file that will publish a marker to rviz. The marker should initially be published at the pickup zone. After 5 seconds it should be hidden. Then after another 5 seconds it should appear at the drop off zone.

2. My robot perform home service tasks correctly. Here is my solution:
- in the `pick_objects.cpp` we have a `SimpleActionClient` which knows whether `move_base` has reached its goal or not, so no need in `add_marker.cpp` to subscribe to `odom` topic and check the robot's pose;
- in `add_marker` package I created a `PublishMarker` service:
```
geometry_msgs/PoseStamped marker_pose
int32 action
---
string msg_feedback
```
- also added a ServiceServer in `publish_markers` node, which gets Marker coordinates and depending on action adds or deletes it;
- new logic for picking up is implemented in `pick_markerobjects` node in `pick_objects` package;
- `pick_markerobjects` node has a goal list in the form (x, y, yaw, visualization_msgs/Marker.action);
- in the beginning it shows the marker of the first goal;
- when my robot reaches its goals a `ServiceClient`, which requests addition/deletion of a Marker, is called.