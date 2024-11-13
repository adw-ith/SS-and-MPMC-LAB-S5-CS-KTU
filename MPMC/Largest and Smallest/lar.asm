ASSUME CS:CODE,DS:DATA
DATA SEGMENT
       ARR DB 1000H DUP (?)
       LEN DB ?
       LARGE DB 00H
       SMALL DB 0FFH
       MSG1 DB 0AH,0DH,"ENTER LENGTH:$"
       MSG2 DB 0AH,0DH,"ENTER NUMBERS:$"
       MSG3 DB 0AH,0DH,"SMALL:$"
       MSG4 DB 0AH,0DH,"LARGE:$"
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
               MOV AH,00H
               ADD AL,00H
               AAA               
               MOV LEN,AL
               LEA SI,ARR               
               MOV CL,LEN
               MOV CH,00H               
               LEA DX,MSG2
               MOV AH,09H
               INT 21H               
INPUT_LOOP:    MOV AH,01H
               INT 21H
    		   MOV [SI],AL
     		   INC SI
			   LOOP INPUT_LOOP  
    		   LEA SI,ARR
       		   MOV CL,LEN
LOOP1: 		   MOV AL,ARR[SI]
			   CMP LARGE,AL
			   JNC SMC
			   MOV LARGE,AL
SMC:   		   CMP SMALL,AL
			   JC LABEL1
			   MOV SMALL,AL
LABEL1:		   INC SI
			   LOOP LOOP1
	           LEA DX,MSG3
               MOV AH,09H
               INT 21H
               MOV DL,SMALL
               MOV AH,02H
               INT 21H
               LEA DX,MSG4
               MOV AH,09H
               INT 21H
               MOV DL,LARGE
               MOV AH,02H
               INT 21H
               MOV AH,4CH
               INT 21H
CODE ENDS
END START
