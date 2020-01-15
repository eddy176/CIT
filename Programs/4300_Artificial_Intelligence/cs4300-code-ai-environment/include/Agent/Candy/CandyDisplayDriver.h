#ifndef _CANDYDISPLAYDRIVER_H_
#define _CANDYDISPLAYDRIVER_H_
namespace ai
{
  namespace Candy
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
#endif /* _CANDYDISPLAYDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
