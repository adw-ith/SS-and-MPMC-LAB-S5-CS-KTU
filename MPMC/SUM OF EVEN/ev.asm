ASSUME CS:CODE,DS:DATA
DATA SEGMENT 
  MSG1 DB 0AH,0DH,"ENTER NUMBER OF ELEMENTS:$"
  MSG2 DB 0AH,0DH,"ENTER ELEMENTS:$"
  MSG3 DB 0AH,0DH,"SUM OF EVEN NUMBERS IS:$"
  LIST1 DB 09H DUP(?)
  NUMBUFFER DB 6 DUP('$')
  N DB ?
  SUM DB ?
 
DATA ENDS
CODE SEGMENT
START:
          MOV AX,DATA
          MOV DS,AX
   	      LEA DX,MSG1
	      MOV AH,09H
	      INT 21H
	      MOV AH,01H
	      INT 21H
	      SUB AL,30H
	      MOV N,AL
	      MOV CL,N
	      MOV SI,OFFSET LIST1
	      LEA DX,MSG2
	      MOV AH,09H
	      INT 21H
READ:     MOV AH,01H
	      INT 21H
	      SUB AL,30H
	      MOV [SI],AL
	      INC SI
	      DEC CL
	      JNZ READ
	      MOV CL,N
	      MOV SI,OFFSET LIST1
	      MOV SUM,00H
LOOP1:    MOV AL,[SI]
		  TEST AL,01H
		  JZ EVENIS
		  JMP NOT_EVEN
EVENIS:   ADD SUM,AL
NOT_EVEN: INC SI
          LOOP LOOP1
PRINT:    LEA DX,MSG3
          MOV AH,09H
          INT 21H
          MOV AL,SUM
          MOV BL,10
          MOV BH,0
          MOV AH,0
          DIV BL
          ADD AL,'0'
          MOV [NUMBUFFER],AL
          MOV DL,AH
          ADD DL,'0'
          MOV [NUMBUFFER+1],DL
          LEA DX,NUMBUFFER
          MOV AH,09H
          INT 21H
          MOV AH,4CH
          INT 21H
CODE ENDS
END START
