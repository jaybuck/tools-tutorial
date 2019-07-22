// Histogram class for programming exercise.
// Used to:
// - Read bin probabilities from file.
// - Resample the histogram bins to finer grain for comparison analyses.
// - Compare two histograms using several metrics.

#ifndef JBHISTOGRAM_H
#define JBHISTOGRAM_H

#include <string>
#include <vector>
#include <utility>
#include <tuple>

class JbHistogram
{
public:
    // Constructors
    JbHistogram();
    JbHistogram(double xmin, double xmax, double binwidth);

    // Static functions
    static void string_split(const std::string& str, 
                             std::vector<std::string> &tokens, 
                             char delim);


    // Member functions
    bool read_bin_probabilities(std::string in_filename, char delim);
    bool resample(double new_bin_width);
    double compute_area() const;
    double diff(const JbHistogram& rhs);
    double kst(const JbHistogram& rhs);
    std::tuple<double, double, double> best_fp_fn(const JbHistogram& rhs);

    // Member variables
    std::vector< std::pair<double, double> > input_probabilities;
    std::vector< std::tuple<double, double, double> > bin_coords;
    double x_min = 0.0;
    double x_max = 1.0;
    double bin_width = 0.01;
    std::vector<double> bin_heights;
};

#endif
