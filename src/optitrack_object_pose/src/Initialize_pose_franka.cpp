#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/Float64MultiArray.h"
#include "geometry_msgs/PoseStamped.h"
#include "optitrack_object_pose/StampedJointState.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "std_srvs/Empty.h"
#include <trac_ik/trac_ik.hpp>
#include <eigen3/Eigen/Dense>
#include "control_function_yang.h"

using namespace std;
using namespace Eigen;

void optitrackCallback(const geometry_msgs::PoseStamped::ConstPtr &msg);
void CounterCallback(const sensor_msgs::JointState::ConstPtr msg);
vector<double> next_object_pose(vector<double> object_pos, int step);

vector<double> mean = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
vector<double> sum = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
vector<double> posJointActual = {0, 0, 0, 0, 0, 0, 0};

bool initCheckOpti = false;
bool initCheck = false;

float x_offset = 0.2;

int step_count = 0;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Object_poses");
    // choose the tolerance and time for the inverse kinematic
    float err_ik = 0.001;
    float t_ik = 0.05;

    NextState nextState(err_ik, t_ik);

    sensor_msgs::JointState msgP;
    vector<double> jointToTarget(7);
    // Initialisation of the Ros Node (Service, Subscrber and Publisher)
    ros::NodeHandle Nh;
    // ros::Subscriber sub = Nh.subscribe("robot_state", 1000, CounterCallback);
    ros::Subscriber sub = Nh.subscribe("robot/joint_state", 1000, CounterCallback);
    ros::Publisher chatter_pub = Nh.advertise<sensor_msgs::JointState>("robot/joint_commands", 1000);
    ros::Subscriber sub_opt = Nh.subscribe("vrpn_client_node/box_multiple/pose", 1000, optitrackCallback);

    // Frequency of the Ros loop
    ros::Rate loop_rate(10);

    Nh.setParam("jointToTarget0", jointToTarget);
    Nh.setParam("jointToTarget1", jointToTarget);
    Nh.setParam("jointToTarget2", jointToTarget);
    Nh.setParam("jointToTarget3", jointToTarget);
    Nh.setParam("jointToTarget4", jointToTarget);

    cout << "Connection to Optitrack connection and Franka actual joint ..." << endl;

    // waiting for the first joint position
    int countInit = 0;
    while (!(initCheck && initCheckOpti))
    {
        countInit++;
        ros::spinOnce();
        loop_rate.sleep();

        if (countInit == 50)
        {
            cout << "Connection is not doing ok. stopping code..." << endl;
            ros::shutdown();
            exit(0);
        }
    }

    cout << "Connection is well done" << endl;

    while (ros::ok())
    {
        // give posision of the object to grasp
        for (int i = 0; i < 5; i++)
        {

            vector<double> posObj = next_object_pose(mean, i);
            vector<double> PosObjectGrasp = {posObj[4], posObj[5], posObj[6] + 0.07};

            // doing Inverse kinematic
            int rc = nextState.getIK(posJointActual, posObj);

            if (rc < 0)
            {
                cout << "Inverse kinematic not found, please move the objects" << endl;
            }

            // set params
            Nh.setParam("jointToTarget" + to_string(i), nextState.posJointNext);
            Nh.setParam("PosObjectGrasp" + to_string(i), PosObjectGrasp);
            // msgP.position = nextState.posJointNext;
            // chatter_pub.publish(msgP);
            // std::this_thread::sleep_for(std::chrono::seconds(5));
        }

        //-----------------------------------------

        ros::spinOnce();
        loop_rate.sleep();
    }
}

void optitrackCallback(const geometry_msgs::PoseStamped::ConstPtr &msg)
{

    // Process the received position and orientation data here.
    double x = msg->pose.position.x;
    double y = msg->pose.position.y;
    double z = msg->pose.position.z;
    double qx = msg->pose.orientation.x;
    double qy = msg->pose.orientation.y;
    double qz = msg->pose.orientation.z;
    double qw = msg->pose.orientation.w;

    if (x != 0 && y != 0 && z != 0 && initCheckOpti == false)
    {

        initCheckOpti = true;
    }
    // Accumulate the data.
    sum[0] += x;
    sum[1] += y;
    sum[2] += z;
    sum[3] += qx;
    sum[4] += qy;
    sum[5] += qz;
    sum[6] += qw;

    step_count++;
    // Check if 100 steps have been reached.
    if (step_count >= 100)
    {
        // Calculate and save the mean values
        mean.clear();
        // mean quat xyzw
        mean.push_back(sum[3] / 100);
        mean.push_back(sum[4] / 100);
        mean.push_back(sum[5] / 100);
        mean.push_back(sum[6] / 100);
        // meanpose xyz
        mean.push_back(sum[0] / 100 + x_offset);
        mean.push_back(sum[1] / 100);
        mean.push_back(sum[2] / 100 + 0.3);
        // Reset counters and sums for the next 100 steps.
        step_count = 0;
        sum.clear();

        sum.assign(7, 0);
    }
}

// void CounterCallback(const sensor_msgs::JointState::ConstPtr msg)
// {

//     posJointActual = msg->position;

//     if (initCheck == false)
//     {

//         initCheck = true;
//     }
// }

void CounterCallback(const optitrack_object_pose::StampedJointState::ConstPtr msg)
{
    sensor_msgs::JointState joint_state = msg->joint_state;
    posJointActual = joint_state.position;
    // posJointActual = msg->position;

    if (initCheck == false)
    {
        initCheck = true;
    }
}

vector<double> next_object_pose(vector<double> object_pos, int step)
{
    // Current position of the object in the global coordinate system
    Eigen::Vector3d current_position(object_pos[4], object_pos[5], object_pos[6]); // Replace with actual values

    // Quaternion representing the current orientation
    Eigen::Quaterniond current_quaternion(object_pos[3], object_pos[0], object_pos[1], object_pos[2]); // Replace with actual values

    // Desired rotation quaternion (90 degrees about the y-axis)
    Eigen::Quaterniond desired_rotation(std::cos(M_PI / 4), 0, std::sin(M_PI / 4), 0);

    // Combine the current and desired rotations
    Eigen::Quaterniond new_quaternion = current_quaternion * desired_rotation;

    // Vector representing the desired direction in the object's local coordinate system
    Eigen::Vector3d local_direction(0, 0.1 * step, 0); // Move 10 cm along the y-axis

    // Rotate the local direction into the global coordinate system
    Eigen::Vector3d global_direction = new_quaternion * local_direction;

    // Calculate the new position
    Eigen::Vector3d new_position = current_position + global_direction;
    vector<double> newQuatPosition = {object_pos[3], object_pos[0], object_pos[1], object_pos[2], new_position(0), new_position(1), new_position(3)};
    // std::cout << "first position: " << current_position.transpose() << std::endl;
    // std::cout << "second position: " << new_position.transpose() << std::endl;

    return newQuatPosition;
}
