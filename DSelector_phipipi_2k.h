#ifndef DSelector_phipipi_2k_h
#define DSelector_phipipi_2k_h

#include <iostream>

#include "DSelector/DSelector.h"
#include "DSelector/DHistogramActions.h"
#include "DSelector/DCutActions.h"

#include "TH1I.h"
#include "TH2I.h"
#include "TF1.h"
//Nian
class DSelector_phipipi_2k : public DSelector
{
	public:

		DSelector_phipipi_2k(TTree* locTree = NULL) : DSelector(locTree){}
		virtual ~DSelector_phipipi_2k(){}

		void Init(TTree *tree);
		Bool_t Process(Long64_t entry);

	private:

		void Get_ComboWrappers(void);
		void Finalize(void);

		// ChiSqOrCL cut parameters  (added by Ting, 10/08/2018)
		double dSlope;
		double dYint;


		//CREATE REACTION-SPECIFIC PARTICLE ARRAYS

		//Step 0
		DParticleComboStep* dStep0Wrapper;
		DBeamParticle* dComboBeamWrapper;
		DChargedTrackHypothesis* dPiPlusWrapper;
		DChargedTrackHypothesis* dPiMinusWrapper;
		DChargedTrackHypothesis* dKPlusWrapper;
		DChargedTrackHypothesis* dKMinusWrapper;
		DChargedTrackHypothesis* dProtonWrapper;

		// DEFINE YOUR HISTOGRAM ACTIONS HERE
		// EXAMPLE HISTOGRAM ACTIONS:
		DHistogramAction_ParticleComboKinematics* dHistComboKinematics;
		DHistogramAction_ParticleComboKinematics* dHistComboKinematics_final;
		DHistogramAction_ParticleID *dHistComboPID, *dHistComboPID_KinFit;
		DHistogramAction_ParticleID *dHistComboPID_final;
		// EXAMPLE CUT ACTIONS:
		DCutAction_PIDDeltaT* dCutPIDDeltaT;

		// DEFINE YOUR HISTOGRAMS HERE
		// EXAMPLES:
		TH1I* dHist_MissingMassSquared;
		TH1I* dHist_BeamEnergy;

		TH1I* dHist_MissingEnergy;

		int nCheck_PhiPiPiCut;

		TH1I* dHist_KinFitChiSq;
		TH1I* dHist_KinFitCL;
		TH2I* dHist_Proton_dEdx_P_before;
		TH2I* dHist_Proton_dEdx_P;
		TH2I* dHist_KPlus_dEdx_P;
		TH2I* dHist_KMinus_dEdx_P;
		TH2I* dHist_PiPlus_dEdx_P;
		TH2I* dHist_PiMinus_dEdx_P;
		TH2I* dHist_Proton_dEdx_P_Measured;
		TH2I* dHist_KPlus_dEdx_P_Measured;
		TH2I* dHist_KMinus_dEdx_P_Measured;
		TH2I* dHist_PiPlus_dEdx_P_Measured;
		TH2I* dHist_PiMinus_dEdx_P_Measured;
		TH2I* dHist_Proton_dEdx_P_PhiPiPiCut;
		TH2I* dHist_KPlus_dEdx_P_PhiPiPiCut;
		TH2I* dHist_KMinus_dEdx_P_PhiPiPiCut;
		TH2I* dHist_PiPlus_dEdx_P_PhiPiPiCut;
		TH2I* dHist_PiMinus_dEdx_P_PhiPiPiCut;
		TH2I* dHist_Proton_Theta_P_PhiPiPiCut;
		TH2I* dHist_KPlus_Theta_P_PhiPiPiCut;
		TH2I* dHist_KMinus_Theta_P_PhiPiPiCut;
		TH2I* dHist_PiPlus_Theta_P_PhiPiPiCut;
		TH2I* dHist_PiMinus_Theta_P_PhiPiPiCut;
		TH2I* dHist_Proton_dEdx_P_PhiPiPiCut_Measured;
		TH2I* dHist_KPlus_dEdx_P_PhiPiPiCut_Measured;
		TH2I* dHist_KMinus_dEdx_P_PhiPiPiCut_Measured;
		TH2I* dHist_PiPlus_dEdx_P_PhiPiPiCut_Measured;
		TH2I* dHist_PiMinus_dEdx_P_PhiPiPiCut_Measured;
		TH2I* dHist_Proton_Theta_P_PhiPiPiCut_Measured;
		TH2I* dHist_KPlus_Theta_P_PhiPiPiCut_Measured;
		TH2I* dHist_KMinus_Theta_P_PhiPiPiCut_Measured;
		TH2I* dHist_PiPlus_Theta_P_PhiPiPiCut_Measured;
		TH2I* dHist_PiMinus_Theta_P_PhiPiPiCut_Measured;
		
		TH1I* dHist_Proton_KPlus_Angle;
		TH1I* dHist_Proton_KMinus_Angle;
		TH1I* dHist_Proton_PiPlus_Angle;
		TH1I* dHist_Proton_PiMinus_Angle;
		TH1I* dHist_KPlus_KMinus_Angle;
		TH1I* dHist_KPlus_PiPlus_Angle;
		TH1I* dHist_KPlus_PiMinus_Angle;
		TH1I* dHist_KMinus_PiPlus_Angle;
		TH1I* dHist_KMinus_PiMinus_Angle;
		TH1I* dHist_PiPlus_PiMinus_Angle;

		TH1I* dHist_Proton_P_PhiPiPiCut;
		TH1I* dHist_KPlus_P_PhiPiPiCut;
		TH1I* dHist_KMinus_P_PhiPiPiCut;
		TH1I* dHist_PiPlus_P_PhiPiPiCut;
		TH1I* dHist_PiMinus_P_PhiPiPiCut;

		TH1I* dHist_Proton_Theta_PhiPiPiCut;
		TH1I* dHist_KPlus_Theta_PhiPiPiCut;
		TH1I* dHist_KMinus_Theta_PhiPiPiCut;
		TH1I* dHist_PiPlus_Theta_PhiPiPiCut;
		TH1I* dHist_PiMinus_Theta_PhiPiPiCut;

		TH1I* dHist_Proton_DeltaT_BCAL_PhiPiPiCut;
		TH1I* dHist_KPlus_DeltaT_BCAL_PhiPiPiCut;
		TH1I* dHist_KMinus_DeltaT_BCAL_PhiPiPiCut;
		TH1I* dHist_PiPlus_DeltaT_BCAL_PhiPiPiCut;
		TH1I* dHist_PiMinus_DeltaT_BCAL_PhiPiPiCut;
		TH1I* dHist_Proton_DeltaT_TOF_PhiPiPiCut;
		TH1I* dHist_KPlus_DeltaT_TOF_PhiPiPiCut;
		TH1I* dHist_KMinus_DeltaT_TOF_PhiPiPiCut;
		TH1I* dHist_PiPlus_DeltaT_TOF_PhiPiPiCut;
		TH1I* dHist_PiMinus_DeltaT_TOF_PhiPiPiCut;

		TH2I* dHist_Proton_P_vs_Beta_BCAL_PhiPiPiCut;
		TH2I* dHist_KPlus_P_vs_Beta_BCAL_PhiPiPiCut;
		TH2I* dHist_KMinus_P_vs_Beta_BCAL_PhiPiPiCut;
		TH2I* dHist_PiPlus_P_vs_Beta_BCAL_PhiPiPiCut;
		TH2I* dHist_PiMinus_P_vs_Beta_BCAL_PhiPiPiCut;
		TH2I* dHist_Proton_P_vs_DeltaT_BCAL_PhiPiPiCut;
		TH2I* dHist_KPlus_P_vs_DeltaT_BCAL_PhiPiPiCut;
		TH2I* dHist_KMinus_P_vs_DeltaT_BCAL_PhiPiPiCut;
		TH2I* dHist_PiPlus_P_vs_DeltaT_BCAL_PhiPiPiCut;
		TH2I* dHist_PiMinus_P_vs_DeltaT_BCAL_PhiPiPiCut;

		TH1I* dHist_Proton_Beta_BCAL_PhiPiPiCut;
		TH1I* dHist_KPlus_Beta_BCAL_PhiPiPiCut;
		TH1I* dHist_KMinus_Beta_BCAL_PhiPiPiCut;
		TH1I* dHist_PiPlus_Beta_BCAL_PhiPiPiCut;
		TH1I* dHist_PiMinus_Beta_BCAL_PhiPiPiCut;

		TH2I* dHist_Proton_P_vs_Beta_TOF_PhiPiPiCut;
		TH2I* dHist_KPlus_P_vs_Beta_TOF_PhiPiPiCut;
		TH2I* dHist_KMinus_P_vs_Beta_TOF_PhiPiPiCut;
		TH2I* dHist_PiPlus_P_vs_Beta_TOF_PhiPiPiCut;
		TH2I* dHist_PiMinus_P_vs_Beta_TOF_PhiPiPiCut;

		TH2I* dHist_Proton_P_vs_DeltaT_TOF_PhiPiPiCut;
		TH2I* dHist_KPlus_P_vs_DeltaT_TOF_PhiPiPiCut;
		TH2I* dHist_KMinus_P_vs_DeltaT_TOF_PhiPiPiCut;
		TH2I* dHist_PiPlus_P_vs_DeltaT_TOF_PhiPiPiCut;
		TH2I* dHist_PiMinus_P_vs_DeltaT_TOF_PhiPiPiCut;

		TH1I* dHist_Proton_Beta_TOF_PhiPiPiCut;
		TH1I* dHist_KPlus_Beta_TOF_PhiPiPiCut;
		TH1I* dHist_KMinus_Beta_TOF_PhiPiPiCut;
		TH1I* dHist_PiPlus_Beta_TOF_PhiPiPiCut;
		TH1I* dHist_PiMinus_Beta_TOF_PhiPiPiCut;

		TH1I* dHist_Proton_EP_BCAL;
		TH1I* dHist_KPlus_EP_BCAL;
		TH1I* dHist_KMinus_EP_BCAL;
		TH1I* dHist_PiPlus_EP_BCAL;
		TH1I* dHist_PiMinus_EP_BCAL;
		TH1I* dHist_Proton_EP_FCAL;
		TH1I* dHist_KPlus_EP_FCAL;
		TH1I* dHist_KMinus_EP_FCAL;
		TH1I* dHist_PiPlus_EP_FCAL;
		TH1I* dHist_PiMinus_EP_FCAL;

		TH1I* dHist_MissingEnergy_PhiPiPiCut;
		TH1I* dHist_MissingMass_PhiPiPiCut;
		TH1I* dHist_MissingMassSquared_PhiPiPiCut;
		TH1I* dHist_Energy_UnusedShowers_PhiPiPiCut;
		TH1I* dHist_KinFitCL_PhiPiPiCut;
		TH1I* dHist_BeamEnergy_PhiPiPiCut;

		TH2I* dHist_MPhiPiPi_vs_MProtonPiPlus_Measured;
		TH2I* dHist_MPhiPiPi_vs_MProtonPiMinus_Measured;
		TH2I* dHist_MPhiPiPi_vs_MPhiProton_Measured;
		TH2I* dHist_MPhiPiPi_vs_MPiPi_Measured;
		TH2I* dHist_MPhiPiPi_vs_MPhiPiPlus_Measured;
		TH2I* dHist_MPhiPiPi_vs_MPhiPiMinus_Measured;
		TH2I* dHist_MPhiPiPlus_vs_MPhiPiMinus_Measured;
		TH2I* dHist_MPhiPiPlus_vs_MPiPi_Measured;
		TH2I* dHist_MPhiPiMinus_vs_MPiPi_Measured;
		TH2I* dHist_MPhiPiPlus_vs_MKPlusPiMinus_Measured;
		TH2I* dHist_MPhiPiPlus_vs_MKMinusPiPlus_Measured;
		TH2I* dHist_MPhiPiMinus_vs_MKPlusPiMinus_Measured;
		TH2I* dHist_MPhiPiMinus_vs_MKMinusPiPlus_Measured;


		TH1I* dHist_Mphipipi;
		TH1I* dHist_Mphipipi_measured;
		TH1I* dHist_Mphi;
		TH1I* dHist_Mphi_measured;
		TH1I* dHist_Mphi_measured1;
		TH1I* dHist_Mphi_measured2;
		TH1I* dHist_Mphi_measured3;
		TH1I* dHist_Mphi_measured4;
		TH1I* dHist_Mphi_measured5;
		TH1I* dHist_Mphi_measured6;
		TH1I* dHist_Mphi_measured7;
		TH1I* dHist_Mphi_measured8;
		TH1I* dHist_Mphi_measured9;
		TH1I* dHist_Mphi_measured10;
		TH1I* dHist_Mphi_measured11;
		TH1I* dHist_Mphi_measured12;
		TH1I* dHist_Mphi_measured13;
		TH1I* dHist_Mphi_measured14;
		TH1I* dHist_Mphi_measured15;
		TH1I* dHist_Mphi_measured16;
		TH1I* dHist_Mphi_measured17;
		TH1I* dHist_Mphi_measured18;
		TH1I* dHist_Mphi_measured19;
		TH1I* dHist_Mphi_measured20;
		TH1I* dHist_Mphi_measured21;
		TH1I* dHist_Mphi_measured22;
		TH1I* dHist_Mphi_measured23;
		TH1I* dHist_Mphi_measured24;
		TH1I* dHist_Mphi_measured25;
		TH1I* dHist_Mphi_measured26;
		TH1I* dHist_Mphi_measured27;
		TH1I* dHist_Mphi_measured28;
		TH1I* dHist_Mphi_measured29;
		TH1I* dHist_Mphi_measured30;
		TH1I* dHist_Mphi_measured31;
		TH1I* dHist_Mphi_measured32;
		TH1I* dHist_Mphi_measured33;
		TH1I* dHist_Mphi_measured34;
		TH1I* dHist_Mphi_measured35;
		TH1I* dHist_Mphi_measured36;
		TH1I* dHist_Mphi_measured37;
		TH1I* dHist_Mphi_measured38;
		TH1I* dHist_Mphi_measured39;
		TH1I* dHist_Mphi_measured40;
		TH1I* dHist_Mphi_measured41;
		TH1I* dHist_Mphi_measured42;
		TH1I* dHist_Mphipip;
		TH1I* dHist_Mphipip_measured;
		TH1I* dHist_Mphipim;
		TH1I* dHist_Mphipim_measured;
		TH1I* dHist_Mpippim;
		TH1I* dHist_Mpippim_measured;
		TH1I* dHist_Mkst;
		TH1I* dHist_Mkst_measured;
		TH1I* dHist_Maks;
		TH1I* dHist_Maks_measured;
		TH2I* dHist_Mpip_Mpim_measured;

		TH1I* dHist_KPlus_DeltaT_BCAL;
		TH2I* dHist_KPlus_P_vs_DeltaT_BCAL;
		TH1I* dHist_KPlus_DeltaT_TOF;
		TH2I* dHist_KPlus_P_vs_DeltaT_TOF;

		TH1I* dHist_KMinus_DeltaT_BCAL;
		TH2I* dHist_KMinus_P_vs_DeltaT_BCAL;
		TH1I* dHist_KMinus_DeltaT_TOF;
		TH2I* dHist_KMinus_P_vs_DeltaT_TOF;


		TH1I* dHist_PiPlus_DeltaT_BCAL;
		TH2I* dHist_PiPlus_P_vs_DeltaT_BCAL;
		TH1I* dHist_PiPlus_DeltaT_TOF;
		TH2I* dHist_PiPlus_P_vs_DeltaT_TOF;

		TH1I* dHist_PiMinus_DeltaT_BCAL;
		TH2I* dHist_PiMinus_P_vs_DeltaT_BCAL;
		TH1I* dHist_PiMinus_DeltaT_TOF;
		TH2I* dHist_PiMinus_P_vs_DeltaT_TOF;

		TH1I* dHist_MProtonPiP_measured;
		TH1I* dHist_MProtonPiM_measured;


		TH1I* dHist_Proton_DeltaT_BCAL;
		TH2I* dHist_Proton_P_vs_DeltaT_BCAL;
		TH1I* dHist_Proton_DeltaT_TOF;
		TH2I* dHist_Proton_P_vs_DeltaT_TOF;

		TH1I* dHist_MphiProton_measured;

		TH1I* dHist_Proton_P;
		TH1I* dHist_Proton_Theta;

		TH1I* dHist_PiPlus_P;
		TH1I* dHist_PiPlus_Theta;
		TH1I* dHist_PiMinus_P;
		TH1I* dHist_PiMinus_Theta;
		TH1I* dHist_KPlus_P;
		TH1I* dHist_KPlus_Theta;
		TH1I* dHist_KMinus_P;
		TH1I* dHist_KMinus_Theta;



		TH2I* dHist_Proton_Theta_P;
		TH2I* dHist_kk_kkpipi;
		TH2I* dHist_ebeam_kkpipi;

		TF1* fMinProton_dEdx;

		TH1I* dHist_PiPlus_TrkChiSq;
		TH1I* dHist_PiMinus_TrkChiSq;
		TH1I* dHist_KPlus_TrkChiSq;
		TH1I* dHist_KMinus_TrkChiSq;
		TH1I* dHist_Proton_TrkChiSq;
		TH1I* dHist_Proton_ChiSq_Tracking;
		TH1I* dHist_KPlus_ChiSq_Tracking;
		TH1I* dHist_KMinus_ChiSq_Tracking;
		TH1I* dHist_PiPlus_ChiSq_Tracking;
		TH1I* dHist_PiMinus_ChiSq_Tracking;
		TH1I* dHist_Proton_NDF_Tracking;
		TH1I* dHist_KPlus_NDF_Tracking;
		TH1I* dHist_KMinus_NDF_Tracking;
		TH1I* dHist_PiPlus_NDF_Tracking;
		TH1I* dHist_PiMinus_NDF_Tracking;

		TH1I* dHist_combo;
		TH1I* dHist_KPlus_Beta_BCAL;
		TH2I* dHist_KPlus_P_vs_Beta_BCAL;
		TH1I* dHist_KPlus_Beta_TOF;
		TH2I* dHist_KPlus_P_vs_Beta_TOF;

		TH1I* dHist_KMinus_Beta_BCAL;
		TH2I* dHist_KMinus_P_vs_Beta_BCAL;
		TH1I* dHist_KMinus_Beta_TOF;
		TH2I* dHist_KMinus_P_vs_Beta_TOF;

		TH1I* dHist_Proton_Beta_BCAL;
		TH2I* dHist_Proton_P_vs_Beta_BCAL;
		TH1I* dHist_Proton_Beta_TOF;
		TH2I* dHist_Proton_P_vs_Beta_TOF;

		TH1I* dHist_PiPlus_Beta_BCAL;
		TH2I* dHist_PiPlus_P_vs_Beta_BCAL;
		TH1I* dHist_PiPlus_Beta_TOF;
		TH2I* dHist_PiPlus_P_vs_Beta_TOF;

		TH1I* dHist_PiMinus_Beta_BCAL;
		TH2I* dHist_PiMinus_P_vs_Beta_BCAL;
		TH1I* dHist_PiMinus_Beta_TOF;
		TH2I* dHist_PiMinus_P_vs_Beta_TOF;



	ClassDef(DSelector_phipipi_2k, 0);
};

void DSelector_phipipi_2k::Get_ComboWrappers(void)
{
	//Step 0
	dStep0Wrapper = dComboWrapper->Get_ParticleComboStep(0);
	dComboBeamWrapper = static_cast<DBeamParticle*>(dStep0Wrapper->Get_InitialParticle());
	dPiPlusWrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(0));
	dPiMinusWrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(1));
	dKPlusWrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(2));
	dKMinusWrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(3));
	dProtonWrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(4));
}

#endif // DSelector_phipipi_2k_h
