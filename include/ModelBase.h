#ifndef MODELBASE_H_
#define MODELBASE_H_

#ifndef __AVR_ARCH__
#include <type_traits>
#endif  //__AVR_ARCH__

template <typename Precission>
class ModelBase {
public:
    static_assert(std::is_arithmetic_v<Precission>, "Precission must be an arithmetic type");

	typedef Precission precission_t;

	enum variable {x, y, n_variables = 1};
	enum parameter {alpha, beta, n_parameters = 1};
	
	void eval(precission_t * const vars, precission_t * const params, precission_t *incs) const
	{
	}

	// pre_step and post_step are optional in Model concept
	void pre_step(precission_t h)
	{
		// Pre-step actions
	}
	void post_step(precission_t h)
	{
		// Post-step actions
	}
};

#endif /*MODELBASE_H_*/