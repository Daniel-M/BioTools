/* Type definitions and #define statements to be used through the libraries.
 */

/* These #define statements are used when parsing the JSON or XML on the libparser methods*/
#define _pMesh "mesh"
#define _pMeshName "name"
#define _pMeshXML "xml"
#define _pMeshJSON "json"
#define _pMeshFile "meshfile"
#define _pMeshDim "dimension"
#define _pMeshNN "numberofnodes"
#define _pMeshBN "bnodes"
#define _pMeshIN "inodes"
#define _pMeshDD "deltaondim"
#define _pMeshND "nodesondim"
#define _pMeshPA "pointa"
#define _pMeshPB "pointb"
#define _pCoord "x"

/* Type Definitions that can be changed in order to assure a better compatibility*/
typedef int	int_t;

typedef std::vector<double> point_t;

typedef std::vector<int_t> index_t;

/*! On the header chem_t.hpp the typedef:
 * typedef std::vector<chem_t> chem_vector_t;
 * was declared after the statement of the chem_t class.
 * This was done to prevent malfunction during compilation.*/

/*! This typedef creates the type system_t, a pointer to a function of the form 
 * void function(const point_t&, point_t&, const double)
 * the ODE system stored on the voxel_t as needed by the libboost::odeint.
 * This allows to use one single class with many different ODE systems for each voxel_t object. */
typedef void (*system_t)( const point_t&, point_t& , const double /* t */ ); /*!< A Pointer to libboost formated ODE systems. */
