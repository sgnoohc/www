#!/bin/env python

import time
import json

from metis.Sample import DirectorySample
from metis.CondorTask import CondorTask

from metis.StatsParser import StatsParser

import sys
import os
import glob
import subprocess

# Configurations
job_tag = "v16_skimv3__trigsafev2"
baby_version = "16"
exec_path = os.path.join(os.getenv("ANALYSIS_BASE"), "scripts", "run.sh")
tar_path = os.path.join(os.getenv("ANALYSIS_BASE"), "scripts", "package.tar.gz")
hadoop_path = "metis/wwwlooper/{}".format(job_tag)
args = "scanchains/WWW_ScanChain.C output.root t -1 doskim"
total_summary = {}
while True:
    task = CondorTask(
            sample = DirectorySample(
                dataset="/WWW_v0_1_{}".format(baby_version),
                location="/hadoop/cms/store/user/bhashemi/AutoTwopler_babies/merged/VVV/WWW_v0.1.16/skim/",
                globber="*.root"
                ),
            open_dataset = False,
            flush = True,
            files_per_output = 1,
            output_name = "merged.root",
            tag = job_tag,
            arguments = args,
            executable = exec_path,
            tarfile = tar_path,
            special_dir = hadoop_path,
            condor_submit_params = {"sites" : "UAF,T2_US_UCSD"}
            )
    task.process()
    # save some information for the dashboard
    total_summary["WWW_v0_1_{}_{}".format(baby_version, job_tag)] = task.get_task_summary()
    # parse the total summary and write out the dashboard
    StatsParser(data=total_summary, webdir="~/public_html/dump/wwwmetis/").do()
    os.system("chmod -R 755 ~/public_html/dump/wwwmetis")
    if task.complete():
        print ""
        print "Job={} finished".format(job_tag)
        print ""
        break
    time.sleep(30)
