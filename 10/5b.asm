	AREA RESET,CODE
		ENTRY
		MOV R0,#30
		MOV R1,#40
LOOP
		CMP R0,R1
		BEQ EXIT
		BGT COND1
		SUB R1,R0
		B LOOP
COND1
		SUB R0,R1
		B LOOP
		
EXIT 
		LDR R0,=GCD
		STR R1,[R0]
STOP	B STOP
	AREA RESULT,DATA
GCD		SPACE 4
	
	END