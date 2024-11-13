ASSUME CS:CODE, DS:DATA

DATA SEGMENT
    MSG1 DB 10, 13, "INPUT:$"
    MSG2 DB 10, 13, "OUTPUT:$"
    BUFFER DB 4 DUP(0) 
DATA ENDS

CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS, AX

    LEA DX, MSG1
    MOV AH, 09H
    INT 21H

    XOR BX, BX     
    MOV CL, 04H    
INPUT:
    MOV AH, 01H      
    INT 21H
    CMP AL, 0DH       
    JE LINE           
    CMP AL, '0'     
    JB LETTER          
    CMP AL, '9'       
    JA LETTER          
    
    
    SUB AL, '0'
    JMP STORE

LETTER:
    
    CMP AL, 'A'
    JB INPUT           
    CMP AL, 'F'
    JA INPUT           
    SUB AL, 37H     
    
STORE:
    SHL BX,1
    SHL BX,1
    SHL BX,1
    SHL BX,1
    OR BL, AL        
    JMP INPUT         

LINE:
    LEA DX, MSG2
    MOV AH, 09H
    INT 21H

    MOV AX, BX       
    MOV CX, 10       
    XOR DX, DX        
    MOV DI, 0         

    
CONVERT:
    DIV CX             
    PUSH DX            
    INC DI             
    XOR DX, DX         
    TEST AX, AX
    JNZ CONVERT       

  
OUTPUT:
    POP DX            
    ADD DL, '0'       
    MOV AH, 02H        
    INT 21H
    DEC DI            
    JNZ OUTPUT        

   
    MOV AH, 4CH
    INT 21H

CODE ENDS

END START

