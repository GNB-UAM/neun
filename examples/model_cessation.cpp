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
	Neuron::ConstructorArgs argsN, argsBurstN;
    Synapsis::ConstructorArgs argsS, argsS_exc, argsS_ind;
	

	argsN.params[Neuron::a]= 0.1; //0.02;
	argsN.params[Neuron::b]= 0.26;
	argsN.params[Neuron::c]=-65.0;
	argsN.params[Neuron::d]= 2; //0.05;
	argsN.params[Neuron::threshold]=30.0;

	argsBurstN.params[Neuron::a]= 0.02; //0.02;
	argsBurstN.params[Neuron::b]= 0.2;
	argsBurstN.params[Neuron::c]=-50.0;
	argsBurstN.params[Neuron::d]= 2; //0.05;
	argsBurstN.params[Neuron::threshold]=30.0;

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
	argsS.params[Synapsis::gsyn] = -0.7;
    argsS.params[Synapsis::T] = 1.0;
    argsS.params[Synapsis::max_release_time] = 200;

	argsS_exc.params[Synapsis::alpha] = 5;
	argsS_exc.params[Synapsis::beta] = 0.18;
	argsS_exc.params[Synapsis::threshold] = 0;
	argsS_exc.params[Synapsis::esyn] = -80;
	argsS_exc.params[Synapsis::gsyn] = 0.1;
    argsS_exc.params[Synapsis::T] = 1.0;
    argsS_exc.params[Synapsis::max_release_time] = 5;

	argsS_ind.params[Synapsis::alpha] = 5;
	argsS_ind.params[Synapsis::beta] = 0.18;
	argsS_ind.params[Synapsis::threshold] = 0;
	argsS_ind.params[Synapsis::esyn] = -80;
	argsS_ind.params[Synapsis::gsyn] = 0.7;
    argsS_ind.params[Synapsis::T] = 1.0;
    argsS_ind.params[Synapsis::max_release_time] = 15;


	Neuron DP(argsBurstN), VPd(argsBurstN), PCN(argsBurstN), CN(argsN);

    Synapsis s1(VPd, Neuron::v, PCN, Neuron::v, argsS, 1);
    Synapsis s2(VPd, Neuron::v, DP, Neuron::v, argsS, 1);

    Synapsis sA(PCN, Neuron::v, CN, Neuron::v, argsS_exc, 10);
    Synapsis sB(DP, Neuron::v, CN, Neuron::v, argsS_exc, 10);

    Synapsis sBack(CN, Neuron::v, VPd, Neuron::v, argsS_ind, 10);

	const double step = 0.1;

	for (double t = 0; t < 30; t += step){
		//CN.add_synaptic_input(0);
        VPd.step(step);
        s1.step(step);
        s2.step(step);
        DP.step(step);
        PCN.step(step);
        sA.step(step);
        sB.step(step);
        CN.step(step);
        sBack.step(step);
    }

	//for (double it = 0; it < 2; it += 1){
		for (double t = 0; t < 100; t += step){
			//DP.add_synaptic_input(4);
			//PCN.add_synaptic_input(4);
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

		for (double t = 0; t < 3200; t += step){
			DP.add_synaptic_input(4);
			PCN.add_synaptic_input(4);
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
	        cout << VPd.get(Neuron::v) << " " << DP.get(Neuron::v) << " " << PCN.get(Neuron::v) << " " << CN.get(Neuron::v) << endl;
	    }
	    for (double t = 0; t < 1000; t += step){
			VPd.add_synaptic_input(10);
			DP.add_synaptic_input(4);
			PCN.add_synaptic_input(4);
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
			cout << VPd.get(Neuron::v) << " " << DP.get(Neuron::v) << " " << PCN.get(Neuron::v) << " " << CN.get(Neuron::v) << endl;
	    }
	    		for (double t = 0; t < 1200; t += step){
			DP.add_synaptic_input(4);
			PCN.add_synaptic_input(4);
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
	        cout << VPd.get(Neuron::v) << " " << DP.get(Neuron::v) << " " << PCN.get(Neuron::v) << " " << CN.get(Neuron::v) << endl;
	    }
//	}

	return 0;
}
