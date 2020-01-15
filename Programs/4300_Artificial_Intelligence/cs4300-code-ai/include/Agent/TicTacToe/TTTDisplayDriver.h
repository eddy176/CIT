#ifndef _TTTDISPLAYDRIVER_H_
#define _TTTDISPLAYDRIVER_H_
namespace ai
{
  namespace TicTacToe
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
#endif /* _TTTDISPLAYDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
