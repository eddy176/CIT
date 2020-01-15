#ifndef _WUMPUSENVIRONMENTDRIVER_H_
#define _WUMPUSENVIRONMENTDRIVER_H_

namespace ai
{
  namespace Wumpus
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

#endif /* _WUMPUSENVIRONMENTDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
