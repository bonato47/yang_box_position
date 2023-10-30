# ifndef CONTROL_FUNC
# define CONTROL_FUNC

#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/Float64MultiArray.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"
#include <trac_ik/trac_ik.hpp>
#include <eigen3/Eigen/Dense>



using namespace std;
using namespace Eigen;



class NextState {       // The class
    public:             // Access specifier
        //iniailization Invers Kinematics
        string baseLink;
        string tipLink;
        string URDF_param="/robot_description";
        TRAC_IK::SolveType type =TRAC_IK::Distance;
        double error; 
        double timeoutInSecs;
        int nJoint{};

        std_msgs::Float64MultiArray msgP;
        vector<double> posJointNext;
        vector<double> speedFromDS;
        vector<double> quatFromDS;

        bool initCheck= false;
        TRAC_IK::TRAC_IK* ikSolver = nullptr;  

    NextState(double err = 0.001,double t = 0.05);
    
    void init_general();
    int getIK(vector<double> actualJoint, vector<double> vectorQuatPos ) ;

     void updateIK(double err);

    void poseCallback(const geometry_msgs::Pose::ConstPtr& msg) ;

};


// Function that Calculate Root Mean Square
bool mseValue_cart(vector<double> v1, vector<double> v2, float tol);


#endif
