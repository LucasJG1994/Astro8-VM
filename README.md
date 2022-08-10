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
 1. NOP
 2. AIN
 3. BIN
 4. CIN
 5. LDIA
 6. LDIB
 7. RDEXP
 8. WREXP
 9. STA
 10. STC
 11. ADD
 12. SUB
 13. MULT
 14. DIV
 15. JMP
 16. JMPZ
 17. JMPC
 18. JREG
 19. LDAIN
 20. STAOUT
 21. LDLGE
 22. STLGE
 23. LDW
 24. SWP 
 25. SWPC
 26. HLT  
 
 **Instructions that require more than 12 bits do not need to use (SET/HERE) instructions. Just add the number after the instructions. EDIT: You can use SET specifically for injecting values into the ROM before being loaded into the CPU RAM.**  
 
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
 
 
 
