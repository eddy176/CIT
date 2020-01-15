#include <ai_wumpus.h>
#include <cstdio>

#ifdef WIN32
#define sprintf sprintf
#else
#define sprintf std::sprintf
#endif

namespace ai
{
  namespace Wumpus
  {
    Agent::Agent()
    {
    }

    Agent::Agent(ai::Agent::Socket * sock_in)
      : ai::XY::Agent(sock_in)
    {
      arrows = 1;
      gold   = 0;
      yell_last = 0;
    }

    ai::Agent::Percept *Agent::GetPercept(const ai::Agent::Location *location)
    {
      char arrow_str[16];
      sprintf(arrow_str, "%d", arrows);
      char gold_str[16];
      sprintf(gold_str, "%d", gold);

      ai::Agent::Percept *p = new ai::Agent::Percept; // XYAgent::GetPercept(location);

      ai::Agent::PerceptAtom p_ARROWS("ARROWS", arrow_str);
      ai::Agent::PerceptAtom p_GOLD("GOLD", gold_str);

      p->JoinAtom(p_ARROWS);
      p->JoinAtom(p_GOLD);
      if(bump)
        {
          ai::Agent::PerceptAtom p_BUMP("BUMP", "T");
          p->JoinAtom(p_BUMP);
        }

      return p;
    }

    ai::Agent::Action * Agent::MessageToAction(const ai::Agent::Message &imsg) const
    {
      Action *action = new Action();
      if(!action->FromMessage(imsg))
        {
          delete action;
          action = 0;
        }
      return action;
    }

    // Add Object's data to omsg, if values are different than stored in old_msg
    bool Agent::AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg)
    {
      if(!ai::XY::Agent::AddToMessageIfChanged(omsg, old_msg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to add to message." << std::endl);
          return false;
        }
      // arrows, gold, yell_last
      ADD_TO_MSG_IF_CHANGED("OBJECT_WUMPUSAGENT_ARROWS " << m_object_id, arrows, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_WUMPUSAGENT_GOLD " << m_object_id, gold, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_WUMPUSAGENT_YELL_LAST " << m_object_id, yell_last, omsg, old_msg);
      return true;
    }

    // Set Object's data from imsg, if values associated with id are present
    bool Agent::SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg)
    {
      if(!ai::XY::Agent::SetFromMessageIfExists(id, imsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to extract from message." << std::endl);
          return false;
        }
      // arrows, gold, yell_last
      SET_FROM_MSG_IF_EXISTS("OBJECT_WUMPUSAGENT_ARROWS " << m_object_id, arrows, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_WUMPUSAGENT_GOLD " << m_object_id, gold, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_WUMPUSAGENT_YELL_LAST " << m_object_id, yell_last, imsg);
      return true;
    }

    void Agent::Shoot()
    {
      if(arrows > 0)
        {
          arrows --;
        }
    }
    void Agent::Grab()
    {
      gold++;
    }
    void Agent::Yell()
    {
      yell_last = 1;
    }
    void Agent::UnYell()
    {
      yell_last = 0;
    }

    int Agent::ArrowCount()
    {
      return arrows;
    }

    int Agent::GoldCount()
    {
      return gold;
    }

    bool Agent::GetYellLast()
    {
      return (yell_last == 1);
    }

  }
}
