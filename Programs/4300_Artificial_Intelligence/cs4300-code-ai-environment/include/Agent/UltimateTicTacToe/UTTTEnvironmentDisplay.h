#ifndef _UTTTENVIRONMENTDISPLAY_H_
#define _UTTTENVIRONMENTDISPLAY_H_
namespace ai
{
  namespace UltimateTicTacToe
  {
    class Environment;

    class EnvironmentDisplay : public ai::Agent::EnvironmentDisplay
    {
    public:
      EnvironmentDisplay(ai::Agent::Environment *env, int width_in, int height_in);
      virtual ~EnvironmentDisplay();

      void DrawBoardLines(ai::Agent::Environment *env);
      void DrawNoughtsAndCrosses(ai::Agent::Environment *env);
      void DrawLastMoves(ai::Agent::Environment *env);
      void DrawStats(ai::Agent::Environment *env);
      void DrawWins(ai::Agent::Environment *env);
      void DrawWin(ai::Agent::Environment *env);
      
      virtual void Redraw(ai::Agent::Environment *env);

      void Quit();
      bool GetQuit() const;

      void MainLoop();
    protected:
      bool quit;
    private:
    };
  }
}
#endif /* _UTTTENVIRONMENTDISPLAY_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
