#ifndef _JETANENVIRONMENTDRIVER_H_
#define _JETANENVIRONMENTDRIVER_H_
namespace ai
{
  namespace Jetan
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
#endif /* _JETANENVIRONMENTDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
