#!/bin/env python

def printEventList(logfilename, pttn, outputname):
    import os.path
    if not os.path.isfile(logfilename):
        print "I can't find the log file: {}".format(logfilename)
        return
    lines = open(logfilename).readlines()
    of = open(outputname, "w")
    for line in lines:
        if line.find(pttn) != -1 and line.find("RooUtil::") != -1:
            of.write(line.strip().split()[-1:][0] + "\n")

printEventList("www.log", "SSEE", "SREE_www_2l_ext1_mia_1.txt")
printEventList("www.log", "SSEM", "SREM_www_2l_ext1_mia_1.txt")
printEventList("www.log", "SSMM", "SRMM_www_2l_ext1_mia_1.txt")

printEventList("tt1l.log", "SSAREE", "AREE_ttbar_1ltop_mgmlm_ext1star.txt")
printEventList("tt1l.log", "SSAREM", "AREM_ttbar_1ltop_mgmlm_ext1star.txt")
printEventList("tt1l.log", "SSARMM", "ARMM_ttbar_1ltop_mgmlm_ext1star.txt")

printEventList("wz.log", "WZCR1SFOS", "WZCR1SFOS_wz_3lstar.txt")
printEventList("wz.log", "WZCR2SFOS", "WZCR2SFOS_wz_3lstar.txt")
printEventList("wz.log", "SSWZCREE", "SSWZCREE_wz_3lstar.txt")
printEventList("wz.log", "SSWZCREM", "SSWZCREM_wz_3lstar.txt")
printEventList("wz.log", "SSWZCRMM", "SSWZCRMM_wz_3lstar.txt")

printEventList("data.log", "SSAREE", "AREE_datastar.txt")
printEventList("data.log", "SSAREM", "AREM_datastar.txt")
printEventList("data.log", "SSARMM", "ARMM_datastar.txt")

