#ifndef _OBSTACLEENVIRONMENTDRIVER_H_
#define _OBSTACLEENVIRONMENTDRIVER_H_

namespace ai
{
  namespace Agent
  {
    class ObstacleEnvironmentDriver : public EnvironmentDriver
    {
    public:
      ObstacleEnvironmentDriver(int argc, char **argv, bool init_options = true);
      virtual void Run();
    protected:
    private:
    };
  }
}

#endif /* _OBSTACLEENVIRONMENTDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
