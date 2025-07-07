#ifndef IZHIKEVICHSYSTEMWRAPPER_H_
#define IZHIKEVICHSYSTEMWRAPPER_H_

#include "SystemWrapper.h"
#include "IzhikevichModel.h"

template <typename Precission>
class IzhikevichSystemWrapper : public SystemWrapper<IzhikevichModel<Precission>> {
public:
    using Base = SystemWrapper<IzhikevichModel<Precission>>;
    using typename Base::precission_t;
    using typename Base::variable;
    using typename Base::parameter;

    void pre_step(precission_t /*h*/) {
    }

    void post_step(precission_t /*h*/) {
        // Izhikevich reset logic: if v >= threshold, reset v and update u
        if (this->get(variable::v) >= this->get(parameter::threshold)) {
            this->set(variable::v, this->get(parameter::c));
            this->set(variable::u, this->get(variable::u) + this->get(parameter::d));
        }
    }
};

#endif /* IZHIKEVICHSYSTEMWRAPPER_H_ */