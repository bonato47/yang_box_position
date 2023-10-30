#include <cmath>
#include <iostream>
#include <sstream>
#include <eigen3/Eigen/Dense>
#include "control_function_yang.h"
#include <vector>

#include "Utils.h"


using namespace std;
using namespace Eigen;






NextState::NextState(double err,double t) {  // Method/function defined inside the class
    baseLink  = "panda_link0";
    tipLink   = "panda_link8";
    nJoint    = 7;
    error=err;
    timeoutInSecs = t;
    init_general();
}    

void NextState::init_general(){
    vector<double> vector0_4(4, 0.0);
    quatFromDS = vector0_4;
    vector<double> vector0_3(3, 0.0);
    speedFromDS = vector0_3;
    vector<double> vector0_7(7, 0.0);
    posJointNext = vector0_7;
    std_msgs::Float64MultiArray msgP;


    ikSolver= new TRAC_IK::TRAC_IK(baseLink, tipLink, URDF_param, timeoutInSecs, error, type);  
    KDL::Chain chain;
    bool valid = ikSolver->getKDLChain(chain);
    if (!valid) {
        ROS_ERROR("There was no valid KDL chain found");
    } 
}

int NextState::getIK(vector<double> actualJoint, vector<double> vectorQuatPos ) {  
    
    int L = actualJoint.size();
    //Inverse kinematics trac-IK
    KDL::JntArray NextJointTask;
    KDL::JntArray actualJointTask(L); 

    for(size_t i = 0; i < L; ++i){
        actualJointTask.data(i) = actualJoint[i];
    }
    KDL::Vector Vec(vectorQuatPos[4],vectorQuatPos[5],vectorQuatPos[6]);

    Quaterniond q(vectorQuatPos[3],vectorQuatPos[0],vectorQuatPos[1],vectorQuatPos[2]);
    q.normalize();
    KDL::Rotation Rot = KDL::Rotation::Quaternion(q.x(),q.y(),q.z(),q.w());
    KDL::Frame NextJointCartesian(Rot,Vec); 

    int rc = ikSolver->CartToJnt(actualJointTask, NextJointCartesian, NextJointTask);
    if (rc< 0){
        ROS_INFO("no inverse kinematic found");    
    }

    VectorXd posJointNextEigen = NextJointTask.data;

    for(int i = 0 ;i<nJoint;++i){    
        posJointNext[i] =posJointNextEigen(i);
    }


    msgP.data = posJointNext;

    return 2;
    
} 

// void NextState::updateIK(double err){
//         ikSolver= new TRAC_IK::TRAC_IK(baseLink, tipLink, URDF_param, timeoutInSecs, err, type);  
// }

void NextState::poseCallback(const geometry_msgs::Pose::ConstPtr& msg) {
    // Process the received Pose message here
    // For example, you can access the position and orientation as follows:
    double x = msg->position.x;
    double y = msg->position.y;
    double z = msg->position.z;

    double qx = msg->orientation.x;
    double qy = msg->orientation.y;
    double qz = msg->orientation.z;
    double qw = msg->orientation.w;


    speedFromDS ={x,y,z};
    quatFromDS = {qx,qy,qz,qw};

    if(initCheck == false && qx != 0 && qy != 0 && qz != 0 && qw != 0){
        initCheck = true;
    }
}




// Function that Calculate Root Mean Square
bool mseValue_cart(vector<double> v1, vector<double> v2,float tol)
{
    // tolerance of the errot between each point
    bool Reached = false;
    int crit =0;
    float err =0;
    int Len = v1.size();

    for (int i = 0; i < Len; i++) {
        err = err + (v1[i]-v2[i])*(v1[i]-v2[i]);
    }
    err = sqrt(err);
    if(err < tol){
        Reached =true;
    }

    return Reached;
}

