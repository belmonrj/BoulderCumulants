#include "BoulderCumulants.h"
#include "TComplex.h"


// <cos(n(phi1-phi2))>
float BoulderCumulants::calc2_event(float Xn, float Yn, float M)
{
  if ( M < 2 ) return -9999;
  float numerator = Xn*Xn + Yn*Yn - M;
  float denominator = M*(M-1);
  return numerator/denominator;
}

// <cos(n(phi1+phi2))>
float BoulderCumulants::calccossum2_event(TComplex& Qn, TComplex& Q2n, float M)
{
  if ( M < 2 ) return -9999;
  TComplex result = Qn*Qn - Q2n;
  float numerator = result.Re();
  float denominator = M*(M-1);
  return numerator/denominator;
}

// <sin(n(phi1+phi2))>
float BoulderCumulants::calcsinsum2_event(TComplex& Qn, TComplex& Q2n, float M)
{
  if ( M < 2 ) return -9999;
  TComplex result = Qn*Qn - Q2n;
  float numerator = result.Im();
  float denominator = M*(M-1);
  return numerator/denominator;
}

// <cos(n(phi1-phi2-phi3))>
float BoulderCumulants::calccos3_event(TComplex& Qn, TComplex& Q2n, float M)
{
  if ( M < 3 ) return -9999;
  TComplex result = Qn*TComplex::Conjugate(Qn)*TComplex::Conjugate(Qn) - Qn*TComplex::Conjugate(Q2n);
  float numerator = result.Re() - 2*(M-1)*TComplex::Conjugate(Qn).Re();
  float denominator = M*(M-1)*(M-2);
  return numerator/denominator;
}

// <sin(n(phi1-phi2-phi3))>
float BoulderCumulants::calcsin3_event(TComplex& Qn, TComplex& Q2n, float M)
{
  if ( M < 3 ) return -9999;
  TComplex result = Qn*TComplex::Conjugate(Qn)*TComplex::Conjugate(Qn) - Qn*TComplex::Conjugate(Q2n);
  float numerator = result.Im() - 2*(M-1)*TComplex::Conjugate(Qn).Im();
  float denominator = M*(M-1)*(M-2);
  return numerator/denominator;
}

// <cos(n(phi1+phi2-phi3-phi4))>
float BoulderCumulants::calc4_event(float Xn, float Yn, float X2n, float Y2n, float M)
{

  if ( M < 4 ) return -9999;

  float Qn2 = Xn*Xn+Yn*Yn;
  float Qn2d = Xn*Xn-Yn*Yn;

  float one   = Qn2*Qn2;
  float two   = X2n*X2n+Y2n*Y2n;
  float three = (2*(X2n*Qn2d + 2*Y2n*Xn*Yn));
  float four  = 2*(2*(M-2)*Qn2);
  float five  = 2*M*(M-3);

  float numerator = one + two - three - four + five;
  float denominator = M*(M-1)*(M-2)*(M-3);

  return numerator/denominator;

}

// <cos(n(phi1+phi2+phi3-phi4-phi5-phi6))>
float BoulderCumulants::calc6_event(TComplex& qn, TComplex& q2n, TComplex& q3n, float M)
{

  if ( M < 6 ) return -9999;

  // TComplex qn, q2n, q3n;
  // qn = TComplex(Q2x,Q2y);
  // q2n = TComplex(Q4x,Q4y);
  // q3n = TComplex(Q6x,Q6y);

  TComplex temp1;

  // first term
  // |Qn|^6 + 9*|Q2n|^2|Qn|^2 - 6 x Re[Q2n x Qn x Qn* x Qn* x Qn*] / (Mx(M-1)x(M-2)x(M-3)x(M-4)x(M-5)
  double term1a = TMath::Power((qn*TComplex::Conjugate(qn)),3);
  double term1b = 9.0 * q2n*TComplex::Conjugate(q2n) * qn*TComplex::Conjugate(qn);
  temp1 = q2n * qn * TComplex::Conjugate(qn) * TComplex::Conjugate(qn) * TComplex::Conjugate(qn);
  double term1c = -6.0 * temp1.Re();
  double term1 = (term1a+term1b+term1c)/(M*(M-1)*(M-2)*(M-3)*(M-4)*(M-5));

  // second term
  // 4 * [Re[Q3nQn*Qn*Qn*] - 3 Re[Q3nQ2n*Qn*]] / (M(M-1)(M-2)(M-3)(M-4)(M-5)
  temp1 = q3n * TComplex::Conjugate(qn) * TComplex::Conjugate(qn) * TComplex::Conjugate(qn);
  double term2a = temp1.Re();
  temp1 = q3n * TComplex::Conjugate(q2n) * TComplex::Conjugate(qn);
  double term2b = -3.0 * temp1.Re();
  double term2 = 4.0 * (term2a+term2b)/(M*(M-1)*(M-2)*(M-3)*(M-4)*(M-5));

  // third term
  // +2 * (9*(M-4)*Re[Q2nQn*qn*] + 2 |Q3n|^2) / ((M(M-1)(M-2)(M-3)(M-4)(M-5))
  temp1 = q2n*TComplex::Conjugate(qn)*TComplex::Conjugate(qn);
  double term3a = 9.0*(M-4)*temp1.Re();
  double term3b = 2.0*q3n*TComplex::Conjugate(q3n);
  double term3 = 2.0 * (term3a + term3b) / (M*(M-1)*(M-2)*(M-3)*(M-4)*(M-5));

  // fourth term
  //double term4 = -9.0 * (TMath::Power(qn*TComplex::Conjugate(qn),2)+q2n*TComplex::Conjugate(q2n)) / (M*(M-1)*(M-2)*(M-3)*(M-5));
  double term4 = -9.0 * (TMath::Power(qn*TComplex::Conjugate(qn),2)+q2n*TComplex::Conjugate(q2n)) ;
  term4 /= (M*(M-1)*(M-2)*(M-3)*(M-5));

  // fifth term
  //double term5 = 18.0 * qn*TComplex::Conjugate(qn) / (M*(M-1)*(M-3)*(M-4));
  double term5 = 18.0 * qn*TComplex::Conjugate(qn) ;
  term5 /=  (M*(M-1)*(M-3)*(M-4));

  // sixth term
  double term6 = -6.0/((M-1)*(M-2)*(M-3));

  // cos(n(phi1+phi2+phi3-phi4-phi5-phi6))
  double six = term1 + term2 + term3 + term4 + term5 + term6;

  return (float)six; // should be smarter about this at some point

}

