void scale()
{

  TCanvas* c1 = new TCanvas("c1","");
  c1->SetMargin(0.15,0.05,0.13,0.08);

  double eta[28], v2[28], ev2[28], eslv2[28], esuv2[28];
  eta[0]  = -4.8614; v2[0]  = 0.0166; ev2[0]  = 0.0038; eslv2[0]  = 0.0025; esuv2[0]  = 0.0034;
  eta[1]  = -4.0059; v2[1]  = 0.0236; ev2[1]  = 0.0025; eslv2[1]  = 0.0032; esuv2[1]  = 0.0038;
  eta[2]  = -3.0445; v2[2]  = 0.0312; ev2[2]  = 0.0015; eslv2[2]  = 0.0038; esuv2[2]  = 0.0038;
  eta[3]  = -1.7500; v2[3]  = 0.0367; ev2[3]  = 0.0033; eslv2[3]  = 0.0025; esuv2[3]  = 0.0043;
  eta[4]  = -1.2497; v2[4]  = 0.0395; ev2[4]  = 0.0020; eslv2[4]  = 0.0031; esuv2[4]  = 0.0040;
  eta[5]  = -0.7558; v2[5]  = 0.0459; ev2[5]  = 0.0026; eslv2[5]  = 0.0027; esuv2[5]  = 0.0033;
  eta[6]  = -0.3048; v2[6]  = 0.0466; ev2[6]  = 0.0029; eslv2[6]  = 0.0029; esuv2[6]  = 0.0035;
  eta[7]  =  0.3006; v2[7]  = 0.0448; ev2[7]  = 0.0025; eslv2[7]  = 0.0034; esuv2[7]  = 0.0041;
  eta[8]  =  0.7572; v2[8]  = 0.0450; ev2[8]  = 0.0025; eslv2[8]  = 0.0027; esuv2[8]  = 0.0033;
  eta[9]  =  1.2567; v2[9]  = 0.0411; ev2[9]  = 0.0022; eslv2[9]  = 0.0028; esuv2[9]  = 0.0035;
  eta[10] =  1.7551; v2[10] = 0.0365; ev2[10] = 0.0021; eslv2[10] = 0.0023; esuv2[10] = 0.0054;
  eta[11] =  3.6751; v2[11] = 0.0268; ev2[11] = 0.0021; eslv2[11] = 0.0045; esuv2[11] = 0.0067;
  eta[12] =  4.2536; v2[12] = 0.0196; ev2[12] = 0.0021; eslv2[12] = 0.0054; esuv2[12] = 0.0052;
  eta[13] =  5.0519; v2[13] = 0.0251; ev2[13] = 0.0094; eslv2[13] = 0.0269; esuv2[13] = 0.0092;
  for ( int i = 14; i < 28; ++i )
    {
      eta[i] = -eta[i-14];
      v2[i] = v2[i-14];
      ev2[i] = ev2[i-14];
      eslv2[i] = eslv2[i-14];
      esuv2[i] = esuv2[i-14];
    }

  TGraphErrors* tge_v2 = new TGraphErrors(28,eta,v2,0,ev2);
  tge_v2->SetMarkerStyle(kFullSquare);
  tge_v2->SetMarkerColor(kBlack);

  TGraphAsymmErrors* tgae_v2 = new TGraphAsymmErrors(28,eta,v2,0,0,eslv2,esuv2);
  tgae_v2->SetMarkerStyle(1);
  tgae_v2->SetMarkerColor(1);
  tgae_v2->SetLineWidth(15);
  tgae_v2->SetLineColor(kGray+1);

  double xmin = -5.0;
  double xmax = 5.0;
  double ymin = 0.0;
  double ymax = 0.06;
  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  empty->GetXaxis()->SetTitle("#eta");
  empty->GetYaxis()->SetTitle("v_{2}");
  tgae_v2->Draw("pz");
  tge_v2->Draw("pz");

  TF1* fun_south = new TF1("fun_south","pol1",-5.0, 0.0);
  TF1* fun_north = new TF1("fun_north","pol1", 0.0, 5.0);
  TF1* fun_centr = new TF1("fun_centr","pol0",-1.0, 1.0);
  tge_v2->Fit("fun_south","","",-5.0,0.0);
  tge_v2->Fit("fun_north","","", 0.0,5.0);
  tge_v2->Fit("fun_centr","","",-1.0,1.0);
  fun_south->Draw("same");
  fun_north->Draw("same");
  fun_centr->Draw("same");

  // c1->Print("fig_scale.png");

  double eta_1[14], v2_1[14], ev2_1[14], eslv2_1[14], esuv2_1[14];
  double eta_2[14], v2_2[14], ev2_2[14], eslv2_2[14], esuv2_2[14];
  for ( int i = 0; i < 14; ++i )
    {
      eta_1[i] = eta[i];
      v2_1[i] = v2[i];
      ev2_1[i] = ev2[i];
      eslv2_1[i] = eslv2[i];
      esuv2_1[i] = esuv2[i];
      eta_2[i] = eta[i+14];
      v2_2[i] = v2[i+14];
      ev2_2[i] = ev2[i+14];
      eslv2_2[i] = eslv2[i+14];
      esuv2_2[i] = esuv2[i+14];
    }

  TGraphErrors* tge_v2_1 = new TGraphErrors(14,eta_1,v2_1,0,ev2_1);
  tge_v2_1->SetMarkerStyle(kFullSquare);
  tge_v2_1->SetMarkerColor(kBlack);
  TGraphAsymmErrors* tgae_v2_1 = new TGraphAsymmErrors(14,eta_1,v2_1,0,0,eslv2_1,esuv2_1);
  tgae_v2_1->SetMarkerStyle(1);
  tgae_v2_1->SetMarkerColor(1);
  tgae_v2_1->SetLineWidth(15);
  tgae_v2_1->SetLineColor(kGray+1);

  TGraphErrors* tge_v2_2 = new TGraphErrors(14,eta_2,v2_2,0,ev2_2);
  tge_v2_2->SetMarkerStyle(kOpenSquare);
  tge_v2_2->SetMarkerColor(kBlack);
  TGraphAsymmErrors* tgae_v2_2 = new TGraphAsymmErrors(14,eta_2,v2_2,0,0,eslv2_2,esuv2_2);
  tgae_v2_2->SetMarkerStyle(1);
  tgae_v2_2->SetMarkerColor(kGray+0);
  tgae_v2_2->SetLineWidth(15);
  tgae_v2_2->SetLineColor(kGray+0);

  empty->Draw();
  tgae_v2_2->Draw("pz");
  tgae_v2_1->Draw("pz");
  tge_v2_1->Draw("pz");
  tge_v2_2->Draw("pz");
  fun_south->Draw("same");
  fun_north->Draw("same");
  fun_centr->Draw("same");

  TLegend* leg = new TLegend(0.78,0.75,0.88,0.88);
  leg->AddEntry(tge_v2_1,"Data","p");
  leg->AddEntry(tge_v2_2,"Mirror","p");
  leg->SetTextSize(0.05);
  leg->Draw();

  TLatex* tl1 = new TLatex(-4.5,0.05325,"PHOBOS, PRC 72 051901 (2005)");
  tl1->SetTextSize(0.05);
  tl1->Draw();

  TLatex* tl2 = new TLatex(-3,0.02,Form("v_{2} for |#eta|<1: %.4f",fun_centr->Eval(0)));
  tl2->SetTextSize(0.05);
  tl2->Draw();

  TLatex* tl3 = new TLatex(-3,0.015,Form("v_{2} for 1<|#eta|<3: %.4f",fun_south->Eval(-2)));
  tl3->SetTextSize(0.05);
  tl3->Draw();

  TLatex* tl3 = new TLatex(-3,0.01,Form("Ratio: %.4f", ( fun_centr->Eval(0) / fun_south->Eval(-2) )  ));
  tl3->SetTextSize(0.05);
  tl3->Draw();

  c1->Print("fig_scale.png");
  c1->Print("fig_scale.pdf");

}
