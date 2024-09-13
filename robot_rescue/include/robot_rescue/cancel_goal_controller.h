#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <string>

class CancelGoalController
{
private:
   
    ros::Subscriber cancel_sub_;     
    ros::Publisher cmd_vel_pub_;     
    typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
    MoveBaseClient ac_;              

public:
    // Constructor and Destructor
    CancelGoalController(ros::NodeHandle &nh);
    ~CancelGoalController();

    void cancelGoalAndStop();  
    void cancelCallback(const std_msgs::String::ConstPtr &msg);  
};
