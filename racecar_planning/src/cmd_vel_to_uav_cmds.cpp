// Takes velocity commands from move_base planning node and sends them
// with rampage_commander lib

// ROS
#include <ros/ros.h>

// C++
// #include <memory>

// ROS standard messages
#include <geometry_msgs/Twist.h>

// Rampage control library
#include <rampage_estimator_and_controller/rampage_commander.h>
#include <rampage_estimator_and_controller/uav.h>
#include <rampage_msgs/UavCmds.h>
#include <limits>

uint16_t siToPwmVel(double vel) {
  return static_cast<uint16_t>(-3.7*vel*vel+36.5*vel+1515.7);
}

uint16_t siToPwmAng(double ang) {
  double a1 = 428.45550781647;
  double a2 = 0.06147539671;
  double a3 = -0.01950110391;
  double a4 = 1505.65754996255;
  return static_cast<uint16_t>(a1 / (1+exp((a3-ang)/a2))-0.5*a1+a4);
}

class CallBackRampagePlanning {

  public:

   CallBackRampagePlanning();
    ~CallBackRampagePlanning();

   void cbCmdVel(const geometry_msgs::Twist::ConstPtr& vel);

  private:

    ros::NodeHandle nh_, nh_p_;
    ros::Subscriber sub_vel_cmds_;
    ros::Publisher pub_uav_cmds_;

    RampageCommander *p_commander_;

};

CallBackRampagePlanning::CallBackRampagePlanning() :
    nh_p_("~") {

  sub_vel_cmds_ = nh_p_.subscribe("/cmd_vel", 1, &CallBackRampagePlanning::cbCmdVel, this);
  pub_uav_cmds_ = nh_p_.advertise<rampage_msgs::UavCmds>("/uav_cmds", 0);
  p_commander_ = new RampageCommander(pub_uav_cmds_, siToPwmAng, siToPwmVel);
  ROS_INFO("Subcribers and publishers initialized.");
  ros::Rate loop_rate(10);
  ros::Time prev_time = ros::Time::now();
  while (ros::Time::now().toSec() - prev_time.toSec() < 3.0) {
    p_commander_->enableMotors();
    loop_rate.sleep();
  }
  ROS_INFO("Motors Enabled");

}

CallBackRampagePlanning::~CallBackRampagePlanning() {
  p_commander_->disableMotors();
  delete p_commander_;
}

void CallBackRampagePlanning::cbCmdVel(const geometry_msgs::Twist::ConstPtr& vel) {

  double si_ang = vel->angular.z; // in-plane rotation
  double si_vel = vel->linear.x; // velocity in x direction is speed in cmd_vel
  if (si_vel < 1.0 && si_vel > 0) {
     si_vel = 1.25252525252525252525252525252525252525252525252525;//Final Outdoor:1.5 Final Indoor: 1.25
  }
  else if (si_vel > -1.5 && si_vel < 0) {
    si_vel = -1.5; //Final Outdoor: -1.5, Final Indoor: -1.5
  }

  if (si_vel < 0) {
     si_vel *= 2; //
  }
  ROS_INFO("si_vel: %f",  si_vel);
  p_commander_->sendCmdMotorsSI(si_ang, si_vel);

}

int main(int argc, char** argv) {

  ros::init(argc, argv, "cmd_vel_to_uav_cmds");
  ros::NodeHandle nh;

  CallBackRampagePlanning cbc;
  ros::spin();

  return 0;
}
