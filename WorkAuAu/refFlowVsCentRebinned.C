// See the bottom of the macro for the list of output files.

void myOptions(Int_t lStat=0);
void myLegendSetUp(TLegend *currentLegend=0,float currentTextSize=0.07);
void myPadSetUp(TPad *currentPad, float currentLeft=0.11, float currentTop=0.04, float currentRight=0.04, float currentBottom=0.15);
void myGraphSetUp(TGraphErrors *currentGraph=0, Float_t currentMarkerSize = 1.0,
                  int currentMarkerStyle=20, int currentMarkerColor=0,
                  int currentLineStyle=1, int currentLineColor=0, int currentFillColor=0, int currentFillStyle=0);


static  int      myDarkRed     = TColor::GetColor(128,0,0);
static  int      myDarkGreen   = TColor::GetColor(0,128,0);
static  int      myDarkBlue    = TColor::GetColor(0,0,128);

Bool_t bRebin = kTRUE;  

void refFlowVsCentRebinned(Int_t rWrite = 0, Int_t rPerformance = 0)
{
 myOptions();
 gROOT->ForceStyle();   
 TDatime now;
 int iDate = now.GetDate();
 int iYear=iDate/10000;
 int iMonth=(iDate%10000)/100;
 int iDay=iDate%100;
 //char* cMonth[12]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
 char cStamp1[25],cStamp2[25];
 //sprintf(cStamp1,"%i %s %i",iDay,cMonth[iMonth-1],iYear);
 //sprintf(cStamp2,"%i/%.2d/%i",iDay,iMonth,iYear);
 
 const Int_t nCentralities = 50;
 
 // Centrality bins:
 Double_t xCent[50] = {0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5, 
                       10.5,11.5,12.5,13.5,14.5,15.5,16.5,17.5,18.5,19.5,
                       21.,23.,25.,27.,29.,31.,33.,35.,37.,39.,
                       41.,43.,45.,47.,49.,51.,53.,55.,57.,59.,
                       61.,63.,65.,67.,69.,71.,73.,75.,77.,79.};   
 Double_t exCent[50] = {0.};
 
 // v2{2}: 
 Double_t V22[] = {2.420509e-02,2.703078e-02,3.055149e-02,3.430685e-02,3.770646e-02,
4.131605e-02,4.468220e-02,4.807997e-02,5.099198e-02,5.400401e-02,
5.715461e-02,5.995449e-02,6.269015e-02,6.494528e-02,6.762260e-02,
7.004811e-02,7.198820e-02,7.432506e-02,7.628393e-02,7.857324e-02,
8.120125e-02,8.455713e-02,8.805196e-02,9.094470e-02,9.343102e-02,
9.593384e-02,9.788518e-02,9.976007e-02,1.017058e-01,1.028503e-01,
1.039796e-01,1.048970e-01,1.054321e-01,1.058401e-01,1.060114e-01,
1.057795e-01,1.055975e-01,1.058080e-01,1.048094e-01,1.044558e-01,
1.037345e-01,1.037953e-01,1.022192e-01,1.028387e-01,1.019666e-01,
1.021492e-01,1.023577e-01,1.037432e-01,1.045945e-01,1.077903e-01}; 
 Double_t V22StatErr[] = {8.785866e-05,9.318537e-05,9.663614e-05,1.005954e-04,1.038919e-04,
1.076056e-04,1.102792e-04,1.140431e-04,1.156746e-04,1.197676e-04,
1.228546e-04,1.250799e-04,1.280185e-04,1.303905e-04,1.346376e-04,
1.363830e-04,1.390494e-04,1.414390e-04,1.459618e-04,1.489325e-04,
1.081354e-04,1.121348e-04,1.166987e-04,1.220324e-04,1.257683e-04,
1.305803e-04,1.353012e-04,1.412582e-04,1.469816e-04,1.529244e-04,
1.580680e-04,1.656866e-04,1.720229e-04,1.796313e-04,1.872899e-04,
1.965870e-04,2.068596e-04,2.179864e-04,2.317650e-04,2.479816e-04,
2.656227e-04,2.862179e-04,3.123013e-04,3.421262e-04,3.792595e-04,
4.282321e-04,4.807014e-04,5.516782e-04,6.398266e-04,7.360318e-04};

 // v2{SP} (eta gap > 1.0):      
 Double_t V2SP[] = {2.130106e-02,2.435402e-02,2.816321e-02,3.188956e-02,3.566601e-02,
3.951162e-02,4.266304e-02,4.626173e-02,4.926470e-02,5.236111e-02,
5.540893e-02,5.805371e-02,6.074272e-02,6.307792e-02,6.607283e-02,
6.858050e-02,7.025335e-02,7.246927e-02,7.447615e-02,7.668431e-02,
7.897235e-02,8.252311e-02,8.572900e-02,8.862134e-02,9.117238e-02,
9.327432e-02,9.522677e-02,9.660688e-02,9.869123e-02,9.970478e-02,
1.002708e-01,1.008174e-01,1.010020e-01,1.010988e-01,1.011032e-01,
1.000526e-01,9.881608e-02,9.847418e-02,9.672397e-02,9.667305e-02,
9.428757e-02,9.120677e-02,8.797762e-02,8.610253e-02,8.394230e-02,
8.041070e-02,7.855092e-02,8.014652e-02,7.073039e-02,7.357049e-02};  
 Double_t V2SPStatErr[] = {2.074075e-04,2.034157e-04,1.957703e-04,1.908029e-04,1.849294e-04,
1.837545e-04,1.837396e-04,1.838488e-04,1.841454e-04,1.869431e-04,
1.878235e-04,1.912247e-04,1.942054e-04,1.953657e-04,2.007491e-04,
2.019173e-04,2.056059e-04,2.092282e-04,2.154226e-04,2.173933e-04,
1.596155e-04,1.648333e-04,1.721508e-04,1.796610e-04,1.881745e-04,
1.979371e-04,2.070464e-04,2.175985e-04,2.295771e-04,2.446827e-04,
2.587786e-04,2.775984e-04,2.947047e-04,3.178706e-04,3.441930e-04,
3.747410e-04,4.153306e-04,4.591145e-04,5.163486e-04,5.747955e-04,
6.562508e-04,7.653615e-04,9.051987e-04,1.065931e-03,1.276695e-03,
1.574969e-03,1.895965e-03,2.250115e-03,3.090780e-03,3.615933e-03};
 Double_t V2SPSysErr[] = {2.074075e-04,2.034157e-04,1.957703e-04,1.908029e-04,1.849294e-04,
1.837545e-04,1.837396e-04,1.838488e-04,1.841454e-04,1.869431e-04,
1.878235e-04,1.912247e-04,1.942054e-04,1.953657e-04,2.007491e-04,
2.019173e-04,2.056059e-04,2.092282e-04,2.154226e-04,2.173933e-04,
1.596155e-04,1.648333e-04,1.721508e-04,1.796610e-04,1.881745e-04,
1.979371e-04,2.070464e-04,2.175985e-04,2.295771e-04,2.446827e-04,
2.587786e-04,2.775984e-04,2.947047e-04,3.178706e-04,3.441930e-04,
3.747410e-04,4.153306e-04,4.591145e-04,5.163486e-04,5.747955e-04,
6.562508e-04,7.653615e-04,9.051987e-04,1.065931e-03,1.276695e-03,
1.574969e-03,1.895965e-03,2.250115e-03,3.090780e-03,3.615933e-03};
 // Calculate combined in quadrature sys. and stat. error: 
 Double_t V2SPSysStatErr[nCentralities] = {0.};
 for (Int_t c=0;c<nCentralities;c++) 
 {
  V2SPSysStatErr[c] = TMath::Sqrt(pow(V2SPSysErr[c],2.)+pow(V2SPStatErr[c],2.)+pow(0.03*4.626173e-02,2.));
 }    
    
 // v2{SP} (eta gap > 0.0):  
 Double_t QaQb_V0_EtaGap00[] = {2.325894e-02,2.593694e-02,2.945582e-02,3.319414e-02,3.686913e-02,
4.038470e-02,4.386371e-02,4.727677e-02,5.034370e-02,5.331245e-02,
5.640731e-02,5.908393e-02,6.194821e-02,6.414316e-02,6.676192e-02,
6.926981e-02,7.124942e-02,7.338955e-02,7.534537e-02,7.755507e-02,
8.042883e-02,8.377299e-02,8.713450e-02,8.988558e-02,9.222654e-02,
9.465976e-02,9.662259e-02,9.838533e-02,1.003657e-01,1.013290e-01,
1.021573e-01,1.031108e-01,1.034099e-01,1.037483e-01,1.038193e-01,
1.030836e-01,1.024550e-01,1.022144e-01,1.010896e-01,1.003615e-01,
9.937872e-02,9.846731e-02,9.588023e-02,9.571284e-02,9.307747e-02,
9.217034e-02,9.126119e-02,9.131787e-02,8.950475e-02,9.222836e-02};
 Double_t errQaQb_V0_EtaGap00[] = {1.074244e-04,1.112029e-04,1.130084e-04,1.168349e-04,1.182064e-04,
1.204549e-04,1.247546e-04,1.273607e-04,1.295207e-04,1.332462e-04,
1.362018e-04,1.384624e-04,1.423423e-04,1.442554e-04,1.487249e-04,
1.502398e-04,1.538279e-04,1.562580e-04,1.608409e-04,1.644491e-04,
1.194855e-04,1.236842e-04,1.285421e-04,1.346166e-04,1.388857e-04,
1.446329e-04,1.500168e-04,1.569676e-04,1.633303e-04,1.704516e-04,
1.778520e-04,1.865271e-04,1.956036e-04,2.054643e-04,2.153007e-04,
2.286678e-04,2.436574e-04,2.596969e-04,2.803926e-04,3.047220e-04,
3.331270e-04,3.664833e-04,4.118274e-04,4.636268e-04,5.330842e-04,
6.200796e-04,7.151101e-04,8.479890e-04,1.026079e-03,1.202475e-03};    
 //  QaQb_V0_EtaGap00:
 Int_t nPointsQaQb_V0_EtaGap00 = sizeof(xCent)/sizeof(Double_t);         
 TGraphErrors *GrQaQb_V0_EtaGap00 = new TGraphErrors(nPointsQaQb_V0_EtaGap00,xCent,QaQb_V0_EtaGap00,exCent,errQaQb_V0_EtaGap00);
 myGraphSetUp(GrQaQb_V0_EtaGap00,0.75,kOpenSquare,kBlue,1,kBlue); 
         
 // v2{4}:       
 Double_t V24[] = {-44.,8.929991e-03,1.538249e-02,2.039141e-02,2.444779e-02,
2.867028e-02,3.269281e-02,3.626870e-02,3.995447e-02,4.271208e-02,
4.568345e-02,4.897344e-02,5.168858e-02,5.399919e-02,5.625026e-02,
5.915024e-02,6.076765e-02,6.313138e-02,6.444763e-02,6.657383e-02,
6.926406e-02,7.220231e-02,7.516436e-02,7.734323e-02,7.966753e-02,
8.157496e-02,8.294946e-02,8.367856e-02,8.502312e-02,8.497611e-02,
8.556932e-02,8.528535e-02,8.518180e-02,8.433332e-02,8.361274e-02,
8.186050e-02,8.063176e-02,8.030987e-02,7.746470e-02,7.428505e-02,
7.084685e-02,7.060003e-02,6.580577e-02,6.447035e-02,5.785129e-02,
5.203995e-02,4.525665e-02}; 
 Double_t V24StatErr[] = {0.000000e+00,4.469321e-03,1.159167e-03,6.698696e-04,5.048081e-04,
3.857036e-04,3.341104e-04,2.930141e-04,2.507839e-04,2.514691e-04,
2.425488e-04,2.298936e-04,2.277990e-04,2.188226e-04,2.299204e-04,
2.217428e-04,2.268487e-04,2.146723e-04,2.316868e-04,2.318329e-04,
1.643222e-04,1.700027e-04,1.752199e-04,1.888604e-04,1.895983e-04,
1.999089e-04,2.135592e-04,2.255372e-04,2.451443e-04,2.652783e-04,
2.807187e-04,3.179848e-04,3.465972e-04,3.988582e-04,4.423813e-04,
5.091861e-04,6.096898e-04,7.051245e-04,8.676153e-04,1.158228e-03,
1.501372e-03,1.854277e-03,2.634282e-03,3.897080e-03,6.042288e-03,
1.372565e-02,2.225528e-02};
 Double_t V24SysErr[] = {0.000000e+00,6.410529e-03,4.059699e-03,1.380303e-03,1.386401e-03,
1.324691e-03,1.323637e-03,1.277620e-03,1.386357e-03,1.248683e-03,
1.176947e-03,1.220325e-03,1.146276e-03,1.189921e-03,1.142882e-03,
1.245528e-03,1.123609e-03,1.204948e-03,1.136454e-03,1.188178e-03,
8.397905e-04,8.412242e-04,8.496689e-04,8.051796e-04,8.383354e-04,
8.540913e-04,8.409681e-04,8.182627e-04,8.230181e-04,8.351450e-04,
8.598540e-04,8.532606e-04,8.860980e-04,8.799271e-04,1.093861e-03,
1.293827e-03,1.108257e-03,1.199848e-03,1.516349e-03,1.726092e-03,
1.965289e-03,2.652755e-03,3.700403e-03,5.581634e-03,6.498875e-03,
1.504874e-02,2.253123e-02};
 // Calculate combined in quadrature sys. and stat. error: 
 Double_t V24SysStatErr[47] = {0.};
 for (Int_t c=0;c<47;c++) 
 {
  V24SysStatErr[c] = TMath::Sqrt(pow(V24SysErr[c],2.)+pow(V24StatErr[c],2.)+pow(0.03*3.626870e-02,2.));
 }    
    
 // v2{6}        
 Double_t V26[] = {-44.,1.423321e-02,1.581362e-02,1.955221e-02,2.407217e-02,
2.844712e-02,3.298782e-02,3.606370e-02,3.968852e-02,4.241349e-02,
4.566376e-02,4.872943e-02,5.159599e-02,5.387742e-02,5.604346e-02,
5.890894e-02,6.059308e-02,6.285176e-02,6.454081e-02,6.638933e-02,
6.906983e-02,7.202423e-02,7.491815e-02,7.734988e-02,7.938127e-02,
8.127143e-02,8.254011e-02,8.324597e-02,8.459111e-02,8.441963e-02,
8.511708e-02,8.459610e-02,8.427834e-02,8.431066e-02,8.313368e-02,
8.226485e-02,7.943093e-02,7.891334e-02,7.480755e-02,7.308909e-02,
7.234384e-02,6.923934e-02,5.909726e-02};
 Double_t V26StatErr[] = {0.000000e+00,4.879988e-03,3.509666e-03,2.202694e-03,1.276984e-03,
6.663474e-04,5.184866e-04,4.160872e-04,3.208725e-04,3.297424e-04,
2.537535e-04,2.819767e-04,2.438709e-04,2.328686e-04,2.818130e-04,
2.623381e-04,2.596004e-04,2.224168e-04,2.313794e-04,2.429875e-04,
1.631309e-04,1.782068e-04,1.724880e-04,1.720756e-04,1.878011e-04,
1.779937e-04,2.281477e-04,2.110524e-04,2.559669e-04,2.614352e-04,
2.074188e-04,3.367986e-04,3.725762e-04,3.101257e-04,5.678973e-04,
3.698334e-04,1.012830e-03,1.272202e-03,1.912697e-03,2.682908e-03,
2.880864e-03,5.743686e-03,1.521541e-02};
 Double_t V26SysErr[] = {0.000000e+00,5.004421e-03,9.402864e-03,2.525333e-03,1.871819e-03,
1.442439e-03,1.475606e-03,1.211104e-03,1.417950e-03,1.219236e-03,
1.161375e-03,1.215354e-03,1.158318e-03,1.168198e-03,1.153236e-03,
1.206354e-03,1.122593e-03,1.167569e-03,1.127301e-03,1.151999e-03,
8.379701e-04,8.288219e-04,8.333615e-04,7.961502e-04,8.323637e-04,
8.539513e-04,8.333497e-04,8.215187e-04,8.254228e-04,8.320366e-04,
8.727773e-04,8.779028e-04,8.806129e-04,8.780106e-04,1.031314e-03,
1.185046e-03,1.416777e-03,1.566047e-03,2.464537e-03,3.083691e-03,
3.303263e-03,6.005737e-03,1.635278e-02};
 // Calculate combined in quadrature sys. and stat. error: 
 Double_t V26SysStatErr[43] = {0.};
 for (Int_t c=0;c<43;c++) 
 {
  V26SysStatErr[c] = TMath::Sqrt(pow(V26SysErr[c],2.)+pow(V26StatErr[c],2.)+pow(0.03*3.606370e-02,2.));
 }  
 
 // v2{8}   
 Double_t V28[] = {-44.,-44.,-44.,1.952045e-02,2.369390e-02,
2.869303e-02,3.290640e-02,3.610693e-02,3.978246e-02,4.247332e-02,
4.564340e-02,4.874435e-02,5.154138e-02,5.391612e-02,5.607667e-02,
5.891868e-02,6.056233e-02,6.286625e-02,6.453377e-02,6.637608e-02,
6.881950e-02,7.195726e-02,7.478452e-02,7.719967e-02,7.933531e-02,
8.095195e-02,8.248186e-02,8.315447e-02,8.457125e-02,8.444266e-02,
8.497288e-02,8.456070e-02,8.423191e-02,8.370223e-02,8.236691e-02,
8.180608e-02,7.934417e-02,7.885544e-02,7.573350e-02,7.295072e-02,
7.390308e-02,7.211272e-02};    
 Double_t V28StatErr[] = {0.000000e+00,0.000000e+00,0.000000e+00,7.539352e-03,3.944978e-03,
1.253248e-03,1.012002e-03,6.329283e-04,4.360791e-04,4.540433e-04,
2.661828e-04,3.742175e-04,2.540728e-04,2.606597e-04,3.761737e-04,
3.264936e-04,3.185124e-04,2.469247e-04,2.493203e-04,2.735972e-04,
1.651921e-04,2.062905e-04,1.847817e-04,2.211669e-04,1.991321e-04,
1.340796e-04,2.758074e-04,2.044411e-04,3.053968e-04,2.722431e-04,
5.035700e-04,3.473569e-04,4.105337e-04,7.913418e-04,8.548541e-04,
1.280096e-03,2.068432e-03,2.493141e-03,3.719605e-03,6.724999e-03,
5.409935e-03,1.401215e-02};   
 Double_t V28SysErr[] = {0.000000e+00,0.000000e+00,0.000000e+00,7.648222e-03,4.104772e-03,
1.774499e-03,1.654488e-03,1.294061e-03,1.439358e-03,1.283565e-03,
1.159846e-03,1.243841e-03,1.154979e-03,1.170810e-03,1.185215e-03,
1.219870e-03,1.137581e-03,1.175481e-03,1.133188e-03,1.161243e-03,
8.363178e-04,8.409710e-04,8.446218e-04,8.048725e-04,8.354533e-04,
8.423581e-04,8.470558e-04,8.233524e-04,8.424173e-04,8.390612e-04,
9.668898e-04,9.219895e-04,9.348268e-04,1.128628e-03,1.320010e-03,
1.636625e-03,2.292508e-03,2.660111e-03,3.960988e-03,6.857876e-03,
5.601397e-03,1.413204e-02};    
 // Calculate combined in quadrature sys. and stat. error: 
 Double_t V28SysStatErr[42] = {0.};
 for (Int_t c=0;c<42;c++) 
 {
  V28SysStatErr[c] = TMath::Sqrt(pow(V28SysErr[c],2.)+pow(V28StatErr[c],2.)+pow(0.03*3.610693e-02,2.));
 }  
      
 // TGraphErrors:
 // v2{2}:
 Int_t nPointsV22 = 50;         
 TGraphErrors *GrV22 = new TGraphErrors(nPointsV22,xCent,V22,exCent,V22StatErr);
 myGraphSetUp(GrV22,0.75,kOpenSquare,kBlue,kSolid,kBlack);
  
 // SP:
 //  Data points:
 Int_t nPointsSP = 50;         
 TGraphErrors *GrSP = new TGraphErrors(nPointsSP,xCent,V2SP,exCent,V2SPStatErr);
 myGraphSetUp(GrSP,0.75,kFullSquare,kBlue,kSolid,kBlack,kBlue-10,1001);
 //  Error mesh (combined in quadrature sys. and stat. error):   
 Int_t nPointsSP_ErrorMesh = sizeof(xCent)/sizeof(Double_t);         
 TGraphErrors *GrSP_ErrorMesh = new TGraphErrors(nPointsSP_ErrorMesh,xCent,V2SP,exCent,V2SPSysStatErr);
 myGraphSetUp(GrSP_ErrorMesh,0.75,kFullCircle,kBlue,kSolid,kBlack,kBlue-10,1001);
 // v2{4}:
 //  Data points:
 //Int_t nPointsV24 = sizeof(xCent)/sizeof(Double_t);         
 Int_t nPointsV24 = 47;         
 TGraphErrors *GrV24 = new TGraphErrors(nPointsV24,xCent,V24,exCent,V24StatErr);
 myGraphSetUp(GrV24,0.75,kFullSquare,kRed,kSolid,kBlack,kRed-10,1001);
 //  Error mesh (combined in quadrature sys. and stat. error):   
 //Int_t nPointsV24_ErrorMesh = sizeof(xCent)/sizeof(Double_t);         
 Int_t nPointsV24_ErrorMesh = 47;         
 TGraphErrors *GrV24_ErrorMesh = new TGraphErrors(nPointsV24_ErrorMesh,xCent,V24,exCent,V24SysStatErr);
 myGraphSetUp(GrV24_ErrorMesh,0.75,kFullSquare,kRed,kSolid,kBlack,kRed-10,1001);
 // v2{6}:
 //  Data points:
 //Int_t nPointsV26 = sizeof(xCent)/sizeof(Double_t);         
 Int_t nPointsV26 = 43;         
 TGraphErrors *GrV26 = new TGraphErrors(nPointsV26,xCent,V26,exCent,V26StatErr);
 myGraphSetUp(GrV26,0.75,kFullSquare,kGreen+2,kSolid,kBlack,kGreen-10,1001);
 //  Error mesh (combined in quadrature sys. and stat. error):   
 //Int_t nPointsV26_ErrorMesh = sizeof(xCent)/sizeof(Double_t);         
 Int_t nPointsV26_ErrorMesh = 43;         
 TGraphErrors *GrV26_ErrorMesh = new TGraphErrors(nPointsV26_ErrorMesh,xCent,V26,exCent,V26SysStatErr);
 myGraphSetUp(GrV26_ErrorMesh,0.75,kFullSquare,kGreen+2,kSolid,kBlack,kGreen-10,1001);
 // v2{8}:
 //  Data points:
 //Int_t nPointsV28 = sizeof(xCent)/sizeof(Double_t);         
 Int_t nPointsV28 = 42;         
 TGraphErrors *GrV28 = new TGraphErrors(nPointsV28,xCent,V28,exCent,V28StatErr);
 myGraphSetUp(GrV28,0.75,kFullSquare,kBlack,kSolid,kBlack,kGray,1001);
 //  Error mesh (combined in quadrature sys. and stat. error):   
 //Int_t nPointsV28_ErrorMesh = sizeof(xCent)/sizeof(Double_t);         
 Int_t nPointsV28_ErrorMesh = 42;         
 TGraphErrors *GrV28_ErrorMesh = new TGraphErrors(nPointsV28_ErrorMesh,xCent,V28,exCent,V28SysStatErr);
 myGraphSetUp(GrV28_ErrorMesh,0.75,kFullSquare,kBlack,kSolid,kBlack,kGray,1001);
    
 // Final plotting:   
 TCanvas *myCan = new TCanvas("myCan",cStamp1);
 myCan->Draw();
 myCan->cd();
    
 TPad *myPad = new TPad("myPad", "The pad",0,0,1,1);
 myPadSetUp(myPad,0.15,0.04,0.04,0.15);
 myPad->Draw();
 myPad->cd();
    
 TH1F *myBlankHisto = new TH1F("myBlankHisto","Blank Histogram",80,0,80);
 myBlankHisto->SetMaximum(0.12);
 myBlankHisto->SetYTitle("v_{2}");
 myBlankHisto->SetXTitle("centrality percentile");
 myBlankHisto->SetNdivisions(505,"y");
 myBlankHisto->Draw();
    
 TLatex *system = new TLatex(0.18,0.91,"ALICE Preliminary, Pb-Pb events at  #sqrt{s_{NN}} = 2.76 TeV");
 system->SetNDC();
 // system->SetTextFont(42);
 system->SetTextSize(0.04);
 system->SetTextColor(myDarkRed);
 system->Draw();
     
 TLegend *myLegend = new TLegend(0.4,0.2,0.7,0.45,"v_{2} (charged hadrons)");
 myLegendSetUp(myLegend,0.04);
 //myLegend->AddEntry(GrV22,"v_{2}{2}","p");
 myLegend->AddEntry(GrQaQb_V0_EtaGap00,"v_{2}{2} (#left|#Delta#eta#right| > 0)","p");
 myLegend->AddEntry(GrSP,"v_{2}{2} (#left|#Delta#eta#right| > 1)","pf");
 myLegend->AddEntry(GrV24,"v_{2}{4}","fp");
 myLegend->AddEntry(GrV26,"v_{2}{6}","fp");
 myLegend->AddEntry(GrV28,"v_{2}{8}","fp");
 myLegend->Draw();
 
 GrV28_ErrorMesh->Draw("same3");
 GrV26_ErrorMesh->Draw("same3");
 GrV24_ErrorMesh->Draw("same3");
 GrV28->Draw("psameX");
 GrV26->Draw("psameX");
 GrV24->Draw("psameX");
 GrSP_ErrorMesh->Draw("same3");
 GrSP->Draw("psameX");
 //GrV22->Draw("psame");
 GrQaQb_V0_EtaGap00->Draw("psame");

 TPad *myPadLogo = new TPad("myPadLogo", "Pad for ALICE Logo",0.18,0.74,0.33,0.89);
 //    myPadLogo->SetFillColor(2); // color to first figure out where is the pad then comment !
 myPadSetUp(myPadLogo,0,0,0,0);
 myPadLogo->Draw();
 myPadLogo->cd();
 TASImage *myAliceLogo = new TASImage("alice_logo_transparent.png");
 myAliceLogo->Draw();  
 
 
 
    /*
    TPad *myPadLogo = new TPad("myPadLogo", "Pad for ALICE Logo",0.47,0.37,0.62,0.60);
    //myPadLogo->SetFillColor(2); // color to first figure out where is the pad then comment !
    myPadSetUp(myPadLogo,0,0,0,0);
    myPadLogo->Draw();
    myPadLogo->cd();
    TASImage *myAliceLogo = new TASImage("alice_logo_transparent.png");
    //.TASImage *myAliceLogo = new TASImage("alice_logo.pdf");     
    myAliceLogo->Draw();
    */
    
    if (rPerformance){
        TLatex *alice = new TLatex(0.75,0.34,"Performance");
        alice->SetNDC();
        alice->SetTextColor(myDarkRed);
        //    alice->SetTextFont(42);
        alice->SetTextSize(0.05);
        alice->SetLineWidth(2);
        alice->Draw();
        
        TText *date = new TText(0.78,0.28,cStamp2);
        date->SetNDC();
        date->SetTextFont(42);
        date->SetTextSize(0.04);
        date->Draw();
        
        TPad *myPadLogo = new TPad("myPadLogo", "Pad for ALICE Logo",0.77,0.37,0.92,0.60);
        myPadLogo->SetFillColor(2); // color to first figure out where is the pad then comment !
        myPadSetUp(myPadLogo,0,0,0,0);
        myPadLogo->Draw();
        myPadLogo->cd();
        TASImage *myAliceLogo = new TASImage("alice_logo_transparent.png");
        //.TASImage *myAliceLogo = new TASImage("alice_logo.pdf");
        
        myAliceLogo->Draw();
    }
    if (rWrite == 1)  myCan->SaveAs("fig_template.pdf");
    if (rWrite == 2)  myCan->SaveAs("fig_template.png");
}

void myLegendSetUp(TLegend *currentLegend=0,float currentTextSize=0.07){
    currentLegend->SetTextFont(42);
    currentLegend->SetBorderSize(0);
    currentLegend->SetFillStyle(0);
    currentLegend->SetFillColor(0);
    currentLegend->SetMargin(0.25);
    currentLegend->SetTextSize(currentTextSize);
    currentLegend->SetEntrySeparation(0.5);
    return;
}

void myPadSetUp(TPad *currentPad, float currentLeft=0.11, float currentTop=0.04, float currentRight=0.04, float currentBottom=0.15){
    currentPad->SetLeftMargin(currentLeft);
    currentPad->SetTopMargin(currentTop);
    currentPad->SetRightMargin(currentRight);
    currentPad->SetBottomMargin(currentBottom);
    return;
}

void myGraphSetUp(TGraphErrors *currentGraph=0, Float_t currentMarkerSize = 1.0,
                  int currentMarkerStyle=20, int currentMarkerColor=0,
                  int currentLineStyle=1, int currentLineColor=0, int currentFillColor=0, int currentFillStyle=0)
{
    currentGraph->SetMarkerSize(currentMarkerSize);
    currentGraph->SetMarkerStyle(currentMarkerStyle);
    currentGraph->SetMarkerColor(currentMarkerColor);
    currentGraph->SetLineStyle(currentLineStyle);
    currentGraph->SetLineColor(currentLineColor);
    currentGraph->SetFillColor(currentFillColor);
    currentGraph->SetFillStyle(currentFillStyle);
    return;
}


void myOptions(Int_t lStat=0){
    // Set gStyle
    int font = 42;
    // From plain
    gStyle->SetFrameBorderMode(0);
    gStyle->SetFrameFillColor(0);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadBorderMode(0);
    gStyle->SetPadColor(10);
    gStyle->SetCanvasColor(10);
    gStyle->SetTitleFillColor(10);
    gStyle->SetTitleBorderSize(1);
    gStyle->SetStatColor(10);
    gStyle->SetStatBorderSize(1);
    gStyle->SetLegendBorderSize(1);
    //
    gStyle->SetDrawBorder(0);
    gStyle->SetTextFont(font);
    gStyle->SetStatFont(font);
    gStyle->SetStatFontSize(0.05);
    gStyle->SetStatX(0.97);
    gStyle->SetStatY(0.98);
    gStyle->SetStatH(0.03);
    gStyle->SetStatW(0.3);
    gStyle->SetTickLength(0.02,"y");
    gStyle->SetEndErrorSize(3);
    gStyle->SetLabelSize(0.05,"xyz");
    gStyle->SetLabelFont(font,"xyz"); 
    gStyle->SetLabelOffset(0.01,"xyz");
    gStyle->SetTitleFont(font,"xyz");  
    gStyle->SetTitleOffset(1.0,"xyz");  
    gStyle->SetTitleSize(0.06,"xyz");  
    gStyle->SetMarkerSize(1); 
    gStyle->SetPalette(1,0); 
    if (lStat){
        gStyle->SetOptTitle(1);
        gStyle->SetOptStat(1111);
        gStyle->SetOptFit(1111);
    }
    else {
        gStyle->SetOptTitle(0);
        gStyle->SetOptStat(0);
        gStyle->SetOptFit(0);
    }
}


//===================================================================

// OUTPUT FILES:

// Remarks: LHC10h period (pass 1) 
// Merged output file with results for V0 centrality estimator is (achieved stat. is ~ 56.7 K per central;ity bin width of 1%):
//  /data/alice2/ab/grid/21-20_patch_light/minBiasV0/cent01_7980/v2/merged/outputCentrality.root

// To estimates systematical error TPC and SPD1clusters were also used as centrality estimators. Output files are:
//  /data/alice2/ab/grid/21-20_patch_light/minBiasTPC/cent01_7980/v2/merged/outputCentrality.root
//  /data/alice2/ab/grid/21-20_patch_light/minBiasSPD/cent01_7980/v2/merged/outputCentrality.root
