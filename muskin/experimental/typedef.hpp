/* Type definitions and #define statements to be used through the libraries.
 */

/* These #define statements are used when parsing the JSON or XML*/
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

typedef std::vector<int_t> index_t;

typedef std::vector<double> point_t;

typedef void (*system_t)( const point_t&, point_t& , const double /* t */ ); /*!< A Pointer to libboost formated ODE systems. */
