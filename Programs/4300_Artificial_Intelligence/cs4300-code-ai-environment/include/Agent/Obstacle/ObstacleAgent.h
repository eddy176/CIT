#ifndef _OBSTACLEAGENT_H_
#define _OBSTACLEAGENT_H_

namespace ai
{
  namespace Agent
  {
    class ObstacleAgent : public Agent
    {
    public:
      ObstacleAgent();
      ObstacleAgent(Socket * sock_in);
      virtual Percept *GetPercept(const Location *location);
      virtual void Go(double direction_in, double distance_in);
      virtual void Stop();
      virtual bool GetStopped() const;
      virtual bool GetBump() const;
      virtual void SetBump(bool bump_in);
      double  GetPathCost() const;
      bool    GetFoundGoal() const;
      void    FoundGoal();
    protected:
      bool   stopped;
      bool   bump;
      bool   found_goal;
      double path_cost;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<Agent>(*this);
	ar & stopped;
	ar & bump;
	ar & found_goal;
	ar & path_cost;
      }
    };
  }
}

#endif /* _OBSTACLEAGENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
