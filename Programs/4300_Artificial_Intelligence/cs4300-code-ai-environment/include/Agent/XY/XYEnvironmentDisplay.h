#ifndef _XYENVIRONMENTDISPLAY_H_
#define _XYENVIRONMENTDISPLAY_H_

namespace ai
{
  namespace XY
  {
    class Environment;

    class EnvironmentDisplay : public ai::Agent::EnvironmentDisplay
    {
    public:
      EnvironmentDisplay(ai::Agent::Environment *env, int width_in, int height_in);
      virtual ~EnvironmentDisplay();
      virtual void Redraw(ai::Agent::Environment *env);
    protected:
      int spacing;
    private:
    };
  }
}
#endif /* _XYENVIRONMENTDISPLAY_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
