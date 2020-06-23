.386
 STACK  SEGMENT  USE16  STACK
   DB  200  DUP(0)
STACK  ENDS
data segment USE16
  a  DB      ?
data ends 
code segment USE16
ASSUME  CS:CODE,DS:DATA,SS:STACK
start:
MOV  AX,data
MOV  DS,AX
MOV  AH ,  3  
MOV  BH ,   1  
ADD  AH ,  BH
ADD  AH, 30h
MOV  a   ,  AH
MOV  DL  ,  a  
MOV  AH , 2h
INT  21h
MOV  AH  , 4Ch
INT   21h
code ends 
 end start 

