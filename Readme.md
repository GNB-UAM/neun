# Neun

![Boost v1.45 dependency](https://img.shields.io/badge/boost-v1.45-blue?style=flat-square)
![CMake v2.8 dependency](https://img.shields.io/badge/cmake-v2.8-blue?style=flat-square)

A library for the simulation of dynamical systems, aimed to model neural
networks with high performance. It is written in an object oriented fashion
with heavily templated C++.

Forked from: https://code.launchpad.net/~elferdo/neun/trunk

## Build

To build it, just type:
```
mkdir build && cd build
cmake ..
```

Install it using:
```
make install
```

The library will install a pkg-config file called "neun.pc" under
${prefix}/${project_name}/${project_version}/pkgconfig. If you want
other applications to be able to find it, you must add this directory
to your PKG_CONFIG_PATH

<!--  
USING ECLIPSE

cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug .. 
-->

## Usage

In order to perform any simulation first you need to define the numerical integrator you are going to use, e.g.:
```
typedef RungeKutta4 Integrator;
```

Then, you define the neuron model and the precision of the simulation, e.g.:
```
typedef HodgkinHuxleyModel<double> HHModel;
```

Finally, you wrapp the model and the numerical integrator to build an integrable dynamical system, e.g.:
```
typedef DifferentialNeuronWrapper<HHModel, Integrator> Neuron;
```

### Integrators

Actual integrators are:
 - Stepper
 - Euler
 - RungeKutta4
 - RungeKutta6

### Neuron models

Currently implemented neuron models:
 - Hodgkin-Huxley conductance model (Hodgkin and Huxley, 1952)
 - Izhikevich spiking neuron model (Izhikevich, 2003)
 - Simple oscillator
 - Matsuoka oscillator (Matsuoka, 1985)
 - Rowat and Selverston (Rowat and Selverston, 1997)
 - Rulkov Map model (Nikolai F. Rulkov, 2002)
 - Bistable Rulkov Map model (Nikolai F. Rulkov, 2002)
 - Vavoulis model

### Synapsis models

Currently implemented synapsis models are:
 - Diffusion synapsis (Destexhe et al. 1994)
 - Electrical synapsis
 - Conductance-based direct synapsis
 - Sigmoidal direct synapsis

