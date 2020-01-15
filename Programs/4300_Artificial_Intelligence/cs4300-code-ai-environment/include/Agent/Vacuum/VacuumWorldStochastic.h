#ifndef _VACUUMWORLDSTOCHASTIC_H_
#define _VACUUMWORLDSTOCHASTIC_H_

namespace ai
{
  namespace Agent
  {
    class VacuumWorldStochastic : public VacuumWorld
    {
    public:
      VacuumWorldStochastic(const RandomNumber &rand_in, 
			    int width, int height, bool do_display,
			    double dirty_percent_in);
      virtual void Step();
    protected:
      double dirty_percent;
    private:
    };
  }
}

#endif /* _VACUUMWORLDSTOCHASTIC_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
