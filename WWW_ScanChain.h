//  .
// ..: P. Chang, philip@physics.ucsd.edu

#include <algorithm>

// RooUtil tool
#include "rooutil/looper.h"
#include "rooutil/autohist.h"
#include "rooutil/eventlist.h"
#include "rooutil/ttreex.h"
#include "rooutil/dorky.h"
#include "WWW_CORE/WWWTree.h"
#include "WWW_CORE/WWWTools.h"


using namespace std;
using namespace RooUtil;
using namespace www;

void ScanChain(TChain* chain, TString output_name, TString optstr, int nevents = -1);

#include "analysis.C"
