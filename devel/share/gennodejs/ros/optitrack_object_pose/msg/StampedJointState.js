// Auto-generated. Do not edit!

// (in-package optitrack_object_pose.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');
let sensor_msgs = _finder('sensor_msgs');

//-----------------------------------------------------------

class StampedJointState {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.joint_state = null;
      this.isTracking = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('joint_state')) {
        this.joint_state = initObj.joint_state
      }
      else {
        this.joint_state = new sensor_msgs.msg.JointState();
      }
      if (initObj.hasOwnProperty('isTracking')) {
        this.isTracking = initObj.isTracking
      }
      else {
        this.isTracking = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type StampedJointState
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [joint_state]
    bufferOffset = sensor_msgs.msg.JointState.serialize(obj.joint_state, buffer, bufferOffset);
    // Serialize message field [isTracking]
    bufferOffset = _serializer.bool(obj.isTracking, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type StampedJointState
    let len;
    let data = new StampedJointState(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [joint_state]
    data.joint_state = sensor_msgs.msg.JointState.deserialize(buffer, bufferOffset);
    // Deserialize message field [isTracking]
    data.isTracking = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += sensor_msgs.msg.JointState.getMessageSize(object.joint_state);
    return length + 1;
  }

  static datatype() {
    // Returns string type for a message object
    return 'optitrack_object_pose/StampedJointState';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '527fc01812df485c424aa8c714601eb6';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new StampedJointState(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.joint_state !== undefined) {
      resolved.joint_state = sensor_msgs.msg.JointState.Resolve(msg.joint_state)
    }
    else {
      resolved.joint_state = new sensor_msgs.msg.JointState()
    }

    if (msg.isTracking !== undefined) {
      resolved.isTracking = msg.isTracking;
    }
    else {
      resolved.isTracking = false
    }

    return resolved;
    }
};

module.exports = StampedJointState;
