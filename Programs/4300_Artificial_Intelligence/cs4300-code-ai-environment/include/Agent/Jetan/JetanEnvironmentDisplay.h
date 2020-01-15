#ifndef _JETANENVIRONMENTDISPLAY_H_
#define _JETANENVIRONMENTDISPLAY_H_
namespace ai
{
  namespace Jetan
  {
    class Environment;

    class EnvironmentDisplay : public ai::Agent::EnvironmentDisplay
    {
    public:
      EnvironmentDisplay(ai::Agent::Environment *env, int width_in, int height_in);
      virtual ~EnvironmentDisplay();

      /* game specific draw routines here */
      void DrawStats( ai::Agent::Environment *env );
      void DrawBoard( ai::Agent::Environment *env );
      void DrawAttackedSquares( ai::Agent::Environment *env );
      void DrawLastMove( ai::Agent::Environment *env );
      /* game specific draw routines here */
      

      
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
#endif /* _JETANENVIRONMENTDISPLAY_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
