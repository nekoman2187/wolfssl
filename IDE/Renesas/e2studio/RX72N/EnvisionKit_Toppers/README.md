## Renesas RX72N EnvisionKit with TOPPERS OS 

本デモはルネサス「RX72N EnvisionKit 」に「Toopers OS」を適用し「WolfSSL」の動作を確認します

# 本デモについては以下が必要です 

1.Renesas e² studio Version: 2022-07 (22.7.0)以降   
2.Toppers OS 1.91.1 Renesas RX72N適用バージョン(gitレポジトリーより入手)    
3.WolfSSL Release 5.X.0 以降 (gitレポジトリーより入手)  
<br>
|要素|名称/バージョン|
|:--|:--|
|Renesas e² studio Version|GR-2022-07 (22.7.0)以降|
|Toppers OS|1.9.1|
|Toppers コンフィギュレータ|1.9.6|
|Renesas r_bsp|7.10|
|Renesas r_cmt_rx|5.10|
<br>

# 以下に環境構築手順を示します
 # 1.ライブラリー作成
  本デモに必要なToppersライブラリー、wolfSSLライブラリーを作成します  
 1-1.[プロジェクトをインポート]ダイアログの[ルートディレクトリーの選択(T)]の[参照(R)]を押下  
 1-2.git レポジトリwolfssl/IDE/Renesas/e2studio/RX72N/EnvisionKit_Toppersの[wolflib]を選択[フォルダーの選択]を押下      
 1-3.プロジェクト・エクスプローラーの作成したプロジェクトをクリック後プルダウンメニューから[プロジェクトのビルド(B)]キーを選択しビルド
 (上記操作操作を行う場合[プロジェクト][プロパティ]の[設定][toolchain]タブで[ツールチェーン:]が選択されている事を確認ください)  
 1-4. [wolflib/Debug]に[libwolflib.a]が生成されます  
 1-5.Toppersライブラリーのビルドの為、[https://www.toppers.jp/asp-d-download.html]より[asp-1.9.1.tar.gz]をダウンロードし[/wolfssl/IDE/Renesas/e2studio/RX72N/EnvisionKit_Toppers/]に解凍します   
 1-6.Toppersライブラリーのビルドの為、[https://www.toppers.jp/cfg-download.html]　より[コンフィギュレータ Release 1.9.6（Windows用バイナリ）]をダウンロードし[1.5]で解凍した[1.9.1/asp]ディレクトリに[cfg/cdg]ディレクトリを作成し中に[cfg.exe]として解凍します  
 1-7.Toppers ASPに以下に示すPtachを適用します         　 
 (Msys2でpatchコマンドが使えない場合は[pacman -S patch] でインストールが必要となります)     
 ``` 
 $ pwd
[個別インストール環境]/wolfssl/IDE/Renesas/e2studio/RX72N/EnvisionKit_Toppers/1.9.1
 patch --binary -p1 < ../toppers.patch
```  
 1-8.事前準備確認  
   コマンド実行ではMsys2等の環境を事前にご用意ください  
   Msys2でgccのツールチェーンのインストールを行ってください  
   Msys2環境では事前にRenesas環境のパス設定を行う必要があります.bashrc等      
---設定例を示します：ルネサスツールチェーンパスを指定---      
 ```  
export PATH=PATH=$PATH:\/C/ProgramData\/GCC\ for\ Renesas\ RX\ 8.3.0.202202-GNURX-ELF/rx-elf/rx-elf/bin
 ``` 
　1-9.設定を確認後、以下を行います
  ```  
$ pwd
[個別インストール環境]/wolfssl/IDE/Renesas/e2studio/RX72N/EnvisionKit_Toppers/1.9.1
$ perl ./asp/configure -T rx72n_gcc
$ make depend
```  
 1-10.プロジェクト・エクスプローラーの作成したプロジェクトをクリック後プルダウンメニューから[プロジェクトのビルド(B)]キーを選択しビルド    
 1-11.toppers_rx]に[libasp.a]が生成されます    
 
# 2.wolfSSLDemoプロジェクトの修正 
 2-1.メニューの[ファイル・システムからプロジェクトを開く...]を選択  
 2-2.git レポジトリwolfssl/IDE/Renesas/e2studio/RX72N/EnvisionKit_Toppersの[wolfSSLDemo]を選択[フォルダーの選択]を押下  
 2-3.[WolfSSLDemo.scfg]をダブルクリックで設定ダイアログが表示→[コンポーネントタブ] を選択  
 2-4.[ソフトウェアコンポーネントダイアログ]ダイアログ右上の[コードの生成]を押下      
 2-5.ダイアログ左のコンポーネント選択で[Startup] [r_bsp]を選択右クリックしコンテキストメニュー[バージョン変更]を選択し[現在のバージョン]  
     が[7.10]である事を確認してください([7.10]でない場合[変更後のバージョン:]で[7.10]を選択し[次へ(N)>]を押下しコードを生成して下さい)   
 2-6.ダイアログ左のコンポーネント選択で[Drivers] [r_cmt_rx]を選択右クリックしコンテキストメニュー[バージョン変更]を選択し[現在のバージョン]     
     が[5.10]である事を確認してください([5.10]でない場合[変更後のバージョン:]で[5.10]を選択し[次へ(N)>]を押下しコードを生成して下さい)     

 # 3.e² studio BSPにPtachを適用する  
 3-1.生成されたBSPをToppersに適用する為、Patch コマンドにて修正をします  
 以下を行います
 ```  
$ pwd
[個別インストール環境]/wolfssl/IDE/Renesas/e2studio/RX72N/EnvisionKit_Toppers/WolfSSLDemo
 patch --binary -p0 < ./bsp.patch
```

# 4.wolfSSLDemoプロジェクトのビルド  
 4-1.[3-1.]終了後プルダウンメニューから[プロジェクトのビルド(B)]キーを選択しビルド   
 4-2.ビルドで生成されたELFファイルを[メニュー]→[実行(R)]→[実行(R)]又は[デバッグ(D)]でボードへ転送を行い、実行します  
 ※コンフィグレーション直後/ビルドクリーン後に[T4_Library_ether_ccrx_rxv1_little]がリンカーでエラーになる場合が
 ありますがプロジェクトの[プロパティ]ダイアログ[C/C++ビルド]の[設定]で[Linker]/[Archives]/[User defined archive (library) files (-I)]/[×]押下から[T4_Library_ether_ccrx_rxv1_little]を削除してください  
 4-3.[WolfSSLDemo.c]のdefine値[#define SSL_SERVER]を定義を行うとサーバとしての動作になり、削除でクライアントとしての動作となります(通信相手はwolfsslサンプルにてlinux,windows,macにて作成の事)    
 ※クライアントとしての動作の場合[src/wolfDemo/wolf_demo.h]の  
 サーバIPアドレスのdefine値 [SERVER_IP]を"xxx.xx.xx.xx"       
 ポート番号のdefine値 [SERVER_PortNo]をポート番号として設定して下さい    
 4-4.[Renesas Debug Virtual Console]にて実行を確認します   