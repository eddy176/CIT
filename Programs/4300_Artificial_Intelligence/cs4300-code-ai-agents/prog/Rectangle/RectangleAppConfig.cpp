#include "RectangleAppConfig.h"
#include <sstream>

namespace ai {
  namespace rectangle {

    AppConfig::AppConfig( ) {
      /* Initialize configuration parameters */
      enablePrompt( );
      setRectangleWidth( 10 );
      setRectangleHeight( 6 );
      disableFloodFill( );
      setDepthLimit( 5 );
      setIDSDepth( 0 );
      setIDSLimit( 5 );
      setAStarLimit( 10.0 );
      setGenerationLimit( 1e6 );
      setStorageLimit( 1e6 );
      disableApplySolution( );
      setDisplaySolutionHuman( );
    }

    bool AppConfig::updateOption( const std::string& option, const std::string& value ) {
      if( mOptions.count( option ) > 0 ) {
        std::stringstream ss( value );
        double number;
        ss >> number;
        mOptions[ option ] = number;
        return true;
      } else {
        return false;
      }
    }

    std::string AppConfig::listOptions( ) const {
      std::stringstream ss;
      bool first = true;
      for( auto it = mOptions.begin( ); it != mOptions.end( ); it++ ) {
        if( !first ) {
          ss << " ";
        }
        ss << it->first;
        first = false;
      }
      return ss.str( );
    }

    void AppConfig::showConfiguration( std::ostream& os ) const {
      for( auto it = mOptions.begin( ); it != mOptions.end( ); it++ ) {
        os << it->first << " " << it->second << std::endl;
      }
    }

    // show a prompt for the user
    void AppConfig::enablePrompt( ) {
      mOptions[ "enable_prompt" ] = 1;
    }
    void AppConfig::disablePrompt( ) {
      mOptions[ "enable_prompt" ] = 0;
    }
    bool AppConfig::prompt( ) const {
      return static_cast< int >( mOptions.at( "enable_prompt" ) ) != 0;
    }
    
    // desired rectangle dimensions
    int AppConfig::rectangleWidth( ) const {
      return static_cast< int >( mOptions.at( "rectangle_width" ) );
    }
    void AppConfig::setRectangleWidth( const int width ) {
      mOptions[ "rectangle_width" ] = width;
    }
    int AppConfig::rectangleHeight( ) const {
      return static_cast< int >( mOptions.at( "rectangle_height" ) );
    }
    void AppConfig::setRectangleHeight( const int height ) {
      mOptions[ "rectangle_height" ] = height;
    }

    // whether to use the flood fill restriction
    void AppConfig::enableFloodFill( ) {
      mOptions[ "flood_fill" ] = 1;
    }
    void AppConfig::disableFloodFill( ) {
      mOptions[ "flood_fill" ] = 0;
    }
    bool AppConfig::floodFill( ) const {
      return static_cast< int >( mOptions.at( "flood_fill" ) ) != 0;
    }

    // search options
    int AppConfig::depthLimit( ) const {
      return static_cast< int >( mOptions.at( "depth_limit" ) );
    }
    void AppConfig::setDepthLimit( const int limit ) {
      mOptions[ "depth_limit" ] = limit;
    }
    int AppConfig::idsDepth( ) const {
      return static_cast< int >( mOptions.at( "ids_depth" ) );
    }
    void AppConfig::setIDSDepth( const int depth ) {
      mOptions[ "ids_depth" ] = depth;
    }
    int AppConfig::idsLimit( ) const {
      return static_cast< int >( mOptions.at( "ids_limit" ) );
    }
    void AppConfig::setIDSLimit( const int limit ) {
      mOptions[ "ids_limit" ] = limit;
    }
    double AppConfig::aStarLimit( ) const {
      return mOptions.at( "astar_limit" );
    }
    void AppConfig::setAStarLimit( const double limit ) {
      mOptions[ "astar_limit" ] = limit;
    }
    double AppConfig::generationLimit( ) const {
      return mOptions.at( "generation_limit" );
    }
    void AppConfig::setGenerationLimit( const double limit ) {
      mOptions[ "generation_limit" ] = limit;
    }
    double AppConfig::storageLimit( ) const {
      return mOptions.at( "storage_limit" );
    }
    void AppConfig::setStorageLimit( const double limit ) {
      mOptions[ "storage_limit" ] = limit;
    }
    void AppConfig::enableApplySolution( ) {
      mOptions[ "apply_solution" ] = 1;
    }
    void AppConfig::disableApplySolution( ) {
      mOptions[ "apply_solution" ] = 0;
    }
    bool AppConfig::applySolution( ) const {
      return static_cast< int >( mOptions.at( "apply_solution" ) ) != 0;
    }

    // how to display search results
    void AppConfig::setDisplaySolutionHuman( ) {
      mOptions[ "solution_display" ] = 0;
    }
    void AppConfig::setDisplaySolutionMachine( ) {
      mOptions[ "solution_display" ] = 1;
    }
    bool AppConfig::displaySolutionHuman( ) const {
      return static_cast< int >( mOptions.at( "solution_display" ) ) == 0;
    }
    bool AppConfig::displaySolutionMachine( ) const {
      return static_cast< int >( mOptions.at( "solution_display" ) ) == 1;
    }

  }
}
