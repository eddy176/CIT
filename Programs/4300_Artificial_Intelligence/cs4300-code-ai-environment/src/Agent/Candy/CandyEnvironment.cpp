#include <ai_candy.h>
#include <fstream>

#ifdef WIN32
#include <windows.h>
#define sleep(x) Sleep(x*1000);
#else
#include <unistd.h>
#endif

namespace ai
{
  namespace Candy
  {
    static const double discrete_bag_probability[]    = { 0.10, 0.20, 0.40, 0.20, 0.10 };
    static const double discrete_cherry_probability[] = { 1.00, 0.75, 0.50, 0.25, 0.00 };
    static const int discrete_count = sizeof(discrete_bag_probability)/sizeof(discrete_bag_probability[0]);

    Environment::Environment()
    {
    }

    Environment::Environment(const ai::Agent::RandomNumber &rand_in, std::vector<ai::Agent::Socket *> *displays_in,
                             const int &environment_type_in)
      : ai::Agent::Environment(rand_in, displays_in),
        environment_type(environment_type_in),
        time_step(0),
        num_flavors(2),
        current_flavor(-1)
    {
      int i;
      double cherry_prob = 0.50;
      double lime_prob   = 0.50;
      if(this->environment_type == DISCRETE5)
        {
          double r = this->random_number.Rand();
          double p = 0.0;
          for(i = 0; i < discrete_count; i++)
            {
              p += discrete_bag_probability[i];
              if(r < p)
                {
                  break;
                }
            }
          cherry_prob = discrete_cherry_probability[i];
          lime_prob = 1.00 - cherry_prob;
        }
      else if(this->environment_type == UNIFORM)
        {
          cherry_prob = this->random_number.Rand();
          lime_prob = 1.0 - cherry_prob;
        }
      else if(this->environment_type == MIXED_BAG)
        {
          std::vector<double> bag1;
          std::vector<double> bag2;
          double bag1_prob = this->random_number.Rand();
          double bag2_prob = 1.0 - bag1_prob;

          /* Choose bags */
          this->bag_probabilities.push_back(bag1_prob);
          this->bag_probabilities.push_back(bag2_prob);

          /* Choose flavors */
          bag1.clear();
          cherry_prob = this->random_number.Rand();
          lime_prob = 1.0 - cherry_prob;
          bag1.push_back(cherry_prob);
          bag1.push_back(lime_prob);
          this->bag_flavor_probabilities.push_back(bag1);

          bag2.clear();
          cherry_prob = this->random_number.Rand();
          lime_prob = 1.0 - cherry_prob;
          bag2.push_back(cherry_prob);
          bag2.push_back(lime_prob);
          this->bag_flavor_probabilities.push_back(bag2);

          /* Choose wrappers */
          bag1.clear();
          cherry_prob = this->random_number.Rand();
          lime_prob = 1.0 - cherry_prob;
          bag1.push_back(cherry_prob);
          bag1.push_back(lime_prob);
          this->bag_wrapper_probabilities.push_back(bag1);

          bag2.clear();
          cherry_prob = this->random_number.Rand();
          lime_prob = 1.0 - cherry_prob;
          bag2.push_back(cherry_prob);
          bag2.push_back(lime_prob);
          this->bag_wrapper_probabilities.push_back(bag2);

          /* Choose holes */
          bag1.clear();
          cherry_prob = this->random_number.Rand();
          lime_prob = 1.0 - cherry_prob;
          bag1.push_back(cherry_prob);
          bag1.push_back(lime_prob);
          this->bag_hole_probabilities.push_back(bag1);

          bag2.clear();
          cherry_prob = this->random_number.Rand();
          lime_prob = 1.0 - cherry_prob;
          bag2.push_back(cherry_prob);
          bag2.push_back(lime_prob);
          this->bag_hole_probabilities.push_back(bag2);

        }
      else
        {
          std::cout << "Error, unexpected environment type: " << this->environment_type << std::endl;
          std::exit(1);
        }
      this->flavor_probabilities.push_back(cherry_prob);
      this->flavor_probabilities.push_back(lime_prob);
      this->flavor_history.push_back(0);
      this->flavor_history.push_back(0);
    }

    Environment::~Environment()
    {
    }

    bool Environment::ApplyAction(ai::Agent::Agent *agent_in, ai::Agent::Action *action_in)
    {
      if(!agent_in->IsAlive())
        {
          return false;
        }
      Action *action = dynamic_cast<Action *>(action_in);
      Agent  *agent  = dynamic_cast<Agent *>(agent_in);

      switch(action->GetCode())
        {
        case Action::PREDICT:
          return this->PredictAgent(agent, action->GetFlavorPrediction(), action->GetProbabilityPrediction());
          break;
        case Action::PREDICT_MIXED_BAG:
          return this->PredictMixedBagAgent(agent, action);
          break;
        case Action::QUIT:
          return this->QuitAgent(agent);
          break;
        case Action::NOOP:
          return this->NoopAgent(agent);
          break;
        default:
          std::cerr << "Unknown action code: " << action->GetCode() << std::endl;
          return false;
        }

      return true;
    }

    void Environment::CalculatePerformance(ai::Agent::Agent *agent_in)
    {
      /* The performance is 1/average_error.
       * If the agent didn't make a prediction every time step, the performance is 0.
       */
      Agent  *agent  = dynamic_cast<Agent *>(agent_in);

      agent->SetPerformance(0);

      int n = agent->GetNumberOfPredictions();
      if(n == this->time_step + 1)
        {
          double total_error = agent->GetTotalError();
          double average_error = total_error/n;

          agent->AddPerformance(1.0/average_error);
        }
      else
        {
          std::cout << "n: " << n << " time_step: " << this->time_step << std::endl;
        }
      return;
    }

    ai::Agent::Percept *Environment::GetPercept(ai::Agent::Agent *agent_in)
    {
      ai::Agent::Percept *percept = ai::Agent::Environment::GetPercept(agent_in);
      /*
       * Environment specific percepts go here
       */
      if(this->environment_type == DISCRETE5)
        {
          char flavor_percept_str[32];
          char flavor_prob_str[32];
          char bag_percept_str[32];
          char bag_prob_str[32];
          char env_str[32];
          int i;
          for(i = 0; i < discrete_count; i++)
            {
              std::sprintf(bag_prob_str, "%f", discrete_bag_probability[i]);
              std::sprintf(bag_percept_str, "BAG_PROB%d", i);

              ai::Agent::PerceptAtom p_BAG_PROB(bag_percept_str, bag_prob_str);
              percept->JoinAtom(p_BAG_PROB);

              std::sprintf(flavor_prob_str, "%f", discrete_cherry_probability[i]);
              std::sprintf(flavor_percept_str, "FLAVOR_PROB%d", i);

              ai::Agent::PerceptAtom p_FLAVOR_PROB(flavor_percept_str, flavor_prob_str);
              percept->JoinAtom(p_FLAVOR_PROB);
            }
          ai::Agent::PerceptAtom p_ENV("DISCRETE", "T");
          percept->JoinAtom(p_ENV);

          std::sprintf(env_str, "%d", discrete_count);
          ai::Agent::PerceptAtom p_ENV_COUNT("DISCRETE_COUNT", env_str);
          percept->JoinAtom(p_ENV_COUNT);

          char flavor_str[16];
          std::sprintf(flavor_str, "%d", this->current_flavor);

          ai::Agent::PerceptAtom p_FLAVOR("FLAVOR", flavor_str);
          percept->JoinAtom(p_FLAVOR);
        }
      else if(this->environment_type == UNIFORM)
        {
          ai::Agent::PerceptAtom p_ENV("UNIFORM", "T");
          percept->JoinAtom(p_ENV);

          char flavor_str[16];
          std::sprintf(flavor_str, "%d", this->current_flavor);

          ai::Agent::PerceptAtom p_FLAVOR("FLAVOR", flavor_str);
          percept->JoinAtom(p_FLAVOR);
        }
      else if(this->environment_type == MIXED_BAG)
        {
          /* environment type */
          ai::Agent::PerceptAtom p_ENV("MIXED_BAG", "T");
          percept->JoinAtom(p_ENV);

          /* number of samples */
          char percept_name_str[32];
          char percept_value_str[32];

          std::sprintf(percept_name_str,  "SAMPLES");
          std::sprintf(percept_value_str, "%d", this->number_of_samples);

          ai::Agent::PerceptAtom p_SAMPLES(percept_name_str, percept_value_str);
          percept->JoinAtom(p_SAMPLES);


          /* each sample */
          int flavor, wrapper, hole;
          unsigned int i;
          for(i = 0; i < this->samples.size(); i++)
            {
              /* flavor */
              flavor = this->samples[i][0];
              std::sprintf(percept_name_str,  "FLAVOR%d", i);
              std::sprintf(percept_value_str, "%d", flavor);
              ai::Agent::PerceptAtom p_FLAVOR(percept_name_str, percept_value_str);
              percept->JoinAtom(p_FLAVOR);

              /* wrapper */
              wrapper = this->samples[i][1];
              std::sprintf(percept_name_str,  "WRAPPER%d", i);
              std::sprintf(percept_value_str, "%d", wrapper);
              ai::Agent::PerceptAtom p_WRAPPER(percept_name_str, percept_value_str);
              percept->JoinAtom(p_WRAPPER);

              /* hole */
              hole = this->samples[i][2];
              std::sprintf(percept_name_str,  "HOLE%d", i);
              std::sprintf(percept_value_str, "%d", hole);
              ai::Agent::PerceptAtom p_HOLE(percept_name_str, percept_value_str);
              percept->JoinAtom(p_HOLE);
            }

        }
      return percept;
    }


    void Environment::Step()
    {
      /* pick a candy from the bag */
      if(this->environment_type == MIXED_BAG)
        {
          this->SetMixedBagSamples();
        }
      else /* DISCRETE5 or UNIFORM */
        {
          int j;
          double p, r;
          this->current_flavor = -1;
          r = this->random_number.Rand();
          p = 0.0;
          for(j = 0; j < this->num_flavors; j++)
            {
              p += this->flavor_probabilities[j];
              if(r < p)
                {
                  this->current_flavor = j;
                  break;
                }
            }
          if((this->current_flavor < 0) || (this->current_flavor >= this->num_flavors))
            { // ERROR
            }
          else
            {
              this->flavor_history[this->current_flavor]++;
            }
        }

      /* randomize order of agents */
      size_t i;
      for(i = 0; i < agents_order.size(); i++)
        {
          size_t j = (size_t)(this->random_number.Rand() * agents_order.size());
          j %= agents_order.size();
          unsigned int t = agents_order[i];
          agents_order[i] = agents_order[j];
          agents_order[j] = t;
        }

      /* process the agents */
      for(i = 0; i < agents_order.size(); i++)
        {
          if(!agents[agents_order[i]]->IsAlive())
            {
              continue;
            }
          Agent  *agent  = dynamic_cast<Agent *>(agents[agents_order[i]]);

          /* build percepts */
          ai::Agent::Percept *percept = this->GetPercept(agent);

          /* ask for action */
          ai::Agent::Action  *action  = agent->Program(percept);
          delete percept;

          /* apply the action */
          if(action)
            {
              if(!this->ApplyAction(agent, action))
                {
                  // problem
                }
              delete action;
            }

          this->CalculatePerformance(agent);

          this->UpdateDisplays();
        }

      /* update displays */
      this->UpdateDisplays();
    }

    void Environment::Run(const int n_steps)
    {
      size_t i;
      for(i = 0; i < agents_order.size(); i++)
        {
          agents[agents_order[i]]->SetPerformance(0);
        }
      this->UpdateDisplays();
      if(this->delay)
        {
          sleep(this->delay);
        }
      for(this->time_step = 0; this->time_step < n_steps; this->time_step++)
        {
          unsigned int alive_agents = 0;
          for(i = 0; i < agents_order.size(); i++)
            {
              if(agents[agents_order[i]]->IsAlive())
                {
                  alive_agents ++;
                }
            }
          if(alive_agents > 0)
            {
              this->Step();
              if(this->delay)
                {
                  sleep(this->delay);
                }
            }
        }
    }

    ai::Agent::Location *Environment::DefaultLocation() const
    { // we don't use location
      return 0;
    }

    bool Environment::GetUpdateMessage(ai::Agent::Message &omsg)
    {
      if(!ai::Agent::Environment::GetUpdateMessage(omsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to get parent class data." << std::endl);
          return false;
        }

      /*
       * Candy::Environment data
       */
      ADD_TO_MSG_IF_CHANGED("ENVIRONMENT_TYPE", environment_type, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("TIME_STEP", time_step, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("NUM_FLAVORS", num_flavors, omsg, mLastMessage);
      ADD_VECTOR_TO_MSG_IF_CHANGED("FLAVOR_PROBABILITIES", flavor_probabilities, omsg, mLastMessage);
      ADD_VECTOR_TO_MSG_IF_CHANGED("FLAVOR_HISTORY", flavor_history, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("CURRENT_FLAVOR", current_flavor, omsg, mLastMessage);

      ADD_VECTOR_TO_MSG_IF_CHANGED("BAG_PROBABILITES", bag_probabilities, omsg, mLastMessage);
      ADD_VECTOR_OF_VECTOR_TO_MSG_IF_CHANGED("BAG_FLAVOR_PROBABILIITES", bag_flavor_probabilities, omsg, mLastMessage);
      ADD_VECTOR_OF_VECTOR_TO_MSG_IF_CHANGED("BAG_WRAPPER_PROBABILITIES", bag_wrapper_probabilities, omsg, mLastMessage);
      ADD_VECTOR_OF_VECTOR_TO_MSG_IF_CHANGED("BAG_HOLE_PROBABILITIES", bag_hole_probabilities, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("NUMBER_OF_SAMPLES", number_of_samples, omsg, mLastMessage);
      ADD_VECTOR_OF_VECTOR_TO_MSG_IF_CHANGED("SAMPLES", samples, omsg, mLastMessage);

      return true;
    }

    bool Environment::UpdateFromMessage(ai::Agent::Message &imsg)
    {
      MSG_MAKE_AGENTS_EXIST(imsg);

      /* MSG_MAKE_OBJECTS_EXIST(imsg);
       */

      if(!ai::Agent::Environment::UpdateFromMessage(imsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to update parent class." << std::endl);
          return false;
        }

      SET_FROM_MSG_IF_EXISTS("ENVIRONMENT_TYPE", environment_type, imsg);
      SET_FROM_MSG_IF_EXISTS("TIME_STEP", time_step, imsg);
      SET_FROM_MSG_IF_EXISTS("NUM_FLAVORS", num_flavors, imsg);
      SET_VECTOR_FROM_MSG_IF_EXISTS("FLAVOR_PROBABILITIES", flavor_probabilities, imsg);
      SET_VECTOR_FROM_MSG_IF_EXISTS("FLAVOR_HISTORY", flavor_history, imsg);
      SET_FROM_MSG_IF_EXISTS("CURRENT_FLAVOR", current_flavor, imsg);

      SET_VECTOR_FROM_MSG_IF_EXISTS("BAG_PROBABILITES", bag_probabilities, imsg);
      SET_VECTOR_OF_VECTOR_FROM_MSG_IF_EXISTS("BAG_FLAVOR_PROBABILIITES", bag_flavor_probabilities, imsg);
      SET_VECTOR_OF_VECTOR_FROM_MSG_IF_EXISTS("BAG_WRAPPER_PROBABILITIES", bag_wrapper_probabilities, imsg);
      SET_VECTOR_OF_VECTOR_FROM_MSG_IF_EXISTS("BAG_HOLE_PROBABILITIES", bag_hole_probabilities, imsg);
      SET_FROM_MSG_IF_EXISTS("NUMBER_OF_SAMPLES", number_of_samples, imsg);
      SET_VECTOR_OF_VECTOR_FROM_MSG_IF_EXISTS("SAMPLES", samples, imsg);

      return true;
    }

    int Environment::GetEnvironmentType() const
    {
      return this->environment_type;
    }

    int Environment::GetCurrentFlavor() const
    {
      return this->current_flavor;
    }

    int Environment::GetNumberOfFlavors( ) const
    {
      return this->num_flavors;
    }

    double Environment::GetFlavorProbability( const int &flavor_in ) const
    {
      if(flavor_in < 0 || flavor_in >= this->num_flavors)
        {
          return 0.0;
        }
      return this->flavor_probabilities[flavor_in];
    }

    bool Environment::SetNumberOfSamples( const int &number_of_samples_in )
    {
      this->number_of_samples = number_of_samples_in;
      return true;
    }

    double Environment::GetBagProbability( const int &bag_in ) const
    {
      if(bag_in < 0 || bag_in >= (int)this->bag_probabilities.size())
        {
          return 0.0;
        }
      return this->bag_probabilities[bag_in];
    }
    double Environment::GetBagFlavorProbability( const int &bag_in, const int &flavor_in ) const
    {
      if(bag_in < 0 || bag_in >= (int)this->bag_flavor_probabilities.size())
        {
          return 0.0;
        }
      if(flavor_in < 0 || flavor_in >= (int)this->bag_flavor_probabilities[bag_in].size())
        {
          return 0.0;
        }
      return this->bag_flavor_probabilities[bag_in][flavor_in];
    }
    double Environment::GetBagWrapperProbability( const int &bag_in, const int &wrapper_in ) const
    {
      if(bag_in < 0 || bag_in >= (int)this->bag_wrapper_probabilities.size())
        {
          return 0.0;
        }
      if(wrapper_in < 0 || wrapper_in >= (int)this->bag_wrapper_probabilities[bag_in].size())
        {
          return 0.0;
        }
      return this->bag_wrapper_probabilities[bag_in][wrapper_in];
    }
    double Environment::GetBagHoleProbability( const int &bag_in, const int &hole_in ) const
    {
      if(bag_in < 0 || bag_in >= (int)this->bag_hole_probabilities.size())
        {
          return 0.0;
        }
      if(hole_in < 0 || hole_in >= (int)this->bag_hole_probabilities[bag_in].size())
        {
          return 0.0;
        }
      return this->bag_hole_probabilities[bag_in][hole_in];
    }


    void Environment::TextDisplay(std::ostream &os) const
    {
      unsigned int i;
      os << this->time_step << " "
         << this->num_flavors << " ";
      for(i = 0; i < this->flavor_probabilities.size(); i++)
        {
          os << this->flavor_probabilities[i] << " ";
        }
      for(i = 0; i < this->flavor_history.size(); i++)
        {
          os << this->flavor_history[i] << " ";
        }
      os << this->current_flavor << std::endl;
    }

    bool Environment::PredictAgent(Agent *agent, const int &flavor_prediction, const double &probability_prediction)
    {
      return agent->Predict(flavor_prediction, probability_prediction);
    }

    bool Environment::PredictMixedBagAgent(Agent *agent, const Action * const action)
    {
      return agent->PredictMixedBag(action);
    }

    bool Environment::QuitAgent(Agent *agent)
    {
      return agent->Quit();
    }

    bool Environment::NoopAgent(Agent *agent)
    {
      return agent->Noop();
    }

    bool Environment::SetMixedBagSamples()
    {
      int i;
      double r,p;
      unsigned int j;
      int bag, flavor, wrapper, hole;

      this->samples.clear();

      for(i = 0; i < this->number_of_samples; i++)
        {
          std::vector<int> sample;

          /* Choose bag */
          r = this->random_number.Rand();
          p = 0.0;
          for(j = 0; j < this->bag_probabilities.size(); j++)
            {
              p += this->bag_probabilities[j];
              if(r < p) { break; }
            }
          if(j >= this->bag_probabilities.size()) { j = this->bag_probabilities.size() - 1; }
          bag = j;


          /* Choose flavor */
          r = this->random_number.Rand();
          p = 0.0;
          for(j = 0; j < this->bag_flavor_probabilities[bag].size(); j++)
            {
              p += this->bag_flavor_probabilities[bag][j];
              if(r < p) { break; }
            }
          if(j >= this->bag_flavor_probabilities[bag].size()) { j = this->bag_flavor_probabilities[bag].size() - 1; }
          flavor = j;


          /* Choose wrapper */
          r = this->random_number.Rand();
          p = 0.0;
          for(j = 0; j < this->bag_wrapper_probabilities[bag].size(); j++)
            {
              p += this->bag_wrapper_probabilities[bag][j];
              if(r < p) { break; }
            }
          if(j >= this->bag_wrapper_probabilities[bag].size()) { j = this->bag_wrapper_probabilities[bag].size() - 1; }
          wrapper = j;


          /* Choose hole */
          r = this->random_number.Rand();
          p = 0.0;
          for(j = 0; j < this->bag_hole_probabilities[bag].size(); j++)
            {
              p += this->bag_hole_probabilities[bag][j];
              if(r < p) { break; }
            }
          if(j >= this->bag_hole_probabilities[bag].size()) { j = this->bag_hole_probabilities[bag].size() - 1; }
          hole = j;

          sample.push_back(flavor);
          sample.push_back(wrapper);
          sample.push_back(hole);

          this->samples.push_back(sample);
        }

      return true;
    }


  }
}
