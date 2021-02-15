# custom makefile added to run riscv tests


.PHONY: long short

long:
	bash riscv-compliance/run_compliance_test.sh


short:
	make -C sw/example/rvtests clean_all
	make all
	bash ../../../sim/ghdl/ghdl_sim.sh
