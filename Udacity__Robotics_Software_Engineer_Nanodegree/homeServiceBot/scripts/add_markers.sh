#!/bin/sh
xterm  -e  " source ./../../devel/setup.bash; roslaunch my_robot world.launch" &
sleep 20
xterm  -e  " source ./../../devel/setup.bash; roslaunch my_robot amcl.launch" &
sleep 40
xterm  -e  " source ./../../devel/setup.bash; roslaunch my_robot view_rviz.launch" &
sleep 30
xterm  -e  " source ./../../devel/setup.bash; rosrun add_markers add_markers"