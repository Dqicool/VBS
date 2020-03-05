#include "/mnt/SSD/VBS/rivet_routine/Src/CutPart.hh"

namespace Rivet {


	/// @brief Just measures a few observables as a demo
	class qidong : public Analysis {
	public:

    /// Constructor
    DEFAULT_RIVET_ANALYSIS_CTOR(qidong);


	/// @name Analysis methods
	//@{

	/// Set up projections and book histograms
	void init() {
		// Projections
		const FinalState fs(Cuts::abseta < 4.5 && Cuts::pT > 500*MeV);
		declare(ChargedFinalState(Cuts::abseta <= 2.7 && (Cuts::abspid == 11 || Cuts::abspid == 13)), "leptons");
		declare(FastJets(fs, FastJets::ANTIKT, 0.4), "Jets");

		// Histograms
		_histJN         = bookHisto1D("Jets_Number", 20, -0.5, 19.5);
		_histLN         = bookHisto1D("lep_Number", 20, -0.5, 19.5);
		_histLN_PASS    = bookHisto1D("lep_Number_PASS", 20, -0.5, 19.5);
		_histJN_PASS    = bookHisto1D("jet_Number_PASS", 20, -0.5, 19.5);
		_histJ1_pt    = bookHisto1D("jet_j1_pt", 300, 0, 300);
		_histJ2_pt    = bookHisto1D("jet_j2_pt", 300, 0, 300);
		_histZ1_m		= bookHisto1D("Z1_m", 300, 0, 300);
		_histZ2_m		= bookHisto1D("Z2_m", 300, 0, 300);
		_hist_M4l		= bookHisto1D("m4l", 100, 0, 1000);
		_hist_Mjj		= bookHisto1D("mjj", 100, 0, 2000);
		_hist_Dphijj	= bookHisto1D("jjDphi", 200, -M_PI, M_PI);
		_hist_xs		= bookHisto1D("xs", 1, -1, 1);
	}

    // Do the analysis
    void analyze(const Event& event) {
		//Finding Weight, jets, and leptons
		const double weight = event.weight();
		const Jets jets = apply<FastJets>(event, "Jets").jets();
		const Particles leps = apply<ChargedFinalState>(event, "leptons").particles();
		//analyse
		Particles pass_leps = lepSel(leps);
		if	(pass_leps.size() < 4) vetoEvent;

		FourMomenta pass_jets = jetSel(jets);
		if	(pass_jets.size() < 2) vetoEvent;

		FourMomenta j1j2 = getJ1J2(pass_jets);
		if	(j1j2.size() < 2 || 
			(j1j2[0] + j1j2[1]).mass() < 200*GeV || 
			std::abs(j1j2[0].rapidity() - j1j2[1].rapidity()) < 2) vetoEvent;

		std::vector<std::vector<Particles>> lep_pairs_comb = getLeptonPairsComb(leps);
		FourMomenta Z1Z2 = getZ1Z2(lep_pairs_comb);
		if	(Z1Z2.size() < 2 ||
			Z1Z2[0].mass() < 70*GeV ||  Z1Z2[0].mass() > 110*GeV || 
			Z1Z2[1].mass() < 21.1876*GeV ||  Z1Z2[1].mass() > 110*GeV) vetoEvent;

		if	(getPtBala(j1j2, Z1Z2) > 0.5) vetoEvent;

		//find weights

		//fill histos
		_histJN->fill(jets.size(), weight);
		_histLN->fill(leps.size(), weight);
		_histLN_PASS->fill(pass_leps.size(), weight);
		_histJN_PASS->fill(pass_jets.size(), weight);
		_histJ1_pt->fill(j1j2[0].pt(), weight);
		_histJ2_pt->fill(j1j2[1].pt(), weight);
		_histZ1_m->fill(Z1Z2[0].mass(), weight);
		_histZ2_m->fill(Z1Z2[1].mass(), weight);
		_hist_M4l->fill((Z1Z2[0] + Z1Z2[1]).mass(), weight);
		_hist_Mjj->fill((j1j2[0] + j1j2[1]).mass(), weight);
		_hist_Dphijj->fill(getJJDelPhi(j1j2), weight);
		_hist_xs->fill(0, weight);
	}

    /// Finalize
	void finalize(){
		scale(_hist_M4l, crossSection() * 1000 / sumOfWeights());
		scale(_hist_Mjj, crossSection() * 1000 / sumOfWeights());
		scale(_hist_Dphijj, crossSection() * 1000 / sumOfWeights());
		scale(_hist_xs, crossSection() * 1000 / sumOfWeights());
	}

    /// Histograms
    Histo1DPtr _histJN, _histLN, _histLN_PASS, _histJN_PASS, _histJ1_pt, _histJ2_pt, _histZ1_m, _histZ2_m,_hist_M4l, _hist_Mjj, _hist_Dphijj, _hist_xs;
    //@}

  	};


  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(qidong);

}
