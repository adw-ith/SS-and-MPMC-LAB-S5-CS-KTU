ASSUME CS:CODE,DS:DATA
DATA SEGMENT 
  MSG1 DB 0AH,0DH,"ENTER NUMBER OF ELEMENTS:$"
  MSG2 DB 0AH,0DH,"ENTER ELEMENTS:$"
  MSG3 DB 0AH,0DH,"SORTED ARRAY IS:$"
  N DB ?
  LIST1 DB 09H DUP(?)
  
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
LOOP1:    MOV CH,N  
          MOV SI,OFFSET LIST1
LOOP2:    MOV DL,[SI]          
          CMP DL,[SI+1]
          JNC SWAP
          JMP SWAPPED
SWAP:     MOV DL,[SI]
          XCHG DL,[SI+1]
          MOV [SI],DL
SWAPPED:  INC SI
          DEC CH
          JNZ LOOP2
          DEC CL
          JNZ LOOP1
          LEA DX,MSG3
	      MOV AH,09H
	      INT 21H
	      MOV SI,OFFSET LIST1
	      MOV CL,N
	      INC SI
PRINT:    MOV DL,[SI]
          ADD DL,30H
          MOV AH,02H
          INT 21H
          INC SI
          DEC CL
          JNZ PRINT
          MOV AH,4CH
          INT 21H
CODE ENDS
END START
