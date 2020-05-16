# Ball Chasing Bot (ROS + GAZEBO)

**Introduction**<br>
A repository containing files required for the environment, robot and functionality of a ball chasing robot.

## Setup

**Requires ROS and Gazebo to be installed**
(A guide for installation can be found [here](http://wiki.ros.org/ROS/Installation))

This repository contains 2 packages for the ball chasing robot - 
- **my_robot** - Contains all the required files for the robot and the world in the gazebo environment.
- **ball_chaser** - Contains all the files for the image processing and bot driving functionality.

### Building
Copy both the files seperately in your src folder of your catkin env. <br>
After running `catkin_make`, source your setup files and you're good to go.

## Usage

To start the gazebo + rviz sim, launch a new terminal and run: <br>

`roslaunch my_robot world.launch`

In rviz -> Add 3 components in the Add menu = Robot Model, Laser Scan and the Camera.<br>
Initialise them with their respective topics.

Now open another terminal and run <br>
` roslaunch ball_chaser ball_chaser.launch`

Now in the main env keep the ball in front of the robot and watch the robot try to follow the ball.
