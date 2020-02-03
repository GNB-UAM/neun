/*************************************************************

Copyright (c) 2016, Ángel Lareo Fernández
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of the author nor the names of his contributors
      may be used to endorse or promote products derived from this
      software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*************************************************************/

#include <HindmarshRoseModel.h>
#include <IzhikevichModel.h>
#include <DifferentialNeuronWrapper.h>
#include <IntegratedSystemWrapper.h>
#include <RungeKutta4.h>
#include <Stepper.h>
#include <DiffusionSynapsis.h>

#include <iostream>

using namespace std;

typedef RungeKutta4 Integrator;
//typedef Stepper StepIntegrator;
//typedef DifferentialNeuronWrapper<HindmarshRoseModel<double>, Integrator> Neuron;
typedef IntegratedSystemWrapper<IzhikevichModel<double>, Integrator> Neuron;
typedef DiffusionSynapsis<Neuron, Neuron, Integrator> Synapsis;

//typedef DiffusionSynapsis<Neuron, IzNeuron, Integrator> SynapsisN2IzN;
//typedef DiffusionSynapsis<IzNeuron, Neuron, Integrator> SynapsisIzN2N;

int main(int argc, char **argv) {
	Neuron::ConstructorArgs argsLTS_VPd, argsRS_DP, argsRS_PCN, argsRS_CN, argsRZN;
    Synapsis::ConstructorArgs argsS_corol, argsS_exc_DP, argsS_exc_PCN, argsS_inh_DP, argsS_inh_PCN;
	

	argsRZN.params[Neuron::a]= 0.1;
	argsRZN.params[Neuron::b]= 0.26;
	argsRZN.params[Neuron::c]=-65.0;
	argsRZN.params[Neuron::d]= 2;
	argsRZN.params[Neuron::threshold]=30.0;

	argsLTS_VPd.params[Neuron::a]= 0.02;
	argsLTS_VPd.params[Neuron::b]= 0.25;
	argsLTS_VPd.params[Neuron::c]=-65.0;
	argsLTS_VPd.params[Neuron::d]= 2.3; 
	argsLTS_VPd.params[Neuron::threshold]=30.0;

	argsRS_DP.params[Neuron::a]= 0.02;
	argsRS_DP.params[Neuron::b]= 0.2;
	argsRS_DP.params[Neuron::c]=-65.0;
	argsRS_DP.params[Neuron::d]= 6;
	argsRS_DP.params[Neuron::threshold]=30.0;	

	argsRS_PCN.params[Neuron::a]= 0.02;
	argsRS_PCN.params[Neuron::b]= 0.2;
	argsRS_PCN.params[Neuron::c]=-60.0;
	argsRS_PCN.params[Neuron::d]= 4;
	argsRS_PCN.params[Neuron::threshold]=30.0;	

	argsRS_CN.params[Neuron::a]= 0.02;
	argsRS_CN.params[Neuron::b]= 0.2;
	argsRS_CN.params[Neuron::c]=-65.0;
	argsRS_CN.params[Neuron::d]= 6;
	argsRS_CN.params[Neuron::threshold]=30.0;	

	/*argsBurstN.params[Neuron::a]= 0.02; //0.02;
	argsBurstN.params[Neuron::b]= 0.2;
	argsBurstN.params[Neuron::c]=-50.0;
	argsBurstN.params[Neuron::d]= 2; //0.05;
	argsBurstN.params[Neuron::threshold]=30.0;*/

    /**
	 * (Destexhe, 1994)
	 * Alpha	= 5	(/ms mM)	: forward (binding) rate
	 * Beta	= 0.18	(/ms)		: backward (unbinding) rate
	 * Erev	= -80	(mV)		: reversal potential
	 * Prethresh = 0 			: voltage level nec for release
	 * Deadtime = 1	(ms)		: mimimum time between release events
	 * gmax		(umho)		: maximum conductance
	 */

	
	argsS_corol.params[Synapsis::alpha] = 5;
	argsS_corol.params[Synapsis::beta] = 0.02;
	argsS_corol.params[Synapsis::threshold] = 0;
	argsS_corol.params[Synapsis::esyn] = -80;
	argsS_corol.params[Synapsis::gsyn] = 0.3;
    argsS_corol.params[Synapsis::T] = 6;
    argsS_corol.params[Synapsis::max_release_time] = 300;

	argsS_inh_DP.params[Synapsis::alpha] = 5;
	argsS_inh_DP.params[Synapsis::beta] = 0.005;
	argsS_inh_DP.params[Synapsis::threshold] = 0;
	argsS_inh_DP.params[Synapsis::esyn] = -80;
	argsS_inh_DP.params[Synapsis::gsyn] = -0.12; //-0.05;
    argsS_inh_DP.params[Synapsis::T] = 1.0;
    argsS_inh_DP.params[Synapsis::max_release_time] = 80;

	argsS_inh_PCN.params[Synapsis::alpha] = 5;
	argsS_inh_PCN.params[Synapsis::beta] = 0.005;
	argsS_inh_PCN.params[Synapsis::threshold] = 0;
	argsS_inh_PCN.params[Synapsis::esyn] = -80;
	argsS_inh_PCN.params[Synapsis::gsyn] = -0.1;
    argsS_inh_PCN.params[Synapsis::T] = 1.0;
    argsS_inh_PCN.params[Synapsis::max_release_time] = 80;

	argsS_exc_DP.params[Synapsis::alpha] = 5;
	argsS_exc_DP.params[Synapsis::beta] = 0.18;
	argsS_exc_DP.params[Synapsis::threshold] = 0;
	argsS_exc_DP.params[Synapsis::esyn] = -80;
	argsS_exc_DP.params[Synapsis::gsyn] = 0.15;
    argsS_exc_DP.params[Synapsis::T] = 1.0;
    argsS_exc_DP.params[Synapsis::max_release_time] = 20;

	argsS_exc_PCN.params[Synapsis::alpha] = 5;
	argsS_exc_PCN.params[Synapsis::beta] = 0.18;
	argsS_exc_PCN.params[Synapsis::threshold] = 0;
	argsS_exc_PCN.params[Synapsis::esyn] = -80;
	argsS_exc_PCN.params[Synapsis::gsyn] = 0.05;
    argsS_exc_PCN.params[Synapsis::T] = 1.0;
    argsS_exc_PCN.params[Synapsis::max_release_time] = 20;

	Neuron VPd(argsLTS_VPd), DP(argsRZN), PCN(argsRS_PCN), CN(argsRZN);

    Synapsis s1(VPd, Neuron::v, PCN, Neuron::v, argsS_inh_PCN, 5);
    Synapsis s2(VPd, Neuron::v, DP, Neuron::v, argsS_inh_DP, 5);
    Synapsis sA(PCN, Neuron::v, CN, Neuron::v, argsS_exc_PCN, 5);
    Synapsis sB(DP, Neuron::v, CN, Neuron::v, argsS_exc_DP, 5);
    Synapsis sBack(CN, Neuron::v, VPd, Neuron::v, argsS_corol, 5);

	const double step = 0.01;

	//for (double it = 0; it < 2; it += 1){
		for (double t = 0; t < 50; t += step){
			DP.add_synaptic_input(2.5);
			PCN.add_synaptic_input(8);
	        s1.step(step);
	        s2.step(step);
	        sA.step(step);
	        sB.step(step);
	        sBack.step(step);
			/*cout << VPd.get_synaptic_input() << " " 
				 << DP.get_synaptic_input() << " "
				 << PCN.get_synaptic_input() << " " 
				 << CN.get_synaptic_input() << endl;*/
		    VPd.step(step);
		    DP.step(step);
		    PCN.step(step);
	        CN.step(step);
	        //cout << VPd.get(Neuron::v) << " " << DP.get(Neuron::v) << " " << PCN.get(Neuron::v) << " " << CN.get(Neuron::v) << endl;
	    }

		for (double t = 0; t < 400; t += step){
			DP.add_synaptic_input(2.5);
			PCN.add_synaptic_input(8);
	        s1.step(step);
	        s2.step(step);
	        sA.step(step);
	        sB.step(step);
	        sBack.step(step);
			//cout << VPd.get_synaptic_input() << " " << DP.get_synaptic_input() << " " << PCN.get_synaptic_input() << " " << CN.get_synaptic_input() << endl;
			VPd.step(step);
		    DP.step(step);
		    PCN.step(step);
	        CN.step(step);
	        cout << VPd.get(Neuron::v) << " " << DP.get(Neuron::v) << " " << PCN.get(Neuron::v) << " " << CN.get(Neuron::v) << endl;
	    }
	    for (double t = 0; t < /*80*/ 40; t += step){
			//VPd.add_synaptic_input(10);
			DP.add_synaptic_input(2.5);
			PCN.add_synaptic_input(20);
	        s1.step(step);
	        s2.step(step);
	        sA.step(step);
	        sB.step(step);
	        sBack.step(step);
			//cout << VPd.get_synaptic_input() << " " << DP.get_synaptic_input() << " " << PCN.get_synaptic_input() << " " << CN.get_synaptic_input() << endl;
		    VPd.step(step);
		    DP.step(step);
		    PCN.step(step);
	        CN.step(step);
			cout << VPd.get(Neuron::v) << " " << DP.get(Neuron::v) << " " << PCN.get(Neuron::v) << " " << CN.get(Neuron::v) << endl;
	    }
	    for (double t = 0; t < 400; t += step){
			DP.add_synaptic_input(2.5);
			PCN.add_synaptic_input(8);
	        s1.step(step);
	        s2.step(step);
	        sA.step(step);
	        sB.step(step);
	        sBack.step(step);
			//cout << VPd.get_synaptic_input() << " " << DP.get_synaptic_input() << " " << PCN.get_synaptic_input() << " " << CN.get_synaptic_input() << endl;
		    VPd.step(step);
		    DP.step(step);
		    PCN.step(step);
	        CN.step(step);
	        cout << VPd.get(Neuron::v) << " " << DP.get(Neuron::v) << " " << PCN.get(Neuron::v) << " " << CN.get(Neuron::v) << endl;
	    }
//	}

	return 0;
}
