#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <random>
#include <format>

using namespace std;

void generate_file(const string& filename,
const vector<double>& probs,
const vector<string>& actions,
long long total_lines){
    random_device rd;
    mt19937 gen(rd());
    discrete_distribution<> dist(probs.begin(), probs.end());

    ofstream outfile(filename);
    if (!outfile){
        cerr << "Error opening file " << filename << "\n";
        return;
    }
    for (long long i = 0; i < total_lines; ++i)
    {
        int act_index = dist(gen);
        outfile << actions[act_index]<<"\n";
    }
    cout << format("Finished {} ({} lines.)", filename, total_lines)<<"\n";
}

int main(){
    const long long NUM_LINES = 1000000;
    const int MAX_THREADS = 3;
    const vector<string> all_actions = {
        "read 0",
        "write 0 1",
        "read 1",
        "write 1 1",
        "string"
    };
    try{
        vector<double> probs_A = {25.0, 5.0, 5.0, 25.0, 40.0};
        for (int i = 1; i <= MAX_THREADS; ++i){
            generate_file(format("test_A_{}.txt", i), probs_A, all_actions, NUM_LINES);
        }
        vector<double> probs_B = {25.0, 25.0, 25.0, 25.0, 25.0};
        for (int i =  1; i <= MAX_THREADS; ++i){
            generate_file(format("test_B_{}.txt", i), probs_B, all_actions, NUM_LINES);
        }
        vector<double> probs_C = {5.0, 10.0, 5.0, 80.0, 0.0};
        for (int i = 1; i <= MAX_THREADS; ++i){
            generate_file(format("test_C_{}.txt", i), probs_C, all_actions, NUM_LINES);
        }
    } catch (const exception& e){
        cerr<<"\nFatal error! "<<e.what()<<"\n";
        return 1;
    }
    cout<<"All files generated."<<"\n";
    return 0;
}