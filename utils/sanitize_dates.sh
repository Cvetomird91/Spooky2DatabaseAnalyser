#!/usr/bin/env bash

DB_PATH=$1
# declare -p $PATH
TXT_FILES="${DB_PATH}/*.txt"

for file in ${TXT_FILES}; do
	 #echo ${file};
	 new_file_name=$( echo ${file} | sed "s/\.17/\.2017/" );
	 echo ${new_file_name};
	# echo ${file} | sed "s/\.17/\.2017/";
done
