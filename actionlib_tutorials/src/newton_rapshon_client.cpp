#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <actionlib_tutorials/Newton_rapshonAction.h>




int main (int argc, char **argv)
{
input:
{
	  ros::init(argc, argv, "test_newton_rapshon");

	  // create the action client
	  // true causes the client to spin its own thread
	  actionlib::SimpleActionClient<actionlib_tutorials::Newton_rapshonAction> ac("newton_rapshon", true);
	  
	  ROS_INFO("Waiting for action server to start.");
	  // wait for the action server to start
	  ac.waitForServer(); //will wait for infinite time

	  ROS_INFO("Action server started, sending goal.");
	  // send a goal to the action
	  actionlib_tutorials::Newton_rapshonGoal goal;
	  //goal.order = 40;
	std::cout<<"please enter the goal"<<std::endl;

	std::cin>>goal.order;
	  ac.sendGoal(goal);
	std::cout<<"sudip"<<goal.order<<std::endl;

	  //wait for the action to return
	  bool finished_before_timeout = ac.waitForResult(ros::Duration());
	  if (finished_before_timeout)
	  {
	    actionlib::SimpleClientGoalState state = ac.getState();
	    ROS_INFO("Action finished: %s",state.toString().c_str());
	  }
	  else
	    ROS_INFO("Action did not finish before the time out.");
}
	goto input;
	//ros::spin();
  //exit
  return 0;
}
