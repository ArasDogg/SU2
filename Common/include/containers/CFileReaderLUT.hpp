/*!
 * \file CFileReaderLUT.hpp
 * \brief reading lookup table for tabulated fluid properties
 * \author D. Mayer, T. Economon
 * \version 7.5.0 "Blackbird"
 *
 * SU2 Project Website: https://su2code.github.io
 *
 * The SU2 Project is maintained by the SU2 Foundation
 * (http://su2foundation.org)
 *
 * Copyright 2012-2023, SU2 Contributors (cf. AUTHORS.md)
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

#include <fstream>
#include <string>
#include <vector>

#include "../../Common/include/parallelization/mpi_structure.hpp"
#include "../../../Common/include/linear_algebra/blas_structure.hpp"
#include "../../../Common/include/toolboxes/CSquareMatrixCM.hpp"

/*!
 * \brief File reader for look up tables.
 * \ingroup LookUpInterp
 */
class CFileReaderLUT {
 protected:
  int rank;

  unsigned short table_dim = 2;
  std::string version_lut;
  std::string version_reader;
  unsigned long n_levels = 1;
  su2vector<unsigned long> n_points, 
                           n_triangles, 
                           n_hull_points;

  unsigned long n_variables;
  su2vector<su2double> table_levels;

  /*! \brief Holds the variable names stored in the table file.
   * Order is in sync with tableFlamelet.
   */
  su2vector<std::string> names_var;

  /*! \brief Holds all data stored in the table.
   * First index addresses the variable while second index addresses the point.
   */
  su2vector<su2activematrix>table_data;

  su2vector<su2matrix<unsigned long>>triangles;

  su2vector<su2vector<unsigned long>>hull;
  /*! \brief Searches for the position of flag in file_stream and 
   *         sets the stream position of file_stream to that position.
   */
  void SkipToFlag(std::ifstream& file_stream, const std::string& current_line, const std::string& flag) const;

  /*! \brief Extracts the next non-empty characters from file_stream and stores them into line.
   */
  bool GetNextNonEmptyLine(std::ifstream& file_stream, std::string& line) const;

  /*! \brief Extracts characters from file_stream, removes trailing control characters,
   *         and stores them into line.
   */
  bool GetStrippedLine(std::ifstream& file_stream, std::string& line) const;

 public:
 
  inline const std::string& GetVersionLUT() const { return version_lut; }
  inline const std::string& GetVersionReader() const { return version_reader; }
  inline unsigned long GetNPoints(std::size_t i_level=0) const { return n_points[i_level]; }
  inline unsigned long GetNTriangles(std::size_t i_level=0) const { return n_triangles[i_level]; }
  inline unsigned long GetNHullPoints(std::size_t i_level=0) const { return n_hull_points[i_level]; }
  inline unsigned long GetNVariables() const { return n_variables; }
  inline unsigned long GetNLevels() const { return n_levels; }

  inline const su2vector<std::string>& GetNamesVar() const { return names_var; }

  inline const su2activematrix& GetTableData(std::size_t i_level=0) const { return table_data[i_level]; }

  inline const su2matrix<unsigned long>& GetTriangles(std::size_t i_level=0) const { return triangles[i_level]; }

  inline const su2vector<unsigned long>& GetHull(std::size_t i_level=0) const { return hull[i_level]; }

  inline su2double GetTableLevel(std::size_t i_level) const { return table_levels[i_level]; }
  
  inline unsigned short GetTableDim() const { return table_dim; }

  void ReadRawLUT(const std::string& file_name);
};