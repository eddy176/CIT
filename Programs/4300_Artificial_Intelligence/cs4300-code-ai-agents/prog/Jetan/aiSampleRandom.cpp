#include "aiSampleRandom.h"
#include <ctime>
#include <cstdlib>
#include <sstream>

namespace ai
{
  namespace Jetan
  {
    Random::Random( ai::Agent::Options *opts ) {
      SetName( "Random" );
    }
    
    Random::~Random( ) {
    }
    
    ai::Agent::Action * Random::Program( const ai::Agent::Percept * percept ) {
      ai::Jetan::Action *action = new ai::Jetan::Action;
      
      std::string board_str = percept->GetAtom( "BOARD" ).GetValue( );
      ai::Jetan::Board board( board_str );

      std::stringstream ss( percept->GetAtom( "PLAYER_NUMBER" ).GetValue( ) );
      int player = 0;
      ss >> player;
      
      const std::vector< ai::Jetan::MoveData > & moves = board.DetermineLegalMoves( player );
      
      DBGP_ENV( LOG_STREAM( std::cout ) 
                << "board percept: " << board_str
                << std::endl );
      const BoardData& data = board.GetBoard( );
      unsigned int i;
      for( i = 0; i < 40; i++ ) {
        DBGP_ENV( LOG_STREAM( std::cout ) 
                  << "piece " << i << " :: " << (int)data.pieces[ i ].mLocation.x << "," << (int)data.pieces[ i ].mLocation.y
                  << std::endl );
      }
      DBGP_ENV( LOG_STREAM( std::cout ) 
                << "legal move count: " << moves.size( )
                << std::endl );
      for( i = 0; i < moves.size( ); i++ ) {
        DBGP_ENV( LOG_STREAM( std::cout ) 
                  << "move " << i << " :: " << moves[ i ]
                  << std::endl );
      }
      
      if( moves.size( ) > 0 ) {
        int random_i = rand( ) % moves.size( );
        ai::Jetan::MoveData random_move = moves[ random_i ];
        std::cout << "Choose: " << random_move << std::endl;
        action->SetMove( random_move );
        action->SetCode( ai::Jetan::Action::MOVE );
      } else {
        /* no legal move */
        action->SetCode( ai::Jetan::Action::QUIT );
      }
      return action;
    }
  }
}
