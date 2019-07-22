// compare-test.cc
// Exercise to compare histograms using several measures.
//

#include <string>
#include <iostream>
#include <utility>
//#include <exception>
//#include <cmath>

#include "jb_histogram.h"

using namespace std;


void usage(string prog_name)
{
    cerr << "Usage: " << prog_name << " fcn hist_file1 hist_file2" << endl;
    cerr << " where fcn is {diff, kst, fp}" << endl;
}

int main(const int argc, const char* argv[])
{
    int result = 0;
    char delim = '\r';
    string program_name = argv[0];

    if (argc != 4) {
        usage(program_name);
        return 1;
    }

    string cmp_fcn = argv[1];
    string hist_filename0 = argv[2];
    string hist_filename1 = argv[3];

    // Create JbHistogram objects from the exercise histogram files.

    JbHistogram hist0 = JbHistogram(-0.1, 1.1, 0.001);
    if (!hist0.read_bin_probabilities(hist_filename0, delim)) {
        // File read error.  Exit.
        return 1;
    }

    if (!hist0.resample(0.0001)) {
        // Error resampling the histogram. Exit.
        return 1;
    }

    JbHistogram hist1 = JbHistogram(-0.1, 1.1, 0.001);
    if (!hist1.read_bin_probabilities(hist_filename1, delim)) {
        // File read error.  Exit.
        return 1;
    }

    if (!hist1.resample(0.0001)) {
        // Error resampling the histogram. Exit.
        return 1;
    }

    double fcn_result = 0.0;
    if (cmp_fcn == "diff") {    // Run diff fcn
        fcn_result = hist1.diff(hist0);
    }
    else if (cmp_fcn == "kst") {    // Run kst fcn
        fcn_result = hist0.kst(hist1);
    }
    else if (cmp_fcn == "fp") {    // Run best_fp_fn fcn
        double best_thresh = 0.0;
        double best_fp = 0.0;
        double best_fn = 0.0;
        std::tie(best_thresh, best_fp, best_fn) = hist0.best_fp_fn(hist1);
        fcn_result = best_fp;
    }
    else {
        usage(program_name);
        return 1;
    }

    cout << fcn_result << endl;
    return result;
}

