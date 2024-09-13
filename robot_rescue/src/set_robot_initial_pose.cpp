#include <robot_rescue/set_robot_initial_pose.h>

RobotInitialPose::RobotInitialPose(ros::NodeHandle &nh)
{
   initial_pose_pub = nh.advertise<geometry_msgs::PoseWithCovarianceStamped>("/initialpose", 10);
   button_sub = nh.subscribe("/robot_rescue", 10, &RobotInitialPose::boolCallback, this);
}

RobotInitialPose::~RobotInitialPose()
{
}

void RobotInitialPose::boolCallback(const std_msgs::String::ConstPtr &msg)
{

   if (msg->data == "set_initial_pose")
   {
      set_initial_pose();
   }
}
void RobotInitialPose::get_pose_from_json(std::string &filename)
{

   std::ifstream file(filename);

   Json::Value JsonFile;
   Json::Reader reader;

   // Using the reader, we are parsing the json file
   reader.parse(file, JsonFile);

   // create new vlaue object to acess "locations" array of object
   Json::Value RobotLocations = JsonFile["locations"];

   for (const auto &location : RobotLocations)
   {

      if (location["Name"] == "home")
      {
         //   std::cout << "x pose is:\n" << item["Position_X"].asFloat() << std::endl;
         Position_X = location["Position_X"].asDouble();
         Position_Y = location["Position_Y"].asDouble();
         Yaw = location["Yaw"].asDouble();
      }
   }
}

void RobotInitialPose::set_initial_pose()
{

   quaternion.setRPY(0, 0, Yaw);
   initial_pose.header.frame_id = "map";
   initial_pose.pose.pose.position.x = Position_X; // Set x position
   initial_pose.pose.pose.position.y = Position_Y; // Set y position

   initial_pose.pose.pose.orientation.z = quaternion.z(); // Set z orientation
   initial_pose.pose.pose.orientation.w = quaternion.w(); // Set w orientation (quaternion)
   initial_pose_pub.publish(initial_pose);
}

int main(int argc, char **argv)
{

   ros::init(argc, argv, "send_initial_pose_node");
   ros::NodeHandle nh;

   RobotInitialPose robot_pose(nh);

   // Get the home directory
   const char *home_dir = getenv("HOME");
   if (home_dir == nullptr)
   {
      std::cerr << "Failed to get the home directory." << std::endl;
      return 1;
   }

   // Construct the absolute path to the JSON file
   std::string filename = std::string(home_dir) + "/arche_ws/src/Robots-DataBase/robot_task/robot_task_str.json";

   robot_pose.get_pose_from_json(filename);

   ros::Rate loop_rate(10);

   while (ros::ok())
   {
      // robot_pose.set_initial_pose();
      loop_rate.sleep();
      ros::spin();
   }

   return 0;
}