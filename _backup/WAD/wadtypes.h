#ifndef WADTYPES_H
#define WADTYPES_H

#define	MIPLEVELS	4

typedef struct
{
	char		identification[4];		// should be WAD2 or 2DAW
	int			numlumps;
	int			infotableofs;
} tWadHeader;

typedef struct
{
	int			filepos;
	int			disksize;
	int			size;					// uncompressed
	char		type;
	char		compression;
	char		pad1, pad2;
	char		name[16];				// must be null terminated
} tWadLump;

typedef struct
{
	int			nummiptex;
	int			dataofs[4];		// [nummiptex]
} tMiptexlump;

typedef struct miptex_s
{
	char		name[16];
	unsigned	width, height;
	unsigned	offsets[MIPLEVELS];		// four mip maps stored
} tMiptex;
#endif