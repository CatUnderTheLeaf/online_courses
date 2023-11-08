#!/bin/sh
xterm  -e  " source ./../../devel/setup.bash; roslaunch my_robot world.launch" &
sleep 30
xterm  -e  " source ./../../devel/setup.bash; roslaunch my_robot amcl.launch" &
sleep 30
xterm  -e  " source ./../../devel/setup.bash; roslaunch my_robot view_rviz.launch" &
sleep 10
xterm  -e  " source ./../../devel/setup.bash; roslaunch pick_objects pick_objects.launch"