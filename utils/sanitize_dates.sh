#!/usr/bin/env bash

DB_PATH=$1
TXT_FILES="${DB_PATH}/*.txt"

# :"
#     0505
#     02.05.2017
#     14.05.17
#     02052017
# "

for file in ${TXT_FILES}; do
	new_file_name=$( echo ${file} | sed "s/\.17/\.2017/" );
 	echo ${new_file_name};
	mv -v "${file}" "${new_file_name}";
done

for file in ${TXT_FILES}; do
	#occurence=$(ack -ic "(\d{4})(?=[a-z])" "${file}");
	#echo "${file}" | perl -pe 's/(?<=[A-Za-z])(\d{2})(\d{2})(?=[A-Za-z])/$2.$3.2017/';
	#echo "${file}:";
	new_file_name=$( echo "${file}" | perl -pe 's/(?<=[A-Za-z])(\d{2})(\d{2})(?=[\.A-Za-z])/$1.$2.2017/');
	echo "${file}" | perl -pe 's/(?<=[A-Za-z])(\d{2})(\d{2})(?=[\.A-Za-z])/$1.$2.2017/'
	mv -v "${file}" "${new_file_name}";
	#echo "${occurence}";
	#if [ $occurence -gt 1 ]; then
	#	echo "${file}";
	#fi
done

for file in ${TXT_FILES}; do
	new_file_name=$( echo "${file}" | perl -pe 's/(\d{2})(\d{2})(\d{4})/$1.$2.$3/' );
	mv -v "${file}" "${new_file_name}";
done
