#include <ai_tictactoe.h>
#include <cstdio>

namespace ai
{
  namespace TicTacToe
  {
    Agent::Agent()
    {
    }
    Agent::Agent(ai::Agent::Socket * sock_in)
      : ai::Agent::Agent(sock_in)
    {
      player_number = -1;
      duration = 0;
    }
    Agent::~Agent()
    {
    }

    ai::Agent::Percept * Agent::GetPercept(const ai::Agent::Location *location_in)
    {
      ai::Agent::Percept *p = new ai::Agent::Percept;

      char buf[32];
      std::sprintf(buf, "%d", player_number);
      ai::Agent::PerceptAtom atom_who("PLAYER_NUMBER", buf);
      p->JoinAtom(atom_who);

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
      if(!ai::Agent::Agent::AddToMessageIfChanged(omsg, old_msg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to add to message." << std::endl);
          return false;
        }
      // player_number, duration
      ADD_TO_MSG_IF_CHANGED("OBJECT_TTTAGENT_PLAYER_NUMBER " << m_object_id, player_number, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_TTTAGENT_DURATION " << m_object_id, duration, omsg, old_msg);
      return true;
    }

    // Set Object's data from imsg, if values associated with id are present
    bool Agent::SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg)
    {
      if(!ai::Agent::Agent::SetFromMessageIfExists(id, imsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to extract from message." << std::endl);
          return false;
        }
      // player_number, duration
      SET_FROM_MSG_IF_EXISTS("OBJECT_TTTAGENT_PLAYER_NUMBER " << m_object_id, player_number, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_TTTAGENT_DURATION " << m_object_id, duration, imsg);
      return true;
    }

    bool Agent::SetPlayerNumber(int n_in)
    {
      player_number = n_in;
      return true;
    }

    int Agent::GetPlayerNumber() const
    {
      return player_number;
    }

    void Agent::SetDuration(double duration_in)
    {
      duration = duration_in;
    }

    double Agent::GetDuration() const
    {
      return duration;
    }
  }
}
