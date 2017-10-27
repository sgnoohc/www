#!/bin/env python

################################
# Job tag and output hadoop path
################################

# NOTE: If you want to resubmit the skimming job, you need to delete $ANALYSIS_BASE/tasks and hadoop_path output path

job_tag = "v16_skim_v2_4"
hadoop_path = "metis/wwwlooper/{}".format(job_tag) # The output goes to /hadoop/cms/store/user/$USER/"hadoop_path"




###################################################################################################################
###################################################################################################################
# Below are the Metis submission code that users do not have to care about.
###################################################################################################################
###################################################################################################################

import time
import json
import metis

from time import sleep

from metis.Sample import DirectorySample
from metis.CondorTask import CondorTask

from metis.StatsParser import StatsParser

import sys
import os
import glob
import subprocess

# file/dir paths
wwwdir = os.path.dirname(os.path.realpath(__file__))
anadir = os.getenv("ANALYSIS_BASE")
scriptsdir = os.path.join(os.getenv("ANALYSIS_BASE"), "scripts")
tar_path = os.path.join(wwwdir, "package.tar")
targzpath = tar_path + ".gz"
metisdashboardpath = os.path.join(os.path.dirname(os.path.dirname(metis.__file__)), "dashboard")

# Create tarball
os.system("tar -cf {} *.C *.h".format(tar_path))
os.chdir(anadir)
os.system("tar -rf {} rooutil/rooutil.so WWW_CORE/WWW_CORE.so rooutil/*.h WWW_CORE/*.h".format(tar_path))
os.chdir(scriptsdir)
os.system("tar -rf {} *.sh *.C ".format(tar_path))
os.chdir(wwwdir)
os.system("gzip -f {}".format(tar_path))

# Configurations
baby_version = "16"
exec_path = os.path.join(scriptsdir, "run.sh")
args = "WWW_ScanChain.C output.root t -1 doskim"
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
            tarfile = targzpath,
            special_dir = hadoop_path,
            condor_submit_params = {"sites" : "UAF,T2_US_UCSD"}
            )
    task.process()
    # save some information for the dashboard
    total_summary["WWW_v0_1_{}_{}".format(baby_version, job_tag)] = task.get_task_summary()
    # parse the total summary and write out the dashboard
    StatsParser(data=total_summary, webdir=metisdashboardpath).do()
    os.system("msummary | tee summary.txt")
    os.system("chmod -R 755 {}".format(metisdashboardpath))
    if task.complete():
        print ""
        print "Job={} finished".format(job_tag)
        print ""
        break

    print 'Press Ctrl-C to force update, otherwise will sleep for 30 seconds'
    try:
        for i in range(0,30):
            sleep(1) # could use a backward counter to be preeety :)
    except KeyboardInterrupt:
        raw_input("Press Enter to force update, or Ctrl-C to quit.")
        print "Force updating..."

print "Renaming merged file names ..."
if not os.path.isfile("WWW_CORE/rename"):
    os.chdir("WWW_CORE/")
    os.system("make rename")
    os.chdir("../")
import getpass
username = getpass.getuser()
os.system("./WWW_CORE/rename mapping.txt /hadoop/cms/store/user/{}/{}/WWW_v0_1_{}_{}/".format(username, hadoop_path, baby_version, job_tag))


