//Data: 2016 data
//fit to Mphi_measured --> all K+K-
//signal PDF: Breit-Wigner X Gauss
//bkb PDF: Chebyshev
//chi2FitTo for binning fits
#include <TMath.h>
#include <math.h>
#include <fstream>
#include <iomanip>
//#include <RoodMyBW.h>

using namespace RooFit;
using namespace std;

void fit_Mphi_measured()
{
	gSystem->Load("libRooFit");
//========= Set paraments ===========
	int k = 0 ;//bin number
	Double_t para[30];
	para[1]= 1.01980e+00 ;  //BW_mean:  (PDG:1019.461+-0.019MeV)
	para[2]= 1.28544e-02 ;  //BW_width: (PDG:4.266+-0.031MeV)
	para[3]= 1.55254e-06 ;  //GS_sigma: gauss
	para[4]= 2.45139e+05 ;  //Nbkg: background
	para[5]= 4.71259e+04 ;  //Nsig: signal
	para[6]= 5.00390e-01 ;  //p0_Cheby
	para[7]=-9.90462e-02 ;  //p1_Cheby
	
	para[8]= 0.00000e+00 ;  //GS_mean:  gauss
	
	Double_t mkpkm_bins=55;
	Double_t mkpkm_low=0.990;
	Double_t mkpkm_up =1.100;
	int dof = 7 ;
//========== input data ============
	TString ROOTNAME = "/nfs/tmp/ting/GlueX/halld_my/nian/phipipi_same_2017/hist_phipipi_2k_50MeV.root";
	TString HISTNAME = "Mphi_measured";
	TString PICNAME  = "app/Mphi_measured.pdf";
	
	TFile *f1= new TFile(ROOTNAME);
	TH1I *h1 = (TH1I*)f1->Get(HISTNAME);
	RooRealVar mkpkm("mkpkm", "", mkpkm_low, mkpkm_up);
	RooDataHist data("inputdata","data set", mkpkm, h1);
//=========== signal PDF =============
//	RooRealVar mean_gs("GS_mean",    "", 0.0);
	RooRealVar sigma_gs("GS_sigma",  "", para[3], 0.0, 0.02);
//	sigma_gs.setConstant();
//	RooGaussian gauss_pdf("gaussian pdf", "", mkpkm, mean_gs, sigma_gs);
	
	RooRealVar mass("BW_mean",   "",  para[1],  1.01,1.03);
	RooRealVar width("BW_width", "",  para[2],  0.0, 0.04);
//	mass.setConstant();
//	width.setConstant();
//	RooBreitWigner BW_pdf("BW", "", mkpkm, mass, width);
//	RoodMyBW BW_pdf("BW", "", mkpkm, mass, width);
	
//	mkpkm.setBins(10000,"cache");
//	RooFFTConvPdf sig_pdf("signal PDF", "", mkpkm, BW_pdf, gauss_pdf);
//	sig_pdf.setBufferFraction(1.0);
//	sig_pdf.setBufferStrategy(RooFFTConvPdf::Flat);//Extend(default), Mirror, Flat

	RooVoigtian sig_pdf("BW x GS","signal PDF (voigtian)", mkpkm, mass, width, sigma_gs);
//=========== background PDF =============
	RooRealVar p0("p0_Cheby", "", para[6], -2, 2);
	RooRealVar p1("p1_Cheby", "", para[7], -2, 2);
	RooRealVar p2("p2_Cheby", "", -2, 2);
	RooChebychev bkg_pdf("background PDF", "", mkpkm, RooArgList(p0,p1));

	RooRealVar argus_m0("m0_argus", "m0_argus", 0.98735);//fixed to KK threshold
	RooRealVar argus_c("c_argus", "c_argus", -100, 100);
	RooRealVar argus_p("p_argus", "p_argus", -100, 100);
//	argus_m0.setConstant();//fixed to KK threshold
//	RooMyArgus bkg_pdf("background PDF", "", mkpkm, argus_m0, argus_c, argus_p);
//========== sum to fit =============
	RooRealVar N1("Nsig",  "",  para[5],  0,  200000);
	RooRealVar N2("Nbkg",  "",  para[4],  0,  1000000);

	RooExtendPdf esig("esig","extended signal p.d.f",sig_pdf,N1);
	RooExtendPdf ebkg("ebkg","extended background p.d.f",bkg_pdf,N2);
	RooAddPdf sum("sum","signalPDF + bkgPDF",RooArgList(esig,ebkg));
//	RooAddPdf sum("sum","signalPDF + bkgPDF",RooArgList(sig_pdf,bkg_pdf),RooArgList(N1,N2));
	
	RooFitResult * fitres = sum.chi2FitTo(data, Save(kTRUE), Extended(kTRUE));
	fitres->Print("v");
//============== plot M(K+K-) ============
	RooPlot *frame_mkpkm = mkpkm.frame(Name("o_o"), Bins(mkpkm_bins), Range(mkpkm_low, mkpkm_up));
	data.plotOn(frame_mkpkm,MarkerColor(kBlack), MarkerSize(1.0),DataError(RooAbsData::SumW2));
	sum.plotOn(frame_mkpkm,LineColor(kRed) ) ;
	double chi2_mkpkm = frame_mkpkm->chiSquare(dof);
	
	TPaveText *pt2 = new TPaveText(0.55, 0.70, 0.60, 0.75, "BRNDC");
	pt2->SetBorderSize(0);
	pt2->SetFillColor(0);
	pt2->SetTextAlign(12);
	pt2->SetTextSize(0.04);
	pt2->SetTextFont(42);
	TString Par5V2 = Form("%2.1f", frame_mkpkm->chiSquare(dof));
//	chisq/nDOF = chisq / (nbin-nFitParam)
	TString Par52 = "#chi^{2}#/d.o.f = " + Par5V2;
	TText *text2 = pt2->AddText(Par52);
	
	sum.plotOn(frame_mkpkm, Components(sig_pdf),   LineColor(3));//3-Green
	sum.plotOn(frame_mkpkm, Components(bkg_pdf),   LineColor(4), LineStyle(7));//4-blue
//	sum.plotOn(frame_mkpkm, Components(bkg_pdf),   DrawOption("F"),FillColor(4),FillStyle(3018),Range(1.005,1.035,kFALSE),VLines());
	sum.paramOn(frame_mkpkm, Parameters(RooArgSet(N1,N2)), RooFit::Layout(0.5, 0.75));
	TCanvas *c_mkpkm = new TCanvas("mkpkm", "qinn@BESIII", 0, 0, 900, 600);
	c_mkpkm->SetLeftMargin(0.15);
	c_mkpkm->SetRightMargin(0.06);
	c_mkpkm->SetTopMargin(0.03);
	c_mkpkm->SetBottomMargin(0.16);
	c_mkpkm->SetFillColor(0);
	c_mkpkm->Divide(1,1);
	c_mkpkm->cd(1);
	
	frame_mkpkm->SetTitle("");
	frame_mkpkm->SetYTitle("Events / 2.0 MeV/c^{2}");
	frame_mkpkm->SetXTitle("M(K^{+}K^{-}) (GeV/c^{2})");
	frame_mkpkm->GetXaxis()->SetLabelFont(42);
	frame_mkpkm->GetXaxis()->SetLabelSize(0.06);
	frame_mkpkm->GetXaxis()->SetLabelOffset(0.01);
	frame_mkpkm->GetXaxis()->SetNdivisions(510);
	frame_mkpkm->GetXaxis()->SetTitleFont(42);
	frame_mkpkm->GetXaxis()->SetTitleColor(1);
	frame_mkpkm->GetXaxis()->SetTitleSize(0.07);
	frame_mkpkm->GetXaxis()->SetTitleOffset(1.15);
	frame_mkpkm->GetXaxis()->CenterTitle();
	frame_mkpkm->GetYaxis()->CenterTitle();
//	frame_mkpkm->SetMinimum(0.0);
	
	frame_mkpkm->Draw();
	pt2->Draw();
	c_mkpkm->Print(PICNAME);

//=============== output result ===============
	RooArgList pars(* ebkg.getParameters(RooArgSet(mkpkm)));
	RooArgSet prodSet(ebkg);prodSet.add(N2);
	RooProduct unNormPdf("fitted Function", "fitted Function", prodSet);
	TF1 * f2 = unNormPdf.asTF(RooArgList(mkpkm), pars);//unnormalized
	
	Double_t norm1 = ((RooRealVar*) pars.find("Nbkg"))->getVal();
	Double_t dnorm1 = ((RooRealVar*) pars.find("Nbkg"))->getError();
	cout << endl;
	cout << "Nbkg = " << norm1 << " +- " << dnorm1 << endl;
	
	Double_t integral_full = f2->Integral(0.988, 1.1);//unnormalized
	Double_t integ2 = norm1*f2->Integral(1.005, 1.035)/integral_full;//normalized
	Double_t dinteg2 = norm1*f2->IntegralError(1.005, 1.035, 0, fitres->covarianceMatrix().GetMatrixArray())/integral_full;
	cout<<"               norm1 = "<<norm1<<endl;
	cout<<"       integral_full = "<<integral_full<<endl;
	cout<<"Normalization factor = "<<norm1/integral_full<<endl;
	cout<<"Integral events in mass window: "<< integ2 <<"+-"<< dinteg2 <<endl;
	cout << endl;



	mkpkm.setRange("MassWindow", 1.005, 1.035);
	mkpkm.setRange("AllRegion",  0.988, 1.1);
	RooAbsReal* nbkg_masswindow = bkg_pdf.createIntegral(mkpkm,NormSet(mkpkm),Range("MassWindow"));
	Double_t Nbkg_masswindow = N2.getVal()*(nbkg_masswindow->getVal());
	
	RooAbsReal* nbkg_allregion = bkg_pdf.createIntegral(mkpkm,NormSet(mkpkm),Range("AllRegion"));
	Double_t Nbkg_allregion = N2.getVal()*(nbkg_allregion->getVal());
	
	cout<<"================================"<<endl;
	cout<<endl;
	cout<< "chi2/ndf = " << chi2_mkpkm << endl;
	cout<<"****************************"<<endl;
	cout<<"Signal BinCnt["<<k<<"]= "<<N1.getVal()<<" ;"<<endl;
	cout<<"Signal BinErr["<<k<<"]= "<<N1.getError()<<" ;"<<endl;
	cout<<"****************************"<<endl;
	cout<<"Background BinCnt["<<k<<"]= "<<N2.getVal()<<" ;"<<endl;
	cout<<"Background BinErr["<<k<<"]= "<<N2.getError()<<" ;"<<endl;
	cout<<"****************************"<<endl;
	cout<<"non-phi bkg in phi mass window BinCnt["<<k<<"]= "<<integ2<<" ;"<<endl;
	cout<<"non-phi bkg in phi mass window BinErr["<<k<<"]= "<<dinteg2<<" ;"<<endl;
	cout<<"****************************"<<endl;
	cout<<"Nbkg_masswindow = "<<Nbkg_masswindow<<endl;
	cout<<"Nbkg_allregion  = "<<Nbkg_allregion<<endl;

	ofstream SaveFile;
	SaveFile.open("Data.txt",ios_base::app);
	SaveFile<<"hsignal->SetBinContent("<<k<<", "<<N1.getVal()<< ");"<< endl;
	SaveFile<<"hsignal->SetBinError("<<k<<", "<<N1.getError()<< ");"<< endl;
	SaveFile<<"hallbkg->SetBinContent("<<k<<", "<<N2.getVal()<< ");"<< endl;
	SaveFile<<"hallbkg->SetBinError("<<k<<", "<<N2.getError()<< ");"<< endl;
	SaveFile<<"hnonphi->SetBinContent("<<k<<", "<<integ2<< ");"<< endl;
	SaveFile<<"hnonphi->SetBinError("<<k<<", "<<dinteg2<< ");"<< endl;
	SaveFile<<endl;
	SaveFile.close();
}

