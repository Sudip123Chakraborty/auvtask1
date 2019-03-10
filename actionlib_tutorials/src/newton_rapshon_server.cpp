    #include <ros/ros.h>
    #include <actionlib/server/simple_action_server.h>
    #include <actionlib_tutorials/Newton_rapshonAction.h>
   
    int i=1,count=0;
//using namespace std;
    class Newton_rapshonAction
    {
    protected:
    
      ros::NodeHandle nh_;
     actionlib::SimpleActionServer<actionlib_tutorials::Newton_rapshonAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
     std::string action_name_;
     // create messages that are used to published feedback/result
     actionlib_tutorials::Newton_rapshonFeedback feedback;
     actionlib_tutorials::Newton_rapshonResult result_;
     float x=1,y1,y2;
   
   public:
   

  
	
     Newton_rapshonAction(std::string name) :
       as_(nh_, name, boost::bind(&Newton_rapshonAction::executeCB, this, _1), false),
      action_name_(name)
     {
      as_.start();
	     }
	   
	     ~Newton_rapshonAction(void)
	     {
     }
   
	

	     void executeCB(const actionlib_tutorials::Newton_rapshonGoalConstPtr &goal)
	     {
	       // helper variables
	      ros::Rate r(1);
	       bool success = true;
	   
	       
	{
		
		 
		 if (as_.isPreemptRequested() || !ros::ok())
		 {
			   ROS_INFO("%s: Preempted", action_name_.c_str());
			  // set the action state to preempted
			  as_.setPreempted();
			   success = false;
		   
		 }
	x=goal->order;

	y1=x;
	x=((2*x*x*x-13)/(3*x*x-5));
	y2=x;
		
	feedback.sequence=x;
	as_.publishFeedback(feedback);
	
		 
	ROS_INFO("%d th value: %f",i,x );
	std::cout<<std::endl;
	result_.rank=0;

	if(y2>y1)
		{
			float temp;
			temp=y2;
			y2=y1;
			y1=temp;
		}
	
			i++;
	if(y1-y2<0.000001)
		{
			std::cout<<"result: "<<x<<std::endl;
			count=1;
			//break;
			result_.rank=1;
			result_.sequence = feedback.sequence;
         		ROS_INFO("%s: Succeeded", action_name_.c_str());
         		// set the action state to succeeded
       			as_.setSucceeded(result_);
		}

		r.sleep();
	   }
   
	
      
     }
   
   
   };
   
   
   int main(int argc, char** argv)
   {

   	
   	{
   	
	     ros::init(argc, argv, "newton_rapshon");
	   
	     Newton_rapshonAction newton_rapshon("newton_rapshon");
	     
     	      ros::spin();
   	}
     return 0;
   }
