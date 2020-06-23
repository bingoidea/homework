.section .rodata
.data
#未优化代码
.text
#函数main代码
	.global main
main:
	# 函数入口
	mov ip,esp
	push {ebp,ip,lr,pc}
	sub ebp,ip,#4
	# 开辟栈帧
	sub esp,esp,#20
	# 加载参数变量到寄存器
	# 函数内代码
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
	# 函数出口
	push {ebp,ip,lr,pc}
