#!/bin/bash  
#use:testpack versionCode versionName

#get current path
direc=$(pwd) 
projName=balloon
#echo $direc  

#拷贝xml文件
cp AndroidManifest.xml AndroidManifest.xm_
cp AndroidManifest.xml.pack AndroidManifest.xml
#set new versionCode 
versionCode=$(printf "android:versionCode=%s%s%s" '"' "$1" '"')
#set new versionName
versionName=$(printf "android:versionName=%s%s%s" '"' "$2" '">')
#replace new versionCode
sed -e 's/android:versionCode.*/'"$versionCode"'/g' -i "" AndroidManifest.xml 
#replace new versionName
sed -e 's/android:versionName.*/'"$versionName"'/g' -i "" AndroidManifest.xml

#遍历当前路径下pack文件夹内的所有文件
for dir2del in $direc/pack/* ; do
    #file is a directory
    if [ -d $dir2del ]; then
		#获取文件夹的名称
	    direcName=`basename $dir2del`
		#获取该文件夹内的apk的名称（包含路径）
		apkName=$(printf "%s/%s_%s_%s.apk" $dir2del $projName $direcName "$2" )		
		echo $apkName
	    
		if [ -a $apkName ]; then
			#该文件夹内含有apk则不打包，输入该apk的路径加名称
			echo $apkName
		else
			#replace umeng channel
			sed -e "s/__UC__/"$direcName"/g" -i "" AndroidManifest.xml
			#start packing
			ant release 
			#将打包好的apk拷到该文件夹内
			cp bin/balloon-release.apk $apkName
		fi
    fi  
done 

#拷贝xml文件
#cp AndroidManifest.xm_ AndroidManifest.xml