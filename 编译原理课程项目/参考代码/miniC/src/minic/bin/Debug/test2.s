.section .rodata
.data
#δ�Ż�����
.text
#����main����
	.global main
main:
	# �������
	mov ip,esp
	push {ebp,ip,lr,pc}
	sub ebp,ip,#4
	# ����ջ֡
	sub esp,esp,#20
	# ���ز����������Ĵ���
	# �����ڴ���
	mov ax,#0
	mov ax,#-20[ebp]
	mov ax,#0
	mov ax,#-16[ebp]
	.L2 :
	mov ax,#-16[ebp]
	mov bx,#10
	cmp ax,bx
	movlt ax,#1
	movge ax,#0
	mov ax,#-24[ebp]
	mov ax,#-24[ebp]
	cmp ax,#0
	jz .L3
	jmp .L5
	.L6 :
	mov ax,#-16[ebp]
	mov ax,#-28[ebp]
	mov ax,#-16[ebp]
	mov bx,#1
	add ax,ax,bx
	mov ax,#-16[ebp]
	mov ax,#-28[ebp]
	mov ax,#-16[ebp]
	jmp .L2
	.L5 :
	mov ax,#-20[ebp]
	mov ax,#-32[ebp]
	mov ax,#-20[ebp]
	mov bx,#1
	add ax,ax,bx
	mov ax,#-20[ebp]
	mov ax,#-32[ebp]
	mov ax,#-20[ebp]
	jmp .L6
	.L3 :
	mov ax,#0
	jmp .L1
	.L1 :
	# ��������
	push {ebp,ip,lr,pc}
