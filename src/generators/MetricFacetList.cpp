#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include <stdexcept>

#include "MetricFacetList.h"

using namespace boost::numeric::ublas;// used for boost matrices

/**
 * @method  MetricFacetList(int nDimensions)
 * @param nDimensions [int] number of points to be chosen from(dimensions)
 * @exception std::out_of_range Dimensions for the metric polytope are 
 *                              MIN_DIMESION (3) to MAX_DIMENSION(overflow).
 *                              Any input outside the specified range will cause
 *                              the object initialization to throw this exeption.
 *
 * Only valid constructor, creates and stores a boost matrix with every
 * possible facet in the metric polytope. Each row is a possible facet
 * in compact form.
 * 
 * @see  getPointer()
 */
MetricFacetList::MetricFacetList(int nDimensions){

  /*
   * throw out any input that is less than MIN_DIMENSION(always 3) and
   * MAX_DIMENSION which is by default is set to 12, see MetricFacetList.h.
   * the reason 12 is chosen is because 12! will not overflow stored as int.
   */
  
  if(nDimensions < MIN_DIMENSION || nDimensions > MAX_DIMENSION){
    throw std::out_of_range("Dimensions for the metric polytope are minimum" 
    " 3 to MAX_DIMENSION(overflow)");}

  /*
   * using the factorial function, it calculates the size of our matrix and
   * initializes it to 0
   */
  int nFacets = 4 * factorial(nDimensions) / (6 * factorial(nDimensions - 3) );
  facetList_ = zero_matrix<int>(nFacets, nDimensions);
  
  
  int index[3];// stores position indices for nonzero elements in the matrix
  int currentFacet = 0;// stores number of facets computed

  /*
   * loops over all possible position choices in order, 
   * innermost loop is over possible -1 positions
   * possible -1 positions include the NULL position and the already nonzero 
   * max one -1 per row  positions on the row
   */

  for(index[0] = 0; index[0] < nDimensions - 2; ++index[0]){
    for(index[1] = index[0] + 1; index[1] < nDimensions - 1; ++index[1]){
      for(index[2] = index[1] + 1; index[2] < nDimensions; ++index[2]){
        for(
            int negativeOneChoice = 0; 
            negativeOneChoice < 4; 
            ++negativeOneChoice){
					
          //initializes the current row and increments the row count
          matrix_row<matrix<int> > row(facetList_, currentFacet++);

          //sets the elements at the computed nonzero positions to 1
          row(index[0]) = 1;
					row(index[1]) = 1;
					row(index[2]) = 1;

          //sets the element at the appropiate position to -1
          if ( negativeOneChoice > 0 ){row(index[negativeOneChoice - 1]) = -1;}
        }
      }
    }
  }

}
