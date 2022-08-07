	AREA	RESET, DATA, READONLY
	EXPORT __Vectors

__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	ALIGN
	AREA	mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler

Reset_Handler
	LDR R0, =SRC
	MOV R5, #5
	ADD R2, R0, #36 ;point to the last location
UP	LDR R1, [R0]
	LDR R3, [R2]
	STR R1, [R2]
	STR R3, [R0]
	ADD R0, R0, #4
	ADD R2, R2, #-4
	SUBS R5, R5, #1
	BNE UP
STOP
	B STOP

	AREA	mydata, DATA, READWRITE
SRC DCD 1,2,3,4,5,6,7,8,9,10
	END