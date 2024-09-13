# robot-rescue


Added  `cancel_goal_controller` ROS node handles goal cancellation for robot navigation.  listens for cancellation commands on the `/robot_rescue` topic and sends a stop command to the `/cmd_vel` topic to halt the robot. Additionally, it cancels the current navigation goal with the `move_base` action server.

## Features

* **Goal Cancellation** : Subscribes to the `/robot_rescue` topic for receiving cancellation commands.
* **Robot Stopping** : Publishes a stop command to the `/cmd_vel` topic to stop the robot's movement.
* **Action Server Interaction** : Sends a goal cancellation request to the `move_base` action server.

### Running the Node

```bash
rosrun robot_rescue cancel_goal_controller
```

### **Send a Cancellation Command**

Publish a message to the `/robot_rescue` topic to send a cancellation command:

```bash
rostopic pub /robot_rescue std_msgs/String "cancel_goal"
```
