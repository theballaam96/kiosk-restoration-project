/**
 * @file stack_trace.c
 * @author Ballaam
 * @brief Modifies the stack trace system to be vastly improved
 * @version 0.1
 * @date 2023-02-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../../include/common.h"

/*
    Register order
    v0-1
    a0-3
    t0-7
    s0-7
    t8-9
    gp, sp, s8, ra
    lo, hi
*/

typedef struct crash_handler_info {
    /* 0x000 */ char unk_000[0x28];
    /* 0x028 */ int general_registers[30][2];
    /* 0x118 */ char unk_118[0x11C-0x118];
    /* 0x11C */ void* pc;
    /* 0x120 */ int cause;
    /* 0x124 */ int va;
    /* 0x128 */ char unk_128[0x12C-0x128];
    /* 0x12C */ int fcsr;
    /* 0x130 */ float float_registers[32];
} crash_handler_info;

static char* general_text[] = {
    "V0:%08X\tV1:%08X\tA0:%08X\n",
    "A1:%08X\tA2:%08X\tA3:%08X\n",
    "T0:%08X\tT1:%08X\tT2:%08X\n",
    "T3:%08X\tT4:%08X\tT5:%08X\n",
    "T6:%08X\tT7:%08X\tS0:%08X\n",
    "S1:%08X\tS2:%08X\tS3:%08X\n",
    "S4:%08X\tS5:%08X\tS6:%08X\n",
    "S7:%08X\tT8:%08X\tT9:%08X\n",
    "GP:%08X\tSP:%08X\tS8:%08X\n",
    "RA:%08X\tLO:%08X\tHI:%08X\n",
};

static char* float_text[] = {
    "F00:%08X\tF01:%08X\tF02:%08X\n",
    "F03:%08X\tF04:%08X\tF05:%08X\n",
    "F06:%08X\tF07:%08X\tF08:%08X\n",
    "F09:%08X\tF10:%08X\tF11:%08X\n",
    "F12:%08X\tF13:%08X\tF14:%08X\n",
    "F15:%08X\tF16:%08X\tF17:%08X\n",
    "F18:%08X\tF19:%08X\tF20:%08X\n",
    "F21:%08X\tF22:%08X\tF23:%08X\n",
    "F24:%08X\tF25:%08X\tF26:%08X\n",
    "F27:%08X\tF28:%08X\tF29:%08X\n",
    "F30:%08X\tF31:%08X\n",
};

static char* general_causes[] = {
    "INTERRUPT",
    "TLB MODIFICATION", 
    "TLB EXCEPTION ON LOAD", 
    "TLB EXCEPTION ON STORE", 
    "ADDRESS ERROR ON LOAD", 
    "ADDRESS ERROR ON STORE", 
    "BUS ERROR ON INST.", 
    "BUS ERROR ON DATA", 
    "SYSTEM CALL EXCEPTION", 
    "BREAKPOINT EXCEPTION", 
    "RESERVED INSTRUCTION", 
    "COPROCESSOR UNUSABLE", 
    "ARITHMETIC OVERFLOW", 
    "TRAP EXCEPTION", 
    "VIRTUAL COHERENCY ON INST.", 
    "FLOATING POINT EXCEPTION", 
    "WATCHPOINT EXCEPTION", 
    "VIRTUAL COHERENCY ON DATA"
};

static char* float_causes[] = {
    "UNIMPLEMENTED OPERATION", 
    "INVALID OPERATION", 
    "DIVISION BY ZERO", 
    "OVERFLOW", 
    "UNDERFLOW", 
    "INEXACT OPERATION"
};

static s8 stack_trace_size = 2;
static s16 stack_unk_0 = -1;
static s16 stack_unk_1 = 1;
static s32 stack_x = 0;
static s32 stack_y = 0;
static s32 stack_start_x = 0;
static u8 reason_code;
static s32 stack_unk_2 = 0;
static s32 stack_unk_3 = 0;
static short* debug_pixels = 0;
stack_trace_log stack_trace_addresses[18];
static s32 stack_depth = 0;

int is_sp_shift(int instruction, int* stack_shift) {
    if ((instruction & 0xFFFF0000) == 0x27BD0000) {
        *stack_shift = *stack_shift + (instruction & 0xFFFF);
        return 1;
    }
    return 0;
}

int is_load_ra(int instruction, int stack_shift, int* write) {
    if ((instruction & 0xFFFF0000) == 0x8FBF0000) {
        int address = stack_shift + (instruction & 0xFFFF);
        *write = *(int*)(address);
        return 1;
    }
    return 0;
}

int is_jr_ra(int instruction, int* stack_shift, int* address, int** address_) {
    if ((instruction & 0x3FFFFFF) != 0x03E00008) {
        return 0;
    }
    is_sp_shift(**address_, stack_shift);
    if ((stack_depth == 0) || (address != stack_trace_addresses[stack_depth - 1].addr)) {
        stack_trace_addresses[stack_depth].addr = address;
        stack_trace_addresses[stack_depth].used = 1;
        stack_depth += 1;
    } else {
        stack_trace_addresses[stack_depth - 1].used += 1;
    }
    *address_ = address;
    return 1;
}

void dumpReturns(crash_handler_info* info) {
    int* pc = (int*)info->pc;
    int stack = info->general_registers[25][1];
    int ret = info->general_registers[27][1];
    stack_depth = 0;
    if (pc) {
        for (stack_depth = 0; stack_depth < 0x12;) {
            int instruction = *pc;
            pc++;
            int found = is_jr_ra(instruction, &stack, ret, &pc);
            if (!found) {
                found = is_load_ra(instruction, stack, &ret);
            }
            if (!found) {
                is_sp_shift(instruction, &stack);   
            }
            int resolved = 0;
            if (stack_depth) {
                resolved = 0xF < stack_trace_addresses[stack_depth - 1].used;
            }
            if (!pc) {
                break;
            }
            if (resolved) {
                break;
            }
        }
    }
    stack_unk_2 += 1;
    //*(int*)(0x807FFFFC) = (int)&stack_trace_addresses[0].addr;
}

void printDebugText(char* base, int arg0, int arg1, int arg2, int arg3) {

}

void CrashHandler(crash_handler_info* info) {
    stack_trace_size = 2; // Pixel Size
    stack_unk_0 = -1;
    stack_unk_1 = 1;
    s32 x = 0;
    s32 y = 0;
    stack_x = x;
    stack_y = y;
    stack_start_x = x;
    printDebugText("OOPS! YOUR GAME HAS CRASHED.\n", 0, 0, 0, 0);
    printDebugText("SEND A PICTURE OF THIS SCREEN TO\n", 0, 0, 0, 0);
    printDebugText("IATEYOURPIE\n", 0, 0, 0, 0);
    stack_trace_size = 1; // Pixel Size
    printDebugText("\n", 0, 0, 0, 0);
    y = stack_y; // Store Y for stack trace dump
    // if (reason_code != 0) { // Reason
    //     printDebugText("REASON: %s\n", (int)ReasonExceptions[(int)ReasonCode], 0, 0, 0);
    // } else {
    //     printDebugText("REASON: NONE ASCERTAINABLE\n", 0, 0, 0, 0);
    // }
    // General Exception
    int cause_index = _SHIFTR(info->cause, 2, 5);
    if (cause_index == 23) { // Watch Point
        cause_index = 16;
    }
    if (cause_index == 31) { // Virtual coherency on data
        cause_index = 17;
    }
    // printDebugText("GENERAL EXCEPTION: %s\n", (int)general_causes[cause_index], 0, 0, 0);
    // Float Exception
    // int flag = FPCSR_CE;
    // for (int i = 0; i < sizeof(float_causes)/4; i++) {
    //     if (info->fcsr & flag) {
    //         printDebugText("FLOAT EXCEPTION: %s\n", (int)float_causes[i], 0, 0, 0);
    //     }
    //     flag >>= 1;
    // }
    printDebugText("PC:%08X\n", (int)info->pc, 0, 0, 0);
    for (int i = 0; i < 10; i++) {
        int reg_start = 3 * i;
        int v1 = info->general_registers[reg_start][1];
        int v2 = info->general_registers[reg_start + 1][1];
        int v3 = info->general_registers[reg_start + 2][1];
        printDebugText(general_text[i], v1, v2, v3, 0);
    }
    printDebugText("\n",0,0,0,0);
    for (int i = 0; i < 11; i++) {
        int reg_start = 3 * i;
        int v1 = *(int*)&info->float_registers[reg_start];
        int v2 = *(int*)&info->float_registers[reg_start + 1];
        int v3 = 0;
        if (i < 10) {
            v3 = *(int*)&info->float_registers[reg_start + 2];
        }
        printDebugText(float_text[i], v1, v2, v3, 0);
    }
    stack_y = y;
    int stack_x = 210;
    stack_x = stack_x;
    stack_start_x = stack_x;
    stack_trace_size = 2; // Pixel Size
    printDebugText("STACK TRACE:\n",0,0,0,0);
    printDebugText("%X\n", (int)info->pc, 0, 0, 0);
    printDebugText("%X\n", (int)info->general_registers[27][1], 0, 0, 0);
    if (stack_unk_2 > 3) {
        for (int i = 0; i < stack_unk_3; i++) { // Stack Depth
            printDebugText("%X\n", (int)stack_trace_addresses[i].addr, 0, 0, 0);
        }
    }
    
    if (stack_unk_2 < 4) {
        stack_unk_2 += 1;
    }
    if (stack_unk_2 == 4) {
        dumpReturns(info);
    }
}

static OSMesgQueue crash_queue;
static OSMesg crash_mesg;
static OSThread crash_thread;

#define ENABLE_TRACE 1

void crashThread(void) {
    __osSetEventMesg(0xC, &crash_queue, 0X10);
    crash_handler_info* reg_data = 0;
    do {
        do {
            OSMesg unk0 = 0;
            __osRecvMesg(&crash_queue, &unk0, 1);
        } while (!ENABLE_TRACE);
        reg_data = getRegData();
    } while (reg_data == 0);
    do {
        for (int i = 0; i < 2; i++) {
            __osViBlack(0);
            debug_pixels = FramebufferPointer[i];
            CrashHandler(reg_data);
            CrashHandler(reg_data);
        }
    } while (1 == 1);
}

void createCrashThread(void) {
    int fpc_csr = __osGetFpcCsr();
    __osSetFpcCsr(fpc_csr | 0x400);
    __osCreateMesgQueue(&crash_queue, &crash_mesg, 1);
    __osCreateThread(&crash_thread, 8, (void*)&crashThread, 0, &crash_mesg, 0x32);
    __osStartThread(&crash_thread);
}