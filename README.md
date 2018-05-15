# ROS_planar_hand
A simple planar hand made in ROS
There are two main folders: visualisation of the robot in Gazebo and Rviz and the packages for moving the real robot
roslaunch gazebo_robot gazebo.launch  ------ to launch gazebo with all controllers
to move the motors: firstly
roslaunch my_dynamixel_tutorial controller_manager.launch 
then
roslaunch my_dynamixel_tutorial start_tilt_controller.launch
then it can be controlled through topics, for example: rostopic pub /tilt_controller/command std_msgs/Float64 "data 0.7"
or can be controlled by joystick/accelerometr(arduino):
rosrun move rotate


