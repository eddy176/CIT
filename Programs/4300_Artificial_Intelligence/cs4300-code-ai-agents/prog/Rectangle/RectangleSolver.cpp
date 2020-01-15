#include "RectangleAppData.h"

#include <ctime>
#include <sys/time.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

namespace ai {
  namespace rectangle {

    // forward declaration
    void process_input_stream_aux( AppData& data );
    
    /*********************************************
     * Commands
     */
    // send a message to the output stream
    int echo( AppData& data ) {
      unsigned int i;
      bool first = true;
      for( i = 1; i < data.words.size( ); i++ ) {
        if( !first ) {
          data.os << " ";
        }
        data.os << data.words[ i ];
        first = false;
      }
      data.os << std::endl;
      return EXIT_OK;
    }

    int config( AppData& data ) {
      if( data.words.size( ) < 3 ) {
        return EXIT_USAGE;
      }
      if( !data.config.updateOption( data.words[ 1 ], data.words[ 2 ] ) ) {
        data.os << "Unknown configuration option: " << data.words[ 1 ] << std::endl;
        data.os << "Known options: " << data.config.listOptions( ) << std::endl;
        return EXIT_USAGE_HELP;
      } else {
        if( data.words[ 1 ] == "rectangle_width" 
            || data.words[ 1 ] == "rectangle_height"  ) {
          data.model.Reset( data.config.rectangleWidth( ), data.config.rectangleHeight( ) );
        }
        if( data.words[ 1 ] == "flood_fill" ) {
          data.model.SetUseFloodFill( data.config.floodFill( ) );
        }
      }
      return EXIT_OK;
    }

    int show_model( AppData& data, const Model& model, bool show_endl=true ) {
      data.os << model.DisplayString( );
      if( show_endl ) {
        data.os << std::endl;
      }
      return EXIT_OK;
    }

    int show_move( AppData& data, const std::string& name, const Move& move ) {
      data.os << move.DisplayString( );
      return EXIT_OK;
    }
    
    int show( AppData& data ) {
      if( data.words.size( ) < 2 ) {
        return EXIT_USAGE;
      } else if( data.words[ 1 ] == "config" ) {
        data.os << "Configuration" << std::endl;
        data.config.showConfiguration( data.os );
        return EXIT_OK;
      } else if( data.words[ 1 ] == "model" ) {
        data.os << "Model: " << std::endl;
        return show_model( data, data.model );
      }
      return EXIT_USAGE_HELP;
    }

    int init_model( AppData& data, Model& model, unsigned int first_word, unsigned int last_word ) {
      std::stringstream ss;
      unsigned int i;
      for( i = first_word; i < last_word; i++ ) {
        ss << data.words[ i ];
      }
      if( ss.str( ) == "empty" ) {
        model.Reset( data.config.rectangleWidth( ), data.config.rectangleHeight( ) );
      } else {
        data.os << "Unexpected initialization request." << std::endl;
        return EXIT_USAGE_HELP;
      }
      return EXIT_OK;
    }

    int init( AppData& data ) {
      if( data.words.size( ) < 3 ) {
        return EXIT_USAGE;
      } else if( data.words[ 1 ] == "model" ) {
        int r = init_model( data, data.model, 2, data.words.size( ) );
        if( r != EXIT_OK ) {
          return r;
        }
        return r;
      }
      return EXIT_USAGE_HELP;
    }

    int place( AppData& data ) {
      if( data.words.size( ) < 2 ) {
        return EXIT_USAGE;
      } else {
        unsigned int i;
        for( i = 1; i < data.words.size( ); i++ ) {
          std::stringstream ss( data.words[ i ] );
          char piece, at, comma, colon1, colon2;
          int x, y, rotation, flip;
          x = -100;
          y = -100;
          ss >> piece >> at >> x >> comma >> y >> colon1 >> rotation >> colon2 >> flip;
          if( ss 
              && piece >= 'a' && piece <= 'l' 
              && at == '@'
              && x >= 0 && x < data.model.GetWidth( )
              && comma == ','
              && y >= 0 && y < data.model.GetHeight( )
              && colon1 == ':'
              && rotation >= 0 && rotation < 4
              && colon2 == ':'
              && flip >= 0 && flip < 2 ) {
            Move move( piece - 'a', rotation, flip, x, y );
            if( !data.model.ApplyMove( move ) ) {
              data.os << "Can not place " << data.words[ 1 ] << std::endl;
              data.model.ClearPiece( piece - 'a' );
            }
          } else {
            data.os << "Unexpected piece placement format: " << data.words[ i ] << std::endl;
            return EXIT_USAGE_HELP;
          }
        }

        return EXIT_OK;
      }
      return EXIT_USAGE_HELP;
    }

    int clear( AppData& data ) {
      if( data.words.size( ) < 2 ) {
        return EXIT_USAGE;
      } else {
        unsigned int i, j;
        for( i = 1; i < data.words.size( ); i++ ) {
          for( j = 0; j < data.words[i].size( ); j++ ) {
            if( data.words[ i ][ j ] >= 'a'
                && data.words[ i ][ j ] <= 'l' ) {
              unsigned int which_piece = data.words[ i ][ j ] - 'a';
              if( !data.model.ClearPiece( which_piece ) ) {
                data.os << "Can not clear '" << data.words[ i ][ j ] << "'." << std::endl;
              }
            } else {
              data.os << "Can not clear '" << data.words[ i ][ j ] << "'.  Not a valid piece." << std::endl;
              break;
            }
          } // j
        } // i
        return EXIT_OK;
      }
      return EXIT_USAGE_HELP;
    }

    int exit_if( AppData& data ) {
      if( data.words.size( ) < 2 ) {
        return EXIT_USAGE;
      } else if( data.words[ 1 ] == "not_solved" ) {
        if( !data.model.IsSolved( ) ) {
          return EXIT_EXIT;
        }
      } else if( data.words[ 1 ] == "solved" ) {
        if( data.model.IsSolved( ) ) {
          return EXIT_EXIT;
        }
      } else {
        data.os << "Unexpected exit_if option: " << data.words[ 1 ] << std::endl;
        return EXIT_USAGE_HELP;
      }
      
      return EXIT_OK;
    }

    unsigned int next_word_length( const std::string& help, const unsigned int i ) {
      unsigned int j;
      for( j = i; j < help.size( ); j++ ) {
        if( help[ j ] == ' ' || help[ j ] == '\t' || help[ j ] == '\n' ) {
          break;
        }
      }
      return j - i;
    }

    void show_help( std::ostream& os, AppData& data, unsigned int offset, const std::string& help ) {
      unsigned int screen_width = 60;
      unsigned int indent = 5;
      unsigned int length;
      if( offset >= screen_width ) {
        offset = screen_width;
      }
      if( offset == 0 ) {
        offset = screen_width+1;
      }
      unsigned int line_length = offset;
      
      unsigned int i, j;
      for( i = 0; i < help.size( ); i++ ) {
        length = next_word_length( help, i );
        if( line_length + length > screen_width ) {
          os << std::endl;
          for( j = 0; j < indent; j++ ) {
            os << " ";
          }
          line_length = indent;
        }
        for( ; i < help.size( ) && length > 0; i++, length--, line_length++ ) {
          os << help[ i ];
        }
        if( i < help.size( ) ) {
          os << help[ i ];
          line_length++;
        }
      }
    }

    int help( AppData& data ) {
      if( data.words.size( ) == 1 ) {
        for( auto it = data.actions.begin( ); it != data.actions.end( ); it++ ) {
          data.os << it->second.usage << " :: ";
          show_help( data.os, data, 0, it->second.help );
          data.os << std::endl;
        }
      } else if( data.words.size( ) == 2 ) {
        const std::string& command = data.words[ 1 ];
        if( data.actions.count( command ) > 0 ) {
          data.os << data.actions.at( command ).usage << " :: ";
          show_help( data.os, data, 0, data.actions.at( command ).help );
          data.os << std::endl;
        } else {
          data.os << "Unknown command: '" << command << "'. No help available." << std::endl;
          return EXIT_USAGE_HELP;
        }
      } else {
        return EXIT_USAGE;
      }
      return EXIT_OK;
    }

    int run( AppData& data ) {
      int exit_status = EXIT_OK;

      bool old_prompt = data.config.prompt( );
      data.config.disablePrompt( );

      if( data.words.size( ) < 2 ) {
        return EXIT_USAGE;
      }
      std::stringstream ss( data.words[ 1 ] );
      std::string filename;
      ss >> filename;

      std::ifstream fin( filename );
      if( !fin ) {
        data.os << "Unable to open the file '" << filename << "'." << std::endl;
        exit_status = EXIT_USAGE;
      } else {
        AppData tmp_data( fin, data.os );
        tmp_data.config = data.config;
        tmp_data.model = data.model;
        tmp_data.actions = data.actions;

        process_input_stream_aux( tmp_data );
        fin.close( );

        data.config = tmp_data.config;
        data.model = tmp_data.model;
      }

      if( old_prompt ) {
        data.config.enablePrompt( );
      } else {
        data.config.disablePrompt( );
      }
      return exit_status;
    }

    void makeActionMap( AppData& data ) {
      data.actions.clear( );
      data.actions[ "echo" ] = { echo, "echo", "echo word*", "Displays the words of its line separated by a single space." };
      data.actions[ "config" ] =  { config, "config", "config option value", "Sets the option to value.  Only predefined options are allowed.  All values are interpreted as floating point." };
      data.actions[ "init" ] =  { init, "init", "init model empty", "Assigns the current state of the working model to have no pieces placed." };

      data.actions[ "place" ] =  { place, "place", "place ([a-l]@x,y:r:f)+", "Places the pieces as directed. Select the piece with a lower case letter a through l. Select the x,y coordinate of the piece origin, which is shown the model display by an upper case letter. Select the rotation number (0-3) and the flip number (0-1).  Multiple placements may be given on one line, separated by whitespace." };
      data.actions[ "clear" ] =  { clear, "clear", "clear [a-l]+", "Removes the pieces listed from the board. Select the piece with a lower case letter a through l.  Multiple pieces may be given on one line, separated by whitespace." };

      data.actions[ "search" ] =  { search, "search", "search tree|graph astar|bfs|dfs|dl|ids|al|greedy|uc", "Searches for a path from the current model to a solved model. Uses the search algorithm and frontier specified. dl requires the depth_limit configuration. ids requires the ids_limit configuration. al requires the astar_limit configuration.  All algorithms and frontiers require the generation_limit and storage_limit configurations.  The flood_fill configuration is used to decide whether to apply restrictions to the legal moves based on empty areas having size that is a multiple of 5." };
      data.actions[ "show" ]   = { show, "show", "show config|model", "Displays the requested item." };
      data.actions[ "help" ] = { help, "help", "help command?", "Displays a list of commands.  If a command is given, only help on that command is displayed." };
      data.actions[ "run" ] = { run, "run", "run filename", "Runs the commands in filename as if they were typed.  Turns off the prompt while reading the file." };
      data.actions[ "exit_if" ] = { exit_if, "exit_if", "exit_if not_solved|solved", "Stops execution if the condition holds." };
    }
    /*
     * Commands
     *********************************************/
    
    /*********************************************
     * Input processing
     */
    /* Read until newline character or end of file
     * If the last character of the line (except for the newline) is \, then remove the \ and read the next line.
     * Store whitespace separated words in output vector
     * return true if something was read, false if any error occurred, including read after EOF was reached
     */
    bool read_one_line( std::istream& is, std::vector< std::string >& words ) {
      words.clear( );

      bool done = false;
      while( !done ) {

        std::string line;
        std::getline( is, line );
        if ( ! is ) { 
          return false;
        }
  
        std::stringstream ss( line );
        std::string word;
        while ( ss >> word ) {
          words.push_back( word );
        }
        
        if( words.size( ) > 0 && words[ words.size( ) - 1 ] == "\\" ) {
          words.pop_back( );
          done = false;
        } else {
          done = true;
        }
      }

      return true;
    }

    void process_input_stream_aux( AppData& data ) {
      
      if( data.config.prompt( ) ) {
        data.os << "rectangle> " << std::flush;
      }
      while( ( !data.done ) && read_one_line( data.is, data.words ) ) {
        if ( data.words.size( ) == 0 ) {
          // empty (whitespace only) lines
          continue;
        } else if ( data.words[ 0 ].size( ) == 0 ) {
          // first word is empty, how does this happen?
          continue;
        } else if ( data.words[ 0 ][ 0 ] == '#' ) {
          // comment lines begin with # as first non-whitespace character
          continue;
        } else if ( data.actions.count( data.words[ 0 ] ) > 0 ) {
          int exit_status = data.actions.at( data.words[ 0 ] ).action( data );
          switch( exit_status ) {
          case EXIT_OK:
            // empty
            break;
          case EXIT_USAGE:
            data.os << "usage: " << data.actions.at( data.words[ 0 ] ).usage << std::endl;
            break;
          case EXIT_HELP:
            data.os << "help: " << data.words[ 0 ] << " :: ";
            show_help( data.os, data, 0, data.actions.at( data.words[ 0 ] ).help );
            data.os << std::endl;
            break;
          case EXIT_USAGE_HELP:
            data.os << "usage: " << data.actions.at( data.words[ 0 ] ).usage << std::endl;
            data.os << "help: " << data.words[ 0 ] << " :: ";
            show_help( data.os, data, 0, data.actions.at( data.words[ 0 ] ).help );
            data.os << std::endl;
            break;
          case EXIT_EXIT:
            data.os << "Early termination of program." << std::endl;
            data.done = true;
            break;
          case EXIT_THROW: 
            {
              std::stringstream ss;
              ss << "Error in command: '" << data.words[ 0 ] << "'.  Exit status " << exit_status << "." << std::endl;
              ss << "usage: " << data.actions.at( data.words[ 0 ] ).usage << std::endl;
              ss << "help: " << data.actions.at( data.words[ 0 ] ).help << std::endl;
              ss << "help: " << data.words[ 0 ] << " :: ";
              show_help( ss, data, 0, data.actions.at( data.words[ 0 ] ).help );
              ss << std::endl;
              
              throw Exception( ss.str( ) );
            }
            break;
          default:
            {
              std::stringstream ss;
              ss << "Unexpected exit status: " << exit_status << std::endl;
              ss << "Error in command: '" << data.words[ 0 ] << "'.  Exit status " << exit_status << "." << std::endl;
              ss << "usage: " << data.actions.at( data.words[ 0 ] ).usage << std::endl;
              ss << "help: " << data.actions.at( data.words[ 0 ] ).help << std::endl;
              throw Exception( ss.str( ) );
            }
            break;
          }
        } else {
          data.os << std::endl;
          data.os << "Unexpected command: '" << data.words[ 0 ] << "'" << std::endl;
          data.os << "The help command will list all available commands." << std::endl;
          data.os << std::endl;
        }
        if( data.config.prompt( ) ) {
          data.os << "rectangle> ";
        }
        data.os << std::flush;
      }
    }


    // "main" program control
    void process_input_stream( std::istream& is, std::ostream& os ) {
      /* srand seeds at 100 usecond resolution */
      struct timeval time;
      gettimeofday(&time,NULL);
      srand((time.tv_sec * 10000) + (time.tv_usec / 100));
      
      AppData data( is, os );
      makeActionMap( data );

      process_input_stream_aux( data );
    }
    /*
     * Input processing
     *********************************************/


  }
}


int main( ) {
  ai::rectangle::process_input_stream( std::cin, std::cout );
  return 0;
}
