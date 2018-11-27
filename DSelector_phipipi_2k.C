#include "DSelector_phipipi_2k.h"
//Nian modified on 2018.07.27
void DSelector_phipipi_2k::Init(TTree *locTree)
{
	// The Init() function is called when the selector needs to initialize a new tree or chain.
	// Typically here the branch addresses and branch pointers of the tree will be set.
	// Init() will be called many times when running on PROOF (once per file to be processed).

	//SET OUTPUT FILE NAME //can be overriden by user in PROOF
	dOutputFileName = "my2k2pi.root"; //"" for none
	dOutputTreeFileName = ""; //"" for none

	//DO THIS NEXT
	//Because this function gets called for each TTree in the TChain, we must be careful:
		//We need to re-initialize the tree interface & branch wrappers, but don't want to recreate histograms
	bool locInitializedPriorFlag = dInitializedFlag; //save whether have been initialized previously
	DSelector::Init(locTree); //This must be called to initialize wrappers for each new TTree
	//gDirectory now points to the output file with name dOutputFileName (if any)
	if(locInitializedPriorFlag)
		return; //have already created histograms, etc. below: exit

	//THEN THIS
	Get_ComboWrappers();

	/******************************************** EXAMPLE USER INITIALIZATION *******************************************/

	//DO WHATEVER YOU WANT HERE

	//EXAMPLE HISTOGRAM ACTIONS:
	dHistComboKinematics = new DHistogramAction_ParticleComboKinematics(dComboWrapper, false); //false: use measured data
	dHistComboPID = new DHistogramAction_ParticleID(dComboWrapper, false); //false: use measured data
	dHistComboPID_KinFit = new DHistogramAction_ParticleID(dComboWrapper, true, "KinFit"); //true: use kinfit data

	//change binning here
	//dHistComboKinematics->Initialize();
	//dHistComboPID->Initialize();
	//dHistComboPID_KinFit->Initialize();

	//EXAMPLE CUT ACTIONS:
	//below: false: measured data, value: +/- N ns, Unknown: All PIDs, SYS_NULL: all timing systems
	dCutPIDDeltaT = new DCutAction_PIDDeltaT(dComboWrapper, false, 2.0, Unknown, SYS_NULL);
	dCutPIDDeltaT->Initialize();

	//EXAMPLE MANUAL HISTOGRAMS:
	//dHist_MissingEnergy = new TH1I("MissingEnergy", ";Missing Energy GeV", 100, -1., 1.);
	//dHist_MissingMassSquared = new TH1I("MissingMassSquared", ";Missing Mass Squared (GeV/c^{2})^{2}", 600, -0.06, 0.06);
	dHist_MissingEnergy = new TH1I("MissingEnergy", ";Missing Energy GeV", 400, -4., 4.);
	dHist_MissingMassSquared = new TH1I("MissingMassSquared", ";Missing Mass Squared (GeV/c^{2})^{2}", 1200, -0.12, 0.12);
	dHist_BeamEnergy = new TH1I("BeamEnergy", ";Beam Energy (GeV)", 600, 0.0, 12.0);

	dHist_KinFitChiSq = new TH1I("KinFitChiSq", ";Kinematic Fit ChiSq", 200, 0., 100);
	dHist_KinFitCL = new TH1I("KinFitCL", ";Kinematic Fit Confidence Level", 10000, 0., 1.0);
	dHist_Proton_dEdx_P_before = new TH2I("Proton_dEdx_P_before", " ;p_{proton} GeV/c; dE/dx (keV/cm)", 250, 0.0, 5.0, 250, 0.0, 25.);
	dHist_Proton_dEdx_P = new TH2I("Proton_dEdx_P", " ;p_{proton} GeV/c; dE/dx (keV/cm)", 250, 0.0, 5.0, 250, 0.0, 25.);
	dHist_KPlus_dEdx_P  = new TH2I("KPlus_dEdx_P", " ;p_{KPlus} GeV/c; dE/dx (keV/cm)", 300, 0.0, 6.0, 250, 0.0, 5.);
	dHist_KMinus_dEdx_P  = new TH2I("KMinus_dEdx_P", " ;p_{KMinus} GeV/c; dE/dx (keV/cm)", 300, 0.0, 6.0, 250, 0.0, 5.);
	dHist_PiPlus_dEdx_P  = new TH2I("PiPlus_dEdx_P", " ;p_{PiPlus} GeV/c; dE/dx (keV/cm)", 300, 0.0, 6.0, 250, 0.0, 5.);
	dHist_PiMinus_dEdx_P  = new TH2I("PiMinus_dEdx_P", " ;p_{PiMinus} GeV/c; dE/dx (keV/cm)", 300, 0.0, 6.0, 250, 0.0, 5.);
dHist_Proton_dEdx_P_Measured = new TH2I("Proton_dEdx_P_Measured", " ;p_{proton} GeV/c; dE/dx (keV/cm)", 250, 0.0, 5.0, 250, 0.0, 25.);
dHist_KPlus_dEdx_P_Measured  = new TH2I("KPlus_dEdx_P_Measured", " ;p_{KPlus} GeV/c; dE/dx (keV/cm)", 300, 0.0, 6.0, 250, 0.0, 5.);
dHist_KMinus_dEdx_P_Measured  = new TH2I("KMinus_dEdx_P_Measured", " ;p_{KMinus} GeV/c; dE/dx (keV/cm)", 300, 0.0, 6.0, 250, 0.0, 5.);
dHist_PiPlus_dEdx_P_Measured  = new TH2I("PiPlus_dEdx_P_Measured", " ;p_{PiPlus} GeV/c; dE/dx (keV/cm)", 300, 0.0, 6.0, 250, 0.0, 5.);
dHist_PiMinus_dEdx_P_Measured  = new TH2I("PiMinus_dEdx_P_Measured", " ;p_{PiMinus} GeV/c; dE/dx (keV/cm)", 300, 0.0, 6.0, 250, 0.0, 5.);
dHist_Proton_dEdx_P_PhiPiPiCut  = new TH2I("Proton_dEdx_P_PhiPiPiCut", " ;p_{proton} GeV/c; dE/dx (keV/cm)", 300, 0.0, 6.0, 250, 0.0, 5.);
dHist_KPlus_dEdx_P_PhiPiPiCut  = new TH2I("KPlus_dEdx_P_PhiPiPiCut", " ;p_{KPlus} GeV/c; dE/dx (keV/cm)", 300, 0.0, 6.0, 250, 0.0, 5.);
dHist_KMinus_dEdx_P_PhiPiPiCut  = new TH2I("KMinus_dEdx_P_PhiPiPiCut", " ;p_{KMinus} GeV/c; dE/dx (keV/cm)", 300, 0.0, 6.0, 250, 0.0, 5.);
dHist_PiPlus_dEdx_P_PhiPiPiCut  = new TH2I("PiPlus_dEdx_P_PhiPiPiCut", " ;p_{PiPlus} GeV/c; dE/dx (keV/cm)", 300, 0.0, 6.0, 250, 0.0, 5.);
dHist_PiMinus_dEdx_P_PhiPiPiCut  = new TH2I("PiMinus_dEdx_P_PhiPiPiCut", " ;p_{PiMinus} GeV/c; dE/dx (keV/cm)", 300, 0.0, 6.0, 250, 0.0, 5.);
dHist_Proton_Theta_P_PhiPiPiCut = new TH2I("Proton_Theta_P_PhiPiPiCut", " ;Theta (degree) ;p_{proton} GeV/c", 125, 0.0, 60., 125, 0.0, 5.);
dHist_KPlus_Theta_P_PhiPiPiCut = new TH2I("KPlus_Theta_P_PhiPiPiCut", " ;Theta (degree) ;p_{KPlus} GeV/c", 125, 0.0, 60., 125, 0.0, 5.);
dHist_KMinus_Theta_P_PhiPiPiCut = new TH2I("KMinus_Theta_P_PhiPiPiCut", " ;Theta (degree) ;p_{KMinus} GeV/c", 125, 0.0, 60., 125, 0.0, 5.);
dHist_PiPlus_Theta_P_PhiPiPiCut = new TH2I("PiPlus_Theta_P_PhiPiPiCut", " ;Theta (degree) ;p_{PiPlus} GeV/c", 125, 0.0, 60., 125, 0.0, 5.);
dHist_PiMinus_Theta_P_PhiPiPiCut = new TH2I("PiMinus_Theta_P_PhiPiPiCut", " ;Theta (degree) ;p_{PiMinus} GeV/c", 125, 0.0, 60., 125, 0.0, 5.);

dHist_Proton_KPlus_Angle = new TH1I("Proton_KPlus_Angle", ";Theta (degree)", 300, 0., 120.);
dHist_Proton_KMinus_Angle = new TH1I("Proton_KMinus_Angle", ";Theta (degree)", 300, 0., 120.);
dHist_Proton_PiPlus_Angle = new TH1I("Proton_PiPlus_Angle", ";Theta (degree)", 300, 0., 120.);
dHist_Proton_PiMinus_Angle = new TH1I("Proton_PiMinus_Angle", ";Theta (degree)", 300, 0., 120.);
dHist_KPlus_KMinus_Angle = new TH1I("KPlus_KMinus_Angle", ";Theta (degree)", 300, 0., 120.);
dHist_KPlus_PiPlus_Angle = new TH1I("KPlus_PiPlus_Angle", ";Theta (degree)", 300, 0., 120.);
dHist_KPlus_PiMinus_Angle = new TH1I("KPlus_PiMinus_Angle", ";Theta (degree)", 300, 0., 120.);
dHist_KMinus_PiPlus_Angle = new TH1I("KMinus_PiPlus_Angle", ";Theta (degree)", 300, 0., 120.);
dHist_KMinus_PiMinus_Angle = new TH1I("KMinus_PiMinus_Angle", ";Theta (degree)", 300, 0., 120.);
dHist_PiPlus_PiMinus_Angle = new TH1I("PiPlus_PiMinus_Angle", ";Theta (degree)", 300, 0., 120.);

dHist_Proton_P_PhiPiPiCut = new TH1I("Proton_P_PhiPiPiCut", ";P(proton) (GeV)", 120, 0., 6.);
dHist_KPlus_P_PhiPiPiCut = new TH1I("KPlus_P_PhiPiPiCut", ";P(KPlus) (GeV)", 120, 0., 6.);
dHist_KMinus_P_PhiPiPiCut = new TH1I("KMinus_P_PhiPiPiCut", ";P(KMinus) (GeV)", 120, 0., 6.);
dHist_PiPlus_P_PhiPiPiCut = new TH1I("PiPlus_P_PhiPiPiCut", ";P(PiPlus) (GeV)", 120, 0., 6.);
dHist_PiMinus_P_PhiPiPiCut = new TH1I("PiMinus_P_PhiPiPiCut", ";P(PiMinus) (GeV)", 120, 0., 6.);

dHist_Proton_Theta_PhiPiPiCut = new TH1I("Proton_Theta_PhiPiPiCut", ";Theta(proton) (degree)", 300, 0., 120.0);
dHist_KPlus_Theta_PhiPiPiCut = new TH1I("KPlus_Theta_PhiPiPiCut", ";Theta(KPlus) (degree)", 300, 0., 120.0);
dHist_KMinus_Theta_PhiPiPiCut = new TH1I("KMinus_Theta_PhiPiPiCut", ";Theta(KMinus) (degree)", 300, 0., 120.0);
dHist_PiPlus_Theta_PhiPiPiCut = new TH1I("PiPlus_Theta_PhiPiPiCut", ";Theta(PiPlus) (degree)", 300, 0., 120.0);
dHist_PiMinus_Theta_PhiPiPiCut = new TH1I("PiMinus_Theta_PhiPiPiCut", ";Theta(PiMinus) (degree)", 300, 0., 120.0);

dHist_Proton_DeltaT_BCAL_PhiPiPiCut = new TH1I("Proton_DeltaT_BCAL_PhiPiPiCut", ";BCAL PR", 200, -2.0, 2.);
dHist_KPlus_DeltaT_BCAL_PhiPiPiCut = new TH1I("KPlus_DeltaT_BCAL_PhiPiPiCut", ";BCAL", 100, -1.0, 1.);
dHist_KMinus_DeltaT_BCAL_PhiPiPiCut = new TH1I("KMinus_DeltaT_BCAL_PhiPiPiCut", ";BCAL M", 100, -1.0, 1.);
dHist_PiPlus_DeltaT_BCAL_PhiPiPiCut = new TH1I("PiPlus_DeltaT_BCAL_PhiPiPiCut", ";BCAL PP", 200, -2.0, 2.);
dHist_PiMinus_DeltaT_BCAL_PhiPiPiCut = new TH1I("PiMinus_DeltaT_BCAL_PhiPiPiCut", ";BCAL PM", 200, -2.0, 2.);
dHist_Proton_DeltaT_TOF_PhiPiPiCut = new TH1I("Proton_DeltaT_TOF_PhiPiPiCut", ";TOF PR", 200, -2.0, 2.);
dHist_KPlus_DeltaT_TOF_PhiPiPiCut = new TH1I("KPlus_DeltaT_TOF_PhiPiPiCut", ";TOF", 50, -0.5, 0.5);
dHist_KMinus_DeltaT_TOF_PhiPiPiCut = new TH1I("KMinus_DeltaT_TOF_PhiPiPiCut", ";TOF M", 50, -0.5, 0.5);
dHist_PiPlus_DeltaT_TOF_PhiPiPiCut = new TH1I("PiPlus_DeltaT_TOF_PhiPiPiCut", ";TOF PP", 200, -2.0, 2.);
dHist_PiMinus_DeltaT_TOF_PhiPiPiCut = new TH1I("PiMinus_DeltaT_TOF_PhiPiPiCut", ";TOF PM", 200, -2.0, 2.);

dHist_Proton_P_vs_Beta_BCAL_PhiPiPiCut = new TH2I("Proton_P_vs_Beta_BCAL_PhiPiPiCut", "Beta_pr", 60, 0., 6., 200, 0.2, 1.4);
dHist_KPlus_P_vs_Beta_BCAL_PhiPiPiCut = new TH2I("KPlus_P_vs_Beta_BCAL_PhiPiPiCut", "Beta", 60, 0., 6., 200, 0.2, 1.4);
dHist_KMinus_P_vs_Beta_BCAL_PhiPiPiCut = new TH2I("KMinus_P_vs_Beta_BCAL_PhiPiPiCut", "Beta_km", 60, 0., 6., 200, 0.2, 1.4);
dHist_PiPlus_P_vs_Beta_BCAL_PhiPiPiCut = new TH2I("PiPlus_P_vs_Beta_BCAL_PhiPiPiCut", "Beta_pip", 60, 0., 6., 200, 0.2, 1.4);
dHist_PiMinus_P_vs_Beta_BCAL_PhiPiPiCut = new TH2I("PiMinus_P_vs_Beta_BCAL_PhiPiPiCut", "Beta_pim", 60, 0., 6., 200, 0.2, 1.4);
dHist_Proton_P_vs_DeltaT_BCAL_PhiPiPiCut = new TH2I("Proton_P_vs_DeltaT_BCAL_PhiPiPiCut", "p DELTAT_BCAL PR", 60, 0., 6., 200, -2., 2.);
dHist_KPlus_P_vs_DeltaT_BCAL_PhiPiPiCut = new TH2I("KPlus_P_vs_DeltaT_BCAL_PhiPiPiCut", "p DELTAT_BCAL", 60, 0., 6., 200, -2, 2.);
dHist_KMinus_P_vs_DeltaT_BCAL_PhiPiPiCut = new TH2I("KMinus_P_vs_DeltaT_BCAL_PhiPiPiCut", "p DELTAT_BCAL M", 60, 0., 6., 200, -2, 2.);
dHist_PiPlus_P_vs_DeltaT_BCAL_PhiPiPiCut = new TH2I("PiPlus_P_vs_DeltaT_BCAL_PhiPiPiCut", "p DELTAT_BCAL PP", 60, 0., 6., 200, -2, 2.);
dHist_PiMinus_P_vs_DeltaT_BCAL_PhiPiPiCut = new TH2I("PiMinus_P_vs_DeltaT_BCAL_PhiPiPiCut", "p DELTAT_BCAL PM", 60, 0., 6., 200, -2, 2.);

dHist_Proton_Beta_BCAL_PhiPiPiCut = new TH1I("Proton_Beta_BCAL_PhiPiPiCut","Beta_pr", 100 ,0 , 2.);
dHist_KPlus_Beta_BCAL_PhiPiPiCut = new TH1I("KPlus_Beta_BCAL_PhiPiPiCut","Beta", 100 ,0 , 2.);
dHist_KMinus_Beta_BCAL_PhiPiPiCut = new TH1I("KMinus_Beta_BCAL_PhiPiPiCut","Beta_km", 100 ,0 , 2.);
dHist_PiPlus_Beta_BCAL_PhiPiPiCut = new TH1I("PiPlus_Beta_BCAL_PhiPiPiCut","Beta_pip", 100 ,0 , 2.);
dHist_PiMinus_Beta_BCAL_PhiPiPiCut = new TH1I("PiMinus_Beta_BCAL_PhiPiPiCut","Beta_pim", 100 ,0 , 2.);

dHist_Proton_P_vs_Beta_TOF_PhiPiPiCut  = new TH2I("Proton_P_vs_Beta_TOF_PhiPiPiCut", "Betat_pr", 60, 0., 6., 200, 0.2, 1.4);
dHist_KPlus_P_vs_Beta_TOF_PhiPiPiCut  = new TH2I("KPlus_P_vs_Beta_TOF_PhiPiPiCut", "Betat", 60, 0., 6., 200, 0.2, 1.4);
dHist_KMinus_P_vs_Beta_TOF_PhiPiPiCut = new TH2I("KMinus_P_vs_Beta_TOF_PhiPiPiCut", "Betat_km", 60, 0., 6., 200, 0.2, 1.4);
dHist_PiPlus_P_vs_Beta_TOF_PhiPiPiCut  = new TH2I("PiPlus_P_vs_Beta_TOF_PhiPiPiCut", "Betat_pip", 60, 0., 6., 200, 0.2, 1.4);
dHist_PiMinus_P_vs_Beta_TOF_PhiPiPiCut = new TH2I("PiMinus_P_vs_Beta_TOF_PhiPiPiCut", "Betat_pim", 60, 0., 6., 200, 0.2, 1.4);

dHist_Proton_P_vs_DeltaT_TOF_PhiPiPiCut = new TH2I("Proton_P_vs_DeltaT_TOF_PhiPiPiCut", "p DELTAT_TOF PR", 60, 0., 6., 200, -2., 2.);
dHist_KPlus_P_vs_DeltaT_TOF_PhiPiPiCut = new TH2I("KPlus_P_vs_DeltaT_TOF_PhiPiPiCut", "p DELTAT_TOF", 60, 0., 6., 200, -2., 2.);
dHist_KMinus_P_vs_DeltaT_TOF_PhiPiPiCut = new TH2I("KMinus_P_vs_DeltaT_TOF_PhiPiPiCut", "p DELTAT_TOF M", 60, 0., 6., 200, -2., 2.);
dHist_PiPlus_P_vs_DeltaT_TOF_PhiPiPiCut = new TH2I("PiPlus_P_vs_DeltaT_TOF_PhiPiPiCut", "p DELTAT_TOF PP", 60, 0., 6., 200, -2., 2.);
dHist_PiMinus_P_vs_DeltaT_TOF_PhiPiPiCut = new TH2I("PiMinus_P_vs_DeltaT_TOF_PhiPiPiCut", "p DELTAT_TOF PM", 50, 0., 6., 200, -2., 2.);

dHist_Proton_Beta_TOF_PhiPiPiCut  = new TH1I("Proton_Beta_TOF_PhiPiPiCut","Betat_pr", 100 ,0 , 2.);
dHist_KPlus_Beta_TOF_PhiPiPiCut  = new TH1I("KPlus_Beta_TOF_PhiPiPiCut","Betat", 100 ,0 , 2.);
dHist_KMinus_Beta_TOF_PhiPiPiCut = new TH1I("KMinus_Beta_TOF_PhiPiPiCut","Betat_km", 100 ,0 , 2.);
dHist_PiPlus_Beta_TOF_PhiPiPiCut  = new TH1I("PiPlus_Beta_TOF_PhiPiPiCut","Betat_pip", 100 ,0 , 2.);
dHist_PiMinus_Beta_TOF_PhiPiPiCut = new TH1I("PiMinus_Beta_TOF_PhiPiPiCut","Betat_pim", 100 ,0 , 2.);

dHist_Proton_ChiSq_Tracking = new TH1I("Proton_ChiSq_Tracking", " ;#chi^{2}", 100, 0, 30.);
dHist_KPlus_ChiSq_Tracking = new TH1I("KPlus_ChiSq_Tracking", " ;#chi^{2}", 100, 0, 30.);
dHist_KMinus_ChiSq_Tracking = new TH1I("KMinus_ChiSq_Tracking", " ;#chi^{2}", 100, 0, 30.);
dHist_PiPlus_ChiSq_Tracking = new TH1I("PiPlus_ChiSq_Tracking", " ;#chi^{2}", 100, 0, 30.);
dHist_PiMinus_ChiSq_Tracking = new TH1I("PiMinus_ChiSq_Tracking", " ;#chi^{2}", 100, 0, 30.);
dHist_Proton_NDF_Tracking = new TH1I("Proton_NDF_Tracking", " ;NDF", 100, 0, 30.);
dHist_KPlus_NDF_Tracking = new TH1I("KPlus_NDF_Tracking", " ;NDF", 100, 0, 30.);
dHist_KMinus_NDF_Tracking = new TH1I("KMinus_NDF_Tracking", " ;NDF", 100, 0, 30.);
dHist_PiPlus_NDF_Tracking = new TH1I("PiPlus_NDF_Tracking", " ;NDF", 100, 0, 30.);
dHist_PiMinus_NDF_Tracking = new TH1I("PiMinus_NDF_Tracking", " ;NDF", 100, 0, 30.);

dHist_Proton_EP_BCAL = new TH1I("Proton_EP_BCAL", " ;E/P", 200, 0., 2.0);
dHist_KPlus_EP_BCAL = new TH1I("KPlus_EP_BCAL", " ;E/P", 200, 0., 2.0);
dHist_KMinus_EP_BCAL = new TH1I("KMinus_EP_BCAL", " ;E/P", 200, 0., 2.0);
dHist_PiPlus_EP_BCAL = new TH1I("PiPlus_EP_BCAL", " ;E/P", 200, 0., 2.0);
dHist_PiMinus_EP_BCAL = new TH1I("PiMinus_EP_BCAL", " ;E/P", 200, 0., 2.0);
dHist_Proton_EP_FCAL = new TH1I("Proton_EP_FCAL", " ;E/P", 200, 0., 2.0);
dHist_KPlus_EP_FCAL = new TH1I("KPlus_EP_FCAL", " ;E/P", 200, 0., 2.0);
dHist_KMinus_EP_FCAL = new TH1I("KMinus_EP_FCAL", " ;E/P", 200, 0., 2.0);
dHist_PiPlus_EP_FCAL = new TH1I("PiPlus_EP_FCAL", " ;E/P", 200, 0., 2.0);
dHist_PiMinus_EP_FCAL = new TH1I("PiMinus_EP_FCAL", " ;E/P", 200, 0., 2.0);


dHist_Proton_dEdx_P_PhiPiPiCut_Measured  = new TH2I("Proton_dEdx_P_PhiPiPiCut_Measured", " ;p_{proton} GeV/c; dE/dx (keV/cm)", 300, 0.0, 6.0, 250, 0.0, 5.);
dHist_KPlus_dEdx_P_PhiPiPiCut_Measured  = new TH2I("KPlus_dEdx_P_PhiPiPiCut_Measured", " ;p_{KPlus} GeV/c; dE/dx (keV/cm)", 300, 0.0, 6.0, 250, 0.0, 5.);
dHist_KMinus_dEdx_P_PhiPiPiCut_Measured  = new TH2I("KMinus_dEdx_P_PhiPiPiCut_Measured", " ;p_{KMinus} GeV/c; dE/dx (keV/cm)", 300, 0.0, 6.0, 250, 0.0, 5.);
dHist_PiPlus_dEdx_P_PhiPiPiCut_Measured  = new TH2I("PiPlus_dEdx_P_PhiPiPiCut_Measured", " ;p_{PiPlus} GeV/c; dE/dx (keV/cm)", 300, 0.0, 6.0, 250, 0.0, 5.);
dHist_PiMinus_dEdx_P_PhiPiPiCut_Measured  = new TH2I("PiMinus_dEdx_P_PhiPiPiCut_Measured", " ;p_{PiMinus} GeV/c; dE/dx (keV/cm)", 300, 0.0, 6.0, 250, 0.0, 5.);
dHist_Proton_Theta_P_PhiPiPiCut_Measured = new TH2I("Proton_Theta_P_PhiPiPiCut_Measured", " ;Theta (degree) ;p_{proton} GeV/c", 125, 0.0, 60., 125, 0.0, 5.);
dHist_KPlus_Theta_P_PhiPiPiCut_Measured = new TH2I("KPlus_Theta_P_PhiPiPiCut_Measured", " ;Theta (degree) ;p_{KPlus} GeV/c", 125, 0.0, 60., 125, 0.0, 5.);
dHist_KMinus_Theta_P_PhiPiPiCut_Measured = new TH2I("KMinus_Theta_P_PhiPiPiCut_Measured", " ;Theta (degree) ;p_{KMinus} GeV/c", 125, 0.0, 60., 125, 0.0, 5.);
dHist_PiPlus_Theta_P_PhiPiPiCut_Measured = new TH2I("PiPlus_Theta_P_PhiPiPiCut_Measured", " ;Theta (degree) ;p_{PiPlus} GeV/c", 125, 0.0, 60., 125, 0.0, 5.);
dHist_PiMinus_Theta_P_PhiPiPiCut_Measured = new TH2I("PiMinus_Theta_P_PhiPiPiCut_Measured", " ;Theta (degree) ;p_{PiMinus} GeV/c", 125, 0.0, 60., 125, 0.0, 5.);

dHist_MissingEnergy_PhiPiPiCut = new TH1I("MissingEnergy_PhiPiPiCut", ";Missing Energy GeV", 200, -2., 2.);
dHist_MissingMass_PhiPiPiCut = new TH1I("MissingMass_PhiPiPiCut", ";Missing Mass (GeV/c^{2})", 400, -0.2, 0.2);
dHist_MissingMassSquared_PhiPiPiCut = new TH1I("MissingMassSquared_PhiPiPiCut", ";Missing Mass Squared (GeV/c^{2})^{2}", 200, -0.1, 0.1);
dHist_Energy_UnusedShowers_PhiPiPiCut = new TH1I("Energy_UnusedShowers_PhiPiPiCut", ";Unused Energy (GeV)", 350, -0.5, 3.0);
dHist_KinFitCL_PhiPiPiCut = new TH1I("KinFitCL_PhiPiPiCut", ";Kinematic Fit Confidence Level", 1000, 0., 1.0);
dHist_BeamEnergy_PhiPiPiCut = new TH1I("BeamEnergy_PhiPiPiCut", ";Beam Energy (GeV)", 600, 0.0, 12.0);

dHist_MPhiPiPi_vs_MProtonPiPlus_Measured = new TH2I("MPhiPiPi_vs_MProtonPiPlus_Measured", " ;M(#phi#pi^{+}#pi^{-}) (GeV/c^2);M(p#pi^{+}) (GeV/c^2)", 210, 1.4, 3.5, 200, 1.0, 3.0);
dHist_MPhiPiPi_vs_MProtonPiMinus_Measured = new TH2I("MPhiPiPi_vs_MProtonPiMinus_Measured", " ;M(#phi#pi^{+}#pi^{-}) (GeV/c^2);M(p#pi^{-}) (GeV/c^2)", 210, 1.4, 3.5, 200, 1.0, 3.0);
dHist_MPhiPiPi_vs_MPhiProton_Measured = new TH2I("MPhiPiPi_vs_MPhiProton_Measured", " ;M(#phi#pi^{+}#pi^{-}) (GeV/c^2);M(#phi p) (GeV/c^2)", 210, 1.4, 3.5, 150, 1.5, 4.5);
dHist_MPhiPiPi_vs_MPiPi_Measured = new TH2I("MPhiPiPi_vs_MPiPi_Measured", " ;M(#phi#pi^{+}#pi^{-}) (GeV/c^2);M(#pi^{+}#pi^{-}) (GeV/c^2)", 210, 1.4, 3.5, 180, 0.2, 2.0);
dHist_MPhiPiPi_vs_MPhiPiPlus_Measured = new TH2I("MPhiPiPi_vs_MPhiPiPlus_Measured", " ;M(#phi#pi^{+}#pi^{-}) (GeV/c^2);M(#phi#pi^{+}) (GeV/c^2)", 210, 1.4, 3.5, 198, 1.0, 2.98);
dHist_MPhiPiPi_vs_MPhiPiMinus_Measured = new TH2I("MPhiPiPi_vs_MPhiPiMinus_Measured", " ;M(#phi#pi^{+}#pi^{-}) (GeV/c^2);M(#phi#pi^{-}) (GeV/c^2)", 210, 1.4, 3.5, 198, 1.0, 2.98);

dHist_MPhiPiPlus_vs_MPhiPiMinus_Measured = new TH2I("MPhiPiPlus_vs_MPhiPiMinus_Measured", " ;M(#phi#pi^{+}) (GeV/c^2);M(#phi#pi^{-}) (GeV/c^2)", 198, 1.0, 2.98, 198, 1.0, 2.98);
dHist_MPhiPiPlus_vs_MPiPi_Measured = new TH2I("MPhiPiPlus_vs_MPiPi_Measured", " ;M(#phi#pi^{+}) (GeV/c^2);M(#pi^{+}#pi^{-}) (GeV/c^2)", 198, 1.0, 2.98, 180, 0.2, 2.0);
dHist_MPhiPiMinus_vs_MPiPi_Measured = new TH2I("MPhiPiMinus_vs_MPiPi_Measured", " ;M(#phi#pi^{-}) (GeV/c^2);M(#pi^{+}#pi^{-}) (GeV/c^2)", 198, 1.0, 2.98, 180, 0.2, 2.0);
dHist_MPhiPiPlus_vs_MKPlusPiMinus_Measured = new TH2I("MPhiPiPlus_vs_MKPlusPiMinus_Measured", " ;M(#phi#pi^{+}) (GeV/c^2);M(K^{+}#pi^{-}) (GeV/c^2)", 198, 1.0, 2.98, 140, 0.6, 2.0);
dHist_MPhiPiPlus_vs_MKMinusPiPlus_Measured = new TH2I("MPhiPiPlus_vs_MKMinusPiPlus_Measured", " ;M(#phi#pi^{+}) (GeV/c^2);M(K^{-}#pi^{+}) (GeV/c^2)", 198, 1.0, 2.98, 140, 0.6, 2.0);
dHist_MPhiPiMinus_vs_MKPlusPiMinus_Measured = new TH2I("MPhiPiMinus_vs_MKPlusPiMinus_Measured", " ;M(#phi#pi^{-}) (GeV/c^2);M(K^{+}#pi^{-}) (GeV/c^2)", 198, 1.0, 2.98, 140, 0.6, 2.0);
dHist_MPhiPiMinus_vs_MKMinusPiPlus_Measured = new TH2I("MPhiPiMinus_vs_MKMinusPiPlus_Measured", " ;M(#phi#pi^{-}) (GeV/c^2);M(K^{-}#pi^{+}) (GeV/c^2)", 198, 1.0, 2.98, 140, 0.6, 2.0);

	//dHist_Mphipipi_measured = new TH1I("Mphipipi_measured", ";M(phi-pi+pi-) (GeV)", 66, 1.50, 3.48);
	//dHist_Mphipipi = new TH1I("Mphipipi", ";M(#phi#pi^{+}#pi^{-}) (GeV)", 66, 1.50, 3.48);

	//dHist_Mphipipi_measured = new TH1I("Mphipipi_measured", ";M(phi-pi+pi-) (GeV)", 21, 1.40, 3.5);
	//dHist_Mphipipi = new TH1I("Mphipipi", ";M(#phi#pi^{+}#pi^{-}) (GeV)", 21, 1.40, 3.50);
	dHist_Mphipipi_measured = new TH1I("Mphipipi_measured", ";M(phi-pi+pi-) (GeV)", 42, 1.4, 3.5);
	dHist_Mphipipi = new TH1I("Mphipipi", ";M(#phi#pi^{+}#pi^{-}) (GeV)", 42, 1.4, 3.50);
	

	//dHist_Mphi_measured = new TH1I("Mphi_measured", ";M(K+K-) (GeV)", 300, 0.9, 1.5);
	//dHist_Mphi = new TH1I("Mphi", ";M(K^{+}K^{-}) (GeV)", 300, 0.9, 1.5);
	//dHist_Mphi_measured = new TH1I("Mphi_measured", ";M(K+K-) (GeV)", 60, 0.98, 1.1);
	//dHist_Mphi = new TH1I("Mphi", ";M(K^{+}K^{-}) (GeV)", 60, 0.98, 1.1);
	dHist_Mphi_measured = new TH1I("Mphi_measured", ";M(K+K-) (GeV)",110, 0.98, 1.2);
	dHist_Mphi = new TH1I("Mphi", ";M(K^{+}K^{-}) (GeV)", 110, 0.98, 1.2);

	dHist_Mphi_measured1 = new TH1I("Mphi_measured1", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured2 = new TH1I("Mphi_measured2", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured3 = new TH1I("Mphi_measured3", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured4 = new TH1I("Mphi_measured4", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured5 = new TH1I("Mphi_measured5", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured6 = new TH1I("Mphi_measured6", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured7 = new TH1I("Mphi_measured7", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured8 = new TH1I("Mphi_measured8", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured9 = new TH1I("Mphi_measured9", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured10 = new TH1I("Mphi_measured10", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured11 = new TH1I("Mphi_measured11", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured12 = new TH1I("Mphi_measured12", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured13 = new TH1I("Mphi_measured13", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured14 = new TH1I("Mphi_measured14", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured15 = new TH1I("Mphi_measured15", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured16 = new TH1I("Mphi_measured16", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured17 = new TH1I("Mphi_measured17", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured18 = new TH1I("Mphi_measured18", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured19 = new TH1I("Mphi_measured19", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured20 = new TH1I("Mphi_measured20", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured21 = new TH1I("Mphi_measured21", ";M(K+K-) (GeV)", 110, 0.98, 1.2);


	dHist_Mphi_measured22 = new TH1I("Mphi_measured22", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured23 = new TH1I("Mphi_measured23", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured24 = new TH1I("Mphi_measured24", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured25 = new TH1I("Mphi_measured25", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured26 = new TH1I("Mphi_measured26", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured27 = new TH1I("Mphi_measured27", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured28 = new TH1I("Mphi_measured28", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured29 = new TH1I("Mphi_measured29", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured30 = new TH1I("Mphi_measured30", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured31 = new TH1I("Mphi_measured31", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured32 = new TH1I("Mphi_measured32", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured33 = new TH1I("Mphi_measured33", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured34 = new TH1I("Mphi_measured34", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured35 = new TH1I("Mphi_measured35", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured36 = new TH1I("Mphi_measured36", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured37 = new TH1I("Mphi_measured37", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured38 = new TH1I("Mphi_measured38", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured39 = new TH1I("Mphi_measured39", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured40 = new TH1I("Mphi_measured40", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured41 = new TH1I("Mphi_measured41", ";M(K+K-) (GeV)", 110, 0.98, 1.2);
	dHist_Mphi_measured42 = new TH1I("Mphi_measured42", ";M(K+K-) (GeV)", 110, 0.98, 1.2);


	dHist_Mphipip_measured = new TH1I("Mphipip_measured", ";M(K+K-pi+) (GeV)", 66, 1.0, 2.98);
	dHist_Mphipip = new TH1I("Mphipip", ";M(#phi#pi^{+}) (GeV)", 66, 1.0, 2.98);
	dHist_Mphipim_measured = new TH1I("Mphipim_measured", ";M(K+K-pi-) (GeV)", 66, 1.0, 2.98);
	dHist_Mphipim = new TH1I("Mphipim", ";M(#phi#pi^{-}) (GeV)", 66, 1.0, 2.98);

	//dHist_Mphipip_measured = new TH1I("Mphipip_measured", ";M(K+K-pi+) (GeV)", 100, 1.0, 3.0);
	//dHist_Mphipip = new TH1I("Mphipip", ";M(#phi#pi^{+}) (GeV)", 100, 1.0, 3.0);
	//dHist_Mphipim_measured = new TH1I("Mphipim_measured", ";M(K+K-pi-) (GeV)", 100, 1.0, 3.0);
	//dHist_Mphipim = new TH1I("Mphipim", ";M(#phi#pi^{-}) (GeV)", 100, 1.0, 3.0);

	//dHist_Mphipip_measured = new TH1I("Mphipip_measured", ";M(K+K-pi+) (GeV)", 200, 1.0, 3.0);
	//dHist_Mphipip = new TH1I("Mphipip", ";M(#phi#pi^{+}) (GeV)", 200, 1.0, 3.0);
	//dHist_Mphipim_measured = new TH1I("Mphipim_measured", ";M(K+K-pi-) (GeV)", 200, 1.0, 3.0);
	//dHist_Mphipim = new TH1I("Mphipim", ";M(#phi#pi^{-}) (GeV)", 200, 1.0, 3.0);


	dHist_Mpippim_measured = new TH1I("Mpippim_measured", ";M(pi+-pi-) (GeV)", 100, 0.0, 2.0);
	dHist_Mpippim = new TH1I("Mpippim", ";M(#pi^{+}#pi^{-}) (GeV)", 100, 0.0, 2.0);
	dHist_Mkst_measured = new TH1I("Mkst_measured", ";M(K+pi-) (GeV)", 100, 0.6, 2.0);
	dHist_Mkst = new TH1I("Mkst", ";M(K^{+}#pi^{-}) (GeV)", 100, 0.0, 2.0);
	dHist_Maks_measured = new TH1I("Maks_measured", ";M(K-pi+) (GeV)", 100, 0.6, 2.0);
	dHist_Maks = new TH1I("Maks", ";M(K^{-}#pi^{+}) (GeV)", 100, 0.6, 2.0);
	dHist_Mpip_Mpim_measured = new TH2I("M-phi-pim vs M-phi-pip", "M-phi-pim GeV; M-phi-pip GeV", 50, 1., 3., 50, 1., 3.);

        dHist_KPlus_DeltaT_BCAL = new TH1I("KPlus_DeltaT_BCAL", ";BCAL", 100, -1.0, 1.);
        dHist_KPlus_P_vs_DeltaT_BCAL = new TH2I("KPlus_P_vs_DeltaT_BCAL", "p DELTAT_BCAL", 60, 0., 6., 200, -2, 2.);
        dHist_KPlus_DeltaT_TOF = new TH1I("KPlus_DeltaT_TOF", ";TOF", 50, -0.5, 0.5);
        dHist_KPlus_P_vs_DeltaT_TOF = new TH2I("KPlus_P_vs_DeltaT_TOF", "p DELTAT_TOF", 60, 0., 6., 200, -2., 2.);

        dHist_KMinus_DeltaT_BCAL = new TH1I("KMinus_DeltaT_BCAL", ";BCAL M", 100, -1.0, 1.);
        dHist_KMinus_P_vs_DeltaT_BCAL = new TH2I("KMinus_P_vs_DeltaT_BCAL", "p DELTAT_BCAL M", 60, 0., 6., 200, -2, 2.);
        dHist_KMinus_DeltaT_TOF = new TH1I("KMinus_DeltaT_TOF", ";TOF M", 50, -0.5, 0.5);
        dHist_KMinus_P_vs_DeltaT_TOF = new TH2I("KMinus_P_vs_DeltaT_TOF", "p DELTAT_TOF M", 60, 0., 6., 200, -2., 2.);


        dHist_PiPlus_DeltaT_BCAL = new TH1I("PiPlus_DeltaT_BCAL", ";BCAL PP", 200, -2.0, 2.);
        dHist_PiPlus_P_vs_DeltaT_BCAL = new TH2I("PiPlus_P_vs_DeltaT_BCAL", "p DELTAT_BCAL PP", 60, 0., 6., 200, -2, 2.);
        dHist_PiPlus_DeltaT_TOF = new TH1I("PiPlus_DeltaT_TOF", ";TOF PP", 200, -2.0, 2.);
        dHist_PiPlus_P_vs_DeltaT_TOF = new TH2I("PiPlus_P_vs_DeltaT_TOF", "p DELTAT_TOF PP", 60, 0., 6., 200, -2., 2.);

        dHist_PiMinus_DeltaT_BCAL = new TH1I("PiMinus_DeltaT_BCAL", ";BCAL PM", 200, -2.0, 2.);
        dHist_PiMinus_P_vs_DeltaT_BCAL = new TH2I("PiMinus_P_vs_DeltaT_BCAL", "p DELTAT_BCAL PM", 60, 0., 6., 200, -2, 2.);
        dHist_PiMinus_DeltaT_TOF = new TH1I("PiMinus_DeltaT_TOF", ";TOF PM", 200, -2.0, 2.);
        dHist_PiMinus_P_vs_DeltaT_TOF = new TH2I("PiMinus_P_vs_DeltaT_TOF", "p DELTAT_TOF PM", 50, 0., 6., 200, -2., 2.);

        dHist_Proton_DeltaT_BCAL = new TH1I("Proton_DeltaT_BCAL", ";BCAL PR", 200, -2.0, 2.);
        dHist_Proton_P_vs_DeltaT_BCAL = new TH2I("Proton_P_vs_DeltaT_BCAL", "p DELTAT_BCAL PR", 60, 0., 6., 200, -2., 2.);
        dHist_Proton_DeltaT_TOF = new TH1I("Proton_DeltaT_TOF", ";TOF PR", 200, -2.0, 2.);
        dHist_Proton_P_vs_DeltaT_TOF = new TH2I("Proton_P_vs_DeltaT_TOF", "p DELTAT_TOF PR", 60, 0., 6., 200, -2., 2.);

	dHist_MphiProton_measured = new TH1I("MPhiProton_measured", ";M(phi-proton) (GeV)", 100, 1.5, 4.5);

	dHist_Proton_P = new TH1I("Proton_P", ";P(proton) (GeV)", 120, 0., 6.);
	//dHist_Proton_Theta = new TH1I("Proton_Theta", ";Theta(proton) (radian)", 150, 0., 1.5);
	dHist_Proton_Theta = new TH1I("Proton_Theta", ";Theta(proton) (degree)", 150, 0., 60.0);
	//dHist_Proton_Theta_P = new TH2I("Proton_Theta_P", " ;p_{proton} GeV/c; Theta (radian)", 250, 0.0, 5.0, 250, 0.0, 1.5);
	dHist_Proton_Theta_P = new TH2I("Proton_Theta_P", " ;Theta (degree) ;p_{proton} GeV/c", 125, 0.0, 60., 125, 0.0, 5.);
	dHist_kk_kkpipi = new TH2I("kk_kkpipi", " ;Mkk GeV ;Mkkpipi GeV", 500, 0.98, 1.2, 500, 1.9, 3.4);
	dHist_ebeam_kkpipi = new TH2I("ebeam_kkpipi", " ;Ebeam GeV ;Mkkpipi GeV", 500, 2., 12., 500, 1.9, 3.4);

	dHist_PiPlus_P = new TH1I("PiPlus_P", ";P(piplus) (GeV)", 120, 0., 6.);
	dHist_PiPlus_Theta = new TH1I("PiPlus_Theta", ";Theta(piplus) (degree)", 300, 0., 120.0);
	dHist_PiMinus_P = new TH1I("PiMinus_P", ";P(piminus) (GeV)", 120, 0., 6.);
	dHist_PiMinus_Theta = new TH1I("PiMinus_Theta", ";Theta(piminus) (degree)", 300, 0., 120.0);
	dHist_KPlus_P = new TH1I("KPlus_P", ";P(kplus) (GeV)", 120, 0., 6.);
	dHist_KPlus_Theta = new TH1I("KPlus_Theta", ";Theta(kplus) (degree)", 300, 0., 120.0);
	dHist_KMinus_P = new TH1I("KMinus_P", ";P(kminus) (GeV)", 120, 0., 6.);
	dHist_KMinus_Theta = new TH1I("KMinus_Theta", ";Theta(kminus) (degree)", 300, 0., 120.0);

	dHist_MProtonPiP_measured = new TH1I("MProtonPiP_measured", ";M(proton-pip) (GeV)", 200, 1.0, 3.0);
	dHist_MProtonPiM_measured = new TH1I("MProtonPiM_measured", ";M(proton-pim) (GeV)", 200, 1.0, 3.0);

	dHist_PiPlus_TrkChiSq = new TH1I("PiPlus_Trk_ChiSq", " ;#pi^{+} #chi^{2}/dof", 100, 0, 25.);
	dHist_PiMinus_TrkChiSq = new TH1I("PiMinus_Trk_ChiSq", " ;#pi^{+} #chi^{2}/dof", 100, 0, 25.);
	dHist_KPlus_TrkChiSq = new TH1I("KPlus_Trk_ChiSq", " ;K^{+} #chi^{2}/dof", 100, 0, 25.);
	dHist_KMinus_TrkChiSq = new TH1I("KMinus_Trk_ChiSq", " ;K^{-} #chi^{2}/dof", 100, 0, 25.);
	dHist_Proton_TrkChiSq = new TH1I("Proton_Trk_ChiSq", " ;p #chi^{2}/dof", 100, 0, 25.);

        dHist_KPlus_Beta_BCAL = new TH1I("KPlus_Beta_BCAL","Beta", 100 ,0 , 2.);
        dHist_KPlus_Beta_TOF  = new TH1I("KPlus_Beta_TOF","Betat", 100 ,0 , 2.);

        dHist_KPlus_P_vs_Beta_BCAL = new TH2I("KPlus_P_vs_Beta_BCAL", "Beta", 60, 0., 6., 200, 0.2, 1.4);
        dHist_KPlus_P_vs_Beta_TOF  = new TH2I("KPlus_P_vs_Beta_TOF", "Betat", 60, 0., 6., 200, 0.2, 1.4);

        dHist_KMinus_Beta_BCAL = new TH1I("KMinus_Beta_BCAL","Beta_km", 100 ,0 , 2.);
        dHist_KMinus_Beta_TOF = new TH1I("KMinus_Beta_TOF","Betat_km", 100 ,0 , 2.);

        dHist_KMinus_P_vs_Beta_BCAL = new TH2I("KMinus_P_vs_Beta_BCAL", "Beta_km", 60, 0., 6., 200, 0.2, 1.4);
        dHist_KMinus_P_vs_Beta_TOF = new TH2I("KMinus_P_vs_Beta_TOF", "Betat_km", 60, 0., 6., 200, 0.2, 1.4);

        dHist_Proton_Beta_BCAL = new TH1I("Proton_Beta_BCAL","Beta_pr", 100 ,0 , 2.);
        dHist_Proton_Beta_TOF  = new TH1I("Proton_Beta_TOF","Betat_pr", 100 ,0 , 2.);

        dHist_Proton_P_vs_Beta_BCAL = new TH2I("Proton_P_vs_Beta_BCAL", "Beta_pr", 60, 0., 6., 200, 0.2, 1.4);
        dHist_Proton_P_vs_Beta_TOF  = new TH2I("Proton_P_vs_Beta_TOF", "Betat_pr", 60, 0., 6., 200, 0.2, 1.4);

        dHist_PiPlus_Beta_BCAL = new TH1I("PiPlus_Beta_BCAL","Beta_pip", 100 ,0 , 2.);
        dHist_PiPlus_Beta_TOF  = new TH1I("PiPlus_Beta_TOF","Betat_pip", 100 ,0 , 2.);

        dHist_PiPlus_P_vs_Beta_BCAL = new TH2I("PiPlus_P_vs_Beta_BCAL", "Beta_pip", 60, 0., 6., 200, 0.2, 1.4);
        dHist_PiPlus_P_vs_Beta_TOF  = new TH2I("PiPlus_P_vs_Beta_TOF", "Betat_pip", 60, 0., 6., 200, 0.2, 1.4);

        dHist_PiMinus_Beta_BCAL = new TH1I("PiMinus_Beta_BCAL","Beta_pim", 100 ,0 , 2.);
        dHist_PiMinus_Beta_TOF = new TH1I("PiMinus_Beta_TOF","Betat_pim", 100 ,0 , 2.);

        dHist_PiMinus_P_vs_Beta_BCAL = new TH2I("PiMinus_P_vs_Beta_BCAL", "Beta_pim", 60, 0., 6., 200, 0.2, 1.4);
        dHist_PiMinus_P_vs_Beta_TOF = new TH2I("PiMinus_P_vs_Beta_TOF", "Betat_pim", 60, 0., 6., 200, 0.2, 1.4);


	// EXAMPLE CUT PARAMETERS:
	fMinProton_dEdx = new TF1("fMinProton_dEdx", "exp(-1.*[0]*x + [1]) + [2]", 0., 10.);
	fMinProton_dEdx->SetParameters(4.0, 2.5, 1.25);

	dHist_combo = new TH1I("combo", "combo", 100, 0, 20.);

	/***************************************** ADVANCED: CHOOSE BRANCHES TO READ ****************************************/

	//TO SAVE PROCESSING TIME
		//If you know you don't need all of the branches/data, but just a subset of it, you can speed things up
		//By default, for each event, the data is retrieved for all branches
		//If you know you only need data for some branches, you can skip grabbing data from the branches you don't need
		//Do this by doing something similar to the commented code below

	//dTreeInterface->Clear_GetEntryBranches(); //now get none
	//dTreeInterface->Register_GetEntryBranch("Proton__P4"); //manually set the branches you want
}

Bool_t DSelector_phipipi_2k::Process(Long64_t locEntry)
{
	// The Process() function is called for each entry in the tree. The entry argument
	// specifies which entry in the currently loaded tree is to be processed.
	//
	// This function should contain the "body" of the analysis. It can contain
	// simple or elaborate selection criteria, run algorithms on the data
	// of the event and typically fill histograms.
	//
	// The processing can be stopped by calling Abort().
	// Use fStatus to set the return value of TTree::Process().
	// The return value is currently not used.

	//CALL THIS FIRST
	DSelector::Process(locEntry); //Gets the data from the tree for the entry
	//cout << "RUN " << Get_RunNumber() << ", EVENT " << Get_EventNumber() << endl;

	/**************************************** SETUP AUTOMATIC UNIQUENESS TRACKING ***************************************/

	//Reset uniqueness tracking for each action
	//dHistComboKinematics->Reset_NewEvent();
	//dHistComboPID->Reset_NewEvent();

	//INSERT OTHER USER ACTIONS HERE

	/***************************************** SETUP MANUAL UNIQUENESS TRACKING *****************************************/

	//PREVENT-DOUBLE COUNTING WHEN HISTOGRAMMING
		//Sometimes, some content is the exact same between one combo and the next
			//e.g. maybe two combos have different beam particles, but the same data for the final-state
		//When histogramming, you don't want to double-count when this happens: artificially inflates your signal (or background)
		//So, for each quantity you histogram, keep track of what particles you used (for a given combo)
		//Then for each combo, just compare to what you used before, and make sure it's unique

	//EXAMPLE 1: Particle-specific info:
	set<Int_t> locUsedSoFar_BeamEnergy; //Int_t: Unique ID for beam particles. set: easy to use, fast to search
	set<Int_t> locUsedSoFar_Proton;

	//EXAMPLE 2: Combo-specific info:
		//In general: Could have multiple particles with the same PID: Use a set of Int_t's
		//In general: Multiple PIDs, so multiple sets: Contain within a map
		//Multiple combos: Contain maps within a set (easier, faster to search)
	set<map<Particle_t, set<Int_t> > > locUsedSoFar_MissingMass;

	//INSERT USER ANALYSIS UNIQUENESS TRACKING HERE


	// count # of tracks
	set<Int_t> trackids;   // Get_NumChargedHypos()
	for(UInt_t loc_i = 0; loc_i < Get_NumChargedHypos(); ++loc_i) {
		//Set branch array indices corresponding to this particle
		dChargedHypoWrapper->Set_ArrayIndex(loc_i);
		
		trackids.insert(dChargedHypoWrapper->Get_TrackID());
	}
	int num_tracks = trackids.size();
	//if(num_tracks > 7)
	if(num_tracks > 7)//Nian
		return 0;//Nian: if I comment out this cut, no different for the combo histogaram

	//cout << "number of tracks = " << trackids.size() << endl;
                
        dHist_combo->Fill(Get_NumCombos());

	//if(Get_NumCombos() > 4)
	//	return 0;


//	nCheck_PhiPiPiCut = 0;

	/************************************************* LOOP OVER COMBOS *************************************************/

	//Loop over combos
	for(UInt_t loc_i = 0; loc_i < Get_NumCombos(); ++loc_i)
	{
		//Set branch array indices for combo and all combo particles
		dComboWrapper->Set_ComboIndex(loc_i);

		// Is used to indicate when combos have been cut
		if(dComboWrapper->Get_IsComboCut()) // Is false when tree originally created
			continue; // Combo has been cut previously

		/********************************************** GET PARTICLE INDICES *********************************************/

		//Used for tracking uniqueness when filling histograms, and for determining unused particles

		//Step 0
		Int_t locBeamID = dComboBeamWrapper->Get_BeamID();
		Int_t locProtonTrackID = dProtonWrapper->Get_TrackID();
		Int_t locPiPlusTrackID = dPiPlusWrapper->Get_TrackID();
		Int_t locPiMinusTrackID = dPiMinusWrapper->Get_TrackID();
                Int_t locProtonBeta = dProtonWrapper->Get_Beta_Timing_Measured();
                Int_t locPiPlusBeta = dPiPlusWrapper->Get_Beta_Timing_Measured();
                Int_t locPiMinusBeta = dPiMinusWrapper->Get_Beta_Timing_Measured();



		//Step 1
		Int_t locKPlusTrackID = dKPlusWrapper->Get_TrackID();
		Int_t locKMinusTrackID = dKMinusWrapper->Get_TrackID();
                Int_t locKPlusBeta = dKPlusWrapper->Get_Beta_Timing_Measured();
                Int_t locKMinusBeta = dKMinusWrapper->Get_Beta_Timing_Measured();

		/*********************************************** GET FOUR-MOMENTUM **********************************************/

		// Get P4's: //is kinfit if kinfit performed, else is measured
		//dTargetP4 is target p4
		//Step 0
		TLorentzVector locBeamP4 = dComboBeamWrapper->Get_P4();
		TLorentzVector locProtonP4 = dProtonWrapper->Get_P4();
		TLorentzVector locPiPlusP4 = dPiPlusWrapper->Get_P4();
		TLorentzVector locPiMinusP4 = dPiMinusWrapper->Get_P4();
		//Step 1
		TLorentzVector locKPlusP4 = dKPlusWrapper->Get_P4();
		TLorentzVector locKMinusP4 = dKMinusWrapper->Get_P4();

		// Get Measured P4's:
		//Step 0
		TLorentzVector locBeamP4_Measured = dComboBeamWrapper->Get_P4_Measured();
		TLorentzVector locProtonP4_Measured = dProtonWrapper->Get_P4_Measured();
		TLorentzVector locPiPlusP4_Measured = dPiPlusWrapper->Get_P4_Measured();
		TLorentzVector locPiMinusP4_Measured = dPiMinusWrapper->Get_P4_Measured();
		//Step 1
		TLorentzVector locKPlusP4_Measured = dKPlusWrapper->Get_P4_Measured();
		TLorentzVector locKMinusP4_Measured = dKMinusWrapper->Get_P4_Measured();

		/********************************************* COMBINE FOUR-MOMENTUM ********************************************/

		// DO YOUR STUFF HERE

		// Combine 4-vectors
		TLorentzVector locMissingP4_Measured = locBeamP4_Measured + dTargetP4;
		locMissingP4_Measured -= locProtonP4_Measured + locPiPlusP4_Measured + locPiMinusP4_Measured + locKPlusP4_Measured + locKMinusP4_Measured;

		TLorentzVector locPhiP4_Measured = locKPlusP4_Measured + locKMinusP4_Measured;
		TLorentzVector locPhiP4 = locKPlusP4 + locKMinusP4;

		TLorentzVector locPhiPiPiP4_Measured = locPhiP4_Measured + locPiPlusP4_Measured + locPiMinusP4_Measured;
		TLorentzVector locPhiPiPiP4 = locPhiP4 + locPiPlusP4 + locPiMinusP4;

		TLorentzVector locPhiPiPP4_Measured = locPhiP4_Measured + locPiPlusP4_Measured;
		TLorentzVector locPhiPiPP4 = locPhiP4 + locPiPlusP4;

		TLorentzVector locPhiPiMP4_Measured = locPhiP4_Measured + locPiMinusP4_Measured;
		TLorentzVector locPhiPiMP4 = locPhiP4 + locPiMinusP4;

		TLorentzVector locPipPiMP4_Measured = locPiPlusP4_Measured + locPiMinusP4_Measured;
		TLorentzVector locPipPiMP4 = locPiPlusP4 + locPiMinusP4;

		TLorentzVector lockstP4_Measured = locKPlusP4_Measured + locPiMinusP4_Measured;
		TLorentzVector lockstP4 = locKPlusP4 + locPiMinusP4;

		TLorentzVector locaksP4_Measured = locPiPlusP4_Measured + locKMinusP4_Measured;
		TLorentzVector locaksP4 = locPiPlusP4 + locKMinusP4;

		TLorentzVector locPhiProtonP4_Measured = locPhiP4_Measured + locProtonP4_Measured;

		TLorentzVector locProtonPiPP4_Measured = locProtonP4_Measured + locPiPlusP4_Measured;
		TLorentzVector locProtonPiMP4_Measured = locProtonP4_Measured + locPiMinusP4_Measured;



		/**************************************** EXAMPLE: HISTOGRAM KINEMATICS ******************************************/

		//dHistComboKinematics->Perform_Action();
		//dHistComboPID->Perform_Action();
		//dHistComboPID_KinFit->Perform_Action();

		/**************************************** EXAMPLE: PID CUT ACTION ************************************************/
/*
		if(!dCutPIDDeltaT->Perform_Action()) {
			dComboWrapper->Set_IsComboCut(true);
			continue;
		}
*/




		/**************************************** EXAMPLE: HISTOGRAM BEAM ENERGY *****************************************/

		//Histogram beam energy (if haven't already)
		if(locUsedSoFar_BeamEnergy.find(locBeamID) == locUsedSoFar_BeamEnergy.end())
		{
			dHist_BeamEnergy->Fill(locBeamP4.E());
			locUsedSoFar_BeamEnergy.insert(locBeamID);
		}

		//if((locBeamP4.E() < 2.0) || (locBeamP4.E() > 7.0)) 
		//if((locBeamP4.E() < 7.0) || (locBeamP4.E() > 12.0)) 
		//if((locBeamP4.E() < 10.0) || (locBeamP4.E() > 12.0)) 
		//if((locBeamP4.E() < 2.0) || (locBeamP4.E() > 16.0)) 
	       	//continue; 
                //
		/************************************ EXAMPLE: HISTOGRAM MISSING MASS SQUARED ************************************/



		/************************************ EXAMPLE: HISTOGRAM MISSING MASS SQUARED ************************************/



		// Proton CDC dE/dx histogram and cut 
		double locProton_dEdx_CDC = dProtonWrapper->Get_dEdx_CDC()*1e6;
		if(locUsedSoFar_Proton.find(locProtonTrackID) == locUsedSoFar_Proton.end())
		{
		  dHist_Proton_dEdx_P_before->Fill(locProtonP4.P(), locProton_dEdx_CDC);
			locUsedSoFar_Proton.insert(locProtonTrackID);
		}
		if(locProton_dEdx_CDC < fMinProton_dEdx->Eval(locProtonP4.P())) {
			dComboWrapper->Set_IsComboCut(true);//Nian
			continue;//Nian
		}
		  dHist_Proton_dEdx_P_Measured->Fill(locProtonP4_Measured.P(), locProton_dEdx_CDC);
		  dHist_Proton_dEdx_P->Fill(locProtonP4.P(), locProton_dEdx_CDC);


		// Kaon/Pion CDC dE/dx histogram
		double locKPlus_dEdx_CDC   = dKPlusWrapper->Get_dEdx_CDC()*1e6;
		double locKMinus_dEdx_CDC  = dKMinusWrapper->Get_dEdx_CDC()*1e6;
		double locPiPlus_dEdx_CDC  = dPiPlusWrapper->Get_dEdx_CDC()*1e6;
		double locPiMinus_dEdx_CDC = dPiMinusWrapper->Get_dEdx_CDC()*1e6;

		dHist_KPlus_dEdx_P_Measured->Fill(locKPlusP4_Measured.P(), locKPlus_dEdx_CDC);
		dHist_KMinus_dEdx_P_Measured->Fill(locKMinusP4_Measured.P(), locKMinus_dEdx_CDC);
		dHist_PiPlus_dEdx_P_Measured->Fill(locPiPlusP4_Measured.P(), locPiPlus_dEdx_CDC);
		dHist_PiMinus_dEdx_P_Measured->Fill(locPiMinusP4_Measured.P(), locPiMinus_dEdx_CDC);
		dHist_KPlus_dEdx_P->Fill(locKPlusP4.P(), locKPlus_dEdx_CDC);
		dHist_KMinus_dEdx_P->Fill(locKMinusP4.P(), locKMinus_dEdx_CDC);
		dHist_PiPlus_dEdx_P->Fill(locPiPlusP4.P(), locPiPlus_dEdx_CDC);
		dHist_PiMinus_dEdx_P->Fill(locPiMinusP4.P(), locPiMinus_dEdx_CDC);


		/**************************************** EXAMPLE: HISTOGRAM BEAM ENERGY *****************************************/

		//Histogram beam energy (if haven't already)
		//if(locUsedSoFar_BeamEnergy.find(locBeamID) == locUsedSoFar_BeamEnergy.end())
		//{
		//	dHist_BeamEnergy->Fill(locBeamP4.E());
		//	locUsedSoFar_BeamEnergy.insert(locBeamID);
		//}

		/************************************ EXAMPLE: HISTOGRAM MISSING MASS SQUARED ************************************/
		
		
		// kinematic fit CL cut
		dHist_KinFitChiSq->Fill(dComboWrapper->Get_ChiSq_KinFit("")/dComboWrapper->Get_NDF_KinFit(""));
		dHist_KinFitCL->Fill(dComboWrapper->Get_ConfidenceLevel_KinFit(""));
		//if(dComboWrapper->Get_ConfidenceLevel_KinFit() > 10000.) {
		if(dComboWrapper->Get_ConfidenceLevel_KinFit("") <= 0.) {
	        //if(dComboWrapper->Get_ConfidenceLevel_KinFit() < 0.1) {
		//if(dComboWrapper->Get_ConfidenceLevel_KinFit() < -100.) {
		//if(dComboWrapper->Get_ConfidenceLevel_KinFit() < 1.e-8) {
		//if(dComboWrapper->Get_ConfidenceLevel_KinFit() < 1.e-20) {
		//if(dComboWrapper->Get_ConfidenceLevel_KinFit() < 1.e-10) {
			dComboWrapper->Set_IsComboCut(true);
			continue;
		}




		//Missing Mass Squared
		double locMissingMassSquared = locMissingP4_Measured.M2();
		//Missing Energy
		double locMissingEnergy = locMissingP4_Measured.E();

		//Uniqueness tracking: Build the map of particles used for the missing mass
			//For beam: Don't want to group with final-state photons. Instead use "Unknown" PID (not ideal, but it's easy).
		map<Particle_t, set<Int_t> > locUsedThisCombo_MissingMass;
		locUsedThisCombo_MissingMass[Unknown].insert(locBeamID); //beam
		locUsedThisCombo_MissingMass[Proton].insert(locProtonTrackID);
		locUsedThisCombo_MissingMass[PiPlus].insert(locPiPlusTrackID);
		locUsedThisCombo_MissingMass[PiMinus].insert(locPiMinusTrackID);
		locUsedThisCombo_MissingMass[KPlus].insert(locKPlusTrackID);
		locUsedThisCombo_MissingMass[KMinus].insert(locKMinusTrackID);

		//compare to what's been used so far
		if(locUsedSoFar_MissingMass.find(locUsedThisCombo_MissingMass) == locUsedSoFar_MissingMass.end())
		{

		// save Missing Energy
			dHist_MissingEnergy->Fill(locMissingEnergy);


		//Missing.E. Cut
		//if((locMissingEnergy < -0.5) || (locMissingEnergy > 0.5))
		if((locMissingEnergy < -0.6) || (locMissingEnergy > 0.6))
		//if((locMissingEnergy > -0.6) && (locMissingEnergy < 0.6))
		//if((locMissingEnergy < -0.8) || (locMissingEnergy > 0.8))
		//if((locMissingEnergy < -2.0) || (locMissingEnergy > 2.0))
			continue; 



			//unique missing mass combo: histogram it, and register this combo of particles
			dHist_MissingMassSquared->Fill(locMissingMassSquared);
			locUsedSoFar_MissingMass.insert(locUsedThisCombo_MissingMass);
			//dHist_MissingEnergy->Fill(locMissingEnergy);
		}

		//E.g. Cut
		//if((locMissingMassSquared < -0.02) || (locMissingMassSquared > 0.02))
		//if((locMissingMassSquared > -0.02) && (locMissingMassSquared < 0.02))
		//if((locMissingMassSquared > -0.03) && (locMissingMassSquared < 0.03))
		  //if((locMissingMassSquared < -0.04) || (locMissingMassSquared > 0.04))
		//if((locMissingMassSquared < -0.03) || (locMissingMassSquared > 0.03))
		 if((locMissingMassSquared < -0.02) || (locMissingMassSquared > 0.02))//Nian
			continue; //could also mark combo as cut, then save cut results to a new TTree




		//MPhiPiPi. Cut
		if((locPhiPiPiP4_Measured.M() < 1.4) || (locPhiPiPiP4_Measured.M() > 3.5)) 
		//if((locPhiPiPiP4_Measured.M() < 1.9) || (locPhiPiPiP4_Measured.M() > 3.4)) 
			continue; 

		dHist_PiPlus_TrkChiSq->Fill(dPiPlusWrapper->Get_ChiSq_Tracking()/dPiPlusWrapper->Get_NDF_Tracking());
		dHist_PiMinus_TrkChiSq->Fill(dPiMinusWrapper->Get_ChiSq_Tracking()/dPiMinusWrapper->Get_NDF_Tracking());
		dHist_KPlus_TrkChiSq->Fill(dKPlusWrapper->Get_ChiSq_Tracking()/dKPlusWrapper->Get_NDF_Tracking());
		dHist_KMinus_TrkChiSq->Fill(dKMinusWrapper->Get_ChiSq_Tracking()/dKMinusWrapper->Get_NDF_Tracking());
		dHist_Proton_TrkChiSq->Fill(dProtonWrapper->Get_ChiSq_Tracking()/dProtonWrapper->Get_NDF_Tracking());


		// track quality
		if(dPiPlusWrapper->Get_ChiSq_Tracking()/dPiPlusWrapper->Get_NDF_Tracking()>6.0)
			continue;
		if(dPiMinusWrapper->Get_ChiSq_Tracking()/dPiMinusWrapper->Get_NDF_Tracking()>6.0)
			continue;
		if(dKPlusWrapper->Get_ChiSq_Tracking()/dKPlusWrapper->Get_NDF_Tracking()>6.0)
			continue;
		if(dKMinusWrapper->Get_ChiSq_Tracking()/dKMinusWrapper->Get_NDF_Tracking()>6.0)
			continue;
		if(dProtonWrapper->Get_ChiSq_Tracking()/dProtonWrapper->Get_NDF_Tracking()>6.0)
			continue;


                // PID TIMING KPlus
                double locRFTime = dComboWrapper->Get_RFTime_Measured();
                double locPropagatedRFTime = locRFTime +
                (dKPlusWrapper->Get_X4_Measured().Z()
                                                        -
                dComboWrapper->Get_TargetCenter().Z() )/29.9792458;
                double locDeltaT = dKPlusWrapper->Get_X4_Measured().T() -
                locPropagatedRFTime;

                if(dKPlusWrapper->Get_Detector_System_Timing() == SYS_BCAL) {
                         dHist_KPlus_DeltaT_BCAL->Fill(locDeltaT);

		//KPlus Cut
		//if(( locDeltaT < -0.4) || ( locDeltaT > 0.4))
		//if(( locDeltaT < -0.5) || ( locDeltaT > 0.5))
		//if(( locDeltaT < -550.3) || ( locDeltaT > 550.3))
		//	continue; 
		double Beta =   dKPlusWrapper->Get_Beta_Timing_Measured();
               double p = fabs(locKPlusP4_Measured.P());
               double y1 = (0.045+1.20*p-0.36*p*p-0.005*p*p*p)*0.8+0.097;

               dHist_KPlus_P_vs_Beta_BCAL->Fill(fabs(locKPlusP4_Measured.P()), Beta);
	       dHist_KPlus_P_vs_DeltaT_BCAL->Fill(locKPlusP4_Measured.P(), locDeltaT);

               if(p > 1.6)
                 y1 = 0.92;
               //if(Beta < y1)
		 //continue;//Nian cancel BetaCut, 2018.07.24
               double y2 = (0.05+1.20*p-0.36*p*p-0.0025*p*p*p)*0.6+0.43;
               if(p > 1.0)
                   y2 = 0.96;
	       if(p > 1.6)
		 y2 = 50;
	       //if(Beta > y2 || Beta < y1)
		 //continue;//Nian cancel BetaCut, 2018.07.24
 	       if(( locDeltaT < -0.5) || ( locDeltaT > 0.5))
	     	continue; 
               dHist_KPlus_Beta_BCAL->Fill(Beta); 
                }

                if(dKPlusWrapper->Get_Detector_System_Timing() == SYS_TOF) {
                        dHist_KPlus_DeltaT_TOF->Fill(locDeltaT);

		//KPlus Cut
		//if(( locDeltaT < -0.1) || ( locDeltaT > 0.3))
		//if(( locDeltaT < -0.2) || ( locDeltaT > 0.2))
	       	double Betat =   dKPlusWrapper->Get_Beta_Timing_Measured();
               double pt = fabs(locKPlusP4_Measured.P());
               double y1t = 0.99;

               dHist_KPlus_P_vs_Beta_TOF->Fill(fabs(locKPlusP4_Measured.P()), Betat);
                dHist_KPlus_P_vs_DeltaT_TOF->Fill(locKPlusP4_Measured.P(), locDeltaT);

               if(pt > 3.0)
                 y1t = 50;
               //if(Betat > y1t)
		 //continue;//Nian cancel BetaCut, 2018.07.24
		if(( locDeltaT < -0.3) || ( locDeltaT > 0.3))
		//if(( locDeltaT < -550.2) || ( locDeltaT > 550.3))
		 continue;
               dHist_KPlus_Beta_TOF->Fill(Betat); 
                }


                // PID TIMING KMinus
                locRFTime = dComboWrapper->Get_RFTime_Measured();
                locPropagatedRFTime = locRFTime +
                (dKMinusWrapper->Get_X4_Measured().Z()
                                                        -
                dComboWrapper->Get_TargetCenter().Z() )/29.9792458;
                locDeltaT = dKMinusWrapper->Get_X4_Measured().T() -
                locPropagatedRFTime;

                if(dKMinusWrapper->Get_Detector_System_Timing() == SYS_BCAL) {
                         dHist_KMinus_DeltaT_BCAL->Fill(locDeltaT);

			 //dHist_KMinus_p_DeltaT_BCAL->Fill(locKMinusP4_Measured.P(), locDeltaT);
		//KMinus Cut
		//  if(  (( locDeltaT > 0.4) && ( (locKMinusP4_Measured.P() < 1.5)))
		//       || (( locDeltaT > 0.4) && ( (locKMinusP4_Measured.P() > 1.5))) )
		//	continue; 
		//   if(  (( locDeltaT < -0.4) && ( (locKMinusP4_Measured.P() < 1.5)))
		//       || (( locDeltaT < -0.3) && ( (locKMinusP4_Measured.P() > 1.5))) )
		//  	continue; 
               double pkm = fabs(locKMinusP4_Measured.P());
               double y2km = (0.05+1.20*pkm-0.36*pkm*pkm-0.0025*pkm*pkm*pkm)*0.6+0.43;
  		double Beta_km =   dKMinusWrapper->Get_Beta_Timing_Measured();

               dHist_KMinus_P_vs_Beta_BCAL->Fill(fabs(locKMinusP4_Measured.P()), Beta_km);
                 dHist_KMinus_P_vs_DeltaT_BCAL->Fill(locKMinusP4_Measured.P(), locDeltaT);

               if(pkm > 1.0)
                   y2km = 0.96;
	       if(pkm > 1.6)
		 y2km = 50;
	       //if(Beta_km > y2km)
		 //continue;//Nian cancel BetaCut, 2018.07.24
 	       if(( locDeltaT < -0.5) || ( locDeltaT > 0.5))
	       continue; 
               dHist_KMinus_Beta_BCAL->Fill(Beta_km); 
 
               }

                if(dKMinusWrapper->Get_Detector_System_Timing() == SYS_TOF) {
                        dHist_KMinus_DeltaT_TOF->Fill(locDeltaT);

		//KMinus Cut
		//if(( locDeltaT < -0.1) || ( locDeltaT > 0.3))
		//if(( locDeltaT < -0.2) || ( locDeltaT > 0.2))
                //
                //
		//  if(  (( locDeltaT > 0.2) && ( (locKMinusP4_Measured.P() < 3.0)))
		//       || (( locDeltaT > 0.2) && ( (locKMinusP4_Measured.P() > 3.0))) )
		//	continue; 
		//  if(  (( locDeltaT < -0.2) && ( (locKMinusP4_Measured.P() < 3.0)))
		//       || (( locDeltaT < -0.1) && ( (locKMinusP4_Measured.P() > 3.0))) )
		//	continue;
                //
                //
		  //    if(( locDeltaT < -550.2) || ( locDeltaT > 550.3))
		  //	continue; 
	       	double Betat_km =   dKMinusWrapper->Get_Beta_Timing_Measured();
               double ptkm = fabs(locKMinusP4_Measured.P());
               double y1tkm = 0.99;

               dHist_KMinus_P_vs_Beta_TOF->Fill(fabs(locKMinusP4_Measured.P()), Betat_km);
                dHist_KMinus_P_vs_DeltaT_TOF->Fill(locKMinusP4_Measured.P(), locDeltaT);

               if(ptkm > 3.0)
                 y1tkm = 50;
               //if(Betat_km > y1tkm)
		 //continue;//Nian cancel BetaCut, 2018.07.24
		if(( locDeltaT < -0.3) || ( locDeltaT > 0.3))
		 continue;
               dHist_KMinus_Beta_TOF->Fill(Betat_km); 
                }
 
		//PKp Cut
		//if((locKPlusP4_Measured.P() < 1.0) || (locKPlusP4_Measured.P() > 222.9)) 
		//	continue; 
		//PKm Cut
		//if((locKMinusP4_Measured.P() < 1.0) || (locKMinusP4_Measured.P() > 222.9)) 
		//	continue; 



                // PID TIMING Proton
                locRFTime = dComboWrapper->Get_RFTime_Measured();
                locPropagatedRFTime = locRFTime +
                (dProtonWrapper->Get_X4_Measured().Z()
                                                        -
                dComboWrapper->Get_TargetCenter().Z() )/29.9792458;
                locDeltaT = dProtonWrapper->Get_X4_Measured().T() -
                locPropagatedRFTime;

                if(dProtonWrapper->Get_Detector_System_Timing() == SYS_BCAL) {
                         dHist_Proton_DeltaT_BCAL->Fill(locDeltaT);

		//Proton Cut
		//if(( locDeltaT < -0.5) || ( locDeltaT > 0.5))
		//		if(( locDeltaT < -0.5) || ( locDeltaT > 0.5))
		  //  if(( locDeltaT < -550.6) || ( locDeltaT > 550.6))
		//	continue;
		// if(  (( locDeltaT > 0.5) && ( (locProtonP4_Measured.P() < 3.0)))
		//       || (( locDeltaT > 0.3) && ( (locProtonP4_Measured.P() > 3.0))) )
		//	continue; 
		//  if(  (( locDeltaT < -0.4) && ( (locProtonP4_Measured.P() < 2.0)))
		//       || (( locDeltaT < -0.3) && ( (locProtonP4_Measured.P() > 2.0))) )
		//	continue; 
		double Beta_pr =   dProtonWrapper->Get_Beta_Timing_Measured();
               double ppr = fabs(locProtonP4_Measured.P());
               double y1pr = 0.94;

               dHist_Proton_P_vs_Beta_BCAL->Fill(fabs(locProtonP4_Measured.P()), Beta_pr);
                dHist_Proton_P_vs_DeltaT_BCAL->Fill(locProtonP4_Measured.P(), locDeltaT);

               //if(Beta_pr > y1pr)
		 //continue;//Nian cancel BetaCut, 2018.07.24
		if(( locDeltaT < -0.5) || ( locDeltaT > 0.5))
		 continue;
               dHist_Proton_Beta_BCAL->Fill(Beta_pr); 

                }

                if(dProtonWrapper->Get_Detector_System_Timing() == SYS_TOF) {
                        dHist_Proton_DeltaT_TOF->Fill(locDeltaT);

		//Proton Cut
		//if(( locDeltaT < -0.2) || ( locDeltaT > 0.2))
		//		  if(  (( locDeltaT > 0.3) && ( (locProtonP4_Measured.P() < 13.0)))
		//	continue; 
		//  if(  (( locDeltaT > 0.4) && ( (locProtonP4_Measured.P() < 2.0)))
		//       || (( locDeltaT > 0.4) && ( (locProtonP4_Measured.P() > 2.0))) )
		//	continue; 
		//  if(  (( locDeltaT < -0.4) && ( (locProtonP4_Measured.P() < 2.0)))
		//       || (( locDeltaT < -0.3) && ( (locProtonP4_Measured.P() > 2.0))) )
		//	continue; 
	       	double Betat_pr =   dProtonWrapper->Get_Beta_Timing_Measured();
               double ptpr = fabs(locProtonP4_Measured.P());
               double y1tpr = 0.965;

               dHist_Proton_P_vs_Beta_TOF->Fill(fabs(locProtonP4_Measured.P()), Betat_pr);
               dHist_Proton_P_vs_DeltaT_TOF->Fill(locProtonP4_Measured.P(), locDeltaT);

               if(ptpr > 3.0)
                 y1tpr = 0.99;
               //if(Betat_pr > y1tpr)
		 //continue;//Nian cancel BetaCut, 2018.07.24
		if(( locDeltaT < -0.5) || ( locDeltaT > 0.5))
		 continue;
               dHist_Proton_Beta_TOF->Fill(Betat_pr); 

                }


                // PID TIMING PiPlus
                locRFTime = dComboWrapper->Get_RFTime_Measured();
                locPropagatedRFTime = locRFTime +
                (dPiPlusWrapper->Get_X4_Measured().Z()
                                                        -
                dComboWrapper->Get_TargetCenter().Z() )/29.9792458;
                locDeltaT = dPiPlusWrapper->Get_X4_Measured().T() -
                locPropagatedRFTime;

                if(dPiPlusWrapper->Get_Detector_System_Timing() == SYS_BCAL) {
                         dHist_PiPlus_DeltaT_BCAL->Fill(locDeltaT);

		//PiPlus Cut
		//if(( locDeltaT < -0.5) || ( locDeltaT > 0.5))
		//    if(( locDeltaT < -550.6) || ( locDeltaT > 550.6))
		//	continue; 
		//if(  (( locDeltaT > 0.5) && ( (locPiPlusP4_Measured.P() < 1.2))) )
		       //     || (( locDeltaT > 0.3) && ( (locPiPlusP4_Measured.P() > 1.2))) )
		//	continue; 
			//  if(  (( locDeltaT < -0.5) && ( (locPiPlusP4_Measured.P() < 12.5))))
               double ppip = fabs(locPiPlusP4_Measured.P());
               double y1pip = 0.9;
		double Beta_pip =   dPiPlusWrapper->Get_Beta_Timing_Measured();

               dHist_PiPlus_P_vs_Beta_BCAL->Fill(fabs(locPiPlusP4_Measured.P()), Beta_pip);
                 dHist_PiPlus_P_vs_DeltaT_BCAL->Fill(locPiPlusP4_Measured.P(), locDeltaT);

	       //if((Beta_pip < y1pip) && (ppip > 0.6))
 		 //continue;//Nian cancel BetaCut, 2018.07.24
		if(( locDeltaT < -0.5) || ( locDeltaT > 0.5))
        	continue; 
               dHist_PiPlus_Beta_BCAL->Fill(Beta_pip); 
                }

                if(dPiPlusWrapper->Get_Detector_System_Timing() == SYS_TOF) {
                        dHist_PiPlus_DeltaT_TOF->Fill(locDeltaT);

		//PiPlus Cut
		//		if(( locDeltaT < -1.0) || ( locDeltaT > 1.0))
		//		if(( locDeltaT < -0.4) || ( locDeltaT > 0.3))
		//		  if(( locDeltaT < -550.2) || ( locDeltaT > 550.4))
		//	continue; 

		//  if(  (( locDeltaT > 0.2) && ( (locPiPlusP4_Measured.P() < 3.0)))
		//       || (( locDeltaT > 0.1) && ( (locPiPlusP4_Measured.P() > 3.0))) )
		//	continue; 
		//  if(  (( locDeltaT < -0.2) && ( (locPiPlusP4_Measured.P() < 12.5))))
		       //      || (( locDeltaT < -0.2) && ( (locPiPlusP4_Measured.P() > 2.5))) )
		//	continue; 


		double Betat_pip =   dPiPlusWrapper->Get_Beta_Timing_Measured();
               double ppip = fabs(locPiPlusP4_Measured.P());
               double y1pipt = 0.985;

               dHist_PiPlus_P_vs_Beta_TOF->Fill(fabs(locPiPlusP4_Measured.P()), Betat_pip);
               dHist_PiPlus_P_vs_DeltaT_TOF->Fill(locPiPlusP4_Measured.P(), locDeltaT);

	       //if((Betat_pip < y1pipt) && (ppip > 0.8))
 		 //continue;//Nian cancel BetaCut, 2018.07.24
		if(( locDeltaT < -0.5) || ( locDeltaT > 0.5))
        	continue; 
               dHist_PiPlus_Beta_TOF->Fill(Betat_pip); 
 
                 }

 
                // PID TIMING PiMinus
                locRFTime = dComboWrapper->Get_RFTime_Measured();
                locPropagatedRFTime = locRFTime +
                (dPiMinusWrapper->Get_X4_Measured().Z()
                                                        -
                dComboWrapper->Get_TargetCenter().Z() )/29.9792458;
                locDeltaT = dPiMinusWrapper->Get_X4_Measured().T() -
                locPropagatedRFTime;

                if(dPiMinusWrapper->Get_Detector_System_Timing() == SYS_BCAL) {
                         dHist_PiMinus_DeltaT_BCAL->Fill(locDeltaT);

		//PiMinus Cut
		//if(( locDeltaT < -0.5) || ( locDeltaT > 0.5))
		  //  if(( locDeltaT < -550.6) || ( locDeltaT > 550.6))
		//	continue; 

                double ppim = fabs(locPiMinusP4_Measured.P());
               double y1pim = 0.9;
		double Beta_pim =   dPiMinusWrapper->Get_Beta_Timing_Measured();

               dHist_PiMinus_P_vs_Beta_BCAL->Fill(fabs(locPiMinusP4_Measured.P()), Beta_pim);
                 dHist_PiMinus_P_vs_DeltaT_BCAL->Fill(locPiMinusP4_Measured.P(), locDeltaT);

	       //if((Beta_pim < y1pim) && (ppim > 0.6))
 		 //continue;//Nian cancel BetaCut, 2018.07.24
		if(( locDeltaT < -0.5) || ( locDeltaT > 0.5))
        	continue; 
               dHist_PiMinus_Beta_BCAL->Fill(Beta_pim); 
               }

                if(dPiMinusWrapper->Get_Detector_System_Timing() == SYS_TOF) {
                        dHist_PiMinus_DeltaT_TOF->Fill(locDeltaT);

		//PiMinus Cut
		//if(( locDeltaT < -0.3) || ( locDeltaT > 0.3))
		//  if(( locDeltaT < -550.2) || ( locDeltaT > 550.4))
		//	continue;
		//  if(  (( locDeltaT > 0.2) && ( (locPiMinusP4_Measured.P() < 3.0)))
		//       || (( locDeltaT > 0.1) && ( (locPiMinusP4_Measured.P() > 3.0))) )
		//	continue; 
		//  if(  (( locDeltaT < -0.2) && ( (locPiMinusP4_Measured.P() < 12.5))))
		       //     || (( locDeltaT < -0.2) && ( (locPiMinusP4_Measured.P() > 2.5))) )
		//	continue; 




	       	double Betat_pim =   dPiMinusWrapper->Get_Beta_Timing_Measured();
               double ppim = fabs(locPiMinusP4_Measured.P());
               double y1pimt = 0.985;

               dHist_PiMinus_P_vs_Beta_TOF->Fill(fabs(locPiMinusP4_Measured.P()), Betat_pim);
                dHist_PiMinus_P_vs_DeltaT_TOF->Fill(locPiMinusP4_Measured.P(), locDeltaT);

	       //if((Betat_pim < y1pimt) && (ppim > 0.8))
 		 //continue;//Nian cancel BetaCut, 2018.07.24
		if(( locDeltaT < -0.5) || ( locDeltaT > 0.5))
        	continue; 
              dHist_PiMinus_Beta_TOF->Fill(Betat_pim); 

                 }






		//MPhiPiPi. Cut
		//if((locPhiPiPiP4_Measured.M() < 2.5) || (locPhiPiPiP4_Measured.M() > 2.9)) 
		//	continue; 

		//MPhiPiPi. Cut
		//if((locPhiPiPiP4_Measured.M() < 2.05) || (locPhiPiPiP4_Measured.M() > 2.20)) 
		//	continue; 

		//Mkst Cut
		//if((lockstP4_Measured.M() > 0.86) && (lockstP4_Measured.M() < 0.94)) 
		//	continue; 

		//Maks Cut
		//if((locaksP4_Measured.M() > 0.86) && (locaksP4_Measured.M() < 0.94)) 
		//	continue; 
		
		
		/**************************************** EXAMPLE: HISTOGRAM BEAM ENERGY *****************************************/

		//Histogram beam energy (if haven't already)
		//if(locUsedSoFar_BeamEnergy.find(locBeamID) == locUsedSoFar_BeamEnergy.end())
		//{
		//	dHist_BeamEnergy->Fill(locBeamP4.E());
		//	locUsedSoFar_BeamEnergy.insert(locBeamID);
		//}

		/***********************************************************************/


		//if((locBeamP4.E() < 2.0) || (locBeamP4.E() > 7.0)) 
		//if((locBeamP4.E() < 7.0) || (locBeamP4.E() > 10.0)) 
		//if((locBeamP4.E() < 10.0) || (locBeamP4.E() > 12.0)) 
		//if((locBeamP4.E() < 2.0) || (locBeamP4.E() > 16.0)) 
	       	//continue; 

		//PKp Cut
		//if((locKPlusP4_Measured.P() < 1.0) || (locKPlusP4_Measured.P() > 222.9)) 
		//	continue; 
		//PKm Cut
		//if((locKMinusP4_Measured.P() < 1.0) || (locKMinusP4_Measured.P() > 222.9)) 
		//	continue; 
          


	       		// save phi mass
		dHist_Mphi->Fill(locPhiP4.M());
		dHist_Mphi_measured->Fill(locPhiP4_Measured.M());
/*
////////////////Begin: MPhiPiPi-----100MeV/bin
		if((locPhiPiPiP4_Measured.M() > 1.40) && (locPhiPiPiP4_Measured.M() < 1.50)) {
 		dHist_Mphi_measured1->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 1.50) && (locPhiPiPiP4_Measured.M() < 1.60)) {
 		dHist_Mphi_measured2->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 1.60) && (locPhiPiPiP4_Measured.M() < 1.70)) {
 		dHist_Mphi_measured3->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 1.70) && (locPhiPiPiP4_Measured.M() < 1.80)) {
 		dHist_Mphi_measured4->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 1.80) && (locPhiPiPiP4_Measured.M() < 1.90)) {
 		dHist_Mphi_measured5->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 1.90) && (locPhiPiPiP4_Measured.M() < 2.00)) {
 		dHist_Mphi_measured6->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.00) && (locPhiPiPiP4_Measured.M() < 2.10)) {
 		dHist_Mphi_measured7->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.10) && (locPhiPiPiP4_Measured.M() < 2.20)) {
 		dHist_Mphi_measured8->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.20) && (locPhiPiPiP4_Measured.M() < 2.30)) {
 		dHist_Mphi_measured9->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.30) && (locPhiPiPiP4_Measured.M() < 2.40)) {
 		dHist_Mphi_measured10->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.40) && (locPhiPiPiP4_Measured.M() < 2.50)) {
 		dHist_Mphi_measured11->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.50) && (locPhiPiPiP4_Measured.M() < 2.60)) {
 		dHist_Mphi_measured12->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.60) && (locPhiPiPiP4_Measured.M() < 2.70)) {
 		dHist_Mphi_measured13->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.70) && (locPhiPiPiP4_Measured.M() < 2.80)) {
 		dHist_Mphi_measured14->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.80) && (locPhiPiPiP4_Measured.M() < 2.90)) {
 		dHist_Mphi_measured15->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.90) && (locPhiPiPiP4_Measured.M() < 3.00)) {
 		dHist_Mphi_measured16->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 3.00) && (locPhiPiPiP4_Measured.M() < 3.10)) {
 		dHist_Mphi_measured17->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 3.10) && (locPhiPiPiP4_Measured.M() < 3.20)) {
 		dHist_Mphi_measured18->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 3.20) && (locPhiPiPiP4_Measured.M() < 3.30)) {
 		dHist_Mphi_measured19->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 3.30) && (locPhiPiPiP4_Measured.M() < 3.40)) {
 		dHist_Mphi_measured20->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 3.40) && (locPhiPiPiP4_Measured.M() < 3.50)) {
 		dHist_Mphi_measured21->Fill(locPhiP4_Measured.M());
		}
////////////////End: MPhiPiPi-----100MeV/bin
*/

/*		
////////////////Begin: MPhiPiPi-----75MeV/bin
		if((locPhiPiPiP4_Measured.M() > 1.40) && (locPhiPiPiP4_Measured.M() < 1.475)) {
 		dHist_Mphi_measured1->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 1.475) && (locPhiPiPiP4_Measured.M() < 1.55)) {
 		dHist_Mphi_measured2->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 1.55) && (locPhiPiPiP4_Measured.M() < 1.625)) {
 		dHist_Mphi_measured3->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 1.625) && (locPhiPiPiP4_Measured.M() < 1.70)) {
 		dHist_Mphi_measured4->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 1.70) && (locPhiPiPiP4_Measured.M() < 1.775)) {
 		dHist_Mphi_measured5->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 1.775) && (locPhiPiPiP4_Measured.M() < 1.85)) {
 		dHist_Mphi_measured6->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 1.85) && (locPhiPiPiP4_Measured.M() < 1.925)) {
 		dHist_Mphi_measured7->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 1.925) && (locPhiPiPiP4_Measured.M() < 2.0)) {
 		dHist_Mphi_measured8->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.0) && (locPhiPiPiP4_Measured.M() < 2.075)) {
 		dHist_Mphi_measured9->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.075) && (locPhiPiPiP4_Measured.M() < 2.15)) {
 		dHist_Mphi_measured10->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.15) && (locPhiPiPiP4_Measured.M() < 2.225)) {
 		dHist_Mphi_measured11->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.225) && (locPhiPiPiP4_Measured.M() < 2.3)) {
 		dHist_Mphi_measured12->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.3) && (locPhiPiPiP4_Measured.M() < 2.375)) {
 		dHist_Mphi_measured13->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.375) && (locPhiPiPiP4_Measured.M() < 2.45)) {
 		dHist_Mphi_measured14->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.45) && (locPhiPiPiP4_Measured.M() < 2.525)) {
 		dHist_Mphi_measured15->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.525) && (locPhiPiPiP4_Measured.M() < 2.6)) {
 		dHist_Mphi_measured16->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.6) && (locPhiPiPiP4_Measured.M() < 2.675)) {
 		dHist_Mphi_measured17->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.675) && (locPhiPiPiP4_Measured.M() < 2.75)) {
 		dHist_Mphi_measured18->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.75) && (locPhiPiPiP4_Measured.M() < 2.825)) {
 		dHist_Mphi_measured19->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.825) && (locPhiPiPiP4_Measured.M() < 2.9)) {
 		dHist_Mphi_measured20->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.9) && (locPhiPiPiP4_Measured.M() < 2.975)) {
 		dHist_Mphi_measured21->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 2.975) && (locPhiPiPiP4_Measured.M() < 3.05)) {
 		dHist_Mphi_measured22->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 3.05) && (locPhiPiPiP4_Measured.M() < 3.125)) {
 		dHist_Mphi_measured23->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 3.125) && (locPhiPiPiP4_Measured.M() < 3.2)) {
 		dHist_Mphi_measured24->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 3.2) && (locPhiPiPiP4_Measured.M() < 3.275)) {
 		dHist_Mphi_measured25->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 3.275) && (locPhiPiPiP4_Measured.M() < 3.35)) {
 		dHist_Mphi_measured26->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 3.35) && (locPhiPiPiP4_Measured.M() < 3.425)) {
 		dHist_Mphi_measured27->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 3.425) && (locPhiPiPiP4_Measured.M() < 3.5)) {
 		dHist_Mphi_measured28->Fill(locPhiP4_Measured.M());
		}
////////////////End: MPhiPiPi-----75MeV/bin
*/


////////////////Begin: MPhiPiPi-----50MeV/bin
		if((locPhiPiPiP4_Measured.M() > 1.40) && (locPhiPiPiP4_Measured.M() < 1.45)) {
 		dHist_Mphi_measured1->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 1.45) && (locPhiPiPiP4_Measured.M() < 1.50)) {
 		dHist_Mphi_measured2->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 1.50) && (locPhiPiPiP4_Measured.M() < 1.55)) {
 		dHist_Mphi_measured3->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 1.55) && (locPhiPiPiP4_Measured.M() < 1.60)) {
 		dHist_Mphi_measured4->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 1.60) && (locPhiPiPiP4_Measured.M() < 1.65)) {
 		dHist_Mphi_measured5->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 1.65) && (locPhiPiPiP4_Measured.M() < 1.70)) {
 		dHist_Mphi_measured6->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 1.70) && (locPhiPiPiP4_Measured.M() < 1.75)) {
 		dHist_Mphi_measured7->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 1.75) && (locPhiPiPiP4_Measured.M() < 1.80)) {
 		dHist_Mphi_measured8->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 1.80) && (locPhiPiPiP4_Measured.M() < 1.85)) {
 		dHist_Mphi_measured9->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 1.85) && (locPhiPiPiP4_Measured.M() < 1.90)) {
 		dHist_Mphi_measured10->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 1.90) && (locPhiPiPiP4_Measured.M() < 1.95)) {
 		dHist_Mphi_measured11->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 1.95) && (locPhiPiPiP4_Measured.M() < 2.00)) {
 		dHist_Mphi_measured12->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.00) && (locPhiPiPiP4_Measured.M() < 2.05)) {
 		dHist_Mphi_measured13->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.05) && (locPhiPiPiP4_Measured.M() < 2.10)) {
 		dHist_Mphi_measured14->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.10) && (locPhiPiPiP4_Measured.M() < 2.15)) {
 		dHist_Mphi_measured15->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.15) && (locPhiPiPiP4_Measured.M() < 2.20)) {
 		dHist_Mphi_measured16->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.20) && (locPhiPiPiP4_Measured.M() < 2.25)) {
 		dHist_Mphi_measured17->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.25) && (locPhiPiPiP4_Measured.M() < 2.30)) {
 		dHist_Mphi_measured18->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.30) && (locPhiPiPiP4_Measured.M() < 2.35)) {
 		dHist_Mphi_measured19->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.35) && (locPhiPiPiP4_Measured.M() < 2.40)) {
 		dHist_Mphi_measured20->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.40) && (locPhiPiPiP4_Measured.M() < 2.45)) {
 		dHist_Mphi_measured21->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 2.45) && (locPhiPiPiP4_Measured.M() < 2.50)) {
 		dHist_Mphi_measured22->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 2.50) && (locPhiPiPiP4_Measured.M() < 2.55)) {
 		dHist_Mphi_measured23->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 2.55) && (locPhiPiPiP4_Measured.M() < 2.60)) {
 		dHist_Mphi_measured24->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 2.60) && (locPhiPiPiP4_Measured.M() < 2.65)) {
 		dHist_Mphi_measured25->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 2.65) && (locPhiPiPiP4_Measured.M() < 2.70)) {
 		dHist_Mphi_measured26->Fill(locPhiP4_Measured.M());
		}
		if((locPhiPiPiP4_Measured.M() > 2.70) && (locPhiPiPiP4_Measured.M() < 2.75)) {
 		dHist_Mphi_measured27->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.75) && (locPhiPiPiP4_Measured.M() < 2.80)) {
 		dHist_Mphi_measured28->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.80) && (locPhiPiPiP4_Measured.M() < 2.85)) {
 		dHist_Mphi_measured29->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.85) && (locPhiPiPiP4_Measured.M() < 2.90)) {
 		dHist_Mphi_measured30->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.90) && (locPhiPiPiP4_Measured.M() < 2.95)) {
 		dHist_Mphi_measured31->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 2.95) && (locPhiPiPiP4_Measured.M() < 3.00)) {
 		dHist_Mphi_measured32->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 3.00) && (locPhiPiPiP4_Measured.M() < 3.05)) {
 		dHist_Mphi_measured33->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 3.05) && (locPhiPiPiP4_Measured.M() < 3.10)) {
 		dHist_Mphi_measured34->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 3.10) && (locPhiPiPiP4_Measured.M() < 3.15)) {
 		dHist_Mphi_measured35->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 3.15) && (locPhiPiPiP4_Measured.M() < 3.20)) {
 		dHist_Mphi_measured36->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 3.20) && (locPhiPiPiP4_Measured.M() < 3.25)) {
 		dHist_Mphi_measured37->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 3.25) && (locPhiPiPiP4_Measured.M() < 3.30)) {
 		dHist_Mphi_measured38->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 3.30) && (locPhiPiPiP4_Measured.M() < 3.35)) {
 		dHist_Mphi_measured39->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 3.35) && (locPhiPiPiP4_Measured.M() < 3.40)) {
 		dHist_Mphi_measured40->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 3.40) && (locPhiPiPiP4_Measured.M() < 3.45)) {
 		dHist_Mphi_measured41->Fill(locPhiP4_Measured.M());
		}
 		if((locPhiPiPiP4_Measured.M() > 3.45) && (locPhiPiPiP4_Measured.M() < 3.50)) {
 		dHist_Mphi_measured42->Fill(locPhiP4_Measured.M());
		}
////////////////End: MPhiPiPi-----50MeV/bin


		// cut on phi mass
		if(locPhiP4_Measured.M() < 1.01 || locPhiP4_Measured.M() > 1.03) {
		  //if(locPhiP4_Measured.M() < 1.014 || locPhiP4_Measured.M() > 1.026) {
		//if(locPhiP4_Measured.M() < 1.04 || locPhiP4_Measured.M() > 1.07) {
		//if(locPhiP4_Measured.M() < 1.04 || locPhiP4_Measured.M() > 1.06) {
		//if(locPhiP4_Measured.M() < 1.04 || locPhiP4_Measured.M() > 1.10) {
		//if(locPhiP4_Measured.M() < 0.99 || locPhiP4_Measured.M() > 1.01) {
		//if(locPhiP4_Measured.M() < 0.99 || locPhiP4_Measured.M() > 1.10) {
		//if(locPhiP4_Measured.M() > 1.005 && locPhiP4_Measured.M() > 1.035) {
		//if(locPhiP4_Measured.M() < 0.98 || locPhiP4_Measured.M() > 1.2) {
		//if(locPhiP4_Measured.M() < 1.00 || locPhiP4_Measured.M() > 1.04) {
		dComboWrapper->Set_IsComboCut(true);
                        continue;
		}

		//check plots with cuts on phi(1.01, 1.03) and phipipi(2.50, 2.80)
		if((locPhiPiPiP4_Measured.M() > 2.50) && (locPhiPiPiP4_Measured.M() < 2.80) && (locPhiP4_Measured.M() > 1.01) && (locPhiP4_Measured.M() < 1.03)) {

//		nCheck_PhiPiPiCut++;

		dHist_Proton_dEdx_P_PhiPiPiCut_Measured->Fill(locProtonP4_Measured.P(), locProton_dEdx_CDC);
		dHist_KPlus_dEdx_P_PhiPiPiCut_Measured->Fill(locKPlusP4_Measured.P(), locKPlus_dEdx_CDC);
		dHist_KMinus_dEdx_P_PhiPiPiCut_Measured->Fill(locKMinusP4_Measured.P(), locKMinus_dEdx_CDC);
		dHist_PiPlus_dEdx_P_PhiPiPiCut_Measured->Fill(locPiPlusP4_Measured.P(), locPiPlus_dEdx_CDC);
		dHist_PiMinus_dEdx_P_PhiPiPiCut_Measured->Fill(locPiMinusP4_Measured.P(), locPiMinus_dEdx_CDC);
		dHist_Proton_dEdx_P_PhiPiPiCut->Fill(locProtonP4.P(), locProton_dEdx_CDC);
		dHist_KPlus_dEdx_P_PhiPiPiCut->Fill(locKPlusP4.P(), locKPlus_dEdx_CDC);
		dHist_KMinus_dEdx_P_PhiPiPiCut->Fill(locKMinusP4.P(), locKMinus_dEdx_CDC);
		dHist_PiPlus_dEdx_P_PhiPiPiCut->Fill(locPiPlusP4.P(), locPiPlus_dEdx_CDC);
		dHist_PiMinus_dEdx_P_PhiPiPiCut->Fill(locPiMinusP4.P(), locPiMinus_dEdx_CDC);

		dHist_Proton_Theta_P_PhiPiPiCut_Measured->Fill(locProtonP4_Measured.Theta()*57.,locProtonP4_Measured.P());
		dHist_KPlus_Theta_P_PhiPiPiCut_Measured->Fill(locKPlusP4_Measured.Theta()*57.,locKPlusP4_Measured.P());
		dHist_KMinus_Theta_P_PhiPiPiCut_Measured->Fill(locKMinusP4_Measured.Theta()*57.,locKMinusP4_Measured.P());
		dHist_PiPlus_Theta_P_PhiPiPiCut_Measured->Fill(locPiPlusP4_Measured.Theta()*57.,locPiPlusP4_Measured.P());
		dHist_PiMinus_Theta_P_PhiPiPiCut_Measured->Fill(locPiMinusP4_Measured.Theta()*57.,locPiMinusP4_Measured.P());
		dHist_Proton_Theta_P_PhiPiPiCut->Fill(locProtonP4.Theta()*57.,locProtonP4.P());
		dHist_KPlus_Theta_P_PhiPiPiCut->Fill(locKPlusP4.Theta()*57.,locKPlusP4.P());
		dHist_KMinus_Theta_P_PhiPiPiCut->Fill(locKMinusP4.Theta()*57.,locKMinusP4.P());
		dHist_PiPlus_Theta_P_PhiPiPiCut->Fill(locPiPlusP4.Theta()*57.,locPiPlusP4.P());
		dHist_PiMinus_Theta_P_PhiPiPiCut->Fill(locPiMinusP4.Theta()*57.,locPiMinusP4.P());

		Double_t a_Proton_KPlus = 57*(locProtonP4_Measured.Angle(locKPlusP4_Measured.Vect()));//degree
		Double_t a_Proton_KMinus = 57*(locProtonP4_Measured.Angle(locKMinusP4_Measured.Vect()));//degree
		Double_t a_Proton_PiPlus = 57*(locProtonP4_Measured.Angle(locPiPlusP4_Measured.Vect()));//degree
		Double_t a_Proton_PiMinus = 57*(locProtonP4_Measured.Angle(locPiMinusP4_Measured.Vect()));//degree
		Double_t a_KPlus_KMinus = 57*(locKPlusP4_Measured.Angle(locKMinusP4_Measured.Vect()));//degree
		Double_t a_KPlus_PiPlus = 57*(locKPlusP4_Measured.Angle(locPiPlusP4_Measured.Vect()));//degree
		Double_t a_KPlus_PiMinus = 57*(locKPlusP4_Measured.Angle(locPiMinusP4_Measured.Vect()));//degree
		Double_t a_KMinus_PiPlus = 57*(locKMinusP4_Measured.Angle(locPiPlusP4_Measured.Vect()));//degree
		Double_t a_KMinus_PiMinus = 57*(locKMinusP4_Measured.Angle(locPiMinusP4_Measured.Vect()));//degree
		Double_t a_PiPlus_PiMinus = 57*(locPiPlusP4_Measured.Angle(locPiMinusP4_Measured.Vect()));//degree
		dHist_Proton_KPlus_Angle->Fill(a_Proton_KPlus);
		dHist_Proton_KMinus_Angle->Fill(a_Proton_KMinus);
		dHist_Proton_PiPlus_Angle->Fill(a_Proton_PiPlus);
		dHist_Proton_PiMinus_Angle->Fill(a_Proton_PiMinus);
		dHist_KPlus_KMinus_Angle->Fill(a_KPlus_KMinus);
		dHist_KPlus_PiPlus_Angle->Fill(a_KPlus_PiPlus);
		dHist_KPlus_PiMinus_Angle->Fill(a_KPlus_PiMinus);
		dHist_KMinus_PiPlus_Angle->Fill(a_KMinus_PiPlus);
		dHist_KMinus_PiMinus_Angle->Fill(a_KMinus_PiMinus);
		dHist_PiPlus_PiMinus_Angle->Fill(a_PiPlus_PiMinus);

		dHist_Proton_P_PhiPiPiCut->Fill(locProtonP4_Measured.P());
		dHist_KPlus_P_PhiPiPiCut->Fill(locKPlusP4_Measured.P());
		dHist_KMinus_P_PhiPiPiCut->Fill(locKMinusP4_Measured.P());
		dHist_PiPlus_P_PhiPiPiCut->Fill(locPiPlusP4_Measured.P());
		dHist_PiMinus_P_PhiPiPiCut->Fill(locPiMinusP4_Measured.P());

		dHist_Proton_Theta_PhiPiPiCut->Fill(locProtonP4_Measured.Theta()*57.);
		dHist_KPlus_Theta_PhiPiPiCut->Fill(locKPlusP4_Measured.Theta()*57.);
		dHist_KMinus_Theta_PhiPiPiCut->Fill(locKMinusP4_Measured.Theta()*57.);
		dHist_PiPlus_Theta_PhiPiPiCut->Fill(locPiPlusP4_Measured.Theta()*57.);
		dHist_PiMinus_Theta_PhiPiPiCut->Fill(locPiMinusP4_Measured.Theta()*57.);

		double locRFTime_Proton = dComboWrapper->Get_RFTime_Measured();
		double locRFTime_KPlus  = dComboWrapper->Get_RFTime_Measured();
		double locRFTime_KMinus = dComboWrapper->Get_RFTime_Measured();
		double locRFTime_PiPlus = dComboWrapper->Get_RFTime_Measured();
		double locRFTime_PiMinus= dComboWrapper->Get_RFTime_Measured();
		double locPropagatedRFTime_Proton = locRFTime + (dProtonWrapper->Get_X4_Measured().Z() - dComboWrapper->Get_TargetCenter().Z() )/29.9792458;
		double locPropagatedRFTime_KPlus = locRFTime + (dKPlusWrapper->Get_X4_Measured().Z() - dComboWrapper->Get_TargetCenter().Z() )/29.9792458;
		double locPropagatedRFTime_KMinus= locRFTime + (dKMinusWrapper->Get_X4_Measured().Z() - dComboWrapper->Get_TargetCenter().Z() )/29.9792458;
		double locPropagatedRFTime_PiPlus = locRFTime + (dPiPlusWrapper->Get_X4_Measured().Z() - dComboWrapper->Get_TargetCenter().Z() )/29.9792458;
		double locPropagatedRFTime_PiMinus= locRFTime + (dPiMinusWrapper->Get_X4_Measured().Z() - dComboWrapper->Get_TargetCenter().Z() )/29.9792458;
		double locDeltaT_Proton = dProtonWrapper->Get_X4_Measured().T() - locPropagatedRFTime_Proton;
		double locDeltaT_KPlus = dKPlusWrapper->Get_X4_Measured().T() - locPropagatedRFTime_KPlus;
		double locDeltaT_KMinus = dKMinusWrapper->Get_X4_Measured().T() - locPropagatedRFTime_KMinus;
		double locDeltaT_PiPlus = dPiPlusWrapper->Get_X4_Measured().T() - locPropagatedRFTime_PiPlus;
		double locDeltaT_PiMinus = dPiMinusWrapper->Get_X4_Measured().T() - locPropagatedRFTime_PiMinus;
		if(dProtonWrapper->Get_Detector_System_Timing() == SYS_BCAL) {
			dHist_Proton_DeltaT_BCAL_PhiPiPiCut->Fill(locDeltaT_Proton);
			dHist_Proton_P_vs_DeltaT_BCAL_PhiPiPiCut->Fill(locProtonP4_Measured.P(), locDeltaT_Proton);
			double Beta_pr = dProtonWrapper->Get_Beta_Timing_Measured();
			dHist_Proton_Beta_BCAL_PhiPiPiCut->Fill(Beta_pr);
			dHist_Proton_P_vs_Beta_BCAL_PhiPiPiCut->Fill(fabs(locProtonP4_Measured.P()), Beta_pr);
		}
		if(dKPlusWrapper->Get_Detector_System_Timing() == SYS_BCAL) {
			dHist_KPlus_DeltaT_BCAL_PhiPiPiCut->Fill(locDeltaT_KPlus);
			dHist_KPlus_P_vs_DeltaT_BCAL_PhiPiPiCut->Fill(locKPlusP4_Measured.P(), locDeltaT_KPlus);
			double Beta_kp = dKPlusWrapper->Get_Beta_Timing_Measured();
			dHist_KPlus_Beta_BCAL_PhiPiPiCut->Fill(Beta_kp);
			dHist_KPlus_P_vs_Beta_BCAL_PhiPiPiCut->Fill(fabs(locKPlusP4_Measured.P()), Beta_kp);
		}
		if(dKMinusWrapper->Get_Detector_System_Timing() == SYS_BCAL) {
			dHist_KMinus_DeltaT_BCAL_PhiPiPiCut->Fill(locDeltaT_KMinus);
			dHist_KMinus_P_vs_DeltaT_BCAL_PhiPiPiCut->Fill(locKMinusP4_Measured.P(), locDeltaT_KMinus);
			double Beta_km = dKMinusWrapper->Get_Beta_Timing_Measured();
			dHist_KMinus_Beta_BCAL_PhiPiPiCut->Fill(Beta_km);
			dHist_KMinus_P_vs_Beta_BCAL_PhiPiPiCut->Fill(fabs(locKMinusP4_Measured.P()), Beta_km);
		}
		if(dPiPlusWrapper->Get_Detector_System_Timing() == SYS_BCAL) {
			dHist_PiPlus_DeltaT_BCAL_PhiPiPiCut->Fill(locDeltaT_PiPlus);
			dHist_PiPlus_P_vs_DeltaT_BCAL_PhiPiPiCut->Fill(locPiPlusP4_Measured.P(), locDeltaT_PiPlus);
			double Beta_pip = dPiPlusWrapper->Get_Beta_Timing_Measured();
			dHist_PiPlus_Beta_BCAL_PhiPiPiCut->Fill(Beta_pip);
			dHist_PiPlus_P_vs_Beta_BCAL_PhiPiPiCut->Fill(fabs(locPiPlusP4_Measured.P()), Beta_pip);
		}
		if(dPiMinusWrapper->Get_Detector_System_Timing() == SYS_BCAL) {
			dHist_PiMinus_DeltaT_BCAL_PhiPiPiCut->Fill(locDeltaT_PiMinus);
			dHist_PiMinus_P_vs_DeltaT_BCAL_PhiPiPiCut->Fill(locPiMinusP4_Measured.P(), locDeltaT_PiMinus);
			double Beta_pim = dPiMinusWrapper->Get_Beta_Timing_Measured();
			dHist_PiMinus_Beta_BCAL_PhiPiPiCut->Fill(Beta_pim);
			dHist_PiMinus_P_vs_Beta_BCAL_PhiPiPiCut->Fill(fabs(locPiMinusP4_Measured.P()), Beta_pim);
		}
		if(dProtonWrapper->Get_Detector_System_Timing() == SYS_TOF) {
			dHist_Proton_DeltaT_TOF_PhiPiPiCut->Fill(locDeltaT_Proton);
			dHist_Proton_P_vs_DeltaT_TOF_PhiPiPiCut->Fill(locProtonP4_Measured.P(), locDeltaT_Proton);
			double Betat_pr = dProtonWrapper->Get_Beta_Timing_Measured();
			dHist_Proton_Beta_TOF_PhiPiPiCut->Fill(Betat_pr);
			dHist_Proton_P_vs_Beta_TOF_PhiPiPiCut->Fill(fabs(locProtonP4_Measured.P()), Betat_pr);
		}
		if(dKPlusWrapper->Get_Detector_System_Timing() == SYS_TOF) {
			dHist_KPlus_DeltaT_TOF_PhiPiPiCut->Fill(locDeltaT_KPlus);
			dHist_KPlus_P_vs_DeltaT_TOF_PhiPiPiCut->Fill(locKPlusP4_Measured.P(), locDeltaT_KPlus);
			double Betat_kp = dKPlusWrapper->Get_Beta_Timing_Measured();
			dHist_KPlus_Beta_TOF_PhiPiPiCut->Fill(Betat_kp);
			dHist_KPlus_P_vs_Beta_TOF_PhiPiPiCut->Fill(fabs(locKPlusP4_Measured.P()), Betat_kp);
		}
		if(dKMinusWrapper->Get_Detector_System_Timing() == SYS_TOF) {
			dHist_KMinus_DeltaT_TOF_PhiPiPiCut->Fill(locDeltaT_KMinus);
			dHist_KMinus_P_vs_DeltaT_TOF_PhiPiPiCut->Fill(locKMinusP4_Measured.P(), locDeltaT_KMinus);
			double Betat_km = dKMinusWrapper->Get_Beta_Timing_Measured();
			dHist_KMinus_Beta_TOF_PhiPiPiCut->Fill(Betat_km);
			dHist_KMinus_P_vs_Beta_TOF_PhiPiPiCut->Fill(fabs(locKMinusP4_Measured.P()), Betat_km);
		}
		if(dPiPlusWrapper->Get_Detector_System_Timing() == SYS_TOF) {
			dHist_PiPlus_DeltaT_TOF_PhiPiPiCut->Fill(locDeltaT_PiPlus);
			dHist_PiPlus_P_vs_DeltaT_TOF_PhiPiPiCut->Fill(locPiPlusP4_Measured.P(), locDeltaT_PiPlus);
			double Betat_pip = dPiPlusWrapper->Get_Beta_Timing_Measured();
			dHist_PiPlus_Beta_TOF_PhiPiPiCut->Fill(Betat_pip);
			dHist_PiPlus_P_vs_Beta_TOF_PhiPiPiCut->Fill(fabs(locPiPlusP4_Measured.P()), Betat_pip);
		}
		if(dPiMinusWrapper->Get_Detector_System_Timing() == SYS_TOF) {
			dHist_PiMinus_DeltaT_TOF_PhiPiPiCut->Fill(locDeltaT_PiMinus);
			dHist_PiMinus_P_vs_DeltaT_TOF_PhiPiPiCut->Fill(locPiMinusP4_Measured.P(), locDeltaT_PiMinus);
			double Betat_pim = dPiMinusWrapper->Get_Beta_Timing_Measured();
			dHist_PiMinus_Beta_TOF_PhiPiPiCut->Fill(Betat_pim);
			dHist_PiMinus_P_vs_Beta_TOF_PhiPiPiCut->Fill(fabs(locPiMinusP4_Measured.P()), Betat_pim);
		}

		dHist_Proton_ChiSq_Tracking->Fill(dProtonWrapper->Get_ChiSq_Tracking());
		dHist_KPlus_ChiSq_Tracking->Fill(dKPlusWrapper->Get_ChiSq_Tracking());
		dHist_KMinus_ChiSq_Tracking->Fill(dKMinusWrapper->Get_ChiSq_Tracking());
		dHist_PiPlus_ChiSq_Tracking->Fill(dPiPlusWrapper->Get_ChiSq_Tracking());
		dHist_PiMinus_ChiSq_Tracking->Fill(dPiMinusWrapper->Get_ChiSq_Tracking());
		dHist_Proton_NDF_Tracking->Fill(dProtonWrapper->Get_NDF_Tracking());
		dHist_KPlus_NDF_Tracking->Fill(dKPlusWrapper->Get_NDF_Tracking());
		dHist_KMinus_NDF_Tracking->Fill(dKMinusWrapper->Get_NDF_Tracking());
		dHist_PiPlus_NDF_Tracking->Fill(dPiPlusWrapper->Get_NDF_Tracking());
		dHist_PiMinus_NDF_Tracking->Fill(dPiMinusWrapper->Get_NDF_Tracking());

		double tmp_Proton_EP_BCAL = (dProtonWrapper->Get_Energy_BCAL()/locProtonP4_Measured.Vect().Mag());
		double tmp_KPlus_EP_BCAL = (dKPlusWrapper->Get_Energy_BCAL()/locKPlusP4_Measured.Vect().Mag());
		double tmp_KMinus_EP_BCAL = (dKMinusWrapper->Get_Energy_BCAL()/locKMinusP4_Measured.Vect().Mag());
		double tmp_PiPlus_EP_BCAL = (dPiPlusWrapper->Get_Energy_BCAL()/locPiPlusP4_Measured.Vect().Mag());
		double tmp_PiMinus_EP_BCAL = (dPiMinusWrapper->Get_Energy_BCAL()/locPiMinusP4_Measured.Vect().Mag());
		double tmp_Proton_EP_FCAL = (dProtonWrapper->Get_Energy_FCAL()/locProtonP4_Measured.Vect().Mag());
		double tmp_KPlus_EP_FCAL = (dKPlusWrapper->Get_Energy_FCAL()/locKPlusP4_Measured.Vect().Mag());
		double tmp_KMinus_EP_FCAL = (dKMinusWrapper->Get_Energy_FCAL()/locKMinusP4_Measured.Vect().Mag());
		double tmp_PiPlus_EP_FCAL = (dPiPlusWrapper->Get_Energy_FCAL()/locPiPlusP4_Measured.Vect().Mag());
		double tmp_PiMinus_EP_FCAL = (dPiMinusWrapper->Get_Energy_FCAL()/locPiMinusP4_Measured.Vect().Mag());
		dHist_Proton_EP_BCAL->Fill(tmp_Proton_EP_BCAL);
		dHist_KPlus_EP_BCAL->Fill(tmp_KPlus_EP_BCAL);
		dHist_KMinus_EP_BCAL->Fill(tmp_KMinus_EP_BCAL);
		dHist_PiPlus_EP_BCAL->Fill(tmp_PiPlus_EP_BCAL);
		dHist_PiMinus_EP_BCAL->Fill(tmp_PiMinus_EP_BCAL);
		dHist_Proton_EP_FCAL->Fill(tmp_Proton_EP_FCAL);
		dHist_KPlus_EP_FCAL->Fill(tmp_KPlus_EP_FCAL);
		dHist_KMinus_EP_FCAL->Fill(tmp_KMinus_EP_FCAL);
		dHist_PiPlus_EP_FCAL->Fill(tmp_PiPlus_EP_FCAL);
		dHist_PiMinus_EP_FCAL->Fill(tmp_PiMinus_EP_FCAL);

		dHist_MissingEnergy_PhiPiPiCut->Fill(locMissingP4_Measured.E());
		dHist_MissingMass_PhiPiPiCut->Fill(locMissingP4_Measured.M());
		dHist_MissingMassSquared_PhiPiPiCut->Fill(locMissingP4_Measured.M2());
		dHist_Energy_UnusedShowers_PhiPiPiCut->Fill(dComboWrapper->Get_Energy_UnusedShowers());
		dHist_KinFitCL_PhiPiPiCut->Fill(dComboWrapper->Get_ConfidenceLevel_KinFit(""));
		dHist_BeamEnergy_PhiPiPiCut->Fill(locBeamP4.E());
	
		}//check plots with cuts on phi and phipipi

        	dHist_MPhiPiPi_vs_MProtonPiPlus_Measured->Fill(locPhiPiPiP4_Measured.M(), locProtonPiPP4_Measured.M());
        	dHist_MPhiPiPi_vs_MProtonPiMinus_Measured->Fill(locPhiPiPiP4_Measured.M(), locProtonPiMP4_Measured.M());
        	dHist_MPhiPiPi_vs_MPhiProton_Measured->Fill(locPhiPiPiP4_Measured.M(), locPhiProtonP4_Measured.M());
        	dHist_MPhiPiPi_vs_MPiPi_Measured->Fill(locPhiPiPiP4_Measured.M(), locPipPiMP4_Measured.M());
        	dHist_MPhiPiPi_vs_MPhiPiPlus_Measured->Fill(locPhiPiPiP4_Measured.M(), locPhiPiPP4_Measured.M());
        	dHist_MPhiPiPi_vs_MPhiPiMinus_Measured->Fill(locPhiPiPiP4_Measured.M(), locPhiPiMP4_Measured.M());
 
        	dHist_MPhiPiPlus_vs_MPhiPiMinus_Measured->Fill(locPhiPiPP4_Measured.M(), locPhiPiMP4_Measured.M());
        	dHist_MPhiPiPlus_vs_MPiPi_Measured->Fill(locPhiPiPP4_Measured.M(), locPipPiMP4_Measured.M());
        	dHist_MPhiPiMinus_vs_MPiPi_Measured->Fill(locPhiPiMP4_Measured.M(), locPipPiMP4_Measured.M());
        	dHist_MPhiPiPlus_vs_MKPlusPiMinus_Measured->Fill(locPhiPiPP4_Measured.M(), lockstP4_Measured.M());
        	dHist_MPhiPiPlus_vs_MKMinusPiPlus_Measured->Fill(locPhiPiPP4_Measured.M(), locaksP4_Measured.M());
        	dHist_MPhiPiMinus_vs_MKPlusPiMinus_Measured->Fill(locPhiPiMP4_Measured.M(), lockstP4_Measured.M());
        	dHist_MPhiPiMinus_vs_MKMinusPiPlus_Measured->Fill(locPhiPiMP4_Measured.M(), locaksP4_Measured.M());


		// save phipipi mass
		dHist_Mphipipi->Fill(locPhiPiPiP4.M());
		dHist_Mphipipi_measured->Fill(locPhiPiPiP4_Measured.M());

		// save phipip mass
		dHist_Mphipip->Fill(locPhiPiPP4.M());
		dHist_Mphipip_measured->Fill(locPhiPiPP4_Measured.M());

		// save phipim mass
		dHist_Mphipim->Fill(locPhiPiMP4.M());
		dHist_Mphipim_measured->Fill(locPhiPiMP4_Measured.M());

		// save pippim mass
		dHist_Mpippim->Fill(locPipPiMP4.M());
		dHist_Mpippim_measured->Fill(locPipPiMP4_Measured.M());

		// save kst mass
		dHist_Mkst->Fill(lockstP4.M());
		dHist_Mkst_measured->Fill(lockstP4_Measured.M());

		// save aks mass
		dHist_Maks->Fill(locaksP4.M());
		dHist_Maks_measured->Fill(locaksP4_Measured.M());

		// save Mphipip Mphipim
		dHist_Mpip_Mpim_measured->Fill(locPhiPiPP4_Measured.M(),locPhiPiMP4_Measured.M());
                  
                // Save MPhiProton
		dHist_MphiProton_measured->Fill(locPhiProtonP4_Measured.M());

		//MPhiPiPi. Cut
		//if((locPhiPiPiP4_Measured.M() < 2.5) || (locPhiPiPiP4_Measured.M() > 2.9)) 
		//	continue; 

                // Save Proton momenta
		dHist_Proton_P->Fill(locProtonP4_Measured.P());

                // Save Proton Theta
		//dHist_Proton_Theta->Fill(locProtonP4.Theta());
		dHist_Proton_Theta->Fill(locProtonP4.Theta()*57.);

		dHist_MProtonPiP_measured->Fill(locProtonPiPP4_Measured.M());
		dHist_MProtonPiM_measured->Fill(locProtonPiMP4_Measured.M());


		//MP-PiP. Cut
		//if((locProtonPiPP4_Measured.M() > 1.18) && (locProtonPiPP4_Measured.M() < 1.30)) 
		//	continue; 

		//MP-PiM. Cut
		//if((locProtonPiMP4_Measured.M() > 1.18) && (locProtonPiMP4_Measured.M() < 1.30)) 
		//	continue; 


		dHist_PiPlus_P->Fill(locPiPlusP4_Measured.P());
		dHist_PiPlus_Theta->Fill(locPiPlusP4.Theta()*57.);
		dHist_PiMinus_P->Fill(locPiMinusP4_Measured.P());
		dHist_PiMinus_Theta->Fill(locPiMinusP4.Theta()*57.);
		dHist_KPlus_P->Fill(locKPlusP4_Measured.P());
		dHist_KPlus_Theta->Fill(locKPlusP4.Theta()*57.);
		dHist_KMinus_P->Fill(locKMinusP4_Measured.P());
		dHist_KMinus_Theta->Fill(locKMinusP4.Theta()*57.);

		//dHist_MProtonPiP_measured->Fill(locProtonPiPP4_Measured.M());
		//dHist_MProtonPiM_measured->Fill(locProtonPiMP4_Measured.M());


		//dHist_Proton_Theta_P->Fill(locProtonP4.P(),locProtonP4.Theta());
		dHist_Proton_Theta_P->Fill(locProtonP4.Theta()*57.,locProtonP4_Measured.P());

        	dHist_kk_kkpipi->Fill(locPhiP4_Measured.M(),locPhiPiPiP4_Measured.M());

        	dHist_ebeam_kkpipi->Fill(locBeamP4.E(),locPhiPiPiP4_Measured.M());
	}

	/******************************************* LOOP OVER THROWN DATA (OPTIONAL) ***************************************/
/*
	//Thrown beam: just use directly
	if(dThrownBeam != NULL)
		double locEnergy = dThrownBeam->Get_P4().E();

	//Loop over throwns
	for(UInt_t loc_i = 0; loc_i < Get_NumThrown(); ++loc_i)
	{
		//Set branch array indices corresponding to this particle
		dThrownWrapper->Set_ArrayIndex(loc_i);

		//Do stuff with the wrapper here ...
	}
*/
	/****************************************** LOOP OVER OTHER ARRAYS (OPTIONAL) ***************************************/
/*
	//Loop over beam particles (note, only those appearing in combos are present)
	for(UInt_t loc_i = 0; loc_i < Get_NumBeam(); ++loc_i)
	{
		//Set branch array indices corresponding to this particle
		dBeamWrapper->Set_ArrayIndex(loc_i);

		//Do stuff with the wrapper here ...
	}

	//Loop over charged track hypotheses (all are present, even those not in any combos)
	for(UInt_t loc_i = 0; loc_i < Get_NumChargedHypos(); ++loc_i)
	{
		//Set branch array indices corresponding to this particle
		dChargedHypoWrapper->Set_ArrayIndex(loc_i);

		//Do stuff with the wrapper here ...
	}

	//Loop over neutral particle hypotheses (all are present, even those not in any combos)
	for(UInt_t loc_i = 0; loc_i < Get_NumNeutralHypos(); ++loc_i)
	{
		//Set branch array indices corresponding to this particle
		dNeutralHypoWrapper->Set_ArrayIndex(loc_i);

		//Do stuff with the wrapper here ...
	}
*/

	/************************************ EXAMPLE: FILL CLONE OF TTREE HERE WITH CUTS APPLIED ************************************/
/*
	Bool_t locIsEventCut = true;
	for(UInt_t loc_i = 0; loc_i < Get_NumCombos(); ++loc_i) {
		//Set branch array indices for combo and all combo particles
		dComboWrapper->Set_ComboIndex(loc_i);
		// Is used to indicate when combos have been cut
		if(dComboWrapper->Get_IsComboCut())
			continue;
		locIsEventCut = false; // At least one combo succeeded
		break;
	}
	if(!locIsEventCut && dOutputTreeFileName != "")
		FillOutputTree();
*/

	return kTRUE;
}

void DSelector_phipipi_2k::Finalize(void)
{
	//Save anything to output here that you do not want to be in the default DSelector output ROOT file.

	//Otherwise, don't do anything else (especially if you are using PROOF).
		//If you are using PROOF, this function is called on each thread,
		//so anything you do will not have the combined information from the various threads.
		//Besides, it is best-practice to do post-processing (e.g. fitting) separately, in case there is a problem.

	//DO YOUR STUFF HERE
//	cout<<"nCheck_PhiPiPiCut = "<<nCheck_PhiPiPiCut<<endl;
	//CALL THIS LAST
	DSelector::Finalize(); //Saves results to the output file
}
