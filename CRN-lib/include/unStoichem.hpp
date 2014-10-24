//#include <string>
//#include <iomanip>
//#include <algorithm>
#include "incluidos.hpp"

/**\brief returns the stochoimetric coefficient of a chemical species on a given reaction
 *
 * When dealing with reaction as \a A + \a 2B -> \a 4C the numbers 2 and 4 are interpreted
 * as stoichometric numbers. They are identified and returned as integers by this function
 * 
 * \param sInput Input std::string to be searched for stoichometric coefficient.
 * \return integer corresponding to the stoichometric coefficient.
 */
int unStoichem(std::string& sInput)
{
  std::string sCoeff;
   
  if(isdigit ( sInput.at ( 0 ) ))
  {
    int i(0);
    
    while(isdigit ( sInput.at ( i ) ))
    {
      i++;
    }
    
    sCoeff=sInput.substr(0,i).c_str();
    sInput=sInput.substr(i,sInput.length());
    
    return atoi(sCoeff.c_str());    
  }
  else
  {
    sInput=sInput;
    return 1;
  }
}
