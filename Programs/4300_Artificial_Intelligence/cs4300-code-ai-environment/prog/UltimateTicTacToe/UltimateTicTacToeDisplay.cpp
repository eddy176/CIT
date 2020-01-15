#include <ai_ultimatetictactoe.h>

int main(int argc, char **argv)
{
  ai::UltimateTicTacToe::DisplayDriver d(argc, argv);
  ai::UltimateTicTacToe::Environment *env = new ai::UltimateTicTacToe::Environment();
  d.SetEnvironment(env);
  d.Run();
  return 0;
}
