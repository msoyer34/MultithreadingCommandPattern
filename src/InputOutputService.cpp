#include <InputOutputService.hpp>

InputOutputService::InputOutputService(){
}

/**
 * Creates Random data with given input
*/
void InputOutputService::createRandomData(int input){
    std::srand(time(0));
    while(input > 0){
        
        unsigned int b = (std::rand() % 10 + 1 ) * 1000;
        data_vector.emplace_back(b);
        input--;
    }
}
vector<int> InputOutputService::returnData(){
    return data_vector;
}
/***    
 * Sorts data with std::sort and lambda function
*/
bool InputOutputService::sortData(){
    try
    {
        sort(data_vector.begin(), data_vector.end(), [] (int x , int y) -> bool 
        {
            return x < y;
        });
        return true;
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    
}
/***
 * Creates Output.
*/
void InputOutputService::createOutput(string filename){
    std::ofstream out(filename);
    if(out.is_open()){
        for(auto x : output){
            out << x.c_str() << endl;
        }
    }
    out.close();
}
void InputOutputService::insertToOutputs(string count){
    output.emplace_back(count);
}

