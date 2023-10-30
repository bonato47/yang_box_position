
(cl:in-package :asdf)

(defsystem "optitrack_object_pose-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :sensor_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "StampedJointState" :depends-on ("_package_StampedJointState"))
    (:file "_package_StampedJointState" :depends-on ("_package"))
  ))