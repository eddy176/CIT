#ifndef _VACUUMWORLD_H_
#define _VACUUMWORLD_H_

namespace ai
{
  namespace Agent
  {
    class VacuumWorld : public XYEnvironment
    {
      friend class VacuumWorldDisplay;
    public:
      VacuumWorld(const RandomNumber &rand_in,
		  int width, int height, bool do_display);
      virtual bool ApplyAction(Agent *agent, Action *action);
      virtual void CalculatePerformance(Agent *agent);

      bool SetMoveCost(int cost_in);
      bool SetSuckCost(int cost_in);
      bool SetEmptyCost(int cost_in);
      bool SetBagSize(int size_in);

      int GetMoveCost() const;
      int GetSuckCost() const;
      int GetEmptyCost() const;
      int GetBagSize() const;
      
    protected:
      int RemoveDirt(XYLocation *xy_loc, int max_remove);
      
      int move_cost;
      int suck_cost;
      int empty_cost;
      int bag_size;
    private:
    };
  }
}

#endif /* _VACUUMWORLD_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
