;*
;*  TOPPERS/ASP Kernel
;*      Toyohashi Open Platform for Embedded Real-Time Systems/
;*      Advanced Standard Profile Kernel
;* 
;*  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
;*                              Toyohashi Univ. of Technology, JAPAN
;*  Copyright (C) 2001 by OAKS16KIT support
;*  Copyright (C) 2003-2004 by Naoki Saito
;*             Nagoya Municipal Industrial Research Institute, JAPAN
;*  Copyright (C) 2003-2004 by Ryosuke Takeuchi
;*               Platform Development Center RICOH COMPANY,LTD. JAPAN
;*  Copyright (C) 2008-2010 by Witz Corporation, JAPAN
;* 
;*  上記著作権者は，Free Software Foundation によって公表されている 
;*  GNU General Public License の Version 2 に記述されている条件か，以
;*  下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェア（本ソフトウェ
;*  アを改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
;*  利用と呼ぶ）することを無償で許諾する．
;*  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
;*      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
;*      スコード中に含まれていること．
;*  (2) 本ソフトウェアを再利用可能なバイナリコード（リロケータブルオブ
;*      ジェクトファイルやライブラリなど）の形で利用する場合には，利用
;*      に伴うドキュメント（利用者マニュアルなど）に，上記の著作権表示，
;*      この利用条件および下記の無保証規定を掲載すること．
;*  (3) 本ソフトウェアを再利用不可能なバイナリコードの形または機器に組
;*      み込んだ形で利用する場合には，次のいずれかの条件を満たすこと．
;*    (a) 利用に伴うドキュメント（利用者マニュアルなど）に，上記の著作
;*        権表示，この利用条件および下記の無保証規定を掲載すること．
;*    (b) 利用の形態を，別に定める方法によって，上記著作権者に報告する
;*        こと．
;*  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
;*      害からも，上記著作権者を免責すること．
;* 
;*  本ソフトウェアは，無保証で提供されているものである．上記著作権者は，
;*  本ソフトウェアに関して，その適用可能性も含めて，いかなる保証も行わ
;*  ない．また，本ソフトウェアの利用により直接的または間接的に生じたい
;*  かなる損害に関しても，その責任を負わない．

.text
.balign 4
	

;
;  レジスタ定義
;
.equ SCKCR,	0x080020

;
;  定義値
;
.equ CLOCK_VAL,	0x00020100


.global	_hardware_init_hook
.global	_software_init_hook


_hardware_init_hook:
	;
	;  動作モード設定
	;
	;  動作モードはボード上の端子によって決定されるため,
	;  ここでは特別設定しない.
	;  ただし, リトルエンディアン/シングルチップモード
	;  であることを前提とする.
	;
	;  またリセット後, 内蔵ROM：有効, 内蔵RAM：有効, 外部バス：無効
	;  である.
	;

	;
	;  モジュールストップ
	;
	;  リセット後, 動作している内蔵周辺モジュールはDMAC, DTC,
	;  内蔵RAMのみである.
	;  それ以外の内蔵周辺モジュールに関しては使用する側で
	;  設定すること.
	;

	rts


_software_init_hook:
	;
	;  本コンパイラではweak definitionの機能が無いため,
	;  特に必要な処理はないが, 必ず呼び出すこととする.
	;
	rts


.end

