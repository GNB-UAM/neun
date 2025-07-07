/*************************************************************

Copyright (c) 2006, Fernando Herrero Carrón
Copyright (c) 2020, Angel Lareo <angel.lareo@gmail.com>
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

#include <DifferentialNeuronWrapper.h>
#include <HodgkinHuxleyModel.h>
#include <RungeKutta4.h>
#include <SystemWrapper.h>
#include <iostream>

typedef RungeKutta4 Integrator;
typedef DifferentialNeuronWrapper<SystemWrapper<HodgkinHuxleyModel<double>>, Integrator>
    Neuron;

int main(int argc, char **argv) {
  // Struct to initialize neuron model parameters
  Neuron::ConstructorArgs args;

  // Set the parameter values
  args.params[Neuron::cm] = 1 * 7.854e-3;
  args.params[Neuron::vna] = 50;
  args.params[Neuron::vk] = -77;
  args.params[Neuron::vl] = -54.387;
  args.params[Neuron::gna] = 120 * 7.854e-3;
  args.params[Neuron::gk] = 36 * 7.854e-3;
  args.params[Neuron::gl] = 0.3 * 7.854e-3;

  // Initialize a new neuron model
  Neuron n(args);

  // You can also initialize the variables of the neuron model to a given value
  n.set(Neuron::v, -80);
  n.set(Neuron::m, 0.1);
  n.set(Neuron::n, 0.7);
  n.set(Neuron::h, 0.01);

  // Set the integration step
  const double step = 0.001;

  // Perform the simulation
  double simulation_time = 100;
  for (double time = 0; time < simulation_time; time += step) {
    n.step(step);

    std::cout << time << " " << n.get(Neuron::v) << std::endl;
  }

  return 0;
}
