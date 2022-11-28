#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <math.h>
#include <memory>
#include <execution>
#include <fstream>
#include <stdio.h>
#include <map>

using namespace std;
class InputOutputService{
    public:
        InputOutputService();
        ~ InputOutputService() = default;
        void createRandomData(int input);
        bool sortData();
        vector<int> returnData();
        void createOutput(string filename);
        void insertToOutputs(string count);
        private:
        vector<int> data_vector;
        vector<string> output;
        string outputs[10];
        float returnMedianHelper(vector<int> sliced_vector);
};