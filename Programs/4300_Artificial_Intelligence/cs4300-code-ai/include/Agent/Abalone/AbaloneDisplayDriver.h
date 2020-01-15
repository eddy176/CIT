#ifndef _ABALONEDISPLAYDRIVER_H_
#define _ABALONEDISPLAYDRIVER_H_

namespace ai
{
  namespace Abalone
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
#endif /* _ABALONEDISPLAYDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
