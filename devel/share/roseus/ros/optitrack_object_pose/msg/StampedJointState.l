;; Auto-generated. Do not edit!


(when (boundp 'optitrack_object_pose::StampedJointState)
  (if (not (find-package "OPTITRACK_OBJECT_POSE"))
    (make-package "OPTITRACK_OBJECT_POSE"))
  (shadow 'StampedJointState (find-package "OPTITRACK_OBJECT_POSE")))
(unless (find-package "OPTITRACK_OBJECT_POSE::STAMPEDJOINTSTATE")
  (make-package "OPTITRACK_OBJECT_POSE::STAMPEDJOINTSTATE"))

(in-package "ROS")
;;//! \htmlinclude StampedJointState.msg.html
(if (not (find-package "SENSOR_MSGS"))
  (ros::roseus-add-msgs "sensor_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass optitrack_object_pose::StampedJointState
  :super ros::object
  :slots (_header _joint_state _isTracking ))

(defmethod optitrack_object_pose::StampedJointState
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:joint_state __joint_state) (instance sensor_msgs::JointState :init))
    ((:isTracking __isTracking) nil)
    )
   (send-super :init)
   (setq _header __header)
   (setq _joint_state __joint_state)
   (setq _isTracking __isTracking)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:joint_state
   (&rest __joint_state)
   (if (keywordp (car __joint_state))
       (send* _joint_state __joint_state)
     (progn
       (if __joint_state (setq _joint_state (car __joint_state)))
       _joint_state)))
  (:isTracking
   (&optional (__isTracking :null))
   (if (not (eq __isTracking :null)) (setq _isTracking __isTracking)) _isTracking)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; sensor_msgs/JointState _joint_state
    (send _joint_state :serialization-length)
    ;; bool _isTracking
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; sensor_msgs/JointState _joint_state
       (send _joint_state :serialize s)
     ;; bool _isTracking
       (if _isTracking (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; sensor_msgs/JointState _joint_state
     (send _joint_state :deserialize buf ptr-) (incf ptr- (send _joint_state :serialization-length))
   ;; bool _isTracking
     (setq _isTracking (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get optitrack_object_pose::StampedJointState :md5sum-) "527fc01812df485c424aa8c714601eb6")
(setf (get optitrack_object_pose::StampedJointState :datatype-) "optitrack_object_pose/StampedJointState")
(setf (get optitrack_object_pose::StampedJointState :definition-)
      "Header header
sensor_msgs/JointState joint_state
bool isTracking
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: sensor_msgs/JointState
# This is a message that holds data to describe the state of a set of torque controlled joints. 
#
# The state of each joint (revolute or prismatic) is defined by:
#  * the position of the joint (rad or m),
#  * the velocity of the joint (rad/s or m/s) and 
#  * the effort that is applied in the joint (Nm or N).
#
# Each joint is uniquely identified by its name
# The header specifies the time at which the joint states were recorded. All the joint states
# in one message have to be recorded at the same time.
#
# This message consists of a multiple arrays, one for each part of the joint state. 
# The goal is to make each of the fields optional. When e.g. your joints have no
# effort associated with them, you can leave the effort array empty. 
#
# All arrays in this message should have the same size, or be empty.
# This is the only way to uniquely associate the joint name with the correct
# states.


Header header

string[] name
float64[] position
float64[] velocity
float64[] effort

")



(provide :optitrack_object_pose/StampedJointState "527fc01812df485c424aa8c714601eb6")


