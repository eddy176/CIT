#ifndef _SCAVENGERDISPLAYDRIVER_H_
#define _SCAVENGERDISPLAYDRIVER_H_
namespace ai
{
  namespace Scavenger
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
#endif /* _SCAVENGERDISPLAYDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
