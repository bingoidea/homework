.section .rodata
.data
#未优化代码
.text
#函数fun代码
	.global fun
fun:
	push ebp
	mov ebp,esp
	# 开辟栈帧
	sub esp,esp,4d
	# 加载参数变量到寄存器
	# 函数内代码
	mov ax,1d
	mov ax,[ebp-16d]
	.L1 :
	# 函数出口
	ret 
#函数main代码
	.global main
main:
	push ebp
	mov ebp,esp
	# 开辟栈帧
	sub esp,esp,12d
	# 加载参数变量到寄存器
	# 函数内代码
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
	# 函数出口
	ret 
