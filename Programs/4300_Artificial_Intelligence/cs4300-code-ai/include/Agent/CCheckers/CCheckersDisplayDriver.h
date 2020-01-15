#ifndef _CCHECKERSDISPLAYDRIVER_H_
#define _CCHECKERSDISPLAYDRIVER_H_
namespace ai
{
  namespace CCheckers
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
#endif /* _CCHECKERSDISPLAYDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
