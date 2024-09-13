#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <fstream>
#include <iostream>
#include <string>

double Position_X;
double Position_Y;
double Yaw;
tf2::Quaternion quaternion;

int main()
{

   // Get the home directory
   const char *home_dir = getenv("HOME");
   if (home_dir == nullptr)
   {
      std::cerr << "Failed to get the home directory." << std::endl;
      return 1;
   }

   // Construct the absolute path to the JSON file
   std::string filename = std::string(home_dir) + "/arche_ws/src/Robots-DataBase/robot_task/robot_task_str.json";

   // Using fstream to get the file pointer in file
   std::ifstream file(filename);
   
   Json::Value JsonFile;
   Json::Reader reader;

   // Using the reader, we are parsing the json file
   reader.parse(file, JsonFile);

   //create new vlaue object to acess "locations" array of object
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

   quaternion.setRPY(0, 0, Yaw);

   quaternion.x();
   quaternion.y();
   quaternion.z();
   quaternion.w();
   std::cout << "x pose is:\n"
             << Position_X << "\n y pose is:\n"
             << Position_Y << "\n yaw pose is:\n"
             << Yaw << std::endl;

   return 0;
}