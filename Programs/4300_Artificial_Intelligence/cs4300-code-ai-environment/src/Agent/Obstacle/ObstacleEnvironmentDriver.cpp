#include <ai_obstacle.h>
#include <fstream>

namespace ai
{
  namespace Agent
  {
    static struct Option options[] = 
      {
	{"distance",   'm', "10",            "Maximum travel distance per step"},
	{"filename",   'f', "obstacles.txt", "World filename"},
	{"height",     'h', "1000",          "World height"},
	{"observable", 'O', "1",             "Enable/disable fully-observable mode"},
	{"width",      'w', "1000",          "World width"},
	{"", 0, "", ""}
      };
    
    ObstacleEnvironmentDriver::ObstacleEnvironmentDriver(int argc, char **argv, bool init_options) : EnvironmentDriver(argc, argv, false)
    {
      mOptions.AddOptions(options);
      if(init_options)
	{
	  mOptions.Initialize(argc, argv);
	  InitRand();
	}
    }
    
    bool ReadFile(ObstacleEnvironment *env, std::string filename, ObstacleAgent *agent)
    {
      std::ifstream fin(filename.c_str());
      double max_x = 0.0, max_y = 0.0;
      double x_in;
      double y_in;
      int    triangle_count;
      int    node_count;
      ObstacleLocation *location;
      ObstacleObject   *object;
      
      if(!fin)
	{
	  return false;
	}
      
      // start coordinates
      fin >> x_in >> y_in;
      if(x_in > max_x) { max_x = x_in; } if(y_in > max_y) { max_y = y_in; }
      location = new ObstacleLocation;
      location->Set(x_in, y_in);
      env->AddAgent(agent, location);
      
      // goal coordinates
      fin >> x_in >> y_in;
      if(x_in > max_x) { max_x = x_in; } if(y_in > max_y) { max_y = y_in; }
      location = new ObstacleLocation;
      location->Set(x_in, y_in);
      object   = new ObstacleObject(-1, -1, location);
      object->SetName("GOAL");
      env->AddObject(object, location);
      
      triangle_count = 0;
      node_count     = 0;
      while(fin)
	{
	  fin >> x_in >> y_in;
	  if(fin)
	    {
	      if(x_in > max_x) { max_x = x_in; } if(y_in > max_y) { max_y = y_in; }
	      location  = new ObstacleLocation;
	      location->Set(x_in, y_in);
	      object    = new ObstacleObject(triangle_count, node_count, location);
	      object->SetName("BEACON");
	      env->AddObject(object, location);
	      node_count ++;
	      if(node_count > 2)
		{
		  node_count = 0;
		  triangle_count ++;
		}
	    }
	}
      fin.close();
      if(node_count != 0)
	{
	  std::cerr << "BAD DATA FILE!" << std::endl;
	}
      if(env->GetWidth() < max_x)
	{
	  env->SetWidth(max_x);
	}
      if(env->GetHeight() < max_y)
	{
	  env->SetHeight(max_y);
	}
      return true;
    }
    
    void ObstacleEnvironmentDriver::Run()
    {
      std::string filename = mOptions.GetArg("filename");
      {
	std::ifstream fin(filename.c_str());
	if(!fin)
	  {
	    std::cerr << "Unable to open Obstacle world file: " << filename << std::endl;
	    exit(1);
	  }
	fin.close();
      }

      InitSockets(1, mOptions.GetArgInt("displays"));
      
      int runs = mOptions.GetArgInt("runs");
      for(int r = 0; r < runs; r++)
	{
	  ObstacleEnvironment *env = new ObstacleEnvironment(mRandomNumber,
							     mOptions.GetArgFlt("width"),
							     mOptions.GetArgFlt("height"),
							     &mDisplaySockets);
	  
	  ObstacleAgent *agent = new ObstacleAgent(mAgentSockets[0]);
	  if(mOptions.GetArgInt("trace"))
	    {
	      agent->Trace();
	    }
	  else
	    {
	      agent->NoTrace();
	    }
	  
	  env->SetMaxStepDistance(mOptions.GetArgFlt("distance"));
	  env->SetFullyObservable(mOptions.GetArgInt("observable"));

	  ReadFile(env, filename, agent);

	  env->SetDelay(mOptions.GetArgInt("delay"));
	  env->Run(mOptions.GetArgInt("steps"));
	  
	  std::cout << "Total Path Length: " << agent->GetPathCost()
		    << " Found Goal: "       << agent->GetFoundGoal()
		    << std::endl;
	  
	  mRandomNumber = env->GetRandomNumber();
	  sleep(mOptions.GetArgInt("sleep"));
	  delete env;
	}
    }
  }
}
