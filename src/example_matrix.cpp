#include <ros/ros.h>
#include <iostream>
#include "position_2d_correction/eigen_functions.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "position_2d_correction_node");
  ros::NodeHandle n;

  // Create an array of size 3 to hold Vector2d objects
  Eigen::Vector2d points[3];

  // Assign values to each element
  points[0] << 1, 2;
  points[1] << 3, 4;
  points[2] << 5, 6;

  Eigen::MatrixXd m(2, 2);
  m(0, 0) = 3;
  m(1, 0) = 2.5;
  m(0, 1) = -2;
  m(1, 1) = m(1, 0) + m(0, 1);

  // ros::init(argc, argv, "talker");
  // ros::NodeHandle n;
  // ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
  ros::Rate loop_rate(10);
  int count = 0;
  while (ros::ok())
  {
    // std_msgs::String msg;

    // std::stringstream ss;
    // ss << "hello world " << count;
    // msg.data = ss.str();

    // ROS_INFO("%s", msg.data.c_str());

    // /**
    //  * The publish() function is how you send messages. The parameter
    //  * is the message object. The type of this object must agree with the type
    //  * given as a template parameter to the advertise<>() call, as was done
    //  * in the constructor above.
    //  */
    // chatter_pub.publish(msg);

    // Access and print elements
    for (int i = 0; i < 3; ++i)
    {
      std::cout << "Point " << i << ": " << points[i].transpose() << std::endl;
    }

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

  return 0;
}
