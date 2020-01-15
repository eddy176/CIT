#include <ai_tictactoe.h>

int main(int argc, char **argv)
{
  ai::TicTacToe::DisplayDriver d(argc, argv);
  ai::TicTacToe::Environment *env = new ai::TicTacToe::Environment();
  d.SetEnvironment(env);
  d.Run();
  return 0;
}
