#include "aiSampleManual.h"
#include <cstdio>

namespace ai
{
  namespace Jetan
  {
    Manual::Manual( ai::Agent::Options *opts ) {
      SetName( "Manual" );
    }
    
    Manual::~Manual( ) {
    }
    
    ai::Agent::Action * Manual::Program( const ai::Agent::Percept * percept ) {
      ai::Jetan::Action *action = new ai::Jetan::Action;
      
      std::string board_str = percept->GetAtom( "BOARD" ).GetValue( );
      ai::Jetan::Board board( board_str );

      std::stringstream ss( percept->GetAtom( "PLAYER_NUMBER" ).GetValue( ) );
      int player = 0;
      ss >> player;

      const std::vector< ai::Jetan::MoveData > & moves = board.DetermineLegalMoves( player );
      
      if( moves.size( ) > 0 ) {
        std::cout << "Player: " << player << std::endl;
        std::cout << std::endl;
        std::cout << "Specify a move with 4 space separated integers: " << std::endl
                  << "from_column from_row  to_column to_row" << std::endl;
        bool done = false;
        while( !done ) {
          ai::Jetan::MoveData move;
          std::cout << "Move? ";
          std::string buf;
          std::getline( std::cin, buf );
          
          int from_row = -1, from_column = -1, to_row = -1, to_column = -1;
          std::stringstream ss( buf );
          std::string line = ss.str();
          if( line.size() > 0 && line[0] == 'q' ) {
            std::cout << "OK. Quitting." << std::endl;
            action->SetCode( ai::Jetan::Action::QUIT );
            done = true;
          } else {
            ss >> from_column >> from_row >> to_column >> to_row;
            if( ss 
                && from_row >= 0 && from_column >= 0 && to_row >= 0 && to_column >= 0
                && from_row < 10 && from_column < 10 && to_row < 10 && to_column < 10 )
              {
                move.piece.x = from_column;
                move.piece.y = from_row;
                move.offset.dx = to_column - from_column;
                move.offset.dy = to_row - from_row;
                if( board.IsLegal( player, move ) ) {
                  action->SetMove( move );
                  action->SetCode( ai::Jetan::Action::MOVE );
                  done = true;
                } // if legal
                else {
                  std::cout << from_column << "," << from_row << "->" << to_column << "," << to_row << " is not a legal move, try again." << std::endl;
                }
              } // if scanned
            else {
              std::cout << "The move did not appear to have the correct syntax." << std::endl
                        << "Rows and columns are from 0 to 9, inclusive." << std::endl
                        << "No characters besides the digits and spaces should be typed." << std::endl
                        << "The entire move needs to be specified in a single line." << std::endl;
            }
          }
        } // while
      } else {
        /* no legal move */
        std::cout << "No legal moves, quitting." << std::endl;
        action->SetCode( ai::Jetan::Action::QUIT );
      }
      return action;
    }
  }
}
