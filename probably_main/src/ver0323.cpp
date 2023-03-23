#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Point32.h"
#include "turtlesim/Pose.h"
#include "cmath"
#include "iostream"

void Callback(const turtlesim::Pose::ConstPtr& the_pose)
{
    x = the_pose->x;
    y = the_pose->y;
    theta = the_pose->theta;
    if(theta < 0)   theta += 2*PI;
    std::cout<<"!!!\t";
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "ver0323");
    ros::NodeHandle nh;
    ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    ros::Subscriber pose_sub = nh.subscribe("/cmd_vel",10,Callback);
    
    while(ros::ok()){
        // nh.getParam("/speed",speed_Kp);
        // nh.getParam("/des_x",des_x);
        // nh.getParam("/des_y",des_y);
        if(des_x_last != des_x || des_y_last != des_y){
            while(ros::ok()){
                ros::spinOnce();
                vel_pub.publish();
                std::cout<<"\tdes_x: "<<des_x<<"\tdes_y: "<<des_y;
                std::cout<<"\tspeed_Kp: "<<speed_Kp<<"\n";
            }
            x_sign = 1, y_sign = 1;
            if_reach = false;
        }
        des_x_last = des_x;
        des_y_last = des_y;
    }
    return 0;
}