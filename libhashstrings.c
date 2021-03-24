//
// Created by paul on 1/23/21.
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include "libhashstrings.h"

const uint64_t kFieldMask = 0x01FFL; // mask for the 9 lsb
static const int kHashFactor = 43;

void setCharMap( tCharMap * charMap,
                 const unsigned char c,
                 const tMappedChar mappedC )
{
    unsigned short shft = (c % 7) * 9;
    charMap[ c/7 ] = (charMap[ c/7 ] & ~(kFieldMask << shft)) |
                      ((mappedC & kFieldMask) << shft);
}

tMappedChar remapChar( tCharMap * charMap, const unsigned char c )
{
    return ((charMap[ c/7 ] >> (( c % 7 ) * 9)) & kFieldMask);
}

tHash hashChar( tHash hash, tMappedChar mappedC )
{
    return (hash ^ ((hash * kHashFactor) + mappedC));
}

tIndex findHash( tRecord skipTable[], tHash hash )
{
    tIndex i = 0;

    do {
        // fprintf(stderr, "%02d-0x%016lx ", i, skipTable[i].hash);

        if ( skipTable[i].hash == hash )
        { // we found it, return the corresponding tIndex (1-based)
            // fprintf( stderr, "match (%s)\n", skipTable[i].hashedString );
            return skipTable[i].index;
        }
        else if ( skipTable[i].hash > hash )
        { /* hash is lower than this record */
            i = skipTable[i].lower;
            // fprintf( stderr, "lower (%u)\n", i );
        }
        else
        { /* hash is higher than this record */
            i = skipTable[i].higher;
            // fprintf( stderr, "higher (%u)\n", i );
        }
    } while ( i != kLeaf );

    // fprintf( stderr, "no match\n" );
    return 0;
}

void dumpHashMap( FILE * out, tRecord skipTable[] )
{
    unsigned int max = 1;
    for ( unsigned int i = 0; i < max; i++)
    {
        if (max < skipTable[i].higher)
        {
            max = skipTable[i].higher;
        }
        fprintf( out, "%d: 0x%016lx,\"%s\",%d,%d,%d\n",
                 i, skipTable[i].hash, skipTable[i].hashedString,
                 skipTable[i].index, skipTable[i].higher, skipTable[i].lower);
    }
}