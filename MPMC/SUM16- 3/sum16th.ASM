ASSUME CS:CODE,DS:DATA
DATA SEGMENT
       NUM1 DW 0A425H
       NUM2 DW 0FE67H
       NUM3 DW 06A27H
       RESULT DW ?
       CARRY DB 00H
DATA ENDS

CODE SEGMENT
START: 
       MOV AX,DATA
       MOV DS,AX
       MOV AX,NUM1
       ADD AX,NUM2
       ADC CARRY,00H
       ADD AX,NUM3
       ADC CARRY,00H
       MOV RESULT,AX
       MOV AH, 4CH
       INT 21H
       
CODE ENDS
END START

