#ifndef _OBSTACLEENVIRONMENTDISPLAY_H_
#define _OBSTACLEENVIRONMENTDISPLAY_H_

namespace ai
{
  namespace Agent
  {
    class ObstacleEnvironment;
    
    class ObstacleEnvironmentDisplay : public EnvironmentDisplay
    {
    public:
      ObstacleEnvironmentDisplay(Environment *env, int width_in, int height_in);
      virtual ~ObstacleEnvironmentDisplay();
      virtual void Redraw(Environment *env);
      void SetSize(double width_in, double height_in);
    protected:
      double scaling;
    private:
    };
  }
}
#endif /* _OBSTACLEENVIRONMENTDISPLAY_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
