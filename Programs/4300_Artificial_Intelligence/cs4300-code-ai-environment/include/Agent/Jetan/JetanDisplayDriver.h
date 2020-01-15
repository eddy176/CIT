#ifndef _JETANDISPLAYDRIVER_H_
#define _JETANDISPLAYDRIVER_H_
namespace ai
{
  namespace Jetan
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
#endif /* _JETANDISPLAYDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
