#!/bin/sh
# param  path

pathlist[0]="./asp/arch/rx_gcc/rx_common"
pathlist[1]="./asp/arch/rx_gcc/rx72n"
pathlist[2]="./asp/target/rx72n_gcc"
pathlist[3]="./asp/sample"

# convert utf-8 to euc-j dir
function convert () {
echo hello_world
echo $1
sed -i -z 's/\r\n/\n/g' $1/*

for file in `find $1 -type f`;
do
    echo $file 
#    iconv -f utf-8  -t euc-jp $file  > tmpfile
    if [[ "$file" =~ rx63* ]] ; then
      nm=`echo  $file | sed -e "s/rx63*/rx72/g"` 
      mv $file $nm
     # rm $file
 
    fi

done
}
rm -rf asp/arch/rx_gcc
#copy target
cp -fr ${1}/asp/arch/rx_gcc ./asp/arch/
cp -fr ${1}/asp/arch/rx_gcc ./

mv  ./asp/arch/rx_gcc/rx63n ./asp/arch/rx_gcc/rx72n
rm -rf ./asp/arch/rx_gcc/rx64m
cp -r ${1}/asp/target/sakura_gcc ./asp/arch/ 
rm -rf ${pathlist[2]}
mv ./asp/arch/sakura_gcc  ${pathlist[2]}
rm ${pathlist[2]}/DTCa_vecter.S 
rm ${pathlist[2]}/target_serial.c
rm ${pathlist[2]}/target_serial.cfg
rm ${pathlist[2]}/target_serial.h
rm ${pathlist[2]}/target_user.txt
rm ${pathlist[2]}/tinet_target_config.h
rm ${pathlist[2]}/tinet_target_defs.h
rm ${pathlist[2]}/tinet_target_config.c
mv ${pathlist[2]}/sakura_gcc.ld  ${pathlist[2]}/rx72n_gcc.ld
rm -rf ${pathlist[2]}/target_device
cp  -r ${1}/asp/sample ./asp
cp  -f ${1}/asp/kernel/interrupt.c ./asp/kernel/
cp  -f ${1}/asp/kernel/kernel_impl.h ./asp/kernel/
sed -i -z 's/\r\n/\n/g' ./asp/kernel/interrupt.c
sed -i -z 's/\r\n/\n/g' ./asp/kernel/kernel_impl.h

#convert target
{
 for ((i=0; i<3; i++))
  do
	 convert  ${pathlist[i]}
  done
}

#patch 
cd ./asp
patch  --binary -t -p1 < ../toppers.patch

