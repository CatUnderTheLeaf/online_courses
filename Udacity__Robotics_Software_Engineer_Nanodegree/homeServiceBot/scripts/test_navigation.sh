#!/bin/sh
xterm  -e  " source ./../../devel/setup.bash; roslaunch my_robot world.launch" &
sleep 20
xterm  -e  " source ./../../devel/setup.bash; roslaunch my_robot amcl.launch" &
sleep 10
xterm  -e  " source ./../../devel/setup.bash; roslaunch my_robot view_rviz.launch"