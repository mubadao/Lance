#!/bin/bash  
#use:testpack versionCode versionName

#get current path
direc=$(pwd) 
projName=galaxyinvader
#echo $direc  

#拷贝xml文件
cp AndroidManifest.xml AndroidManifest.xm_
#set new versionCode 
versionCode=$(printf "android:versionCode=%s%s%s" '"' "$1" '"')
#set new versionName
versionName=$(printf "android:versionName=%s%s%s" '"' "$2" '">')

#遍历当前路径下pack文件夹内的所有文件
for dir2del in $direc/pack/* ; do
	cp AndroidManifest.xml.pack AndroidManifest.xml
	#replace new versionCode
	sed -e 's/android:versionCode.*/'"$versionCode"'/g' -i "" AndroidManifest.xml 
	#replace new versionName
	sed -e 's/android:versionName.*/'"$versionName"'/g' -i "" AndroidManifest.xml
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
			destName=$(printf "%s/package/%s_%s_%s.apk" $direc $projName $direcName "$2" )
			echo $destName
			cp bin/balloon-release.apk $destName
#			cp AndroidManifest.xml AndroidManifest.$direcName
		fi
    fi  
done 

cp AndroidManifest.xm_ AndroidManifest.xml
rm AndroidManifest.xm_

#拷贝xml文件
#cp AndroidManifest.xm_ AndroidManifest.xml
