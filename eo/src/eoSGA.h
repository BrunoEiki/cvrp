// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

//-----------------------------------------------------------------------------
// eoSGA.h
// (c) GeNeura Team, 2000 - EEAAX 1999 - Maarten Keijzer 2000
/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Contact: todos@geneura.ugr.es, http://geneura.ugr.es
             Marc.Schoenauer@polytechnique.fr
             mak@dhi.dk
 */
//-----------------------------------------------------------------------------

#ifndef _eoSGA_h
#define _eoSGA_h

#include "eoInvalidateOps.h"
#include "eoContinue.h"
#include "eoPop.h"
#include "eoSelectOne.h"
#include "eoSelectPerc.h"
#include "eoEvalFunc.h"
#include "eoAlgo.h"
#include "apply.h"

/** The Simple Genetic Algorithm, following Holland and Goldberg
 *
 * Needs a selector (class eoSelectOne) a crossover (eoQuad, i.e. a
 * 2->2 operator) and a mutation with their respective rates, of
 * course an evaluation function (eoEvalFunc) and a continuator
 * (eoContinue) which gives the stopping criterion. Performs full
 * generational replacement.
 *
 * @ingroup Algorithms
 */
template <class EOT>
class eoSGA : public eoAlgo<EOT>
{
public:
  // added this second ctor as I didn't like the ordering of the parameters
  // in the one above. Any objection :-) MS
  eoSGA(
      eoSelectOne<EOT> &_select,
      eoQuadOp<EOT> &_cross, float _crate,
      eoMonOp<EOT> &_mutate, float _mrate,
      eoEvalFunc<EOT> &_eval,
      eoContinue<EOT> &_cont)
      : cont(_cont),
        mutate(_mutate),
        mutationRate(_mrate),
        cross(_cross),
        crossoverRate(_crate),
        select(_select),
        eval(_eval) {}

  void operator()(eoPop<EOT> &_pop)
  {
    eoPop<EOT> offspring;

    // cross.className()
    std::ofstream out("/home/eiki/Documents/cvrp/eo/tutorial/Lesson1/academic_cvrp-2-rj-17.json.txt", std::ios::out | std::ios::app);
    // std::ofstream out("/home/eiki/cvrp/eo/tutorial/Lesson1/cumulative_results/all_generations_Antwerp1.txt", std::ios::out | std::ios::app);
    // std::ofstream out("/home/eiki/cvrp/eo/tutorial/Lesson1/li_vehicles.txt", std::ios::out | std::ios::app);
    // std::ofstream out2("/home/eiki/cvrp/eo/tutorial/Lesson1/last_generation_teste.txt", std::ios::out | std::ios::app);

    if (!out)
    {
      std::cerr << "Erro ao abrir o arquivo.\n";
    }
    do
    {
      select(_pop, offspring);

      unsigned i;

      for (i = 0; i < _pop.size() / 2; i++)
      {
        if (rng.flip(crossoverRate))
        {
          // this crossover generates 2 offspring from two parents
          if (cross(offspring[2 * i], offspring[2 * i + 1]))
          {
            // invalidates parents
            offspring[2 * i].invalidate();
            offspring[2 * i + 1].invalidate();
          }
        }
      }

      for (i = 0; i < offspring.size(); i++)
      {
        if (rng.flip(mutationRate))
        {
          if (mutate(offspring[i]))
            offspring[i].invalidate();
        }
      }

      _pop.swap(offspring);
      apply<EOT>(eval, _pop);

      std::stringstream bestof_generation;
      _pop.sort();

      bestof_generation << std::fixed << _pop.back();

      // ! get only the total distance
      // ! Slice 6:17 to get only the value and make sum easier
      out << bestof_generation.str().substr(0, 10) << "\n";
      std:cout << bestof_generation.str().substr(0, 10) << "\n";
      out.flush();
      // out << bestof_generation.str() << "\n";

      std::stringstream().swap(bestof_generation);

    } while (cont(_pop));
    // out << "\n";
    // std::stringstream bestof_generation2;
    // bestof_generation2 << std::fixed << _pop.back();
    // out2 << bestof_generation2.str().substr(0, 10) << "\n";

    out.close();
    // out2.close();
  }

private:
  eoContinue<EOT> &cont;
  /// eoInvalidateMonOp invalidates the embedded operator
  eoInvalidateMonOp<EOT> mutate;
  float mutationRate;
  // eoInvalidateQuadOp invalidates the embedded operator
  eoInvalidateQuadOp<EOT> cross;
  float crossoverRate;
  eoSelectPerc<EOT> select;
  eoEvalFunc<EOT> &eval;
};

#endif


// // // -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

// // //-----------------------------------------------------------------------------
// // // eoSGA.h
// // // (c) GeNeura Team, 2000 - EEAAX 1999 - Maarten Keijzer 2000
// // /*
// //     This library is free software; you can redistribute it and/or
// //     modify it under the terms of the GNU Lesser General Public
// //     License as published by the Free Software Foundation; either
// //     version 2 of the License, or (at your option) any later version.

// //     This library is distributed in the hope that it will be useful,
// //     but WITHOUT ANY WARRANTY; without even the implied warranty of
// //     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// //     Lesser General Public License for more details.

// //     You should have received a copy of the GNU Lesser General Public
// //     License along with this library; if not, write to the Free Software
// //     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

// //     Contact: todos@geneura.ugr.es, http://geneura.ugr.es
// //              Marc.Schoenauer@polytechnique.fr
// //              mak@dhi.dk
// //  */
// // //-----------------------------------------------------------------------------

// // #ifndef _eoSGA_h
// // #define _eoSGA_h

// // #include "eoInvalidateOps.h"
// // #include "eoContinue.h"
// // #include "eoPop.h"
// // #include "eoSurviveAndDie.h"
// // #include "eoSelectPerc.h"
// // #include "eoEvalFunc.h"
// // #include "eoAlgo.h"
// // #include "apply.h"

// // /** The Simple Genetic Algorithm, following Holland and Goldberg
// //  *
// //  * Needs a selector (class eoSelectOne) a crossover (eoQuad, i.e. a
// //  * 2->2 operator) and a mutation with their respective rates, of
// //  * course an evaluation function (eoEvalFunc) and a continuator
// //  * (eoContinue) which gives the stopping criterion. Performs full
// //  * generational replacement.
// //  *
// //  * @ingroup Algorithms
// //  */
// // template <class EOT>
// // class eoSGA : public eoAlgo<EOT>
// // {
// // public:
// //   // added this second ctor as I didn't like the ordering of the parameters
// //   // in the one above. Any objection :-) MS
// //   eoSGA(
// //       eoReplacement<EOT> &_select,
// //       eoQuadOp<EOT> &_cross, float _crate,
// //       eoMonOp<EOT> &_mutate, float _mrate,
// //       eoEvalFunc<EOT> &_eval,
// //       eoContinue<EOT> &_cont)
// //       : cont(_cont),
// //         mutate(_mutate),
// //         mutationRate(_mrate),
// //         cross(_cross),
// //         crossoverRate(_crate),
// //         select(_select),
// //         eval(_eval) {}

// //   void operator()(eoPop<EOT> &_pop)
// //   {
// //     eoPop<EOT> offspring;

// //     do
// //     {
// //       select(_pop, offspring);

// //       unsigned i;

// //       for (i = 0; i < _pop.size() / 2; i++)
// //       {
// //         if (rng.flip(crossoverRate))
// //         {
// //           // this crossover generates 2 offspring from two parents
// //           if (cross(offspring[2 * i], offspring[2 * i + 1]))
// //           {
// //             offspring[2 * i].invalidate();
// //             offspring[2 * i + 1].invalidate();
// //           }
// //         }
// //       }

// //       for (i = 0; i < offspring.size(); i++)
// //       {
// //         if (rng.flip(mutationRate))
// //         {
// //           if (mutate(offspring[i]))
// //             offspring[i].invalidate();
// //         }
// //       }

// //       _pop.swap(offspring);
// //       apply<EOT>(eval, _pop);

// //     } while (cont(_pop));
// //   }

// // private:
// //   eoContinue<EOT> &cont;
// //   /// eoInvalidateMonOp invalidates the embedded operator
// //   eoInvalidateMonOp<EOT> mutate;
// //   float mutationRate;
// //   // eoInvalidateQuadOp invalidates the embedded operator
// //   eoInvalidateQuadOp<EOT> cross;
// //   float crossoverRate;
// //   eoDeterministicSaDReplacement<EOT> select;
// //   eoEvalFunc<EOT> &eval;
// // };

// // #endif

// // -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

// //-----------------------------------------------------------------------------
// // eoSGA.h
// // (c) GeNeura Team, 2000 - EEAAX 1999 - Maarten Keijzer 2000
// /*
//     This library is free software; you can redistribute it and/or
//     modify it under the terms of the GNU Lesser General Public
//     License as published by the Free Software Foundation; either
//     version 2 of the License, or (at your option) any later version.

//     This library is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//     Lesser General Public License for more details.

//     You should have received a copy of the GNU Lesser General Public
//     License along with this library; if not, write to the Free Software
//     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

//     Contact: todos@geneura.ugr.es, http://geneura.ugr.es
//              Marc.Schoenauer@polytechnique.fr
//              mak@dhi.dk
//  */
// //-----------------------------------------------------------------------------

// #ifndef _eoSGA_h
// #define _eoSGA_h

// #include "eoInvalidateOps.h"
// #include "eoContinue.h"
// #include "eoPop.h"
// #include "eoSelectOne.h"
// #include "eoSelectPerc.h"
// #include "eoEvalFunc.h"
// #include "eoAlgo.h"
// #include "apply.h"

// /** The Simple Genetic Algorithm, following Holland and Goldberg
//  *
//  * Needs a selector (class eoSelectOne) a crossover (eoQuad, i.e. a
//  * 2->2 operator) and a mutation with their respective rates, of
//  * course an evaluation function (eoEvalFunc) and a continuator
//  * (eoContinue) which gives the stopping criterion. Performs full
//  * generational replacement.
//  *
//  * @ingroup Algorithms
//  */
// template <class EOT>
// class eoSGA : public eoAlgo<EOT>
// {
// public:
//   // added this second ctor as I didn't like the ordering of the parameters
//   // in the one above. Any objection :-) MS
//   eoSGA(
//       eoSelectOne<EOT> &_select,
//       eoQuadOp<EOT> &_cross, float _crate,
//       eoMonOp<EOT> &_mutate, float _mrate,
//       eoEvalFunc<EOT> &_eval,
//       eoContinue<EOT> &_cont)
//       : cont(_cont),
//         mutate(_mutate),
//         mutationRate(_mrate),
//         cross(_cross),
//         crossoverRate(_crate),
//         select(_select),
//         eval(_eval) {}

//   void operator()(eoPop<EOT> &_pop)
//   {
//     eoPop<EOT> offspring;

//     do
//     {
//       select(_pop, offspring);

//       unsigned i;

//       for (i = 0; i < _pop.size() / 2; i++)
//       {
//         if (rng.flip(crossoverRate))
//         {
//           // this crossover generates 2 offspring from two parents
//           if (cross(offspring[2 * i], offspring[2 * i + 1]))
//           {
//             // invalidates parents
//             offspring[2 * i].invalidate();
//             offspring[2 * i + 1].invalidate();
//           }
//         }
//       }

//       for (i = 0; i < offspring.size(); i++)
//       {
//         if (rng.flip(mutationRate))
//         {
//           if (mutate(offspring[i]))
//             offspring[i].invalidate();
//         }
//       }

//       _pop.swap(offspring);
//       apply<EOT>(eval, _pop);

//       std::stringstream bestof_generation;
//       _pop.sort();
//       bestof_generation << std::fixed << _pop.back();
//       // ! get only the total distance
//       // ! Slice 6:17 to get only the value and make sum easier
//       std::cout << bestof_generation.str().substr(0, 10) << ",";
//       std::stringstream().swap(bestof_generation);
//     } while (cont(_pop));
//     std::cout << "\n";
//   }

// private:
//   eoContinue<EOT> &cont;
//   /// eoInvalidateMonOp invalidates the embedded operator
//   eoInvalidateMonOp<EOT> mutate;
//   float mutationRate;
//   // eoInvalidateQuadOp invalidates the embedded operator
//   eoInvalidateQuadOp<EOT> cross;
//   float crossoverRate;
//   eoSelectPerc<EOT> select;
//   eoEvalFunc<EOT> &eval;
// };

// #endif