#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <visualization_msgs/MarkerArray.h>


class PathDisplayNode{
public:
  PathDisplayNode(){
        path_sub_ = nh_.subscribe("/test_optim_node/local_plan",10,&PathDisplayNode::pathCallback, this);
        marker_pub_ = nh_.advertise<visualization_msgs::MarkerArray>("markers", 10);
  }        


private:

     void pathCallback(const nav_msgs::Path::ConstPtr& msg) {
        visualization_msgs::MarkerArray markers;
        int id = 0;

        for (const auto& pose : msg->poses) {
            // Create a new marker for each pose in the path
            visualization_msgs::Marker marker;
            marker.header.frame_id = msg->header.frame_id;
            marker.header.stamp = ros::Time::now();
            marker.ns = "path";
            marker.id = id++;
            marker.type = visualization_msgs::Marker::CYLINDER;
            marker.action = visualization_msgs::Marker::ADD;
            marker.pose = pose.pose;
            marker.scale.x = 0.2;
            marker.scale.y = 0.2;
            marker.scale.z = 0.2;
            marker.color.a = 1;
            marker.color.r = 1;
            marker.color.g = 1;
            marker.color.b = 0.0;

            markers.markers.push_back(marker);
        }

        marker_pub_.publish(markers); 
    }

  ros::NodeHandle nh_;
  ros::Subscriber path_sub_;
  ros::Publisher  marker_pub_;
};


int main(int argc, char** argv) {
    ros::init(argc, argv, "path_display");
    PathDisplayNode node;
    ros::spin();
    return 0;
}