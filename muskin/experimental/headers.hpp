/* Including external libraries */
#include "stl_includes.hpp"
#include "libboost_includes.hpp"

#ifndef OMP_H
	#include <omp.h>
	#define OMP_H
#endif

/* My headers
 * They are hierarchically ordered so the bottom includes depend on the ones defined above them
 * */

#ifndef NUMBERSTRINGS_H
	#include "numberStrings.hpp"
	#define NUMBERSTRINGS_H
#endif

#ifndef TYPES_H
	#include "typedef.hpp"
	#define TYPES_H
#endif

#ifndef INDEX_H
	#include "index_t.hpp"
	#define INDEX_H
#endif

#ifndef POINT_H
	#include "point_t.hpp"
	#define POINT_H
#endif

#ifndef PARSERPRTREE_H
#include "parserPrTree.hpp"
#define PARSERPRTREE_H
#endif

#ifndef MATHGLDRAW_H
	#include "mglDrawData.hpp"
	#include<mgl2/mgl.h>
#define MATHGLDRAW_H
#endif

#ifndef CHEM_T_H
	#include "chem_t.hpp"
	#define CHEM_T_H
#endif

#ifndef VOXEL_H
	#include "voxel_t.hpp"
	#define VOXEL_H
#endif

#ifndef NODE_H
	#include "node.hpp"
	#define NODE_H
#endif

#ifndef MESH_H
	#include "mesh.hpp"
	#define MESH_H
#endif
