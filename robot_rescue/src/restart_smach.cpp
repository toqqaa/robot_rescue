#include <iostream>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <cstdio>

class RestartSmach
{
public:
    RestartSmach(ros::NodeHandle &nh) : counter_(0)
    {
        robot_rescue_sub_ = nh.subscribe("/robot_rescue", 100, &RestartSmach::robotStateCallback, this);
    }

    bool MessagesIsCalled()
    {

        if (robot_rescue_msg_ == "restart_smach")
        {
            robot_rescue_msg_ = " ";
            return true;
            
        }
        else
        {
            return false;
            ROS_INFO("no command");
        }

        return false;
    }

    void closeSMACH()
    {

        executeShellCommand("cd ~/arche_ws/src/Arche-Robots-App/scripts && ./close_SMACH.sh");
        ROS_INFO_STREAM("smach code closed ");
    }

    void startSMACH()
    {
        executeShellCommand("cd ~/arche_ws/src/Arche-Robots-App/scripts && ./start_SMACH.sh");
        ROS_INFO_STREAM("smach code restarting ");
    }

    void robotStateCallback(const std_msgs::String &msg)
    {
        robot_rescue_msg_ = msg.data;
    }

private:
    ros::Subscriber robot_rescue_sub_;
    std::string robot_rescue_msg_;
    int counter_;

    void executeShellCommand(const std::string &command)
    {
        FILE *pipe = popen(command.c_str(), "r");
        if (pipe)
        {
            pclose(pipe);
        }
        else
        {
            ROS_ERROR_STREAM("Failed to execute shell command: " << command);
        }
    }
};

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "smach_code_restart");
    ros::NodeHandle nh;

    RestartSmach controller(nh);

    ros::Rate loop_rate(50);
    while (ros::ok())
    {
        if (controller.MessagesIsCalled())
        {
            controller.closeSMACH();
            controller.startSMACH();

        }



        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
