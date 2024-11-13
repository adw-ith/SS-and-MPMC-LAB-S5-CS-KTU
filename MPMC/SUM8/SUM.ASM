ASSUME CS:CODE,DS:DATA
DATA SEGMENT
        n1 DB 02H
        n2 DB 03H
        sum DB ?
DATA ENDS
CODE SEGMENT
START:
        MOV AX,DATA
        MOV DS,AX
        MOV AL,n1
        ADD AL,n2
        MOV sum,AL
        MOV AH,4CH
        INT 21H
CODE ENDS
END START
