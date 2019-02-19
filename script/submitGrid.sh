#!/bin/bash

njob=`qstat | wc -l`


while [ 1 -lt 2 ]
do

njob=`qstat | wc -l`

if [ $njob -lt 60 ] 
then
	echo " "
	echo "You may submit jobs. Current number of job = ${njob}"
	echo " -- SUBMITTING JOB WFD_SN_${wfdid} -- "
	echo " "
	qsub gridBMAD.sh
	let "wfdid++"
else
	echo " "
	echo " -- > Reached Job Queue limit. Curent number of job = ${njob}" 
	echo " -- WAIT 60 SECONDS "
	echo " "
	sleep 60
fi

done
