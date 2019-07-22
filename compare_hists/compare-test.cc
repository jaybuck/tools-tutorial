// compare-test.cc
// Test functions in jb_histogram.cc
// For this exercise, since we don't want to use external libraries
// we simply use a single executable to run a few tests.
//

#include <string>
#include <iostream>
#include <utility>
#include <exception>
#include <cmath>

#include "jb_histogram.h"

using namespace std;

// Quick test function to check whether two doubles are very close in value.

int check_equal(string& desc, double val0, double val1)
{
    int err_count = 0;
    double epsilon = 0.00001;

    if (std::abs(val1 - val0) > epsilon) {
        err_count += 1;
        cout << "Test Error: Not Equal: " << desc << endl;
    } else {
        cout << "Test Success: Equal: " << desc << endl;
    }

    return err_count;
}


int main(const int argc, const char* argv[])
{
    int result = 0;
    unsigned int test_count = 0;
    unsigned int error_count = 0;
    char delim = '\n';

    // Test JbHistogram constructor
    // Specifically, make sure the area of the re-sampled histogram
    // sums to the same value as that of the input histogram.

    string test_desc("JbHistogram area and input area");
    cout << "Test " << test_count << '\t' << test_desc << endl;
    test_count++;
    double input_area = 0.0;
    JbHistogram hist0 = JbHistogram(-0.2, 1.2, 0.001);
    //if (!hist0.read_bin_probabilities("test-hist0.txt", delim)) {
    if (!hist0.read_bin_probabilities("h1.txt", delim)) {
        // File read error.  Exit.
        return 1;
    }

    //cout << "hist1: # input bins: " << hist0.input_probabilities.size() << endl;
    for (auto bin_pair : hist0.input_probabilities) {
        input_area += bin_pair.second;
        //cout << bin_pair.first << '\t' << bin_pair.second << endl;
    }

    if (!hist0.resample(0.001)) {
        // Error resampling the histogram. Exit.
        return 1;
    }
    double hist_area = hist0.compute_area();
    error_count += check_equal(test_desc, hist_area, input_area);

    /*double x0 = hist0.x_min;

    for (int i = 0; i < hist0.bin_heights.size(); ++i) {
    cout << "histbins\t" << hist0.bin_xmins[i] << '\t'
    << x0 << '\t'
    << hist0.bin_heights[i] << endl;
        x0 += hist0.bin_width;
        }*/


    // Test JbHistogram constructor on second histogram file.

    test_desc = "JbHistogram area and input area";
    cout << "Test " << test_count << '\t' << test_desc << endl;
    test_count++;

    JbHistogram hist1 = JbHistogram(-0.2, 1.2, 0.001);
    //if (!hist1.read_bin_probabilities("test-hist1.txt")) {
    if (!hist1.read_bin_probabilities("h2.txt", delim)) {
        // File read error.  Exit.
        return 1;
    }

    input_area = 0.0;
    for (auto bin_pair : hist1.input_probabilities) {
        input_area += bin_pair.second;
        //cout << bin_pair.first << '\t' << bin_pair.second << endl;
    }

    if (!hist1.resample(0.001)) {
        // Error resampling the histogram. Exit.
        return 1;
    }
    hist_area = hist0.compute_area();
    error_count += check_equal(test_desc, hist_area, input_area);

    // Test the function that computes the absolute value of the
    // difference between the histograms.

    test_desc = "diff";
    cout << "Test " << test_count << '\t' << test_desc << endl;
    test_count++;

    double actual_diff = 1.12583;
    double area_diff = 0.0;
    try
    {
        area_diff = hist1.diff(hist0);
    }
    catch (std::invalid_argument& e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    error_count += check_equal(test_desc, area_diff, actual_diff);
    cout << "diff\t" << area_diff << endl;


    // Test the function that computes Kolmogorov_Smirnov value.

    test_desc = "kst";
    cout << "Test " << test_count << '\t' << test_desc << endl;
    test_count++;

    double actual_kst = 0.54;
    double test_kst = 0.0;
    try
    {
        test_kst = hist1.kst(hist0);
    }
    catch (std::invalid_argument& e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    error_count += check_equal(test_desc, test_kst, actual_kst);
    cout << "kst\t" << test_kst << endl;

    // Test the function that computes best false positive and
    // false negative rates.

    test_desc = "best_fp_fn";
    cout << "Test " << test_count << '\t' << test_desc << endl;
    test_count++;

    double actual_thresh = 0.687;
    double actual_fp = 0.2304;
    double actual_fn = 0.2296;
    double test_thresh = 0.0;
    double test_fp = 0.0;
    double test_fn = 0.0;
    try
    {
        std::tie(test_thresh, test_fp, test_fn) = hist0.best_fp_fn(hist1);
    }
    catch (std::invalid_argument& e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    string msg = test_desc + " thresholds";
    int err0 = check_equal(msg, test_thresh, actual_thresh);
    msg = test_desc + " fp rates";
    int err1 = check_equal(msg, test_fp, actual_fp);
    msg = test_desc + " fp rates";
    int err2 = check_equal(msg, test_fn, actual_fn);

    error_count += (err0 + err1 + err2 > 0 ? 1 : 0);
    cout << "best_fn_fp " 
         << test_thresh << " " 
         << test_fp << " " 
         << test_fn << endl;

    cout << "Total number of errors: " << error_count << endl;
    result = (error_count > 0 ? 1 : 0);
    return result;
}
