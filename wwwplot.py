#!/bin/env python

from plottery import plottery as p
import ROOT as r
import plottery_wrapper as pw

import os
if not os.path.isdir("plots"):
    os.makedirs("plots")

tfile = r.TFile("output.root")
hists = {}

proc_groups = {}
proc_groups["W"]        = [ "wj", "wg" ]
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
proc_groups["Fake"]     = [ "fakepred" ]
proc_groups["WH"]       = [ "whwww" ]
proc_groups["WWW"]      = [ "www" ]
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
proc_colors["Fake"]     = 2005
proc_colors["WH"]       = 4
proc_colors["WWW"]      = 2
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
proc_categs["Fake"]     = "bkg"
proc_categs["VVV"]      = "bkg"
proc_categs["VH"]       = "bkg"
proc_categs["WH"]       = "sig"
proc_categs["WWW"]      = "sig"
proc_categs["Data"]     = "data"

bkg_groups = {}
bkg_groups["Prompt"]             = [ "trueSS", "true3L", "trueWWW" ]
bkg_groups["Q-flip"]             = [ "chargeflips" ]
bkg_groups["Lost-Lep"]           = [ "SSLL", "3lLL" ]
bkg_groups["#gamma#rightarrowl"] = [ "photonfakes", "photondoublefakes", "photontriplefakes", "fakesphotonfakes", "otherphotonfakes" ]
bkg_groups["Fake"]               = [ "fakes", "doublefakes"]
#bkg_groups["Fake"]               = [ "fakepred" ]
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

def drawbyproc(histname, options={}):
    # Declare a map to hold the histograms that I access for this round of plotting
    hists = {}
    # Looping over MC sample process (e.g. W, ttbar, WZ, etc.)
    for key in proc_groups:
        # the total background for this category is saved (e.g. W, ttbar, WZ, etc.)
        histsum = None
        # Loop over the individual that makes up the grouping.
        for proc in proc_groups[key]:
            # place holder
            hist = None
            # Form the name of the histogram
            histkey = proc + "__" + histname
            # Try to access it
            try :
                hist = hists[histkey]
            # If not get it from the tfile
            except:
                # Open it and save it to the self.hists which persists as long as this object persists.
                hists[histkey] = tfile.Get( histkey )
                # Get the pointer
                hist = hists[histkey]
            # If successfully retrieved
            if hist:
                # If already a clone was created copy the content over
                if histsum:
                    histsum.Add( hist )
                # If a clone has not been created yet, create one
                else:
                    histsum = hist.Clone( key )
                    histsum.SetDirectory( 0 )
        # Once done looping over the grouping, set the histogram
        if histname.find("Pred") == -1 and key == "Fake": continue
        hists[key] = histsum
    # Now, we put them in std::vector<TH1*> so that we can pass it on to plotmaker.cc
    v_bkg_hists = []
    v_sig_hists = []
    data_hist = None
    colors = []
    for key in proc_categs:
        if histname.find("Pred") == -1 and key == "Fake": continue
        if proc_categs[key] == "bkg" and hists[key]:
            v_bkg_hists.append(hists[key])
            colors.append(proc_colors[key])
        if proc_categs[key] == "sig" and hists[key]:
            v_sig_hists.append(hists[key])
        if proc_categs[key] == "data" and hists[key]:
            data_hist = hists[key]
    pw.plot_hist(data_hist, v_bkg_hists, v_sig_hists, options, colors)


def drawbytype(histname, options={}):
    # Declare a map to hold the histograms that I access for this round of plotting
    hists = {}
    # Looping over based on background categorization
    for bkgtype in bkg_groups:
        # the total background for this category is saved (e.g. trueSS, LL, fakes, etc.)
        histsum = None
        # Loop over the individual bkg type
        for bkg in bkg_groups[bkgtype]:
            # place holder
            hist = None
            # Form the name of the histogram
            histkey = "_" + bkg + "_" + histname
            # Try to access it
            try :
                hist = hists[histkey]
            # If not get it from the tfile
            except:
                # Open it and save it to the hists which persists as long as this object persists.
                hists[histkey] = tfile.Get( histkey )
                # Get the pointer
                hist = hists[histkey]
            # If successfully retrieved
            if hist:
                # If already a clone was created copy the content over
                if histsum:
                    histsum.Add( hist )
                # If a clone has not been created yet, create one
                else:
                    histsum = hist.Clone( bkgtype )
                    histsum.SetDirectory( 0 )
        # Once done looping over the grouping, set the histogram
        hists[bkgtype] = histsum
    # Now, we put them in std::vector<TH1*> so that we can pass it on to plotmaker.cc
    v_bkg_hists = []
    v_sig_hists = []
    data_hist = None
    colors = []
    # For the histograms we have stylize a bit
    for key in bkg_groups:
        if bkg_categs[key] == "bkg"  and hists[key]:
            v_bkg_hists.append(hists[key])
            colors.append(bkg_colors[key])
        if bkg_categs[key] == "sig"  and hists[key]:
            v_sig_hists.append(hists[key])
        if bkg_categs[key] == "data" and hists[key]:
            hists[key].SetLineColor( 1 )
            data_hist = hists[key]
    pw.plot_hist(data_hist, v_bkg_hists, v_sig_hists, options, colors)

def drawclosure(histname, histname_fakepred, options={}):
    # Declare a map to hold the histograms that I access for this round of plotting
    hists = {}
    hists["tt1l__"+histname] = tfile.Get("tt1l__"+histname).Clone("tt1l")
    hists["tt1l__"+histname].Reset()
    hists["tt1l__"+histname].Add(tfile.Get("tt1l__"+histname))
    hists["wj__"+histname] = tfile.Get("wj__"+histname).Clone("W")
    hists["wj__"+histname].Reset()
    hists["wj__"+histname].Add(tfile.Get("wj__"+histname))
    hists["wj__"+histname].Add(tfile.Get("wg__"+histname))
    hists["fakepred__"+histname] = tfile.Get("fakepred__"+histname_fakepred).Clone("Pred")
    hists["fakepred__"+histname].Reset()
    hists["fakepred__"+histname].Add(tfile.Get("fakepred__"+histname_fakepred))
    hists["www__"+histname] = tfile.Get("www__"+histname).Clone("W")
    hists["www__"+histname].Reset()
    print hists
    # Now, we put them in std::vector<TH1*> so that we can pass it on to plotmaker.cc
    v_bkg_hists = []
    v_bkg_hists.append(hists["wj__"+histname])
    v_bkg_hists.append(hists["tt1l__"+histname])
    print v_bkg_hists
    #v_sig_hists = [hists["www__"+histname]];
    v_sig_hists = []
    data_hist = hists["fakepred__"+histname]
    data_hist.Print("all")
    colors = []
    colors.append(2006)
    colors.append(2005)
    options["output_name"] = histname+".pdf"
    # For the histograms we have stylize a bit
    #for key in bkg_groups:
    #    if bkg_categs[key] == "bkg"  and hists[key]:
    #        v_bkg_hists.append(hists[key])
    #        colors.append(bkg_colors[key])
    #    if bkg_categs[key] == "sig"  and hists[key]:
    #        v_sig_hists.append(hists[key])
    #        hists[key].Print("all")
    #    if bkg_categs[key] == "data" and hists[key]:
    #        hists[key].SetLineColor( 1 )
    #        data_hist = hists[key]
    pw.plot_hist(data_hist, v_bkg_hists, v_sig_hists, options, colors)

if __name__ == "__main__":

    drawbytype("PRSS_MjjW"  , options={"output_name": "plots/fig2_a_typePRSS_MjjW.png"  , "nbin":12, "blind":True})
    drawbytype("PRSS_Mll"  , options={"output_name": "plots/fig2_b_typePRSS_Mll.png"  , "nbin":12, "blind":True})
    drawbytype("PRSS_MET"  , options={"output_name": "plots/fig2_c_typePRSS_MET.png"  , "nbin":12, "blind":True})
    drawbytype("PRSS_MTmax"  , options={"output_name": "plots/fig2_d_typePRSS_MTmax.png"  , "nbin":12, "blind":True})

    drawbytype("PR3L_DPhi3lMET"  , options={"output_name": "plots/fig3_a_typePR3L_DPhi3lMET.png"  , "nbin":12, "blind":True})
    drawbytype("PR3L_MET"  , options={"output_name": "plots/fig3_b_typePR3L_MET.png"  , "nbin":12, "blind":True})
    drawbytype("PR3L_Pt3l"  , options={"output_name": "plots/fig3_c_typePR3L_Pt3l.png"  , "nbin":12, "blind":True})
    drawbytype("PR3L_MSFOS"  , options={"output_name": "plots/fig3_d_typePR3L_MSFOS.png"  , "nbin":12, "blind":True})

    drawbytype("SR_count", options={"output_name":"plots/fig4_SR_count.png", "blind":True, "print_yield":True, "yield_prec":2})
