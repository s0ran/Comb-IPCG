#!/bin/sh
bindir=$(pwd)
cd /Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/src/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		GDB_COMMAND-NOTFOUND -batch -command=$bindir/gdbscript  /Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/build/marker-based-AR 
	else
		"/Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/build/marker-based-AR"  
	fi
else
	"/Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/build/marker-based-AR"  
fi
