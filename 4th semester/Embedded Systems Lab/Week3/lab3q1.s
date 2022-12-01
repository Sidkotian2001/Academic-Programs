	AREA	RESET, DATA, READONLY
	EXPORT __Vectors

__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	ALIGN
	AREA	mycode, CODE, READONLY
	EXPORT Reset_Handler
		
Reset_Handler
	LDR R0, =N1
	LDR R1, =N2
	LDR R6, =DST
	LDR R3, [R0]
	LDR R4, [R1]
	MOV R2, #0
UP	CMP R3, R4
	BCC DOWN
	SUBS R3, R3, R4
	ADD R2, R2, #1
	B UP
	
DOWN	STR R2, [R6], #4
	STR R3, [R6]
STOP
	B STOP

N1 DCD 0X05
N2 DCD 0X0A
	AREA	mydata, DATA, READWRITE
DST DCD 0
	END