// Compile:
//     cl /Zi /Fo decode.c
// Link:
//     link /fixed /debug decode.obj

#include "hack.h"
#include "XP3Archive.h"
#include "DebugIntf.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <crtdbg.h>
#include <windows.h>


// Type Definitions
//
static_assert(sizeof(tTVPXP3ExtractionFilterInfo) == 24, "");



// types from reversing on cxdec.tpm
typedef int (*tDecodeL1)(tTVPXP3ExtractionFilterInfo *decodeInfo);

struct FunctionPoolEntry {
    char text[128];  // executable code
};

struct FunctionPool {
    FunctionPoolEntry functions[123];
};

struct DecodeFunctions {
    FunctionPool *function_pool;
    void *functions[128];
    int counter;
    int function_indices[100];
    struct _RTL_CRITICAL_SECTION critical_section;
};
static_assert(sizeof(DecodeFunctions) == 0x3b0, "");  // note struct alignment
// end types from reversing on cxdec.tpm



// Global Variables
//
char gBuffer[0x10000];
DecodeFunctions **pDecodeFunctions = (DecodeFunctions **) 0x1E019B8C;
tDecodeL1 DecodeL1 = (tDecodeL1) 0x1e001e80;


// Functions
//
// Decompiled from 1E001000@cxdec.tpm
DecodeFunctions *DecodeFunctions_init(DecodeFunctions *v1)
{
    FunctionPool *v2;

    InitializeCriticalSection(&v1->critical_section);
    v2 = (FunctionPool *) VirtualAlloc(0, 0x3200u, 0x1000u, 0x40u);
    v1->function_pool = v2;
    if (!v2) {
        while (1)
            ;
    }
    memset(v1->functions, 0, sizeof(v1->functions));
    memset(v1->function_indices, 0xFFu, sizeof(v1->function_indices));
    v1->counter = 0;
    return v1;
}


int main(int argc, char **argv)
{
    int ret = 0;

    if (argc <= 1) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return -1;
    }
    const char* filename = argv[1];

    HMODULE hCxdec = LoadLibraryA("cxdec.tpm.patched");
    if (!hCxdec) {
        fprintf(stderr, "Load cxdec.tpm failed\n");
        return -1;
    }

    // TVPSetLogLocation("hack.log");
    // TVPStartLogToFile(true);

    // tTVPXP3Archive xp3(filename);

    // int filehash;
    // sscanf(argv[2], "%x", &filehash);

    // FILE *f = fopen(argv[1], "rb");
    // if (!f) {
    //     fprintf(stderr, "File open failed\n");
    //     return -1;
    // }
    // int sz_done = 0;
    // int sz_read;
    // while ((sz_read = fread(gBuffer, 1, 0x10000, f)) > 0) {
    //     sz_done += sz_read;
    // }
    // printf("size_done=0x%x\n", sz_done);
    // fclose(f);
    // f = NULL;

    // *pDecodeFunctions = new DecodeFunctions;
    // if (*pDecodeFunctions) {
    //     DecodeFunctions_init(*pDecodeFunctions);

    //     tTVPXP3ExtractionFilterInfo info(0, gBuffer, sz_done, filehash);
    //     DecodeL1(&info);
    //     fwrite(gBuffer, 1, sz_done, stdout);
    // }

    FreeLibrary(hCxdec);

    return ret;
}
