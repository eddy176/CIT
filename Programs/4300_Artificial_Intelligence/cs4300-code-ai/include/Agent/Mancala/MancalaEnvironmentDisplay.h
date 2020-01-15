#ifndef _MANCALAENVIRONMENTDISPLAY_H_
#define _MANCALAENVIRONMENTDISPLAY_H_
namespace ai
{
  namespace Mancala
  {
    class Environment;

    class EnvironmentDisplay : public ai::Agent::EnvironmentDisplay
    {
    public:
      EnvironmentDisplay(ai::Agent::Environment *env, int width_in, int height_in);
      virtual ~EnvironmentDisplay();

      void DrawBoardOutline(ai::Agent::Environment *env);
      void DrawBins(ai::Agent::Environment *env);
      void DrawLastMoves(ai::Agent::Environment *env);
      void DrawStats(ai::Agent::Environment *env);

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
#endif /* _MANCALAENVIRONMENTDISPLAY_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
