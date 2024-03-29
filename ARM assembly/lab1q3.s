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
	LDR R1, =DST
	MOV R3, #10
UP	LDR R2, [R0], #4
	STR R2, [R1], #4
	SUBS R3, R3, #1
	BNE UP
STOP
	B STOP
SRC DCD 1,2,3,4,5,6,7,8,9,10
	AREA	mydata, DATA, READWRITE
DST DCD 0
	END