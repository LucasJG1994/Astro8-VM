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

NOP ==> No Operation  
AIN N ==> RAM( N ) -> A  
AIN N, B ==> RAM( N + B ) -> A  
AIN N, C ==> RAM( N + C ) -> A  

AIN.L N ==> LOCAL( N ) -> A  
AIN.L N, B ==> LOCAL( N + B ) -> A  
AIN.L N, C ==> LOCAL( N + C ) -> A  

BIN N ==> RAM( N ) -> B  
BIN.L N ==> LOCAL( N ) -> B  

CIN N ==> RAM( N ) -> C  
CIN.L N ==> LOCAL( N ) -> C  

LDIA N ==> N -> A  
LDIB N ==> N -> B  
LDIC N ==> N -> C  

INA ==> A = A + 1  
INB ==> B = B + 1  
INC ==> C = C + 1  

RDEXP ==> EXP -> A  
WREXP ==> A -> EXP  

STA N ==> A -> RAM( N )  
STA N, B ==> A -> RAM( N + B )  
STA N, C ==> A -> RAM( N + C )  

STA.L N ==> A -> LOCAL( N )  
STA.L N, B ==> A -> LOCAL( N + B )  
STA.L N, C ==> A -> LOCAL( N + C )  

STB N ==> B -> RAM( N )  
STB.L N ==> B -> LOCAL( N )  

STC N ==> C -> RAM( N )  
STC.L N ==> C -> LOCAL( N )  

PHA ==> A -> STACK  
PLA ==> STACK -> A  
PHF ==> FLAG -> STACK  
PLF ==> STACK -> FLAG  

ADD ==> A = A + B  
SUB ==> A = A - B  
MULT ==> A = A x B  
DIV ==> A = A / B  

JMP N ==> N -> IP  
JMPZ N ==> IF ZE : N -> IP  
JMPC N ==> IF CA : N -> IP  
JCLR N ==> IF CL : N -> IP  
JREG N ==> A -> IP  

CALL N ==> IP -> STACK : N -> IP  
RET ==> STACK -> IP  

SWP ==> A -> C : B -> A : C -> B  
SWPC ==> A -> B : C -> A : B -> C  

HLT ==> Stop Execution  

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
 
 
 
