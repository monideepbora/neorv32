#!/bin/bash

STARTTIME=$(date +%s)
echo "$STARTTIME"

## declare an array variable
declare -a arr=("add" 
                "addi" 
                "and" 
                "andi" 
                "auipc" 
                "beq" 
                "bge" 
                "bgeu" 
                "blt" 
                "bltu" 
                "bne" 
                "j" 
                "jal" 
                "jalr" 
                "lb" 
                "lbu" 
                "lh" 
                "lhu" 
                "lui" 
                "lw" 
                "or" 
                "ori" 
                "sb" 
                "sh" 
                "simple" 
                "sll" 
                "slli" 
                "slt" 
                "slti" 
                "sra" 
                "srai" 
                "srl" 
                "srli" 
                "sub" 
                "sw" 
                "xor" 
                "xori" )

printf "Welcome to the riscv-tests of NEORV32\n"                

## now loop through the above array
for i in "${arr[@]}"
do
   printf "\nTesting the \"$i\" instruction\n"
   # or do whatever with individual element of the array
   bash sw/application/rvtests/tests/generate_start.sh $i
   make --silent -C sw/application/rvtests clean_all
   make --silent -C sw/application/rvtests all
   cd sim/ghdl/
   rm  -f !*.sh
   
    if bash ghdl_sim.sh; then
        printf "Tests for \"$i\" instruction were successsful\n"
        cd ../..
    else
        printf "Tests for \"$i\" instruction have failed\n"
        exit 1
    fi
done

cd ../..
make --silent -C sw/application/rvtests clean_all
rm -f !sim/ghdl/*.sh
printf "\n All riscv-tests successfully done.\n"

ENDTIME=$(date +%s)

echo "It takes $(($ENDTIME - $STARTTIME)) seconds to complete this task..."