.section .rodata
.data
#δ�Ż�����
.text
#����fun����
	.global fun
fun:
	push ebp
	mov ebp,esp
	# ����ջ֡
	sub esp,esp,4d
	# ���ز����������Ĵ���
	# �����ڴ���
	mov ax,1d
	mov ax,[ebp-16d]
	.L1 :
	# ��������
	ret 
#����main����
	.global main
main:
	push ebp
	mov ebp,esp
	# ����ջ֡
	sub esp,esp,12d
	# ���ز����������Ĵ���
	# �����ڴ���
	mov ax,0d
	mov ax,[ebp-16d]
	mov ax,1d
	mov ax,[ebp-20d]
	mov ax,[ebp-16d]
	mov bx,[ebp-20d]
	add ax,ax,bx
	mov ax,[ebp-24d]
	mov ax,[ebp-24d]
	mov ax,[ebp-16d]
	call fun
	add esp,esp,0d
	mov ax,0d
	jmp .L2
	.L2 :
	# ��������
	ret 
