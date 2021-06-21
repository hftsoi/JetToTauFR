./Make.sh FinalSelection_mmt.cc
./FinalSelection_mmt.exe /hdfs/store/user/htsoi/frwhmmt2018_17dec/data_obs.root files_mmt_2018/data_obs.root data_obs data_obs 0 2018
./FinalSelection_mmt.exe /hdfs/store/user/htsoi/frwhmmt2018_17dec/WZ3LNu.root files_mmt_2018/WZ3LNu.root WZ3LNu VV 0 2018
./FinalSelection_mmt.exe /hdfs/store/user/htsoi/frwhmmt2018_17dec/ZZ4L.root files_mmt_2018/ZZ4L.root ZZ4L VV 0 2018
hadd -f files_mmt_2018/VV.root files_mmt_2018/ZZ4L.root files_mmt_2018/WZ3LNu.root
python CreateFRhist.py --year 2018
root -l -b -q "FitFakeRateTau.cc(2018)"
