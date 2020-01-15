#include <ai_candy.h>
#include <cmath>
#include <cstdio>

namespace ai
{
  namespace Candy
  {
    Agent::Agent()
    {
    }

    Agent::Agent(ai::Agent::Socket *sock_in)
      : ai::Agent::Agent(sock_in),
        total_error(0),
        smallest_error(1.e12),
        number_of_predictions(0)
    {
    }

    ai::Agent::Percept *Agent::GetPercept(const ai::Agent::Location *location_in)
    {
      ai::Agent::Percept *p = new ai::Agent::Percept;
      /* no percepts from the agent */
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
      // 
      ADD_TO_MSG_IF_CHANGED("OBJECT_CANDYAGENT_TOTAL_ERROR " << m_object_id, total_error, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_CANDYAGENT_SMALLEST_ERROR " << m_object_id, smallest_error, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_CANDYAGENT_NUMBER_OF_PREDICTIONS " << m_object_id, number_of_predictions, omsg, old_msg);
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
      // 
      SET_FROM_MSG_IF_EXISTS("OBJECT_CANDYAGENT_TOTAL_ERROR " << m_object_id, total_error, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_CANDYAGENT_SMALLEST_ERROR " << m_object_id, smallest_error, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_CANDYAGENT_NUMBER_OF_PREDICTIONS " << m_object_id, number_of_predictions, imsg);
      return true;
    }

    bool Agent::Predict (const int &flavor_prediction, const double &probability_prediction)
    {
      const Environment *env = dynamic_cast<const Environment *>(this->environment);
      double probability = env->GetFlavorProbability(flavor_prediction);
      double dp = std::fabs(probability - probability_prediction);
      if(dp < this->smallest_error)
        {
          this->smallest_error = dp;
        }
      this->total_error += dp;
      this->number_of_predictions += 1;

      return true;
    }

    bool Agent::PredictMixedBag (const Action * const action)
    {
      const Environment *env = dynamic_cast<const Environment *>(this->environment);
      std::vector<double> bag_p = action->GetBagProbabilities();
      std::vector< std::vector<double> > flavor_p = action->GetBagFlavorProbabilities();
      std::vector< std::vector<double> > wrapper_p = action->GetBagWrapperProbabilities();
      std::vector< std::vector<double> > hole_p = action->GetBagHoleProbabilities();

      double p1, p2, dp;
      unsigned int i, j;

      /* bags, flavors, wrappers, holes */
      for(i = 0; i < bag_p.size(); i++)
        {
          p1 = env->GetBagProbability(i);
          p2 = bag_p[i];
          dp = std::fabs(p1 - p2);
          this->smallest_error = std::min(this->smallest_error, dp);
          this->total_error += dp;

          for(j = 0; j < flavor_p.size(); j++)
            {
              p1 = env->GetBagFlavorProbability(i, j);
              p2 = flavor_p[i][j];
              dp = std::fabs(p1 - p2);
              this->smallest_error = std::min(this->smallest_error, dp);
              this->total_error += dp;

              p1 = env->GetBagWrapperProbability(i, j);
              p2 = wrapper_p[i][j];
              dp = std::fabs(p1 - p2);
              this->smallest_error = std::min(this->smallest_error, dp);
              this->total_error += dp;

              p1 = env->GetBagHoleProbability(i, j);
              p2 = hole_p[i][j];
              dp = std::fabs(p1 - p2);
              this->smallest_error = std::min(this->smallest_error, dp);
              this->total_error += dp;
            }
        }
      this->number_of_predictions += 1;

      return true;
    }

    bool Agent::Quit ( )
    {
      this->alive = false;
      return true;
    }

    bool Agent::Noop ( )
    {
      return true;
    }

    double Agent::GetTotalError() const
    {
      return this->total_error;
    }

    double Agent::GetSmallestError() const
    {
      return this->smallest_error;
    }

    int    Agent::GetNumberOfPredictions() const
    {
      return this->number_of_predictions;
    }

  }
}
