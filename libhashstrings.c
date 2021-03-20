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

tIndex findHash( tRecord ** skipTable, tHash hash )
{
    tIndex i = 0;

    do {
        if ( skipTable[i]->hash == hash )
        {
            return i;
        }
        else if ( skipTable[i]->hash > hash )
        { /* hash is lower */
            if ( skipTable[i]->lower != kLeaf )
            {
                i = skipTable[i]->lower;
            }
            else break;
        }
        else
        { /* hash is higher */
            if ( skipTable[i]->higher != kLeaf )
            {
                i = skipTable[i]->higher;
            }
            else break;
        }
    } while ( true );

    return UINT32_MAX;
}
