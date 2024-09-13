#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <fstream>
#include <iostream>
#include <string>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
class SendRobotToCS
{
private:
    double Position_X;
    double Position_Y;
    double Yaw;
    tf2::Quaternion quaternion;
    move_base_msgs::MoveBaseGoal goal;
    ros::Subscriber button_sub;
    typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
    MoveBaseClient ac;

public:
    void get_pose_from_json(std::string &fie_name);
    void send_to_CS();
    void boolCallback(const std_msgs::String::ConstPtr &msg);
    SendRobotToCS(ros::NodeHandle &nh);

    ~SendRobotToCS();
};
