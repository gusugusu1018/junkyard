#!/usr/bin/env python
import rospy
import rosparam
from std_msgs.msg import String

def talker():
    rospy.init_node('talker')
    pub = rospy.Publisher('messagefromtalker', String, queue_size=10)
    r = rospy.Rate(1) # 10hz
    while not rospy.is_shutdown():
        str = "hello"
        rospy.loginfo(str)
        pub.publish(str)
        r.sleep()
if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException: pass
