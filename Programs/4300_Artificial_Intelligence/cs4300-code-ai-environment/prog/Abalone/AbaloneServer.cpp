#include <ai_abalone.h>

int main(int argc, char **argv)
{
  ai::Abalone::EnvironmentDriver d(argc, argv);
  d.Run();
  return 0;
}
