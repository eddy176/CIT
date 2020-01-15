#ifndef _MANCALADISPLAYDRIVER_H_
#define _MANCALADISPLAYDRIVER_H_
namespace ai
{
  namespace Mancala
  {
    class DisplayDriver : public ai::Agent::DisplayDriver
    {
    public:
      DisplayDriver(int argc, char **argv);
      virtual void SetEnvironmentDisplay(ai::Agent::Environment * env);
    protected:
    private:
    };
  }
}
#endif /* _MANCALADISPLAYDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
