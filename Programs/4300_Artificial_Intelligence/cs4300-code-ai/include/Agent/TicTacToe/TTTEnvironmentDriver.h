#ifndef _TTTENVIRONMENTDRIVER_H_
#define _TTTENVIRONMENTDRIVER_H_
namespace ai
{
  namespace TicTacToe
  {
    class EnvironmentDriver : public ai::Agent::EnvironmentDriver
    {
    public:
      EnvironmentDriver(int argc, char **argv, bool init_options = true);
      virtual void Run();
    protected:
    private:
    };
  }
}
#endif /* _TTTENVIRONMENTDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
