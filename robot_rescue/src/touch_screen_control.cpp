#include <iostream>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <cstdio>

class TouchScreenController {
public:
    TouchScreenController() : counter_(0) {
        robot_rescue_sub_ = nh_.subscribe("/robot_rescue", 100, &TouchScreenController::robotStateCallback, this);
    }

    void run() {
        ros::Rate loop_rate(50);
        while (ros::ok()) {
            processMessages();
            ros::spinOnce();
            loop_rate.sleep();
        }
    }

private:
    ros::NodeHandle nh_;
    ros::Subscriber robot_rescue_sub_;
    std::string robot_rescue_msg_;
    int counter_;

    void robotStateCallback(const std_msgs::String &msg) {
        robot_rescue_msg_ = msg.data;
    }

    void processMessages() {
        if (counter_ == 0) {
            counter_ = 1;
        }

        if (robot_rescue_msg_ == "activate_ts" && counter_ == 1) {
            activateTouchScreen();
            robot_rescue_msg_ = " ";
        }

        if (robot_rescue_msg_ == "deactivate_ts" && counter_ == 1) {
            deactivateTouchScreen();
            counter_ = 0;
            robot_rescue_msg_ = " ";
        }
    }

    void activateTouchScreen() {
        ROS_INFO_STREAM("Touch screen activated");
        executeShellCommand("cd ~/arche_ws/src/Arche-Robots-App/scripts && ./activate_ts.sh");
    }

    void deactivateTouchScreen() {
        ROS_INFO_STREAM("Touch screen deactivated");
        executeShellCommand("cd ~/arche_ws/src/Arche-Robots-App/scripts && ./deactivate_ts.sh");
    }

    void executeShellCommand(const std::string &command) {
        FILE *pipe = popen(command.c_str(), "r");
        if (pipe) {
            pclose(pipe);
        } else {
            ROS_ERROR_STREAM("Failed to execute shell command: " << command);
        }
    }
};

int main(int argc, char *argv[]) {
    ros::init(argc, argv, "touch_screen_control");

    TouchScreenController controller;
    controller.run();

    return 0;
}
