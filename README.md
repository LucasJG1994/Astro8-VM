# Astro8-VM
 Original Project: https://github.com/sam-astro/Astro8-Computer by AstroSam  
 
# How to use
 1. Open up your command prompt and type
 ```
 Astro8.exe <filename>.asm
 ```
 within the directory the .exe file resides in.  
 
 **Armstrong is not supported**  
 
# Assembler Instructions
N -> number
A -> register A
B -> register B
C -> register C

ZE -> zero flag
CA -> carry flag
CL -> flag is clear

IP -> instruction pointer

1.	NOP				No Operation
	
2.	AIN 	N		RAM( N ) -> A
3.	AIN 	N, B	RAM( N + B ) -> A
4.	AIN		N, C	RAM( N + C ) -> A

5.	AIN.L 	N		LOCAL( N ) -> A
6.	AIN.L	N, B	LOCAL( N + B ) -> A
7.	AIN.L	N, C	LOCAL( N + C ) -> A

8.	BIN		N		RAM( N ) -> B
9.	BIN.L	N		LOCAL( N ) -> B

10.	CIN		N		RAM( N ) -> C
11.	CIN.L	N		LOCAL( N ) -> C

12.	LDIA	N		N -> A
13.	LDIB	N		N -> B
14.	LDIC	N		N -> C

15.	INA     		A = A + 1
16.	INB     		B = B + 1
17.	INC     		C = C + 1

18.	RDEXP   		EXP -> A
19.	WREXP   		A -> EXP

20.	STA		N		A -> RAM( N )
21.	STA		N, B	A -> RAM( N + B )
22.	STA		N, C	A -> RAM( N + C )

23.	STA.L	N		A -> LOCAL( N )
24.	STA.L	N, B	A -> LOCAL( N + B )
25.	STA.L	N, C	A -> LOCAL( N + C )

26.	STB		N		B -> RAM( N )
27.	STB.L	N		B -> LOCAL( N )

28.	STC		N		C -> RAM( N )
29.	STC.L	N		C -> LOCAL( N )

30.	PHA     		A -> STACK
31.	PLA     		STACK -> A
32.	PHF     		FLAG -> STACK
33.	PLF     		STACK -> FLAG

34.	ADD     		A = A + B
35.	SUB     		A = A - B
36.	MULT    		A = A x B
37.	DIV     		A = A / B

38.	JMP		N		N -> IP
39.	JMPZ	N		IF ZE : N -> IP
40.	JMPC	N		IF CA : N -> IP
41.	JCLR	N		IF CL : N -> IP
42.	JREG    N		A -> IP

43.	CALL	N		IP -> STACK : N -> IP
44.	RET				STACK -> IP

45.	SWP				A -> C : B -> A : C -> B
46.	SWPC			A -> B : C -> A : B -> C

47.	HLT				Stop Execution

 **Massive change to the CPU instructions and operand deem this version incompatible with the original Astro-8 Emulator. This is instead a custom version with my own instructions and some Astro-8 instructions.**  
 
 **Number systems supported**
 1. Hex
 2. Decimal
 
 **Hex**
 ```
 0xFFFF | 0xffff
 ```
 
 **Decimal**
 ```
 0d1234
 ```
 
 **Comments can be used with ';'**
 ```
 ;This is a comment
 ```
 
 
 
