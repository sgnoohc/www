run.sh -c WWW_ScanChain.C output.root t -1 dosync /nfs-7/userdata/bhashemi/WWW_babies/WWW_v0.1.16/skim/www_2l_ext1_mia_skim_1.root | tee eventlists/www.log
run.sh -c WWW_ScanChain.C output.root t -1 dosync '/nfs-7/userdata/bhashemi/WWW_babies/WWW_v0.1.16/skim/ttbar_1ltop_mgmlm_ext1*.root' | tee eventlists/tt1l.log
run.sh -c WWW_ScanChain.C output.root t -1 dosync '/nfs-7/userdata/bhashemi/WWW_babies/WWW_v0.1.16/skim/wz_3l*.root' | tee eventlists/wz.log
run.sh -c WWW_ScanChain.C output.root t -1 dosync '/nfs-7/userdata/bhashemi/WWW_babies/WWW_v0.1.16/skim/data*.root' | tee eventlists/data.log
#run.sh -c WWW_ScanChain.C output.root t -1 dosync /home/users/phchang/public_html/analysis/www/code/www/WWW_v0_1_16_v16_skim.root | tee eventlists/data.log
cd eventlists/
python parse.py
cd ../ # in case some users initate command via "source", which i think is not the kosher bash way... but OK. whatever....
