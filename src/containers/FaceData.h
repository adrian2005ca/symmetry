#ifndef SYMMETRY_CONTAINERS_FACEDATA_H_
#define SYMMETRY_CONTAINERS_FACEDATA_H_

/*
 * Matrix dependencies declared here so we can take
 * advantage of automatic destruction of our matrix members
 * at the end of instance scope
 */
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

/**
 * @brief Container class for all information regarding a face.
 *
 * @class FaceInfo
 *
 * Provides storage and some useful methods for faces.
 */
class   FaceData {
  public:
    /**
     * Default constructor initializes class variables.
     *
     * @method  FaceInfo()
     * @see  setBin(), getBin()
     */
    FaceData() {setBin(1);}

    /**
     * Mutator method for setting the grouping of the face.
     *
     * @method  setBin(int bin)
     * @param  bin [int] an integer representing the grouping of a face
     *
     * Faces can be split up into bins based on invariances. This allows
     * for less complexity when doing pairwise comparisons.
     * @see  getBin()
     */
    void setBin(int bin) {bin_ = bin;}

    /**
     * Accessor method for outputting the bin of the face to an integer.
     *
     * @method getBin()
     * @return  [int] the bin of the face object    
     * @see setBin(int bin)
     */
    int getBin() {return bin_;}

    // Debugging method for testing purposes.
    void test() {boost::numeric::ublas::matrix<int> m;}

  private:
    // holds facets generated by intersection.
    boost::numeric::ublas::matrix<int> originalFacets;

    // holds full list of facets.
    boost::numeric::ublas::matrix<int> allFacets;

    int bin_;  // holds current bin of the face.
};

#endif  // SYMMETRY_CONTAINERS_FACEDATA_H_
