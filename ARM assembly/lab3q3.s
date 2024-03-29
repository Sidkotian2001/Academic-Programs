	AREA	RESET, DATA, READONLY
	EXPORT __Vectors

__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	AREA	mycode, CODE, READONLY
	ALIGN
	EXPORT Reset_Handler
	
Reset_Handler
	LDR R0, =N1
	LDR R1, =N2
	LDR R6, =DST
	MOV R2, #0
	LDR R3, [R0]
	LDR R4, [R1]
BACK	CMP R3, R4
	BEQ STORE
	BCC DOWN
	SUBS R3, R4
	B BACK
DOWN	SUBS R4, R3
	B BACK
STORE	STR R3, [R6], #4
	MOV R7, R3
	LDR R3, [R0]
	LDR R4, [R1]
	MUL R5, R3, R4
	CMP R7, #1
	BEQ PROD
UP	SUB R5, R7
	ADD R2, R2, #1
	CMP R5, #0
	BNE UP
	STR R2, [R6]
	B STOP
PROD	STR R5, [R6]
STOP
	B STOP
N1 DCD 0X0C
N2 DCD 0X08
	AREA	mydata, DATA, READWRITE
DST DCD 0
	END