#ifndef _CANDYENVIRONMENTDISPLAY_H_
#define _CANDYENVIRONMENTDISPLAY_H_

namespace ai
{
  namespace Candy
  {
    class Environment;

    class EnvironmentDisplay : public ai::Agent::EnvironmentDisplay
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


#endif /* _CANDYENVIRONMENTDISPLAY_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
