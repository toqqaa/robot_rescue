#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <fstream>
#include <iostream>
#include <string>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>

class RobotInitialPose
{
private:
    double Position_X;
    double Position_Y;
    double Yaw;
    tf2::Quaternion quaternion;
    geometry_msgs::PoseWithCovarianceStamped initial_pose;
    ros::Publisher initial_pose_pub;
    ros::Subscriber button_sub;
   
    

public:
    void get_pose_from_json(std::string &fie_name);
    void set_initial_pose();
     void boolCallback(const std_msgs::String::ConstPtr& msg);
    RobotInitialPose(ros::NodeHandle &nh);
    
    
    ~RobotInitialPose();
};
