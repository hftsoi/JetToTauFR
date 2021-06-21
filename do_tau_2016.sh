./Make.sh FinalSelection_mmt.cc
./FinalSelection_mmt.exe /hdfs/store/user/htsoi/frwhmmt2016_17dec/data_obs.root files_mmt_2016/data_obs.root data_obs data_obs 0 2016
./FinalSelection_mmt.exe /hdfs/store/user/htsoi/frwhmmt2016_17dec/WZ3LNu.root files_mmt_2016/WZ3LNu.root WZ3LNu VV 0 2016
./FinalSelection_mmt.exe /hdfs/store/user/htsoi/frwhmmt2016_17dec/ZZ4L.root files_mmt_2016/ZZ4L.root ZZ4L VV 0 2016
hadd -f files_mmt_2016/VV.root files_mmt_2016/ZZ4L.root files_mmt_2016/WZ3LNu.root
python CreateFRhist.py --year 2016
root -l -b -q "FitFakeRateTau.cc(2016)"
