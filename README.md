[![NEORV32](https://raw.githubusercontent.com/stnolting/neorv32/master/docs/figures/neorv32_logo.png)](https://github.com/stnolting/neorv32)

# The NEORV32 RISC-V Processor

[![Processor Check](https://github.com/stnolting/neorv32/workflows/Processor%20Check/badge.svg)](https://github.com/stnolting/neorv32/actions?query=workflow%3A%22Processor+Check%22)
[![RISC-V Compliance](https://github.com/stnolting/neorv32/workflows/RISC-V%20Compliance/badge.svg)](https://github.com/stnolting/neorv32/actions?query=workflow%3A%22RISC-V+Compliance%22)
[![license](https://img.shields.io/github/license/stnolting/neorv32)](https://github.com/stnolting/neorv32/blob/master/LICENSE)
[![release](https://img.shields.io/github/v/release/stnolting/neorv32)](https://github.com/stnolting/neorv32/releases)

* [Overview](#Overview)
* [Status](#Status)
* [Features](#Features)
* [FPGA Implementation Results](#FPGA-Implementation-Results)
* [Performance](#Performance)
* [Top Entities](#Top-Entities)
* [**Getting Started**](#Getting-Started)
* [Contribute/Feedback/Questions](#ContributeFeedbackQuestions)
* [Legal](#Legal)



## Overview

The NEORV32 Processor is a customizable microcontroller-like system on chip (SoC) that is based
on the RISC-V-compliant NEORV32 CPU. The processor is intended as *ready-to-go* auxiliary processor within a larger SoC
designs or as stand-alone custom microcontroller.

:label: The project’s change log is available in the [CHANGELOG.md](https://github.com/stnolting/neorv32/blob/master/CHANGELOG.md) file in the root directory of this repository.
To see the changes between releases visit the project's [release page](https://github.com/stnolting/neorv32/releases).

:books: The doxygen-based documentation of the software framework is available online at [GitHub-pages](https://stnolting.github.io/neorv32/files.html).

:page_facing_up: For more detailed information take a look at the [NEORV32 data sheet (pdf)](https://raw.githubusercontent.com/stnolting/neorv32/master/docs/NEORV32.pdf).


### Key Features

* RISC-V 32-bit `rv32i` [**NEORV32 CPU**](#NEORV32-CPU-Features), compliant to
  * Subset of the *Unprivileged ISA Specification* [(Version 2.2)](https://github.com/stnolting/neorv32/blob/master/docs/riscv-privileged.pdf)
  * Subset of the *Privileged Architecture Specification* [(Version 1.12-draft)](https://github.com/stnolting/neorv32/blob/master/docs/riscv-spec.pdf)
  * Passes the [offcial RISC-V compliance tests](#Status)
* Configurable RISC-V-compliant CPU extensions
  * [`A`](#Atomic-memory-access-a-extension) - atomic memory access instructions (optional)
  * [`B`](#Bit-manipulation-instructions-B-extension) - Bit manipulation instructions (optional)
  * [`C`](#Compressed-instructions-C-extension) - compressed instructions (16-bit) (optional)
  * [`E`](#Embedded-CPU-version-E-extension) - embedded CPU (reduced register file size) (optional)
  * [`I`](#Integer-base-instruction-set-I-extension) - base integer instruction set (always enabled)
  * [`M`](#Integer-multiplication-and-division-hardware-M-extension) - integer multiplication and division hardware (optional)
  * [`U`](#Privileged-architecture---User-mode-U-extension) - less-privileged *user mode* (optional)
  * [`X`](#NEORV32-specific-CPU-extensions-X-extension) - NEORV32-specific extensions (always enabled)
  * [`Zicsr`](#Privileged-architecture---CSR-access-Zicsr-extension) - control and status register access instructions (+ exception/irq system) (optional)
  * [`Zifencei`](#Privileged-architecture---Instruction-stream-synchronization-Zifencei-extension) - instruction stream synchronization (optional)
  * [`PMP`](#Privileged-architecture---Physical-memory-protection-PMP) - physical memory protection (optional)
  * [`HPM`](#Privileged-architecture---Hardware-performance-monitors-HPM-extension) - hardware performance monitors (optional)
* Full-scale RISC-V microcontroller system / **SoC** [**NEORV32 Processor**](#NEORV32-Processor-Features) with optional submodules
  * optional embedded memories (instructions/data/bootloader, RAM/ROM) and caches
  * timers (watch dog, RISC-V-compliant machine timer)
  * serial interfaces (SPI, TWI, UART)
  * general purpose IO and PWM channels
  * external bus interface (Wishbone / [AXI4](#AXI4-Connectivity))
  * subsystem for custom co-processors
  * [more ...](#NEORV32-Processor-Features)
* Software framework
  * core libraries for high-level usage of the provided functions and peripherals
  * application compilation based on [GNU makefiles](https://github.com/stnolting/neorv32/blob/master/sw/example/blink_led/makefile)
  * GCC-based toolchain ([pre-compiled toolchains available](https://github.com/stnolting/riscv-gcc-prebuilt))
  * bootloader with UART interface console
  * runtime environment
  * several example programs
  * [doxygen-based](https://github.com/stnolting/neorv32/blob/master/docs/doxygen_makefile_sw) documentation: available on [GitHub pages](https://stnolting.github.io/neorv32/files.html)
  * [FreeRTOS port](https://github.com/stnolting/neorv32/blob/master/sw/example/demo_freeRTOS) available
* [**Full-blown data sheet**](https://raw.githubusercontent.com/stnolting/neorv32/master/docs/NEORV32.pdf) (pdf)
* Completely described in behavioral, platform-independent VHDL - no primitives, macros, etc.
* Fully synchronous design, no latches, no gated clocks
* Small hardware footprint and high operating frequency


### Design Principles

 * From zero to *hello_world*: Completely open source and documented.
 * Plain VHDL without technology-specific parts like attributes, macros or primitives.
 * Easy to use – working out of the box.
 * Clean synchronous design, no wacky combinatorial interfaces.
 * Be as small as possible – but with a reasonable size-performance tradeoff.
 * Be as RISC-V-compliant as possible.
 * The processor has to fit in a Lattice iCE40 UltraPlus 5k low-power FPGA running at 20+ MHz.


### Status

The processor is [synthesizable](#FPGA-Implementation-Results) (tested on *real hardware* using Intel Quartus Prime, Xilinx Vivado and Lattice Radiant/Synplify Pro) and can successfully execute
all the [provided example programs](https://github.com/stnolting/neorv32/tree/master/sw/example) including the [CoreMark benchmark](#CoreMark-Benchmark).

**RISC-V Compliance**: The processor passes the official `rv32_m/C`, `rv32_m/I`, `rv32_m/M`, `rv32_m/privilege` and `rv32_m/Zifencei`
[RISC-V compliance](https://github.com/riscv/riscv-compliance) tests. More information regarding the NEORV32 port of the compliance framework can be found in
[`riscv-compliance/README.md`](https://github.com/stnolting/neorv32/blob/master/riscv-compliance/README.md).

| Project component | CI status |
|:----------------- |:----------|
| [NEORV32 processor](https://github.com/stnolting/neorv32)                                             | [![Processor Check](https://github.com/stnolting/neorv32/workflows/Processor%20Check/badge.svg)](https://github.com/stnolting/neorv32/actions?query=workflow%3A%22Processor+Check%22) |
| [SW Framework Documentation (online)](https://stnolting.github.io/neorv32/files.html)                 | [![Doc@GitHub-pages](https://github.com/stnolting/neorv32/workflows/Deploy%20SW%20Framework%20Documentation%20to%20GitHub-Pages/badge.svg)](https://stnolting.github.io/neorv32/files.html) |
| [Pre-built toolchains](https://github.com/stnolting/riscv-gcc-prebuilt)                               | [![Test Toolchains](https://github.com/stnolting/riscv-gcc-prebuilt/workflows/Test%20Toolchains/badge.svg)](https://github.com/stnolting/riscv-gcc-prebuilt/actions?query=workflow%3A%22Test+Toolchains%22) |
| [RISC-V compliance test](https://github.com/stnolting/neorv32/blob/master/riscv-compliance/README.md) | [![RISC-V Compliance](https://github.com/stnolting/neorv32/workflows/RISC-V%20Compliance/badge.svg)](https://github.com/stnolting/neorv32/actions?query=workflow%3A%22RISC-V+Compliance%22) |



### To-Do / Wish List / Help Wanted

* Use LaTeX for data sheet
* Further size and performance optimization
* Further expand associativity configuration of instruction cache (4x/8x set-associativity)?
* Add data cache?
* Burst mode for the external memory/bus interface?
* RISC-V `F` (using [`Zfinx`](https://github.com/riscv/riscv-zfinx/blob/master/Zfinx_spec.adoc)?) CPU extension (single-precision floating point)
* Add template (HW module + intrinsics skeleton) for custom instructions?
* Implement further RISC-V (or custom) CPU extensions?
* More support for FreeRTOS (like *all* traps)?
* Port additional RTOSs (like [Zephyr](https://github.com/zephyrproject-rtos/zephyr) or [RIOT](https://www.riot-os.org))?
* Add debugger ([RISC-V debug spec](https://github.com/riscv/riscv-debug-spec))?
* Add encryption/decryption/hash accelerator (maybe [XTEA](https://en.wikipedia.org/wiki/XTEA))?
* ...
* [Ideas?](#ContributeFeedbackQuestions)



## Features

The full-blown data sheet of the NEORV32 Processor and CPU is available as pdf file:
[:page_facing_up: NEORV32 data sheet](https://raw.githubusercontent.com/stnolting/neorv32/master/docs/NEORV32.pdf).


### NEORV32 Processor Features

![neorv32 Overview](https://raw.githubusercontent.com/stnolting/neorv32/master/docs/figures/neorv32_processor.png)

The NEORV32 Processor provides a full-scale microcontroller-like SoC based on the NEORV32 CPU. The setup
is highly customizable via the processor's top generics and already provides the following *optional* modules:

* processor-internal data and instruction memories (**DMEM** / **IMEM**) & cache (**iCACHE**)
* bootloader (**BOOTLDROM**) with UART console and automatic application boot from SPI flash option
* machine system timer (**MTIME**), RISC-V-compliant
* watchdog timer (**WDT**)
* universal asynchronous receiver and transmitter (**UART**) with simulation output option via text.io
* 8/16/24/32-bit serial peripheral interface controller (**SPI**) with 8 dedicated chip select lines
* two wire serial interface controller (**TWI**), with optional clock-stretching, compatible to the I²C standard
* general purpose parallel IO port (**GPIO**), 32xOut & 32xIn, with pin-change interrupt
* 32-bit external bus interface, Wishbone b4 compliant (**WISHBONE**), *standard* or *pipelined* handshake/transactions mode
* wrapper for **AXI4-Lite Master Interface** (see [AXI Connectivity](#AXI4-Connectivity))
* PWM controller with 4 channels and 8-bit duty cycle resolution (**PWM**)
* ring-oscillator-based true random number generator (**TRNG**)
* custom functions subsystem (**CFS**) for tightly-coupled custom co-processor extensions
* system configuration information memory to check hardware configuration by software (**SYSINFO**, mandatory - not *optional*)


### NEORV32 CPU Features

The NEORV32 CPU is **compliant** to the
[official RISC-V specifications (2.2)](https://raw.githubusercontent.com/stnolting/neorv32/master/docs/riscv-spec.pdf) including a subset of the 
[RISC-V privileged architecture specifications (1.12-draft)](https://raw.githubusercontent.com/stnolting/neorv32/master/docs/riscv-spec.pdf)
tested via the [official RISC-V Compliance Test Framework](https://github.com/riscv/riscv-compliance)
(see [`riscv-compliance/README`](https://github.com/stnolting/neorv32/blob/master/riscv-compliance/README.md)).

More information regarding the CPU including a detailed list of the instruction set and the available CSRs can be found in
the [:page_facing_up: NEORV32 data sheet](https://raw.githubusercontent.com/stnolting/neorv32/master/docs/NEORV32.pdf).


#### General Features

  * Modified Harvard architecture (separate CPU interfaces for data and instructions; NEORV32 processor: Single processor-internal bus via I/D mux)
  * Two stages in-order pipeline (FETCH, EXECUTE); each stage uses a multi-cycle processing scheme
  * No hardware support of unaligned accesses - they will trigger an exception
  * BIG-ENDIAN byte-order, processor's external memory interface allows endianness configuration to connect to system with different endianness
  * All reserved or unimplemented instructions will raise an illegal instruction exception
  * Privilege levels: `machine` mode, `user` mode (if enabled via `U` extension)
  * Official [RISC-V open-source architecture ID](https://github.com/riscv/riscv-isa-manual/blob/master/marchid.md)


#### Atomic memory access (`A` extension)

  * Supported instructions: `LR.W` (load-reservate) `SC.W` (store-conditional)


#### Bit manipulation instructions (`B` extension)

  * :warning: Extension is not officially ratified yet by the RISC-V foundation! 
  * Implies `Zbb` extension (base bit manipulation instruction set)
  * Compatible to [v0.94-draft](https://raw.githubusercontent.com/stnolting/neorv32/master/docs/bitmanip-draft.pdf) of the bit manipulation spec
  * Support via intrisc library (see [`sw/example/bit_manipulation`](https://github.com/stnolting/neorv32/tree/master/sw/example/bit_manipulation))
  * Only the `Zbb` base instructions subset is supported yet
  * Supported instructions: `CLZ` `CTZ` `CPOP` `SEXT.B` `SEXT.H` `MIN[U]` `MAX[U]` `ANDN` `ORN` `XNOR` `ROL` `ROR` `RORI` `zext`(*pseudo-instruction* for `PACK rd, rs, zero`) `rev8`(*pseudo-instruction* for `GREVI rd, rs, -8`) `orc.b`(*pseudo-instruction* for `GORCI rd, rs, 7`)


#### Compressed instructions (`C` extension)

  * ALU instructions: `C.ADDI4SPN` `C.ADDI` `C.ADD` `C.ADDI16SP` `C.LI` `C.LUI` `C.SLLI` `C.SRLI` `C.SRAI` `C.ANDI` `C.SUB` `C.XOR` `C.OR` `C.AND` `C.MV` `C.NOP`
  * Jump and branch instructions: `C.J` `C.JAL` `C.JR` `C.JALR` `C.BEQZ` `C.BNEZ`
  * Memory instructions: `C.LW` `C.SW` `C.LWSP` `C.SWSP`
  * System instructions: `C.EBREAK` (only with `Zicsr` extension)
  * Pseudo-instructions are not listed

#### Embedded CPU version (`E` extension)

  * Reduced register file (only the 16 lowest registers)


#### Integer base instruction set (`I` extension)

  * ALU instructions: `LUI` `AUIPC` `ADDI` `SLTI` `SLTIU` `XORI` `ORI` `ANDI` `SLLI` `SRLI` `SRAI` `ADD` `SUB` `SLL` `SLT` `SLTU` `XOR` `SRL` `SRA` `OR` `AND`
  * Jump and branch instructions: `JAL` `JALR` `BEQ` `BNE` `BLT` `BGE` `BLTU` `BGEU` 
  * Memory instructions: `LB` `LH` `LW` `LBU` `LHU` `SB` `SH` `SW`
  * System instructions: `ECALL` `EBREAK` `FENCE`
  * Pseudo-instructions are not listed


#### Integer multiplication and division hardware (`M` extension)

  * Multiplication instructions: `MUL` `MULH` `MULHSU` `MULHU`
  * Division instructions: `DIV` `DIVU` `REM` `REMU`
  * By default, the multiplier and divider cores use an iterative bit-serial processing scheme
  * Multiplications can be mapped to DSPs via the `FAST_MUL_EN` generic to increase performance


#### Privileged architecture - User mode (`U` extension)

  * Requires `Zicsr` extension
  * Privilege levels: `M` (machine mode) + less-privileged `U` (user mode)


#### NEORV32-specific CPU extensions (`X` extension)

* The NEORV32-specific extensions are always enabled and are indicated via the `X` bit set in the `misa` CSR.
* Eight *fast interrupt* request channels with according control/status bits in `mie` and `mip` and custom exception codes in `mcause`
* `mzext` CSR to check for implemented `Z*` CPU extensions (like `Zifencei`)
* All undefined/umimplemented/malformed/illegal instructions do raise an illegal instruction exception


#### Privileged architecture - CSR access (`Zicsr` extension)

  * Privilege levels: `M-mode` (Machine mode)
  * CSR access instructions: `CSRRW` `CSRRS` `CSRRC` `CSRRWI` `CSRRSI` `CSRRCI`
  * System instructions: `MRET` `WFI`
  * Pseudo-instructions are not listed
  * Counter CSRs: `[m]cycle[h]` `[m]instret[m]` `time[h]` `[m]hpmcounter*[h]`(3..31, configurable) `mcounteren` `mcountinhibit` `mhpmevent*`(3..31, configurable)
  * Machine CSRs: `mstatus[h]` `misa`(read-only!) `mie` `mtvec` `mscratch` `mepc` `mcause` `mtval` `mip` `mvendorid` [`marchid`](https://github.com/riscv/riscv-isa-manual/blob/master/marchid.md) `mimpid` `mhartid` `mzext`(custom)
  * Supported exceptions and interrupts:
    * Misaligned instruction address
    * Instruction access fault (via unacknowledged bus access after timeout)
    * Illegal instruction
    * Breakpoint (via `ebreak` instruction)
    * Load address misaligned
    * Load access fault (via unacknowledged bus access after timeout)
    * Store address misaligned
    * Store access fault (via unacknowledged bus access after timeout)
    * Environment call from U-mode (via `ecall` instruction in user mode)
    * Environment call from M-mode (via `ecall` instruction in machine mode)
    * Machine timer interrupt `mti` (via processor's MTIME unit / external signal)
    * Machine software interrupt `msi` (via external signal)
    * Machine external interrupt `mei` (via external signal)
    * Eight fast interrupt requests (custom extension)


#### Privileged architecture - Instruction stream synchronization (`Zifencei` extension)

  * System instructions: `FENCE.I` (among others, used to clear and reload instruction cache)


#### Privileged architecture - Physical memory protection (`PMP`)

  * Requires `Zicsr` extension
  * Configurable number of regions (0..63)
  * Additional machine CSRs: `pmpcfg*`(0..15) `pmpaddr*`(0..63)


#### Privileged architecture - Hardware performance monitors (`HPM` extension)

  * Requires `Zicsr` extension
  * Configurable number of counters (0..29)
  * Additional machine CSRs: `mhpmevent*`(3..31) `[m]hpmcounter*[h]`(3..31)


### :warning: Non-RISC-V-Compliant Issues and Limitations

* CPU and Processor are BIG-ENDIAN, but this should be no problem as the external memory bus interface provides big- and little-endian configurations
* `misa` CSR is read-only - no dynamic enabling/disabling of synthesized CPU extensions during runtime; for compatibility: write accesses (in m-mode) are ignored and do not cause an exception
* The physical memory protection (**PMP**) only supports `NAPOT` mode yet and a minimal granularity of 8 bytes
* The `A` extension only implements `lr.w` and `sc.w` instructions yet. However, these instructions are sufficient to emulate all further AMO operations
* The `mcause` trap code `0x80000000` (originally reserved in the RISC-V specs) is used to indicate a hardware reset (as "non-maskable interrupt")
* The bit manipulation extension is not yet officially ratified, but is expected to stay unchanged. There is no software support in the upstream GCC RISC-V port yet. However, an intrinsic library is provided to utilize the provided bit manipulation extension from C-language code (see [`sw/example/bit_manipulation`](https://github.com/stnolting/neorv32/tree/master/sw/example/bit_manipulation)). NEORV32's `B`/`Zbb` extension is compliant to spec. version "0.94-draft".



## FPGA Implementation Results

### NEORV32 CPU

This chapter shows exemplary implementation results of the NEORV32 CPU for an **Intel Cyclone IV EP4CE22F17C6N FPGA** on
a DE0-nano board. The design was synthesized using **Intel Quartus Prime Lite 20.1** ("balanced implementation"). The timing
information is derived from the Timing Analyzer / Slow 1200mV 0C Model. If not otherwise specified, the default configuration
of the CPU's generics is assumed (e.g. no physical memory protection, no hardware performance monitors).
No constraints were used at all. The `u` and `Zifencei` extensions have a negligible impact on the hardware requirements.

Results generated for hardware version [`1.5.0.3`](https://github.com/stnolting/neorv32/blob/master/CHANGELOG.md).

| CPU Configuration                        | LEs        | FFs      | Memory bits | DSPs | f_max   |
|:-----------------------------------------|:----------:|:--------:|:-----------:|:----:|:-------:|
| `rv32i`                                  |       1190 |      512 |        1024 |    0 | 120 MHz |
| `rv32i`     + `u` + `Zicsr` + `Zifencei` |       1927 |      903 |        1024 |    0 | 123 MHz |
| `rv32im`    + `u` + `Zicsr` + `Zifencei` |       2471 |     1148 |        1024 |    0 | 120 MHz |
| `rv32imc`   + `u` + `Zicsr` + `Zifencei` |       2716 |     1165 |        1024 |    0 | 120 MHz |
| `rv32imac`  + `u` + `Zicsr` + `Zifencei` |       2736 |     1168 |        1024 |    0 | 120 MHz |
| `rv32imacb` + `u` + `Zicsr` + `Zifencei` |       3045 |     1260 |        1024 |    0 | 116 MHz |

Setups with enabled "embedded CPU extension" `E` show the same LUT and FF utilization and identical f_max. However, the size of the register file is cut in half. 


### NEORV32 Processor-Internal Peripherals and Memories

Results generated for hardware version [`1.5.0.3`](https://github.com/stnolting/neorv32/blob/master/CHANGELOG.md).

| Module    | Description                                          | LEs | FFs | Memory bits | DSPs |
|:----------|:-----------------------------------------------------|----:|----:|------------:|-----:|
| BOOT ROM  | Bootloader ROM (default 4kB)                         |   3 |   1 |      32 768 |    0 |
| BUSSWITCH | Mux for CPU I & D interfaces                         |  65 |   8 |           0 |    0 |
| i-CACHE   | Proc.-int. nstruction cache (default 1x4x64 bytes)   | 234 | 156 |       8 192 |    0 |
| CFS       | Custom functions subsystem                           |   - |   - |           - |    - |
| DMEM      | Processor-internal data memory (default 8kB)         |   6 |   2 |      65 536 |    0 |
| GPIO      | General purpose input/output ports                   |  67 |  65 |           0 |    0 |
| IMEM      | Processor-internal instruction memory (default 16kb) |   6 |   2 |     131 072 |    0 |
| MTIME     | Machine system timer                                 | 274 | 166 |           0 |    0 |
| PWM       | Pulse-width modulation controller                    |  71 |  69 |           0 |    0 |
| SPI       | Serial peripheral interface                          | 138 | 124 |           0 |    0 |
| SYSINFO   | System configuration information memory              |  11 |  10 |           0 |    0 |
| TRNG      | True random number generator                         | 132 | 105 |           0 |    0 |
| TWI       | Two-wire interface                                   |  77 |  46 |           0 |    0 |
| UART      | Universal asynchronous receiver/transmitter          | 176 | 132 |           0 |    0 |
| WDT       | Watchdog timer                                       |  60 |  45 |           0 |    0 |
| WISHBONE  | External memory interface                            | 129 | 104 |           0 |    0 |


### NEORV32 Processor - Exemplary FPGA Setups

Exemplary processor implementation results for different FPGA platforms. The processor setup uses *the default peripheral configuration* (like no _CFS_ and no _TRNG_),
no external memory interface and only internal instruction and data memories. IMEM uses 16kB and DMEM uses 8kB memory space. The setup's top entity connects most of the
processor's [top entity](https://github.com/stnolting/neorv32/blob/master/rtl/core/neorv32_top.vhd) signals
to FPGA pins - except for the Wishbone bus and the interrupt signals. The "default" strategy of each toolchain is used.

Results generated for hardware version [`1.4.9.0`](https://github.com/stnolting/neorv32/blob/master/CHANGELOG.md).

| Vendor  | FPGA                              | Board            | Toolchain                  | CPU Configuration                              | LUT / LE   | FF / REG   | DSP    | Memory Bits  | BRAM / EBR | SPRAM    | Frequency     |
|:--------|:----------------------------------|:-----------------|:---------------------------|:-----------------------------------------------|:-----------|:-----------|:-------|:-------------|:-----------|:---------|--------------:|
| Intel   | Cyclone IV `EP4CE22F17C6N`        | Terasic DE0-Nano | Quartus Prime Lite 20.1    | `rv32imc` + `u` + `Zicsr` + `Zifencei`         | 3813 (17%) | 1904  (8%) | 0 (0%) | 231424 (38%) |          - |        - |       119 MHz |
| Lattice | iCE40 UltraPlus `iCE40UP5K-SG48I` | Upduino v2.0     | Radiant 2.1 (Synplify Pro) | `rv32ic`  + `u` + `Zicsr` + `Zifencei`         | 4397 (83%) | 1679 (31%) | 0 (0%) |            - |   12 (40%) | 4 (100%) | *c* 22.15 MHz |
| Xilinx  | Artix-7 `XC7A35TICSG324-1L`       | Arty A7-35T      | Vivado 2019.2              | `rv32imc` + `u` + `Zicsr` + `Zifencei` + `PMP` | 2465 (12%) | 1912  (5%) | 0 (0%) |            - |    8 (16%) |        - |   *c* 100 MHz |

**_Notes_**
* The Lattice iCE40 UltraPlus setup uses the FPGA's SPRAM memory primitives for the internal IMEM and DMEM (each 64kb).
The FPGA-specific memory components can be found in [`rtl/fpga_specific`](https://github.com/stnolting/neorv32/blob/master/rtl/fpga_specific/lattice_ice40up).
* The clock frequencies marked with a "c" are constrained clocks. The remaining ones are _f_max_ results from the place and route timing reports.
* The Upduino and the Arty board have on-board SPI flash memories for storing the FPGA configuration. These device can also be used by the default NEORV32
bootloader to store and automatically boot an application program after reset (both tested successfully).
* The setups with `PMP` implement 2 regions with a minimal granularity of 64kB.
* No HPM counters are implemented.



## Performance

### CoreMark Benchmark

The [CoreMark CPU benchmark](https://www.eembc.org/coremark) was executed on the NEORV32 and is available in the
[sw/example/coremark](https://github.com/stnolting/neorv32/blob/master/sw/example/coremark) project folder. This benchmark
tests the capabilities of a CPU itself rather than the functions provided by the whole system / SoC.

~~~
**Configuration**
Hardware:       32kB IMEM, 16kB DMEM, no caches, 100MHz clock
CoreMark:       2000 iterations, MEM_METHOD is MEM_STACK
Compiler:       RISCV32-GCC 10.1.0 (rv32i toolchain)
Compiler flags: default, see makefile
Peripherals:    UART for printing the results
~~~

Results generated for hardware version [`1.4.9.8`](https://github.com/stnolting/neorv32/blob/master/CHANGELOG.md).

| CPU (including `Zicsr`)                     | Executable Size | Optimization | CoreMark Score | CoreMarks/MHz |
|:--------------------------------------------|:---------------:|:------------:|:--------------:|:-------------:|
| `rv32i`                                     |    28 756 bytes |        `-O3` |          36.36 |    **0.3636** |
| `rv32im`                                    |    27 516 bytes |        `-O3` |          68.97 |    **0.6897** |
| `rv32imc`                                   |    22 008 bytes |        `-O3` |          68.97 |    **0.6897** |
| `rv32imc` + `FAST_MUL_EN`                   |    22 008 bytes |        `-O3` |          86.96 |    **0.8696** |
| `rv32imc` + `FAST_MUL_EN` + `FAST_SHIFT_EN` |    22 008 bytes |        `-O3` |          90.91 |    **0.9091** |

The `FAST_MUL_EN` configuration uses DSPs for the multiplier of the `M` extension (enabled via the `FAST_MUL_EN` generic). The `FAST_SHIFT_EN` configuration
uses a barrel shifter for CPU shift operations (enabled via the `FAST_SHIFT_EN` generic).

When the `C` extension is enabled, branches to an unaligned uncompressed instruction require additional instruction fetch cycles.


### Instruction Cycles

The NEORV32 CPU is based on a two-stages pipelined architecutre. Each stage uses a multi-cycle processing scheme. Hence,
each instruction requires several clock cycles to execute (2 cycles for ALU operations, ..., 40 cycles for divisions).
The average CPI (cycles per instruction) depends on the instruction mix of a specific applications and also on the available
CPU extensions. *By default* the CPU-internal shifter (e.g. for the `SLL` instruction) as well as the multiplier and divider of the
`M` extension use a bit-serial approach and require several cycles for completion.

The following table shows the performance results for successfully running 2000 CoreMark
iterations, which reflects a pretty good "real-life" work load. The average CPI is computed by
dividing the total number of required clock cycles (only the timed core to avoid distortion due to IO wait cycles; sampled via the `cycle[h]` CSRs)
by the number of executed instructions (`instret[h]` CSRs). The executables were generated using optimization `-O3`.

Results generated for hardware version [`1.4.9.8`](https://github.com/stnolting/neorv32/blob/master/CHANGELOG.md).

| CPU  (including `Zicsr`)                    | Required Clock Cycles | Executed Instructions | Average CPI |
|:--------------------------------------------|----------------------:|----------------------:|:-----------:|
| `rv32i`                                     |         5 595 750 503 |         1 466 028 607 |    **3.82** |
| `rv32im`                                    |         2 966 086 503 |           598 651 143 |    **4.95** |
| `rv32imc`                                   |         2 981 786 734 |           611 814 918 |    **4.87** |
| `rv32imc` + `FAST_MUL_EN`                   |         2 399 234 734 |           611 814 918 |    **3.92** |
| `rv32imc` + `FAST_MUL_EN` + `FAST_SHIFT_EN` |         2 265 135 174 |           611 814 948 |    **3.70** |

The `FAST_MUL_EN` configuration uses DSPs for the multiplier of the `M` extension (enabled via the `FAST_MUL_EN` generic). The `FAST_SHIFT_EN` configuration
uses a barrel shifter for CPU shift operations (enabled via the `FAST_SHIFT_EN` generic).

When the `C` extension is enabled branches to an unaligned uncompressed instruction require additional instruction fetch cycles.



## Top Entities

The top entity of the **NEORV32 Processor** (SoC) is [`rtl/core/neorv32_top.vhd`](https://github.com/stnolting/neorv32/blob/master/rtl/core/neorv32_top.vhd).

All signals of the top entity are of type *std_ulogic* or *std_ulogic_vector*, respectively
(except for the processor's TWI signals, which are of type *std_logic*). Leave all unused output ports unconnected (`open`) and tie all unused
input ports to zero (`'0'` or `(others => '0')`, respectively).

Use the top's generics to configure the system according to your needs. Each generic is initilized with the default configuration.
Detailed information regarding the interface signals and configuration generics can be found in
the [:page_facing_up: NEORV32 data sheet](https://raw.githubusercontent.com/stnolting/neorv32/master/docs/NEORV32.pdf) (pdf).


### Using the CPU in Stand-Alone Mode

If you *do not* want to use the NEORV32 processor setup, you can also use the CPU in stand-alone mode and build your own system around it.
The top entity of the stand-alone **NEORV32 CPU** is [`rtl/core/neorv32_cpu.vhd`](https://github.com/stnolting/neorv32/blob/master/rtl/core/neorv32_cpu.vhd).
Note that the CPU uses a proprietary interface for accessing data and instruction memory. More information can be found in the
[:page_facing_up: NEORV32 data sheet](https://raw.githubusercontent.com/stnolting/neorv32/master/docs/NEORV32.pdf).

:information_source: It is recommended to use the processor setup even if you only want to use the CPU. Simply disable all the processor-internal modules via the generics
and you will get a "CPU wrapper" that already provides a minimal CPU environment and an external memory interface (like AXI4). This setup also allows to further use the default
bootloader and software framework. From this base you can start building your own processor system.


### Alternative Top Entities

*Alternative top entities*, like the simplified ["hello world" test setup](#Create-a-new-Hardware-Project) or CPU/Processor
wrappers with resolved port signal types (i.e. *std_logic*), can be found in [`rtl/top_templates`](https://github.com/stnolting/neorv32/blob/master/rtl/top_templates).


### AXI4 Connectivity

Via the [`rtl/top_templates/neorv32_top_axi4lite.vhd`](https://github.com/stnolting/neorv32/blob/master/rtl/top_templates/neorv32_top_axi4lite.vhd)
wrapper the NEORV32 provides an **AXI4-Lite** compatible master interface. This wrapper instantiates the default
[NEORV32 processor top entitiy](https://github.com/stnolting/neorv32/blob/master/rtl/core/neorv32_top.vhd) and implements a Wishbone to AXI4-Lite bridge.

The AXI4-Lite interface has been tested using Xilinx Vivado 19.2 block designer:

![AXI-SoC](https://raw.githubusercontent.com/stnolting/neorv32/master/docs/figures/neorv32_axi_soc.png)

The processor was packed as custom IP using `neorv32_top_axi4lite.vhd` as top entity. The AXI interface is automatically detected by the packager.
All remaining IO interfaces are available as custom signals. The configuration generics are available via the "customize IP" dialog.
In the figure above the resulting IP block is named "neorv32_top_axi4lite_v1_0".
*(Note: Use Syntheiss option "global" when generating the block design to maintain the internal TWI tri-state drivers.)*

The setup uses an AXI interconnect to attach two block RAMs to the processor. Since the processor in this example is configured *without* IMEM and DMEM,
the attached block RAMs are used for storing instructions and data: the first RAM is used as instruction memory
and is mapped to address `0x00000000 - 0x00003fff` (16kB), the second RAM is used as data memory and is mapped to address `0x80000000 - 0x80001fff` (8kB).



## Getting Started

This overview is just a short excerpt from the *Let's Get It Started* section of the NEORV32 documentary:

[:page_facing_up: NEORV32 data sheet](https://raw.githubusercontent.com/stnolting/neorv32/master/docs/NEORV32.pdf)


### Toolchain

At first you need the **RISC-V GCC toolchain**. You can either [download the sources](https://github.com/riscv/riscv-gnu-toolchain)
and build the toolchain by yourself, or you can download a prebuilt one and install it.

To build the toolchain by yourself, follow the official [build instructions](https://github.com/riscv/riscv-gnu-toolchain).
Make sure to use the `ilp32` or `ilp32e` ABI.

**Alternatively**, you can download a prebuilt toolchain. I have uploaded the toolchains I am using to GitHub. These toolchains
were compiled on a 64-bit x86 Ubuntu 20.04 LTS (Ubuntu on Windows, actually). Download the toolchain of choice: 
[:octocat: github.com/stnolting/riscv-gcc-prebuilt](https://github.com/stnolting/riscv-gcc-prebuilt)

You can also use the toolchains provided by [SiFive](https://github.com/sifive/freedom-tools/releases). These are 64-bit toolchains that can also emit 32-bit
RISC-V code. They were compiled for more sophisticated machines (`imac`) so the according hardware extensions are *mandatory*

:warning: Keep in mind that – for instance – a `rv32imc` toolchain only provides library code compiled with compressed and
`mul`/`div` instructions! Hence, this code cannot be executed (without emulation) on an architecture without these extensions!


### Dowload the NEORV32 Project

Get the sources of the NEORV32 Processor project. The simplest way is using `git clone` (suggested for easy project updates via `git pull`):

    $ git clone https://github.com/stnolting/neorv32.git

Alternatively, you can either download a specific [release](https://github.com/stnolting/neorv32/releases) or get the most recent version
of this project as [`*.zip` file](https://github.com/stnolting/neorv32/archive/master.zip).


### Create a new Hardware Project

Create a new project with your FPGA design tool of choice. Add all the `*.vhd` files from the [`rtl/core`](https://github.com/stnolting/neorv32/blob/master/rtl)
folder to this project. Make sure to add these files to a **new design library** called `neorv32`.

You can either instantiate the [processor's top entity](https://github.com/stnolting/neorv32/blob/master/rtl/core/neorv32_top.vhd) or one of its
[wrappers](https://github.com/stnolting/neorv32/blob/master/rtl/top_templates) in your own project. If you just want to try out the processor,
you can use the simple [test setup](https://github.com/stnolting/neorv32/blob/master/rtl/top_templates/neorv32_test_setup.vhd) as top entity.

![neorv32 test setup](https://raw.githubusercontent.com/stnolting/neorv32/master/docs/figures/neorv32_test_setup.png)


This test setup instantiates the processor and implements most of the peripherals and some ISA extensions. Only the UART lines, clock, reset and some GPIO output signals are
propagated as actual entity signals. Basically, it is a FPGA "hello world" example:

```vhdl
  entity neorv32_test_setup is
    port (
      -- Global control --
      clk_i      : in  std_ulogic := '0'; -- global clock, rising edge
      rstn_i     : in  std_ulogic := '0'; -- global reset, low-active, async
      -- GPIO --
      gpio_o     : out std_ulogic_vector(7 downto 0); -- parallel output
      -- UART --
      uart_txd_o : out std_ulogic; -- UART send data
      uart_rxd_i : in  std_ulogic := '0' -- UART receive data
    );
  end neorv32_test_setup;
```


### Check the Toolchain

Make sure `GNU Make` and a native `GCC` compiler are installed. To test the installation of the RISC-V toolchain navigate to an example project like
`sw/example/blink_led` and run:

    neorv32/sw/example/blink_led$ make check


### Compiling an Example Program

The NEORV32 project includes some [example programs](https://github.com/stnolting/neorv32/tree/master/sw/example) from
which you can start your own application. Simply compile one of these projects. This will create a NEORV32
*executable* `neorv32_exe.bin` in the same folder:

    neorv32/sw/example/blink_led$ make clean_all exe


### Upload the Executable via the Bootloader

You can upload a generated executable directly from the command line using the makefile's `upload` target. Replace `/dev/ttyUSB0` with
the according serial port.

    sw/exeample/blink_example$ make COM_PORT=/dev/ttyUSB0` upload

A more "secure" way is to use a dedicated terminal program. This allows to directly interact with the bootloader console.
Connect your FPGA board via UART to your computer and open the according port to interface with the NEORV32 bootloader. The bootloader
uses the following default UART configuration:

* 19200 Baud
* 8 data bits
* 1 stop bit
* No parity bits
* No transmission / flow control protocol (raw bytes only)
* Newline on `\r\n` (carriage return & newline) - also for sent data

Use the bootloader console to upload the `neorv32_exe.bin` executable and run your application image.

```
<< NEORV32 Bootloader >>

BLDV: Nov  7 2020
HWV:  0x01040606
CLK:  0x0134FD90 Hz
USER: 0x0001CE40
MISA: 0x42801104
PROC: 0x03FF0035
IMEM: 0x00010000 bytes @ 0x00000000
DMEM: 0x00010000 bytes @ 0x80000000

Autoboot in 8s. Press key to abort.
Aborted.

Available CMDs:
 h: Help
 r: Restart
 u: Upload
 s: Store to flash
 l: Load from flash
 e: Execute
CMD:> u
Awaiting neorv32_exe.bin... OK
CMD:> e
Booting...

Blinking LED demo program
```

Going further: Take a look at the _Let's Get It Started!_ chapter of the [:page_facing_up: NEORV32 data sheet](https://raw.githubusercontent.com/stnolting/neorv32/master/docs/NEORV32.pdf).



## Contribute/Feedback/Questions

I'm always thankful for help! So if you have any questions, bug reports, ideas or if you want to give some kind of feedback, feel free
to [:bulb: open a new issue](https://github.com/stnolting/neorv32/issues), start a new [:sparkles: discussion on GitHub](https://github.com/stnolting/neorv32/discussions)
or directly [:e-mail: drop me a line](mailto:stnolting@gmail.com).

If you'd like to directly contribute to this repository:

0. :star: this repository ;)
1. Check out the project's [code of conduct](https://github.com/stnolting/neorv32/tree/master/CODE_OF_CONDUCT.md)
2. [Fork](https://github.com/stnolting/neorv32/fork) this repository and clone the fork
3. Create a feature branch in your fork: `git checkout -b awesome_new_feature_branch`
4. Create a new remote for the upstream repo: `git remote add upstream https://github.com/stnolting/neorv32`
5. Commit your modifications: `git commit -m "Awesome new feature!"`
6. Push to the branch: `git push origin awesome_new_feature_branch`
7. Create a new [pull request](https://github.com/stnolting/neorv32/pulls)


## Legal

This project is released under the BSD 3-Clause license. No copyright infringement intended.
Other implied or used projects might have different licensing - see their documentation to get more information.

#### Citing

If you are using the NEORV32 or some parts of the project in some kind of publication, please cite it as follows:

> S. Nolting, "The NEORV32 Processor", github.com/stnolting/neorv32

#### BSD 3-Clause License

Copyright (c) 2021, Stephan Nolting. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of
conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or other materials
provided with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors may be used to
endorse or promote products derived from this software without specific prior written
permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
OF THE POSSIBILITY OF SUCH DAMAGE.


#### Limitation of Liability for External Links

Our website contains links to the websites of third parties ("external links"). As the
content of these websites is not under our control, we cannot assume any liability for
such external content. In all cases, the provider of information of the linked websites
is liable for the content and accuracy of the information provided. At the point in time
when the links were placed, no infringements of the law were recognisable to us. As soon
as an infringement of the law becomes known to us, we will immediately remove the
link in question.


#### Proprietary  Notice

"Artix" and "Vivado" are trademarks of Xilinx Inc.

"Cyclone" and "Quartus Prime Lite" are trademarks of Intel Corporation.

"iCE40", "UltraPlus" and "Radiant" are trademarks of Lattice Semiconductor Corporation.

"AXI", "AXI4" and "AXI4-Lite" are trademarks of Arm Holdings plc.



## Acknowledgements

[![RISC-V](https://raw.githubusercontent.com/stnolting/neorv32/master/docs/figures/riscv_logo.png)](https://riscv.org/)

[RISC-V](https://riscv.org/) - Instruction Sets Want To Be Free!

Continous integration provided by [:octocat: GitHub Actions](https://github.com/features/actions) and powered by [GHDL](https://github.com/ghdl/ghdl).

![Open Source Hardware Logo https://www.oshwa.org](https://raw.githubusercontent.com/stnolting/neorv32/master/docs/figures/oshw_logo.png)

This project is not affiliated with or endorsed by the Open Source Initiative (https://www.oshwa.org / https://opensource.org).

--------

Made with :coffee: in Hannover, Germany :eu:
