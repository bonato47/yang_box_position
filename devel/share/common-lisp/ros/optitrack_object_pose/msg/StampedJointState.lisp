; Auto-generated. Do not edit!


(cl:in-package optitrack_object_pose-msg)


;//! \htmlinclude StampedJointState.msg.html

(cl:defclass <StampedJointState> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (joint_state
    :reader joint_state
    :initarg :joint_state
    :type sensor_msgs-msg:JointState
    :initform (cl:make-instance 'sensor_msgs-msg:JointState))
   (isTracking
    :reader isTracking
    :initarg :isTracking
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass StampedJointState (<StampedJointState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StampedJointState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StampedJointState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name optitrack_object_pose-msg:<StampedJointState> is deprecated: use optitrack_object_pose-msg:StampedJointState instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <StampedJointState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader optitrack_object_pose-msg:header-val is deprecated.  Use optitrack_object_pose-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'joint_state-val :lambda-list '(m))
(cl:defmethod joint_state-val ((m <StampedJointState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader optitrack_object_pose-msg:joint_state-val is deprecated.  Use optitrack_object_pose-msg:joint_state instead.")
  (joint_state m))

(cl:ensure-generic-function 'isTracking-val :lambda-list '(m))
(cl:defmethod isTracking-val ((m <StampedJointState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader optitrack_object_pose-msg:isTracking-val is deprecated.  Use optitrack_object_pose-msg:isTracking instead.")
  (isTracking m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StampedJointState>) ostream)
  "Serializes a message object of type '<StampedJointState>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'joint_state) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'isTracking) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <StampedJointState>) istream)
  "Deserializes a message object of type '<StampedJointState>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'joint_state) istream)
    (cl:setf (cl:slot-value msg 'isTracking) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StampedJointState>)))
  "Returns string type for a message object of type '<StampedJointState>"
  "optitrack_object_pose/StampedJointState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StampedJointState)))
  "Returns string type for a message object of type 'StampedJointState"
  "optitrack_object_pose/StampedJointState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StampedJointState>)))
  "Returns md5sum for a message object of type '<StampedJointState>"
  "527fc01812df485c424aa8c714601eb6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StampedJointState)))
  "Returns md5sum for a message object of type 'StampedJointState"
  "527fc01812df485c424aa8c714601eb6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StampedJointState>)))
  "Returns full string definition for message of type '<StampedJointState>"
  (cl:format cl:nil "Header header~%sensor_msgs/JointState joint_state~%bool isTracking~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: sensor_msgs/JointState~%# This is a message that holds data to describe the state of a set of torque controlled joints. ~%#~%# The state of each joint (revolute or prismatic) is defined by:~%#  * the position of the joint (rad or m),~%#  * the velocity of the joint (rad/s or m/s) and ~%#  * the effort that is applied in the joint (Nm or N).~%#~%# Each joint is uniquely identified by its name~%# The header specifies the time at which the joint states were recorded. All the joint states~%# in one message have to be recorded at the same time.~%#~%# This message consists of a multiple arrays, one for each part of the joint state. ~%# The goal is to make each of the fields optional. When e.g. your joints have no~%# effort associated with them, you can leave the effort array empty. ~%#~%# All arrays in this message should have the same size, or be empty.~%# This is the only way to uniquely associate the joint name with the correct~%# states.~%~%~%Header header~%~%string[] name~%float64[] position~%float64[] velocity~%float64[] effort~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StampedJointState)))
  "Returns full string definition for message of type 'StampedJointState"
  (cl:format cl:nil "Header header~%sensor_msgs/JointState joint_state~%bool isTracking~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: sensor_msgs/JointState~%# This is a message that holds data to describe the state of a set of torque controlled joints. ~%#~%# The state of each joint (revolute or prismatic) is defined by:~%#  * the position of the joint (rad or m),~%#  * the velocity of the joint (rad/s or m/s) and ~%#  * the effort that is applied in the joint (Nm or N).~%#~%# Each joint is uniquely identified by its name~%# The header specifies the time at which the joint states were recorded. All the joint states~%# in one message have to be recorded at the same time.~%#~%# This message consists of a multiple arrays, one for each part of the joint state. ~%# The goal is to make each of the fields optional. When e.g. your joints have no~%# effort associated with them, you can leave the effort array empty. ~%#~%# All arrays in this message should have the same size, or be empty.~%# This is the only way to uniquely associate the joint name with the correct~%# states.~%~%~%Header header~%~%string[] name~%float64[] position~%float64[] velocity~%float64[] effort~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StampedJointState>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'joint_state))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StampedJointState>))
  "Converts a ROS message object to a list"
  (cl:list 'StampedJointState
    (cl:cons ':header (header msg))
    (cl:cons ':joint_state (joint_state msg))
    (cl:cons ':isTracking (isTracking msg))
))
