#include <robot_rescue/cancel_goal_controller.h>

CancelGoalController::CancelGoalController(ros::NodeHandle &nh) : ac_("move_base", true)
{
    cancel_sub_ = nh.subscribe("/robot_rescue", 10, &CancelGoalController::cancelCallback, this);  
    cmd_vel_pub_ = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ROS_INFO("Waiting for move_base action server to start.");
    ac_.waitForServer();
    ROS_INFO("Connected to move_base action server.");
}

CancelGoalController::~CancelGoalController()
{
}

void CancelGoalController::cancelCallback(const std_msgs::String::ConstPtr &msg)
{
    if (msg->data == "cancel_goal")
    {
        ROS_INFO("Received cancel_goal command. Cancelling the move_base goal and stopping the robot.");
        cancelGoalAndStop();
    }
}

void CancelGoalController::cancelGoalAndStop()
{
    ac_.cancelAllGoals();
    ROS_INFO("Sent cancel request to move_base.");

   
    geometry_msgs::Twist stop_msg;
    stop_msg.linear.x = 0.0;
    stop_msg.angular.z = 0.0;
    cmd_vel_pub_.publish(stop_msg);
    ROS_INFO("Published stop command to /cmd_vel.");
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "cancel_goal_controller_node");
    ros::NodeHandle nh;
    CancelGoalController controller(nh);

    ros::spin();

    return 0;
}