#ifndef _ABALONEENVIRONMENTDISPLAY_H_
#define _ABALONEENVIRONMENTDISPLAY_H_

namespace ai
{
  namespace Abalone
  {
    class Environment;

    class EnvironmentDisplay : public ai::Agent::EnvironmentDisplay
    {
    public:
      EnvironmentDisplay(ai::Agent::Environment *env, int width_in, int height_in);
      virtual ~EnvironmentDisplay();

      float DrawConvertX(int x, int y);
      void DrawGridLines();
      void DrawBoardLines(ai::Agent::Environment *env);
      void DrawHolesAndMarbles(ai::Agent::Environment *env);
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

#endif /* _ABALONEENVIRONMENTDISPLAY_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
