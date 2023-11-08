#!/bin/sh
xterm  -e  " source ./../../devel/setup.bash; roslaunch my_robot world.launch" &
sleep 20
xterm  -e  " source ./../../devel/setup.bash; roslaunch my_robot gmapping.launch" &
sleep 10
xterm  -e  " source ./../../devel/setup.bash; roslaunch my_robot view_rviz.launch" &
sleep 10
xterm  -e  " source ./../../devel/setup.bash; rosrun teleop_twist_keyboard teleop_twist_keyboard.py"