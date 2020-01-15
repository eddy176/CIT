#ifndef _WUMPUSENVIRONMENT_H_
#define _WUMPUSENVIRONMENT_H_

namespace ai
{
  namespace Wumpus
  {
    class Environment : public ai::XY::Environment
    {
      friend class EnvironmentDisplay;
    public:
      Environment();
      Environment(const ai::Agent::RandomNumber &rand_in,
                  int width, int height, double pit_probability, int nirvana,
                  int drwho,
                  std::vector<ai::Agent::Socket *> *displays_in);
      virtual ~Environment();
      virtual bool ApplyAction(ai::Agent::Agent *agent, ai::Agent::Action *action);
      virtual void CalculatePerformance(ai::Agent::Agent *agent);
      virtual ai::Agent::Percept *GetPercept(ai::Agent::Agent *agent);
      virtual void AddAgent(ai::Agent::Agent *agent_in);
      /*
       * Handle messages with the client.
       */
      virtual bool GetUpdateMessage(ai::Agent::Message &omsg);
      virtual bool UpdateFromMessage(ai::Agent::Message &imsg);

    protected:
      bool InPit(ai::Agent::Agent *agent_in);
      bool EatenByWumpus(ai::Agent::Agent *agent_in);

      bool GrabGold(ai::XY::Location *xy_loc);
      void ShootArrow(ai::XY::Location *xy_loc, int direction);

      void Visit(int x, int y);
      bool IsVisited(int x, int y) const;

    protected:
      std::vector<int> visited;
      int nirvana;
      int drwho;
      double pit_probability;
      ai::Agent::Message old_message;
    };
  }
}

#endif /* _WUMPUSENVIRONMENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
