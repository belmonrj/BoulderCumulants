#include "HeaderFileYouNeed.h"
#include "AnotherHeaderFileYouNeed.h"
// etc...

int main()
{

  // open the data file
  File* file = File::Open("YourDataFile");

  // get the data from the file
  Data* data = file->GetData();

  // get the number of events
  int number_of_events = data->GetNumberOfEvents();

  // loop over events
  for ( int ievent = 0; ievent < number_of_events; ++ievent )
    {
      // get the current event
      Event* event = data->GetEvent(ievent);

      // get the number of particles in the event
      int number_of_particles = event->GetNumberOfParticles();

      // initialize the q-vectors for each event
      double qx2 = 0;
      double qy2 = 0;
      double qx4 = 0;
      double qy4 = 0;
      double qx6 = 0;
      double qy6 = 0;
      // loop over particle in the current event
      for ( int iparticle = 0; iparticle < number_of_particles; ++iparticle)
	{
	  // get the current particle in the current event
	  Particle* particle = event->GetParticle(iparticle);

	  // get the momentum vector from the particle
	  double px = particle->px();
	  double py = particle->py();

	  // calculate the phi angle
	  double phi = atan2(py,px);
	  // add to the q-vectors
	  qx2 += cos(2*phi);
	  qy2 += sin(2*phi);
	  qx4 += cos(4*phi);
	  qy4 += sin(4*phi);
	  qx6 += cos(6*phi);
	  qy6 += sin(6*phi);

	} // end of loop over particles

      // add a shortcut for the number of tracks
      double m = (double)number_of_particles;

      // create complex numbers based on the Q-vector components
      TComplex Q2(qx2,qy2);
      TComplex Q4(qx4,qy4);
      TComplex Q6(qx6,qy6);

      // ---------------------------------------------------------------
      // --- calculate the main terms
      // calculate <2> = <cos(n(phi1-phi2)>
      double two = calc2_event(qx2,qy2,m);
      // calculate <4> = <cos(n(phi1+phi2-phi3-phi4))>
      double four = calc4_event(qx2,qy2,qx4,qy4,m);
      // calculate <6> = <cos(n(phi1+phi2+phi3-phi4-phi5-phi6))>
      double six = calc6_event(Q2,Q4,Q6,m);

      // ---------------------------------------------------------------
      // --- acceptance terms
      // calculate <cos(n(phi1))> and <sin(n(phi1))>
      double cos1 = qx2/m;
      double sin1 = qy2/m;
      // calculate <cos(n(phi1+phi2))> and <sin(n(phi1+phi2))>
      double cossum2 = calccossum2_event(Q2,Q4,m);
      double sinsum2 = calcsinsum2_event(Q2,Q4,m);
      // calculate <cos(n(phi1-phi2-phi3))> and <sin(n(phi1-phi2-phi3))>
      double cos3 = calccos3_event(Q2,Q4,m);
      double sin3 = calcsin3_event(Q2,Q4,m);

      // ---------------------------------------------------------------
      // --- fill histograms
      histogram_two->Fill(m,two);
      histogram_four->Fill(m,four);
      histogram_six->Fill(m,six);
      histogram_cos1->Fill(m,cos1);
      histogram_sin1->Fill(m,sin1);
      histogram_cossum2->Fill(m,cossum2);
      histogram_sinsum2->Fill(m,sinsum2);
      histogram_cos3->Fill(m,cos3);
      histogram_sin3->Fill(m,sin3);

    } // end of loop over events

  // now that we're done with the events, we can do the final calculations

  // -------------------------------------------------------------------
  // --- this is the part where the pseudo code is really, really pseudo

  // two particle stuff
  c22_uncorrected = two;
  c22_corrected = two - cos1*cos1 - sin1*sin1;
  v22_corrected = sqrt(c22_corrected);

  // four particle stuff
  c24_uncorrected = four - 2*two*two;
  term1 = 4*cos1*cos3;
  term2 = 4*sin1*sin3;
  term3 = cossum2*cossum2;
  term4 = sinsum2*sinsum2;
  term5 = 4*cossum2*(cos1*cos1 - sin1*sin1);
  term6 = 8*sinsum2*sin1*cos1;
  term7 = 8*two*(cos1*cos1 + sin1*sin1);
  term8 = 6*(cos1*cos1 + sin1*sin1)*(cos1*cos1 + sin1*sin1);
  c24_corrected = c24_uncorrected - term1 + term2 - term3 - term4 + term5 + term6 + term7 - term8;

  // six particle stuff
  c26_uncorrected = six - 9*four*two + 12*two*two*two;

}
