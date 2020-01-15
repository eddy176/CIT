#ifndef _MANCALAENVIRONMENT_H_
#define _MANCALAENVIRONMENT_H_
namespace ai
{
  namespace Mancala
  {
    class Environment : public ai::Agent::Environment
    {
      friend class EnvironmentDisplay;
    public:
      Environment();
      Environment(const ai::Agent::RandomNumber &rand_in, std::vector<ai::Agent::Socket *> *displays_in);
      virtual ~Environment();

      /*
       * Apply the move that is returned by an agent
       */
      virtual bool ApplyAction(ai::Agent::Agent *agent, ai::Agent::Action *action);

      /*
       * Calculate the agent's score
       */
      virtual void CalculatePerformance(ai::Agent::Agent *agent);

      /*
       * The percept is a copy of the game board
       */
      virtual ai::Agent::Percept *GetPercept(ai::Agent::Agent *agent);

      /*
       * Step applies 1 ply for the current player
       */
      virtual void Step();

      /*
       * Run until the game has completed, or n_steps have been reached
       */
      virtual void Run(const int n_steps);

      /*
       *
       */
      virtual void AddAgent(ai::Agent::Agent *agent);

      /*
       * Agent Locations are not used, but must override this
       * not to be an abstract class
       */
      virtual ai::Agent::Location *DefaultLocation() const;

      /*
       * Handle messages with the client.
       */
      virtual bool GetUpdateMessage(ai::Agent::Message &omsg);
      virtual bool UpdateFromMessage(ai::Agent::Message &imsg);

      /*
       * Get a reference to the game board
       */
      const Board & GameBoard() const;

    protected:
      Board game_board;
    private:
    };
  }
}
#endif /* _MANCALAENVIRONMENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
