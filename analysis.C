
void doClosure( RooUtil::AutoHist& );
bool doAnalysis( RooUtil::AutoHist&, bool doskim );

void fillHistograms( RooUtil::AutoHist&, TString, int regionid, int isyst );
void fillHistogramsFull( RooUtil::AutoHist&, TString, TString, TString, int regionid, int isyst );
void fillLepHistograms( RooUtil::AutoHist&, TString, TString, TString, int );
void fillJetHistograms( RooUtil::AutoHist&, TString, TString, TString, int );
void fillWWWHistograms( RooUtil::AutoHist&, TString, int );

void printevent( TString );

//void doTmpAnalysis( RooUtil::AutoHist& hists );

//_________________________________________________________________________________________________
void fillLepHistograms( RooUtil::AutoHist& hists, TString categ, TString name, TString prefix, int isyst )
{
    bool ff = prefix.Contains( "Pred" );
    double wgt = weight( ff, isyst );
    hists.fill( lepidx[categ].size(), isyst, Form( "%slep%s_size" , prefix.Data(), name.Data() ), wgt, 5, 0, 5, NSYST, 0, NSYST );
    for ( unsigned int i = 0; i < lepidx[categ].size() && i < MAXOBJ; ++i )
    {
        int ilep = lepidx[categ][i];
        hists.fill( wwwbaby.lep_pdgId()[ilep]      , isyst , Form( "%slep%s%d_pid"       , prefix.Data(), name.Data(), i ), wgt,   40,  -20     ,  20      , NSYST, 0, NSYST );
        hists.fill( wwwbaby.lep_p4()[ilep].pt()    , isyst , Form( "%slep%s%d_pt"        , prefix.Data(), name.Data(), i ), wgt, 1080,    0     , 250.     , NSYST, 0, NSYST );
        hists.fill( wwwbaby.lep_p4()[ilep].eta()   , isyst , Form( "%slep%s%d_eta"       , prefix.Data(), name.Data(), i ), wgt, 1080,   -3     ,   3      , NSYST, 0, NSYST );
        hists.fill( wwwbaby.lep_p4()[ilep].phi()   , isyst , Form( "%slep%s%d_phi"       , prefix.Data(), name.Data(), i ), wgt, 1080,   -3.1416,   3.1416 , NSYST, 0, NSYST );
        hists.fill( wwwbaby.lep_p4()[ilep].energy(), isyst , Form( "%slep%s%d_E"         , prefix.Data(), name.Data(), i ), wgt, 1080,    0     , 250.     , NSYST, 0, NSYST );
        hists.fill( wwwbaby.lep_relIso03EA()[ilep] , isyst , Form( "%slep%s%d_iso"       , prefix.Data(), name.Data(), i ), wgt, 1080,    0     ,   0.1    , NSYST, 0, NSYST );
        hists.fill( wwwbaby.lep_ip3d()[ilep]       , isyst , Form( "%slep%s%d_ip3"       , prefix.Data(), name.Data(), i ), wgt, 1080,   -0.05  ,   0.05   , NSYST, 0, NSYST );
        hists.fill( wwwbaby.lep_ip3derr()[ilep]    , isyst , Form( "%slep%s%d_ip3err"    , prefix.Data(), name.Data(), i ), wgt, 1080,   -0.5   ,   0.5    , NSYST, 0, NSYST );
        hists.fill( wwwbaby.lep_ip3d()[ilep]       , isyst , Form( "%slep%s%d_ip3_wide"  , prefix.Data(), name.Data(), i ), wgt, 1080,   -0.5   ,   0.5    , NSYST, 0, NSYST );
        hists.fill( wwwbaby.lep_ip3d()[ilep]       , isyst , Form( "%slep%s%d_ip3_widepp", prefix.Data(), name.Data(), i ), wgt, 1080,   -2.5   ,   2.5    , NSYST, 0, NSYST );
        hists.fill( wwwbaby.lep_ip3d()[ilep]       , isyst , Form( "%slep%s%d_ip3calc"   , prefix.Data(), name.Data(), i ), wgt, 1080,   -0.05  ,   0.05   , NSYST, 0, NSYST );
        hists.fill( wwwbaby.lep_dxy ()[ilep]       , isyst , Form( "%slep%s%d_dxy"       , prefix.Data(), name.Data(), i ), wgt, 1080,   -0.5   ,   0.5    , NSYST, 0, NSYST );
        hists.fill( wwwbaby.lep_dz  ()[ilep]       , isyst , Form( "%slep%s%d_dz"        , prefix.Data(), name.Data(), i ), wgt, 1080,   -0.5   ,   0.5    , NSYST, 0, NSYST );
        if ( wwwbaby.lep_ip3d()[ilep] > 0.5 )
            std::cout << wwwbaby.lep_ip3d()[ilep] << std::endl;
    }
}

//_________________________________________________________________________________________________
void fillJetHistograms( RooUtil::AutoHist& hists, TString categ, TString name, TString prefix, int isyst )
{
    bool ff = prefix.Contains( "Pred" );
    double wgt = weight( ff, isyst );
    hists.fill( jetidx[categ].size(), isyst, Form( "%sjet%s_size" , prefix.Data(), name.Data() ), wgt, 5, 0, 5, NSYST, 0, NSYST );
    for ( unsigned int i = 0; i < jetidx[categ].size() && i < MAXOBJ; ++i )
    {
        int ijet = jetidx[categ][i];
        hists.fill( wwwbaby.jets_p4()[ijet].pt()    , isyst, Form( "%sjet%s%d_pt" , prefix.Data(), name.Data(), i ), wgt, 180,  0     , 180     , NSYST, 0, NSYST );
        hists.fill( wwwbaby.jets_p4()[ijet].eta()   , isyst, Form( "%sjet%s%d_eta", prefix.Data(), name.Data(), i ), wgt, 180, -3     ,   3     , NSYST, 0, NSYST );
        hists.fill( wwwbaby.jets_p4()[ijet].phi()   , isyst, Form( "%sjet%s%d_phi", prefix.Data(), name.Data(), i ), wgt, 180, -3.1416,   3.1416, NSYST, 0, NSYST );
        hists.fill( wwwbaby.jets_p4()[ijet].energy(), isyst, Form( "%sjet%s%d_E"  , prefix.Data(), name.Data(), i ), wgt, 180,  0     , 250     , NSYST, 0, NSYST );
        hists.fill( wwwbaby.jets_csv()[ijet]        , isyst, Form( "%sjet%s%d_csv", prefix.Data(), name.Data(), i ), wgt, 180, -1     ,   1     , NSYST, 0, NSYST );
    }
}

//_________________________________________________________________________________________________
void fillWWWHistograms( RooUtil::AutoHist& hists, TString prefix, int isyst )
{
    bool ff = prefix.Contains( "Pred" );
    double wgt = weight( ff, isyst );
    hists.fill( wwwbaby.met_pt()                                 , isyst , Form( "%smet"        , prefix.Data() ) , wgt , 180 , 0. , 250.  , NSYST, 0, NSYST );
    hists.fill( MjjW()                                           , isyst , Form( "%sMjjW"       , prefix.Data() ) , wgt , 180 , 0. , 160.  , NSYST, 0, NSYST );
    hists.fill( MjjLead()                                        , isyst , Form( "%sMjjLead"    , prefix.Data() ) , wgt , 180 , 0. , 800.  , NSYST, 0, NSYST );
    hists.fill( DEtajjLead()                                     , isyst , Form( "%sDEtajjLead" , prefix.Data() ) , wgt , 180 , 0. , 9.    , NSYST, 0, NSYST );
    hists.fill( DPhill()                                         , isyst , Form( "%sDPhill"     , prefix.Data() ) , wgt , 180 , 0. , 3.1416, NSYST, 0, NSYST );
    hists.fill( DEtall()                                         , isyst , Form( "%sDEtall"     , prefix.Data() ) , wgt , 180 , 0. , 9.    , NSYST, 0, NSYST );
    hists.fill( Mll()                                            , isyst , Form( "%sMll"        , prefix.Data() ) , wgt , 180 , 0. , 180.  , NSYST, 0, NSYST );
    hists.fill( Mll()                                            , isyst , Form( "%sMll250"     , prefix.Data() ) , wgt , 180 , 0. , 250.  , NSYST, 0, NSYST );
    hists.fill( Mll()                                            , isyst , Form( "%sMll500"     , prefix.Data() ) , wgt , 180 , 0. , 500.  , NSYST, 0, NSYST );
    hists.fill( MTmax()                                          , isyst , Form( "%sMTmax"      , prefix.Data() ) , wgt , 180 , 0. , 180.  , NSYST, 0, NSYST );
    hists.fill( M4()                                             , isyst , Form( "%sm4"         , prefix.Data() ) , wgt , 180 , 0. , 180.  , NSYST, 0, NSYST );
    hists.fill( M4()                                             , isyst , Form( "%sm4wide"     , prefix.Data() ) , wgt , 150 , 0. , 1500. , NSYST, 0, NSYST );
    hists.fill( wwwbaby.nisoTrack_mt2_cleaned_VVV_cutbased_veto(), isyst , Form( "%snisotrack"  , prefix.Data() ) , wgt , 5   , 0  , 5     , NSYST, 0, NSYST );
    hists.fill( wwwbaby.nlep_VVV_cutbased_veto()                 , isyst , Form( "%snvetolep"   , prefix.Data() ) , wgt , 5   , 0  , 5     , NSYST, 0, NSYST );
    hists.fill( wwwbaby.nVert()                                  , isyst , Form( "%snvtx"       , prefix.Data() ) , wgt , 70  , 0  , 70.   , NSYST, 0, NSYST );
    if ( lepidx["3LTightLepton"].size() == 3 )
    {
        hists.fill( Pt3l()     , isyst, Form( "%sPt3l"         , prefix.Data() ) , wgt , 180 , 0. , 180.  , NSYST, 0, NSYST );
        hists.fill( DPhi3lMET(), isyst, Form( "%sDPhi3lMET"    , prefix.Data() ) , wgt , 180 , 0. , 3.1416, NSYST, 0, NSYST );
        if ( pass3L0SFOS() )
        {
            hists.fill( get0SFOSMll(), isyst, Form( "%sget0SFOSMll"  , prefix.Data() ) , wgt , 180 , 0. , 180., NSYST, 0, NSYST );
            hists.fill( get0SFOSMee(), isyst, Form( "%sget0SFOSMee"  , prefix.Data() ) , wgt , 180 , 0. , 180., NSYST, 0, NSYST );
        }
        if ( pass3L1SFOS() )
        {
            hists.fill( get1SFOSMll(), isyst, Form( "%sget1SFOSMll"  , prefix.Data() ) , wgt , 180 , 0. , 180., NSYST, 0, NSYST );
        }
        if ( pass3L2SFOS() )
        {
            hists.fill( get2SFOSMll0(), isyst, Form( "%sget2SFOSMll0" , prefix.Data() ) , wgt , 180 , 0. , 180., NSYST, 0, NSYST );
            hists.fill( get2SFOSMll1(), isyst, Form( "%sget2SFOSMll1" , prefix.Data() ) , wgt , 180 , 0. , 180., NSYST, 0, NSYST );
        }
    }
}

//_________________________________________________________________________________________________
void printevent( TString region )
{
    RooUtil::print( Form( "passed event list %s %llu %d %d", region.Data(), wwwbaby.evt(), wwwbaby.run(), wwwbaby.lumi() ) );
}

//_________________________________________________________________________________________________
void doClosure(RooUtil::AutoHist& hists)
{
//    if (sampleCategory().EqualTo("tt1l") || sampleCategory().EqualTo("wj"))
    if (sampleCategory().EqualTo("tt1l"))
    {
        if (lepidx["TightLepton"].size() >= 1 && lepidx["LooseLepton"].size() == 2 && jetidx["GoodSSJet"].size() >= 2 && jetidx["LooseBJet"].size() == 0)
        {
            for ( auto& idx : lepidx["LooseLepton"] )
            {
                if (wwwbaby.lep_motherIdSS()[idx] > 0) continue;
                if (abs(wwwbaby.lep_pdgId()[idx]) == 11)
                {
                    hists.fill(wwwbaby.lep_relIso03EAv2()[idx], Form("%s_el_reliso", sampleCategory().Data()), weight(), 40, 0, 0.4);
                }
                else
                {
                    hists.fill(wwwbaby.lep_relIso03EAv2()[idx], Form("%s_mu_reliso", sampleCategory().Data()), weight(), 40, 0, 0.4);
                    double relIso = wwwbaby.lep_relIso03EAv2()[idx];
                    double coneptcorr = std::max( 0., relIso - 0.06 );
                    double pt = wwwbaby.lep_p4()[idx].pt();
                    double corrpt = pt * ( 1 + coneptcorr );
                    double eta = wwwbaby.lep_p4()[idx].eta();
                    int mid = wwwbaby.lep_motherIdSS()[idx];
                    hists.fill(pt, wwwbaby.lep_relIso03EAv2()[idx], Form("%s_mu_pt_v_reliso", sampleCategory().Data()), weight(), 40, 0, 100, 40, 0, 0.4);
                    hists.fill(corrpt, wwwbaby.lep_relIso03EAv2()[idx], Form("%s_mu_conecorrpt_v_reliso", sampleCategory().Data()), weight(), 40, 0, 100, 40, 0, 0.4);
                    hists.fill(pt, Form("%s_mu_pt", sampleCategory().Data()), weight(), 40, 0, 100.);
                    hists.fill(corrpt, Form("%s_mu_conecorrpt", sampleCategory().Data()), weight(), 40, 0, 100.);
                    hists.fill(wwwbaby.lep_motherIdSS()[idx], Form("%s_mu_motherId", sampleCategory().Data()), weight(), 5, -4, 1.);
                    if (mid == -1)
                    {
                        hists.fill(pt, wwwbaby.lep_relIso03EAv2()[idx], Form("%s_mu_mid1_pt_v_reliso", sampleCategory().Data()), weight(), 40, 0, 100, 40, 0, 0.4);
                        hists.fill(corrpt, wwwbaby.lep_relIso03EAv2()[idx], Form("%s_mu_mid1_conecorrpt_v_reliso", sampleCategory().Data()), weight(), 40, 0, 100, 40, 0, 0.4);
                    }
                    double ptvarbounds[5] = {10., 20., 30., 50., 120.};
                    double etavarbounds[5] = {0., 1.2, 2.1, 2.4};
                    hists.fill(std::min(corrpt, 119.99), fabs(eta), Form("%s_mu_den_conecorrpt_v_eta", sampleCategory().Data()), weight(), 4, ptvarbounds, 3, etavarbounds);
                    if (isTightLepton(idx))
                        hists.fill(std::min(corrpt, 119.99), fabs(eta), Form("%s_mu_num_conecorrpt_v_eta", sampleCategory().Data()), weight(), 4, ptvarbounds, 3, etavarbounds);

                }
            }
        }
        if (passPRARSSMM())
        //if (passSSARMM())
        {
            float wgt = weight();
            wgt *= fakefactor(lepidx["LbntLepton"][0]);
            for (int isyst = 0; isyst < 3; ++isyst)
                hists.fill(0, Form("%s_ARSS_closure_counter", sampleCategory().Data()), wgt, 1, 0, 1);
//                hists.fill(0, isyst, Form("%s_ARSS_closure_counter", sampleCategory().Data()), wgt, 1, 0, 1, NSYST, 0, NSYST);
            printevent("MMAR");
        }
        else if (passPRVRSSMM())
        //else if (passSSMM())
        {
            for (int isyst = 0; isyst < 3; ++isyst)
                hists.fill(0, Form("%s_VRSS_closure_counter", sampleCategory().Data()), weight(), 1, 0, 1);
//                hists.fill(0, isyst, Form("%s_VRSS_closure_counter", sampleCategory().Data()), weight(), 1, 0, 1, NSYST, 0, NSYST);
            printevent("MMVR");
        }
        //// Prediction
        //if (passPRARSSEE() || passPRARSSEM() || passPRARSSMM())
        ////if (lepidx["TightLepton"].size() == 1 && lepidx["LooseLepton"].size() == 2 && jetidx["GoodSSJet"].size() >= 2)
        //{
        //    for (int isyst = 0; isyst < 3; ++isyst)
        //    {
        //        int flav = 0;
        //        float wgt = weight();
        //        flav = abs(wwwbaby.lep_pdgId()[lepidx["LbntLepton"][0]]) == 11 ? 0 : 1;
        //        float factor = 0;
        //        if ( isyst == 1 ) factor = -1;
        //        if ( isyst == 2 ) factor =  1;
        //        wgt *= fakefactor(lepidx["LbntLepton"][0], factor);
        //        hists.fill(flav, isyst, Form("%s_ARSS_closure_counter"       , sampleCategory().Data()), weight(), 2, 0, 2, NSYST, 0, NSYST);
        //        hists.fill(flav, isyst, Form("%s_VRSSPred_closure_counter"   , sampleCategory().Data()), wgt     , 2, 0, 2, NSYST, 0, NSYST);
        //    }
        //}
        //// Measurement
        //else if (passPRVRSSEE() || passPRVRSSEM() || passPRVRSSMM())
        ////else if (lepidx["TightLepton"].size() == 2 && lepidx["LooseLepton"].size() == 2 && jetidx["GoodSSJet"].size() >= 2)
        //{
        //    for ( auto& idx : lepidx["TightLepton"] )
        //    {
        //        if (wwwbaby.lep_motherIdSS()[idx] > 0) continue;
        //        //if (wwwbaby.lep_isFromW()[idx] == 1) continue;
        //        int flav = abs( wwwbaby.lep_pdgId()[idx] ) == 11 ? 0 : 1;
        //        hists.fill(flav, 0, Form("%s_VRSS_closure_counter"   , sampleCategory().Data()), weight(), 2, 0, 2, NSYST, 0, NSYST);
        //        hists.fill(flav, 1, Form("%s_VRSS_closure_counter"   , sampleCategory().Data()), weight(), 2, 0, 2, NSYST, 0, NSYST);
        //        hists.fill(flav, 2, Form("%s_VRSS_closure_counter"   , sampleCategory().Data()), weight(), 2, 0, 2, NSYST, 0, NSYST);
        //    }
        //}
    }
}

//_________________________________________________________________________________________________
bool doAnalysis( RooUtil::AutoHist& hists, bool doskim )
{
    bool passed = false;
    for ( int isyst = 0; isyst < NSYST; ++isyst )
    {
        if ( passSSEE              () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "SSEE"             , 0 , isyst ); }
        if ( passSSEM              () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "SSEM"             , 1 , isyst ); }
        if ( passSSMM              () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "SSMM"             , 2 , isyst ); }
        if ( pass3L0SFOS           () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "3L0SFOS"          , 3 , isyst ); }
        if ( pass3L1SFOS           () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "3L1SFOS"          , 4 , isyst ); }
        if ( pass3L2SFOS           () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "3L2SFOS"          , 5 , isyst ); }
        if ( passBTagVRSSEE        () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "BTagVRSSEE"       , 6 , isyst ); }
        if ( passBTagVRSSEM        () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "BTagVRSSEM"       , 7 , isyst ); }
        if ( passBTagVRSSMM        () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "BTagVRSSMM"       , 8 , isyst ); }
        if ( passBTagARSSEE        () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "BTagARSSEE"       , 9 , isyst ); }
        if ( passBTagARSSEM        () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "BTagARSSEM"       , 10, isyst ); }
        if ( passBTagARSSMM        () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "BTagARSSMM"       , 11, isyst ); }
        if ( passSSAREE            () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "SSAREE"           , 12, isyst ); }
        if ( passSSAREM            () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "SSAREM"           , 13, isyst ); }
        if ( passSSARMM            () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "SSARMM"           , 14, isyst ); }
        if ( passMjjSBVRSSEE       () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBVRSSEE"      , 15, isyst ); }
        if ( passMjjSBVRSSEM       () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBVRSSEM"      , 16, isyst ); }
        if ( passMjjSBVRSSMM       () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBVRSSMM"      , 17, isyst ); }
        if ( passMjjSBARSSEE       () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBARSSEE"      , 18, isyst ); }
        if ( passMjjSBARSSEM       () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBARSSEM"      , 19, isyst ); }
        if ( passMjjSBARSSMM       () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBARSSMM"      , 20, isyst ); }
        if ( passSSEEPred          () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "SSEEPred"         , 21, isyst ); }
        if ( passSSEMPred          () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "SSEMPred"         , 22, isyst ); }
        if ( passSSMMPred          () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "SSMMPred"         , 23, isyst ); }
        if ( passSSAREEPred        () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "SSAREEPred"       , 21, isyst ); }
        if ( passSSAREMPred        () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "SSAREMPred"       , 22, isyst ); }
        if ( passSSARMMPred        () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "SSARMMPred"       , 23, isyst ); }
        if ( passBTagVRSSEEPred    () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "BTagVRSSEEPred"   , 24, isyst ); }
        if ( passBTagVRSSEMPred    () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "BTagVRSSEMPred"   , 25, isyst ); }
        if ( passBTagVRSSMMPred    () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "BTagVRSSMMPred"   , 26, isyst ); }
        if ( passBTagARSSEEPred    () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "BTagARSSEEPred"   , 24, isyst ); }
        if ( passBTagARSSEMPred    () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "BTagARSSEMPred"   , 25, isyst ); }
        if ( passBTagARSSMMPred    () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "BTagARSSMMPred"   , 26, isyst ); }
        if ( passMjjSBVRSSEEPred   () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBVRSSEEPred"  , 27, isyst ); }
        if ( passMjjSBVRSSEMPred   () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBVRSSEMPred"  , 28, isyst ); }
        if ( passMjjSBVRSSMMPred   () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBVRSSMMPred"  , 29, isyst ); }
        if ( passMjjSBARSSEEPred   () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBARSSEEPred"  , 27, isyst ); }
        if ( passMjjSBARSSEMPred   () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBARSSEMPred"  , 28, isyst ); }
        if ( passMjjSBARSSMMPred   () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBARSSMMPred"  , 29, isyst ); }
        if ( passMjjSBPRVRSSEE     () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBPRVRSSEE"    , 30, isyst ); }
        if ( passMjjSBPRVRSSEM     () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBPRVRSSEM"    , 31, isyst ); }
        if ( passMjjSBPRVRSSMM     () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBPRVRSSMM"    , 32, isyst ); }
        if ( passMjjSBPRARSSEE     () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBPRARSSEE"    , 33, isyst ); }
        if ( passMjjSBPRARSSEM     () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBPRARSSEM"    , 34, isyst ); }
        if ( passMjjSBPRARSSMM     () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBPRARSSMM"    , 35, isyst ); }
        if ( passMjjSBPRVRSSEEPred () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBPRVRSSEEPred", 36, isyst ); }
        if ( passMjjSBPRVRSSEMPred () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBPRVRSSEMPred", 37, isyst ); }
        if ( passMjjSBPRVRSSMMPred () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBPRVRSSMMPred", 38, isyst ); }
        if ( passMjjSBPRARSSEEPred () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBPRARSSEEPred", 36, isyst ); }
        if ( passMjjSBPRARSSEMPred () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBPRARSSEMPred", 37, isyst ); }
        if ( passMjjSBPRARSSMMPred () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "MjjSBPRARSSMMPred", 38, isyst ); }
        if ( passPRVRSSEE          () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "PRVRSSEE"         , 39, isyst ); }
        if ( passPRVRSSEM          () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "PRVRSSEM"         , 40, isyst ); }
        if ( passPRVRSSMM          () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "PRVRSSMM"         , 41, isyst ); }
        if ( passPRARSSEE          () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "PRARSSEE"         , 42, isyst ); }
        if ( passPRARSSEM          () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "PRARSSEM"         , 43, isyst ); }
        if ( passPRARSSMM          () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "PRARSSMM"         , 44, isyst ); }
        if ( passPRVRSSEEPred      () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "PRVRSSEEPred"     , 45, isyst ); }
        if ( passPRVRSSEMPred      () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "PRVRSSEMPred"     , 46, isyst ); }
        if ( passPRVRSSMMPred      () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "PRVRSSMMPred"     , 47, isyst ); }
        if ( passPRARSSEEPred      () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "PRARSSEEPred"     , 45, isyst ); }
        if ( passPRARSSEMPred      () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "PRARSSEMPred"     , 46, isyst ); }
        if ( passPRARSSMMPred      () ) { passed = true; if ( !doskim ) fillHistograms ( hists, "PRARSSMMPred"     , 47, isyst ); }
    }
    return passed;
}

//=================================================================================================
//=================================================================================================
//=================================================================================================

//_________________________________________________________________________________________________
void fillHistograms( RooUtil::AutoHist& hists, TString prefix, int regionid, int isyst )
{

    // Print event lists
    if ( wwwbaby.isData() )
        printevent( prefix );

    // Sample categories (e.g. Z, DY.. or fake, trueSS etc.)
    int sample_priority = -1;
    TString sample_category = sampleCategory( sample_priority );
    TString bkg_category = bkgCategory();
    TString empty = "";

    // If it's for a prediction the data category is replaced by "fakepred"
    if ( wwwbaby.isData() && prefix.Contains( "AR" ) && prefix.Contains( "Pred" ) )
    {
        sample_category = "fakepred";
        bkg_category = "fakepred";
    }

    // Fill histograms for the MC boundary plots
    fillHistogramsFull( hists, sample_category, empty, prefix, regionid, isyst );

    // Fill histograms for the bkg type boundary plots
    if ( sample_priority == 1 )
        fillHistogramsFull( hists, empty, bkg_category, prefix, regionid, isyst );

    // The following fill will only occur for counter categories
    fillHistogramsFull( hists, sample_category, bkg_category, prefix, regionid, isyst );
}

//_________________________________________________________________________________________________
void fillHistogramsFull(
        RooUtil::AutoHist& hists,
        TString sample_category,
        TString bkg_category,
        TString prefix,
        int regionid,
        int isyst )
{
    // Compute a boolean whether to use fakefactor or not.
    bool ff = prefix.Contains( "Pred" ) && prefix.Contains( "AR" );

    // Generally the format is something like "ttX__" or "_trueSS_"
    TString procprefix = sample_category + "_" + bkg_category;

    // The fake prediction will be applied to the appropriate region.
    if ( wwwbaby.isData() && prefix.Contains( "AR" ) && prefix.Contains( "Pred" ) )
    {
        if ( prefix.Contains( "SSAR" ) ) prefix.ReplaceAll( "AR", "" );
        if ( prefix.Contains( "ARSS" ) ) prefix.ReplaceAll( "AR", "VR" );
    }

    // The counter plots are split by lepton flavors
    std::vector<TString> binlabels = { "ee", "e#mu", "#mu#mu" };
    double wgt = weight( ff, isyst );

    hists.fill( regionid     , isyst, Form( "%s_SS_counter"              , procprefix.Data() ), wgt, 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid     , isyst, Form( "%s_SS_rawcounter"           , procprefix.Data() ), 1  , 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 3 , isyst, Form( "%s_3L_counter"              , procprefix.Data() ), wgt, 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 3 , isyst, Form( "%s_3L_rawcounter"           , procprefix.Data() ), 1  , 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 6 , isyst, Form( "%s_BTagVRSS_counter"        , procprefix.Data() ), wgt, 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 6 , isyst, Form( "%s_BTagVRSS_rawcounter"     , procprefix.Data() ), 1  , 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 9 , isyst, Form( "%s_BTagARSS_counter"        , procprefix.Data() ), wgt, 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 9 , isyst, Form( "%s_BTagARSS_rawcounter"     , procprefix.Data() ), 1  , 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 12, isyst, Form( "%s_ARSS_counter"            , procprefix.Data() ), wgt, 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 12, isyst, Form( "%s_ARSS_rawcounter"         , procprefix.Data() ), 1  , 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 15, isyst, Form( "%s_MjjSBVRSS_counter"       , procprefix.Data() ), wgt, 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 15, isyst, Form( "%s_MjjSBVRSS_rawcounter"    , procprefix.Data() ), 1  , 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 18, isyst, Form( "%s_MjjSBARSS_counter"       , procprefix.Data() ), wgt, 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 18, isyst, Form( "%s_MjjSBARSS_rawcounter"    , procprefix.Data() ), 1  , 3, 0, 3, NSYST, 0, NSYST, binlabels );

    hists.fill( regionid - 21, isyst, Form( "%s_SSPred_counter"          , procprefix.Data() ), wgt, 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 21, isyst, Form( "%s_SSPred_rawcounter"       , procprefix.Data() ), 1  , 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 24, isyst, Form( "%s_BTagVRSSPred_counter"    , procprefix.Data() ), wgt, 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 24, isyst, Form( "%s_BTagVRSSPred_rawcounter" , procprefix.Data() ), 1  , 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 27, isyst, Form( "%s_MjjSBVRSSPred_counter"   , procprefix.Data() ), wgt, 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 27, isyst, Form( "%s_MjjSBVRSSPred_rawcounter", procprefix.Data() ), 1  , 3, 0, 3, NSYST, 0, NSYST, binlabels );

    hists.fill( regionid - 30, isyst, Form( "%s_MjjSBPRVRSS_counter"       , procprefix.Data() ), wgt, 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 30, isyst, Form( "%s_MjjSBPRVRSS_rawcounter"    , procprefix.Data() ), 1  , 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 33, isyst, Form( "%s_MjjSBPRARSS_counter"       , procprefix.Data() ), wgt, 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 33, isyst, Form( "%s_MjjSBPRARSS_rawcounter"    , procprefix.Data() ), 1  , 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 36, isyst, Form( "%s_MjjSBPRVRSSPred_counter"   , procprefix.Data() ), wgt, 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 36, isyst, Form( "%s_MjjSBPRVRSSPred_rawcounter", procprefix.Data() ), 1  , 3, 0, 3, NSYST, 0, NSYST, binlabels );

    hists.fill( regionid - 39, isyst, Form( "%s_PRVRSS_counter"              , procprefix.Data() ), wgt, 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 39, isyst, Form( "%s_PRVRSS_rawcounter"           , procprefix.Data() ), 1  , 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 42, isyst, Form( "%s_PRARSS_counter"              , procprefix.Data() ), wgt, 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 42, isyst, Form( "%s_PRARSS_rawcounter"           , procprefix.Data() ), 1  , 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 45, isyst, Form( "%s_PRVRSSPred_counter"          , procprefix.Data() ), wgt, 3, 0, 3, NSYST, 0, NSYST, binlabels );
    hists.fill( regionid - 45, isyst, Form( "%s_PRVRSSPred_rawcounter"       , procprefix.Data() ), 1  , 3, 0, 3, NSYST, 0, NSYST, binlabels );

//    if ( regionid >= 42 && regionid <= 44 )
//    {
//        int flav = 0;
//        if ( abs( wwwbaby.lep_pdgId()[lepidx["LbntLepton"][0]] ) == 11 ) flav = 0;
//        if ( abs( wwwbaby.lep_pdgId()[lepidx["LbntLepton"][0]] ) == 13 ) flav = 1;
//        hists.fill( flav, isyst, Form( "%s_PRARSS_closure_counter"              , procprefix.Data() ), wgt, 2, 0, 2, NSYST, 0, NSYST, {"Lbnt e", "Lbnt #mu"} );
//        hists.fill( flav, isyst, Form( "%s_PRARSS_closure_rawcounter"           , procprefix.Data() ), 1  , 2, 0, 2, NSYST, 0, NSYST, {"Lbnt e", "Lbnt #mu"} );
//    }
//
//    if ( regionid >= 39 && regionid <= 41 )
//    {
//        int flav = 0;
//        if      ( wwwbaby.lep_isFromW()[lepidx["TightLepton"][0]] == 0 ) flav = abs( wwwbaby.lep_pdgId()[lepidx["TightLepton"][0]] ) == 11 ? 0 : 1;
//        else if ( wwwbaby.lep_isFromW()[lepidx["TightLepton"][1]] == 0 ) flav = abs( wwwbaby.lep_pdgId()[lepidx["TightLepton"][1]] ) == 11 ? 0 : 1;
//        hists.fill( flav, isyst, Form( "%s_PRVRSS_closure_counter"              , procprefix.Data() ), wgt, 2, 0, 2, NSYST, 0, NSYST, {"Lbnt e", "Lbnt #mu"} );
//        hists.fill( flav, isyst, Form( "%s_PRVRSS_closure_rawcounter"           , procprefix.Data() ), 1  , 2, 0, 2, NSYST, 0, NSYST, {"Lbnt e", "Lbnt #mu"} );
//    }

    // Check whether the beginning or the ending of the procprefix has "_"
    if ( !procprefix.BeginsWith( "_" ) && !procprefix.EndsWith( "_" ) )
        return;

    TString fullprefix = sample_category + "_" + bkg_category + "_" + prefix + "_";
    fillLepHistograms( hists, "LooseLepton"  , "loose" , fullprefix, isyst );
    fillJetHistograms( hists, "GoodSSJet"    , ""      , fullprefix, isyst );
    fillJetHistograms( hists, "LooseBJet"    , "b"     , fullprefix, isyst );
    fillJetHistograms( hists, "Good3LJet"    , "3l"    , fullprefix, isyst );
    fillJetHistograms( hists, "GoodSSWJet"   , "wtag"  , fullprefix, isyst );
    fillWWWHistograms( hists, fullprefix, isyst );

}

