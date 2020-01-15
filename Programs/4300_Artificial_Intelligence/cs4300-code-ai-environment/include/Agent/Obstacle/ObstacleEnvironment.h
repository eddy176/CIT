#ifndef _OBSTACLEENVIRONMENT_H_
#define _OBSTACLEENVIRONMENT_H_

namespace ai
{
  namespace Agent
  {
    class ObstacleWorld
    {
    public:
      ObstacleWorld();
      ~ObstacleWorld();
      bool AddNode(int triangle_index, int node_index,
		   double x_in, double y_in);
      bool SetGoal(double x_in, double y_in);
      int  GetNumTriangle() const;
      bool GetGoal(double &x_out, double &y_out) const;
      bool GetNode(int triangle_index, int node_index,
		   double &x_out, double &y_out) const;
      bool IntersectsWithObstacle(double x1, double y1,
				  double x2, double y2);
      double GetMinDist() const;
    protected:
      struct Triangle
      {
      public:
	Triangle()
	{
	  int i;
	  for(i = 0; i < 3; i++)
	    {
	      x[i] = 0.0;
	      y[i] = 0.0;
	    }
	}
	double x[3];
	double y[3];
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
	  ar & x;
	  ar & y;
	}
      };
      std::vector<Triangle> triangles;
      double    goal_x;
      double    goal_y;
      double    min_dist;
    private:
      friend class boost::serialization::access;
      template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
	  ar & triangles;
	  ar & goal_x;
	  ar & goal_y;
	  ar & min_dist;
	}
    };
    
    class ObstacleEnvironment : public Environment
    {
      friend class ObstacleEnvironmentDisplay;
    public:
      ObstacleEnvironment();
      ObstacleEnvironment(const RandomNumber &rand_in, 
			  double width_in,
			  double height_in,
			  std::vector<Socket *> *displays_in);
      virtual ~ObstacleEnvironment();
      void DoGo(ObstacleAgent  *obs_agent, ObstacleAction *obs_action);
      virtual bool ApplyAction(Agent *agent, Action *action);
      virtual void CalculatePerformance(Agent *agent);
      virtual Percept *GetPercept(Agent *agent);
      virtual void AddObject(Object *object, Location *location);
      virtual Location *DefaultLocation() const;
      void SetWidth(double width_in);
      void SetHeight(double height_in);
      double GetWidth() const;
      double GetHeight() const;
      bool   GetFullyObservable() const;
      void   SetFullyObservable(bool fully_observable_in);
      double GetMaxStepDistance() const;
      void   SetMaxStepDistance(double max_step_distance_in);
    protected:
      double width;
      double height;
      bool   fully_observable;
      double max_step_distance;
    private:
      ObstacleWorld  *data;
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<Environment>(*this);
	ar & width;
	ar & height;
	ar & fully_observable;
	ar & max_step_distance;
	ar & data;
      }
    };
  }
}
#endif /* _OBSTACLEENVIRONMENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
