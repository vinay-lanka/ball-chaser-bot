#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

using namespace std;

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // ROS_INFO_STREAM("Moving the bot towards the ball!");

    // Request centered joint angles [1.57, 1.57]
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    // Call the safe_move service and pass the requested joint angles
    if (!client.call(srv))
        ROS_ERROR("Failed to call service drive_bot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
    int reg1=0,reg2=0,reg3=0;
    for (int i = 0; i <img.height * img.step; i+=3) {
        if (img.data[i] == white_pixel && img.data[i+1] == white_pixel && img.data[i+2] == white_pixel) {
            int reg = i%img.step;
            if(reg<(img.step/3)){
                reg1++;
            }else if((reg>(img.step/3)) && (reg<(2 * img.step / 3))){
                reg2++;
            }else{
                reg3++;
            }
        }
    }
    if(reg1>reg2 && reg1>reg3){
            drive_robot(0.2,0.5);
    }else if(reg2>reg1 && reg2>reg3){
            drive_robot(0.2,0);
    }else if(reg3>reg2 && reg3>reg1){
            drive_robot(0.2,-0.5);
    }else{
       drive_robot(0,0);
   }
}   

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}