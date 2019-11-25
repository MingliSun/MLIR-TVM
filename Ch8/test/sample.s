	.text
	.file	"LLVMDialectModule"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%r15
	.cfi_def_cfa_offset 16
	pushq	%r14
	.cfi_def_cfa_offset 24
	pushq	%r13
	.cfi_def_cfa_offset 32
	pushq	%r12
	.cfi_def_cfa_offset 40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset %rbx, -48
	.cfi_offset %r12, -40
	.cfi_offset %r13, -32
	.cfi_offset %r14, -24
	.cfi_offset %r15, -16
	movl	$48, %edi
	callq	malloc
	movq	%rax, %r12
	xorl	%r15d, %r15d
	movl	$48, %edi
	callq	malloc
	movq	%rax, %r14
	movabsq	$4607182418800017408, %rax # imm = 0x3FF0000000000000
	movq	%rax, (%r14)
	movabsq	$4611686018427387904, %rax # imm = 0x4000000000000000
	movq	%rax, 8(%r14)
	movabsq	$4613937818241073152, %rax # imm = 0x4008000000000000
	movq	%rax, 16(%r14)
	movabsq	$4616189618054758400, %rax # imm = 0x4010000000000000
	movq	%rax, 24(%r14)
	movabsq	$4617315517961601024, %rax # imm = 0x4014000000000000
	movq	%rax, 32(%r14)
	movabsq	$4618441417868443648, %rax # imm = 0x4018000000000000
	movq	%rax, 40(%r14)
	xorl	%eax, %eax
	cmpq	$1, %rax
	jle	.LBB0_2
	jmp	.LBB0_6
	.p2align	4, 0x90
.LBB0_5:                                #   in Loop: Header=BB0_2 Depth=1
	incq	%rax
	addq	$24, %r15
	cmpq	$1, %rax
	jg	.LBB0_6
.LBB0_2:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_4 Depth 2
	movq	%r15, %rcx
	xorl	%edx, %edx
	cmpq	$2, %rdx
	jg	.LBB0_5
	.p2align	4, 0x90
.LBB0_4:                                #   Parent Loop BB0_2 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movsd	(%r14,%rcx), %xmm0      # xmm0 = mem[0],zero
	addsd	%xmm0, %xmm0
	movsd	%xmm0, (%r12,%rcx)
	incq	%rdx
	addq	$8, %rcx
	cmpq	$2, %rdx
	jle	.LBB0_4
	jmp	.LBB0_5
.LBB0_6:
	xorl	%r13d, %r13d
	xorl	%r15d, %r15d
	cmpq	$1, %r15
	jle	.LBB0_8
	jmp	.LBB0_12
	.p2align	4, 0x90
.LBB0_11:                               #   in Loop: Header=BB0_8 Depth=1
	movl	$nl, %edi
	xorl	%eax, %eax
	callq	printf
	incq	%r15
	addq	$24, %r13
	cmpq	$1, %r15
	jg	.LBB0_12
.LBB0_8:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_10 Depth 2
	xorl	%ebx, %ebx
	cmpq	$2, %rbx
	jg	.LBB0_11
	.p2align	4, 0x90
.LBB0_10:                               #   Parent Loop BB0_8 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	leaq	(%r12,%r13), %rax
	movsd	(%rax,%rbx,8), %xmm0    # xmm0 = mem[0],zero
	movl	$frmt_spec, %edi
	movb	$1, %al
	callq	printf
	incq	%rbx
	cmpq	$2, %rbx
	jle	.LBB0_10
	jmp	.LBB0_11
.LBB0_12:
	movq	%r14, %rdi
	callq	free
	movq	%r12, %rdi
	callq	free
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	nl,@object              # @nl
	.section	.rodata,"a",@progbits
nl:
	.asciz	"\n"
	.size	nl, 2

	.type	frmt_spec,@object       # @frmt_spec
frmt_spec:
	.asciz	"%f "
	.size	frmt_spec, 4


	.section	".note.GNU-stack","",@progbits
