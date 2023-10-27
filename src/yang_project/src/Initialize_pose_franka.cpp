#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/Float64MultiArray.h"
#include "geometry_msgs/PoseStamped.h"
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

void optitrackCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
void CounterCallback(const sensor_msgs::JointState::ConstPtr msg);


vector<double> mean = {0.0,0.0,0.0,0.0,0.0,0.0,0.0};
vector<double> sum = {0.0,0.0,0.0,0.0,0.0,0.0,0.0};
vector<double> posJointActual = {0,0,0,0,0,0,0};

bool initCheckOpti = false;
bool initCheck = false;

int step_count = 0;

int main(int argc, char **argv){
    ros::init(argc, argv, "Object_poses");

    //choose the tolerance and time for the inverse kinematic
    float err_ik =0.001;
    float t_ik = 0.05;

    NextState nextState(err_ik,t_ik);

    sensor_msgs::JointState msgP;

    //Initialisation of the Ros Node (Service, Subscrber and Publisher)
    ros::NodeHandle Nh;
    ros::Subscriber sub = Nh.subscribe("robot/joint_state", 1000, CounterCallback);
    ros::Publisher chatter_pub = Nh.advertise<sensor_msgs::JointState>("robot/joint_commands", 1000);
    ros::Subscriber sub_opt = Nh.subscribe("vrpn_client_node/box_multiple/pose", 1000, optitrackCallback);

    //Frequency of the Ros loop
    ros::Rate loop_rate(10);
    cout<< "setup .. " << endl;

    //waiting for the first joint position
    while(!(initCheck && initCheckOpti) ){
        ros::spinOnce();
    } 

    cout<< "setupready" << endl;


    while (ros::ok())
    {

        vector<double> traj_cart  = mean;

        int rc = nextState.getIK(posJointActual,traj_cart);
        cout <<"start"<< endl;

        for(int i =0; i<7 ; i++){
            cout << posJointActual[i] << endl;

        }
        // while (!mseValue_cart(posJointActual,nextState.posJointNext,0.01) ){
        //     chatter_pub.publish(nextState.msgP);
        //     ros::spinOnce();        
        //     loop_rate.sleep();  
        // }

        msgP.position= posJointActual;
        chatter_pub.publish(msgP);

        //-----------------
        //send the  new joint to param

        //-----------------------------------------
        // needto find a conditionif noik
        // if(rc < 0){
        //     ROS_INFO("this point is not achivable, please give another");
        // }

        ros::spinOnce();
        loop_rate.sleep();  

    }

}

void optitrackCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
        
    // Process the received position and orientation data here.
    double x = msg->pose.position.x;
    double y = msg->pose.position.y;
    double z = msg->pose.position.z;
    double qx = msg->pose.orientation.x;
    double qy = msg->pose.orientation.y;
    double qz = msg->pose.orientation.z;
    double qw = msg->pose.orientation.w;


    if(x != 0 && y != 0 && z != 0 && initCheckOpti == false ){
        
        initCheckOpti = true;
    }  
    // Accumulate the data.
    sum[0]  += x;
    sum[1]  += y;
    sum[2]  += z;
    sum[3]  += qx;
    sum[4]  += qy;
    sum[5]  += qz;
    sum[6]  += qw;


    step_count++;
    // Check if 100 steps have been reached.
    if (step_count >= 100)
    {
        // Calculate and save the mean values
        mean.clear();
        //mean quat xyzw
        mean.push_back(sum[3]/100);
        mean.push_back(sum[4]/100);
        mean.push_back(sum[5]/100);
        mean.push_back(sum[6]/100);
        //meanpose xyz
        mean.push_back(sum[0]/100);
        mean.push_back(sum[1]/100);
        mean.push_back(sum[2]/100 +0.5);
        // Reset counters and sums for the next 100 steps.
        step_count = 0;
        sum.clear();

        sum.assign(7,0);
    }
}





void CounterCallback(const sensor_msgs::JointState::ConstPtr msg)
{
    posJointActual = msg->position;
    
    if(initCheck == false){
        
        initCheck = true;
    }    
}













