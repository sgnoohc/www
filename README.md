# WWW analysis code

# First time installing

    git clone --recursive git@github.com:sgnoohc/www.git
    cd www/
    source scripts/setup.sh
    cd CORE; make -j20; cd ..;
    cd WWW_CORE; make -j20; cd ..;
    cd rooutil; make -j20; cd ..;

# Second time

    source scripts/setup.sh

# To further skim VVV baby ntuples to a smaller size. (output TTree root files.)

    run.sh -c WWW_ScanChain.C output.root t -1 doskim /hadoop/cms/store/user/bhashemi/AutoTwopler_babies/merged/VVV/WWW_v0.1.16/skim/www_2l_ext1_mia_skim_1.root
                                               ^^^^^^
                                               keyword

# To run the analysis code on the VVV baby ntuple directly. (outputs histograms.)

    run.sh -c WWW_ScanChain.C output.root t -1 v0.1.16 /hadoop/cms/store/user/bhashemi/AutoTwopler_babies/merged/VVV/WWW_v0.1.16/skim/www_2l_ext1_mia_skim_1.root
                                               ^^^^^^^
                                               Provide the version

# To run over ALL ntuples

    run.sh -c WWW_ScanChain.C output.root t -1 v0.1.16 '/hadoop/cms/store/user/bhashemi/AutoTwopler_babies/merged/VVV/WWW_v0.1.16/skim/*.root'
                                               ^^^^^^^
                                               Provide the version
