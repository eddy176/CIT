#ifndef _UTTTENVIRONMENTDRIVER_H_
#define _UTTTENVIRONMENTDRIVER_H_
namespace ai
{
  namespace UltimateTicTacToe
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
#endif /* _UTTTENVIRONMENTDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
