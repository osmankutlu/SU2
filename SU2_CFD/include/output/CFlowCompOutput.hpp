/*!
 * \file CFlowCompOutput.hpp
 * \brief  Headers of the compressible flow output.
 * \author R. Sanchez, T. Albring.
 * \version 6.2.0 "Falcon"
 *
 * The current SU2 release has been coordinated by the
 * SU2 International Developers Society <www.su2devsociety.org>
 * with selected contributions from the open-source community.
 *
 * The main research teams contributing to the current release are:
 *  - Prof. Juan J. Alonso's group at Stanford University.
 *  - Prof. Piero Colonna's group at Delft University of Technology.
 *  - Prof. Nicolas R. Gauger's group at Kaiserslautern University of Technology.
 *  - Prof. Alberto Guardone's group at Polytechnic University of Milan.
 *  - Prof. Rafael Palacios' group at Imperial College London.
 *  - Prof. Vincent Terrapon's group at the University of Liege.
 *  - Prof. Edwin van der Weide's group at the University of Twente.
 *  - Lab. of New Concepts in Aeronautics at Tech. Institute of Aeronautics.
 *
 * Copyright 2012-2019, Francisco D. Palacios, Thomas D. Economon,
 *                      Tim Albring, and the SU2 contributors.
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

#pragma once

#include "CFlowOutput.hpp"

class CVariable;

/*! \class CFlowCompOutput
 *  \brief Output class for compressible flow problems.
 *  \author R. Sanchez, T. Albring.
 *  \date May 30, 2018.
 */
class CFlowCompOutput final: public CFlowOutput {
private:
  
  unsigned short turb_model; /*!< \brief Kind of turbulence model */
  unsigned short scalar_model; /*!< \brief The kind of scalar transport model*/
  unsigned long lastInnerIter;
   
public:

  /*!
   * \brief Constructor of the class
   * \param[in] config - Definition of the particular problem.
   */
  CFlowCompOutput(CConfig *config, unsigned short nDim);

  /*!
   * \brief Destructor of the class.
   */
  ~CFlowCompOutput(void) override;

  
  /*!
   * \brief Load the history output field values
   * \param[in] config - Definition of the particular problem.
   */
  void LoadHistoryData(CConfig *config, CGeometry *geometry, CSolver **solver) override;
  
  /*!
   * \brief Set the values of the volume output fields for a surface point.
   * \param[in] config - Definition of the particular problem.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver - The container holding all solution data.
   * \param[in] iPoint - Index of the point.
   * \param[in] iMarker - Index of the surface marker.
   * \param[in] iVertex - Index of the vertex on the marker.
   */
  void LoadSurfaceData(CConfig *config, CGeometry *geometry, CSolver **solver, 
                       unsigned long iPoint, unsigned short iMarker, unsigned long iVertex) override;  
  
  /*!
   * \brief Set the available volume output fields
   * \param[in] config - Definition of the particular problem.
   */
  void SetVolumeOutputFields(CConfig *config) override;
  
  /*!
   * \brief Set the values of the volume output fields for a point.
   * \param[in] config - Definition of the particular problem.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver - The container holding all solution data.
   * \param[in] iPoint - Index of the point.
   */
  void LoadVolumeData(CConfig *config, CGeometry *geometry, CSolver **solver, unsigned long iPoint) override; 
  
  /*!
   * \brief Set the available history output fields
   * \param[in] config - Definition of the particular problem.
   */
  void SetHistoryOutputFields(CConfig *config) override;
  
  /*!
   * \brief Check whether the base values for relative residuals should be initialized
   * \param[in] config - Definition of the particular problem.
   * \return <TRUE> if the residuals should be initialized.
   */
  bool SetInit_Residuals(CConfig *config) override;
  
  /*!
   * \brief Check whether the averaged values should be updated
   * \param[in] config - Definition of the particular problem.
   * \return <TRUE> averages should be updated.
   */
  bool SetUpdate_Averages(CConfig *config) override;

  /*!
   * \brief Write any additional output defined for the current solver.
   * \param[in] config - Definition of the particular problem per zone.
   */
  void SetAdditionalScreenOutput(CConfig *config) override;

  /*!
   * \brief Write additional output for fixed CL mode.
   * \param[in] config - Definition of the particular problem per zone.
   */
  void SetFixedCLScreenOutput(CConfig *config);
  
  /*!
   * \brief Determines if the history file output.
   * \param[in] config - Definition of the particular problem.
   */
  bool WriteHistoryFile_Output(CConfig *config) override;
};
