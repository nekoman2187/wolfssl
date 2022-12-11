## Renesas RX72N EnvisionKit with TOPPERS OS 

本デモはルネサス「RX72N EnvisionKit 」に「Toopers OS」を適用し「WolfSSL」の動作を確認します

# 本デモについては以下が必要です 

1.Renesas e² studio Version: 2022-07 (22.7.0)以降   
2.Toppers OS 1.91.1 Renesas RX72N適用バージョン(gitレポジトリーより入手)    
3.WolfSSL Release 5.X.0 以降 (gitレポジトリーより入手)  

# 以下に環境構築手順を示します
 # 1.ライブラリー作成
  本デモに必要なToppersライブラリー、wolfSSLライブラリーを作成します  
 1-1.[プロジェクトをインポート]ダイアログの[ルートディレクトリーの選択(T)]の[参照(R)]を押下  
 1-2.git レポジトリwolfssl/IDE/Renesas/e2studio/RX72N/EnvisionKit_Toppersの[wolflib]を選択[フォルダーの選択]を押下      
 1-3.プロジェクト・エクスプローラーの作成したプロジェクトをクリック後プルダウンメニューから[プロジェクトのビルド(B)]キーを選択しビルドを行う  
 1-4. [wolflib/Debug]に[libwolflib.a]が生成されます  
 1-5.Toppersライブラリーのビルドの為、[https://github.com/nekoman2187/RenesasRX72NwithToppers]　よりgit clone又はダウンロードし解凍します(フォルダー名は[RenesasRX72NwithToppers]として下さい)  
 1-6.事前準備確認  
   コマンド実行ではMsys2等の環境を事前にご用意ください  
   Msys2でgccのツールチェーンのインストールを行ってください  
   Msys2環境では事前にRenesas環境のパス設定を行う必要があります.bashrc等      
---設定例を示します：ルネサスツールチェーンパスを指定---      
 ```  
export PATH=PATH=$PATH:\/C/ProgramData\/GCC\ for\ Renesas\ RX\ 8.3.0.202202-GNURX-ELF/rx-elf/rx-elf/bin
 ``` 
　1-7.設定を確認後、以下を行います

  ```  
$ pwd
[個別インストール環境]/wolfssl/IDE/Renesas/e2studio/RX72N/EnvisionKit_Toppers/RenesasRX72NwithToppers
$ perl ./asp/configure -T rx72n_gcc
$ make depend
```  
 1-9.[1-7.]終了後、前述[1-1./1-2.]同様、[Toppers_app]を選択[フォルダーの選択]を押下  
 1-10.[1-3.]同様ビルドを行うと「toppers_rx]に[libasp.a]が生成されます    
 
# 2.wolfSSLDemoプロジェクトの修正 
 2-1.メニューの[ファイル・システムからプロジェクトを開く...]を選択  
 2-2.git レポジトリwolfssl/IDE/Renesas/e2studio/RX72N/EnvisionKit_Toppersの[wolfSSLDemo]を選択[フォルダーの選択]を押下  
 2-3.[WolfSSLDemo.scfg]をダブルクリックで設定ダイアログが表示→[コンポーネントタブ] を選択  
 2-4.[ソフトウェアコンポーネントダイアログ]ダイアログ右上の[コードの生成]を押下      
 
 # 3.e² studio BSP修正
 3-1.生成されたBSPをToppersに適用する為、以下の変更及び修正を加えます  
 ```  
smc_gen/r_t4_driver_rx/src/t4_driver.c  
#elif (defined BSP_MCU_RX72M || defined BSP_MCU_RX72N || defined BSP_MCU_RX66N) && \
    (BSP_CFG_MCU_PART_FUNCTION == 0x11 /* H */)
#include "r_tsip_rx_if.h"  
  ↓  修正  
#elif (defined BSP_MCU_RX72M || defined BSP_MCU_RX72N || defined BSP_MCU_RX66N) && \
    (BSP_CFG_MCU_PART_FUNCTION == 0x11 /* H */)
//#include "r_tsip_rx_if.h"

smc_gen\general\r_cg_hardware_setup.c  
void R_Systeminit(void)  
    R_Interrupt_Create();  が存在した場合
	↓  修正  
   // R_Interrupt_Create();  
smc_gen/r_config/r_bsp_config.h
#define BSP_CFG_RTOS_USED               (0)
	↓  修正  
#define BSP_CFG_RTOS_USED               (4)

smc_gen/r_bsp/mcu/all/resetprg.c   
#if (BSP_CFG_RTOS_USED == 0) || (BSP_CFG_RTOS_USED == 5)     /* Non-OS or Azure RTOS */
extern void R_BSP_MAIN_FUNCTION(void);
#endif
↓  修正  
#if (BSP_CFG_RTOS_USED == 0) || (BSP_CFG_RTOS_USED == 5) || (BSP_CFG_RTOS_USED == 4)    /* Non-OS or Azure RTOS */
extern void R_BSP_MAIN_FUNCTION(void);
#endif

#if (BSP_CFG_RTOS_USED == 0) || (BSP_CFG_RTOS_USED == 5)  /* Non-OS or Azure RTOS */
    /* Call the main program function (should not return) */
    R_BSP_MAIN_FUNCTION();
#elif BSP_CFG_RTOS_USED == 1    /* FreeRTOS */
    /* Lock the channel that system timer of RTOS is using. */
↓  修正  
#if (BSP_CFG_RTOS_USED == 0) || (BSP_CFG_RTOS_USED == 5)  || (BSP_CFG_RTOS_USED == 4)  /* Non-OS or Azure RTOS */
    /* Call the main program function (should not return) */
    R_BSP_MAIN_FUNCTION();
#elif BSP_CFG_RTOS_USED == 1    /* FreeRTOS */
    /* Lock the channel that system timer of RTOS is using. */


R_BSP_POR_FUNCTION(R_BSP_STARTUP_FUNCTION)  
#if BSP_CFG_USER_STACK_ENABLE == 1
    INTERNAL_NOT_USED(ustack_area);
#endif
    INTERNAL_NOT_USED(istack_area);
#endif
	↓  修正  
#if BSP_CFG_USER_STACK_ENABLE == 1
   // INTERNAL_NOT_USED(ustack_area);
#endif
  //  INTERNAL_NOT_USED(istack_area);
#endif    
R_BSP_SET_INTB(R_BSP_SECTOP_INTVECTTBL);  
	↓  修正  
// R_BSP_SET_INTB(R_BSP_SECTOP_INTVECTTBL);  

#if (BSP_CFG_RTOS_USED == 0) || (BSP_CFG_RTOS_USED == 5)  /* Non-OS or Azure RTOS or Toppers*/
    /* Call the main program function (should not return) */
    R_BSP_MAIN_FUNCTION();

#if (BSP_CFG_RTOS_USED == 0) || (BSP_CFG_RTOS_USED == 5) || (BSP_CFG_RTOS_USED == 4)   /* Non-OS or Azure RTOS or Toppers*/
    /* Call the main program function (should not return) */
    R_BSP_MAIN_FUNCTION();    

   bsp_interrupt_open();  
 	↓  修正  
   //bsp_interrupt_open();  

smc_gen\r_config\r_cmt_rx_config.h  (初回ビルド後に生成)
#if (BSP_CFG_RTOS_USED == 4) && (BSP_CFG_RENESAS_RTOS_USED == 0) /* RI600V4 */
#define _RI_TRACE_TIMER 1 /* RI600V4 uses CMT1 channel for the trace feature.*/
  ↓  修正  
#if (BSP_CFG_RTOS_USED == 4) && (BSP_CFG_RENESAS_RTOS_USED == 0) /* RI600V4 */
#define _RI_TRACE_TIMER 0 /* RI600V4 uses CMT1 channel for the trace feature.*/

```

# 4.wolfSSLDemoプロジェクトのビルド  
 4-1.[3-1.]終了後プルダウンメニューから[プロジェクトのビルド(B)]キーを選択しビルド   
 4-2.ビルドで生成されたELFファイルを[メニュー]→[実行(R)]→[実行(R)]又は[デバッグ(D)]でボードへ転送を行い、実行します  
 ※コンフィグレーション直後/ビルドクリーン後に[T4_Library_ether_ccrx_rxv1_little]がリンカーでエラーになる場合が
 あります　プロジェクトの[プロパティ]ダイアログ[C/C++ビルド]の[設定]で[Linker]/[Archives]  
 [User defined archive (library) files (-I)]から[×]押下から[T4_Library_ether_ccrx_rxv1_little]を削除してください  
 4-3.[WolfSSLDemo.c]のdefine値[#define SSL_SERVER]を定義を行うとサーバとしての動作になり、削除でクライアントとしての動作となります(通信相手はwolfsslサンプルにてlinux,windows,macにて作成の事)    
 ※クライアントとしての動作の場合[src/wolfDemo/wolf_demo.h]の  
 サーバIPアドレスのdefine値 [SERVER_IP]を"xxx.xx.xx.xx"       
 ポート番号のdefine値 [SERVER_PortNo]をポート番号として設定して下さい    
 4-4.[Renesas Debug Virtual Console]にて実行を確認します   