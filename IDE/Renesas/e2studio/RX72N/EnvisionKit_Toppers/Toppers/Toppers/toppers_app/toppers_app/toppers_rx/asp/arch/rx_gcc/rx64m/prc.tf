$ 
$  TOPPERS/ASP Kernel
$      Toyohashi Open Platform for Embedded Real-Time Systems/
$      Advanced Standard Profile Kernel
$ 
$  Copyright (C) 2008-2010 by Witz Corporation, JAPAN
$ 
$  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
$  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
$  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
$  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
$      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
$      スコード中に含まれていること．
$  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
$      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
$      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
$      の無保証規定を掲載すること．
$  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
$      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
$      と．
$    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
$        作権表示，この利用条件および下記の無保証規定を掲載すること．
$    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
$        報告すること．
$  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
$      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
$      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
$      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
$      免責すること．
$ 
$  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
$  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
$  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
$  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
$  の責任を負わない．
$ 
$ 

$ 
$  アーキテクチャ依存テンプレート（RX64m用）
$ 



$ 
$  ATT_ISRで使用できる割込み番号とそれに対応する割込みハンドラ番号
$ 

$INTNO_ATTISR_VALID = INTNO_VALID$
$INHNO_ATTISR_VALID = INHNO_VALID$


$ 
$  DEF_INT／DEF_EXCで使用できる割込みハンドラ番号／CPU例外ハンドラ番号
$ 

$INHNO_DEFINH_VALID = INHNO_VALID$
$EXCNO_DEFEXC_VALID = EXCNO_VALID$


$ 
$  CFG_INTで使用できる割込み番号と割込み優先度
$ 

$INTNO_CFGINT_VALID = INHNO_VALID$
$INTPRI_CFGINT_VALID = { -15, -14,...,-1 }$


$ 
$  ターゲット非依存部に含まれる標準の割込み管理機能/例外管理機能の初期化処理を使用する
$ 

$OMIT_INITIALIZE_INTERRUPT = 0$
$OMIT_INITIALIZE_EXCEPTION = 0$


$ 
$  スタックサイズのチェック方法指定
$ 

$CHECK_STKSZ_ALIGN = 4$


$ 
$  タスクスタックサイズの最小値
$ 
$  タスク起動時に4byte,
$  割込み入口処理にて48byte, CPU例外入口処理にて84byte,
$  であるため, 最小値は88byteとする.
$ 

$TARGET_MIN_STKSZ = 88$


$ 
$  定数定義
$ 

$TA_POSEDGE = TA_EDGE$


$ 
$ ターゲット依存の割込み属性の定義
$ 

$TARGET_INTATR = TA_POSEDGE | TA_NEGEDGE | TA_BOTHEDGE | TA_LOWLEVEL$


$ 
$ ターゲット依存の割込みハンドラ属性の定義
$ 

$TARGET_INHATR = TA_NONKERNEL$


$ 
$ カーネル管理外割込みハンドラは固定させないため,
$ INTNO_FIX_KERNEL
$ INHNO_FIX_KERNEL
$ INHNO_FIX_NONKERNEL
$ INHNO_FIX_NONKERNEL
$ を定義しない.
$ 


$ 
$  標準テンプレートファイルのインクルード
$ 
$INCLUDE "kernel/kernel.tf"$



$ 
$  CFG_INTのターゲット依存のエラーチェック
$ 

$FOREACH intno INT.ORDER_LIST$
$ IRQ割込み番号かどうかをチェック
	$IF ( LENGTH( FIND( INTNO_INT, INT.INTNO[intno] ) ) != 0 )$

$   TA_POSEDGEとTA_NEGEDGEが同時に設定されている場合
		$IF ((INT.INTATR[intno] & ( TA_POSEDGE | TA_NEGEDGE )) == ( TA_POSEDGE | TA_NEGEDGE ))$
			$ERROR$ INT.TEXT_LINE[intno]:$FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "intatr", INT.INTATR[intno], INT.INTNO[intno], "CFG_INT")$$END$
		$END$

$   TA_POSEDGEとTA_BOTHEDGEが同時に設定されている場合
		$IF ((INT.INTATR[intno] & ( TA_POSEDGE | TA_BOTHEDGE )) == ( TA_POSEDGE | TA_BOTHEDGE ))$
			$ERROR$ INT.TEXT_LINE[intno]:$FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "intatr", INT.INTATR[intno], INT.INTNO[intno], "CFG_INT")$$END$
		$END$

$   TA_NEGEDGEとTA_BOTHEDGEが同時に設定されている場合
		$IF ((INT.INTATR[intno] & ( TA_NEGEDGE | TA_BOTHEDGE )) == ( TA_NEGEDGE | TA_BOTHEDGE ))$
			$ERROR$ INT.TEXT_LINE[intno]:$FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "intatr", INT.INTATR[intno], INT.INTNO[intno], "CFG_INT")$$END$
		$END$

$   TA_POSEDGEとTA_NEGEDGEとTA_BOTHEDGEが同時に設定されている場合
		$IF ((INT.INTATR[intno] & ( TA_POSEDGE | TA_NEGEDGE | TA_BOTHEDGE )) == ( TA_POSEDGE | TA_NEGEDGE | TA_BOTHEDGE ))$
			$ERROR$ INT.TEXT_LINE[intno]:$FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "intatr", INT.INTATR[intno], INT.INTNO[intno], "CFG_INT")$$END$
		$END$

	$ELSE$

$   IRQ割込み以外の割込みに対して割込み属性が指定されている場合
		$IF (INT.INTATR[intno] & (~( TA_ENAINT | TA_EDGE ))) != 0$
			$ERROR$ INT.TEXT_LINE[intno]: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "intatr", INT.INTATR[intno], INT.INTNO[intno], "CFG_INT")$$END$
		$END$

	$END$

$END$



$ 
$ 割込み番号から割込み優先度及び属性を取り出すテーブル
$ 

/*$NL$
$SPC$*$SPC$$SPC$Interrupt Level and Attribute Table$NL$
$SPC$*/$NL$
const CFG_INT_INFO _kernel_cfg_int_table[$LENGTH(INTNO_RANGE)$] = {$NL$
$FOREACH intno INTNO_RANGE$
$ 割込み優先度を取得
	$IF LENGTH(INT.INTNO[intno])$
		$intpri = -INT.INTPRI[intno]$
		$intatr = INT.INTATR[intno]$
	$ELSE$
		$intpri = "0"$
		$intatr = "0xFFFFFFFF"$
	$END$

$ テーブルの中身を出力
	$TAB$$FORMAT("{ %2d, %08x }, /* %02u */", intpri, intatr, +intno)$$NL$
$END$
};$NL$$NL$


$ 
$  アセンブラ出力ファイル
$ 

$FILE "kernel_cfg_asm.S"$

;$NL$
;  RX610アーキテクチャ依存出力ファイル$NL$
;$NL$
;  割込みベクタ及び割込みハンドラ定義$NL$
;$NL$
$NL$$NL$


$ 
$  割込み入口処理
$ 

$ 
$  共通関数の宣言
$ 

$TAB$.text$NL$
$TAB$.extern$TAB$_kernel_interrupt$NL$
$TAB$.extern$TAB$__kernel_default_int_handler$NL$
$TAB$.extern$TAB$__kernel_default_exc_handler$NL$$NL$$NL$


$ 
$  割込みハンドラの出力
$ 

$FOREACH inhno INHNO_RANGE$
	$IF LENGTH(INH.INHNO[inhno])$
		$IF ((INH.INHATR[inhno] & TA_NONKERNEL) == 0)$
			$TAB$.extern	_$INH.INTHDR[inhno]$$NL$
			$TAB$.global	__kernel_$INH.INTHDR[inhno]$_$+INH.INHNO[inhno]$_entry$NL$
			__kernel_$INH.INTHDR[inhno]$_$+INH.INHNO[inhno]$_entry:$NL$
			$TAB$pushm	r1-r5						; スクラッチレジスタをタスクスタックへ退避 $NL$
			$TAB$mov.l	#$+INH.INHNO[inhno]$, r1	; 割込みハンドラ番号をr1へ $NL$
			$TAB$mov.l	#_$INH.INTHDR[inhno]$, r2	; ハンドラのアドレスをr2へ $NL$
			$TAB$bra.a	_kernel_interrupt			; 共通ルーチンへ $NL$$NL$$NL$
		$END$
	$END$
$END$


$ 未登録割込みハンドラ入口処理

$FOREACH inhno INHNO_RANGE$
  $TAB$.extern$TAB$__kernel_default_int_handler_entry_$inhno$$NL$
  __kernel_default_int_handler_entry_$inhno$:$NL$
  $TAB$pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 $NL$
  $TAB$mov.l	#$+inhno$, r1						; 割込みハンドラ番号をr1へ $NL$
  $TAB$mov.l	#__kernel_default_int_handler, r2	; ハンドラのアドレスをr2へ $NL$
  $TAB$bra.a	_kernel_interrupt					; 共通ルーチンへ $NL$$NL$$NL$
$END$


$ 
$  CPU例外ハンドラ入口処理
$ 

$TAB$.extern	_kernel_exception$NL$$NL$

$FOREACH excno EXCNO_RANGE$
	$IF LENGTH(EXC.EXCNO[excno])$
		$TAB$.extern	_$EXC.EXCHDR[excno]$$NL$
		$TAB$.global	__kernel_$EXC.EXCHDR[excno]$_$+EXC.EXCNO[excno]$_entry$NL$
		__kernel_$EXC.EXCHDR[excno]$_$+EXC.EXCNO[excno]$_entry:$NL$
		$TAB$pushm	r1-r5						; スクラッチレジスタをタスクスタックへ退避 $NL$
		$TAB$mov.l	#$+EXC.EXCNO[excno]$, r1	; CPU例外ハンドラ番号をr1へ $NL$
		$TAB$mov.l	#_$EXC.EXCHDR[excno]$, r2	; ハンドラのアドレスをr2へ $NL$
		$TAB$bra.a	_kernel_exception			; 共通ルーチンへ $NL$$NL$$NL$
	$END$
$END$


$ 未登録CPU例外ハンドラ入口処理
$TAB$.extern$TAB$__kernel_default_exc_handler_entry$NL$
__kernel_default_exc_handler_entry:$NL$
$TAB$pushm	r1-r5								; スクラッチレジスタをタスクスタックへ退避 $NL$
$TAB$mov.l	#0FFFFFFFFH, r1						; CPU例外ハンドラ番号をr1へ $NL$
$TAB$mov.l	#__kernel_default_exc_handler, r2	; ハンドラのアドレスをr2へ $NL$
$TAB$bra.a	_kernel_exception					; 共通ルーチンへ $NL$$NL$$NL$


$ 
$  可変ベクタテーブル
$ 

;$NL$
;  可変ベクタテーブル$NL$
;$NL$
$NL$

$TAB$.extern $TAB$ _start$NL$$NL$

$FOREACH inhno INH.ORDER_LIST$
	$IF ((INH.INHATR[inhno] & TA_NONKERNEL) != 0)$
		$TAB$.global $TAB$ _$INH.INTHDR[inhno]$ $NL$
	$END$
$END$
$NL$

$TAB$.section C$$VECT$NL$$NL$
$TAB$.glb __vvector_table$NL$$NL$
__vvector_table:$NL$
$FOREACH inhno INHNO_RANGE$
	$IF LENGTH(INH.INHNO[inhno])$
		$IF ((INH.INHATR[inhno] & TA_NONKERNEL) == 0)$
			$inhhdr = CONCAT(CONCAT("_kernel_" , CONCAT(INH.INTHDR[inhno] , "_")) , CONCAT(+INH.INHNO[inhno] , "_entry"))$
		$ELSE$
			$inhhdr = INH.INTHDR[inhno]$
		$END$
	$ELSE$
		$inhhdr = CONCAT("_kernel_default_int_handler_entry_", inhno)$
	$END$

	$TAB$.word$TAB$_$inhhdr$ $TAB$ $TAB$ $FORMAT("; %02d" , inhno)$ $NL$
$END$


$ 
$  固定ベクタテーブル
$ 
$FOREACH excno EXCNO_RANGE$
	$IF LENGTH(EXC.EXCNO[excno])$
		$EXCHDR[excno] = CONCAT(CONCAT("_kernel_" , CONCAT(EXC.EXCHDR[excno] , "_")) , CONCAT(+EXC.EXCNO[excno] , "_entry"))$
	$ELSE$
		$EXCHDR[excno] = "_kernel_default_exc_handler_entry"$
	$END$
$END$

$NL$
;$NL$
;  固定ベクタテーブル$NL$
;$NL$
$NL$

$TAB$ .section .fvect,ROMDATA,align=4 $NL$
$TAB$ .glb fvector_table $NL$
fvector_table:$NL$$NL$
$TAB$ .space$TAB$ 0x1c$NL$
$TAB$ .word$TAB$ 0xFFFFFFFF $TAB$ ; ROMコード(0xFFFFFF9C)$NL$
$TAB$ .word$TAB$ 0xFFFFFFFF $TAB$ ; 制御コード(0xFFFFFFA0), IDコード1 - 3$NL$
$TAB$ .word$TAB$ 0xFFFFFFFF $TAB$ ; IDコード4 - 7$NL$
$TAB$ .word$TAB$ 0xFFFFFFFF $TAB$ ; IDコード8 - 11$NL$
$TAB$ .word$TAB$ 0xFFFFFFFF $TAB$ ; IDコード12 - 15$NL$
$TAB$ .space$TAB$ 0x20$NL$
$TAB$ .word$TAB$ _$EXCHDR[20]$ $TAB$ $TAB$ ;$SPC$ 20:特権命令例外 $SPC$$NL$
$TAB$ .word$TAB$ _$EXCHDR[21]$ $TAB$ $TAB$ ;$SPC$ 20:ACCESS例外 $SPC$$NL$
$TAB$ .space$TAB$ 0x4$NL$
$TAB$ .word$TAB$ _$EXCHDR[23]$ $TAB$ $TAB$ ;$SPC$ 23:未定義命令例外 $SPC$$NL$
$TAB$ .space$TAB$ 0x4$NL$
$TAB$ .word$TAB$ _$EXCHDR[25]$ $TAB$ $TAB$ ;$SPC$ 25:浮動小数点例外 $SPC$$NL$
$TAB$ .space$TAB$ 0x10$NL$
$TAB$ .word$TAB$ _$EXCHDR[30]$ $TAB$ $TAB$ ;$SPC$ 30:ノンマスカブル例外 $SPC$$NL$
$TAB$ .word$TAB$ _start $TAB$ $TAB$ $TAB$ $TAB$ ;$SPC$ 31:リセット $SPC$$NL$

$NL$ $NL$

	$TAB$.end
$NL$
