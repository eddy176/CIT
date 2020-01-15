#ifndef _SCAVENGERENVIRONMENTDISPLAY_H_
#define _SCAVENGERENVIRONMENTDISPLAY_H_

namespace ai
{
  namespace Scavenger
  {
    class Environment;

    class EnvironmentDisplay : public ai::Agent::EnvironmentDisplay
    {
    public:
      EnvironmentDisplay(ai::Agent::Environment *env, int width_in, int height_in);
      virtual ~EnvironmentDisplay();
      virtual void Redraw(ai::Agent::Environment *env);
      
      void ResetParameters();

    protected:

      int m_width_orig, m_height_orig;
      
      double scale;
      double minx;
      double maxx;
      double miny;
      double maxy;
      double spanx;
      double spany;

    private:

    };
  }
}

#endif /* _SCAVENGERENVIRONMENTDISPLAY_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
