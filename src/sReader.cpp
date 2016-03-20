#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>


geometry_msgs::Twist tws;
ros::Publisher twistPub;

void sonarCallback(const std_msgs::Float32ConstPtr &son){
    ROS_INFO("sonar received");
    
    if(son->data != 0){
        tws.linear.x = son->data-0.5;
		tws.angular.z = 0.3;
    }
    else{
        tws.linear.x = 0.5;
		tws.angular.z = 0;
    }
    
    twistPub.publish(tws);
}

int main(int argc, char **argv){
    ros::init(argc, argv, "simpleReader");
    
    ros::NodeHandle node;
    
    ros::Subscriber sonarSub = node.subscribe("/vrep/vehicle/frontSonar",1,sonarCallback);
    
	twistPub = node.advertise<geometry_msgs::Twist>("/vehicle/Twist",1);
    
    ros::spin();
}
