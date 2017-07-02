#ifndef BSPTYPES_H
#define BSPTYPES_H

typedef unsigned char byte;

////////////////////////////////////////////////////////////
// Maximum Lumpcount definitions
////////////////////////////////////////////////////////////
#define	MAX_MAP_HULLS		4

#define	MAX_MAP_MODELS		400
#define	MAX_MAP_BRUSHES		4096
#define	MAX_MAP_ENTITIES	1024
#define	MAX_MAP_ENTSTRING	(128*1024)

#define	MAX_MAP_PLANES		32767
#define	MAX_MAP_NODES		32767		// because negative shorts are contents
#define	MAX_MAP_CLIPNODES	32767
#define	MAX_MAP_LEAFS		8192
#define	MAX_MAP_VERTS		65535
#define	MAX_MAP_FACES		65535
#define	MAX_MAP_MARKSURFACES 65535
#define	MAX_MAP_TEXINFO		8192
#define	MAX_MAP_EDGES		256000
#define	MAX_MAP_SURFEDGES	512000
#define	MAX_MAP_TEXTURES	512
#define	MAX_MAP_MIPTEX		0x200000
#define	MAX_MAP_LIGHTING	0x200000
#define	MAX_MAP_VISIBILITY	0x200000

#define	MAX_MAP_PORTALS		65536

#define	MIPLEVELS		4
#define	MAXLIGHTMAPS	4
#define	NUM_AMBIENTS	4
#define	TEX_SPECIAL		1


////////////////////////////////////////////////////////////
// Plane type definitions
// 0-2 are axial planes
// 3-5 are non-axial planes snapped to the nearest
////////////////////////////////////////////////////////////
#define	PLANE_X			0
#define	PLANE_Y			1
#define	PLANE_Z			2

#define	PLANE_ANYX		3
#define	PLANE_ANYY		4
#define	PLANE_ANYZ		5

////////////////////////////////////////////////////////////
// Content type definitions
////////////////////////////////////////////////////////////
#define	CONTENTS_EMPTY		-1
#define	CONTENTS_SOLID		-2
#define	CONTENTS_WATER		-3
#define	CONTENTS_SLIME		-4
#define	CONTENTS_LAVA		-5
#define	CONTENTS_SKY		-6
#define	CONTENTS_ORIGIN		-7		// removed at csg time
#define	CONTENTS_CLIP		-8		// changed to contents_solid

#define	CONTENTS_CURRENT_0		-9
#define	CONTENTS_CURRENT_90		-10
#define	CONTENTS_CURRENT_180	-11
#define	CONTENTS_CURRENT_270	-12
#define	CONTENTS_CURRENT_UP		-13
#define	CONTENTS_CURRENT_DOWN	-14

#define CONTENTS_TRANSLUCENT	-15

////////////////////////////////////////////////////////////
// Texture type definitions
////////////////////////////////////////////////////////////
#define	AMBIENT_WATER	0
#define	AMBIENT_SKY		1
#define	AMBIENT_SLIME	2
#define	AMBIENT_LAVA	3

////////////////////////////////////////////////////////////
// BSP content specification
////////////////////////////////////////////////////////////
typedef struct
{
	float		mins[3], maxs[3];
	float		origin[3];
	int			headnode[MAX_MAP_HULLS];
	int			visleafs;		// not including the solid leaf 0
	int			firstface, numfaces;
} tModel;

typedef struct
{
	float	point[3];
} tVertex;

typedef struct
{
	float	normal[3];
	float	dist;
	int		type;
} tPlane;

typedef struct
{
	int			planenum;
	short		children[2];	// negative numbers are -(leafs+1), not nodes
	short		mins[3];		// for sphere culling
	short		maxs[3];
	unsigned short	firstface;
	unsigned short	numfaces;	// counting both sides
} tNode;

typedef struct
{
	int			planenum;
	short		children[2];	// negative numbers are contents
} tClipnode;

typedef struct
{
	float		vecs[2][4];		// [s/t][xyz offset]
	int			miptex;
	int			flags;
} tTexinfo;

typedef struct
{
	unsigned short	v[2];		// vertex numbers
} tEdge;

typedef struct
{
	short		planenum;
	short		side;

	int			firstedge;		// we must support > 64k edges
	short		numedges;	
	short		texinfo;

// lighting info
	byte		styles[MAXLIGHTMAPS];
	int			lightofs;		// start of [numstyles*surfsize] samples
} tFace;

typedef struct
{
	int			contents;
	int			visofs;				// -1 = no visibility info

	short		mins[3];			// for frustum culling
	short		maxs[3];

	unsigned short		firstmarksurface;
	unsigned short		nummarksurfaces;

	byte		ambient_level[NUM_AMBIENTS];
} tLeaf;

#include "../WAD/wadtypes.h"
#endif
