/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2010 by Witz Corporation, JAPAN
 *  Copyright (C) 2016- by Hisashi Hata, JAPAN
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

#ifndef	TOPPERS_STARTER_KIT_H
#define	TOPPERS_STARTER_KIT_H


/*
 *  MCU依存情報の読み込み
 */
#include <rx64m.h>

#ifndef TOPPERS_MACRO_ONLY
#include "target_device/target_device.h"
#endif

#define F_PCLKA		120000000UL	/* PCLKA frequency (configured by SCKCR.PCK) usec*/
#define F_PCLKB		60000000UL	/* PCLKB frequency (configured by SCKCR.PCK) usec*/
#define F_SDCLK

#define F_USEC_UNIT 1000000
#define F_MSEC_UNIT 1000

#define USEC_TO_COUNT(BUS_CLK, U_TIME) (BUS_CLK/F_USEC_UNIT*U_TIME)
#define MSEC_TO_COUNT(BUS_CLK, U_TIME) (BUS_CLK/F_MSEC_UNIT*U_TIME)

// stdio config(UART)

/*
 *  UART クロックソース
 */
#define UART_CLKSRC			CLK_F4 // set PCLK/4

/*
 *  UART ボーレート設定
 */
#define BAUD_9600BPS		UINT_C( 48 ) //PCLKB = 60MHz,  n = 1

#define UART_BAUDRATE		BAUD_9600BPS

#endif	/* TOPPERS_STARTER_KIT_H */



/*
 * SD Ram setting
 */

//#define USE_SYSTEM_SDRAM
//#define USE_DATA_SDRAM

#ifndef TOPPERS_MACRO_ONLY
void target_sdram_config();
#endif
