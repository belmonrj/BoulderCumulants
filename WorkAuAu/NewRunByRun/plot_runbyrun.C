void crunch(int);


void plot_runbyrun()
{

  gStyle->SetOptTitle(1);

  ifstream fin;
  fin.open("run14auau.list");
  int run;
  while ( fin >> run )
    {
      //if ( run > 406000) break;
      crunch(run);
    }

}


void crunch(int run)
{

  TFile* file = TFile::Open(Form("RunFiles/%d.root",run));
  if ( file == NULL ) { cout << "run number " << run << " not found" << endl; return; }

  TProfile* tp1f_south_c2 = (TProfile*)file->Get("centrality_recoffsets_south_0_2");
  TProfile* tp1f_north_c2 = (TProfile*)file->Get("centrality_recoffsets_north_0_2");
  TProfile* tp1f_south_s2 = (TProfile*)file->Get("centrality_recoffsets_south_1_2");
  TProfile* tp1f_north_s2 = (TProfile*)file->Get("centrality_recoffsets_north_1_2");

  TCanvas* c1 = new TCanvas("c1","",800,800);
  c1->Divide(2,2);
  c1->cd(1);
  tp1f_south_c2->SetTitle("south cos2#phi");
  tp1f_south_c2->Draw();
  tp1f_south_c2->SetMaximum(0.2);
  tp1f_south_c2->SetMinimum(-0.2);
  c1->cd(2);
  tp1f_north_c2->SetTitle("north cos2#phi");
  tp1f_north_c2->Draw();
  tp1f_north_c2->SetMaximum(0.2);
  tp1f_north_c2->SetMinimum(-0.2);
  c1->cd(3);
  tp1f_south_s2->SetTitle("south sin2#phi");
  tp1f_south_s2->Draw();
  tp1f_south_s2->SetMaximum(0.2);
  tp1f_south_s2->SetMinimum(-0.2);
  c1->cd(4);
  tp1f_north_s2->SetTitle("north sin2#phi");
  tp1f_north_s2->Draw();
  tp1f_north_s2->SetMaximum(0.2);
  tp1f_north_s2->SetMinimum(-0.2);

  c1->Print(Form("RunFigs/rbr_h2_%d.png",run));
  c1->Print(Form("RunFigs/rbr_h2_%d.pdf",run));

  delete c1;

}
