	;PROGRAM to add 2 32bit no in RAM memory 3X+4Y+9Z X=2 Y=3 Z=4
	AREA RESET,CODE
X	EQU 2
Y 	EQU 3
Z	EQU	4
	ENTRY
	MOV R0,#X
	MOV R1,#Y
	MOV R2,#Z
	ADD R0,R0,R0,LSL #1
	MOV R1,R1,LSL #2
	ADD R2,R2,R2,LSL #3
	ADD R0,R0,R1
	ADD R0,R0,R2
	
	
	
STOP B STOP  ;B-BRANCH


	END
		
	