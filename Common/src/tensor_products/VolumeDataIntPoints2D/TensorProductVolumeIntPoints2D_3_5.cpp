/*!
 * \file TensorProductVolumeIntPoints2D_3_5.cpp
 * \brief Function, which carries out the tensor product for (nDOFs1D,nInt1D) = (3,5)
 * \author Automatically generated file, do not change manually
 * \version 7.0.8 "Blackbird"
 *
 * SU2 Project Website: https://su2code.github.io
 *
 * The SU2 Project is maintained by the SU2 Foundation
 * (http://su2foundation.org)
 *
 * Copyright 2012-2020, SU2 Contributors (cf. AUTHORS.md)
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#include "../../../include/tensor_products/TensorProductVolumeIntPoints2D.hpp"
#include "../../../include/fem/CFEMStandardElementBase.hpp"

void TensorProductVolumeIntPoints2D_3_5(const int           N,
                                        const int           ldb,
                                        const int           ldc,
                                        const passivedouble *Ai,
                                        const passivedouble *Aj,
                                        const su2double     *B,
                                        su2double           *C) {

  /*--- Compute the padded value of the number of integration points. ---*/
  const int MP = CFEMStandardElementBase::PaddedValue(5);

  /*--- Cast the one dimensional input arrays for the A-tensor to 2D arrays.
        Note that C++ stores multi-dimensional arrays in row major order,
        hence the indices are reversed compared to the column major order
        storage of e.g. Fortran. ---*/
  const passivedouble (*ai)[MP] = (const passivedouble (*)[MP]) Ai;
  const passivedouble (*aj)[MP] = (const passivedouble (*)[MP]) Aj;

  /*--- Define the variables to store the intermediate results. ---*/
  su2double tmpJ[3][MP];

  /*--- Outer loop over N. ---*/
  for(int l=0; l<N; ++l) {

    /*--- Cast the index l of B and C to multi-dimensional arrays. ---*/
    const su2double (*b)[3] = (const su2double (*)[3]) &B[l*ldb];
    su2double       (*c)[5] = (su2double (*)[5]) &C[l*ldc];

    /*--- Tensor product in j-direction to obtain the solution
          in the integration points in j-direction. ---*/
    for(int i=0; i<3; ++i) {
      SU2_OMP_SIMD
      for(int j=0; j<MP; ++j) tmpJ[i][j] = 0.0;
      for(int jj=0; jj<3; ++jj) {
        SU2_OMP_SIMD_IF_NOT_AD
        for(int j=0; j<MP; ++j)
          tmpJ[i][j] += aj[jj][j] * b[jj][i];
      }
    }

    /*--- Check if the padded number MP is larger than the
          number the integration points. In this case the
          result cannot be stored directly in c. ---*/
    if(MP > 5) {

    /*--- Tensor product in i-direction to obtain the solution
          in the integration points in i-direction. This is
          the final result of the tensor product, which is
          in tmpI for performance reasons. ---*/
      su2double tmpI[MP];
      for(int j=0; j<5; ++j) {
        SU2_OMP_SIMD
        for(int i=0; i<MP; ++i) tmpI[i] = 0.0;
        for(int ii=0; ii<3; ++ii) {
          SU2_OMP_SIMD_IF_NOT_AD
          for(int i=0; i<MP; ++i)
            tmpI[i] += ai[ii][i] * tmpJ[ii][j];
        }

        /*--- Copy the values to the appropriate location in c. ---*/
        for(int i=0; i<5; ++i)
          c[j][i] = tmpI[i];
      }
    }
    else {

      /*--- The padded number equals the number of integration
            points. The result of the tensor product in
            i-direction to obtain the solution in the integration
            points in i-direction can be stored in c directly. ---*/
      for(int j=0; j<5; ++j) {
        SU2_OMP_SIMD
        for(int i=0; i<MP; ++i) c[j][i] = 0.0;
        for(int ii=0; ii<3; ++ii) {
          SU2_OMP_SIMD_IF_NOT_AD
          for(int i=0; i<MP; ++i)
            c[j][i] += ai[ii][i] * tmpJ[ii][j];
        }
      }
    }

  } /*--- End of the loop over N. ---*/
}
