#!/bin/sh
# param  path

pathlist[0]="./asp/arch/rx_gcc/rx_common"
pathlist[1]="./asp/arch/rx_gcc/rx72n"
pathlist[2]="./asp/target/rx72n_gcc"
pathlist[3]="./asp/sample"

# CR + LF -> LF
# ファイル名をrx63nxx rx72nxxに変更
function convert () {
echo $1
sed -i -z 's/\r\n/\n/g' $1/*

for file in `find $1 -type f`;
do
    echo $file 
    if [[ "$file" =~ rx63* ]] ; then
      nm=`echo  $file | sed -e "s/rx63*/rx72/g"` 
      mv $file $nm 
    fi

done
}

#1.9.1/aspに存在した場合、rx_gcc削除（通常は存在しない）
rm -rf asp/arch/rx_gcc
#まずはbismath_evalkit_targetのrx_gccを1.9.1/aspにコピー
cp -fr ${1}/asp/arch/rx_gcc ./asp/arch/
#コピーしたディレクトリrx63nをrx72nにrename
mv  ./asp/arch/rx_gcc/rx63n ./asp/arch/rx_gcc/rx72n
#コピーした不要なディレクトリrx63mを削除
rm -rf ./asp/arch/rx_gcc/rx64m
#bismath_evalkit_targetのターゲットディレクトリsakura_gccを1.9.1/aspにコピー
cp -r ${1}/asp/target/sakura_gcc ./asp/arch/ 
#1.9.1/asp/targetにrx72n_gccが存在した場合削除（通常は存在しない）
rm -rf ${pathlist[2]}
#コピーしたディレクトリsakura_gccをrx72n_gccにrename
mv ./asp/arch/sakura_gcc  ${pathlist[2]}
#renameしたrx72n_gccディレクトリの使用しないファイルを削除
rm ${pathlist[2]}/DTCa_vecter.S 
rm ${pathlist[2]}/target_serial.c
rm ${pathlist[2]}/target_serial.cfg
rm ${pathlist[2]}/target_serial.h
rm ${pathlist[2]}/target_user.txt
rm ${pathlist[2]}/tinet_target_config.h
rm ${pathlist[2]}/tinet_target_defs.h
rm ${pathlist[2]}/tinet_target_config.c
#リンカースクリプトファイル名変更
mv ${pathlist[2]}/sakura_gcc.ld  ${pathlist[2]}/rx72n_gcc.ld
#使用しないディレクトリtarget_deviceを削除
rm -rf ${pathlist[2]}/target_device
#sample ディレクトリをbismath_evalkit_targetより1.9.1/aspへコピー
cp  -r ${1}/asp/sample ./asp
#kernel/interrupt.cをbismath_evalkit_targetより1.9.1/asp/kernelへコピー
cp   ${1}/asp/kernel/interrupt.c ./asp/kernel/
#kernel/kernel_implをbismath_evalkit_targetより1.9.1/asp/kernelへコピー
cp   ${1}/asp/kernel/kernel_impl.h ./asp/kernel/
# コピーしたファイルを変換CR + LF -> LF
sed -i -z 's/\r\n/\n/g' ./asp/kernel/interrupt.c
sed -i -z 's/\r\n/\n/g' ./asp/kernel/kernel_impl.h

{
 for ((i=0; i<4; i++))
  do
	 convert  ${pathlist[i]}
  done
}

#patch 処理
cd ./asp
patch  --binary -t -p1 < ../toppers.patch

