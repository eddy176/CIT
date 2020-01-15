#ifndef _VACUUMWORLDDISPLAY_H_
#define _VACUUMWORLDDISPLAY_H_

namespace ai
{
  namespace Agent
  {
    class VacuumWorld;
    class VacuumWorldDisplay : public XYEnvironmentDisplay
    {
    public:
      VacuumWorldDisplay(Environment *env);
      virtual ~VacuumWorldDisplay();
      virtual void Redraw(Environment *env);
    protected:
    private:
    };
  }
}

#endif /* _VACUUMWORLDDISPLAY_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
