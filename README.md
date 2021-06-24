# JetToTauFR

Measurement of jet->tauh fake rate for the haabbtt analysis

- Measured in Z->mumu + jets data events, where simulated diboson events are subtracted to avoid events with real tauh
- Run the skimming files in the skim branch to process the data and diboson samples in the mu+mu+tauh final state
- Run the FinalSelection_mmt code to make numerator and denominator histograms with different tauID WP
- Run CreateFRhist.py to subtract simulated diboson from data
- Run root -l -b -q "FitFakeRateTau.cc(${year})" to do histogram division and fake rate fitting
