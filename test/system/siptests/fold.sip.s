	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0
	.p2align	4, 0x90                         ## -- Begin function fold
_fold:                                  ## @fold
	.cfi_startproc
## %bb.0:                               ## %entry
	pushq	%r15
	.cfi_def_cfa_offset 16
	pushq	%r14
	.cfi_def_cfa_offset 24
	pushq	%r12
	.cfi_def_cfa_offset 32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	subq	$40, %rsp
	.cfi_def_cfa_offset 80
	.cfi_offset %rbx, -40
	.cfi_offset %r12, -32
	.cfi_offset %r14, -24
	.cfi_offset %r15, -16
	movq	%rdi, 8(%rsp)
	movq	%rsi, 16(%rsp)
	movq	%rdx, 24(%rsp)
	movq	$0, (%rsp)
	movq	$0, 32(%rsp)
	movl	$100, %edi
	callq	__tip_output
	movq	16(%rsp), %rdi
	movq	%rdi, (%rsp)
	callq	__tip_output
	movq	8(%rsp), %r15
	movq	(%r15), %rax
	leaq	8(%r15,%rax,8), %r14
	movl	$1, %edi
	movl	$8, %esi
	callq	_calloc
	movq	%rax, %r12
	addq	$8, %r15
	movq	%r15, (%rax)
	leaq	__tip_ftable(%rip), %r15
	cmpq	%r14, (%r12)
	je	LBB0_3
	.p2align	4, 0x90
LBB0_2:                                 ## %forbody
                                        ## =>This Inner Loop Header: Depth=1
	movq	(%r12), %rbx
	movq	(%rbx), %rsi
	movq	%rsi, 32(%rsp)
	movq	24(%rsp), %rax
	movq	(%rsp), %rdi
	callq	*(%r15,%rax,8)
	movq	%rax, (%rsp)
	movq	%rax, %rdi
	callq	__tip_output
	addq	$8, %rbx
	movq	%rbx, (%r12)
	cmpq	%r14, (%r12)
	jne	LBB0_2
LBB0_3:                                 ## %forend
	movq	(%rsp), %rax
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r14
	popq	%r15
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function sum
_sum:                                   ## @sum
	.cfi_startproc
## %bb.0:                               ## %entry
	movq	%rdi, -16(%rsp)
	movq	%rsi, -8(%rsp)
	leaq	(%rdi,%rsi), %rax
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function orodd
_orodd:                                 ## @orodd
	.cfi_startproc
## %bb.0:                               ## %entry
	movq	%rdi, -16(%rsp)
	movq	%rsi, -8(%rsp)
	movq	%rsi, %rax
	shrq	$63, %rax
	addq	%rsi, %rax
	andq	$-2, %rax
	cmpq	%rax, %rsi
	sete	%al
	testq	%rdi, %rdi
	setne	%cl
	andb	%al, %cl
	movzbl	%cl, %eax
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__tip_main                      ## -- Begin function _tip_main
	.p2align	4, 0x90
__tip_main:                             ## @_tip_main
	.cfi_startproc
## %bb.0:                               ## %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -16
	movq	$0, 8(%rsp)
	movl	$1, %edi
	movl	$4, %esi
	callq	_calloc
	movq	%rax, %rbx
	movq	$1, (%rax)
	movl	$6, %edi
	movl	$8, %esi
	callq	_calloc
	movq	$5, (%rax)
	cmpq	$5, (%rbx)
	jg	LBB3_2
## %bb.1:                               ## %body
	movq	(%rbx), %rcx
	movq	$13, (%rax,%rcx,8)
	leaq	1(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$7, 8(%rax,%rcx,8)
	leaq	2(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$-4, 16(%rax,%rcx,8)
	leaq	3(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$14, 24(%rax,%rcx,8)
	leaq	4(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 32(%rax,%rcx,8)
	addq	$5, %rcx
	movq	%rcx, (%rbx)
LBB3_2:                                 ## %end
	movq	%rax, 8(%rsp)
	movq	(%rax), %rdi
	callq	__tip_output
	movq	8(%rsp), %rdi
	movl	$1, %edx
	xorl	%esi, %esi
	callq	*__tip_ftable(%rip)
	cmpq	$30, %rax
	je	LBB3_4
## %bb.3:                               ## %then2
	movq	8(%rsp), %rdi
	movl	$1, %edx
	xorl	%esi, %esi
	callq	*__tip_ftable(%rip)
	movq	%rax, %rdi
	callq	__tip_error
LBB3_4:                                 ## %ifmerge2
	movq	8(%rsp), %rdi
	movl	$1, %esi
	movl	$2, %edx
	callq	*__tip_ftable(%rip)
	xorq	$1, %rax
	jne	LBB3_6
## %bb.5:                               ## %then3
	movq	$-1, %rdi
	callq	__tip_error
LBB3_6:                                 ## %ifmerge3
	xorl	%eax, %eax
	addq	$16, %rsp
	popq	%rbx
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__DATA,__const
	.p2align	4                               ## @_tip_ftable
__tip_ftable:
	.quad	_fold
	.quad	_sum
	.quad	_orodd
	.quad	__tip_main

	.section	__TEXT,__const
	.globl	__tip_num_inputs                ## @_tip_num_inputs
	.p2align	3
__tip_num_inputs:
	.quad	0                               ## 0x0

	.comm	__tip_input_array,1,3           ## @_tip_input_array
.subsections_via_symbols
