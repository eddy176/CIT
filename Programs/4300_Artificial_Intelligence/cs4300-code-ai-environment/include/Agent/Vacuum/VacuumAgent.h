#ifndef _VACUUMAGENT_H_
#define _VACUUMAGENT_H_

namespace ai
{
  namespace Agent
  {
    class VacuumAgent : public XYAgent
    {
    public:
      VacuumAgent(AgentProgram *agent_program_in);
      virtual Percept *GetPercept(const Location *location);
      virtual bool Suck();
      virtual bool EmptyBag();
      int     GetNumDirt() const;
    protected:
      int n_dirt; /* The number of dirts that have been
		   * stored in the cleaners bag */
    private:
    };
  }
}

#endif /* _VACUUMAGENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
