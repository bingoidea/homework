DATA  SEGMENT

  X DB 100 DUP(0)            ;����X

  Y DB 100 DUP(0)            ;����Y

  Z DB 100 DUP(0),'$'        ;����Z������$Ϊ������

DATA ENDS

CODE SEGMENT                 ;��������

ASSUME CS:CODE,DS:DATA

GO:MOV AX,DATA

   MOV DS,AX

   MOV CX,20               ;CX��ֵΪ20

   MOV SI,10               ;SI��ֵΪ10

X0:   MOV AH,01H           ;X0�εĹ����ǽ��մӼ�����������ִ���X��������Ļ����ʾ

   INT 21H

 MOV DL,AL                 ;��������������ִ���DL

    CMP DL,'+'             ;�Ƚ�DL�Ƿ�Ϊ'+'��

    JZ X1                  ;���DLΪ'+'������ת��X1

     MOV X[SI],DL          ;���DL��Ϊ'+'����DL����X

    INC SI                 ;SI+1

 LOOP X0                   ;CX-1������ѭ��ִ��X0

 X1:  MOV CX,20            ;CX��ֵΪ20

 MOV DI,10                 ;DI��ֵΪ10

X2: MOV AH,01H             ;X2�εĹ����ǽ��մӼ�����������ִ���Y��������Ļ����ʾ

   INT 21H

    MOV DL,AL              ;��������������ִ���DL

    CMP DL,'='             ;�Ƚ�DL�Ƿ�Ϊ'='��

    JZ A0                  ;���DLΪ'='������ת��A0

    MOV Y[DI],DL           ;���DL��Ϊ'='����DL����Y

    INC DI                 ;DI+1

LOOP X2                    ;CX-1������ѭ��ִ��X2��ֱ��CX=0

   CLC                     ;CF����

   PUSHF                   ;CF������ջ

A0:MOV CX,10               ;CX��ֵΪ10

   MOV BX,90               ;BX��ֵΪ90

A1:MOV DL,X[SI-1]          ;A1�Ĺ�����ʵ�ּӷ����㣬��X����DL

   MOV AL,Y[DI-1]          ;��Y����AL

   POPF                    ;CF��ջ

   ADC AL,DL               ;AL��DL��Ӳ��ѽ������AL

   AAA                     ;�����λ

   PUSHF                   ;CF��ջ

    ADD AL,30H             ;��ALת��ASC����

   MOV Z[BX],AL            ;AL���ݴ���Z

   DEC SI                  ;SI-1

   DEC DI                  ;DI-1

   DEC BX                  ;BX-1

LOOP A1                    ;CX-1����ѭ��ִ��A1

   INC BX                  ;BX-1

A2: CMP Z[BX],30H          ;A2�Ĺ������ж�Z�ĸ�λ�Ƿ�Ϊ0�����Ϊ0������ʾ

   JNZ A3                  ;���Z�ĸ�λ��Ϊ0������ת��A3

   INC BX                  ;���Z�ĸ�λΪ0����BX-1

LOOP A2                    ;ѭ��ִ��A2

A3:LEA DX,Z[BX]            ;A3�εĹ�������ʾ������Z����Z��ַ������DX

   MOV AH,09H              ;����09H��ʾ������ʾZ

   INT 21H 

   MOV AH,4CH              ;�˻ص�DOS

   INT 21H

CODE ENDS 

END GO
