/*************************************************************

Copyright (c) 2006, Fernando Herrero Carrón
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
typedef IntegratedSystemWrapper<IzhikevichModel<double>, Integrator> IzNeuron;
//typedef DiffusionSynapsis<Neuron, Neuron, Integrator> Synapsis;
//typedef DiffusionSynapsis<Neuron, IzNeuron, Integrator> SynapsisN2IzN;
//typedef DiffusionSynapsis<IzNeuron, Neuron, Integrator> SynapsisIzN2N;

int main(int argc, char **argv) {
	IzNeuron::ConstructorArgs argsIzN;
	//Neuron::ConstructorArgs argsN;
    //Synapsis::ConstructorArgs argsS, argsS_exc, argsS_ind;
	

	argsIzN.params[IzNeuron::a]= 0.02;
	argsIzN.params[IzNeuron::b]= 0.2;
	argsIzN.params[IzNeuron::c]= -50.0;
	argsIzN.params[IzNeuron::d]= 2; //0.05;
	argsIzN.params[IzNeuron::threshold]=30.0;

	//argsN.params[Neuron::e] = 3.281;
 	//argsN.params[Neuron::mu] = 0.0021;
 	//argsN.params[Neuron::S] = 4;

    /**
	 * (Destexhe, 1994)
	 * Alpha	= 5	(/ms mM)	: forward (binding) rate
	 * Beta	= 0.18	(/ms)		: backward (unbinding) rate
	 * Erev	= -80	(mV)		: reversal potential
	 * Prethresh = 0 			: voltage level nec for release
	 * Deadtime = 1	(ms)		: mimimum time between release events
	 * gmax		(umho)		: maximum conductance
	 */

	/*
	argsS.params[Synapsis::alpha] = 10;
	argsS.params[Synapsis::beta] = 100;
	argsS.params[Synapsis::threshold] = 0;
	argsS.params[Synapsis::esyn] = 0.9;
	argsS.params[Synapsis::gsyn] = 0.1;
    argsS.params[Synapsis::T] = 1.0;
    argsS.params[Synapsis::max_release_time] = 50;

	argsS_ind.params[Synapsis::alpha] = 100;
	argsS_ind.params[Synapsis::beta] = 10;
	argsS_ind.params[Synapsis::threshold] = 0;
	argsS_ind.params[Synapsis::esyn] = -0.2;
	argsS_ind.params[Synapsis::gsyn] = 0.01;
    argsS_ind.params[Synapsis::T] = 1.0;
    argsS_ind.params[Synapsis::max_release_time] = 2;

	argsS_exc.params[Synapsis::alpha] = 100;
	argsS_exc.params[Synapsis::beta] = 10;
	argsS_exc.params[Synapsis::threshold] = 0;
	argsS_exc.params[Synapsis::esyn] = -0.5;
	argsS_exc.params[Synapsis::gsyn] = 0.05;
    argsS_exc.params[Synapsis::T] = 1.0;
    argsS_exc.params[Synapsis::max_release_time] = 5;*/

	//Neuron DP(argsN), VPd(argsN), PCN(argsN);
	IzNeuron CN(argsIzN);

//    Synapsis s1(VPd, Neuron::x, PCN, Neuron::x, argsS, 20);
//    Synapsis s2(VPd, Neuron::x, DP, Neuron::x, argsS, 20);

//    SynapsisN2IzN sA(PCN, Neuron::x, CN, IzNeuron::v, argsS_exc, 20);
//    SynapsisN2IzN sB(DP, Neuron::x, CN, IzNeuron::v, argsS_exc, 20);

//    SynapsisIzN2N sBack(CN, IzNeuron::v, VPd, Neuron::x, argsS_ind, 20);

	const double step = 0.1;

//	for (double t = 0; t < 2000; t += step){
		//DP.add_synaptic_input(0);
		//CN.add_synaptic_input(0);
//        VPd.step(step);
//        s1.step(step);
//        s2.step(step);
//        DP.step(step);
//        sA.step(step);
//        sB.step(step);
//        CN.step(step);
//        sBack.step(step);
//    }

    for (double t = 0; t < 500; t += step){
        CN.step(step);
        cout << CN.get(IzNeuron::v) << endl;
    }

   for (double t = 0; t < 1500; t += step){
    	CN.add_synaptic_input(4);
        CN.step(step);
        cout << CN.get(IzNeuron::v) << endl;
    }

     for (double t = 0; t < 1600; t += step){
    	CN.add_synaptic_input(8);
        CN.step(step);
        cout << CN.get(IzNeuron::v) << endl;
    }

/*    for (double t = 0; t < 400; t += step){
    	CN.add_synaptic_input(0.15);
        CN.step(step);
        cout << CN.get(IzNeuron::v) << endl;
    }

    for (double t = 0; t < 20; t += step){
    	CN.add_synaptic_input(2);
        CN.step(step);
        cout << CN.get(IzNeuron::v) << endl;
    }*/
	return 0;
}
