#ifndef _MANCALAENVIRONMENTDRIVER_H_
#define _MANCALAENVIRONMENTDRIVER_H_
namespace ai
{
  namespace Mancala
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
#endif /* _MANCALAENVIRONMENTDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
