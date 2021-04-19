//
// Created by paul on 1/23/21.
//

#ifndef HASHSTRINGS_LIBHASHSTRINGS_H
#define HASHSTRINGS_LIBHASHSTRINGS_H

#include <inttypes.h>

typedef void           tNode;
typedef uint32_t       tIndex;
typedef uint64_t       tHash;

typedef uint64_t       tCharMap;
typedef unsigned short tMappedChar;

#define kLeaf   0

/* don't need name - use lookup<prefix>asString[index] instead
 * otherwise the 'name' strings may be duplicated */
typedef struct {
    tHash        hash;
    const char * hashedString;
    tIndex       index;
    tIndex       lower, higher;
} tRecord;


extern tMappedChar remapChar( tCharMap * charMap,
                              const unsigned char c );

extern tHash hashChar( tHash hash,
                       const tMappedChar mappedC );

extern tHash hashString(const char * string, tCharMap * charMap );

extern tIndex findHash( tRecord skipTable[], tHash hash );

extern void setCharMap( tCharMap * charMap,
                        const unsigned char c,
                        const tMappedChar mappedC );

void dumpHashMap( FILE * out, tRecord skipTable[] );

#endif //HASHSTRINGS_LIBHASHSTRINGS_H
