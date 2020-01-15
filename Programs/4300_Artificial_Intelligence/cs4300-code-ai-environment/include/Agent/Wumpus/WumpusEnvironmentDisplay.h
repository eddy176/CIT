#ifndef _WUMPUSENVIRONMENTDISPLAY_H_
#define _WUMPUSENVIRONMENTDISPLAY_H_

namespace ai
{
  namespace Wumpus
  {
    class Environment;

    class EnvironmentDisplay : public ai::XY::EnvironmentDisplay
    {
    public:
      EnvironmentDisplay(ai::Agent::Environment *env, int width_in, int height_in);
      virtual ~EnvironmentDisplay();
      virtual void Redraw(ai::Agent::Environment *env);
    protected:
    private:
    };
  }
}

#endif /* _WUMPUSENVIRONMENTDISPLAY_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
