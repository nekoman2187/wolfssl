/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2010 by Witz Corporation, JAPAN
 *  Copyright (C) 2016- by Hisashi Hata, JAPAN
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
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
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 */

#include <kernel_impl.h>

/*
 *        プロセッサ依存モジュール（RX63n用）
 */

#define NULL_OFF 0 //reserved IPR


#define ICU_IPR_BASE 0x00087300
#define ICU_IPR000_OFFSET 0x00U
#define ICU_IPR001_OFFSET 0x01U
#define ICU_IPR002_OFFSET 0x02U
#define ICU_IPR003_OFFSET 0x03U
#define ICU_IPR004_OFFSET 0x04U
#define ICU_IPR005_OFFSET 0x05U
#define ICU_IPR006_OFFSET 0x06U
#define ICU_IPR007_OFFSET 0x07U

#define IRREGURLAR_IPR_NUM 32

const uint8_t ipr_reg_offset[IRREGURLAR_IPR_NUM] = {
    NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF,    /* No.0 - 4   予約 */
    NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF,    /* No.5 - 9   予約 */
    NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF,    /* No.10 - 14 予約 */
    NULL_OFF,                            /* No.15  予約 */
    ICU_IPR000_OFFSET,                   /* No.16   バスエラー BUSERR  */
    NULL_OFF,                            /* No.17 予約 */
    ICU_IPR000_OFFSET,                   /* No.18 RAM Error */
    NULL_OFF, NULL_OFF,                  /* No.19 - 20 予約 */
    ICU_IPR001_OFFSET,                   /* No.21   FCU FIFERR  */
    NULL_OFF,                            /* No.22  予約 */
    ICU_IPR002_OFFSET,                   /* No.23   FCU FRDYI  */
    NULL_OFF, NULL_OFF,                  /* No.24 - 25  予約 */
    ICU_IPR003_OFFSET,                   /* No.26  ICU SWINT2 */
    ICU_IPR003_OFFSET,                   /* No.27  ICU SWINT  */
    ICU_IPR004_OFFSET,                   /* No.28   CMTユニット0 CMT0  */
    ICU_IPR005_OFFSET,                   /* No.29   CMTユニット0 CMT1  */
    ICU_IPR006_OFFSET,                   /* No.30   CMTW0 CMWI0  */
    ICU_IPR007_OFFSET,                   /* No.31   CMTユニット1 CMT3  */
};

/*
 * set interrupt priority register
 */

void set_icu_ipr(INTNO intno, uint8_t pri_num){
  if(intno <= IRREGURLAR_IPR_NUM)
    *((volatile uint8_t *)(ICU_IPR_BASE + ipr_reg_offset[intno])) = pri_num;
  else
    *((volatile uint8_t *)(ICU_IPR_BASE + intno)) = pri_num;
}
