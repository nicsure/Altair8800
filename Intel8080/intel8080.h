#ifndef INTEL8080_H_
#define INTEL8080_H_

#include "pch.h"
#include "dllmain.h"

// Code by nicsure (C)2022
// https://www.youtube.com/nicsure

static const UINT8 OP_TCOUNT[256] =
{
    4,10,7,5,5,5,7,4,4,10,7,5,5,5,7,4,
    4,10,7,5,5,5,7,4,4,10,7,5,5,5,7,4,
    4,10,16,5,5,5,7,4,4,10,16,5,5,5,7,4,
    4,10,13,5,10,10,10,4,4,10,13,5,5,5,7,4,
    5,5,5,5,5,5,7,5,5,5,5,5,5,5,7,5,
    5,5,5,5,5,5,7,5,5,5,5,5,5,5,7,5,
    5,5,5,5,5,5,7,5,5,5,5,5,5,5,7,5,
    7,7,7,7,7,7,7,7,5,5,5,5,5,5,7,5,
    4,4,4,4,4,4,7,4,4,4,4,4,4,4,7,4,
    4,4,4,4,4,4,7,4,4,4,4,4,4,4,7,4,
    4,4,4,4,4,4,7,4,4,4,4,4,4,4,7,4,
    4,4,4,4,4,4,7,4,4,4,4,4,4,4,7,4,
    5,10,10,10,11,11,7,11,5,10,10,10,11,17,7,11,
    5,10,10,10,11,11,7,11,5,10,10,10,11,17,7,11,
    5,10,10,18,11,11,7,11,5,5,10,4,11,17,7,11,
    5,10,10,4,11,11,7,11,5,5,10,4,11,17,7,11
};

static const BOOL PARITY[256] = 
{
    1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
    0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
    0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
    1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
    0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
    1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
    1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
    0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
    0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
    1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
    1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
    0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
    1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
    0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
    0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
    1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1
};

static UINT8 STATE[65792];
static UINT8 STATUS[140];
static UINT8* RAM = (UINT8*)&STATE[0x100];

static UINT16* BC = (UINT16*)&STATE[0];
static UINT16* DE = (UINT16*)&STATE[2];
static UINT16* HL = (UINT16*)&STATE[4];
static UINT16* AF = (UINT16*)&STATE[6];
static UINT16* SP = (UINT16*)&STATE[8];
static UINT16* PC = (UINT16*)&STATE[10];

static UINT8* A = (UINT8*)&STATE[7];
static UINT8* F = (UINT8*)&STATE[6];
static UINT8* B = (UINT8*)&STATE[1];
static UINT8* C = (UINT8*)&STATE[0];
static UINT8* D = (UINT8*)&STATE[3];
static UINT8* E = (UINT8*)&STATE[2];
static UINT8* H = (UINT8*)&STATE[5];
static UINT8* L = (UINT8*)&STATE[4];
static UINT8* IV = (UINT8*)&STATE[12];
static BOOL* EI = (BOOL*)&STATE[16];
static BOOL* HLT = (BOOL*)&STATE[20];

static UINT32* sA = (UINT32*)&STATUS[0];
static UINT32* sD = (UINT32*)&STATUS[64];
static UINT32* sWAIT = (UINT32*)&STATUS[96];
static UINT32* sEI = (UINT32*)&STATUS[100];
static UINT32* sRM = (UINT32*)&STATUS[104];
static UINT32* sIN = (UINT32*)&STATUS[108];
static UINT32* sM1 = (UINT32*)&STATUS[112];
static UINT32* sOUT = (UINT32*)&STATUS[116];
static UINT32* sHLT = (UINT32*)&STATUS[120];
static UINT32* sSTK = (UINT32*)&STATUS[124];
static UINT32* sWO = (UINT32*)&STATUS[128];
static UINT32* sINT = (UINT32*)&STATUS[132];
static UINT32* sCNT = (UINT32*)&STATUS[136];

void EXECUTE(UINT8);
void RESET(BOOL);
UINT8 RAM8(UINT16);
void RAM8(UINT16, UINT8);
void UPDATE(UINT16, UINT8);
void LOOP();
void STATUSCALLBACK();

static BOOL bRM;
static BOOL bIN;
static BOOL bM1;
static BOOL bOUT;
static BOOL bSTK;
static BOOL bWO;
static BOOL bINT;

static UINT64 tsCount;
static DWORD timerCount;
static BOOL requestEI;
static HANDLE pauseMutex;
static DWORD startTime;
static UINT64 speed;
static BOOL running;
static BOOL step;
static BOOL stepping;
static BOOL doStatus;
static BOOL updatedPC;
static BOOL incPC;

static int currentOP;

#endif