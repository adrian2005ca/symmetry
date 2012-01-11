#ifndef SYMMETRY_GENERATORS_METRICFACETLIST_H_
#define SYMMETRY_GENERATORS_METRICFACETLIST_H_

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

/**
 * @class MetricFacetList
 * @brief Generator class for the metric polytope.
 *
 * Generates a matrix containing a facet list for the polytope of n dimensions
 * and can provide a pointer to the matrix.
 *
 * Sample usage:
 * @code
 * using namespace std;
 * using namespace boost::numeric::ublas;
 * 
 * MetricFacetList m(4);
 * matrix<int> computed_matrix = *m.get_facetlist();
 * cout << computed_matrix;
 * @endcode
 */ 
class MetricFacetList {
  public:
    /**
     * Initializes the member boost matrix to contain all possible facets of the
     * metric polytope.
     */
    explicit MetricFacetList(int n_dimensions);

    /**
     * @method  get_facetlist()
     *  
     * Returns a pointer to the the boost matrix that 
     * is created at initialization.
     *
     * WARNING: may cause dangling pointer, do not use past object expiration!
     * 
     * @return  [ boost::numeric::ublas::matrix<int>*]  Pointer to facet matrix
     *
     * @see  MetricFacetList(int n_dimensions)
     */
    boost::numeric::ublas::matrix<int>* get_facetlist() {return &facetlist_;}

  private:
    // The metric polytope has at least dimension 3.
    static const int k_min_dimension = 3;

    // To avoid integer overflow, the maximum dimension for creating the
    // metric polytope is set here.
    static const int k_max_dimension = 100;

    // Private default initializer is empty.
    MetricFacetList() {}

    // Computes the combinatoric formula for choosing 3 objects out
    // of n objects.
    int nChoose3(int n) {return n * (n - 1) * (n - 2) / 6;}

    // Holds the matrix of possible facets.
    boost::numeric::ublas::matrix<int> facetlist_;
};

#endif  // SYMMETRY_GENERATORS_METRICFACETLIST_H_
