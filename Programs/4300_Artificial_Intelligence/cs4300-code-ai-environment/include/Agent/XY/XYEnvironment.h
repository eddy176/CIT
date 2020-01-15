#ifndef _XYENVIRONMENT_H_
#define _XYENVIRONMENT_H_

namespace ai
{
  namespace XY
  {
    class Environment : public ai::Agent::Environment
    {
      friend class EnvironmentDisplay;
    public:
      Environment();
      Environment(const ai::Agent::RandomNumber &rand_in,
                  int width_in, int height_in, std::vector<ai::Agent::Socket *> *displays_in);
      virtual ~Environment();
      virtual bool ApplyAction(ai::Agent::Agent *agent, ai::Agent::Action *action);
      virtual void CalculatePerformance(ai::Agent::Agent *agent);
      virtual ai::Agent::Percept *GetPercept(ai::Agent::Agent *agent);
      virtual ai::Agent::Location *DefaultLocation() const;
      /*
       * Handle messages with the client.
       */
      virtual bool GetUpdateMessage(ai::Agent::Message &omsg);
      virtual bool UpdateFromMessage(ai::Agent::Message &imsg);

      int GetWidth() const;
      int GetHeight() const;
    protected:
      int width;
      int height;
    private:
    };
  }
}
#endif /* _XYENVIRONMENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
