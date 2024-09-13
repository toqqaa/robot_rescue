#include <robot_rescue/send_robot_to_cs.h>

SendRobotToCS::SendRobotToCS(ros::NodeHandle &nh) : ac("move_base", true)
{

   button_sub = nh.subscribe("/robot_rescue", 10, &SendRobotToCS::boolCallback, this);
}

SendRobotToCS::~SendRobotToCS()
{
}

void SendRobotToCS::boolCallback(const std_msgs::String::ConstPtr &msg)
{
if (msg->data=="send_to_cs")
{
   send_to_CS();
}

   
}

void SendRobotToCS::get_pose_from_json(std::string &filename)
{

   std::ifstream file(filename);

   Json::Value JsonFile;
   Json::Reader reader;

   // Using the reader, we are parsing the json file
   reader.parse(file, JsonFile);

   // create new vlaue object to acess "locations" array of object

   for (const auto &location : JsonFile)
   {

      if (location["Name"] == "new cs")
      {
         //   std::cout << "x pose is:\n" << item["Position_X"].asFloat() << std::endl;
         Position_X = location["Position_X"].asDouble();
         Position_Y = location["Position_Y"].asDouble();
         Yaw = location["Yaw"].asDouble();
      }
   }
}

void SendRobotToCS::send_to_CS()
{

   quaternion.setRPY(0, 0, Yaw);
   goal.target_pose.header.frame_id = "map";
   goal.target_pose.header.stamp = ros::Time::now();

   goal.target_pose.pose.position.x = Position_X;
   goal.target_pose.pose.position.y = Position_Y;
   goal.target_pose.pose.orientation.z = quaternion.z();
   goal.target_pose.pose.orientation.w = quaternion.w();

   ROS_INFO("Sending goalto cs");
   ac.sendGoal(goal);
   ac.waitForResult();
   if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("reached CS");
   else
      ROS_INFO("could't reach CS");
}

int main(int argc, char **argv)
{

   ros::init(argc, argv, "send_initial_pose_node");
   ros::NodeHandle nh;

   SendRobotToCS robot_to_cs(nh);

   // Get the home directory
   const char *home_dir = getenv("HOME");
   if (home_dir == nullptr)
   {
      std::cerr << "Failed to get the home directory." << std::endl;
      return 1;
   }

   // Construct the absolute path to the JSON file
   std::string cs_filename = std::string(home_dir) + "/arche_ws/src/Robots-DataBase/robot_task/robot_cs.json";
   robot_to_cs.get_pose_from_json(cs_filename);

   ros::Rate loop_rate(10);

   while (ros::ok())
   {
      // robot_pose.set_initial_pose();
      loop_rate.sleep();
      ros::spin();
   }

   return 0;
}