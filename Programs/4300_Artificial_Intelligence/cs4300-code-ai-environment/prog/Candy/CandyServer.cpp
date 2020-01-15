#include <ai_candy.h>

int main(int argc, char **argv)
{
  ai::Candy::EnvironmentDriver d(argc, argv);
  d.Run();
  return 0;
}
