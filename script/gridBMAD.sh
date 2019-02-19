#!/bin/bash
#This is a template script for use in the batch queueing system. Please only edit the user sections.
LOCAL_DIR=${TMPDIR}
################USER SETTINGS###########################
#You can edit the variables here, but something valid must be present.
# SOURCE_DIR defaults to a files subdirectory of the directory you submitted the job from
#Comment out to not import any files for the job. Edit for your specific needs.
SOURCE_DIR=/nfs/gm2/data1/achapela/BMAD2018/
DESTINATION_DIR=/nfs/gm2/data1/achapela/BMAD2018/Jobs/${JOB_ID}
########################################################
if [ ! -z "${SOURCE_DIR}" ]; then
   rsync -avz ${SOURCE_DIR}/g-2/test ${LOCAL_DIR}
   rsync -avz ${SOURCE_DIR}/g-2/magneticfield/inf_field_alone.dat ${LOCAL_DIR}/test/
   rsync -avz ${SOURCE_DIR}/g-2/magneticfield/injec_fld.dat ${LOCAL_DIR}/test
   rsync -avz ${SOURCE_DIR}/g-2/files/KICKER_E989_NoRolledEdges.dat ${LOCAL_DIR}/test/
   rsync -avz ${SOURCE_DIR}/production/bin/g2_tracking ${LOCAL_DIR}/test/
fi

#Put your code in the user section below. You can delete the entire
#section between USER SECTION and END USER SECTION - it is a very simple
#example script that does a loop and echos some job data for testing.
#################USER SECTION###########################
cd ${LOCAL_DIR}/test/
rm -r ${LOCAL_DIR}/test/2018*
${LOCAL_DIR}/test/g2_tracking > $LOCAL_DIR/${JOB_ID}.log

#################END USER SECTION#######################
mkdir -p ${DESTINATION_DIR}
ls ${DESTINATION_DIR}
rsync -avz ${LOCAL_DIR}/ ${DESTINATION_DIR}
#mv ${DESTINATION_DIR}/test/2018*/Time_Dep_Moments_at_END.dat ${DESTINATION_DIR}
mv ${DESTINATION_DIR}/test/2018*/*.dat ${DESTINATION_DIR}
mv ${DESTINATION_DIR}/${JOB_ID}.log ${DESTINATION_DIR}
rm -rf ${DESTINATION_DIR}/test/
