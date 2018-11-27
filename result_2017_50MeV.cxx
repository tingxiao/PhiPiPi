void result_2017_50MeV()
{
        gStyle->SetOptStat(00);

        TFile *Mydata=new TFile("/nfs/tmp/ting/GlueX/halld_my/nian/phipipi_same_2017/hist_phipipi_2k_50MeV.root");
        TH1F *hCut = (TH1F*)Mydata->Get("Mphipipi_measured");//42 bins

        TH1F *hsignal = new TH1F("hsignal", "", 42, 1.4, 3.5);
        TH1F *hallbkg = new TH1F("hallbkg", "", 42, 1.4, 3.5);
        TH1F *hnonphi = new TH1F("hnonphi", "", 42, 1.4, 3.5);

hsignal->SetBinContent(1, 1421.54);
hsignal->SetBinError(1, 158.672);
hallbkg->SetBinContent(1, 5292.17);
hallbkg->SetBinError(1, 170.417);
hnonphi->SetBinContent(1, 1675.89);
hnonphi->SetBinError(1, 33.1455);

hsignal->SetBinContent(2, 3281.67);
hsignal->SetBinError(2, 281.289);
hallbkg->SetBinContent(2, 10824.9);
hallbkg->SetBinError(2, 294.396);
hnonphi->SetBinContent(2, 2980.21);
hnonphi->SetBinError(2, 2.59233);

hsignal->SetBinContent(3, 4925.23);
hsignal->SetBinError(3, 348.094);
hallbkg->SetBinContent(3, 20085.9);
hallbkg->SetBinError(3, 369.256);
hnonphi->SetBinContent(3, 5336.07);
hnonphi->SetBinError(3, 0.000105036);

hsignal->SetBinContent(4, 5850.64);
hsignal->SetBinError(4, 366.962);
hallbkg->SetBinContent(4, 37516.8);
hallbkg->SetBinError(4, 407.825);
hnonphi->SetBinContent(4, 9770.47);
hnonphi->SetBinError(4, 5.27835);

hsignal->SetBinContent(5, 8843.84);
hsignal->SetBinError(5, 492.692);
hallbkg->SetBinContent(5, 56521.1);
hallbkg->SetBinError(5, 538.903);
hnonphi->SetBinContent(5, 13419.4);
hnonphi->SetBinError(5, 8.08291);

hsignal->SetBinContent(6, 10590.3);
hsignal->SetBinError(6, 467.643);
hallbkg->SetBinContent(6, 76740.1);
hallbkg->SetBinError(6, 533.688);
hnonphi->SetBinContent(6, 18104.9);
hnonphi->SetBinError(6, 714.706);

hsignal->SetBinContent(7, 12994.6);
hsignal->SetBinError(7, 568.876);
hallbkg->SetBinContent(7, 98531.5);
hallbkg->SetBinError(7, 639.643);
hnonphi->SetBinContent(7, 23452.4);
hnonphi->SetBinError(7, 1039.98);

hsignal->SetBinContent(8, 15064.9);
hsignal->SetBinError(8, 594.297);
hallbkg->SetBinContent(8, 121718);
hallbkg->SetBinError(8, 678.099);
hnonphi->SetBinContent(8, 29217.5);
hnonphi->SetBinError(8, 10.7708);

hsignal->SetBinContent(9, 17290.8);
hsignal->SetBinError(9, 627.9);
hallbkg->SetBinContent(9, 132380);
hallbkg->SetBinError(9, 713.653);
hnonphi->SetBinContent(9, 30302);
hnonphi->SetBinError(9, 10.8578);

hsignal->SetBinContent(10, 18159);
hsignal->SetBinError(10, 628.42);
hallbkg->SetBinContent(10, 131451);
hallbkg->SetBinError(10, 712.842);
hnonphi->SetBinContent(10, 28963);
hnonphi->SetBinError(10, 1284);

hsignal->SetBinContent(11, 16435.5);
hsignal->SetBinError(11, 507.615);
hallbkg->SetBinContent(11, 131867);
hallbkg->SetBinError(11, 610.788);
hnonphi->SetBinContent(11, 28312.7);
hnonphi->SetBinError(11, 8.41883);

hsignal->SetBinContent(12, 14991);
hsignal->SetBinError(12, 459.409);
hallbkg->SetBinContent(12, 127469);
hallbkg->SetBinError(12, 568.758);
hnonphi->SetBinContent(12, 26997.2);
hnonphi->SetBinError(12, 733.084);

hsignal->SetBinContent(13, 15140.5);
hsignal->SetBinError(13, 416.627);
hallbkg->SetBinContent(13, 121889);
hallbkg->SetBinError(13, 529.44);
hnonphi->SetBinContent(13, 25271);
hnonphi->SetBinError(13, 6.1919);

hsignal->SetBinContent(14, 16696.7);
hsignal->SetBinError(14, 418.542);
hallbkg->SetBinContent(14, 112947);
hallbkg->SetBinError(14, 520.95);
hnonphi->SetBinContent(14, 22751.7);
hnonphi->SetBinError(14, 655.507);

hsignal->SetBinContent(15, 16817.6);
hsignal->SetBinError(15, 416.809);
hallbkg->SetBinContent(15, 106086);
hallbkg->SetBinError(15, 513.149);
hnonphi->SetBinContent(15, 21076.7);
hnonphi->SetBinError(15, 630.505);

hsignal->SetBinContent(16, 16641.7);
hsignal->SetBinError(16, 404.421);
hallbkg->SetBinContent(16, 99120.2);
hallbkg->SetBinError(16, 496.01);
hnonphi->SetBinContent(16, 19775.8);
hnonphi->SetBinError(16, 593.876);

hsignal->SetBinContent(17, 16458.5);
hsignal->SetBinError(17, 576.395);
hallbkg->SetBinContent(17, 96113.1);
hallbkg->SetBinError(17, 641.757);
hnonphi->SetBinContent(17, 19067.1);
hnonphi->SetBinError(17, 12.3231);

hsignal->SetBinContent(18, 17269.6);
hsignal->SetBinError(18, 381.523);
hallbkg->SetBinContent(18, 91250);
hallbkg->SetBinError(18, 468.507);
hnonphi->SetBinContent(18, 17954.7);
hnonphi->SetBinError(18, 557.533);

hsignal->SetBinContent(19, 17230.5);
hsignal->SetBinError(19, 1192.87);
hallbkg->SetBinContent(19, 84691);
hallbkg->SetBinError(19, 1187.64);
hnonphi->SetBinContent(19, 16691.4);
hnonphi->SetBinError(19, 33.6354);

hsignal->SetBinContent(20, 18969.2);
hsignal->SetBinError(20, 270.6);
hallbkg->SetBinContent(20, 81116.3);
hallbkg->SetBinError(20, 367.897);
hnonphi->SetBinContent(20, 15655.8);
hnonphi->SetBinError(20, 59.1727);

hsignal->SetBinContent(21, 16057.1);
hsignal->SetBinError(21, 251.523);
hallbkg->SetBinContent(21, 80629);
hallbkg->SetBinError(21, 357.512);
hnonphi->SetBinContent(21, 15969.5);
hnonphi->SetBinError(21, 0);

hsignal->SetBinContent(22, 16054);
hsignal->SetBinError(22, 376.257);
hallbkg->SetBinContent(22, 77721);
hallbkg->SetBinError(22, 450.677);
hnonphi->SetBinContent(22, 15154.5);
hnonphi->SetBinError(22, 598.465);

hsignal->SetBinContent(23, 16499.7);
hsignal->SetBinError(23, 397.511);
hallbkg->SetBinContent(23, 73634.1);
hallbkg->SetBinError(23, 463.755);
hnonphi->SetBinContent(23, 14293.1);
hnonphi->SetBinError(23, 476.706);

hsignal->SetBinContent(24, 14543.3);
hsignal->SetBinError(24, 369.603);
hallbkg->SetBinContent(24, 70701.1);
hallbkg->SetBinError(24, 438.516);
hnonphi->SetBinContent(24, 13907.6);
hnonphi->SetBinError(24, 453.529);

hsignal->SetBinContent(25, 13901.2);
hsignal->SetBinError(25, 340.985);
hallbkg->SetBinContent(25, 65718.5);
hallbkg->SetBinError(25, 410.008);
hnonphi->SetBinContent(25, 12956.2);
hnonphi->SetBinError(25, 430.494);

hsignal->SetBinContent(26, 13349.3);
hsignal->SetBinError(26, 349.819);
hallbkg->SetBinContent(26, 61301.9);
hallbkg->SetBinError(26, 412.77);
hnonphi->SetBinContent(26, 12152.3);
hnonphi->SetBinError(26, 519.396);

hsignal->SetBinContent(27, 12734.8);
hsignal->SetBinError(27, 308.036);
hallbkg->SetBinContent(27, 56500);
hallbkg->SetBinError(27, 372.329);
hnonphi->SetBinContent(27, 10966.1);
hnonphi->SetBinError(27, 2.69031);

hsignal->SetBinContent(28, 12157.2);
hsignal->SetBinError(28, 310.956);
hallbkg->SetBinContent(28, 51308.7);
hallbkg->SetBinError(28, 368.54);
hnonphi->SetBinContent(28, 9904.55);
hnonphi->SetBinError(28, 346.335);

hsignal->SetBinContent(29, 10981.8);
hsignal->SetBinError(29, 291.709);
hallbkg->SetBinContent(29, 47746.9);
hallbkg->SetBinError(29, 349.057);
hnonphi->SetBinContent(29, 9480.16);
hnonphi->SetBinError(29, 290.897);

hsignal->SetBinContent(30, 9259.16);
hsignal->SetBinError(30, 410.541);
hallbkg->SetBinContent(30, 42645.8);
hallbkg->SetBinError(30, 449.349);
hnonphi->SetBinContent(30, 8378.97);
hnonphi->SetBinError(30, 7.56263);

hsignal->SetBinContent(31, 8555.08);
hsignal->SetBinError(31, 255.652);
hallbkg->SetBinContent(31, 38072.6);
hallbkg->SetBinError(31, 307.941);
hnonphi->SetBinContent(31, 7476.44);
hnonphi->SetBinError(31, 262.262);

hsignal->SetBinContent(32, 6704.13);
hsignal->SetBinError(32, 334.835);
hallbkg->SetBinContent(32, 34397.6);
hallbkg->SetBinError(32, 373.895);
hnonphi->SetBinContent(32, 6748.82);
hnonphi->SetBinError(32, 173.217);

hsignal->SetBinContent(33, 5976.06);
hsignal->SetBinError(33, 199.287);
hallbkg->SetBinContent(33, 28525.4);
hallbkg->SetBinError(33, 249.508);
hnonphi->SetBinContent(33, 5619.97);
hnonphi->SetBinError(33, 196.097);

hsignal->SetBinContent(34, 4878.65);
hsignal->SetBinError(34, 226.843);
hallbkg->SetBinContent(34, 23233.2);
hallbkg->SetBinError(34, 263.911);
hnonphi->SetBinContent(34, 4383.23);
hnonphi->SetBinError(34, 160.04);

hsignal->SetBinContent(35, 3561.72);
hsignal->SetBinError(35, 182.445);
hallbkg->SetBinContent(35, 19402.4);
hallbkg->SetBinError(35, 221.64);
hnonphi->SetBinContent(35, 3733.55);
hnonphi->SetBinError(35, 201.594);

hsignal->SetBinContent(36, 2910.87);
hsignal->SetBinError(36, 157.023);
hallbkg->SetBinContent(36, 15396.5);
hallbkg->SetBinError(36, 192.702);
hnonphi->SetBinContent(36, 2980.52);
hnonphi->SetBinError(36, 145.17);

hsignal->SetBinContent(37, 2420.74);
hsignal->SetBinError(37, 142.692);
hallbkg->SetBinContent(37, 12467.2);
hallbkg->SetBinError(37, 174.362);
hnonphi->SetBinContent(37, 2438.74);
hnonphi->SetBinError(37, 74.6771);

hsignal->SetBinContent(38, 2178.17);
hsignal->SetBinError(38, 172.327);
hallbkg->SetBinContent(38, 9534.48);
hallbkg->SetBinError(38, 192.571);
hnonphi->SetBinContent(38, 1753);
hnonphi->SetBinError(38, 74.1992);

hsignal->SetBinContent(39, 1392.78);
hsignal->SetBinError(39, 201.612);
hallbkg->SetBinContent(39, 8000.42);
hallbkg->SetBinError(39, 217.371);
hnonphi->SetBinContent(39, 1570.37);
hnonphi->SetBinError(39, 4.92099);

hsignal->SetBinContent(40, 2084.44);
hsignal->SetBinError(40, 679.271);
hallbkg->SetBinContent(40, 5550.9);
hallbkg->SetBinError(40, 645.579);
hnonphi->SetBinContent(40, 852.085);
hnonphi->SetBinError(40, 7.75539);

hsignal->SetBinContent(41, 924.85);
hsignal->SetBinError(41, 92.3321);
hallbkg->SetBinContent(41, 5080.81);
hallbkg->SetBinError(41, 112.6);
hnonphi->SetBinContent(41, 944.295);
hnonphi->SetBinError(41, 0.983807);

hsignal->SetBinContent(42, 854.743);
hsignal->SetBinError(42, 55.8693);
hallbkg->SetBinContent(42, 3651.79);
hallbkg->SetBinError(42, 57.7703);
hnonphi->SetBinContent(42, 638.776);
hnonphi->SetBinError(42, 89.5867);




        TCanvas *MyCanvas = new TCanvas("MyCanvas","BESIII",0,0,900,600);
//        MyCanvas->Divide(1,1);
        MyCanvas->SetMargin(0.15,0.15,0.15,0.15);

        hsignal->SetXTitle("M(#phi#pi^{+}#pi^{-}) (GeV/c^{2})");
        hsignal->SetYTitle("Events / 50.0 MeV/c^{2}");
        hsignal->GetXaxis()->SetLabelFont(42);
        hsignal->GetXaxis()->SetLabelSize(0.05);
        hsignal->GetYaxis()->SetLabelSize(0.05);
        hsignal->GetXaxis()->SetLabelOffset(0.01);
        hsignal->GetXaxis()->SetNdivisions(510);
        hsignal->GetXaxis()->SetTitleFont(42);
        hsignal->GetXaxis()->SetTitleColor(1);
        hsignal->GetXaxis()->SetTitleSize(0.06);
        hsignal->GetYaxis()->SetTitleSize(0.06);
        hsignal->GetXaxis()->SetTitleOffset(1.15);
        hsignal->GetYaxis()->SetTitleOffset(1.3);
        hsignal->GetXaxis()->CenterTitle();
        hsignal->GetYaxis()->CenterTitle();
//        hsignal->SetMinimum(0);

        hCut->SetMarkerStyle(20);
        hCut->SetMarkerColor(1);//1-black
        hCut->SetLineColor(1);
        hCut->SetMarkerSize(1);
        hCut->SetLineWidth(2);

        hsignal->SetMarkerStyle(20);
        hsignal->SetMarkerColor(2);//2-red
        hsignal->SetLineColor(2);
        hsignal->SetMarkerSize(1);
        hsignal->SetLineWidth(2);

        hallbkg->SetMarkerStyle(20);
        hallbkg->SetMarkerColor(4);//4-blue
        hallbkg->SetLineColor(4);
        hallbkg->SetMarkerSize(1);
        hallbkg->SetLineWidth(2);
        hnonphi->SetMarkerStyle(4);//4-hollow
        hnonphi->SetMarkerColor(4);//4-blue
        hnonphi->SetLineColor(4);
        hnonphi->SetMarkerSize(1);
        hnonphi->SetLineWidth(2);

        TLegend *lg1 = new TLegend(0.35,0.2,0.75,0.4);
        lg1->AddEntry(hCut,"Cut directly","lep");
        lg1->AddEntry(hsignal,"bin by bin reconstructed","lep");
        lg1->SetFillColor(0);
        lg1->SetTextFont(42);

        hsignal->Draw("");
//        hCut->Draw("e1&&same");
//        hallbkg->Draw("same");
//        hnonphi->Draw("same");
//        lg1->Draw();
        MyCanvas->Print("app/result_2017_50MeV.pdf");

        TFile *fsignal=new TFile("app/result_2017_50MeV.root","recreate");
        TH1F *hsig = (TH1F*)hsignal->Clone("hsig");
        TH1F *hbkg = (TH1F*)hallbkg->Clone("hbkg");
        TH1F *hnphi = (TH1F*)hnonphi->Clone("hnphi");
        TH1F *hcut = (TH1F*)hCut->Clone("hcut");
        fsignal->Write();
        fsignal->Close();

}

