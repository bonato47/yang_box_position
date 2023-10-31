// Generated by gencpp from file optitrack_object_pose/StampedJointState.msg
// DO NOT EDIT!


#ifndef OPTITRACK_OBJECT_POSE_MESSAGE_STAMPEDJOINTSTATE_H
#define OPTITRACK_OBJECT_POSE_MESSAGE_STAMPEDJOINTSTATE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <sensor_msgs/JointState.h>

namespace optitrack_object_pose
{
template <class ContainerAllocator>
struct StampedJointState_
{
  typedef StampedJointState_<ContainerAllocator> Type;

  StampedJointState_()
    : header()
    , joint_state()
    , isTracking(false)  {
    }
  StampedJointState_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , joint_state(_alloc)
    , isTracking(false)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef  ::sensor_msgs::JointState_<ContainerAllocator>  _joint_state_type;
  _joint_state_type joint_state;

   typedef uint8_t _isTracking_type;
  _isTracking_type isTracking;





  typedef boost::shared_ptr< ::optitrack_object_pose::StampedJointState_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::optitrack_object_pose::StampedJointState_<ContainerAllocator> const> ConstPtr;

}; // struct StampedJointState_

typedef ::optitrack_object_pose::StampedJointState_<std::allocator<void> > StampedJointState;

typedef boost::shared_ptr< ::optitrack_object_pose::StampedJointState > StampedJointStatePtr;
typedef boost::shared_ptr< ::optitrack_object_pose::StampedJointState const> StampedJointStateConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::optitrack_object_pose::StampedJointState_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::optitrack_object_pose::StampedJointState_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::optitrack_object_pose::StampedJointState_<ContainerAllocator1> & lhs, const ::optitrack_object_pose::StampedJointState_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.joint_state == rhs.joint_state &&
    lhs.isTracking == rhs.isTracking;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::optitrack_object_pose::StampedJointState_<ContainerAllocator1> & lhs, const ::optitrack_object_pose::StampedJointState_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace optitrack_object_pose

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::optitrack_object_pose::StampedJointState_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::optitrack_object_pose::StampedJointState_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::optitrack_object_pose::StampedJointState_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::optitrack_object_pose::StampedJointState_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::optitrack_object_pose::StampedJointState_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::optitrack_object_pose::StampedJointState_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::optitrack_object_pose::StampedJointState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "527fc01812df485c424aa8c714601eb6";
  }

  static const char* value(const ::optitrack_object_pose::StampedJointState_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x527fc01812df485cULL;
  static const uint64_t static_value2 = 0x424aa8c714601eb6ULL;
};

template<class ContainerAllocator>
struct DataType< ::optitrack_object_pose::StampedJointState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "optitrack_object_pose/StampedJointState";
  }

  static const char* value(const ::optitrack_object_pose::StampedJointState_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::optitrack_object_pose::StampedJointState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n"
"sensor_msgs/JointState joint_state\n"
"bool isTracking\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
"\n"
"================================================================================\n"
"MSG: sensor_msgs/JointState\n"
"# This is a message that holds data to describe the state of a set of torque controlled joints. \n"
"#\n"
"# The state of each joint (revolute or prismatic) is defined by:\n"
"#  * the position of the joint (rad or m),\n"
"#  * the velocity of the joint (rad/s or m/s) and \n"
"#  * the effort that is applied in the joint (Nm or N).\n"
"#\n"
"# Each joint is uniquely identified by its name\n"
"# The header specifies the time at which the joint states were recorded. All the joint states\n"
"# in one message have to be recorded at the same time.\n"
"#\n"
"# This message consists of a multiple arrays, one for each part of the joint state. \n"
"# The goal is to make each of the fields optional. When e.g. your joints have no\n"
"# effort associated with them, you can leave the effort array empty. \n"
"#\n"
"# All arrays in this message should have the same size, or be empty.\n"
"# This is the only way to uniquely associate the joint name with the correct\n"
"# states.\n"
"\n"
"\n"
"Header header\n"
"\n"
"string[] name\n"
"float64[] position\n"
"float64[] velocity\n"
"float64[] effort\n"
;
  }

  static const char* value(const ::optitrack_object_pose::StampedJointState_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::optitrack_object_pose::StampedJointState_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.joint_state);
      stream.next(m.isTracking);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct StampedJointState_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::optitrack_object_pose::StampedJointState_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::optitrack_object_pose::StampedJointState_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "joint_state: ";
    s << std::endl;
    Printer< ::sensor_msgs::JointState_<ContainerAllocator> >::stream(s, indent + "  ", v.joint_state);
    s << indent << "isTracking: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.isTracking);
  }
};

} // namespace message_operations
} // namespace ros

#endif // OPTITRACK_OBJECT_POSE_MESSAGE_STAMPEDJOINTSTATE_H
