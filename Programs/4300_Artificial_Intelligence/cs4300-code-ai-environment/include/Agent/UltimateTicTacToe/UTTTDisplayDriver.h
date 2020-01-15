#ifndef _UTTTDISPLAYDRIVER_H_
#define _UTTTDISPLAYDRIVER_H_
namespace ai
{
  namespace UltimateTicTacToe
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
#endif /* _UTTTDISPLAYDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
