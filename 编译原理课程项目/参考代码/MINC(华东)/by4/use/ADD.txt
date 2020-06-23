DATA  SEGMENT

  X DB 100 DUP(0)            ;定义X

  Y DB 100 DUP(0)            ;定义Y

  Z DB 100 DUP(0),'$'        ;定义Z，并以$为结束符

DATA ENDS

CODE SEGMENT                 ;定义代码段

ASSUME CS:CODE,DS:DATA

GO:MOV AX,DATA

   MOV DS,AX

   MOV CX,20               ;CX赋值为20

   MOV SI,10               ;SI赋值为10

X0:   MOV AH,01H           ;X0段的功能是接收从键盘输入的数字存入X，并在屏幕上显示

   INT 21H

 MOV DL,AL                 ;将键盘输入的数字存入DL

    CMP DL,'+'             ;比较DL是否为'+'号

    JZ X1                  ;如果DL为'+'，则跳转至X1

     MOV X[SI],DL          ;如果DL不为'+'，则将DL存入X

    INC SI                 ;SI+1

 LOOP X0                   ;CX-1，并且循环执行X0

 X1:  MOV CX,20            ;CX赋值为20

 MOV DI,10                 ;DI赋值为10

X2: MOV AH,01H             ;X2段的功能是接收从键盘输入的数字存入Y，并在屏幕上显示

   INT 21H

    MOV DL,AL              ;将键盘输入的数字存入DL

    CMP DL,'='             ;比较DL是否为'='号

    JZ A0                  ;如果DL为'='，则跳转至A0

    MOV Y[DI],DL           ;如果DL不为'='，则将DL存入Y

    INC DI                 ;DI+1

LOOP X2                    ;CX-1，并且循环执行X2，直到CX=0

   CLC                     ;CF清零

   PUSHF                   ;CF内容入栈

A0:MOV CX,10               ;CX赋值为10

   MOV BX,90               ;BX赋值为90

A1:MOV DL,X[SI-1]          ;A1的功能是实现加法运算，将X存入DL

   MOV AL,Y[DI-1]          ;将Y存入AL

   POPF                    ;CF出栈

   ADC AL,DL               ;AL与DL相加并把结果存入AL

   AAA                     ;处理进位

   PUSHF                   ;CF入栈

    ADD AL,30H             ;将AL转成ASCⅡ码

   MOV Z[BX],AL            ;AL内容存入Z

   DEC SI                  ;SI-1

   DEC DI                  ;DI-1

   DEC BX                  ;BX-1

LOOP A1                    ;CX-1，并循环执行A1

   INC BX                  ;BX-1

A2: CMP Z[BX],30H          ;A2的功能是判断Z的高位是否为0，如果为0，则不显示

   JNZ A3                  ;如果Z的高位不为0，则跳转至A3

   INC BX                  ;如果Z的高位为0，则BX-1

LOOP A2                    ;循环执行A2

A3:LEA DX,Z[BX]            ;A3段的功能是显示运算结果Z；将Z地址传送至DX

   MOV AH,09H              ;调用09H显示功能显示Z

   INT 21H 

   MOV AH,4CH              ;退回到DOS

   INT 21H

CODE ENDS 

END GO
