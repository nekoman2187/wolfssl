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

#ifndef	TOPPERS_STARTER_KIT_H
#define	TOPPERS_STARTER_KIT_H


/*
 *  MCU依存情報の読み込み
 */
#include <rx63n.h>

#ifndef TOPPERS_MACRO_ONLY
#include "target_device/target_device.h"
#endif

#define F_PCLKA		96000000UL	/* PCLKA frequency (configured by SCKCR.PCK) */
#define F_PCLKB		48000000UL	/* PCLKB frequency (configured by SCKCR.PCK) */

/*
 *  ボーレート設定
 */
// 9600 bps
#define BAUD_9600BPS_F4		UINT_C( 38 )
#define UART_BAUDRATE		BAUD_9600BPS_F4
#define UART_CLKSRC			CLK_F4
//38400 bps
//#define BAUD_38400BPS_F1		UINT_C( 38 )
//#define UART_BAUDRATE		BAUD_38400BPS_F1
//#define UART_CLKSRC			CLK_F1
//57600 bps
//#define BAUD_57600BPS_F1		UINT_C( 26 )
//#define UART_BAUDRATE		BAUD_57600BPS_F1
//#define UART_CLKSRC			CLK_F1
//115200
//#define BAUD_115200BPS_F1		UINT_C( 13 )
//#define UART_BAUDRATE		BAUD_115200BPS_F1
//#define UART_CLKSRC			CLK_F1

#endif	/* TOPPERS_STARTER_KIT_H */

 
