/*************************************************************

Copyright (c) 	2006, Fernando Herrero Carrón
				2016, Ángel Lareo Fernández
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
	Neuron::ConstructorArgs argsN;
    Synapsis::ConstructorArgs argsS, argsS_exc, argsS_ind;
	

	argsN.params[Neuron::a]= 0.1; //0.02;
	argsN.params[Neuron::b]= 0.26;
	argsN.params[Neuron::c]=-65.0;
	argsN.params[Neuron::d]= 2; //0.05;
	argsN.params[Neuron::threshold]=30.0;


    /**
	 * (Destexhe, 1994)
	 * Alpha	= 5	(/ms mM)	: forward (binding) rate
	 * Beta	= 0.18	(/ms)		: backward (unbinding) rate
	 * Erev	= -80	(mV)		: reversal potential
	 * Prethresh = 0 			: voltage level nec for release
	 * Deadtime = 1	(ms)		: mimimum time between release events
	 * gmax		(umho)		: maximum conductance
	 */

	
	argsS.params[Synapsis::alpha] = 5;
	argsS.params[Synapsis::beta] = 0.18;
	argsS.params[Synapsis::threshold] = 0;
	argsS.params[Synapsis::esyn] = -80;
	argsS.params[Synapsis::gsyn] = -0.05;
    argsS.params[Synapsis::T] = 1.0;
    argsS.params[Synapsis::max_release_time] = 10;

	Neuron DP(argsN), DP2(argsN);

    Synapsis s(DP, Neuron::v, DP2, Neuron::v, argsS, 20);

	const double step = 0.01;

	for (double t = 0; t < 30; t += step){
		//CN.add_synaptic_input(0);
        DP.step(step);
        DP2.step(step);
        //s.step(step);
    }

	for (double it = 0; it < 10; it += 1){
		for (double t = 0; t < 1; t += step){
			DP.add_synaptic_input(3);
        	DP.step(step);
        	s.step(step);
        	
			cout << DP.get(Neuron::v) << " " << DP2.get(Neuron::v) << " " << DP2.get_synaptic_input()  << " 3" << endl;
			DP2.step(step);
	    }
	    for (double t = 0; t < 10; t += step){
			//DP.add_synaptic_input(10);
			//CN.add_synaptic_input(0);
        	DP.step(step);
        	s.step(step);
        	
			cout << DP.get(Neuron::v) << " " << DP2.get(Neuron::v) << " " << DP2.get_synaptic_input() << " 0" << endl;
			DP2.step(step);
	    }

	    for (double t = 0; t < 1; t += step){
			DP2.add_synaptic_input(3);
        	DP.step(step);
        	s.step(step);
        	
			cout << DP.get(Neuron::v) << " " << DP2.get(Neuron::v) << " " << DP2.get_synaptic_input()  << " 3" << endl;
			DP2.step(step);
	    }

	    for (double t = 0; t < 20; t += step){
			//DP.add_synaptic_input(10);
			//CN.add_synaptic_input(0);
        	DP.step(step);
        	s.step(step);
        	
			cout << DP.get(Neuron::v) << " " << DP2.get(Neuron::v) << " " << DP2.get_synaptic_input() << " 0" << endl;
			DP2.step(step);
	    }
	}

	return 0;
}
