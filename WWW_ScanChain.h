//  .
// ..: P. Chang, philip@physics.ucsd.edu

#include <algorithm>

// RooUtil tool
#include "rooutil/looper.h"
#include "rooutil/autohist.h"
#include "rooutil/eventlist.h"
#include "rooutil/ttreex.h"
#include "WWW_CORE/WWWTree.h"
#include "WWW_CORE/WWWTools.h"

#include "CORE/Tools/dorky/dorky.h"

using namespace std;
using namespace RooUtil;

#define MAXOBJ 3
#define NSYST 3

void ScanChain( TChain* chain, TString output_name, TString optstr, int nevents = -1 ); // the default nevents=-1 option means loop over all events.

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
