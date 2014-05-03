#Makefile

all: SCP

SCP: SingleCycleProc.v 
	vcs -R SingleCycleProc.v CPU_Control_Unit.v ALU_behav.v RegFile.v m555.v mux.v signextend.v IdealMemory.v ProgramCounter.v lshift2.v

clean:
	rm simv
	rm -r csrc
	rm .vcsmx_rebuild