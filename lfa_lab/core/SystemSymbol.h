/*
  LFA Lab - Library to simplify local Fourier analysis.
  Copyright (C) 2018  Hannah Rittich

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. 
*/

#ifndef LFA_SYSTEM_SYMBOL_H
#define LFA_SYSTEM_SYMBOL_H

#include "Common.h"
#include "Symbol.h"

namespace lfa {

class SystemSymbol {
    public:
        explicit SystemSymbol(
                int rows = 0,
                int cols = 0,
                HarmonicClusters output_clusters = HarmonicClusters(),
                HarmonicClusters input_clusters = HarmonicClusters());

        static SystemSymbol Identity(int rows,
                                     int cols,
                                     HarmonicClusters output_clusters,
                                     HarmonicClusters input_clusters);

        Symbol& operator() (int i, int j) {
            return m_store[i][j];
        }
        const Symbol& operator() (int i, int j) const {
            return (*const_cast<SystemSymbol*>(this))(i, j);
        }

        void resize(int rows, int cols);

        SystemSymbol operator* (const SystemSymbol& other) const;
        SystemSymbol operator+ (const SystemSymbol& other) const;
        friend SystemSymbol operator* (double scalar, const SystemSymbol& other);
        SystemSymbol operator- (const SystemSymbol& other) const {
            return (*this) + (-1) * other;
        }

        SystemSymbol inverse() const;

        NdRange baseIndices() const { return m_output_clusters.baseIndices(); }

        int rows() const { return m_rows; }
        int cols() const { return m_cols; }

        double norm() const;
    private:
        int m_rows;
        int m_cols;
        HarmonicClusters m_output_clusters;
        HarmonicClusters m_input_clusters;

        vector<vector<Symbol> > m_store;
};


}

#endif
