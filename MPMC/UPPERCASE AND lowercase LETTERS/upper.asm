ASSUME CS:CODE,DS:DATA
DATA SEGMENT 
  MSG1 DB 0AH,0DH,"ENTER STRING:$"
  MSG2 DB "UPPERCASE LETTERS:$"
  MSG3 DB "LOWERCASE LETTERS:$"
  BUFFER DB 255
  UPPERCOUNT DB ?
  LOWERCOUNT DB ?  
DATA ENDS
CODE SEGMENT
START:
         	 MOV AX,DATA
         	 MOV DS,AX
   	     	 LEA DX,MSG1
	     	 MOV AH,09H
	     	 INT 21H
	     	 MOV AH,0AH
	     	 LEA DX,BUFFER
	     	 INT 21H
	     	 XOR CX,CX
	     	 MOV CL,[BUFFER+1]
	         XOR BX,BX
	         MOV DX,0000H
LOOP1:    	 MOV AL,[BUFFER+2+BX]
          	 CMP AL,'a'
         	 JB CHECK_UPPER
     	     CMP AL,'z'
	         JA CHECK_UPPER
             INC DL
             JMP NEXT
CHECK_UPPER: CMP AL,'A'
             JB NEXT
             CMP AL,'Z'
             JA NEXT
             INC DH
NEXT:        INC BX
			 LOOP LOOP1
			 MOV UPPERCOUNT,DH
			 MOV LOWERCOUNT,DL
			 MOV DX,OFFSET MSG2
             MOV AH,09H
             INT 21H
             MOV AL,UPPERCOUNT
             ADD AL,'0'
             MOV DL,AL
             MOV AH,02H
             INT 21H
             MOV DX,OFFSET MSG3
             MOV AH,09H
             INT 21H
             MOV AL,LOWERCOUNT
             JMP PRINT
PRINT:       ADD AL,'0'
             MOV DL,AL
             MOV AH,02H
             INT 21H
             MOV AH,4CH
             MOV AL,0
             INT 21H
CODE ENDS
END START
