#ifndef _CCHECKERSENVIRONMENTDRIVER_H_
#define _CCHECKERSENVIRONMENTDRIVER_H_

namespace ai
{
  namespace CCheckers
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

#endif /* _CCHECKERSENVIRONMENTDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
