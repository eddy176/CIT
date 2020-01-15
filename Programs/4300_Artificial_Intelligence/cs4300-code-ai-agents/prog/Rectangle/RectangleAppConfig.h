#ifndef _RECTANGLEAPPCONFIG_H_
#define _RECTANGLEAPPCONFIG_H_

#include <string>
#include <iostream>
#include <map>

namespace ai {
  namespace rectangle {

    class AppConfig {
    public:
      AppConfig( );
      bool updateOption( const std::string& option, const std::string& value );
      std::string listOptions( ) const;
      void showConfiguration( std::ostream& os ) const;
      
      // show a prompt for the user
      void enablePrompt( );
      void disablePrompt( );
      bool prompt( ) const;

      // desired rectangle dimensions
      int rectangleWidth( ) const;
      void setRectangleWidth( const int width );
      int rectangleHeight( ) const;
      void setRectangleHeight( const int height );

      // whether to use the flood fill restriction
      void enableFloodFill( );
      void disableFloodFill( );
      bool floodFill( ) const;

      // search options
      int depthLimit( ) const;
      void setDepthLimit( const int limit );
      int idsDepth( ) const;
      void setIDSDepth( const int depth );
      int idsLimit( ) const;
      void setIDSLimit( const int limit );
      double aStarLimit( ) const;
      void setAStarLimit( const double limit );
      double generationLimit( ) const;
      void setGenerationLimit( const double limit );
      double storageLimit( ) const;
      void setStorageLimit( const double limit );

      void enableApplySolution( );
      void disableApplySolution( );
      bool applySolution( ) const;

      // how to display search results
      void setDisplaySolutionHuman( );
      void setDisplaySolutionMachine( );
      bool displaySolutionHuman( ) const;
      bool displaySolutionMachine( ) const;

    protected:
      std::map< std::string, double > mOptions;

    private:
    };

  }
}


#endif /* _RECTANGLEAPPCONFIG_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
