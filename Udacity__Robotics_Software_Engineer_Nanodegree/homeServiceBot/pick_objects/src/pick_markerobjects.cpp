#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <add_markers/PublishMarker.h>
#include <tf2/LinearMath/Quaternion.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> PickObjects;
ros::ServiceClient client;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "simple_navigation_goals");
  ros::NodeHandle n;

  // Define a client service capable of requesting services from publish_markers_server
  client = n.serviceClient<add_markers::PublishMarker>("/marker/publish");

  // list of goals 
  std::vector<std::vector<double> > goal_list
  {
    // x, y, yaw, visualization_msgs/Marker.action for publish_markers service (0 - add, 2 - delete)
    {3.0, 2.0, 1.5707, 2.0},
    {3.0, -5.0, 0.0, 0.0}
  };
  std::vector<std::string> goal_name
  { "pickup zone", "drop off zone" };
  add_markers::PublishMarker srv;
  

  //tell the action client that we want to spin a thread by default
  PickObjects ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the pick_object action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;
  

  // for (auto& target : goal_list)
  for (int i=0; i < goal_list.size(); i++)
  {
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
    goal.target_pose.pose.position.x = goal_list[i][0];
    goal.target_pose.pose.position.y = goal_list[i][1];
    goal.target_pose.pose.position.z = 0.0;
    tf2::Quaternion myQuaternion;
    myQuaternion.setRPY( 0, 0, goal_list[i][2] ); 
    goal.target_pose.pose.orientation.x = myQuaternion.x();
    goal.target_pose.pose.orientation.y = myQuaternion.y();
    goal.target_pose.pose.orientation.z = myQuaternion.z();
    goal.target_pose.pose.orientation.w = myQuaternion.w();

    if (i==0)
    {
      srv.request.marker_pose = goal.target_pose;
      // add marker for the first goal
      srv.request.action = 0;

      // Call the publish_markers service and pass the requested target_pose
      if (!client.call(srv))
          ROS_ERROR("Failed to call service PublishMarker");
    }

    ROS_INFO("Sending goal location ...");
    ac.sendGoal(goal);
    ac.waitForResult();
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
      ROS_INFO_STREAM("Hooray, the base moved to the " << goal_name[i]);

      srv.request.marker_pose = goal.target_pose;
      srv.request.action = goal_list[i][3];

      // Call the publish_markers service and pass the requested target_pose
      if (!client.call(srv))
          ROS_ERROR("Failed to call service PublishMarker");
    }
    else
      ROS_INFO("The base failed to move to the goal position");
    ros::Duration(5.0).sleep();
  }

  // Handle ROS communication events
  ros::spin();

  return 0;
}