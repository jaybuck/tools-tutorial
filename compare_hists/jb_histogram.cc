// Histogram class for programming exercise:  Implementation
// Used to:
// - Read bin probabilities from file.
// - Resample the histogram bins to finer grain for comparison analyses.
// - Compare two histograms using several metrics.


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#include <exception>
#include <cmath>
#include <numeric>
#include <limits>

#include "jb_histogram.h"

using namespace std;


/*******************************************************************************
 * Constructors
 */

JbHistogram::JbHistogram() : x_min(0.0), x_max(0.0), bin_width(0.01) {
}
 

JbHistogram::JbHistogram(double xmin, double xmax, double binwidth) : 
    x_min(xmin), x_max(xmax), bin_width(binwidth) {
}


/*******************************************************************************
 * Static functions
 */

void JbHistogram::string_split(const std::string& str, 
                               std::vector<std::string> &tokens, 
                               char delim)
{
    string::size_type pos = 0;
    string::size_type last_pos = 0;

    if (str.length() > 0) {
        while (true) {
            pos = str.find(delim, last_pos);
            if (pos == string::npos)
            {
                pos = str.length();
                tokens.push_back(str.substr(last_pos, pos - last_pos));
                break;
            }
            else {
                tokens.push_back(str.substr(last_pos, pos - last_pos));
            }
            last_pos = pos + 1;
        }
    }
}


/*******************************************************************************
 * Member functions
 */

bool JbHistogram::read_bin_probabilities(std::string in_filename, char delim) {
    string line;

    ifstream in_file(in_filename);
    if (!in_file.is_open()) {
        // Write error msg to stderr.
        // Normally I'd write this to whatever logging facility we are using.
        cerr << "Error opening " << in_filename << endl;
        return false;
    }

    input_probabilities.clear();

    while (getline(in_file, line, delim)) {
        // Parse the two values out of the input string.
        // I'd normally use boost::tokenize for this,
        // but in this case I don't want to use external libraries.
        if (line.length() > 2)    // shortest valid line is 3 chars.  eg: 0,0
        {
            std::vector<std::string> tokens;
            JbHistogram::string_split(line, tokens, ',');
            if (tokens.size() < 2)
                continue;

            double xp[2] = {0.0, 0.0};
            bool parse_good = true;

            for (int i = 0; i < 2; ++i) {
                stringstream ss(tokens[i]);
                ss >> xp[i];
                if (ss.fail()) {
                    parse_good = false;
                    break;
                }
            }
            if (parse_good) {
                input_probabilities.push_back(pair<double, double>(xp[0], xp[1]));
            }
        }
    }

    return true;
}


// The resample() function takes the input probabilities and
// resamples them into bins of equal (usually much smaller) width.
// The goal is to produce a histogram representation that is easier to compare
// with other histograms.
// 
// The input probabilities are a vector of pairs holding
// - the center of a bin of x values 
// - the probability of values in that bin.
//
// To calculate the minimum and maximum x values for the bin we set the boundary
// between bins at halfway between adjacent input x values.
// That is, 1/2 of the total bin width is boundary x - input x.
// For the first bin, since the center of the bin is still the
// input x value, we set the minimum x value for the bin to be
// input x - 1/2 bin width.
// Similary for the last bin.
//
// Once we have the x interval for a bin, we compute the height of the bin
// bin_height = bin_area / x_delta

bool JbHistogram::resample(double new_bin_width) {

    if (input_probabilities.size() < 2)
        return false;

    bin_coords.clear();
    bin_heights.clear();
    bin_width = new_bin_width;

    double last_bin_max = x_min;
    double input_bin_max = 0.0;
    double half_input_bin_width = 0.0;
    double epsilon = bin_width / 100.0;

    for (int i = 0; i < input_probabilities.size(); ++i) {
        auto input_bin_pair = input_probabilities[i];
        double input_bin_x = input_bin_pair.first;
        double input_bin_area = input_bin_pair.second;

        // For most bins:
        if (i < input_probabilities.size() - 1) {
            auto input_bin_pair_next = input_probabilities[i+1];
            half_input_bin_width = (input_bin_pair_next.first - input_bin_x) / 2.0;
        }
        input_bin_max = input_bin_x + half_input_bin_width;

        if (i == 0) {
            last_bin_max = input_bin_x - half_input_bin_width;

            // Pad the left side of histogram with zero-height bins to make
            // histogram comparison easier.
            double bin_xmin = x_min;
            double bin_xmax = x_min + bin_width;
            while (bin_xmax <= last_bin_max + epsilon) {
                bin_heights.push_back(0.0);
                bin_xmin = bin_xmax;
                bin_xmax += bin_width;
            }
        }

        double input_bin_w =  (input_bin_max - last_bin_max);
        double input_bin_height = (input_bin_w > 0 ? input_bin_area / input_bin_w : 0.0);

        // Diagnostics
        bin_coords.push_back(make_tuple(last_bin_max, input_bin_max, input_bin_height));

        // Resample this input bin into narrower bins.
        double epsilon = bin_width / 100.0;
        double bin_xmin = last_bin_max;
        double bin_xmax = last_bin_max + bin_width;
        while (bin_xmax <= input_bin_max + epsilon) {
            bin_heights.push_back(input_bin_height);
            bin_xmin = bin_xmax;
            bin_xmax += bin_width;
        }

        last_bin_max = input_bin_max;

        // After the last bin,
        // Pad the right side of histogram with zero-height bins to make
        // histogram comparison easier.
        if (i == input_probabilities.size() - 1) {
            double bin_xmin = last_bin_max;
            double bin_xmax = last_bin_max + bin_width;
            while (bin_xmax <= x_max + epsilon) {
                bin_heights.push_back(0.0);
                bin_xmin = bin_xmax;
                bin_xmax += bin_width;
            }
        }
    }

    return true;
}


inline double JbHistogram::compute_area() const {
    double area = bin_width * std::accumulate(bin_heights.begin(), bin_heights.end(), 0.0);
    return area;
}

// Compute absolute value of differences between two histograms.

double JbHistogram::diff(const JbHistogram& rhs) {
    double area_diff = 0.0;

    if (x_min != rhs.x_min ||
        x_max != rhs.x_max ||
        bin_width != rhs.bin_width ||
        bin_heights.size() != rhs.bin_heights.size()) {
        throw invalid_argument("diff: JbHistogram parameters are not equal");
    }

    for (int i = 0; i < bin_heights.size(); ++i) {
        double d = bin_width * std::abs(bin_heights[i] - rhs.bin_heights[i]);
        area_diff += d;
    }

    return area_diff;
}


// Compute Kolmogorov_Smirnov test

double JbHistogram::kst(const JbHistogram& rhs) {
    double kst = 0.0;

    if (x_min != rhs.x_min ||
        x_max != rhs.x_max ||
        bin_width != rhs.bin_width ||
        bin_heights.size() != rhs.bin_heights.size()) {
        throw invalid_argument("diff: JbHistogram parameters are not equal");
    }

    double cumulative_area = 0.0;
    double cumulative_area1 = 0.0;

    for (int i = 0; i < bin_heights.size(); ++i) {
        cumulative_area += bin_width * bin_heights[i];
        cumulative_area1 += bin_width * rhs.bin_heights[i];
        double delta = std::abs(cumulative_area1 - cumulative_area);
        kst = std::max(kst, delta);
    }

    return kst;
}

// Compute best false positive and false negative rates.
// Idea: Assume the two histograms represent histograms of scores from 
// a classifier trained to detect items belonging to a category.
// The first histogram is the scores for the known negatives for that category;
// the second histogram is the scores for the known positives.
// To use these scores to output whether the item should be considered a
// positive or a negative we typically threshold the score.
// Usually the classifier was trained to produce an output near 1 for positives,
// and output near 0 for negatives.
// Of course most classifers will not do a perfect job at this task.
// For any fixed threshold we can compute the fraction of false positives and
// the fraction of false negatives given the histograms of the scores for
// the negatives and the positives.
// This function determines the threshold that yields the best combination of
// false positive and false negative rates given these score histograms.
// 
// It outputs a tuple containing the best
// threshold, false positive rate, false negative rate.
// In this function, that's the point where the 
// false positive rate is closest to the false negative rate.
//
// This JbHistogram object is the histogram for the negatives
// and the rhs is the histogram for the positives.
//

tuple<double, double, double> JbHistogram::best_fp_fn(const JbHistogram& rhs) {
    if (x_min != rhs.x_min ||
        x_max != rhs.x_max ||
        bin_width != rhs.bin_width ||
        bin_heights.size() != rhs.bin_heights.size()) {
        throw invalid_argument("diff: JbHistogram parameters are not equal");
    }

    double cumulative_area0 = 0.0;
    double cumulative_area1 = 0.0;
    double total_area0 = compute_area();
    double total_area1 = rhs.compute_area();
    double best_fp_rate = total_area0;    // Worst case value
    double best_fn_rate = total_area1;    // Worst case value
    double best_thresh = 0.0;
    double best_delta = std::numeric_limits<double>::max();

    double last_bin_max = x_min;

    for (int i = 0; i < bin_heights.size(); ++i) {
        double fp_rate = total_area0 - cumulative_area0;
        cumulative_area0 += bin_width * bin_heights[i];

        double fn_rate = cumulative_area1;
        cumulative_area1 += bin_width * rhs.bin_heights[i];

        double delta = std::abs(fp_rate - fn_rate);
        if (delta < best_delta) {
            best_delta = delta;
            best_thresh = last_bin_max;
            best_fp_rate = fp_rate;
            best_fn_rate = fn_rate;
        }
        last_bin_max += bin_width;
    }

    return make_tuple(best_thresh, best_fp_rate, best_fn_rate);
}

