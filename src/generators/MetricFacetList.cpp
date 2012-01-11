#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include "MetricFacetList.h"

using namespace boost::numeric::ublas;  // used for boost matrices

/**
 * @method  MetricFacetList(int n_dimensions)
 * @param n_dimensions [int] number of points to be chosen from(dimensions)
 * 
 * Only valid constructor, creates and stores a boost matrix with every
 * possible facet in the metric polytope. Each row is a possible facet
 * in compact form.
 * 
 * Will not create the matrix if the dimension given:
 * @li @c is too small:  the metric polytope has at least 3 dimensions. 
 * @li @c is too big:  input values over 100 will overflow the containers used.
 * 
 * @see  get_facetlist()
 */

MetricFacetList::MetricFacetList(int n_dimensions) {
  if (n_dimensions < k_min_dimension || n_dimensions > k_max_dimension) {
    n_dimensions = 0;}

  /*
   * using the factorial function, it calculates the size of our matrix and
   * initializes it to 0
   */
  int n_facets = 4 * nChoose3(n_dimensions);
  facetlist_ = zero_matrix<int>(n_facets, n_dimensions);


  int index[3];           // stores position indices for nonzero elements
  int current_facet = 0;  // stores number of facets computed

  /*
   * loops over all possible position choices in order, 
   * innermost loop is over possible -1 positions
   * possible -1 positions include the NULL position and the already nonzero
   * max one -1 per row  positions on the row
   */

  for (index[0] = 0; index[0] < n_dimensions - 2; ++index[0]) {
    for (index[1] = index[0] + 1; index[1] < n_dimensions - 1; ++index[1]) {
      for (index[2] = index[1] + 1; index[2] < n_dimensions; ++index[2]) {
        for (
            int negative_choice = 0;  // start with no -1s //
            negative_choice < 4;    // move up through the possible -1   //
            ++negative_choice) {    // positions                         //

          // initializes the current row
          matrix_row<matrix<int> > row(facetlist_, current_facet);

          // sets the elements at the computed nonzero positions to 1
          row(index[0]) = 1;
          row(index[1]) = 1;
          row(index[2]) = 1;

          // sets the element at the appropiate position to -1
          if ( negative_choice > 0 ) {row(index[negative_choice - 1]) = -1;}

          // increments the row count
          current_facet++;
        }
      }
    }
  }
}
