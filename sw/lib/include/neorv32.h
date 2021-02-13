// #################################################################################################
// # << NEORV32: neorv32.h - Main Core Library File >>                                             #
// # ********************************************************************************************* #
// # BSD 3-Clause License                                                                          #
// #                                                                                               #
// # Copyright (c) 2021, Stephan Nolting. All rights reserved.                                     #
// #                                                                                               #
// # Redistribution and use in source and binary forms, with or without modification, are          #
// # permitted provided that the following conditions are met:                                     #
// #                                                                                               #
// # 1. Redistributions of source code must retain the above copyright notice, this list of        #
// #    conditions and the following disclaimer.                                                   #
// #                                                                                               #
// # 2. Redistributions in binary form must reproduce the above copyright notice, this list of     #
// #    conditions and the following disclaimer in the documentation and/or other materials        #
// #    provided with the distribution.                                                            #
// #                                                                                               #
// # 3. Neither the name of the copyright holder nor the names of its contributors may be used to  #
// #    endorse or promote products derived from this software without specific prior written      #
// #    permission.                                                                                #
// #                                                                                               #
// # THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS   #
// # OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF               #
// # MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE    #
// # COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,     #
// # EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE #
// # GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED    #
// # AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING     #
// # NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED  #
// # OF THE POSSIBILITY OF SUCH DAMAGE.                                                            #
// # ********************************************************************************************* #
// # The NEORV32 Processor - https://github.com/stnolting/neorv32              (c) Stephan Nolting #
// #################################################################################################


/**********************************************************************//**
 * @file neorv32.h
 * @author Stephan Nolting
 *
 * @brief Main NEORV32 core library include file.
 **************************************************************************/

#ifndef neorv32_h
#define neorv32_h

// Standard libraries
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>


/**********************************************************************//**
 * Available CPU Control and Status Registers (CSRs)
 **************************************************************************/
enum NEORV32_CSR_enum {
  CSR_MSTATUS        = 0x300, /**< 0x300 - mstatus    (r/w): Machine status register */
  CSR_MISA           = 0x301, /**< 0x301 - misa       (r/-): CPU ISA and extensions (read-only in NEORV32) */
  CSR_MIE            = 0x304, /**< 0x304 - mie        (r/w): Machine interrupt-enable register */
  CSR_MTVEC          = 0x305, /**< 0x305 - mtvec      (r/w): Machine trap-handler base address (for ALL traps) */
  CSR_MCOUNTEREN     = 0x306, /**< 0x305 - mcounteren (r/w): Machine counter enable register (controls access rights from U-mode) */
  CSR_MSTATUSH       = 0x310, /**< 0x310 - mstatush   (r/-): Machine status register - high word */

  CSR_MCOUNTINHIBIT  = 0x320, /**< 0x320 - mcountinhibit (r/w): Machine counter-inhibit register */

  CSR_MHPMEVENT3     = 0x323, /**< 0x323 - mhpmevent3  (r/w): Machine hardware performance monitor event selector 3  */
  CSR_MHPMEVENT4     = 0x324, /**< 0x324 - mhpmevent4  (r/w): Machine hardware performance monitor event selector 4  */
  CSR_MHPMEVENT5     = 0x325, /**< 0x325 - mhpmevent5  (r/w): Machine hardware performance monitor event selector 5  */
  CSR_MHPMEVENT6     = 0x326, /**< 0x326 - mhpmevent6  (r/w): Machine hardware performance monitor event selector 6  */
  CSR_MHPMEVENT7     = 0x327, /**< 0x327 - mhpmevent7  (r/w): Machine hardware performance monitor event selector 7  */
  CSR_MHPMEVENT8     = 0x328, /**< 0x328 - mhpmevent8  (r/w): Machine hardware performance monitor event selector 8  */
  CSR_MHPMEVENT9     = 0x329, /**< 0x329 - mhpmevent9  (r/w): Machine hardware performance monitor event selector 9  */
  CSR_MHPMEVENT10    = 0x32a, /**< 0x32a - mhpmevent10 (r/w): Machine hardware performance monitor event selector 10 */
  CSR_MHPMEVENT11    = 0x32b, /**< 0x32b - mhpmevent11 (r/w): Machine hardware performance monitor event selector 11 */
  CSR_MHPMEVENT12    = 0x32c, /**< 0x32c - mhpmevent12 (r/w): Machine hardware performance monitor event selector 12 */
  CSR_MHPMEVENT13    = 0x32d, /**< 0x32d - mhpmevent13 (r/w): Machine hardware performance monitor event selector 13 */
  CSR_MHPMEVENT14    = 0x32e, /**< 0x32e - mhpmevent14 (r/w): Machine hardware performance monitor event selector 14 */
  CSR_MHPMEVENT15    = 0x32f, /**< 0x32f - mhpmevent15 (r/w): Machine hardware performance monitor event selector 15 */
  CSR_MHPMEVENT16    = 0x330, /**< 0x330 - mhpmevent16 (r/w): Machine hardware performance monitor event selector 16 */
  CSR_MHPMEVENT17    = 0x331, /**< 0x331 - mhpmevent17 (r/w): Machine hardware performance monitor event selector 17 */
  CSR_MHPMEVENT18    = 0x332, /**< 0x332 - mhpmevent18 (r/w): Machine hardware performance monitor event selector 18 */
  CSR_MHPMEVENT19    = 0x333, /**< 0x333 - mhpmevent19 (r/w): Machine hardware performance monitor event selector 19 */
  CSR_MHPMEVENT20    = 0x334, /**< 0x334 - mhpmevent20 (r/w): Machine hardware performance monitor event selector 20 */
  CSR_MHPMEVENT21    = 0x335, /**< 0x335 - mhpmevent21 (r/w): Machine hardware performance monitor event selector 21 */
  CSR_MHPMEVENT22    = 0x336, /**< 0x336 - mhpmevent22 (r/w): Machine hardware performance monitor event selector 22 */
  CSR_MHPMEVENT23    = 0x337, /**< 0x337 - mhpmevent23 (r/w): Machine hardware performance monitor event selector 23 */
  CSR_MHPMEVENT24    = 0x338, /**< 0x338 - mhpmevent24 (r/w): Machine hardware performance monitor event selector 24 */
  CSR_MHPMEVENT25    = 0x339, /**< 0x339 - mhpmevent25 (r/w): Machine hardware performance monitor event selector 25 */
  CSR_MHPMEVENT26    = 0x33a, /**< 0x33a - mhpmevent26 (r/w): Machine hardware performance monitor event selector 26 */
  CSR_MHPMEVENT27    = 0x33b, /**< 0x33b - mhpmevent27 (r/w): Machine hardware performance monitor event selector 27 */
  CSR_MHPMEVENT28    = 0x33c, /**< 0x33c - mhpmevent28 (r/w): Machine hardware performance monitor event selector 28 */
  CSR_MHPMEVENT29    = 0x33d, /**< 0x33d - mhpmevent29 (r/w): Machine hardware performance monitor event selector 29 */
  CSR_MHPMEVENT30    = 0x33e, /**< 0x33e - mhpmevent30 (r/w): Machine hardware performance monitor event selector 30 */
  CSR_MHPMEVENT31    = 0x33f, /**< 0x33f - mhpmevent31 (r/w): Machine hardware performance monitor event selector 31 */

  CSR_MSCRATCH       = 0x340, /**< 0x340 - mscratch (r/w): Machine scratch register */
  CSR_MEPC           = 0x341, /**< 0x341 - mepc     (r/w): Machine exception program counter */
  CSR_MCAUSE         = 0x342, /**< 0x342 - mcause   (r/w): Machine trap cause */
  CSR_MTVAL          = 0x343, /**< 0x343 - mtval    (r/w): Machine bad address or instruction */
  CSR_MIP            = 0x344, /**< 0x344 - mip      (r/w): Machine interrupt pending register */

  CSR_PMPCFG0        = 0x3a0, /**< 0x3a0 - pmpcfg0  (r/w): Physical memory protection configuration register 0  */
  CSR_PMPCFG1        = 0x3a1, /**< 0x3a1 - pmpcfg1  (r/w): Physical memory protection configuration register 1  */
  CSR_PMPCFG2        = 0x3a2, /**< 0x3a2 - pmpcfg2  (r/w): Physical memory protection configuration register 2  */
  CSR_PMPCFG3        = 0x3a3, /**< 0x3a3 - pmpcfg3  (r/w): Physical memory protection configuration register 3  */
  CSR_PMPCFG4        = 0x3a4, /**< 0x3a4 - pmpcfg4  (r/w): Physical memory protection configuration register 4  */
  CSR_PMPCFG5        = 0x3a5, /**< 0x3a5 - pmpcfg5  (r/w): Physical memory protection configuration register 5  */
  CSR_PMPCFG6        = 0x3a6, /**< 0x3a6 - pmpcfg6  (r/w): Physical memory protection configuration register 6  */
  CSR_PMPCFG7        = 0x3a7, /**< 0x3a7 - pmpcfg7  (r/w): Physical memory protection configuration register 7  */
  CSR_PMPCFG8        = 0x3a8, /**< 0x3a8 - pmpcfg8  (r/w): Physical memory protection configuration register 8  */
  CSR_PMPCFG9        = 0x3a9, /**< 0x3a9 - pmpcfg9  (r/w): Physical memory protection configuration register 9  */
  CSR_PMPCFG10       = 0x3aa, /**< 0x3aa - pmpcfg10 (r/w): Physical memory protection configuration register 10 */
  CSR_PMPCFG11       = 0x3ab, /**< 0x3ab - pmpcfg11 (r/w): Physical memory protection configuration register 11 */
  CSR_PMPCFG12       = 0x3ac, /**< 0x3ac - pmpcfg12 (r/w): Physical memory protection configuration register 12 */
  CSR_PMPCFG13       = 0x3ad, /**< 0x3ad - pmpcfg13 (r/w): Physical memory protection configuration register 13 */
  CSR_PMPCFG14       = 0x3ae, /**< 0x3ae - pmpcfg14 (r/w): Physical memory protection configuration register 14 */
  CSR_PMPCFG15       = 0x3af, /**< 0x3af - pmpcfg15 (r/w): Physical memory protection configuration register 15 */

  CSR_PMPADDR0       = 0x3b0, /**< 0x3b0 - pmpaddr0  (r/w): Physical memory protection address register 0  */
  CSR_PMPADDR1       = 0x3b1, /**< 0x3b1 - pmpaddr1  (r/w): Physical memory protection address register 1  */
  CSR_PMPADDR2       = 0x3b2, /**< 0x3b2 - pmpaddr2  (r/w): Physical memory protection address register 2  */
  CSR_PMPADDR3       = 0x3b3, /**< 0x3b3 - pmpaddr3  (r/w): Physical memory protection address register 3  */
  CSR_PMPADDR4       = 0x3b4, /**< 0x3b4 - pmpaddr4  (r/w): Physical memory protection address register 4  */
  CSR_PMPADDR5       = 0x3b5, /**< 0x3b5 - pmpaddr5  (r/w): Physical memory protection address register 5  */
  CSR_PMPADDR6       = 0x3b6, /**< 0x3b6 - pmpaddr6  (r/w): Physical memory protection address register 6  */
  CSR_PMPADDR7       = 0x3b7, /**< 0x3b7 - pmpaddr7  (r/w): Physical memory protection address register 7  */
  CSR_PMPADDR8       = 0x3b8, /**< 0x3b8 - pmpaddr8  (r/w): Physical memory protection address register 8  */
  CSR_PMPADDR9       = 0x3b9, /**< 0x3b9 - pmpaddr9  (r/w): Physical memory protection address register 9  */
  CSR_PMPADDR10      = 0x3ba, /**< 0x3ba - pmpaddr10 (r/w): Physical memory protection address register 10 */
  CSR_PMPADDR11      = 0x3bb, /**< 0x3bb - pmpaddr11 (r/w): Physical memory protection address register 11 */
  CSR_PMPADDR12      = 0x3bc, /**< 0x3bc - pmpaddr12 (r/w): Physical memory protection address register 12 */
  CSR_PMPADDR13      = 0x3bd, /**< 0x3bd - pmpaddr13 (r/w): Physical memory protection address register 13 */
  CSR_PMPADDR14      = 0x3be, /**< 0x3be - pmpaddr14 (r/w): Physical memory protection address register 14 */
  CSR_PMPADDR15      = 0x3bf, /**< 0x3bf - pmpaddr15 (r/w): Physical memory protection address register 15 */
  CSR_PMPADDR16      = 0x3c0, /**< 0x3c0 - pmpaddr16 (r/w): Physical memory protection address register 16 */
  CSR_PMPADDR17      = 0x3c1, /**< 0x3c1 - pmpaddr17 (r/w): Physical memory protection address register 17 */
  CSR_PMPADDR18      = 0x3c2, /**< 0x3c2 - pmpaddr18 (r/w): Physical memory protection address register 18 */
  CSR_PMPADDR19      = 0x3c3, /**< 0x3c3 - pmpaddr19 (r/w): Physical memory protection address register 19 */
  CSR_PMPADDR20      = 0x3c4, /**< 0x3c4 - pmpaddr20 (r/w): Physical memory protection address register 20 */
  CSR_PMPADDR21      = 0x3c5, /**< 0x3c5 - pmpaddr21 (r/w): Physical memory protection address register 21 */
  CSR_PMPADDR22      = 0x3c6, /**< 0x3c6 - pmpaddr22 (r/w): Physical memory protection address register 22 */
  CSR_PMPADDR23      = 0x3c7, /**< 0x3c7 - pmpaddr23 (r/w): Physical memory protection address register 23 */
  CSR_PMPADDR24      = 0x3c8, /**< 0x3c8 - pmpaddr24 (r/w): Physical memory protection address register 24 */
  CSR_PMPADDR25      = 0x3c9, /**< 0x3c9 - pmpaddr25 (r/w): Physical memory protection address register 25 */
  CSR_PMPADDR26      = 0x3ca, /**< 0x3ca - pmpaddr26 (r/w): Physical memory protection address register 26 */
  CSR_PMPADDR27      = 0x3cb, /**< 0x3cb - pmpaddr27 (r/w): Physical memory protection address register 27 */
  CSR_PMPADDR28      = 0x3cc, /**< 0x3cc - pmpaddr28 (r/w): Physical memory protection address register 28 */
  CSR_PMPADDR29      = 0x3cd, /**< 0x3cd - pmpaddr29 (r/w): Physical memory protection address register 29 */
  CSR_PMPADDR30      = 0x3ce, /**< 0x3ce - pmpaddr30 (r/w): Physical memory protection address register 30 */
  CSR_PMPADDR31      = 0x3cf, /**< 0x3cf - pmpaddr31 (r/w): Physical memory protection address register 31 */
  CSR_PMPADDR32      = 0x3d0, /**< 0x3d0 - pmpaddr32 (r/w): Physical memory protection address register 32 */
  CSR_PMPADDR33      = 0x3d1, /**< 0x3d1 - pmpaddr33 (r/w): Physical memory protection address register 33 */
  CSR_PMPADDR34      = 0x3d2, /**< 0x3d2 - pmpaddr34 (r/w): Physical memory protection address register 34 */
  CSR_PMPADDR35      = 0x3d3, /**< 0x3d3 - pmpaddr35 (r/w): Physical memory protection address register 35 */
  CSR_PMPADDR36      = 0x3d4, /**< 0x3d4 - pmpaddr36 (r/w): Physical memory protection address register 36 */
  CSR_PMPADDR37      = 0x3d5, /**< 0x3d5 - pmpaddr37 (r/w): Physical memory protection address register 37 */
  CSR_PMPADDR38      = 0x3d6, /**< 0x3d6 - pmpaddr38 (r/w): Physical memory protection address register 38 */
  CSR_PMPADDR39      = 0x3d7, /**< 0x3d7 - pmpaddr39 (r/w): Physical memory protection address register 39 */
  CSR_PMPADDR40      = 0x3d8, /**< 0x3d8 - pmpaddr40 (r/w): Physical memory protection address register 40 */
  CSR_PMPADDR41      = 0x3d9, /**< 0x3d9 - pmpaddr41 (r/w): Physical memory protection address register 41 */
  CSR_PMPADDR42      = 0x3da, /**< 0x3da - pmpaddr42 (r/w): Physical memory protection address register 42 */
  CSR_PMPADDR43      = 0x3db, /**< 0x3db - pmpaddr43 (r/w): Physical memory protection address register 43 */
  CSR_PMPADDR44      = 0x3dc, /**< 0x3dc - pmpaddr44 (r/w): Physical memory protection address register 44 */
  CSR_PMPADDR45      = 0x3dd, /**< 0x3dd - pmpaddr45 (r/w): Physical memory protection address register 45 */
  CSR_PMPADDR46      = 0x3de, /**< 0x3de - pmpaddr46 (r/w): Physical memory protection address register 46 */
  CSR_PMPADDR47      = 0x3df, /**< 0x3df - pmpaddr47 (r/w): Physical memory protection address register 47 */
  CSR_PMPADDR48      = 0x3e0, /**< 0x3e0 - pmpaddr48 (r/w): Physical memory protection address register 48 */
  CSR_PMPADDR49      = 0x3e1, /**< 0x3e1 - pmpaddr49 (r/w): Physical memory protection address register 49 */
  CSR_PMPADDR50      = 0x3e2, /**< 0x3e2 - pmpaddr50 (r/w): Physical memory protection address register 50 */
  CSR_PMPADDR51      = 0x3e3, /**< 0x3e3 - pmpaddr51 (r/w): Physical memory protection address register 51 */
  CSR_PMPADDR52      = 0x3e4, /**< 0x3e4 - pmpaddr52 (r/w): Physical memory protection address register 52 */
  CSR_PMPADDR53      = 0x3e5, /**< 0x3e5 - pmpaddr53 (r/w): Physical memory protection address register 53 */
  CSR_PMPADDR54      = 0x3e6, /**< 0x3e6 - pmpaddr54 (r/w): Physical memory protection address register 54 */
  CSR_PMPADDR55      = 0x3e7, /**< 0x3e7 - pmpaddr55 (r/w): Physical memory protection address register 55 */
  CSR_PMPADDR56      = 0x3e8, /**< 0x3e8 - pmpaddr56 (r/w): Physical memory protection address register 56 */
  CSR_PMPADDR57      = 0x3e9, /**< 0x3e9 - pmpaddr57 (r/w): Physical memory protection address register 57 */
  CSR_PMPADDR58      = 0x3ea, /**< 0x3ea - pmpaddr58 (r/w): Physical memory protection address register 58 */
  CSR_PMPADDR59      = 0x3eb, /**< 0x3eb - pmpaddr59 (r/w): Physical memory protection address register 59 */
  CSR_PMPADDR60      = 0x3ec, /**< 0x3ec - pmpaddr60 (r/w): Physical memory protection address register 60 */
  CSR_PMPADDR61      = 0x3ed, /**< 0x3ed - pmpaddr61 (r/w): Physical memory protection address register 61 */
  CSR_PMPADDR62      = 0x3ee, /**< 0x3ee - pmpaddr62 (r/w): Physical memory protection address register 62 */
  CSR_PMPADDR63      = 0x3ef, /**< 0x3ef - pmpaddr63 (r/w): Physical memory protection address register 63 */

  CSR_MCYCLE         = 0xb00, /**< 0xb00 - mcycle        (r/w): Machine cycle counter low word */
  CSR_MINSTRET       = 0xb02, /**< 0xb02 - minstret      (r/w): Machine instructions-retired counter low word */

  CSR_MHPMCOUNTER3   = 0xb03, /**< 0xb03 - mhpmcounter3  (r/w): Machine hardware performance monitor 3  counter low word */
  CSR_MHPMCOUNTER4   = 0xb04, /**< 0xb04 - mhpmcounter4  (r/w): Machine hardware performance monitor 4  counter low word */
  CSR_MHPMCOUNTER5   = 0xb05, /**< 0xb05 - mhpmcounter5  (r/w): Machine hardware performance monitor 5  counter low word */
  CSR_MHPMCOUNTER6   = 0xb06, /**< 0xb06 - mhpmcounter6  (r/w): Machine hardware performance monitor 6  counter low word */
  CSR_MHPMCOUNTER7   = 0xb07, /**< 0xb07 - mhpmcounter7  (r/w): Machine hardware performance monitor 7  counter low word */
  CSR_MHPMCOUNTER8   = 0xb08, /**< 0xb08 - mhpmcounter8  (r/w): Machine hardware performance monitor 8  counter low word */
  CSR_MHPMCOUNTER9   = 0xb09, /**< 0xb09 - mhpmcounter9  (r/w): Machine hardware performance monitor 9  counter low word */
  CSR_MHPMCOUNTER10  = 0xb0a, /**< 0xb0a - mhpmcounter10 (r/w): Machine hardware performance monitor 10 counter low word */
  CSR_MHPMCOUNTER11  = 0xb0b, /**< 0xb0b - mhpmcounter11 (r/w): Machine hardware performance monitor 11 counter low word */
  CSR_MHPMCOUNTER12  = 0xb0c, /**< 0xb0c - mhpmcounter12 (r/w): Machine hardware performance monitor 12 counter low word */
  CSR_MHPMCOUNTER13  = 0xb0d, /**< 0xb0d - mhpmcounter13 (r/w): Machine hardware performance monitor 13 counter low word */
  CSR_MHPMCOUNTER14  = 0xb0e, /**< 0xb0e - mhpmcounter14 (r/w): Machine hardware performance monitor 14 counter low word */
  CSR_MHPMCOUNTER15  = 0xb0f, /**< 0xb0f - mhpmcounter15 (r/w): Machine hardware performance monitor 15 counter low word */
  CSR_MHPMCOUNTER16  = 0xb10, /**< 0xb10 - mhpmcounter16 (r/w): Machine hardware performance monitor 16 counter low word */
  CSR_MHPMCOUNTER17  = 0xb11, /**< 0xb11 - mhpmcounter17 (r/w): Machine hardware performance monitor 17 counter low word */
  CSR_MHPMCOUNTER18  = 0xb12, /**< 0xb12 - mhpmcounter18 (r/w): Machine hardware performance monitor 18 counter low word */
  CSR_MHPMCOUNTER19  = 0xb13, /**< 0xb13 - mhpmcounter19 (r/w): Machine hardware performance monitor 19 counter low word */
  CSR_MHPMCOUNTER20  = 0xb14, /**< 0xb14 - mhpmcounter20 (r/w): Machine hardware performance monitor 20 counter low word */
  CSR_MHPMCOUNTER21  = 0xb15, /**< 0xb15 - mhpmcounter21 (r/w): Machine hardware performance monitor 21 counter low word */
  CSR_MHPMCOUNTER22  = 0xb16, /**< 0xb16 - mhpmcounter22 (r/w): Machine hardware performance monitor 22 counter low word */
  CSR_MHPMCOUNTER23  = 0xb17, /**< 0xb17 - mhpmcounter23 (r/w): Machine hardware performance monitor 23 counter low word */
  CSR_MHPMCOUNTER24  = 0xb18, /**< 0xb18 - mhpmcounter24 (r/w): Machine hardware performance monitor 24 counter low word */
  CSR_MHPMCOUNTER25  = 0xb19, /**< 0xb19 - mhpmcounter25 (r/w): Machine hardware performance monitor 25 counter low word */
  CSR_MHPMCOUNTER26  = 0xb1a, /**< 0xb1a - mhpmcounter26 (r/w): Machine hardware performance monitor 26 counter low word */
  CSR_MHPMCOUNTER27  = 0xb1b, /**< 0xb1b - mhpmcounter27 (r/w): Machine hardware performance monitor 27 counter low word */
  CSR_MHPMCOUNTER28  = 0xb1c, /**< 0xb1c - mhpmcounter28 (r/w): Machine hardware performance monitor 28 counter low word */
  CSR_MHPMCOUNTER29  = 0xb1d, /**< 0xb1d - mhpmcounter29 (r/w): Machine hardware performance monitor 29 counter low word */
  CSR_MHPMCOUNTER30  = 0xb1e, /**< 0xb1e - mhpmcounter30 (r/w): Machine hardware performance monitor 30 counter low word */
  CSR_MHPMCOUNTER31  = 0xb1f, /**< 0xb1f - mhpmcounter31 (r/w): Machine hardware performance monitor 31 counter low word */

  CSR_MCYCLEH        = 0xb80, /**< 0xb80 - mcycleh        (r/w): Machine cycle counter high word */
  CSR_MINSTRETH      = 0xb82, /**< 0xb82 - minstreth      (r/w): Machine instructions-retired counter high word */

  CSR_MHPMCOUNTER3H  = 0xb83, /**< 0xb83 - mhpmcounter3h  (r/w): Machine hardware performance monitor 3  counter high word */
  CSR_MHPMCOUNTER4H  = 0xb84, /**< 0xb84 - mhpmcounter4h  (r/w): Machine hardware performance monitor 4  counter high word */
  CSR_MHPMCOUNTER5H  = 0xb85, /**< 0xb85 - mhpmcounter5h  (r/w): Machine hardware performance monitor 5  counter high word */
  CSR_MHPMCOUNTER6H  = 0xb86, /**< 0xb86 - mhpmcounter6h  (r/w): Machine hardware performance monitor 6  counter high word */
  CSR_MHPMCOUNTER7H  = 0xb87, /**< 0xb87 - mhpmcounter7h  (r/w): Machine hardware performance monitor 7  counter high word */
  CSR_MHPMCOUNTER8H  = 0xb88, /**< 0xb88 - mhpmcounter8h  (r/w): Machine hardware performance monitor 8  counter high word */
  CSR_MHPMCOUNTER9H  = 0xb89, /**< 0xb89 - mhpmcounter9h  (r/w): Machine hardware performance monitor 9  counter high word */
  CSR_MHPMCOUNTER10H = 0xb8a, /**< 0xb8a - mhpmcounter10h (r/w): Machine hardware performance monitor 10 counter high word */
  CSR_MHPMCOUNTER11H = 0xb8b, /**< 0xb8b - mhpmcounter11h (r/w): Machine hardware performance monitor 11 counter high word */
  CSR_MHPMCOUNTER12H = 0xb8c, /**< 0xb8c - mhpmcounter12h (r/w): Machine hardware performance monitor 12 counter high word */
  CSR_MHPMCOUNTER13H = 0xb8d, /**< 0xb8d - mhpmcounter13h (r/w): Machine hardware performance monitor 13 counter high word */
  CSR_MHPMCOUNTER14H = 0xb8e, /**< 0xb8e - mhpmcounter14h (r/w): Machine hardware performance monitor 14 counter high word */
  CSR_MHPMCOUNTER15H = 0xb8f, /**< 0xb8f - mhpmcounter15h (r/w): Machine hardware performance monitor 15 counter high word */
  CSR_MHPMCOUNTER16H = 0xb90, /**< 0xb90 - mhpmcounter16h (r/w): Machine hardware performance monitor 16 counter high word */
  CSR_MHPMCOUNTER17H = 0xb91, /**< 0xb91 - mhpmcounter17h (r/w): Machine hardware performance monitor 17 counter high word */
  CSR_MHPMCOUNTER18H = 0xb92, /**< 0xb92 - mhpmcounter18h (r/w): Machine hardware performance monitor 18 counter high word */
  CSR_MHPMCOUNTER19H = 0xb93, /**< 0xb93 - mhpmcounter19h (r/w): Machine hardware performance monitor 19 counter high word */
  CSR_MHPMCOUNTER20H = 0xb94, /**< 0xb94 - mhpmcounter20h (r/w): Machine hardware performance monitor 20 counter high word */
  CSR_MHPMCOUNTER21H = 0xb95, /**< 0xb95 - mhpmcounter21h (r/w): Machine hardware performance monitor 21 counter high word */
  CSR_MHPMCOUNTER22H = 0xb96, /**< 0xb96 - mhpmcounter22h (r/w): Machine hardware performance monitor 22 counter high word */
  CSR_MHPMCOUNTER23H = 0xb97, /**< 0xb97 - mhpmcounter23h (r/w): Machine hardware performance monitor 23 counter high word */
  CSR_MHPMCOUNTER24H = 0xb98, /**< 0xb98 - mhpmcounter24h (r/w): Machine hardware performance monitor 24 counter high word */
  CSR_MHPMCOUNTER25H = 0xb99, /**< 0xb99 - mhpmcounter25h (r/w): Machine hardware performance monitor 25 counter high word */
  CSR_MHPMCOUNTER26H = 0xb9a, /**< 0xb9a - mhpmcounter26h (r/w): Machine hardware performance monitor 26 counter high word */
  CSR_MHPMCOUNTER27H = 0xb9b, /**< 0xb9b - mhpmcounter27h (r/w): Machine hardware performance monitor 27 counter high word */
  CSR_MHPMCOUNTER28H = 0xb9c, /**< 0xb9c - mhpmcounter28h (r/w): Machine hardware performance monitor 28 counter high word */
  CSR_MHPMCOUNTER29H = 0xb9d, /**< 0xb9d - mhpmcounter29h (r/w): Machine hardware performance monitor 29 counter high word */
  CSR_MHPMCOUNTER30H = 0xb9e, /**< 0xb9e - mhpmcounter30h (r/w): Machine hardware performance monitor 30 counter high word */
  CSR_MHPMCOUNTER31H = 0xb9f, /**< 0xb9f - mhpmcounter31h (r/w): Machine hardware performance monitor 31 counter high word */

  CSR_CYCLE          = 0xc00, /**< 0xc00 - cycle        (r/-): Cycle counter low word (from MCYCLE) */
  CSR_TIME           = 0xc01, /**< 0xc01 - time         (r/-): Timer low word (from MTIME.TIME_LO) */
  CSR_INSTRET        = 0xc02, /**< 0xc02 - instret      (r/-): Instructions-retired counter low word (from MINSTRET) */

  CSR_HPMCOUNTER3    = 0xc03, /**< 0xc03 - hpmcounter3  (r/w): Hardware performance monitor 3  counter low word */
  CSR_HPMCOUNTER4    = 0xc04, /**< 0xc04 - hpmcounter4  (r/w): Hardware performance monitor 4  counter low word */
  CSR_HPMCOUNTER5    = 0xc05, /**< 0xc05 - hpmcounter5  (r/w): Hardware performance monitor 5  counter low word */
  CSR_HPMCOUNTER6    = 0xc06, /**< 0xc06 - hpmcounter6  (r/w): Hardware performance monitor 6  counter low word */
  CSR_HPMCOUNTER7    = 0xc07, /**< 0xc07 - hpmcounter7  (r/w): Hardware performance monitor 7  counter low word */
  CSR_HPMCOUNTER8    = 0xc08, /**< 0xc08 - hpmcounter8  (r/w): Hardware performance monitor 8  counter low word */
  CSR_HPMCOUNTER9    = 0xc09, /**< 0xc09 - hpmcounter9  (r/w): Hardware performance monitor 9  counter low word */
  CSR_HPMCOUNTER10   = 0xc0a, /**< 0xc0a - hpmcounter10 (r/w): Hardware performance monitor 10 counter low word */
  CSR_HPMCOUNTER11   = 0xc0b, /**< 0xc0b - hpmcounter11 (r/w): Hardware performance monitor 11 counter low word */
  CSR_HPMCOUNTER12   = 0xc0c, /**< 0xc0c - hpmcounter12 (r/w): Hardware performance monitor 12 counter low word */
  CSR_HPMCOUNTER13   = 0xc0d, /**< 0xc0d - hpmcounter13 (r/w): Hardware performance monitor 13 counter low word */
  CSR_HPMCOUNTER14   = 0xc0e, /**< 0xc0e - hpmcounter14 (r/w): Hardware performance monitor 14 counter low word */
  CSR_HPMCOUNTER15   = 0xc0f, /**< 0xc0f - hpmcounter15 (r/w): Hardware performance monitor 15 counter low word */
  CSR_HPMCOUNTER16   = 0xc10, /**< 0xc10 - hpmcounter16 (r/w): Hardware performance monitor 16 counter low word */
  CSR_HPMCOUNTER17   = 0xc11, /**< 0xc11 - hpmcounter17 (r/w): Hardware performance monitor 17 counter low word */
  CSR_HPMCOUNTER18   = 0xc12, /**< 0xc12 - hpmcounter18 (r/w): Hardware performance monitor 18 counter low word */
  CSR_HPMCOUNTER19   = 0xc13, /**< 0xc13 - hpmcounter19 (r/w): Hardware performance monitor 19 counter low word */
  CSR_HPMCOUNTER20   = 0xc14, /**< 0xc14 - hpmcounter20 (r/w): Hardware performance monitor 20 counter low word */
  CSR_HPMCOUNTER21   = 0xc15, /**< 0xc15 - hpmcounter21 (r/w): Hardware performance monitor 21 counter low word */
  CSR_HPMCOUNTER22   = 0xc16, /**< 0xc16 - hpmcounter22 (r/w): Hardware performance monitor 22 counter low word */
  CSR_HPMCOUNTER23   = 0xc17, /**< 0xc17 - hpmcounter23 (r/w): Hardware performance monitor 23 counter low word */
  CSR_HPMCOUNTER24   = 0xc18, /**< 0xc18 - hpmcounter24 (r/w): Hardware performance monitor 24 counter low word */
  CSR_HPMCOUNTER25   = 0xc19, /**< 0xc19 - hpmcounter25 (r/w): Hardware performance monitor 25 counter low word */
  CSR_HPMCOUNTER26   = 0xc1a, /**< 0xc1a - hpmcounter26 (r/w): Hardware performance monitor 26 counter low word */
  CSR_HPMCOUNTER27   = 0xc1b, /**< 0xc1b - hpmcounter27 (r/w): Hardware performance monitor 27 counter low word */
  CSR_HPMCOUNTER28   = 0xc1c, /**< 0xc1c - hpmcounter28 (r/w): Hardware performance monitor 28 counter low word */
  CSR_HPMCOUNTER29   = 0xc1d, /**< 0xc1d - hpmcounter29 (r/w): Hardware performance monitor 29 counter low word */
  CSR_HPMCOUNTER30   = 0xc1e, /**< 0xc1e - hpmcounter30 (r/w): Hardware performance monitor 30 counter low word */
  CSR_HPMCOUNTER31   = 0xc1f, /**< 0xc1f - hpmcounter31 (r/w): Hardware performance monitor 31 counter low word */

  CSR_CYCLEH         = 0xc80, /**< 0xc80 - cycleh        (r/-): Cycle counter high word (from MCYCLEH) */
  CSR_TIMEH          = 0xc81, /**< 0xc81 - timeh         (r/-): Timer high word (from MTIME.TIME_HI) */
  CSR_INSTRETH       = 0xc82, /**< 0xc82 - instreth      (r/-): Instructions-retired counter high word (from MINSTRETH) */

  CSR_HPMCOUNTER3H   = 0xc83, /**< 0xc83 - hpmcounter3h  (r/w): Hardware performance monitor 3  counter high word */
  CSR_HPMCOUNTER4H   = 0xc84, /**< 0xc84 - hpmcounter4h  (r/w): Hardware performance monitor 4  counter high word */
  CSR_HPMCOUNTER5H   = 0xc85, /**< 0xc85 - hpmcounter5h  (r/w): Hardware performance monitor 5  counter high word */
  CSR_HPMCOUNTER6H   = 0xc86, /**< 0xc86 - hpmcounter6h  (r/w): Hardware performance monitor 6  counter high word */
  CSR_HPMCOUNTER7H   = 0xc87, /**< 0xc87 - hpmcounter7h  (r/w): Hardware performance monitor 7  counter high word */
  CSR_HPMCOUNTER8H   = 0xc88, /**< 0xc88 - hpmcounter8h  (r/w): Hardware performance monitor 8  counter high word */
  CSR_HPMCOUNTER9H   = 0xc89, /**< 0xc89 - hpmcounter9h  (r/w): Hardware performance monitor 9  counter high word */
  CSR_HPMCOUNTER10H  = 0xc8a, /**< 0xc8a - hpmcounter10h (r/w): Hardware performance monitor 10 counter high word */
  CSR_HPMCOUNTER11H  = 0xc8b, /**< 0xc8b - hpmcounter11h (r/w): Hardware performance monitor 11 counter high word */
  CSR_HPMCOUNTER12H  = 0xc8c, /**< 0xc8c - hpmcounter12h (r/w): Hardware performance monitor 12 counter high word */
  CSR_HPMCOUNTER13H  = 0xc8d, /**< 0xc8d - hpmcounter13h (r/w): Hardware performance monitor 13 counter high word */
  CSR_HPMCOUNTER14H  = 0xc8e, /**< 0xc8e - hpmcounter14h (r/w): Hardware performance monitor 14 counter high word */
  CSR_HPMCOUNTER15H  = 0xc8f, /**< 0xc8f - hpmcounter15h (r/w): Hardware performance monitor 15 counter high word */
  CSR_HPMCOUNTER16H  = 0xc90, /**< 0xc90 - hpmcounter16h (r/w): Hardware performance monitor 16 counter high word */
  CSR_HPMCOUNTER17H  = 0xc91, /**< 0xc91 - hpmcounter17h (r/w): Hardware performance monitor 17 counter high word */
  CSR_HPMCOUNTER18H  = 0xc92, /**< 0xc92 - hpmcounter18h (r/w): Hardware performance monitor 18 counter high word */
  CSR_HPMCOUNTER19H  = 0xc93, /**< 0xc93 - hpmcounter19h (r/w): Hardware performance monitor 19 counter high word */
  CSR_HPMCOUNTER20H  = 0xc94, /**< 0xc94 - hpmcounter20h (r/w): Hardware performance monitor 20 counter high word */
  CSR_HPMCOUNTER21H  = 0xc95, /**< 0xc95 - hpmcounter21h (r/w): Hardware performance monitor 21 counter high word */
  CSR_HPMCOUNTER22H  = 0xc96, /**< 0xc96 - hpmcounter22h (r/w): Hardware performance monitor 22 counter high word */
  CSR_HPMCOUNTER23H  = 0xc97, /**< 0xc97 - hpmcounter23h (r/w): Hardware performance monitor 23 counter high word */
  CSR_HPMCOUNTER24H  = 0xc98, /**< 0xc98 - hpmcounter24h (r/w): Hardware performance monitor 24 counter high word */
  CSR_HPMCOUNTER25H  = 0xc99, /**< 0xc99 - hpmcounter25h (r/w): Hardware performance monitor 25 counter high word */
  CSR_HPMCOUNTER26H  = 0xc9a, /**< 0xc9a - hpmcounter26h (r/w): Hardware performance monitor 26 counter high word */
  CSR_HPMCOUNTER27H  = 0xc9b, /**< 0xc9b - hpmcounter27h (r/w): Hardware performance monitor 27 counter high word */
  CSR_HPMCOUNTER28H  = 0xc9c, /**< 0xc9c - hpmcounter28h (r/w): Hardware performance monitor 28 counter high word */
  CSR_HPMCOUNTER29H  = 0xc9d, /**< 0xc9d - hpmcounter29h (r/w): Hardware performance monitor 29 counter high word */
  CSR_HPMCOUNTER30H  = 0xc9e, /**< 0xc9e - hpmcounter30h (r/w): Hardware performance monitor 30 counter high word */
  CSR_HPMCOUNTER31H  = 0xc9f, /**< 0xc9f - hpmcounter31h (r/w): Hardware performance monitor 31 counter high word */

  CSR_MVENDORID      = 0xf11, /**< 0xf11 - mvendorid (r/-): Vendor ID */
  CSR_MARCHID        = 0xf12, /**< 0xf12 - marchid   (r/-): Architecture ID */
  CSR_MIMPID         = 0xf13, /**< 0xf13 - mimpid    (r/-): Implementation ID/version */
  CSR_MHARTID        = 0xf14, /**< 0xf14 - mhartid   (r/-): Hardware thread ID (always 0) */

  CSR_MZEXT          = 0xfc0  /**< 0xfc0 - mzext (custom CSR) (r/-): Available Z* CPU extensions */
};


/**********************************************************************//**
 * CPU <b>mstatus</b> CSR (r/w): Machine status (RISC-V spec.)
 **************************************************************************/
enum NEORV32_CSR_MSTATUS_enum {
  CSR_MSTATUS_MIE   =  3, /**< CPU mstatus CSR  (3): MIE - Machine interrupt enable bit (r/w) */
  CSR_MSTATUS_UBE   =  6, /**< CPU mstatus CSR  (6): UBE - User-mode endianness (little-endian=0, big-endian=1) (r/-) */
  CSR_MSTATUS_MPIE  =  7, /**< CPU mstatus CSR  (7): MPIE - Machine previous interrupt enable bit (r/w) */
  CSR_MSTATUS_MPP_L = 11, /**< CPU mstatus CSR (11): MPP_L - Machine previous privilege mode bit low (r/w) */
  CSR_MSTATUS_MPP_H = 12  /**< CPU mstatus CSR (12): MPP_H - Machine previous privilege mode bit high (r/w) */
};


/**********************************************************************//**
 * CPU <b>mstatush</b> CSR (r/-): Machine status - high word (RISC-V spec.)
 **************************************************************************/
enum NEORV32_CSR_MSTATUSH_enum {
  CSR_MSTATUSH_MBE = 5 /**< CPU mstatush CSR (5): MBE - Machine-mode endianness (little-endian=0, big-endian=1) (r/-) */
};


/**********************************************************************//**
 * CPU <b>mcounteren</b> CSR (r/w): Machine counter enable (RISC-V spec.)
 **************************************************************************/
enum NEORV32_CSR_MCOUNTEREN_enum {
  CSR_MCOUNTEREN_CY = 0, /**< CPU mcounteren CSR (0): CY - Allow access to cycle[h] CSRs from U-mode when set (r/w) */
  CSR_MCOUNTEREN_TM = 1, /**< CPU mcounteren CSR (1): TM - Allow access to time[h] CSRs from U-mode when set (r/w) */
  CSR_MCOUNTEREN_IR = 2  /**< CPU mcounteren CSR (2): IR - Allow access to instret[h] CSRs from U-mode when set (r/w) */
};


/**********************************************************************//**
 * CPU <b>mcountinhibit</b> CSR (r/w): Machine counter-inhibit (RISC-V spec.)
 **************************************************************************/
enum NEORV32_CSR_MCOUNTINHIBIT_enum {
  CSR_MCOUNTINHIBIT_CY = 0, /**< CPU mcountinhibit CSR (0): CY - Enable auto-increment of [m]cycle[h] CSR when set (r/w) */
  CSR_MCOUNTINHIBIT_IR = 2  /**< CPU mcountinhibit CSR (2): IR - Enable auto-increment of [m]instret[h] CSR when set (r/w) */
};


/**********************************************************************//**
 * CPU <b>mie</b> CSR (r/w): Machine interrupt enable (RISC-V spec.)
 **************************************************************************/
enum NEORV32_CSR_MIE_enum {
  CSR_MIE_MSIE   =  3, /**< CPU mie CSR  (3): MSIE - Machine software interrupt enable (r/w) */
  CSR_MIE_MTIE   =  7, /**< CPU mie CSR  (7): MTIE - Machine timer interrupt enable bit (r/w) */
  CSR_MIE_MEIE   = 11, /**< CPU mie CSR (11): MEIE - Machine external interrupt enable bit (r/w) */
  CSR_MIE_FIRQ0E = 16, /**< CPU mie CSR (16): FIRQ0E - Fast interrupt channel 0 enable bit (r/w) */
  CSR_MIE_FIRQ1E = 17, /**< CPU mie CSR (17): FIRQ1E - Fast interrupt channel 1 enable bit (r/w) */
  CSR_MIE_FIRQ2E = 18, /**< CPU mie CSR (18): FIRQ2E - Fast interrupt channel 2 enable bit (r/w) */
  CSR_MIE_FIRQ3E = 19, /**< CPU mie CSR (19): FIRQ3E - Fast interrupt channel 3 enable bit (r/w) */
  CSR_MIE_FIRQ4E = 20, /**< CPU mie CSR (20): FIRQ4E - Fast interrupt channel 4 enable bit (r/w) */
  CSR_MIE_FIRQ5E = 21, /**< CPU mie CSR (21): FIRQ5E - Fast interrupt channel 5 enable bit (r/w) */
  CSR_MIE_FIRQ6E = 22, /**< CPU mie CSR (22): FIRQ6E - Fast interrupt channel 6 enable bit (r/w) */
  CSR_MIE_FIRQ7E = 23  /**< CPU mie CSR (23): FIRQ7E - Fast interrupt channel 7 enable bit (r/w) */
};


/**********************************************************************//**
 * CPU <b>mip</b> CSR (r/-): Machine interrupt pending (RISC-V spec.)
 **************************************************************************/
enum NEORV32_CSR_MIP_enum {
  CSR_MIP_MSIP   =  3, /**< CPU mip CSR  (3): MSIP - Machine software interrupt pending (r/-) */
  CSR_MIP_MTIP   =  7, /**< CPU mip CSR  (7): MTIP - Machine timer interrupt pending (r/-) */
  CSR_MIP_MEIP   = 11, /**< CPU mip CSR (11): MEIP - Machine external interrupt pending (r/-) */

  CSR_MIP_FIRQ0P = 16, /**< CPU mip CSR (16): FIRQ0P - Fast interrupt channel 0 pending (r/-) */
  CSR_MIP_FIRQ1P = 17, /**< CPU mip CSR (17): FIRQ1P - Fast interrupt channel 1 pending (r/-) */
  CSR_MIP_FIRQ2P = 18, /**< CPU mip CSR (18): FIRQ2P - Fast interrupt channel 2 pending (r/-) */
  CSR_MIP_FIRQ3P = 19, /**< CPU mip CSR (19): FIRQ3P - Fast interrupt channel 3 pending (r/-) */
  CSR_MIP_FIRQ4P = 20, /**< CPU mip CSR (20): FIRQ4P - Fast interrupt channel 4 pending (r/-) */
  CSR_MIP_FIRQ5P = 21, /**< CPU mip CSR (21): FIRQ5P - Fast interrupt channel 5 pending (r/-) */
  CSR_MIP_FIRQ6P = 22, /**< CPU mip CSR (22): FIRQ6P - Fast interrupt channel 6 pending (r/-) */
  CSR_MIP_FIRQ7P = 23  /**< CPU mip CSR (23): FIRQ7P - Fast interrupt channel 7 pending (r/-) */
};


/**********************************************************************//**
 * CPU <b>misa</b> CSR (r/-): Machine instruction set extensions (RISC-V spec.)
 **************************************************************************/
enum NEORV32_CSR_MISA_enum {
  CSR_MISA_A_EXT      =  0, /**< CPU misa CSR  (0): A: Atomic instructions CPU extension available (r/-)*/
  CSR_MISA_B_EXT      =  1, /**< CPU misa CSR  (1): B: Bit manipulation CPU extension available (r/-)*/
  CSR_MISA_C_EXT      =  2, /**< CPU misa CSR  (2): C: Compressed instructions CPU extension available (r/-)*/
  CSR_MISA_E_EXT      =  4, /**< CPU misa CSR  (4): E: Embedded CPU extension available (r/-) */
  CSR_MISA_I_EXT      =  8, /**< CPU misa CSR  (8): I: Base integer ISA CPU extension available (r/-) */
  CSR_MISA_M_EXT      = 12, /**< CPU misa CSR (12): M: Multiplier/divider CPU extension available (r/-)*/
  CSR_MISA_U_EXT      = 20, /**< CPU misa CSR (20): U: User mode CPU extension available (r/-)*/
  CSR_MISA_X_EXT      = 23, /**< CPU misa CSR (23): X: Non-standard CPU extension available (r/-) */
  CSR_MISA_MXL_LO_EXT = 30, /**< CPU misa CSR (30): MXL.lo: CPU data width (r/-) */
  CSR_MISA_MXL_HI_EXT = 31  /**< CPU misa CSR (31): MXL.Hi: CPU data width (r/-) */
};


/**********************************************************************//**
 * CPU <b>mzext</b> custom CSR (r/-): Implemented Z* CPU extensions
 **************************************************************************/
enum NEORV32_CSR_MZEXT_enum {
  CSR_MZEXT_ZICSR    = 0, /**< CPU mzext CSR (0): Zicsr extension available when set (r/-) */
  CSR_MZEXT_ZIFENCEI = 1, /**< CPU mzext CSR (1): Zifencei extension available when set (r/-) */
  CSR_MZEXT_ZBB      = 2  /**< CPU mzext CSR (2): Zbb extension available when set (r/-) */
};


/**********************************************************************//**
 * CPU <b>mhpmevent</b> hardware performance monitor events
 **************************************************************************/
enum NEORV32_HPMCNT_EVENT_enum {
  HPMCNT_EVENT_CY      = 0,  /**< CPU mhpmevent CSR (0):  Active cycle */
  HPMCNT_EVENT_IR      = 2,  /**< CPU mhpmevent CSR (2):  Retired instruction */

  HPMCNT_EVENT_CIR     = 3,  /**< CPU mhpmevent CSR (3):  Retired compressed instruction */
  HPMCNT_EVENT_WAIT_IF = 4,  /**< CPU mhpmevent CSR (4):  Instruction fetch memory wait cycle */
  HPMCNT_EVENT_WAIT_II = 5,  /**< CPU mhpmevent CSR (5):  Instruction issue wait cycle */
  HPMCNT_EVENT_WAIT_MC = 6,  /**< CPU mhpmevent CSR (6):  Multi-cycle ALU-operation wait cycle */
  HPMCNT_EVENT_LOAD    = 7,  /**< CPU mhpmevent CSR (7):  Load operation */
  HPMCNT_EVENT_STORE   = 8,  /**< CPU mhpmevent CSR (8):  Store operation */
  HPMCNT_EVENT_WAIT_LS = 9,  /**< CPU mhpmevent CSR (9):  Load/store memory wait cycle */

  HPMCNT_EVENT_JUMP    = 10, /**< CPU mhpmevent CSR (10): Unconditional jump */
  HPMCNT_EVENT_BRANCH  = 11, /**< CPU mhpmevent CSR (11): Conditional branch (taken or not taken) */
  HPMCNT_EVENT_TBRANCH = 12, /**< CPU mhpmevent CSR (12): Conditional taken branch */

  HPMCNT_EVENT_TRAP    = 13, /**< CPU mhpmevent CSR (13): Entered trap */
  HPMCNT_EVENT_ILLEGAL = 14  /**< CPU mhpmevent CSR (14): Illegal instruction exception */
};


/**********************************************************************//**
 * Trap codes from mcause CSR.
 **************************************************************************/
enum NEORV32_EXCEPTION_CODES_enum {
  TRAP_CODE_I_MISALIGNED = 0x00000000, /**< 0.0:  Instruction address misaligned */
  TRAP_CODE_I_ACCESS     = 0x00000001, /**< 0.1:  Instruction (bus) access fault */
  TRAP_CODE_I_ILLEGAL    = 0x00000002, /**< 0.2:  Illegal instruction */
  TRAP_CODE_BREAKPOINT   = 0x00000003, /**< 0.3:  Breakpoint (EBREAK instruction) */
  TRAP_CODE_L_MISALIGNED = 0x00000004, /**< 0.4:  Load address misaligned */
  TRAP_CODE_L_ACCESS     = 0x00000005, /**< 0.5:  Load (bus) access fault */
  TRAP_CODE_S_MISALIGNED = 0x00000006, /**< 0.6:  Store address misaligned */
  TRAP_CODE_S_ACCESS     = 0x00000007, /**< 0.7:  Store (bus) access fault */
  TRAP_CODE_UENV_CALL    = 0x00000008, /**< 0.8:  Environment call from user mode (ECALL instruction) */
  TRAP_CODE_MENV_CALL    = 0x0000000b, /**< 0.11: Environment call from machine mode (ECALL instruction) */
  TRAP_CODE_RESET        = 0x80000000, /**< 1.0:  Hardware reset */
  TRAP_CODE_MSI          = 0x80000003, /**< 1.3:  Machine software interrupt */
  TRAP_CODE_MTI          = 0x80000007, /**< 1.7:  Machine timer interrupt */
  TRAP_CODE_MEI          = 0x8000000b, /**< 1.11: Machine external interrupt */
  TRAP_CODE_FIRQ_0       = 0x80000010, /**< 1.16: Fast interrupt channel 0 */
  TRAP_CODE_FIRQ_1       = 0x80000011, /**< 1.17: Fast interrupt channel 1 */
  TRAP_CODE_FIRQ_2       = 0x80000012, /**< 1.18: Fast interrupt channel 2 */
  TRAP_CODE_FIRQ_3       = 0x80000013, /**< 1.19: Fast interrupt channel 3 */
  TRAP_CODE_FIRQ_4       = 0x80000014, /**< 1.20: Fast interrupt channel 4 */
  TRAP_CODE_FIRQ_5       = 0x80000015, /**< 1.21: Fast interrupt channel 5 */
  TRAP_CODE_FIRQ_6       = 0x80000016, /**< 1.22: Fast interrupt channel 6 */
  TRAP_CODE_FIRQ_7       = 0x80000017  /**< 1.23: Fast interrupt channel 7 */
};


/**********************************************************************//**
 * Processor clock prescalers 
 **************************************************************************/
enum NEORV32_CLOCK_PRSC_enum {
  CLK_PRSC_2    = 0, /**< CPU_CLK (from clk_i top signal) / 2 */
  CLK_PRSC_4    = 1, /**< CPU_CLK (from clk_i top signal) / 4 */
  CLK_PRSC_8    = 2, /**< CPU_CLK (from clk_i top signal) / 8 */
  CLK_PRSC_64   = 3, /**< CPU_CLK (from clk_i top signal) / 64 */
  CLK_PRSC_128  = 4, /**< CPU_CLK (from clk_i top signal) / 128 */
  CLK_PRSC_1024 = 5, /**< CPU_CLK (from clk_i top signal) / 1024 */
  CLK_PRSC_2048 = 6, /**< CPU_CLK (from clk_i top signal) / 2048 */
  CLK_PRSC_4096 = 7  /**< CPU_CLK (from clk_i top signal) / 4096 */
};


/**********************************************************************//**
 * Official NEORV32 >RISC-V open-source architecture ID<
 * https://github.com/riscv/riscv-isa-manual/blob/master/marchid.md
 **************************************************************************/
#define NEORV32_ARCHID 19


/**********************************************************************//**
 * @name Helper macros for easy memory-mapped register access
 **************************************************************************/
/**@{*/
/** memory-mapped byte (8-bit) read/write register */
#define IO_REG8  (volatile uint8_t*)
/** memory-mapped half-word (16-bit) read/write register */
#define IO_REG16 (volatile uint16_t*)
/** memory-mapped word (32-bit) read/write register */
#define IO_REG32 (volatile uint32_t*)
/** memory-mapped double-word (64-bit) read/write register */
#define IO_REG64 (volatile uint64_t*)
/** memory-mapped byte (8-bit) read-only register */
#define IO_ROM8  (const volatile uint8_t*) 
/** memory-mapped half-word (16-bit) read-only register */
#define IO_ROM16 (const volatile uint16_t*)
/** memory-mapped word (32-bit) read-only register */
#define IO_ROM32 (const volatile uint32_t*)
/** memory-mapped double-word (64-bit) read-only register */
#define IO_ROM64 (const volatile uint64_t*)
/**@}*/


/**********************************************************************//**
 * @name Address space sections
 **************************************************************************/
/**@{*/
/** instruction memory base address (r/w/x) */
// -> configured via ispace_base_c constant in neorv32_package.vhd and available to SW via SYSCONFIG entry
/** data memory base address (r/w/x) */
// -> configured via dspace_base_c constant in neorv32_package.vhd and available to SW via SYSCONFIG entry
/** bootloader memory base address (r/-/x) */
#define BOOTLOADER_BASE_ADDRESS (0xFFFF0000UL)
/** peripheral/IO devices memory base address (r/w/x) */
#define IO_BASE_ADDRESS (0xFFFFFF00UL)
/**@}*/


/**********************************************************************//**
 * @name IO Device: Custom Functions Subsystem (CFS)
 **************************************************************************/
/**@{*/
/** custom CFS register 0 */
#define CFS_REG_0  (*(IO_REG32 0xFFFFFF00UL)) // /**< (r)/(w): CFS register 0, user-defined */
/** custom CFS register 1 */
#define CFS_REG_1  (*(IO_REG32 0xFFFFFF04UL)) // /**< (r)/(w): CFS register 1, user-defined */
/** custom CFS register 2 */
#define CFS_REG_2  (*(IO_REG32 0xFFFFFF08UL)) // /**< (r)/(w): CFS register 2, user-defined */
/** custom CFS register 3 */
#define CFS_REG_3  (*(IO_REG32 0xFFFFFF0CUL)) // /**< (r)/(w): CFS register 3, user-defined */
/** custom CFS register 4 */
#define CFS_REG_4  (*(IO_REG32 0xFFFFFF10UL)) // /**< (r)/(w): CFS register 4, user-defined */
/** custom CFS register 5 */
#define CFS_REG_5  (*(IO_REG32 0xFFFFFF14UL)) // /**< (r)/(w): CFS register 5, user-defined */
/** custom CFS register 6 */
#define CFS_REG_6  (*(IO_REG32 0xFFFFFF18UL)) // /**< (r)/(w): CFS register 6, user-defined */
/** custom CFS register 7 */
#define CFS_REG_7  (*(IO_REG32 0xFFFFFF1CUL)) // /**< (r)/(w): CFS register 7, user-defined */
/** custom CFS register 8 */
#define CFS_REG_8  (*(IO_REG32 0xFFFFFF20UL)) // /**< (r)/(w): CFS register 8, user-defined */
/** custom CFS register 9 */
#define CFS_REG_9  (*(IO_REG32 0xFFFFFF24UL)) // /**< (r)/(w): CFS register 9, user-defined */
/** custom CFS register 10 */
#define CFS_REG_10 (*(IO_REG32 0xFFFFFF28UL)) // /**< (r)/(w): CFS register 10, user-defined */
/** custom CFS register 11 */
#define CFS_REG_11 (*(IO_REG32 0xFFFFFF2CUL)) // /**< (r)/(w): CFS register 11, user-defined */
/** custom CFS register 12 */
#define CFS_REG_12 (*(IO_REG32 0xFFFFFF30UL)) // /**< (r)/(w): CFS register 12, user-defined */
/** custom CFS register 13 */
#define CFS_REG_13 (*(IO_REG32 0xFFFFFF34UL)) // /**< (r)/(w): CFS register 13, user-defined */
/** custom CFS register 14 */
#define CFS_REG_14 (*(IO_REG32 0xFFFFFF38UL)) // /**< (r)/(w): CFS register 14, user-defined */
/** custom CFS register 15 */
#define CFS_REG_15 (*(IO_REG32 0xFFFFFF3CUL)) // /**< (r)/(w): CFS register 15, user-defined */
/** custom CFS register 16 */
#define CFS_REG_16 (*(IO_REG32 0xFFFFFF40UL)) // /**< (r)/(w): CFS register 16, user-defined */
/** custom CFS register 17 */
#define CFS_REG_17 (*(IO_REG32 0xFFFFFF44UL)) // /**< (r)/(w): CFS register 17, user-defined */
/** custom CFS register 18 */
#define CFS_REG_18 (*(IO_REG32 0xFFFFFF48UL)) // /**< (r)/(w): CFS register 18, user-defined */
/** custom CFS register 19 */
#define CFS_REG_19 (*(IO_REG32 0xFFFFFF4CUL)) // /**< (r)/(w): CFS register 19, user-defined */
/** custom CFS register 20 */
#define CFS_REG_20 (*(IO_REG32 0xFFFFFF50UL)) // /**< (r)/(w): CFS register 20, user-defined */
/** custom CFS register 21 */
#define CFS_REG_21 (*(IO_REG32 0xFFFFFF54UL)) // /**< (r)/(w): CFS register 21, user-defined */
/** custom CFS register 22 */
#define CFS_REG_22 (*(IO_REG32 0xFFFFFF58UL)) // /**< (r)/(w): CFS register 22, user-defined */
/** custom CFS register 23 */
#define CFS_REG_23 (*(IO_REG32 0xFFFFFF5CUL)) // /**< (r)/(w): CFS register 23, user-defined */
/** custom CFS register 24 */
#define CFS_REG_24 (*(IO_REG32 0xFFFFFF60UL)) // /**< (r)/(w): CFS register 24, user-defined */
/** custom CFS register 25 */
#define CFS_REG_25 (*(IO_REG32 0xFFFFFF64UL)) // /**< (r)/(w): CFS register 25, user-defined */
/** custom CFS register 26 */
#define CFS_REG_26 (*(IO_REG32 0xFFFFFF68UL)) // /**< (r)/(w): CFS register 26, user-defined */
/** custom CFS register 27 */
#define CFS_REG_27 (*(IO_REG32 0xFFFFFF6CUL)) // /**< (r)/(w): CFS register 27, user-defined */
/** custom CFS register 28 */
#define CFS_REG_28 (*(IO_REG32 0xFFFFFF70UL)) // /**< (r)/(w): CFS register 28, user-defined */
/** custom CFS register 29 */
#define CFS_REG_29 (*(IO_REG32 0xFFFFFF74UL)) // /**< (r)/(w): CFS register 29, user-defined */
/** custom CFS register 30 */
#define CFS_REG_30 (*(IO_REG32 0xFFFFFF78UL)) // /**< (r)/(w): CFS register 30, user-defined */
/** custom CFS register 31 */
#define CFS_REG_31 (*(IO_REG32 0xFFFFFF7CUL)) // /**< (r)/(w): CFS register 31, user-defined */
/**@}*/


/**********************************************************************//**
 * @name IO Device: General Purpose Input/Output Port Unit (GPIO)
 **************************************************************************/
/**@{*/
/** read access: GPIO parallel input port 32-bit (r/-), write_access: pin-change IRQ for each input pin (-/w) */
#define GPIO_INPUT  (*(IO_REG32 0xFFFFFF80UL))
/** GPIO parallel output port 32-bit (r/w) */
#define GPIO_OUTPUT (*(IO_REG32 0xFFFFFF84UL))
/**@}*/


/**********************************************************************//**
 * @name IO Device: True Random Number Generator (TRNG)
 **************************************************************************/
/**@{*/
/** TRNG control/data register (r/w) */
#define TRNG_CT (*(IO_REG32 0xFFFFFF88UL))

/** TRNG control/data register bits */
enum NEORV32_TRNG_CT_enum {
  TRNG_CT_DATA_LSB =  0, /**< TRNG data/control register(0)  (r/-): Random data byte LSB */
  TRNG_CT_DATA_MSB =  7, /**< TRNG data/control register(7)  (r/-): Random data byte MSB */

  TRNG_CT_EN       = 30, /**< TRNG data/control register(30) (r/w): TRNG enable */
  TRNG_CT_VALID    = 31  /**< TRNG data/control register(31) (r/-): Random data output valid */
};
/**@}*/


/**********************************************************************//**
 * @name IO Device: Watchdog Timer (WDT)
 **************************************************************************/
/**@{*/
/** Watchdog control register (r/w) */
#define WDT_CT (*(IO_REG32 0xFFFFFF8CUL))

/** WTD control register bits */
enum NEORV32_WDT_CT_enum {
  WDT_CT_EN       = 0, /**< WDT control register(0) (r/w): Watchdog enable */
  WDT_CT_CLK_SEL0 = 1, /**< WDT control register(1) (r/w): Clock prescaler select bit 0 */
  WDT_CT_CLK_SEL1 = 2, /**< WDT control register(2) (r/w): Clock prescaler select bit 1 */
  WDT_CT_CLK_SEL2 = 3, /**< WDT control register(3) (r/w): Clock prescaler select bit 2 */
  WDT_CT_MODE     = 4, /**< WDT control register(4) (r/w): Watchdog mode: 0=timeout causes interrupt, 1=timeout causes processor reset */
  WDT_CT_RCAUSE   = 5, /**< WDT control register(5) (r/-): Cause of last system reset: 0=external reset, 1=watchdog */
  WDT_CT_RESET    = 6, /**< WDT control register(6) (-/w): Reset WDT counter when set, auto-clears */
  WDT_CT_FORCE    = 7, /**< WDT control register(7) (-/w): Force WDT action, auto-clears */
  WDT_CT_LOCK     = 8  /**< WDT control register(8) (r/w): Lock write access to control register, clears on reset (HW or WDT) only */
};
/**@}*/


/**********************************************************************//**
 * @name IO Device: Machine System Timer (MTIME)
 **************************************************************************/
/**@{*/
/** MTIME (time register) low word (r/w) */
#define MTIME_LO     (*(IO_REG32 0xFFFFFF90UL))
/** MTIME (time register) high word (r/w) */
#define MTIME_HI     (*(IO_REG32 0xFFFFFF94UL))
/** MTIMECMP (time compare register) low word (r/w) */
#define MTIMECMP_LO  (*(IO_REG32 0xFFFFFF98UL))
/** MTIMECMP (time register) high word (r/w) */
#define MTIMECMP_HI  (*(IO_REG32 0xFFFFFF9CUL))

/** MTIME (time register) 64-bit access (r/w) */
#define MTIME        (*(IO_REG64 (&MTIME_LO)))
/** MTIMECMP (time compare register) low word (r/w) */
#define MTIMECMP     (*(IO_REG64 (&MTIMECMP_LO)))
/**@}*/


/**********************************************************************//**
 * @name IO Device: Universal Asynchronous Receiver and Transmitter (UART)
 **************************************************************************/
/**@{*/
/** UART control register (r/w) */
#define UART_CT  (*(IO_REG32 0xFFFFFFA0UL))
/** UART receive/transmit data register (r/w) */
#define UART_DATA (*(IO_REG32 0xFFFFFFA4UL))

/** UART control register bits */
enum NEORV32_UART_CT_enum {
  UART_CT_BAUD00   =  0, /**< UART control register(0)  (r/w): BAUD rate config value lsb (12-bi, bit 0) */
  UART_CT_BAUD01   =  1, /**< UART control register(1)  (r/w): BAUD rate config value (12-bi, bit 1) */
  UART_CT_BAUD02   =  2, /**< UART control register(2)  (r/w): BAUD rate config value (12-bi, bit 2) */
  UART_CT_BAUD03   =  3, /**< UART control register(3)  (r/w): BAUD rate config value (12-bi, bit 3) */
  UART_CT_BAUD04   =  4, /**< UART control register(4)  (r/w): BAUD rate config value (12-bi, bit 4) */
  UART_CT_BAUD05   =  5, /**< UART control register(5)  (r/w): BAUD rate config value (12-bi, bit 4) */
  UART_CT_BAUD06   =  6, /**< UART control register(6)  (r/w): BAUD rate config value (12-bi, bit 5) */
  UART_CT_BAUD07   =  7, /**< UART control register(7)  (r/w): BAUD rate config value (12-bi, bit 6) */
  UART_CT_BAUD08   =  8, /**< UART control register(8)  (r/w): BAUD rate config value (12-bi, bit 7) */
  UART_CT_BAUD09   =  9, /**< UART control register(9)  (r/w): BAUD rate config value (12-bi, bit 8) */
  UART_CT_BAUD10   = 10, /**< UART control register(10) (r/w): BAUD rate config value (12-bi, bit 9) */
  UART_CT_BAUD11   = 11, /**< UART control register(11) (r/w): BAUD rate config value msb (12-bi, bit 0) */

  UART_CT_SIM_MODE = 12, /**< UART control register(12) (r/w): Simulation output override enable, for use in simulation only */

  UART_CT_PMODE0   = 22, /**< UART control register(22) (r/w): Parity configuration (0=even; 1=odd) */
  UART_CT_PMODE1   = 23, /**< UART control register(23) (r/w): Parity bit enabled when set */
  UART_CT_PRSC0    = 24, /**< UART control register(24) (r/w): BAUD rate clock prescaler select bit 0 */
  UART_CT_PRSC1    = 25, /**< UART control register(25) (r/w): BAUD rate clock prescaler select bit 1 */
  UART_CT_PRSC2    = 26, /**< UART control register(26) (r/w): BAUD rate clock prescaler select bit 2 */

  UART_CT_EN       = 28, /**< UART control register(28) (r/w): UART global enable */
  UART_CT_RX_IRQ   = 29, /**< UART control register(29) (r/w): Activate interrupt on RX done */
  UART_CT_TX_IRQ   = 30, /**< UART control register(30) (r/w): Activate interrupt on TX done */
  UART_CT_TX_BUSY  = 31  /**< UART control register(31) (r/-): Transmitter is busy when set */
};

/** UART receive/transmit data register bits */
enum NEORV32_UART_DATA_enum {
  UART_DATA_LSB   =  0, /**< UART receive/transmit data register(0)  (r/w): Receive/transmit data LSB (bit 0) */
  UART_DATA_MSB   =  7, /**< UART receive/transmit data register(7)  (r/w): Receive/transmit data MSB (bit 7) */

  UART_DATA_PERR  = 28, /**< UART receive/transmit data register(18) (r/-): RX parity error detected when set */
  UART_DATA_FERR  = 29, /**< UART receive/transmit data register(29) (r/-): RX frame error (not valid stop bit) wdetected when set */
  UART_DATA_OVERR = 30, /**< UART receive/transmit data register(30) (r/-): RX data overrun when set */
  UART_DATA_AVAIL = 31  /**< UART receive/transmit data register(31) (r/-): RX data available when set  */
};
/**@}*/


/**********************************************************************//**
 * @name IO Device: Serial Peripheral Interface Controller (SPI)
 **************************************************************************/
/**@{*/
/** SPI control register (r/w) */
#define SPI_CT  (*(IO_REG32 0xFFFFFFA8UL))
/** SPI receive/transmit data register (r/w) */
#define SPI_DATA (*(IO_REG32 0xFFFFFFACUL))

/** SPI control register bits */
enum NEORV32_SPI_CT_enum {
  SPI_CT_CS0    =  0, /**< UART control register(0) (r/w): Direct chip select line 0 (output is low when set) */
  SPI_CT_CS1    =  1, /**< UART control register(1) (r/w): Direct chip select line 1 (output is low when set) */
  SPI_CT_CS2    =  2, /**< UART control register(2) (r/w): Direct chip select line 2 (output is low when set) */
  SPI_CT_CS3    =  3, /**< UART control register(3) (r/w): Direct chip select line 3 (output is low when set) */
  SPI_CT_CS4    =  4, /**< UART control register(4) (r/w): Direct chip select line 4 (output is low when set) */
  SPI_CT_CS5    =  5, /**< UART control register(5) (r/w): Direct chip select line 5 (output is low when set) */
  SPI_CT_CS6    =  6, /**< UART control register(6) (r/w): Direct chip select line 6 (output is low when set) */
  SPI_CT_CS7    =  7, /**< UART control register(7) (r/w): Direct chip select line 7 (output is low when set) */

  SPI_CT_EN     =  8, /**< UART control register(8) (r/w): SPI unit enable */
  SPI_CT_CPHA   =  9, /**< UART control register(9) (r/w): Clock polarity (idle polarity) */
  SPI_CT_PRSC0  = 10, /**< UART control register(10) (r/w): Clock prescaler select bit 0 */
  SPI_CT_PRSC1  = 11, /**< UART control register(11) (r/w): Clock prescaler select bit 1 */
  SPI_CT_PRSC2  = 12, /**< UART control register(12) (r/w): Clock prescaler select bit 2 */
  SPI_CT_SIZE0  = 13, /**< UART control register(13) (r/w): Transfer data size lsb (00: 8-bit, 01: 16-bit, 10: 24-bit, 11: 32-bit) */
  SPI_CT_SIZE1  = 14, /**< UART control register(14) (r/w): Transfer data size msb (00: 8-bit, 01: 16-bit, 10: 24-bit, 11: 32-bit) */
  SPI_CT_IRQ_EN = 15, /**< UART control register(15) (r/w): Transfer done interrupt enable */

  SPI_CT_BUSY   = 31  /**< UART control register(31) (r/-): SPI busy flag */
};
/**@}*/


/**********************************************************************//**
 * @name IO Device: Two-Wire Interface Controller (TWI)
 **************************************************************************/
/**@{*/
/** TWI control register (r/w) */
#define TWI_CT   (*(IO_REG32 0xFFFFFFB0UL))
/** TWI receive/transmit data register (r/w) */
#define TWI_DATA (*(IO_REG32 0xFFFFFFB4UL))

/** TWI control register bits */
enum NEORV32_TWI_CT_enum {
  TWI_CT_EN     =  0, /**< TWI control register(0) (r/w): TWI enable */
  TWI_CT_START  =  1, /**< TWI control register(1) (-/w): Generate START condition, auto-clears */
  TWI_CT_STOP   =  2, /**< TWI control register(2) (-/w): Generate STOP condition, auto-clears */
  TWI_CT_IRQ_EN =  3, /**< TWI control register(3) (r/w): Enable transmission done interrupt */
  TWI_CT_PRSC0  =  4, /**< TWI control register(4) (r/w): Clock prescaler select bit 0 */
  TWI_CT_PRSC1  =  5, /**< TWI control register(5) (r/w): Clock prescaler select bit 1 */
  TWI_CT_PRSC2  =  6, /**< TWI control register(6) (r/w): Clock prescaler select bit 2 */
  TWI_CT_MACK   =  7, /**< TWI control register(7) (r/w): Generate controller ACK for each transmission */
  TWI_CT_CKSTEN =  8, /**< TWI control register(8) (r/w): Enable clock stretching (by peripheral) */

  TWI_CT_ACK    = 30, /**< TWI control register(30) (r/-): ACK received when set */
  TWI_CT_BUSY   = 31  /**< TWI control register(31) (r/-): Transfer in progress, busy flag */
};

/** WTD receive/transmit data register bits */
enum NEORV32_TWI_DATA_enum {
  TWI_DATA_LSB = 0, /**< TWI data register(0) (r/w): Receive/transmit data (8-bit) LSB */
  TWI_DATA_MSB = 7  /**< TWI data register(7) (r/w): Receive/transmit data (8-bit) MSB */
};
/**@}*/


/**********************************************************************//**
 * @name IO Device: Pulse Width Modulation Controller (PWM)
 **************************************************************************/
/**@{*/
/** PWM control register (r/w) */
#define PWM_CT   (*(IO_REG32 0xFFFFFFB8UL)) // r/w: control register
/** PWM duty cycle register (4-channels) (r/w) */
#define PWM_DUTY (*(IO_REG32 0xFFFFFFBCUL)) // r/w: duty cycle channel 1 and 0

/** PWM control register bits */
enum NEORV32_PWM_CT_enum {
  PWM_CT_EN    =  0, /**< PWM control register(0) (r/w): PWM controller enable */
  PWM_CT_PRSC0 =  1, /**< PWM control register(1) (r/w): Clock prescaler select bit 0 */
  PWM_CT_PRSC1 =  2, /**< PWM control register(2) (r/w): Clock prescaler select bit 1 */
  PWM_CT_PRSC2 =  3  /**< PWM control register(3) (r/w): Clock prescaler select bit 2 */
};

/**PWM duty cycle register bits */
enum NEORV32_PWM_DUTY_enum {
  PWM_DUTY_CH0_LSB =  0, /**< PWM duty cycle register(0)  (r/w): Channel 0 duty cycle (8-bit) LSB */
  PWM_DUTY_CH0_MSB =  7, /**< PWM duty cycle register(7)  (r/w): Channel 0 duty cycle (8-bit) MSB */
  PWM_DUTY_CH1_LSB =  8, /**< PWM duty cycle register(8)  (r/w): Channel 1 duty cycle (8-bit) LSB */
  PWM_DUTY_CH1_MSB = 15, /**< PWM duty cycle register(15) (r/w): Channel 1 duty cycle (8-bit) MSB */
  PWM_DUTY_CH2_LSB = 16, /**< PWM duty cycle register(16) (r/w): Channel 2 duty cycle (8-bit) LSB */
  PWM_DUTY_CH2_MSB = 23, /**< PWM duty cycle register(23) (r/w): Channel 2 duty cycle (8-bit) MSB */
  PWM_DUTY_CH3_LSB = 24, /**< PWM duty cycle register(24) (r/w): Channel 3 duty cycle (8-bit) LSB */
  PWM_DUTY_CH3_MSB = 31  /**< PWM duty cycle register(31) (r/w): Channel 3 duty cycle (8-bit) MSB */
};
/**@}*/


/**********************************************************************//**
 * @name IO Device: System Configuration Info Memory (SYSINFO)
 **************************************************************************/
/**@{*/
/** SYSINFO(0): Clock speed */
#define SYSINFO_CLK         (*(IO_ROM32 0xFFFFFFE0UL))
/** SYSINFO(1): Custom user code (via "USER_CODE" generic) */
#define SYSINFO_USER_CODE   (*(IO_ROM32 0xFFFFFFE4UL))
/** SYSINFO(2): Clock speed */
#define SYSINFO_FEATURES    (*(IO_ROM32 0xFFFFFFE8UL))
/** SYSINFO(3): Cache configuration */
#define SYSINFO_CACHE       (*(IO_ROM32 0xFFFFFFECUL))
/** SYSINFO(4): Instruction memory address space base */
#define SYSINFO_ISPACE_BASE (*(IO_ROM32 0xFFFFFFF0UL))
/** SYSINFO(5): Data memory address space base */
#define SYSINFO_DSPACE_BASE (*(IO_ROM32 0xFFFFFFF4UL))
/** SYSINFO(6): Internal instruction memory (IMEM) size in bytes */
#define SYSINFO_IMEM_SIZE   (*(IO_ROM32 0xFFFFFFF8UL))
/** SYSINFO(7): Internal data memory (DMEM) size in bytes */
#define SYSINFO_DMEM_SIZE   (*(IO_ROM32 0xFFFFFFFCUL))
/**@}*/

/**********************************************************************//**
 * SYSINFO_FEATURES (r/-): Implemented processor devices/features
 **************************************************************************/
 enum NEORV32_SYSINFO_FEATURES_enum {
  SYSINFO_FEATURES_BOOTLOADER       =  0, /**< SYSINFO_FEATURES  (0) (r/-): Bootloader implemented when 1 (via BOOTLOADER_EN generic) */
  SYSINFO_FEATURES_MEM_EXT          =  1, /**< SYSINFO_FEATURES  (1) (r/-): External bus interface implemented when 1 (via MEM_EXT_EN generic) */
  SYSINFO_FEATURES_MEM_INT_IMEM     =  2, /**< SYSINFO_FEATURES  (2) (r/-): Processor-internal instruction memory implemented when 1 (via MEM_INT_IMEM_EN generic) */
  SYSINFO_FEATURES_MEM_INT_IMEM_ROM =  3, /**< SYSINFO_FEATURES  (3) (r/-): Processor-internal instruction memory implemented as ROM when 1 (via MEM_INT_IMEM_ROM generic) */
  SYSINFO_FEATURES_MEM_INT_DMEM     =  4, /**< SYSINFO_FEATURES  (4) (r/-): Processor-internal data memory implemented when 1 (via MEM_INT_DMEM_EN generic) */
  SYSINFO_FEATURES_MEM_EXT_ENDIAN   =  5, /**< SYSINFO_FEATURES  (5) (r/-): External bus interface uses BIG-endian byte-order when 1 (via package.xbus_big_endian_c constant) */
  SYSINFO_FEATURES_ICACHE           =  6, /**< SYSINFO_FEATURES  (6) (r/-): Processor-internal instruction cache implemented when 1 (via ICACHE_EN generic) */

  SYSINFO_FEATURES_IO_GPIO          = 16, /**< SYSINFO_FEATURES (16) (r/-): General purpose input/output port unit implemented when 1 (via IO_GPIO_EN generic) */
  SYSINFO_FEATURES_IO_MTIME         = 17, /**< SYSINFO_FEATURES (17) (r/-): Machine system timer implemented when 1 (via IO_MTIME_EN generic) */
  SYSINFO_FEATURES_IO_UART          = 18, /**< SYSINFO_FEATURES (18) (r/-): Universal asynchronous receiver/transmitter implemented when 1 (via IO_UART_EN generic) */
  SYSINFO_FEATURES_IO_SPI           = 19, /**< SYSINFO_FEATURES (19) (r/-): Serial peripheral interface implemented when 1 (via IO_SPI_EN generic) */
  SYSINFO_FEATURES_IO_TWI           = 20, /**< SYSINFO_FEATURES (20) (r/-): Two-wire interface implemented when 1 (via IO_TWI_EN generic) */
  SYSINFO_FEATURES_IO_PWM           = 21, /**< SYSINFO_FEATURES (21) (r/-): Pulse-width modulation unit implemented when 1 (via IO_PWM_EN generic) */
  SYSINFO_FEATURES_IO_WDT           = 22, /**< SYSINFO_FEATURES (22) (r/-): Watchdog timer implemented when 1 (via IO_WDT_EN generic) */
  SYSINFO_FEATURES_IO_CFS           = 23, /**< SYSINFO_FEATURES (23) (r/-): Custom functions subsystem implemented when 1 (via IO_CFS_EN generic) */
  SYSINFO_FEATURES_IO_TRNG          = 24  /**< SYSINFO_FEATURES (24) (r/-): True random number generator implemented when 1 (via IO_TRNG_EN generic) */
};

/**********************************************************************//**
 * SYSINFO_CACHE (r/-): Cache configuration
 **************************************************************************/
 enum NEORV32_SYSINFO_CACHE_enum {
  SYSINFO_CACHE_IC_BLOCK_SIZE_0    =  0, /**< SYSINFO_CACHE  (0) (r/-): i-cache: log2(Block size in bytes), bit 0 (via ICACHE_BLOCK_SIZE generic) */
  SYSINFO_CACHE_IC_BLOCK_SIZE_1    =  1, /**< SYSINFO_CACHE  (1) (r/-): i-cache: log2(Block size in bytes), bit 1 (via ICACHE_BLOCK_SIZE generic) */
  SYSINFO_CACHE_IC_BLOCK_SIZE_2    =  2, /**< SYSINFO_CACHE  (2) (r/-): i-cache: log2(Block size in bytes), bit 2 (via ICACHE_BLOCK_SIZE generic) */
  SYSINFO_CACHE_IC_BLOCK_SIZE_3    =  3, /**< SYSINFO_CACHE  (3) (r/-): i-cache: log2(Block size in bytes), bit 3 (via ICACHE_BLOCK_SIZE generic) */

  SYSINFO_CACHE_IC_NUM_BLOCKS_0    =  4, /**< SYSINFO_CACHE  (4) (r/-): i-cache: log2(Number of cache blocks/pages/lines), bit 0 (via ICACHE_NUM_BLOCKS generic) */
  SYSINFO_CACHE_IC_NUM_BLOCKS_1    =  5, /**< SYSINFO_CACHE  (5) (r/-): i-cache: log2(Number of cache blocks/pages/lines), bit 1 (via ICACHE_NUM_BLOCKS generic) */
  SYSINFO_CACHE_IC_NUM_BLOCKS_2    =  6, /**< SYSINFO_CACHE  (6) (r/-): i-cache: log2(Number of cache blocks/pages/lines), bit 2 (via ICACHE_NUM_BLOCKS generic) */
  SYSINFO_CACHE_IC_NUM_BLOCKS_3    =  7, /**< SYSINFO_CACHE  (7) (r/-): i-cache: log2(Number of cache blocks/pages/lines), bit 3 (via ICACHE_NUM_BLOCKS generic) */

  SYSINFO_CACHE_IC_ASSOCIATIVITY_0 =  8, /**< SYSINFO_CACHE  (8) (r/-): i-cache: log2(associativity), bit 0 (via ICACHE_ASSOCIATIVITY generic) */
  SYSINFO_CACHE_IC_ASSOCIATIVITY_1 =  9, /**< SYSINFO_CACHE  (9) (r/-): i-cache: log2(associativity), bit 1 (via ICACHE_ASSOCIATIVITY generic) */
  SYSINFO_CACHE_IC_ASSOCIATIVITY_2 = 10, /**< SYSINFO_CACHE (10) (r/-): i-cache: log2(associativity), bit 2 (via ICACHE_ASSOCIATIVITY generic) */
  SYSINFO_CACHE_IC_ASSOCIATIVITY_3 = 11, /**< SYSINFO_CACHE (11) (r/-): i-cache: log2(associativity), bit 3 (via ICACHE_ASSOCIATIVITY generic) */

  SYSINFO_CACHE_IC_REPLACEMENT_0   = 12, /**< SYSINFO_CACHE (12) (r/-): i-cache: replacement policy (0001 = LRU if associativity > 0) bit 0 */
  SYSINFO_CACHE_IC_REPLACEMENT_1   = 13, /**< SYSINFO_CACHE (13) (r/-): i-cache: replacement policy (0001 = LRU if associativity > 0) bit 1 */
  SYSINFO_CACHE_IC_REPLACEMENT_2   = 14, /**< SYSINFO_CACHE (14) (r/-): i-cache: replacement policy (0001 = LRU if associativity > 0) bit 2 */
  SYSINFO_CACHE_IC_REPLACEMENT_3   = 15, /**< SYSINFO_CACHE (15) (r/-): i-cache: replacement policy (0001 = LRU if associativity > 0) bit 3 */
};


// ----------------------------------------------------------------------------
// Include all IO driver headers
// ----------------------------------------------------------------------------
// cpu core
#include "neorv32_cpu.h"

// neorv32 runtime environment
#include "neorv32_rte.h"

// io/peripheral devices
#include "neorv32_cfs.h"
#include "neorv32_gpio.h"
#include "neorv32_mtime.h"
#include "neorv32_pwm.h"
#include "neorv32_spi.h"
#include "neorv32_trng.h"
#include "neorv32_twi.h"
#include "neorv32_uart.h"
#include "neorv32_wdt.h"

#endif // neorv32_h
