TFile* fout;

void make_cumulants()
{

  fout = TFile::Open("ampt_cumulants_non.root","recreate");

  argument("dAu",200);
  argument("dAu",62);
  argument("dAu",39);
  argument("dAu",20);
  //argument("pAu",200);

  fout->Write();
  fout->Close();

}

void argument(const char* system, int energy)
{

  // --- now bill stuff
  TFile *bill = TFile::Open(Form("%s%d_non_cumulant.root",system,energy));
  int bin_size = 50; // PbPb: maximum 100      pPb: 50

  TProfile* tp1f_raa4 = (TProfile*)bill->Get("raa4_Ncharge");
  TProfile* tp1f_raa2 = (TProfile*)bill->Get("raa2_Ncharge");
  TProfile* tp1f_gapp = (TProfile*)bill->Get("comp_Ncharge");
  TH1D* th1d_raa4 = tp1f_raa4->ProjectionX("th1d_raa4");
  TH1D* th1d_raa2 = tp1f_raa2->ProjectionX("th1d_raa2");
  TH1D* th1d_gapp = tp1f_gapp->ProjectionX("th1d_gapp");

  TH1D* th1d_c2 = (TH1D*)th1d_raa2->Clone("th1d_c2");
  th1d_c2->Multiply(th1d_raa2);
  th1d_c2->Scale(2.0);
  TH1D* th1d_c24 = (TH1D*)th1d_raa4->Clone("th1d_c24");
  th1d_c24->Add(th1d_c2, -1.0);
  TH1D* th1d_cv24 = (TH1D*)th1d_c24->Clone("th1d_cv24");
  for (int i = 1; i < bin_size+1; i++)
    {
      double temp_1 = th1d_cv24->GetBinContent(i);
      double erro_1 = th1d_cv24->GetBinError(i);
      if (temp_1 >= 0) th1d_cv24->SetBinContent(i, -9999);
      else
	{
	  double temp_2 = pow(-temp_1, 0.25);
	  //cout << temp_1 << " " << fabs(temp_1) << endl;
	  double erro_2 = 0.25 * erro_1 * fabs(temp_2) / fabs(temp_1);
	  th1d_cv24->SetBinContent(i, temp_2);
	  th1d_cv24->SetBinError(i, erro_2);
	}
    }
  TH1D* th1d_cv22 = (TH1D*)th1d_raa2->Clone("th1d_cv22");
  for (int i = 1; i < bin_size+1; i++)
    {
      double temp_1 = th1d_cv22->GetBinContent(i);
      double erro_1 = th1d_cv22->GetBinError(i);
      if (temp_1 <= 0) th1d_cv22->SetBinContent(i, -9999);
      else
	{
	  double temp_2 = pow(temp_1, 0.5);
	  double erro_2 = 0.5 * erro_1 * fabs(temp_2) / fabs(temp_1);
	  th1d_cv22->SetBinContent(i, temp_2);
	  th1d_cv22->SetBinError(i, erro_2);
	}
    }
  TH1D* th1d_cv22gap = (TH1D*)th1d_gapp->Clone("th1d_cv22gap");
  for (int i = 1; i < bin_size+1; i++)
    {
      double temp_1 = th1d_cv22gap->GetBinContent(i);
      double erro_1 = th1d_cv22gap->GetBinError(i);
      if (temp_1 <= 0) th1d_cv22gap->SetBinContent(i, -9999);
      else
	{
	  double temp_2 = pow(temp_1, 0.5);
	  double erro_2 = 0.5 * erro_1 * fabs(temp_2) / fabs(temp_1);
	  th1d_cv22gap->SetBinContent(i, temp_2);
	  th1d_cv22gap->SetBinError(i, erro_2);
	}
    }

  // ---
  // --- it never stops
  // ---

  // ------------------------------------------------------------------------------
  TH1D* th1d_v2_mid = (TH1D*)th1d_c24->Clone("th1d_v2_mid");
  TH1D* th1d_v2_sigma = (TH1D*)th1d_c24->Clone("th1d_v2_sigma");
  for (int i = 1; i < bin_size+1; i++)
    {
      double temp_1 = th1d_cv24->GetBinContent(i);
      double temp_2 = th1d_cv22->GetBinContent(i);
      double etemp_1 = th1d_cv24->GetBinError(i);
      double etemp_2 = th1d_cv22->GetBinError(i);
      if (temp_1 <= 0)
	{
	  th1d_v2_mid->SetBinContent(i, temp_1);
	  th1d_v2_sigma->SetBinContent(i, temp_1);
	}
      else
	{
	  double v2_mid = (temp_1 * temp_1 + temp_2 * temp_2) / 2;
	  double v2_sigma = (temp_2 * temp_2 - temp_1 * temp_1) / 2;
	  v2_mid = TMath::Sqrt(v2_mid);
	  if (v2_sigma > 0) v2_sigma = TMath::Sqrt(v2_sigma)/v2_mid;
	  else v2_sigma = -9999;
	  double ev2_mid = v2_mid*sqrt( (etemp_1/temp_1)*(etemp_1/temp_1) + (etemp_2/temp_2)*(etemp_2/temp_2) );
	  double ev2_sigma = v2_sigma*(ev2_mid/v2_mid);
	  th1d_v2_mid->SetBinContent(i, v2_mid);
	  th1d_v2_sigma->SetBinContent(i, v2_sigma);
	  th1d_v2_mid->SetBinError(i, ev2_mid);
	  th1d_v2_sigma->SetBinError(i, ev2_sigma);
	}
    }

  TFile *fppp = TFile::Open(Form("%s%d_non_ppplane.root",system,energy));
  TProfile* v2s = (TProfile*)fppp->Get("v2s");
  TH1D* th1d_v2_pplane = v2s->ProjectionX("th1d_v2_pplane");

  fout->cd();
  th1d_v2_pplane->SetName(Form("th1d_AMPT%s%d_non_v2pplane",system,energy));
  th1d_v2_pplane->SetTitle("");
  th1d_v2_pplane->Write();
  th1d_v2_mid->SetName(Form("th1d_AMPT%s%d_non_v2mid",system,energy));
  th1d_v2_mid->SetTitle("");
  th1d_v2_mid->Write();
  th1d_v2_sigma->SetName(Form("th1d_AMPT%s%d_non_v2sigma",system,energy));
  th1d_v2_sigma->SetTitle("");
  th1d_v2_sigma->Write();
  th1d_cv22gap->SetName(Form("th1d_AMPT%s%d_non_v22gap",system,energy));
  th1d_cv22gap->SetTitle("");
  th1d_cv22gap->Write();
  th1d_cv22->SetName(Form("th1d_AMPT%s%d_non_v22",system,energy));
  th1d_cv22->SetTitle("");
  th1d_cv22->Write();
  th1d_cv24->SetName(Form("th1d_AMPT%s%d_non_v24",system,energy));
  th1d_cv24->SetTitle("");
  th1d_cv24->Write();
  th1d_c2->SetName(Form("th1d_AMPT%s%d_non_222",system,energy));
  th1d_c2->SetTitle("");
  th1d_c2->Write();
  th1d_raa4->SetName(Form("th1d_AMPT%s%d_non_four",system,energy));
  th1d_raa4->SetTitle("");
  th1d_raa4->Write();
  th1d_c24->SetName(Form("th1d_AMPT%s%d_non_c24",system,energy));
  th1d_c24->SetTitle("");
  th1d_c24->Write();

}



double calc_corr_four(double four, double two, double cos1, double sin1, double cossum2, double sinsum2, double cos3, double sin3)
{
  double uncorr = four - 2*two*two;
  double corr_term1 = 4*cos1*cos3;
  double corr_term2 = 4*sin1*sin3;
  double corr_term3 = cossum2*cossum2;
  double corr_term4 = sinsum2*sinsum2;
  double corr_term5 = 4*cossum2*(cos1*cos1 - sin1*sin1);
  double corr_term6 = 8*sinsum2*sin1*cos1;
  double corr_term7 = 8*two*(cos1*cos1 + sin1*sin1);
  double corr_term8 = 6*(cos1*cos1 + sin1*sin1)*(cos1*cos1 + sin1*sin1);
  double result = uncorr - corr_term1 + corr_term2 - corr_term3 - corr_term4 + corr_term5 + corr_term6 + corr_term7 - corr_term8;
  return result;
}

