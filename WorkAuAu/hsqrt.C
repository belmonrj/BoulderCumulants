TH1D* hsqrt(TProfile*);
TH1D* hsqrt(TH1D*);

TH1D* hsqrt(TProfile* hp)
{
  if ( hp == NULL ) return NULL;
  TH1D* h1 = hp->ProjectionX();
  return hsqrt(h1);
}

TH1D* hsqrt(TH1D* h)
{
  if ( h == NULL ) return NULL;
  TH1D* hr = (TH1D*)h->Clone(Form("sqrt_%s",h->GetName()));
  int nbins = h->GetNbinsX();
  for ( int i = 0; i < nbins; ++i )
    {
      double get_content = h->GetBinContent(i+1);
      double set_content = 0;
      if ( get_content > 0 ) set_content = sqrt(get_content);
      else set_content = -sqrt(-get_content);
      hr->SetBinContent(i+1,set_content);
      double get_error = h->GetBinError(i+1);
      double set_error = 0;
      if ( get_error > 0 ) set_error = (1.0/(2.0*set_content))*get_error;
      hr->SetBinError(i+1,set_error);
    }
  return hr;
}
