#include "ros/ros.h"
#include <add_markers/PublishMarker.h>
#include <visualization_msgs/Marker.h>

ros::Publisher marker_pub;

bool handle_marker_request(add_markers::PublishMarker::Request& req,
    add_markers::PublishMarker::Response& res)
{

    ROS_INFO("PublishMarkerRequest received");

    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = req.marker_pose.header.frame_id;
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = visualization_msgs::Marker::CUBE;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = req.action;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose = req.marker_pose.pose;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.2;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();


    marker_pub.publish(marker);

    // Return a response message
    res.msg_feedback = "Marker was published";
    ROS_INFO_STREAM(res.msg_feedback);

    return true;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "publish_markers_server");
    ros::NodeHandle n;

    marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    ros::ServiceServer service = n.advertiseService("/marker/publish", handle_marker_request);
    ROS_INFO("Ready to publish markers");

    // Handle ROS communication events
    ros::spin();

    return 0;
}