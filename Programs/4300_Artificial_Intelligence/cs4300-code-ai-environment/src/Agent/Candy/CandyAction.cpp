#include <ai_candy.h>
#include <sstream>

namespace ai
{
  namespace Candy
  {
    Action::Action (  )
    {
      SetCode(NOOP);
    }

    Action::~Action()
    {
    }

    bool Action::TextDisplay(std::ostream &os) const
    {
      std::stringstream ss;

      switch(this->GetCode())
        {
        case PREDICT:
          ss << "PREDICT " << this->flavor_prediction << " " << this->probability_prediction;
          break;
        case PREDICT_MIXED_BAG:
          ss << "PREDICT_MIXED_BAG (";
          unsigned int i,j;
          for(i = 0; i < this->bag_probabilities.size(); i++)
            {
              ss << " { bag: ";
              ss << this->bag_probabilities[i];
              ss << " [ flavor: ";
              for(j = 0; j < this->bag_flavor_probabilities[i].size(); j++)
                {
                  ss << this->bag_flavor_probabilities[i][j] << " ";
                }
              ss << " ]";
              ss << " [ wrapper: ";
              for(j = 0; j < this->bag_wrapper_probabilities[i].size(); j++)
                {
                  ss << this->bag_wrapper_probabilities[i][j] << " ";
                }
              ss << " ]";
              ss << " [ hole: ";
              for(j = 0; j < this->bag_hole_probabilities[i].size(); j++)
                {
                  ss << this->bag_hole_probabilities[i][j] << " ";
                }
              ss << " ]";
              ss << " }";
            }
          ss << " )";
          break;
        case QUIT:
          ss << "QUIT";
          break;
        case NOOP:
          ss << "NOOP";
          break;
        default:
          ss << "UNKNOWN";
          break;
        }

      os << ss.str();
      return true;
    }

    bool Action::ToMessage(ai::Agent::Message &omsg) const
    {
      if(!omsg.SetName(ai::Agent::MESSAGE_ACTION_NAME))
        {
          return false;
        }
      ADD_TO_MSG("CODE", action_code, omsg);
      switch(action_code)
        {
        case PREDICT:
          ADD_TO_MSG("FLAVOR_PREDICTION", flavor_prediction, omsg);
          ADD_TO_MSG("PROBABILITY_PREDICTION", probability_prediction, omsg);
          break;
        case PREDICT_MIXED_BAG:
          ADD_VECTOR_TO_MSG("BAG_PROBABILITIES", bag_probabilities, omsg);
          ADD_VECTOR_OF_VECTOR_TO_MSG("BAG_FLAVOR_PROBABILITIES", bag_flavor_probabilities, omsg);
          ADD_VECTOR_OF_VECTOR_TO_MSG("BAG_WRAPPER_PROBABILITIES", bag_wrapper_probabilities, omsg);
          ADD_VECTOR_OF_VECTOR_TO_MSG("BAG_HOLE_PROBABILITIES", bag_hole_probabilities, omsg);
          break;
        case QUIT:
        case NOOP:
          // OK, no other data
          break;
        default:
          DBGP_E(LOG_STREAM(std::cerr) << "Bad action_code: " << action_code << std::endl);
          return false;
        }

      DBGP_MSG(LOG_STREAM(std::cerr) << "Message: " << omsg << std::endl);
      return true;
    }

    bool Action::FromMessage(const ai::Agent::Message &imsg)
    {
      if(imsg.GetName() != ai::Agent::MESSAGE_ACTION_NAME)
        {
          return false;
        }
      SET_FROM_MSG("CODE", action_code, imsg);
      switch(action_code)
        {
        case PREDICT:
          SET_FROM_MSG("FLAVOR_PREDICTION", flavor_prediction, imsg);
          SET_FROM_MSG("PROBABILITY_PREDICTION", probability_prediction, imsg);
          break;
        case PREDICT_MIXED_BAG:
          SET_VECTOR_FROM_MSG("BAG_PROBABILITIES", bag_probabilities, imsg);
          SET_VECTOR_OF_VECTOR_FROM_MSG("BAG_FLAVOR_PROBABILITIES", bag_flavor_probabilities, imsg);
          SET_VECTOR_OF_VECTOR_FROM_MSG("BAG_WRAPPER_PROBABILITIES", bag_wrapper_probabilities, imsg);
          SET_VECTOR_OF_VECTOR_FROM_MSG("BAG_HOLE_PROBABILITIES", bag_hole_probabilities, imsg);
          break;
        case QUIT:
        case NOOP:
          // OK, no other data
          break;
        default:
          DBGP_E(LOG_STREAM(std::cerr) << "Bad action_code: " << action_code << std::endl);
          return false;
        }
      return true;
    }
    
    bool Action::AddToMessageIfChanged(const std::string &keyprefix, ai::Agent::Message &omsg, ai::Agent::Message &old_msg)
    {
      DBGP_E(LOG_STREAM(std::cerr) << "Implement this method to remove this error" << std::endl);
      {
        int *x = 0;
        *x = 1;
      }
      return false;
    }
    
    bool Action::SetFromMessageIfExists(const std::string &keyprefix, ai::Agent::Message &imsg)
    {
      DBGP_E(LOG_STREAM(std::cerr) << "Implement this method to remove this error" << std::endl);
      {
        int *x = 0;
        *x = 1;
      }
      return false;
    }

    double Action::GetProbabilityPrediction (  ) const
    {
      return this->probability_prediction;
    }

    bool Action::SetProbabilityPrediction ( const double & probability_prediction_in )
    {
      this->probability_prediction = probability_prediction_in;
      return true;
    }

    int Action::GetFlavorPrediction ( ) const
    {
      return this->flavor_prediction;
    }

    bool Action::SetFlavorPrediction ( const int & flavor_prediction_in )
    {
      this->flavor_prediction = flavor_prediction_in;
      return true;
    }

    std::vector<double> Action::GetBagProbabilities ( ) const
    {
      return this->bag_probabilities;
    }
    std::vector< std::vector<double> > Action::GetBagFlavorProbabilities ( ) const
    {
      return this->bag_flavor_probabilities;
    }
    std::vector< std::vector<double> > Action::GetBagWrapperProbabilities ( ) const
    {
      return this->bag_wrapper_probabilities;
    }
    std::vector< std::vector<double> > Action::GetBagHoleProbabilities ( ) const
    {
      return this->bag_hole_probabilities;
    }

    bool Action::SetBagProbabilities ( const std::vector<double> &p_in )
    {
      this->bag_probabilities = p_in;
      return true;
    }
    bool Action::SetBagFlavorProbabilities ( const std::vector< std::vector<double> > &p_in )
    {
      this->bag_flavor_probabilities = p_in;
      return true;
    }
    bool Action::SetBagWrapperProbabilities ( const std::vector< std::vector<double> > &p_in )
    {
      this->bag_wrapper_probabilities = p_in;
      return true;
    }
    bool Action::SetBagHoleProbabilities ( const std::vector< std::vector<double> > &p_in )
    {
      this->bag_hole_probabilities = p_in;
      return true;
    }

  }
}

