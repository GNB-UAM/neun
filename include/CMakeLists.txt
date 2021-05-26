install(FILES algorithm.h CurrentPulse.h NeuronBase.h CurrentSource.h DirectSynapsis.h
		SigmoidalDirectSynapsis.h DiffusionSynapsis.h #DiscreteDiffusionSynapse.h
		ElectricalSynapsis.h analysis.h DifferentialNeuronWrapper.h DynamicalSystemWrapper.h
		GradualActivationSynapsis.h
		DESTINATION ${PROJECT_NAME}/${PROJECT_VERSION}/include)
