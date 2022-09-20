;	AREA RESET,CODE
;		ENTRY
;		MOV R3,#0
;		MOV R4,#0
;		LDR R0,=INPUTS
;		LDR R1,=OUTPUTS
;		
;CONT 
;		LDR R2,[R0]
;		ADD R4,R4,R2
;		ADD R0,R0,#4
;		ADD R3,R3,#1
;		CMP R3,#5
;		BNE CONT
;		MOV R2,#5
;		MOV R3,#0
;REPT 	SUBS R4,R4,R2
;	    ADDPL R3,R3,#1
;		BPL REPT
;		ADDMI R4,R4,R2
;		STR R3,[R1]
;		 
;STOP	B STOP

;INPUTS	DCD 1,2,3,4,5
;	AREA MEMORY,DATA
;OUTPUTS SPACE 4
;	
;	END
	AREA RESET,CODE
		ENTRY
		;INTIALISATION
		LDR R0,=NUMS
		MOV R5,#0
		MOV R2,#0
		MOV R3,#0
		;OPERATION
CONT	LDR R1,[R0]
		ADDS R2,R1
		ADC R3,#0
		;UPDATION
		ADD R0,#4
		ADD R5,#1
		;LOOP COMPLETION
		CMP R5,#5
		BNE CONT
		
		;CALL DIVIDE FUNCT TO DIVIDE BY 5
		MOV R1,R2
		MOV R2,#5
		BL DIV
		LDR R0,=0X40000000
		STR R3,[R0]
STOP	B STOP

;INPUTS:DIVIDEND-R1  DIVISOR-R2
;OUTPUTS: QUOTIENTS-R3

DIV 
		MOV R3,#0
CONT1 	SUBS R1,R2
		ADDPL R3,#1
		BPL CONT1
		ADD R1,R2
		MOV PC,LR
		
NUMS	DCD 1,2,3,4,5
	END
		
		
		
		;UPDATION
		