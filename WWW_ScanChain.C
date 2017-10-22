//  .
// ..: P. Chang, philip@physics.ucsd.edu

#include "WWW_ScanChain.h"

//_________________________________________________________________________________________________
void ScanChain(TChain* chain, TString output_name, TString base_optstr, int nevents)
{
    // -~-~-~-~-~-~
    // Event Looper
    // -~-~-~-~-~-~
    Looper<WWWTree> looper(chain, &wwwbaby, nevents);
    chain->GetEntry(0);
    wwwbaby.Init(chain->GetTree());

    // -~-~-~-~-~-~-~-~-~-~-
    // Parse option settings
    // -~-~-~-~-~-~-~-~-~-~-
    TString option = base_optstr;
    RooUtil::print("the base option string = " + base_optstr);
    int babyver = getBabyVersion(base_optstr);
    std::cout << "baby version = " << babyver << std::endl;

    // -~-~-~-~-~
    // Event List
    // -~-~-~-~-~
    RooUtil::EventList event_list("list.txt");

    // -~-~-~-~-~
    // Set output
    // -~-~-~-~-~
    RooUtil::AutoHist hists;
    RooUtil::TTreeX tx;

    // -~-~-~-~-~-~
    // Set skimming
    // -~-~-~-~-~-~
    bool doskim = false;

    if (base_optstr.Contains("doskim")) { doskim = true; }
    if (doskim)
    {
        looper.setSkim(output_name);
        looper.setSkimBranchFilterPattern(
        {
        "Flag_EcalDeadCellTriggerPrimitiveFilter",
        "Flag_HBHEIsoNoiseFilter",
        "Flag_HBHENoiseFilter",
        "Flag_badChargedCandidateFilter",
        "Flag_badMuonFilter",
        "Flag_eeBadScFilter",
        "Flag_globalTightHalo2016",
        "Flag_goodVertices",
        "HLT_DoubleEl",
        "HLT_DoubleEl_DZ",
        "HLT_DoubleEl_DZ_2",
        "HLT_DoubleEl_noiso",
        "HLT_DoubleMu",
        "HLT_DoubleMu_noiso",
        "HLT_MuEG",
        "HLT_MuEG_noiso",
        "evt",
        "evt_dataset",
        "evt_passgoodrunlist",
        "evt_scale1fb",
        "firstgoodvertex",
        "genPart_motherId",
        "genPart_p4*",
        "genPart_pdgId",
        "genPart_status",
        "genPart_charge",
        "isData",
        "jets_csv",
        "jets_p4*",
        "lep_3ch_agree",
        "lep_charge",
        "lep_dxy",
        "lep_dz",
        "lep_etaSC",
        "lep_ip3d",
        "lep_ip3derr",
        "lep_isFromB",
        "lep_isFromC",
        "lep_isFromL",
        "lep_isFromLF",
        "lep_isFromW",
        "lep_isFromZ",
        "lep_isTriggerSafe_v1",
        "lep_isTriggerSafe_v2",
        "lep_lostHits",
        "lep_mc_Id",
        "lep_motherIdSS",
        "lep_p4*",
        "lep_pass_VVV_cutbased_fo",
        "lep_pass_VVV_cutbased_fo_noiso",
        "lep_pass_VVV_cutbased_tight",
        "lep_pass_VVV_cutbased_tight_noiso",
        "lep_pass_VVV_cutbased_veto",
        "lep_pass_VVV_cutbased_veto_noiso",
        "lep_genPart_index",
        "nlep_VVV_cutbased_veto",
        "lep_pdgId",
        "lep_relIso03EA",
        "lep_relIso03EAv2",
        "lumi",
        "met_phi",
        "met_pt",
        "ngenLep",
        "ngenLepFromTau",
        "nisoTrack_mt2_cleaned_VVV_cutbased_veto",
        "nVert",
        "run"
        }
        );
    }

    while (looper.nextEvent())
    {
        // -~-~-~-~-~-~-~-~-~-~-~-
        // Remove duplicate events
        // -~-~-~-~-~-~-~-~-~-~-~-
        if (wwwbaby.isData())
        {
            duplicate_removal::DorkyEventIdentifier id(wwwbaby.run(), wwwbaby.evt(), wwwbaby.lumi());
            if (is_duplicate(id)) { continue; }
        }

        // -~-~-~-~-~-~-~-~-~-~-~-
        // If do skim, skim presel
        // -~-~-~-~-~-~-~-~-~-~-~-
        setObjectIndices();
        if (doskim)
        {
            if (
                (
                    lepidx["VetoLepton"].size() == 2
                    && lepidx["TightLepton"].size() >= 1
                    && jetidx["GoodSSJet"].size() >= 2
                    && ( wwwbaby.lep_p4()[lepidx["VetoLepton"][0]].pt() >= 30.)
                    && ( wwwbaby.lep_p4()[lepidx["VetoLepton"][1]].pt() >= 30.)
                )
                ||
                (
                    lepidx["LooseLepton"].size() >= 3
                    && lepidx["Tight3lLepton"].size() >= 2
                    && ( wwwbaby.lep_p4()[lepidx["LooseLepton"][0]].pt() >= 25.)
                    && ( wwwbaby.lep_p4()[lepidx["LooseLepton"][1]].pt() >= 20.)
                    && ( wwwbaby.lep_p4()[lepidx["LooseLepton"][2]].pt() >= 20.)
                )
            )
            {
                looper.fillSkim();
                continue;
            }
        }

        if (event_list.has(wwwbaby.run(), wwwbaby.lumi(), wwwbaby.evt()))
            printEvent();

        if (base_optstr.Contains("dosync"))
            doSync();

        // -~-~-~-~-~-~-~-~-~-~-~-
        // Do analysis here
        // -~-~-~-~-~-~-~-~-~-~-~-
        doAnalysis(hists);
    }

    if (doskim) { looper.saveSkim(); }
    else { hists.save(output_name); }
}
// eof
