	.file	"demo9.c"
	.intel_syntax noprefix
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
	.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	push ebp
	mov ebp,esp
	and esp, -16
	sub esp,20
	call	___main
	mov eax,DWORD PTR [ebp-4]
	mov ebx,2
	imul ebx
	mov DWORD PTR[ebp-4],eax
L1:
	mov esp,ebp
	pop ebp
	ret
	.ident	"GCC: (GNU) 6.4.0"
