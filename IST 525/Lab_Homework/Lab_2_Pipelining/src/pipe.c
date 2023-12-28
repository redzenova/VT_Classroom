/*
 * ECE 18-447, Spring 2013
 *
 * MIPS pipeline timing simulator
 *
 * Chris Fallin, 2012
 */

#include "pipe.h"
#include "shell.h"
#include "mips.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

//#define DEBUG

/* debug */
void print_op(Pipe_Op *op)
{
    if (op)
        printf("OP (PC=%08x inst=%08x) src1=R%d (%08x) src2=R%d (%08x) dst=R%d valid %d (%08x) br=%d taken=%d dest=%08x mem=%d addr=%08x\n",
                op->pc, op->instruction, op->reg_src1, op->reg_src1_value, op->reg_src2, op->reg_src2_value, op->reg_dst, op->reg_dst_value_ready,
                op->reg_dst_value, op->is_branch, op->branch_taken, op->branch_dest, op->is_mem, op->mem_addr);
    else
        printf("(null)\n");
}

/* global pipeline state */
Pipe_State pipe;

Cache instruction_cache_table[64][4];
Cache data_cache_table[256][8];

PHTs PHT[256];
BTBs BTB[1024];
uint32_t GHR = 0;

void pipe_init()
{
    memset(&pipe, 0, sizeof(Pipe_State));
    pipe.PC = 0x00400000;
    cache_init();
    pipe.syscall = 0;
}

void pipe_cycle()
{
#ifdef DEBUG
    printf("\n\n----\n\nPIPELINE:\n");
    printf("DCODE: "); print_op(pipe.decode_op);
    printf("EXEC : "); print_op(pipe.execute_op);
    printf("MEM  : "); print_op(pipe.mem_op);
    printf("WB   : "); print_op(pipe.wb_op);
    printf("\n");
#endif

    pipe_stage_wb();
    pipe_stage_mem();
    pipe_stage_execute();
    pipe_stage_decode();
    pipe_stage_fetch();

    /* handle branch recoveries */
    if (pipe.branch_recover) {
#ifdef DEBUG
        printf("branch recovery: new dest %08x flush %d stages\n", pipe.branch_dest, pipe.branch_flush);
#endif

        // stop stalling, if current pc != dest.
        if(pipe.PC != pipe.branch_dest){
            pipe.instruction_cache_stall = 0;
        }

        pipe.PC = pipe.branch_dest;
        
        //printf("DO THE BRANCH RECOVERRRR, PC dest = %x\n", pipe.PC);
        if (pipe.branch_flush >= 2) {
            if (pipe.decode_op) free(pipe.decode_op);
            pipe.decode_op = NULL;
        }

        if (pipe.branch_flush >= 3) {
            if (pipe.execute_op) free(pipe.execute_op);
            pipe.execute_op = NULL;
        }

        if (pipe.branch_flush >= 4) {
            if (pipe.mem_op) free(pipe.mem_op);
            pipe.mem_op = NULL;
        }

        if (pipe.branch_flush >= 5) {
            if (pipe.wb_op) free(pipe.wb_op);
            pipe.wb_op = NULL;
        }
                     
        //pipe.instruction_cache_stall = 0;
        pipe.branch_recover = 0;
        pipe.branch_dest = 0;
        pipe.branch_flush = 0;
        
        stat_squash++;
    }
}

void pipe_recover(int flush, uint32_t dest)
{
    /* if there is already a recovery scheduled, it must have come from a later
     * stage (which executes older instructions), hence that recovery overrides
     * our recovery. Simply return in this case. */
    if (pipe.branch_recover) return;

    /* schedule the recovery. This will be done once all pipeline stages simulate the current cycle. */
    pipe.branch_recover = 1;
    pipe.branch_flush = flush;
    pipe.branch_dest = dest;
}

void pipe_stage_wb()
{
    /* if there is no instruction in this pipeline stage, we are done */
    if (!pipe.wb_op)
        return;

    /* grab the op out of our input slot */
    Pipe_Op *op = pipe.wb_op;
    pipe.wb_op = NULL;

    /* if this instruction writes a register, do so now */
    if (op->reg_dst != -1 && op->reg_dst != 0) {
        pipe.REGS[op->reg_dst] = op->reg_dst_value;
#ifdef DEBUG
        printf("R%d = %08x\n", op->reg_dst, op->reg_dst_value);
#endif
    }

    /* if this was a syscall, perform action */
    if (op->opcode == OP_SPECIAL && op->subop == SUBOP_SYSCALL) {
        if (op->reg_src1_value == 0xA) {
            pipe.PC = op->pc + 4; /* fetch will do pc += 4, then we stop with correct PC */
            printf("IT'S A SYSCALLLL, PC = %x\n", pipe.PC);
            pipe.syscall = 1;
            RUN_BIT = 0;
            
        }
    }

    /* free the op */
    free(op);

    stat_inst_retire++;
}


void pipe_stage_mem()
{
    /* if there is no instruction in this pipeline stage, we are done */
    if (!pipe.mem_op)
        return;

    if(pipe.syscall)
        return;
    
    
    /* grab the op out of our input slot */
    Pipe_Op *op = pipe.mem_op;

    if (pipe.data_cache_stall == 1){
        //printf("%d UPDATE data cache\n", pipe.data_cache_stall);
        update_data_cache(op->mem_addr & ~3);
    }

    if (pipe.data_cache_stall > 0){
        //printf("%d data remaining stall\n", pipe.data_cache_stall);
        pipe.data_cache_stall--;
        return;
    }

    uint32_t val = 0;
    if (op->is_mem)
        //val = mem_read_32(op->mem_addr & ~3);
        val = read_data_cache(op->mem_addr & ~3);

        if (pipe.data_cache_stall > 0){
            //printf("%d data remaining stall\n", pipe.data_cache_stall);
            pipe.data_cache_stall--;
            return;
    }

    switch (op->opcode) {
        case OP_LW:
        case OP_LH:
        case OP_LHU:
        case OP_LB:
        case OP_LBU:
            {
                /* extract needed value */
                op->reg_dst_value_ready = 1;
                if (op->opcode == OP_LW) {
                    op->reg_dst_value = val;
                }
                else if (op->opcode == OP_LH || op->opcode == OP_LHU) {
                    if (op->mem_addr & 2)
                        val = (val >> 16) & 0xFFFF;
                    else
                        val = val & 0xFFFF;

                    if (op->opcode == OP_LH)
                        val |= (val & 0x8000) ? 0xFFFF8000 : 0;

                    op->reg_dst_value = val;
                }
                else if (op->opcode == OP_LB || op->opcode == OP_LBU) {
                    switch (op->mem_addr & 3) {
                        case 0:
                            val = val & 0xFF;
                            break;
                        case 1:
                            val = (val >> 8) & 0xFF;
                            break;
                        case 2:
                            val = (val >> 16) & 0xFF;
                            break;
                        case 3:
                            val = (val >> 24) & 0xFF;
                            break;
                    }

                    if (op->opcode == OP_LB)
                        val |= (val & 0x80) ? 0xFFFFFF80 : 0;

                    op->reg_dst_value = val;
                }
            }
            break;

        case OP_SB:
            switch (op->mem_addr & 3) {
                case 0: val = (val & 0xFFFFFF00) | ((op->mem_value & 0xFF) << 0); break;
                case 1: val = (val & 0xFFFF00FF) | ((op->mem_value & 0xFF) << 8); break;
                case 2: val = (val & 0xFF00FFFF) | ((op->mem_value & 0xFF) << 16); break;
                case 3: val = (val & 0x00FFFFFF) | ((op->mem_value & 0xFF) << 24); break;
            }

            mem_write_32(op->mem_addr & ~3, val);
            break;

        case OP_SH:
#ifdef DEBUG
            printf("SH: addr %08x val %04x old word %08x\n", op->mem_addr, op->mem_value & 0xFFFF, val);
#endif
            if (op->mem_addr & 2)
                val = (val & 0x0000FFFF) | (op->mem_value) << 16;
            else
                val = (val & 0xFFFF0000) | (op->mem_value & 0xFFFF);
#ifdef DEBUG
            printf("new word %08x\n", val);
#endif

            mem_write_32(op->mem_addr & ~3, val);
            break;

        case OP_SW:
            val = op->mem_value;
            mem_write_32(op->mem_addr & ~3, val);
            break;
    }

    /* clear stage input and transfer to next stage */
    pipe.mem_op = NULL;
    pipe.wb_op = op;
}

void pipe_stage_execute()
{
    /* if a multiply/divide is in progress, decrement cycles until value is ready */
    if (pipe.multiplier_stall > 0)
        pipe.multiplier_stall--;

    /* if downstream stall, return (and leave any input we had) */
    if (pipe.mem_op != NULL)
        return;

    /* if no op to execute, return */
    if (pipe.execute_op == NULL)
        return;

    if(pipe.syscall)
        return;

    /* grab op and read sources */
    Pipe_Op *op = pipe.execute_op;

    if((4300 < stat_cycles) && (stat_cycles < 4361)){
        printf("\n\nEXECUTE pc = %x\n", op->pc);
    }
    
    /* read register values, and check for bypass; stall if necessary */
    int stall = 0;
    if (op->reg_src1 != -1) {
        if (op->reg_src1 == 0)
            op->reg_src1_value = 0;
        else if (pipe.mem_op && pipe.mem_op->reg_dst == op->reg_src1) {
            if (!pipe.mem_op->reg_dst_value_ready)
                stall = 1;
            else
                op->reg_src1_value = pipe.mem_op->reg_dst_value;
        }
        else if (pipe.wb_op && pipe.wb_op->reg_dst == op->reg_src1) {
            op->reg_src1_value = pipe.wb_op->reg_dst_value;
        }
        else
            op->reg_src1_value = pipe.REGS[op->reg_src1];
    }
    if (op->reg_src2 != -1) {
        if (op->reg_src2 == 0)
            op->reg_src2_value = 0;
        else if (pipe.mem_op && pipe.mem_op->reg_dst == op->reg_src2) {
            if (!pipe.mem_op->reg_dst_value_ready)
                stall = 1;
            else
                op->reg_src2_value = pipe.mem_op->reg_dst_value;
        }
        else if (pipe.wb_op && pipe.wb_op->reg_dst == op->reg_src2) {
            op->reg_src2_value = pipe.wb_op->reg_dst_value;
        }
        else
            op->reg_src2_value = pipe.REGS[op->reg_src2];
    }

    /* if bypassing requires a stall (e.g. use immediately after load),
     * return without clearing stage input */
    if (stall) 
        return;

    /* execute the op */
    switch (op->opcode) {
        case OP_SPECIAL:
            op->reg_dst_value_ready = 1;
            switch (op->subop) {
                case SUBOP_SLL:
                    op->reg_dst_value = op->reg_src2_value << op->shamt;
                    break;
                case SUBOP_SLLV:
                    op->reg_dst_value = op->reg_src2_value << op->reg_src1_value;
                    break;
                case SUBOP_SRL:
                    op->reg_dst_value = op->reg_src2_value >> op->shamt;
                    break;
                case SUBOP_SRLV:
                    op->reg_dst_value = op->reg_src2_value >> op->reg_src1_value;
                    break;
                case SUBOP_SRA:
                    op->reg_dst_value = (int32_t)op->reg_src2_value >> op->shamt;
                    break;
                case SUBOP_SRAV:
                    op->reg_dst_value = (int32_t)op->reg_src2_value >> op->reg_src1_value;
                    break;
                case SUBOP_JR:
                case SUBOP_JALR:
                    op->reg_dst_value = op->pc + 4;
                    op->branch_dest = op->reg_src1_value;
                    op->branch_taken = 1;
                    break;

                case SUBOP_MULT:
                    {
                        /* we set a result value right away; however, we will
                         * model a stall if the program tries to read the value
                         * before it's ready (or overwrite HI/LO). Also, if
                         * another multiply comes down the pipe later, it will
                         * update the values and re-set the stall cycle count
                         * for a new operation.
                         */
                        int64_t val = (int64_t)((int32_t)op->reg_src1_value) * (int64_t)((int32_t)op->reg_src2_value);
                        uint64_t uval = (uint64_t)val;
                        pipe.HI = (uval >> 32) & 0xFFFFFFFF;
                        pipe.LO = (uval >>  0) & 0xFFFFFFFF;

                        /* four-cycle multiplier latency */
                        pipe.multiplier_stall = 4;
                    }
                    break;
                case SUBOP_MULTU:
                    {
                        uint64_t val = (uint64_t)op->reg_src1_value * (uint64_t)op->reg_src2_value;
                        pipe.HI = (val >> 32) & 0xFFFFFFFF;
                        pipe.LO = (val >>  0) & 0xFFFFFFFF;

                        /* four-cycle multiplier latency */
                        pipe.multiplier_stall = 4;
                    }
                    break;

                case SUBOP_DIV:
                    if (op->reg_src2_value != 0) {

                        int32_t val1 = (int32_t)op->reg_src1_value;
                        int32_t val2 = (int32_t)op->reg_src2_value;
                        int32_t div, mod;

                        div = val1 / val2;
                        mod = val1 % val2;

                        pipe.LO = div;
                        pipe.HI = mod;
                    } else {
                        // really this would be a div-by-0 exception
                        pipe.HI = pipe.LO = 0;
                    }

                    /* 32-cycle divider latency */
                    pipe.multiplier_stall = 32;
                    break;

                case SUBOP_DIVU:
                    if (op->reg_src2_value != 0) {
                        pipe.HI = (uint32_t)op->reg_src1_value % (uint32_t)op->reg_src2_value;
                        pipe.LO = (uint32_t)op->reg_src1_value / (uint32_t)op->reg_src2_value;
                    } else {
                        /* really this would be a div-by-0 exception */
                        pipe.HI = pipe.LO = 0;
                    }

                    /* 32-cycle divider latency */
                    pipe.multiplier_stall = 32;
                    break;

                case SUBOP_MFHI:
                    /* stall until value is ready */
                    if (pipe.multiplier_stall > 0)
                        return;

                    op->reg_dst_value = pipe.HI;
                    break;
                case SUBOP_MTHI:
                    /* stall to respect WAW dependence */
                    if (pipe.multiplier_stall > 0)
                        return;

                    pipe.HI = op->reg_src1_value;
                    break;

                case SUBOP_MFLO:
                    /* stall until value is ready */
                    if (pipe.multiplier_stall > 0)
                        return;

                    op->reg_dst_value = pipe.LO;
                    break;
                case SUBOP_MTLO:
                    /* stall to respect WAW dependence */
                    if (pipe.multiplier_stall > 0)
                        return;

                    pipe.LO = op->reg_src1_value;
                    break;

                case SUBOP_ADD:
                case SUBOP_ADDU:
                    op->reg_dst_value = op->reg_src1_value + op->reg_src2_value;
                    break;
                case SUBOP_SUB:
                case SUBOP_SUBU:
                    op->reg_dst_value = op->reg_src1_value - op->reg_src2_value;
                    break;
                case SUBOP_AND:
                    op->reg_dst_value = op->reg_src1_value & op->reg_src2_value;
                    break;
                case SUBOP_OR:
                    op->reg_dst_value = op->reg_src1_value | op->reg_src2_value;
                    break;
                case SUBOP_NOR:
                    op->reg_dst_value = ~(op->reg_src1_value | op->reg_src2_value);
                    break;
                case SUBOP_XOR:
                    op->reg_dst_value = op->reg_src1_value ^ op->reg_src2_value;
                    break;
                case SUBOP_SLT:
                    op->reg_dst_value = ((int32_t)op->reg_src1_value <
                            (int32_t)op->reg_src2_value) ? 1 : 0;
                    break;
                case SUBOP_SLTU:
                    op->reg_dst_value = (op->reg_src1_value < op->reg_src2_value) ? 1 : 0;
                    break;
            }
            break;

        case OP_BRSPEC:
            switch (op->subop) {
                case BROP_BLTZ:
                case BROP_BLTZAL:
                    if ((int32_t)op->reg_src1_value < 0) op->branch_taken = 1;
                    break;

                case BROP_BGEZ:
                case BROP_BGEZAL:
                    if ((int32_t)op->reg_src1_value >= 0) op->branch_taken = 1;
                    break;
            }
            break;

        case OP_BEQ:
            if (op->reg_src1_value == op->reg_src2_value) op->branch_taken = 1;
            break;

        case OP_BNE:
            if (op->reg_src1_value != op->reg_src2_value) op->branch_taken = 1;
            break;

        case OP_BLEZ:
            if ((int32_t)op->reg_src1_value <= 0) op->branch_taken = 1;
            break;

        case OP_BGTZ:
            if ((int32_t)op->reg_src1_value > 0) op->branch_taken = 1;
            break;

        case OP_ADDI:
        case OP_ADDIU:
            op->reg_dst_value_ready = 1;
            op->reg_dst_value = op->reg_src1_value + op->se_imm16;
            break;
        case OP_SLTI:
            op->reg_dst_value_ready = 1;
            op->reg_dst_value = (int32_t)op->reg_src1_value < (int32_t)op->se_imm16 ? 1 : 0;
            break;
        case OP_SLTIU:
            op->reg_dst_value_ready = 1;
            op->reg_dst_value = (uint32_t)op->reg_src1_value < (uint32_t)op->se_imm16 ? 1 : 0;
            break;
        case OP_ANDI:
            op->reg_dst_value_ready = 1;
            op->reg_dst_value = op->reg_src1_value & op->imm16;
            break;
        case OP_ORI:
            op->reg_dst_value_ready = 1;
            op->reg_dst_value = op->reg_src1_value | op->imm16;
            break;
        case OP_XORI:
            op->reg_dst_value_ready = 1;
            op->reg_dst_value = op->reg_src1_value ^ op->imm16;
            break;
        case OP_LUI:
            op->reg_dst_value_ready = 1;
            op->reg_dst_value = op->imm16 << 16;
            break;

        case OP_LW:
        case OP_LH:
        case OP_LHU:
        case OP_LB:
        case OP_LBU:
            op->mem_addr = op->reg_src1_value + op->se_imm16;
            break;

        case OP_SW:
        case OP_SH:
        case OP_SB:
            op->mem_addr = op->reg_src1_value + op->se_imm16;
            op->mem_value = op->reg_src2_value;
            break;
    }

    /* handle branch recoveries at this point */
    // if (op->branch_taken)
    //     pipe_recover(3, op->branch_dest);

    uint32_t BTBentry = (op->pc >> 2) & 0x3FF; //[11:2] of pc
    uint32_t GHRpc = (op->pc >> 2) & 0xFF; //[9:2] of pc
    uint32_t dest;
    //update GHR

    if(op->is_branch){
        if (op->branch_taken == 0){
            dest = op->pc+4;
        }
        if (op->branch_taken == 1){
            dest = op->branch_dest;
        }
    }

    // flush.
    if (op->is_branch == 1){ 
        if((4300 < stat_cycles) && (stat_cycles < 4361)){
            printf("EXECUTE BRANCHHHHHHHHHHHHHHH\n");
        }
        if ((op->predicted_dir != op->branch_taken) || (op->predicted_dest != dest) ||  BTB[BTBentry].valid == 0 ){
            if((4300 < stat_cycles) && (stat_cycles < 4361)){
                printf("misdir = %d, misdest = %d, not valid = %d\n", (op->predicted_dir != op->branch_taken), (op->predicted_dest != dest), BTB[BTBentry].valid == 0);  
                printf("predicted dir = %d, branch dir = %d\n",op->predicted_dir, op->branch_taken);
                printf("predicted dest = %x, branch dest = %x\n", op->predicted_dest, dest);
            }
            if (op->branch_taken) { // taken -> dest
                pipe_recover(3, op->branch_dest);
                
                if((4300 < stat_cycles) && (stat_cycles < 4361)){
                    printf("flush to dest pc (%x)\n", op->branch_dest);
                }
            }
            else {  // not taken -> pc + 4
                pipe_recover(3, op->pc + 4);
        
                if((4300 < stat_cycles) && (stat_cycles < 4361)){
                    printf("flush to pc + 4 (%x)\n", op->pc + 4);
                }
            }
        }
        // if BTB miss??
    }

    // update BTB
    if (op->is_branch == 1){
        //printf("update BTB\n");
        //printf("BTBentry = %d\n", BTBentry);
        BTB[BTBentry].tag = op->pc;
        BTB[BTBentry].valid = 1; // ??
        BTB[BTBentry].cond = op->branch_cond;
        BTB[BTBentry].target = op->branch_dest;
        
    }


    uint32_t PHTentry = (GHR ^ GHRpc) & 0xFF;

    // update PHT (only cond branch)
    if(op->is_branch && op->branch_cond){
        PHT[PHTentry].counter = (op->branch_taken) ? PHT[PHTentry].counter+1 : PHT[PHTentry].counter-1;
    }

    if(PHT[PHTentry].counter > 3) PHT[PHTentry].counter = 3;
    if(PHT[PHTentry].counter < 0) PHT[PHTentry].counter = 0;

    // update GHR
    if (op->is_branch == 1){
        if (op->branch_taken){
            GHR = ((GHR << 1) + 1) & 0xFF;
        } 
        else {
            GHR = (GHR << 1) & 0xFF;
        }
    }


    /* remove from upstream stage and place in downstream stage */
    pipe.execute_op = NULL;
    pipe.mem_op = op;
}

void pipe_stage_decode()
{
    /* if downstream stall, return (and leave any input we had) */
    if (pipe.execute_op != NULL)
        return;

    /* if no op to decode, return */
    if (pipe.decode_op == NULL)
        return;
    
    if(pipe.syscall)
        return;

    /* grab op and remove from stage input */
    Pipe_Op *op = pipe.decode_op;
    pipe.decode_op = NULL;

    /* set up info fields (source/dest regs, immediate, jump dest) as necessary */
    uint32_t opcode = (op->instruction >> 26) & 0x3F;
    uint32_t rs = (op->instruction >> 21) & 0x1F;
    uint32_t rt = (op->instruction >> 16) & 0x1F;
    uint32_t rd = (op->instruction >> 11) & 0x1F;
    uint32_t shamt = (op->instruction >> 6) & 0x1F;
    uint32_t funct1 = (op->instruction >> 0) & 0x1F;
    uint32_t funct2 = (op->instruction >> 0) & 0x3F;
    uint32_t imm16 = (op->instruction >> 0) & 0xFFFF;
    uint32_t se_imm16 = imm16 | ((imm16 & 0x8000) ? 0xFFFF8000 : 0);
    uint32_t targ = (op->instruction & ((1UL << 26) - 1)) << 2;

    // my code //
    // uint32_t set_index = (op->instruction >> 5) & 0x3F;
    // uint32_t offset = (op->instruction >> 0) & 0x1F;
    // uint32_t tag = (op->instruction >> 11) & 0x1FFFF;
    // my code //
    
    op->opcode = opcode;
    op->imm16 = imm16;
    op->se_imm16 = se_imm16;
    op->shamt = shamt;
    
    
    switch (opcode) {
        case OP_SPECIAL:
            /* all "SPECIAL" insts are R-types that use the ALU and both source
             * regs. Set up source regs and immediate value. */
            op->reg_src1 = rs;
            op->reg_src2 = rt;
            op->reg_dst = rd;
            op->subop = funct2;
            if (funct2 == SUBOP_SYSCALL) {
                op->reg_src1 = 2; // v0
                op->reg_src2 = 3; // v1
            }
            if (funct2 == SUBOP_JR || funct2 == SUBOP_JALR) {
                op->is_branch = 1;
                op->branch_cond = 0;
            }

            break;

        case OP_BRSPEC:
            /* branches that have -and-link variants come here */
            op->is_branch = 1;
            op->reg_src1 = rs;
            op->reg_src2 = rt;
            op->is_branch = 1;
            op->branch_cond = 1; /* conditional branch */
            op->branch_dest = op->pc + 4 + (se_imm16 << 2);
            op->subop = rt;
            if (rt == BROP_BLTZAL || rt == BROP_BGEZAL) {
                /* link reg */
                op->reg_dst = 31;
                op->reg_dst_value = op->pc + 4;
                op->reg_dst_value_ready = 1;
            }
            break;

        case OP_JAL:
            op->reg_dst = 31;
            op->reg_dst_value = op->pc + 4;
            op->reg_dst_value_ready = 1;
            op->branch_taken = 1;
            /* fallthrough */
        case OP_J:
            op->is_branch = 1;
            op->branch_cond = 0;
            op->branch_taken = 1;
            op->branch_dest = (op->pc & 0xF0000000) | targ;
            break;

        case OP_BEQ:
        case OP_BNE:
        case OP_BLEZ:
        case OP_BGTZ:
            /* ordinary conditional branches (resolved after execute) */
            op->is_branch = 1;
            op->branch_cond = 1;
            op->branch_dest = op->pc + 4 + (se_imm16 << 2);
            op->reg_src1 = rs;
            op->reg_src2 = rt;
            break;

        case OP_ADDI:
        case OP_ADDIU:
        case OP_SLTI:
        case OP_SLTIU:
            /* I-type ALU ops with sign-extended immediates */
            op->reg_src1 = rs;
            op->reg_dst = rt;
            break;

        case OP_ANDI:
        case OP_ORI:
        case OP_XORI:
        case OP_LUI:
            /* I-type ALU ops with non-sign-extended immediates */
            op->reg_src1 = rs;
            op->reg_dst = rt;
            break;

        case OP_LW:
        case OP_LH:
        case OP_LHU:
        case OP_LB:
        case OP_LBU:
        case OP_SW:
        case OP_SH:
        case OP_SB:
            /* memory ops */
            op->is_mem = 1;
            op->reg_src1 = rs;
            if (opcode == OP_LW || opcode == OP_LH || opcode == OP_LHU || opcode == OP_LB || opcode == OP_LBU) {
                /* load */
                op->mem_write = 0;
                op->reg_dst = rt;
            }
            else {
                /* store */
                op->mem_write = 1;
                op->reg_src2 = rt;
            }
            break;
    }

    /* we will handle reg-read together with bypass in the execute stage */

    /* place op in downstream slot */
    pipe.execute_op = op;
}




void pipe_stage_fetch()
{
    /* if pipeline is stalled (our output slot is not empty), return */
    if (pipe.decode_op != NULL)
        return;
    
    if (pipe.instruction_cache_stall == 1){
        update_instruction_cache(pipe.PC);
    }

    if (pipe.instruction_cache_stall > 0){
        if((4300 < stat_cycles) && (stat_cycles < 4361)){
            printf("%d instruction remaining stall\n", pipe.instruction_cache_stall);
        }
        pipe.instruction_cache_stall--;
        return;
    }


    if(pipe.syscall)
        return;
    
    //printf("in fetch\n");

    /* Allocate an op and send it down the pipeline. */
    Pipe_Op *op = malloc(sizeof(Pipe_Op));
    memset(op, 0, sizeof(Pipe_Op));
    op->reg_src1 = op->reg_src2 = op->reg_dst = -1;

    
    //printf("FETCH pc = %x\n", pipe.PC);

    op->instruction = read_instruction_cache(pipe.PC);


    if (pipe.instruction_cache_stall > 0){
        if((4300 < stat_cycles) && (stat_cycles < 4361)){
            printf("%d instruction remaining stall\n", pipe.instruction_cache_stall);
        }
        pipe.instruction_cache_stall--;
        return;
    }


    op->pc = pipe.PC;

    uint32_t BTB2entry = (op->pc >> 2) & 0x3FF; //[11:2] of pc
    uint32_t GHRpc = (op->pc >> 2) & 0xFF; //[9:2] of pc
    uint32_t PHT2entry = GHR ^ GHRpc;

    if ((BTB[BTB2entry].tag != op->pc) || BTB[BTB2entry].valid == 0 || PHT[PHT2entry].counter < 2){ // not taken

        op->predicted_dir = 0;
        op->predicted_dest = pipe.PC + 4;
        pipe.decode_op = op;
        pipe.PC = op->predicted_dest; // update PC
        stat_inst_fetch++;
        return;
    } 

    else if (BTB[BTB2entry].cond == 0 || PHT[PHT2entry].counter >= 2){  // taken
        
        op->predicted_dir = 1;
        op->predicted_dest = BTB[BTB2entry].target;
        pipe.decode_op = op;
        pipe.PC = op->predicted_dest; // update PC
        stat_inst_fetch++;
        return;
    }


    pipe.decode_op = op;


    /* update PC */
 
    pipe.PC += 4;
    stat_inst_fetch++;

    
}



void cache_init(){
    int a;
    int b;
    for(a=0; a<64; a++){
        for(b=0; b<4; b++){
            instruction_cache_table[a][b].age = 0;
            instruction_cache_table[a][b].tag = 0;
            instruction_cache_table[a][b].value = 0;
        }
    }

    for(a=0; a<256; a++){
        for(b=0; b<8; b++){
            data_cache_table[a][b].age = 0;
            data_cache_table[a][b].tag = 0;
            data_cache_table[a][b].value = 0;
        }
    }
}


uint32_t read_data_cache(uint32_t address){

    uint8_t set = (address>>5) & 0xFF;
    uint32_t tag = (address>>13) & 0x7FFFFF;

    int way, value, isHit = -1;
    int i, maxAge , maxAgeIndex;
    //check cache tag, every way in the set

    for(way=0; way<8; way++){
        if(data_cache_table[set][way].tag == tag && data_cache_table[set][way].age != 0){ //cache hit
            //update age
            data_cache_table[set][way].age = 1;
            value = mem_read_32(address);
            isHit = 1;
        }
        else{
            //if cache is not empty, increment the age.
            if (data_cache_table[set][way].age != 0){
                data_cache_table[set][way].age +=1;
            }
        }
    }
    if(isHit == -1){ // if no cache hit
        //stall 50 cycles
        pipe.data_cache_stall = 50;

        return 0;
    }
    return value;
}


void update_data_cache(uint32_t address){

    uint8_t set = (address>>5) & 0xFF;
    uint32_t tag = (address>>13) & 0x7FFFFF;
    
    int i, maxAge, maxAgeIndex;
    uint32_t value;

    value = mem_read_32(address); 

        //find and replace into the oldest cache
    maxAge = 1;
    maxAgeIndex = 0;
    for(i=0; i<8; i++){ 
        if(maxAge < data_cache_table[set][i].age){   // find
            maxAge = data_cache_table[set][i].age;
            maxAgeIndex = i;
        }
        if(data_cache_table[set][i].age == 0){
            maxAgeIndex = i;
            break;
        }
    }
    data_cache_table[set][maxAgeIndex].value = value;  // replace
    data_cache_table[set][maxAgeIndex].age = 1;  //set age to youngest
    data_cache_table[set][maxAgeIndex].tag = tag;
}

uint32_t read_instruction_cache(uint32_t address){ //address is pc
    
    uint8_t set = ((address>>5) & 0x3F);  // set is known from pc[10:5]
    uint32_t tag = ((address>>11) & 0x1FFFFF);    // tag is known from pc[31:11]

    uint32_t value;
    int way, isHit = -1;

    // check tag to find cache hit, every way in the set
    for(way=0; way<4; way++){
        if(instruction_cache_table[set][way].tag == tag && instruction_cache_table[set][way].age != 0){   // cache hit
            printf("instruction cache HIT\n");
            
            // it is just used!! so set its age to youngest
            instruction_cache_table[set][way].age = 1;
            value = mem_read_32(pipe.PC);
            isHit = 1;
        }
        else{
            //if cache is not empty, increment the age.
            if (instruction_cache_table[set][way].age != 0){
                instruction_cache_table[set][way].age +=1;
            }  
        }
    }
    if(isHit == -1){    // if no cache hit
        //stall 50 cycles
        printf("instruction cache MISS\n");
        pipe.instruction_cache_stall = 50;

        return 0;
    }
    return value;
}

void update_instruction_cache(uint32_t address){

    uint8_t set = ((address>>5) & 0x3F);  // set is known from pc[10:5]
    uint32_t tag = ((address>>11) & 0x1FFFFF);    // tag is known from pc[31:11]
    
    int i, maxAge, maxAgeIndex;
    uint32_t value;

    value = mem_read_32(pipe.PC); // not just this??

    //find and replace into the oldest cache
    maxAge = 1;
    maxAgeIndex = 0;
    for(i=0; i<4; i++){ 
        if(maxAge < instruction_cache_table[set][i].age){   // find
            maxAge = instruction_cache_table[set][i].age;
            maxAgeIndex = i;
        }
        if(instruction_cache_table[set][i].age == 0){
            maxAgeIndex = i;
            break;
        }
    }
    instruction_cache_table[set][maxAgeIndex].value = value;  // replace
    instruction_cache_table[set][maxAgeIndex].age = 1;  //set age to youngest
    instruction_cache_table[set][maxAgeIndex].tag = tag;
}





