;
;  RX610アーキテクチャ依存出力ファイル
;
;  割込みベクタ及び割込みハンドラ定義
;


	.text
	.extern	_kernel_interrupt
	.extern	__kernel_default_int_handler
	.extern	__kernel_default_exc_handler


	.extern	_target_timer_handler
	.global	__kernel_target_timer_handler_28_entry
__kernel_target_timer_handler_28_entry:
	pushm	r1-r5						; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#28, r1	; 割込みハンドラ番号をr1へ 
	mov.l	#_target_timer_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt			; 共通ルーチンへ 


	.extern	_target_timer_cmt1_handler
	.global	__kernel_target_timer_cmt1_handler_29_entry
__kernel_target_timer_cmt1_handler_29_entry:
	pushm	r1-r5						; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#29, r1	; 割込みハンドラ番号をr1へ 
	mov.l	#_target_timer_cmt1_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt			; 共通ルーチンへ 


	.extern	_rx72n_edmac_interrput_wrapper
	.global	__kernel_rx72n_edmac_interrput_wrapper_113_entry
__kernel_rx72n_edmac_interrput_wrapper_113_entry:
	pushm	r1-r5						; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#113, r1	; 割込みハンドラ番号をr1へ 
	mov.l	#_rx72n_edmac_interrput_wrapper, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt			; 共通ルーチンへ 


	.extern	_target_timer_cmt2_handler
	.global	__kernel_target_timer_cmt2_handler_128_entry
__kernel_target_timer_cmt2_handler_128_entry:
	pushm	r1-r5						; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#128, r1	; 割込みハンドラ番号をr1へ 
	mov.l	#_target_timer_cmt2_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt			; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_0
__kernel_default_int_handler_entry_0:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#0, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_1
__kernel_default_int_handler_entry_1:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#1, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_2
__kernel_default_int_handler_entry_2:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#2, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_3
__kernel_default_int_handler_entry_3:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#3, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_4
__kernel_default_int_handler_entry_4:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#4, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_5
__kernel_default_int_handler_entry_5:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#5, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_6
__kernel_default_int_handler_entry_6:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#6, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_7
__kernel_default_int_handler_entry_7:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#7, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_8
__kernel_default_int_handler_entry_8:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#8, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_9
__kernel_default_int_handler_entry_9:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#9, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_10
__kernel_default_int_handler_entry_10:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#10, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_11
__kernel_default_int_handler_entry_11:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#11, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_12
__kernel_default_int_handler_entry_12:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#12, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_13
__kernel_default_int_handler_entry_13:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#13, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_14
__kernel_default_int_handler_entry_14:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#14, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_15
__kernel_default_int_handler_entry_15:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#15, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_16
__kernel_default_int_handler_entry_16:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#16, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_17
__kernel_default_int_handler_entry_17:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#17, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_18
__kernel_default_int_handler_entry_18:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#18, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_19
__kernel_default_int_handler_entry_19:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#19, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_20
__kernel_default_int_handler_entry_20:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#20, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_21
__kernel_default_int_handler_entry_21:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#21, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_22
__kernel_default_int_handler_entry_22:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#22, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_23
__kernel_default_int_handler_entry_23:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#23, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_24
__kernel_default_int_handler_entry_24:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#24, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_25
__kernel_default_int_handler_entry_25:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#25, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_26
__kernel_default_int_handler_entry_26:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#26, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_27
__kernel_default_int_handler_entry_27:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#27, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_28
__kernel_default_int_handler_entry_28:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#28, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_29
__kernel_default_int_handler_entry_29:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#29, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_30
__kernel_default_int_handler_entry_30:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#30, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_31
__kernel_default_int_handler_entry_31:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#31, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_32
__kernel_default_int_handler_entry_32:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#32, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_33
__kernel_default_int_handler_entry_33:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#33, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_34
__kernel_default_int_handler_entry_34:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#34, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_35
__kernel_default_int_handler_entry_35:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#35, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_36
__kernel_default_int_handler_entry_36:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#36, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_37
__kernel_default_int_handler_entry_37:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#37, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_38
__kernel_default_int_handler_entry_38:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#38, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_39
__kernel_default_int_handler_entry_39:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#39, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_40
__kernel_default_int_handler_entry_40:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#40, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_41
__kernel_default_int_handler_entry_41:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#41, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_42
__kernel_default_int_handler_entry_42:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#42, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_43
__kernel_default_int_handler_entry_43:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#43, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_44
__kernel_default_int_handler_entry_44:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#44, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_45
__kernel_default_int_handler_entry_45:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#45, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_46
__kernel_default_int_handler_entry_46:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#46, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_47
__kernel_default_int_handler_entry_47:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#47, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_48
__kernel_default_int_handler_entry_48:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#48, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_49
__kernel_default_int_handler_entry_49:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#49, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_50
__kernel_default_int_handler_entry_50:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#50, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_51
__kernel_default_int_handler_entry_51:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#51, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_52
__kernel_default_int_handler_entry_52:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#52, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_53
__kernel_default_int_handler_entry_53:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#53, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_54
__kernel_default_int_handler_entry_54:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#54, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_55
__kernel_default_int_handler_entry_55:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#55, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_56
__kernel_default_int_handler_entry_56:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#56, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_57
__kernel_default_int_handler_entry_57:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#57, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_58
__kernel_default_int_handler_entry_58:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#58, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_59
__kernel_default_int_handler_entry_59:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#59, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_60
__kernel_default_int_handler_entry_60:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#60, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_61
__kernel_default_int_handler_entry_61:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#61, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_62
__kernel_default_int_handler_entry_62:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#62, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_63
__kernel_default_int_handler_entry_63:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#63, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_64
__kernel_default_int_handler_entry_64:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#64, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_65
__kernel_default_int_handler_entry_65:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#65, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_66
__kernel_default_int_handler_entry_66:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#66, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_67
__kernel_default_int_handler_entry_67:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#67, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_68
__kernel_default_int_handler_entry_68:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#68, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_69
__kernel_default_int_handler_entry_69:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#69, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_70
__kernel_default_int_handler_entry_70:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#70, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_71
__kernel_default_int_handler_entry_71:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#71, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_72
__kernel_default_int_handler_entry_72:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#72, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_73
__kernel_default_int_handler_entry_73:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#73, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_74
__kernel_default_int_handler_entry_74:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#74, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_75
__kernel_default_int_handler_entry_75:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#75, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_76
__kernel_default_int_handler_entry_76:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#76, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_77
__kernel_default_int_handler_entry_77:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#77, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_78
__kernel_default_int_handler_entry_78:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#78, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_79
__kernel_default_int_handler_entry_79:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#79, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_80
__kernel_default_int_handler_entry_80:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#80, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_81
__kernel_default_int_handler_entry_81:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#81, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_82
__kernel_default_int_handler_entry_82:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#82, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_83
__kernel_default_int_handler_entry_83:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#83, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_84
__kernel_default_int_handler_entry_84:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#84, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_85
__kernel_default_int_handler_entry_85:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#85, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_86
__kernel_default_int_handler_entry_86:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#86, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_87
__kernel_default_int_handler_entry_87:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#87, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_88
__kernel_default_int_handler_entry_88:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#88, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_89
__kernel_default_int_handler_entry_89:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#89, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_90
__kernel_default_int_handler_entry_90:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#90, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_91
__kernel_default_int_handler_entry_91:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#91, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_92
__kernel_default_int_handler_entry_92:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#92, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_93
__kernel_default_int_handler_entry_93:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#93, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_94
__kernel_default_int_handler_entry_94:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#94, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_95
__kernel_default_int_handler_entry_95:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#95, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_96
__kernel_default_int_handler_entry_96:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#96, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_97
__kernel_default_int_handler_entry_97:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#97, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_98
__kernel_default_int_handler_entry_98:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#98, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_99
__kernel_default_int_handler_entry_99:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#99, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_100
__kernel_default_int_handler_entry_100:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#100, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_101
__kernel_default_int_handler_entry_101:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#101, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_102
__kernel_default_int_handler_entry_102:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#102, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_103
__kernel_default_int_handler_entry_103:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#103, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_104
__kernel_default_int_handler_entry_104:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#104, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_105
__kernel_default_int_handler_entry_105:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#105, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_106
__kernel_default_int_handler_entry_106:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#106, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_107
__kernel_default_int_handler_entry_107:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#107, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_108
__kernel_default_int_handler_entry_108:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#108, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_109
__kernel_default_int_handler_entry_109:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#109, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_110
__kernel_default_int_handler_entry_110:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#110, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_111
__kernel_default_int_handler_entry_111:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#111, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_112
__kernel_default_int_handler_entry_112:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#112, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_113
__kernel_default_int_handler_entry_113:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#113, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_114
__kernel_default_int_handler_entry_114:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#114, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_115
__kernel_default_int_handler_entry_115:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#115, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_116
__kernel_default_int_handler_entry_116:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#116, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_117
__kernel_default_int_handler_entry_117:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#117, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_118
__kernel_default_int_handler_entry_118:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#118, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_119
__kernel_default_int_handler_entry_119:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#119, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_120
__kernel_default_int_handler_entry_120:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#120, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_121
__kernel_default_int_handler_entry_121:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#121, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_122
__kernel_default_int_handler_entry_122:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#122, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_123
__kernel_default_int_handler_entry_123:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#123, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_124
__kernel_default_int_handler_entry_124:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#124, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_125
__kernel_default_int_handler_entry_125:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#125, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_126
__kernel_default_int_handler_entry_126:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#126, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_127
__kernel_default_int_handler_entry_127:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#127, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_128
__kernel_default_int_handler_entry_128:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#128, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_129
__kernel_default_int_handler_entry_129:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#129, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_130
__kernel_default_int_handler_entry_130:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#130, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_131
__kernel_default_int_handler_entry_131:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#131, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_132
__kernel_default_int_handler_entry_132:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#132, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_133
__kernel_default_int_handler_entry_133:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#133, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_134
__kernel_default_int_handler_entry_134:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#134, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_135
__kernel_default_int_handler_entry_135:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#135, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_136
__kernel_default_int_handler_entry_136:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#136, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_137
__kernel_default_int_handler_entry_137:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#137, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_138
__kernel_default_int_handler_entry_138:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#138, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_139
__kernel_default_int_handler_entry_139:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#139, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_140
__kernel_default_int_handler_entry_140:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#140, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_141
__kernel_default_int_handler_entry_141:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#141, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_142
__kernel_default_int_handler_entry_142:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#142, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_143
__kernel_default_int_handler_entry_143:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#143, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_144
__kernel_default_int_handler_entry_144:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#144, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_145
__kernel_default_int_handler_entry_145:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#145, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_146
__kernel_default_int_handler_entry_146:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#146, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_147
__kernel_default_int_handler_entry_147:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#147, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_148
__kernel_default_int_handler_entry_148:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#148, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_149
__kernel_default_int_handler_entry_149:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#149, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_150
__kernel_default_int_handler_entry_150:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#150, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_151
__kernel_default_int_handler_entry_151:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#151, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_152
__kernel_default_int_handler_entry_152:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#152, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_153
__kernel_default_int_handler_entry_153:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#153, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_154
__kernel_default_int_handler_entry_154:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#154, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_155
__kernel_default_int_handler_entry_155:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#155, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_156
__kernel_default_int_handler_entry_156:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#156, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_157
__kernel_default_int_handler_entry_157:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#157, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_158
__kernel_default_int_handler_entry_158:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#158, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_159
__kernel_default_int_handler_entry_159:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#159, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_160
__kernel_default_int_handler_entry_160:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#160, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_161
__kernel_default_int_handler_entry_161:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#161, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_162
__kernel_default_int_handler_entry_162:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#162, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_163
__kernel_default_int_handler_entry_163:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#163, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_164
__kernel_default_int_handler_entry_164:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#164, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_165
__kernel_default_int_handler_entry_165:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#165, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_166
__kernel_default_int_handler_entry_166:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#166, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_167
__kernel_default_int_handler_entry_167:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#167, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_168
__kernel_default_int_handler_entry_168:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#168, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_169
__kernel_default_int_handler_entry_169:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#169, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_170
__kernel_default_int_handler_entry_170:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#170, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_171
__kernel_default_int_handler_entry_171:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#171, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_172
__kernel_default_int_handler_entry_172:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#172, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_173
__kernel_default_int_handler_entry_173:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#173, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_174
__kernel_default_int_handler_entry_174:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#174, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_175
__kernel_default_int_handler_entry_175:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#175, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_176
__kernel_default_int_handler_entry_176:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#176, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_177
__kernel_default_int_handler_entry_177:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#177, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_178
__kernel_default_int_handler_entry_178:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#178, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_179
__kernel_default_int_handler_entry_179:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#179, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_180
__kernel_default_int_handler_entry_180:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#180, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_181
__kernel_default_int_handler_entry_181:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#181, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_182
__kernel_default_int_handler_entry_182:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#182, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_183
__kernel_default_int_handler_entry_183:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#183, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_184
__kernel_default_int_handler_entry_184:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#184, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_185
__kernel_default_int_handler_entry_185:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#185, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_186
__kernel_default_int_handler_entry_186:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#186, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_187
__kernel_default_int_handler_entry_187:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#187, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_188
__kernel_default_int_handler_entry_188:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#188, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_189
__kernel_default_int_handler_entry_189:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#189, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_190
__kernel_default_int_handler_entry_190:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#190, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_191
__kernel_default_int_handler_entry_191:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#191, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_192
__kernel_default_int_handler_entry_192:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#192, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_193
__kernel_default_int_handler_entry_193:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#193, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_194
__kernel_default_int_handler_entry_194:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#194, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_195
__kernel_default_int_handler_entry_195:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#195, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_196
__kernel_default_int_handler_entry_196:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#196, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_197
__kernel_default_int_handler_entry_197:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#197, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_198
__kernel_default_int_handler_entry_198:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#198, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_199
__kernel_default_int_handler_entry_199:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#199, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_200
__kernel_default_int_handler_entry_200:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#200, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_201
__kernel_default_int_handler_entry_201:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#201, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_202
__kernel_default_int_handler_entry_202:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#202, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_203
__kernel_default_int_handler_entry_203:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#203, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_204
__kernel_default_int_handler_entry_204:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#204, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_205
__kernel_default_int_handler_entry_205:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#205, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_206
__kernel_default_int_handler_entry_206:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#206, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_207
__kernel_default_int_handler_entry_207:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#207, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_208
__kernel_default_int_handler_entry_208:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#208, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_209
__kernel_default_int_handler_entry_209:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#209, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_210
__kernel_default_int_handler_entry_210:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#210, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_211
__kernel_default_int_handler_entry_211:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#211, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_212
__kernel_default_int_handler_entry_212:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#212, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_213
__kernel_default_int_handler_entry_213:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#213, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_214
__kernel_default_int_handler_entry_214:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#214, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_215
__kernel_default_int_handler_entry_215:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#215, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_216
__kernel_default_int_handler_entry_216:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#216, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_217
__kernel_default_int_handler_entry_217:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#217, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_218
__kernel_default_int_handler_entry_218:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#218, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_219
__kernel_default_int_handler_entry_219:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#219, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_220
__kernel_default_int_handler_entry_220:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#220, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_221
__kernel_default_int_handler_entry_221:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#221, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_222
__kernel_default_int_handler_entry_222:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#222, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_223
__kernel_default_int_handler_entry_223:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#223, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_224
__kernel_default_int_handler_entry_224:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#224, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_225
__kernel_default_int_handler_entry_225:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#225, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_226
__kernel_default_int_handler_entry_226:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#226, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_227
__kernel_default_int_handler_entry_227:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#227, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_228
__kernel_default_int_handler_entry_228:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#228, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_229
__kernel_default_int_handler_entry_229:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#229, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_230
__kernel_default_int_handler_entry_230:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#230, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_231
__kernel_default_int_handler_entry_231:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#231, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_232
__kernel_default_int_handler_entry_232:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#232, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_233
__kernel_default_int_handler_entry_233:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#233, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_234
__kernel_default_int_handler_entry_234:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#234, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_235
__kernel_default_int_handler_entry_235:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#235, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_236
__kernel_default_int_handler_entry_236:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#236, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_237
__kernel_default_int_handler_entry_237:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#237, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_238
__kernel_default_int_handler_entry_238:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#238, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_239
__kernel_default_int_handler_entry_239:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#239, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_240
__kernel_default_int_handler_entry_240:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#240, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_241
__kernel_default_int_handler_entry_241:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#241, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_242
__kernel_default_int_handler_entry_242:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#242, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_243
__kernel_default_int_handler_entry_243:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#243, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_244
__kernel_default_int_handler_entry_244:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#244, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_245
__kernel_default_int_handler_entry_245:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#245, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_246
__kernel_default_int_handler_entry_246:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#246, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_247
__kernel_default_int_handler_entry_247:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#247, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_248
__kernel_default_int_handler_entry_248:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#248, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_249
__kernel_default_int_handler_entry_249:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#249, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_250
__kernel_default_int_handler_entry_250:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#250, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_251
__kernel_default_int_handler_entry_251:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#251, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_252
__kernel_default_int_handler_entry_252:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#252, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_253
__kernel_default_int_handler_entry_253:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#253, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_254
__kernel_default_int_handler_entry_254:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#254, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	__kernel_default_int_handler_entry_255
__kernel_default_int_handler_entry_255:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#255, r1						; 割込みハンドラ番号をr1へ 
	mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_interrupt					; 共通ルーチンへ 


	.extern	_kernel_exception

	.extern	_cpuexc_handler
	.global	__kernel_cpuexc_handler_25_entry
__kernel_cpuexc_handler_25_entry:
	pushm	r1-r5						; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#25, r1	; CPU例外ハンドラ番号をr1へ 
	mov.l	#_cpuexc_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_exception			; 共通ルーチンへ 


	.extern	__kernel_default_exc_handler_entry
__kernel_default_exc_handler_entry:
	pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 
	mov.l	#0FFFFFFFFH, r1						; CPU例外ハンドラ番号をr1へ 
	mov.l	#__kernel_default_exc_handler, r2	; ハンドラのアドレスをr2へ 
	bra.a	_kernel_exception					; 共通ルーチンへ 


;
;  可変ベクタテーブル
;

	.extern 	 _startw


	.section C$VECT

	.glb __vvector_table

__vvector_table:
	.word	__kernel_default_int_handler_entry_0 	 	 ; 00 
	.word	__kernel_default_int_handler_entry_1 	 	 ; 01 
	.word	__kernel_default_int_handler_entry_2 	 	 ; 02 
	.word	__kernel_default_int_handler_entry_3 	 	 ; 03 
	.word	__kernel_default_int_handler_entry_4 	 	 ; 04 
	.word	__kernel_default_int_handler_entry_5 	 	 ; 05 
	.word	__kernel_default_int_handler_entry_6 	 	 ; 06 
	.word	__kernel_default_int_handler_entry_7 	 	 ; 07 
	.word	__kernel_default_int_handler_entry_8 	 	 ; 08 
	.word	__kernel_default_int_handler_entry_9 	 	 ; 09 
	.word	__kernel_default_int_handler_entry_10 	 	 ; 10 
	.word	__kernel_default_int_handler_entry_11 	 	 ; 11 
	.word	__kernel_default_int_handler_entry_12 	 	 ; 12 
	.word	__kernel_default_int_handler_entry_13 	 	 ; 13 
	.word	__kernel_default_int_handler_entry_14 	 	 ; 14 
	.word	__kernel_default_int_handler_entry_15 	 	 ; 15 
	.word	__kernel_default_int_handler_entry_16 	 	 ; 16 
	.word	__kernel_default_int_handler_entry_17 	 	 ; 17 
	.word	__kernel_default_int_handler_entry_18 	 	 ; 18 
	.word	__kernel_default_int_handler_entry_19 	 	 ; 19 
	.word	__kernel_default_int_handler_entry_20 	 	 ; 20 
	.word	__kernel_default_int_handler_entry_21 	 	 ; 21 
	.word	__kernel_default_int_handler_entry_22 	 	 ; 22 
	.word	__kernel_default_int_handler_entry_23 	 	 ; 23 
	.word	__kernel_default_int_handler_entry_24 	 	 ; 24 
	.word	__kernel_default_int_handler_entry_25 	 	 ; 25 
	.word	__kernel_default_int_handler_entry_26 	 	 ; 26 
	.word	__kernel_default_int_handler_entry_27 	 	 ; 27 
	.word	__kernel_target_timer_handler_28_entry 	 	 ; 28 
	.word	__kernel_target_timer_cmt1_handler_29_entry 	 	 ; 29 
	.word	__kernel_default_int_handler_entry_30 	 	 ; 30 
	.word	__kernel_default_int_handler_entry_31 	 	 ; 31 
	.word	__kernel_default_int_handler_entry_32 	 	 ; 32 
	.word	__kernel_default_int_handler_entry_33 	 	 ; 33 
	.word	__kernel_default_int_handler_entry_34 	 	 ; 34 
	.word	__kernel_default_int_handler_entry_35 	 	 ; 35 
	.word	__kernel_default_int_handler_entry_36 	 	 ; 36 
	.word	__kernel_default_int_handler_entry_37 	 	 ; 37 
	.word	__kernel_default_int_handler_entry_38 	 	 ; 38 
	.word	__kernel_default_int_handler_entry_39 	 	 ; 39 
	.word	__kernel_default_int_handler_entry_40 	 	 ; 40 
	.word	__kernel_default_int_handler_entry_41 	 	 ; 41 
	.word	__kernel_default_int_handler_entry_42 	 	 ; 42 
	.word	__kernel_default_int_handler_entry_43 	 	 ; 43 
	.word	__kernel_default_int_handler_entry_44 	 	 ; 44 
	.word	__kernel_default_int_handler_entry_45 	 	 ; 45 
	.word	__kernel_default_int_handler_entry_46 	 	 ; 46 
	.word	__kernel_default_int_handler_entry_47 	 	 ; 47 
	.word	__kernel_default_int_handler_entry_48 	 	 ; 48 
	.word	__kernel_default_int_handler_entry_49 	 	 ; 49 
	.word	__kernel_default_int_handler_entry_50 	 	 ; 50 
	.word	__kernel_default_int_handler_entry_51 	 	 ; 51 
	.word	__kernel_default_int_handler_entry_52 	 	 ; 52 
	.word	__kernel_default_int_handler_entry_53 	 	 ; 53 
	.word	__kernel_default_int_handler_entry_54 	 	 ; 54 
	.word	__kernel_default_int_handler_entry_55 	 	 ; 55 
	.word	__kernel_default_int_handler_entry_56 	 	 ; 56 
	.word	__kernel_default_int_handler_entry_57 	 	 ; 57 
	.word	__kernel_default_int_handler_entry_58 	 	 ; 58 
	.word	__kernel_default_int_handler_entry_59 	 	 ; 59 
	.word	__kernel_default_int_handler_entry_60 	 	 ; 60 
	.word	__kernel_default_int_handler_entry_61 	 	 ; 61 
	.word	__kernel_default_int_handler_entry_62 	 	 ; 62 
	.word	__kernel_default_int_handler_entry_63 	 	 ; 63 
	.word	__kernel_default_int_handler_entry_64 	 	 ; 64 
	.word	__kernel_default_int_handler_entry_65 	 	 ; 65 
	.word	__kernel_default_int_handler_entry_66 	 	 ; 66 
	.word	__kernel_default_int_handler_entry_67 	 	 ; 67 
	.word	__kernel_default_int_handler_entry_68 	 	 ; 68 
	.word	__kernel_default_int_handler_entry_69 	 	 ; 69 
	.word	__kernel_default_int_handler_entry_70 	 	 ; 70 
	.word	__kernel_default_int_handler_entry_71 	 	 ; 71 
	.word	__kernel_default_int_handler_entry_72 	 	 ; 72 
	.word	__kernel_default_int_handler_entry_73 	 	 ; 73 
	.word	__kernel_default_int_handler_entry_74 	 	 ; 74 
	.word	__kernel_default_int_handler_entry_75 	 	 ; 75 
	.word	__kernel_default_int_handler_entry_76 	 	 ; 76 
	.word	__kernel_default_int_handler_entry_77 	 	 ; 77 
	.word	__kernel_default_int_handler_entry_78 	 	 ; 78 
	.word	__kernel_default_int_handler_entry_79 	 	 ; 79 
	.word	__kernel_default_int_handler_entry_80 	 	 ; 80 
	.word	__kernel_default_int_handler_entry_81 	 	 ; 81 
	.word	__kernel_default_int_handler_entry_82 	 	 ; 82 
	.word	__kernel_default_int_handler_entry_83 	 	 ; 83 
	.word	__kernel_default_int_handler_entry_84 	 	 ; 84 
	.word	__kernel_default_int_handler_entry_85 	 	 ; 85 
	.word	__kernel_default_int_handler_entry_86 	 	 ; 86 
	.word	__kernel_default_int_handler_entry_87 	 	 ; 87 
	.word	__kernel_default_int_handler_entry_88 	 	 ; 88 
	.word	__kernel_default_int_handler_entry_89 	 	 ; 89 
	.word	__kernel_default_int_handler_entry_90 	 	 ; 90 
	.word	__kernel_default_int_handler_entry_91 	 	 ; 91 
	.word	__kernel_default_int_handler_entry_92 	 	 ; 92 
	.word	__kernel_default_int_handler_entry_93 	 	 ; 93 
	.word	__kernel_default_int_handler_entry_94 	 	 ; 94 
	.word	__kernel_default_int_handler_entry_95 	 	 ; 95 
	.word	__kernel_default_int_handler_entry_96 	 	 ; 96 
	.word	__kernel_default_int_handler_entry_97 	 	 ; 97 
	.word	__kernel_default_int_handler_entry_98 	 	 ; 98 
	.word	__kernel_default_int_handler_entry_99 	 	 ; 99 
	.word	__kernel_default_int_handler_entry_100 	 	 ; 100 
	.word	__kernel_default_int_handler_entry_101 	 	 ; 101 
	.word	__kernel_default_int_handler_entry_102 	 	 ; 102 
	.word	__kernel_default_int_handler_entry_103 	 	 ; 103 
	.word	__kernel_default_int_handler_entry_104 	 	 ; 104 
	.word	__kernel_default_int_handler_entry_105 	 	 ; 105 
	.word	__kernel_default_int_handler_entry_106 	 	 ; 106 
	.word	__kernel_default_int_handler_entry_107 	 	 ; 107 
	.word	__kernel_default_int_handler_entry_108 	 	 ; 108 
	.word	__kernel_default_int_handler_entry_109 	 	 ; 109 
	.word	__kernel_default_int_handler_entry_110 	 	 ; 110 
	.word	__kernel_default_int_handler_entry_111 	 	 ; 111 
	.word	__kernel_default_int_handler_entry_112 	 	 ; 112 
	.word	__kernel_rx72n_edmac_interrput_wrapper_113_entry 	 	 ; 113 
	.word	__kernel_default_int_handler_entry_114 	 	 ; 114 
	.word	__kernel_default_int_handler_entry_115 	 	 ; 115 
	.word	__kernel_default_int_handler_entry_116 	 	 ; 116 
	.word	__kernel_default_int_handler_entry_117 	 	 ; 117 
	.word	__kernel_default_int_handler_entry_118 	 	 ; 118 
	.word	__kernel_default_int_handler_entry_119 	 	 ; 119 
	.word	__kernel_default_int_handler_entry_120 	 	 ; 120 
	.word	__kernel_default_int_handler_entry_121 	 	 ; 121 
	.word	__kernel_default_int_handler_entry_122 	 	 ; 122 
	.word	__kernel_default_int_handler_entry_123 	 	 ; 123 
	.word	__kernel_default_int_handler_entry_124 	 	 ; 124 
	.word	__kernel_default_int_handler_entry_125 	 	 ; 125 
	.word	__kernel_default_int_handler_entry_126 	 	 ; 126 
	.word	__kernel_default_int_handler_entry_127 	 	 ; 127 
	.word	__kernel_target_timer_cmt2_handler_128_entry 	 	 ; 128 
	.word	__kernel_default_int_handler_entry_129 	 	 ; 129 
	.word	__kernel_default_int_handler_entry_130 	 	 ; 130 
	.word	__kernel_default_int_handler_entry_131 	 	 ; 131 
	.word	__kernel_default_int_handler_entry_132 	 	 ; 132 
	.word	__kernel_default_int_handler_entry_133 	 	 ; 133 
	.word	__kernel_default_int_handler_entry_134 	 	 ; 134 
	.word	__kernel_default_int_handler_entry_135 	 	 ; 135 
	.word	__kernel_default_int_handler_entry_136 	 	 ; 136 
	.word	__kernel_default_int_handler_entry_137 	 	 ; 137 
	.word	__kernel_default_int_handler_entry_138 	 	 ; 138 
	.word	__kernel_default_int_handler_entry_139 	 	 ; 139 
	.word	__kernel_default_int_handler_entry_140 	 	 ; 140 
	.word	__kernel_default_int_handler_entry_141 	 	 ; 141 
	.word	__kernel_default_int_handler_entry_142 	 	 ; 142 
	.word	__kernel_default_int_handler_entry_143 	 	 ; 143 
	.word	__kernel_default_int_handler_entry_144 	 	 ; 144 
	.word	__kernel_default_int_handler_entry_145 	 	 ; 145 
	.word	__kernel_default_int_handler_entry_146 	 	 ; 146 
	.word	__kernel_default_int_handler_entry_147 	 	 ; 147 
	.word	__kernel_default_int_handler_entry_148 	 	 ; 148 
	.word	__kernel_default_int_handler_entry_149 	 	 ; 149 
	.word	__kernel_default_int_handler_entry_150 	 	 ; 150 
	.word	__kernel_default_int_handler_entry_151 	 	 ; 151 
	.word	__kernel_default_int_handler_entry_152 	 	 ; 152 
	.word	__kernel_default_int_handler_entry_153 	 	 ; 153 
	.word	__kernel_default_int_handler_entry_154 	 	 ; 154 
	.word	__kernel_default_int_handler_entry_155 	 	 ; 155 
	.word	__kernel_default_int_handler_entry_156 	 	 ; 156 
	.word	__kernel_default_int_handler_entry_157 	 	 ; 157 
	.word	__kernel_default_int_handler_entry_158 	 	 ; 158 
	.word	__kernel_default_int_handler_entry_159 	 	 ; 159 
	.word	__kernel_default_int_handler_entry_160 	 	 ; 160 
	.word	__kernel_default_int_handler_entry_161 	 	 ; 161 
	.word	__kernel_default_int_handler_entry_162 	 	 ; 162 
	.word	__kernel_default_int_handler_entry_163 	 	 ; 163 
	.word	__kernel_default_int_handler_entry_164 	 	 ; 164 
	.word	__kernel_default_int_handler_entry_165 	 	 ; 165 
	.word	__kernel_default_int_handler_entry_166 	 	 ; 166 
	.word	__kernel_default_int_handler_entry_167 	 	 ; 167 
	.word	__kernel_default_int_handler_entry_168 	 	 ; 168 
	.word	__kernel_default_int_handler_entry_169 	 	 ; 169 
	.word	__kernel_default_int_handler_entry_170 	 	 ; 170 
	.word	__kernel_default_int_handler_entry_171 	 	 ; 171 
	.word	__kernel_default_int_handler_entry_172 	 	 ; 172 
	.word	__kernel_default_int_handler_entry_173 	 	 ; 173 
	.word	__kernel_default_int_handler_entry_174 	 	 ; 174 
	.word	__kernel_default_int_handler_entry_175 	 	 ; 175 
	.word	__kernel_default_int_handler_entry_176 	 	 ; 176 
	.word	__kernel_default_int_handler_entry_177 	 	 ; 177 
	.word	__kernel_default_int_handler_entry_178 	 	 ; 178 
	.word	__kernel_default_int_handler_entry_179 	 	 ; 179 
	.word	__kernel_default_int_handler_entry_180 	 	 ; 180 
	.word	__kernel_default_int_handler_entry_181 	 	 ; 181 
	.word	__kernel_default_int_handler_entry_182 	 	 ; 182 
	.word	__kernel_default_int_handler_entry_183 	 	 ; 183 
	.word	__kernel_default_int_handler_entry_184 	 	 ; 184 
	.word	__kernel_default_int_handler_entry_185 	 	 ; 185 
	.word	__kernel_default_int_handler_entry_186 	 	 ; 186 
	.word	__kernel_default_int_handler_entry_187 	 	 ; 187 
	.word	__kernel_default_int_handler_entry_188 	 	 ; 188 
	.word	__kernel_default_int_handler_entry_189 	 	 ; 189 
	.word	__kernel_default_int_handler_entry_190 	 	 ; 190 
	.word	__kernel_default_int_handler_entry_191 	 	 ; 191 
	.word	__kernel_default_int_handler_entry_192 	 	 ; 192 
	.word	__kernel_default_int_handler_entry_193 	 	 ; 193 
	.word	__kernel_default_int_handler_entry_194 	 	 ; 194 
	.word	__kernel_default_int_handler_entry_195 	 	 ; 195 
	.word	__kernel_default_int_handler_entry_196 	 	 ; 196 
	.word	__kernel_default_int_handler_entry_197 	 	 ; 197 
	.word	__kernel_default_int_handler_entry_198 	 	 ; 198 
	.word	__kernel_default_int_handler_entry_199 	 	 ; 199 
	.word	__kernel_default_int_handler_entry_200 	 	 ; 200 
	.word	__kernel_default_int_handler_entry_201 	 	 ; 201 
	.word	__kernel_default_int_handler_entry_202 	 	 ; 202 
	.word	__kernel_default_int_handler_entry_203 	 	 ; 203 
	.word	__kernel_default_int_handler_entry_204 	 	 ; 204 
	.word	__kernel_default_int_handler_entry_205 	 	 ; 205 
	.word	__kernel_default_int_handler_entry_206 	 	 ; 206 
	.word	__kernel_default_int_handler_entry_207 	 	 ; 207 
	.word	__kernel_default_int_handler_entry_208 	 	 ; 208 
	.word	__kernel_default_int_handler_entry_209 	 	 ; 209 
	.word	__kernel_default_int_handler_entry_210 	 	 ; 210 
	.word	__kernel_default_int_handler_entry_211 	 	 ; 211 
	.word	__kernel_default_int_handler_entry_212 	 	 ; 212 
	.word	__kernel_default_int_handler_entry_213 	 	 ; 213 
	.word	__kernel_default_int_handler_entry_214 	 	 ; 214 
	.word	__kernel_default_int_handler_entry_215 	 	 ; 215 
	.word	__kernel_default_int_handler_entry_216 	 	 ; 216 
	.word	__kernel_default_int_handler_entry_217 	 	 ; 217 
	.word	__kernel_default_int_handler_entry_218 	 	 ; 218 
	.word	__kernel_default_int_handler_entry_219 	 	 ; 219 
	.word	__kernel_default_int_handler_entry_220 	 	 ; 220 
	.word	__kernel_default_int_handler_entry_221 	 	 ; 221 
	.word	__kernel_default_int_handler_entry_222 	 	 ; 222 
	.word	__kernel_default_int_handler_entry_223 	 	 ; 223 
	.word	__kernel_default_int_handler_entry_224 	 	 ; 224 
	.word	__kernel_default_int_handler_entry_225 	 	 ; 225 
	.word	__kernel_default_int_handler_entry_226 	 	 ; 226 
	.word	__kernel_default_int_handler_entry_227 	 	 ; 227 
	.word	__kernel_default_int_handler_entry_228 	 	 ; 228 
	.word	__kernel_default_int_handler_entry_229 	 	 ; 229 
	.word	__kernel_default_int_handler_entry_230 	 	 ; 230 
	.word	__kernel_default_int_handler_entry_231 	 	 ; 231 
	.word	__kernel_default_int_handler_entry_232 	 	 ; 232 
	.word	__kernel_default_int_handler_entry_233 	 	 ; 233 
	.word	__kernel_default_int_handler_entry_234 	 	 ; 234 
	.word	__kernel_default_int_handler_entry_235 	 	 ; 235 
	.word	__kernel_default_int_handler_entry_236 	 	 ; 236 
	.word	__kernel_default_int_handler_entry_237 	 	 ; 237 
	.word	__kernel_default_int_handler_entry_238 	 	 ; 238 
	.word	__kernel_default_int_handler_entry_239 	 	 ; 239 
	.word	__kernel_default_int_handler_entry_240 	 	 ; 240 
	.word	__kernel_default_int_handler_entry_241 	 	 ; 241 
	.word	__kernel_default_int_handler_entry_242 	 	 ; 242 
	.word	__kernel_default_int_handler_entry_243 	 	 ; 243 
	.word	__kernel_default_int_handler_entry_244 	 	 ; 244 
	.word	__kernel_default_int_handler_entry_245 	 	 ; 245 
	.word	__kernel_default_int_handler_entry_246 	 	 ; 246 
	.word	__kernel_default_int_handler_entry_247 	 	 ; 247 
	.word	__kernel_default_int_handler_entry_248 	 	 ; 248 
	.word	__kernel_default_int_handler_entry_249 	 	 ; 249 
	.word	__kernel_default_int_handler_entry_250 	 	 ; 250 
	.word	__kernel_default_int_handler_entry_251 	 	 ; 251 
	.word	__kernel_default_int_handler_entry_252 	 	 ; 252 
	.word	__kernel_default_int_handler_entry_253 	 	 ; 253 
	.word	__kernel_default_int_handler_entry_254 	 	 ; 254 
	.word	__kernel_default_int_handler_entry_255 	 	 ; 255 

;
;  固定ベクタテーブル
;

	 .section .fvect,ROMDATA,align=4 
	 .glb fvector_table 
fvector_table:

	 .space	 0x1c
	 .word	 0xFFFFFFFF 	 ; ROMコード(0xFFFFFF9C)
	 .word	 0xFFFFFFFF 	 ; 制御コード(0xFFFFFFA0), IDコード1 - 3
	 .word	 0xFFFFFFFF 	 ; IDコード4 - 7
	 .word	 0xFFFFFFFF 	 ; IDコード8 - 11
	 .word	 0xFFFFFFFF 	 ; IDコード12 - 15
	 .space	 0x20
	 .word	 __kernel_default_exc_handler_entry 	 	 ;  20:特権命令例外  
	 .space	 0x8
	 .word	 __kernel_default_exc_handler_entry 	 	 ;  23:未定義命令例外  
	 .space	 0x4
	 .word	 __kernel_cpuexc_handler_25_entry 	 	 ;  25:浮動小数点例外  
	 .space	 0x10
	 .word	 __kernel_default_exc_handler_entry 	 	 ;  30:ノンマスカブル例外  
;	 .word	 _startw 	 	 	 	 ;  31:リセット  
;wata
 
	.end
