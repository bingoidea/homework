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
	sub esp,esp,16d
	# ���ز����������Ĵ���
	# �����ڴ���
	mov ax,1d
	mov ax,[ebp-16d]
	mov ax,3d
	mov ax,[ebp-20d]
	mov ax,0d
	mov ax,[ebp-24d]
	mov ax,[ebp-16d]
	mov bx,[ebp-20d]
	add ax,ax,bx
	mov ax,[ebp-28d]
	mov ax,[ebp-28d]
	mov ax,[ebp-24d]
	.L1 :
	# ��������
	ret 
