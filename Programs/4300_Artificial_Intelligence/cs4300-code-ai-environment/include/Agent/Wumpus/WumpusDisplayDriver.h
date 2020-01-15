#ifndef _WUMPUSDISPLAYDRIVER_H_
#define _WUMPUSDISPLAYDRIVER_H_
namespace ai
{
  namespace Wumpus
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
#endif /* _WUMPUSDISPLAYDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
