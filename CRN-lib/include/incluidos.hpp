#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <fstream>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>


#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/find_iterator.hpp>
#include <boost/algorithm/string/iter_find.hpp>
#include <boost/algorithm/string/classification.hpp> 


#ifndef GET_MASS_ACTION_LAW_EQUATIONS
  #define GET_MASS_ACTION_LAW_EQUATIONS
  #include "getMassActionLawEquations.hpp"
#endif

#ifndef GET_SIMPLE_REACTIONS
  #define GET_SIMPLE_REACTIONS
  #include "getSimpleReactions.hpp"
#endif

#ifndef GET_SPECIES_MAP
  #define GET_SPECIES_MAP
  #include "getSpeciesMap.hpp"
#endif

#ifndef GET_REACTION_MATRIX
  #define GET_REACTION_MATRIX
  #include "getReactionMatrix.hpp"
#endif

#ifndef GET_REACTION_VECTOR
  #define GET_REACTION_VECTOR
  #include "getReactantsVector.hpp"
#endif

#ifndef GET_PRODUCTS_VECTOR
  #define GET_PRODUCTS_VECTOR
  #include "getProductsVector.hpp"
#endif

#ifndef OVERLOADED_VECTOR
  #define OVERLOADED_VECTOR
  #include "overloadedVector.hpp"
#endif

#ifndef OVERLOADED_MATRIX
  #define OVERLOADED_MATRIX
  #include "overloadedMatrix.hpp"
#endif

#ifndef UN_STOICHEM
  #define UN_STOICHEM
  #include "unStoichem.hpp"
#endif

#ifndef NUMBER_TO_STRING
  #define NUMBER_TO_STRING
  #include "numberToString.hpp"
#endif
