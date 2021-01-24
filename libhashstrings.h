//
// Created by paul on 1/23/21.
//

#ifndef HASHSTRINGS_LIBHASHSTRINGS_H
#define HASHSTRINGS_LIBHASHSTRINGS_H

#include <inttypes.h>

typedef void           tNode;
typedef unsigned short tIndex;
typedef uint64_t       tHash;

typedef uint64_t       tCharMap;
typedef unsigned short tMappedChar;

typedef struct
{
    tHash hash;
    const char * hashedString;
    const char * name;
    tIndex lower, higher;

    unsigned int level;
    char         hand;
} tRecord;


extern tMappedChar remapChar( tCharMap * charMap,
                              const unsigned char c );

extern void setCharMap( tCharMap * charMap,
                        const unsigned char c,
                        const tMappedChar mappedC );

extern tMappedChar remapChar( tCharMap * charMap,
                              const unsigned char c );

extern tHash hashChar( tHash hash,
                       const tMappedChar mappedC );

extern tRecord * findHash( tRecord ** skipTable, tHash hash );


#endif //HASHSTRINGS_LIBHASHSTRINGS_H
