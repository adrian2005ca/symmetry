#ifndef SYMMETRY_GENERATORS_METRICFACETLIST_H
#define SYMMETRY_GENERATORS_METRICFACETLIST_H

#define MIN_DIMENSION 3 ///< metric polytope minimum
#define MAX_DIMENSION 12 ///< 12! will not overflow int

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include <stdexcept>

/**
 *  @brief Generator class for the metric polytope.
 *  @class MetricFacetList
 *
 *  Generates a matrix containing a facet list for the polytope of n dimensions
 *  and can provide a pointer to the matrix.
 */
class MetricFacetList
{
public:

  /**
   *  Used to initialize boost matrix to contain all possible facets.
   */
  explicit MetricFacetList(int nDimensions);

  /**
   *  Returns a POINTER to the the boost matrix that 
   *  is created at initialization.
   *
   *  @method  getPointer()
   *  @return  [ boost::numeric::ublas::matrix<int>*]  Pointer to facet matrix
   *
   *  WARNING: may cause dangling pointer, do not use past expiration!
   *
   *  @see  MetricFacetList(int nDimensions)
   */
  boost::numeric::ublas::matrix<int>* getPointer(){return &facetList_;}

private:
  // Private default initializer
  MetricFacetList(){} 

  // Simple lazy factorial computation function
  // OVERFLOW if value > 12
  int factorial(int value){
    int result = 1;
    for(int i = 1; i <= value; i++){result *= i;}
    return result;
  }

  // Holds the matrix of possible facets
  boost::numeric::ublas::matrix<int> facetList_; 

};

#endif //SYMMETRY_GENERATORS_METRICFACETLIST_H
