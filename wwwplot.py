#!/bin/env python

from plottery import plottery as p
import ROOT as r
import plottery_wrapper as pw
from histx import HistX
import math

import os
if not os.path.isdir("plots"):
    os.makedirs("plots")

tfile = r.TFile("output.root")
hists = {}

proc_groups = {}
proc_groups["W"]        = [ "wj", "wg", "wgstar" ]
proc_groups["Z"]        = [ "dy", "zg" ]
proc_groups["tt1l"]     = [ "tt1l" ]
proc_groups["tt2l"]     = [ "tt2l" ]
proc_groups["WW"]       = [ "ww", "wwdpi", "vbsww" ]
proc_groups["WZ"]       = [ "wz" ]
proc_groups["ZZ"]       = [ "zz" ]
proc_groups["tX"]       = [ "singletop" ]
proc_groups["ttX"]      = [ "ttz", "ttw", "tth", "ttg" ]
proc_groups["VVV"]      = [ "wwz_incl", "wzz_incl", "zzz_incl"]#, "wwg_incl", "wzg_incl" ]
proc_groups["VH"]       = [ "vh" ]
proc_groups["WH"]       = [ "whwww" ]
proc_groups["WWW"]      = [ "www" ]
proc_groups["Fake"]     = [ "fakepred" ]
proc_groups["Data"]     = [ "data_mm", "data_em", "data_ee", "data_other" ]

proc_colors = {}
proc_colors["W"]        = 2006
proc_colors["Z"]        = 2010
proc_colors["tt1l"]     = 2005
proc_colors["tt2l"]     = 2008
proc_colors["WW"]       = 2007
proc_colors["WZ"]       = 2003
proc_colors["ZZ"]       = 2011
proc_colors["tX"]       = 2009
proc_colors["ttX"]      = 2004
proc_colors["VVV"]      = 616
proc_colors["VH"]       = 2002
proc_colors["WH"]       = 4
proc_colors["WWW"]      = 2
proc_colors["Fake"]     = 2005
proc_colors["Data"]     = 1

proc_categs = {}
proc_categs["W"]        = "bkg"
proc_categs["Z"]        = "bkg"
proc_categs["tt1l"]     = "bkg"
proc_categs["tt2l"]     = "bkg"
proc_categs["WW"]       = "bkg"
proc_categs["WZ"]       = "bkg"
proc_categs["ZZ"]       = "bkg"
proc_categs["tX"]       = "bkg"
proc_categs["ttX"]      = "bkg"
proc_categs["VVV"]      = "bkg"
proc_categs["VH"]       = "bkg"
proc_categs["WH"]       = "sig"
proc_categs["WWW"]      = "sig"
proc_categs["Fake"]     = "bkg"
proc_categs["Data"]     = "data"

bkg_groups = {}
bkg_groups["Prompt"]             = [ "trueSS", "true3L", "trueWWW" ]
bkg_groups["Q-flip"]             = [ "chargeflips" ]
bkg_groups["Lost-Lep"]           = [ "SSLL", "3lLL" ]
bkg_groups["#gamma#rightarrowl"] = [ "photonfakes", "photondoublefakes", "photontriplefakes", "fakesphotonfakes", "otherphotonfakes" ]
#bkg_groups["Fake"]               = [ "fakes", "doublefakes"]
bkg_groups["Fake"]               = [ "fakepred" ]
bkg_groups["Others"]             = [ "others" ]
bkg_groups["Data"]               = [ "data_mm", "data_em", "data_ee", "data_other" ]
bkg_groups["WWW"]                = [ "www" ]
bkg_groups["WH"]                 = [ "whwww" ]

bkg_colors = {}
bkg_colors["Prompt"]             = 2001
bkg_colors["Q-flip"]             = 2007
bkg_colors["Lost-Lep"]           = 2003
bkg_colors["#gamma#rightarrowl"] = 2011
bkg_colors["Fake"]               = 2005
bkg_colors["Others"]             = 616
bkg_colors["Data"]               = 1
bkg_colors["WWW"]                = 2
bkg_colors["WH"]                 = 4

bkg_categs = {}
bkg_categs["Prompt"]             = "bkg"
bkg_categs["Q-flip"]             = "bkg"
bkg_categs["Lost-Lep"]           = "bkg"
bkg_categs["#gamma#rightarrowl"] = "bkg"
bkg_categs["Fake"]               = "bkg"
bkg_categs["Others"]             = "bkg"
bkg_categs["Data"]               = "data"
bkg_categs["WWW"]                = "sig"
bkg_categs["WH"]                 = "sig"

#_____________________________________________________________________________________________
# Loops over the categories defined above and aggregates all the histograms in to a dictionary
# Returns two dictionaries one aggregated by "types" (e.g. Fake, Prompt, and etc.)
#                      another aggregated by "procs" (e.g. WZ, WW, tt1l, and etc.)
def load(histname, options={}):
    byproc = {}
    bytype = {}
    for proc_group in proc_groups:
        tmpbyproc = []
        for bkg_group in bkg_groups:
            tmpbytype = []
            for proc in proc_groups[proc_group]:
                for bkg in bkg_groups[bkg_group]:
                    histkey = "{}_{}_{}".format(proc, bkg, histname)
                    hist = tfile.Get(histkey)
                    if hist:
                        hist = hist.Clone()
                        hist.SetDirectory(0)
                        if "WZNF" in options and options["WZNF"] and histname.find("SR_count") != -1 and proc == "wz":
                            for i in xrange(1, hist.GetNbinsX() + 1):
                                for j in xrange(1, hist.GetNbinsY() + 1):
                                    hist.SetBinContent(i, j, hist.GetBinContent(i, j) * options["WZNF"].GetBinContent(i))
                                    hist.SetBinError(i, j, math.sqrt(hist.GetBinError(i, j)**2 + (hist.GetBinContent(i, j) * (options["WZNF"].GetBinError(i) / options["WZNF"].GetBinContent(i)))**2))
                        tmpbyproc.append(hist)
                        tmpbytype.append(hist)
            if bkg_group in bytype:
                bytype[bkg_group].extend(tmpbytype)
            else:
                bytype[bkg_group] = []
                bytype[bkg_group].extend(tmpbytype)
        if proc_group in byproc:
            byproc[proc_group].extend(tmpbyproc)
        else:
            byproc[proc_group] = []
            byproc[proc_group].extend(tmpbyproc)
    for bkg_group in bkg_groups:
        if len(bytype[bkg_group]) != 0:
            sumhist = bytype[bkg_group][0].Clone(bkg_group)
            sumhist.Reset()
            for hist in bytype[bkg_group]:
                sumhist.Add(hist)
            bytype[bkg_group] = sumhist
        else:
            bytype[bkg_group] = None
    for proc_group in proc_groups:
        if len(byproc[proc_group]) != 0:
            sumhist = byproc[proc_group][0].Clone(proc_group)
            sumhist.Reset()
            for hist in byproc[proc_group]:
                sumhist.Add(hist)
            byproc[proc_group] = sumhist
        else:
            byproc[proc_group] = None
    if "WZNF" in options: del options["WZNF"]
    return byproc, bytype

#_____________________________________________________________________________________________
# Draw a histogram with backgrounds categorized by the "procs" (i.e. process, e.g. tt1l, WW, etc.)
def drawbyproc(histname, options={}):
    byproc, bytype = load(histname, options)
    # by proc
    v_bkg_hists = []
    v_sig_hists = []
    data_hist = None
    colors = []
    for proc in byproc:
        if not byproc[proc]: continue
        if proc_categs[proc] == "bkg":
            v_bkg_hists.append(HistX(byproc[proc]).get_hist())
            colors.append(proc_colors[proc])
        if proc_categs[proc] == "sig":
            v_sig_hists.append(HistX(byproc[proc]).get_hist())
        if proc_categs[proc] == "data":
            data_hist = HistX(byproc[proc]).get_hist_no_syst()
    pw.plot_hist_1d(
            hdata=data_hist,
            hbkgs=v_bkg_hists,
            hsigs=v_sig_hists,
            options=options,
            colors=colors)

#_____________________________________________________________________________________________
# Draw a histogram with backgrounds categorized by the "types" (i.e. Fake, Prompt, and etc.)
def drawbytype(histname, options={}):
    byproc, bytype = load(histname, options)
    # by type
    v_bkg_hists = []
    v_sig_hists = []
    data_hist = None
    colors = []
    for typ in bytype:
        if not bytype[typ]: continue
        if typ == "Others": continue
        # Flat normalization systematics on Fake contributions
        if typ == "Fake":
            bytype[typ].SetBinContent(1, 0,  0.2) # ee channel gets 100%
            bytype[typ].SetBinContent(2, 0,  0.1) # em channel gets 200%
            bytype[typ].SetBinContent(3, 0,  0.2) # mm channel gets 20%
            bytype[typ].SetBinContent(4, 0,  0.2) # 0SFOS gets 100%
            bytype[typ].SetBinContent(5, 0,  0.2) # 1SFOS gets 1000%
            bytype[typ].SetBinContent(6, 0,  0.2) # 2SFOS gets 0%
        if bkg_categs[typ] == "bkg":
            v_bkg_hists.append(HistX(bytype[typ]).get_hist())
            colors.append(bkg_colors[typ])
        if bkg_categs[typ] == "sig":
            v_sig_hists.append(HistX(bytype[typ]).get_hist())
        if bkg_categs[typ] == "data":
            data_hist = HistX(bytype[typ]).get_hist_no_syst()
    pw.plot_hist_1d(
            hdata=data_hist,
            hbkgs=v_bkg_hists,
            hsigs=v_sig_hists,
            options=options,
            colors=colors)

#_____________________________________________________________________________________________
# From the WZCR count plot, obtain NFs for each categories
def getWZNF():
    byproc, bytype = load("WZCR_count")
    if len(byproc) == 0:
        print "ERROR: getWZNF()  Do not have any histograms to work with! How am I supposed to compute NFs?"
    # WZ histograms
    hist_WZ = HistX(byproc["WZ"]).get_hist()
    # nonWZ histogram
    hist_nonWZ = HistX(byproc["WZ"]).get_hist().Clone("non-WZ") # clone a histogram for place holder
    hist_nonWZ.Reset() # Reset the content
    for proc in byproc:
        # Skip WZ
        if proc == "WZ": continue
        # Sum only the backgrounds
        if proc_categs[proc] != "bkg": continue
        if byproc[proc]: hist_nonWZ.Add(HistX(byproc[proc]).get_hist())
    # data histogram
    data_hist = HistX(byproc["Data"]).get_hist()
    # data - nonWZ
    obs_WZ = data_hist.Clone("obsWZ")
    obs_WZ.Add(hist_nonWZ, -1) # subtract nonWZ
    # NF = obsWZ / predWZ
    NFs = obs_WZ.Clone("NFs")
    NFs.Divide(obs_WZ, hist_WZ)
    NFs.SetBinContent(4, 1.0) # 0SFOS region gets 1.0 NF but with uncertainty from 1SFOS + 2SFOS
    err_0SFOS = NFs.GetBinError(5) / NFs.GetBinContent(5)
    err_1SFOS = NFs.GetBinError(6) / NFs.GetBinContent(6)
    err_larger = err_0SFOS if err_0SFOS > err_1SFOS else err_1SFOS
    NFs.SetBinError(4, err_larger) # 0SFOS region gets 1.0 NF but with uncertainty from 1SFOS + 2SFOS
    #NFs.Print("all")
    return NFs

if __name__ == "__main__":

    drawbytype("SR_count", {"inject_signal": True, "print_yield": True, "output_name": "SR_count_wNF.png", "blind": True, "WZNF": getWZNF()})
    drawbytype("SR_count", {"inject_signal": True, "print_yield": True, "output_name": "SR_count.png", "blind": True})
