/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2010 by Witz Corporation, JAPAN
 * 
 *  上記著作権者は，以下の (1)〜(4) の条件か，Free Software Foundation 
 *  によって公表されている GNU General Public License の Version 2 に記
 *  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
 *  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 * 
 */


/*
 *	ターゲットシステム依存モジュール（GR-SAKURA用）
 */


#include "kernel_impl.h"
#include <sil.h>
#include "target_board.h"
#include <target_serial.h>
#include <target_device/target_device.h>


/*
 *  ターゲットシステム依存 初期化ルーチン
 */
void
sakura_clock_waitcount_config(void){
  //unlock lopwermode register access
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY | SYSTEM_PRC1);

  //clock wait count set
  sil_wrb_mem((void *)(SYSTEM_MOSCWTR_ADDR),SYSTEM_CLKWAIT_HE );
 // sil_wrb_mem((void *)(SYSTEM_PLLWTCR_ADDR), SYSTEM_CLKWAIT_HA);
  
  //lock lopwermode register access
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY );
}


void 
sakura_clock_config( void ){
  
  sakura_clock_waitcount_config();

  //unlock access of clock setting register
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY | SYSTEM_PRC0);
  //GR-SAKURA Bord OSC is 12MHz
  //set clock freq(PLL 196MHz, PCKB 48MHz PCKA 98MHz ICK 98MHz)
  //pll set div 1, mul 16
  sil_wrh_mem((void *)(CKG_PLLCR_ADDR), CKG_PLLCR_PLIDIV1 | CKG_PLLCR_STC16);
  sil_wrh_mem((void *)(CKG_PLLCR_ADDR), CKG_PLLCR_PLIDIV1 | ( 0x1FUL << 8U ));

  //( 0x0FUL << 8U )
  //set bus clock rate
  sil_wrw_mem((void *)(CKG_SCKCR_ADDR),   CKG_SCKCR_PB_DIV04 
                                        | CKG_SCKCR_PA_DIV02   
                                        | CKG_SCKCR_BCK_DIV04
                                        | CKG_SCKCR_PSTOP0
                                        | CKG_SCKCR_PSTOP1
                                        | CKG_SCKCR_FCK_DIV04
                                        | CKG_SCKCR_ICK_DIV02
                                        | CKG_SCKCR_RESERVE);

  sil_wrh_mem((void *)(CKG_SCKCR2_ADDR), CKG_SCKCR2_IEBCK_DIV4 | CKG_SCKCR2_UCK_NOT_USE);

  //Main clock enable
   sil_wrb_mem((void *)(CKG_MOSCCR_ADDR), CKG_CLOCK_ENABLE);
   //Wait Main clock lock
   while(sil_reb_mem((void *)(CKG_MOSCCR_ADDR)) != CKG_CLOCK_ENABLE);
   
  //pll enable
   sil_wrb_mem((void *)(CKG_PLLCR2_ADDR), CKG_CLOCK_ENABLE);
   while(sil_reb_mem((void *)(CKG_PLLCR2_ADDR)) != CKG_CLOCK_ENABLE);
   //PLL lock wait
   //wait over 10ms, LOCO freq 125Khz, wait count is 125*10 = 1250;                               
   //switch clock(PLL select)
   sil_wrh_mem((void *)(CKG_SCKCR3_ADDR),   CKG_SCKCR3_PLL);                        
  //lock access of clock setting register
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY );


}

void
target_initialize( void )
{

	/*
	 *  プロセッサ依存の初期化
	 */

  prc_initialize();
 // sakura_clock_config();
  target_device_init();
  std_uart_init(TARGET_PUTC_PORTID, UART_BAUDRATE, UART_CLKSRC); //9600 baudrate

}

/*
 *  ターゲットシステムの終了ルーチン
 */
void
target_exit( void )
{
	/*
	 *	プロセッサ依存の終了処理
	 */
	prc_terminate();

	while ( 1 );
}

/*
 *  システムログの低レベル出力のための文字出力
 */
void
target_fput_log( char c )
{
	if( c == '\n' ){
	   sci_uart_pol_putc( '\r' , TARGET_PUTC_PORTID );
	}

    sci_uart_pol_putc( c , TARGET_PUTC_PORTID );
}

