/*************************************************************

Copyright (c) 2006, Fernando Herrero Carrón
          (c) 2016-2020, Ángel Lareo <angel.lareo@gmail.com>
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

$Id: HindmarshRoseModel.h 203 2007-06-26 14:46:34Z elferdo $
*************************************************************/

#ifndef HINDMARSHROSEMODEL_H_
#define HINDMARSHROSEMODEL_H_

#include <algorithm>
#include <cmath>

#include "NeuronBase.h"

/**
 * (Hindmarsh and Rose, 1984)
 * e = 3.0
 * mu = 0.0021
 * S = 4
 */

template <typename Precission>
class HindmarshRoseModel : public NeuronBase<Precission> {
 public:
  typedef Precission precission_t;

  enum variable { x, y, z, n_variables };
  enum parameter { e, mu, S, n_parameters };

 protected:
  Precission m_variables[n_variables];
  Precission m_parameters[n_parameters];

 public:
  void eval(const Precission *const vars, Precission *const params,
            Precission *const incs) const {
    incs[x] = vars[y] + 3.0 * vars[x] * vars[x] - vars[x] * vars[x] * vars[x] -
              vars[z] + params[e] + SYNAPTIC_INPUT;
    incs[y] = 1 - 5.0 * vars[x] * vars[x] - vars[y];
    incs[z] = params[mu] * (-vars[z] + params[S] * (vars[x] + 1.6));
  }
};

#endif /*HINDMARSHROSEMODEL_H_*/
