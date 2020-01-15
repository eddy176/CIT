#ifndef _CANDYENVIRONMENTDRIVER_H_
#define _CANDYENVIRONMENTDRIVER_H_

namespace ai
{
  namespace Candy
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

#endif /* _CANDYENVIRONMENTDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
