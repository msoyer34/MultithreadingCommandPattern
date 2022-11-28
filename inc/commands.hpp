#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include<pthread.h>
#include "InputOutputService.hpp"

typedef void * (*THREADFUNCPTR)(void *);

class ICommand{
public:
    virtual void* execute(void *arg) = 0;
    pthread_t thread_id;
};

class IRunnable{
public:
    virtual void start() = 0;
    virtual void finish() = 0;
    std::string result_;
    std::vector<int> inputs_;
};


/***
 * Calculate Minimum value of data
*/
class CalcMin : public ICommand, public IRunnable
{
public: 
    void * execute(void * args) override
    {
        
        if(inputs_.size() > 0){
            result_ = std::to_string(inputs_.at(0));
        }
        return NULL;
    }
    void start(){
        pthread_create(&thread_id, NULL, (THREADFUNCPTR)&CalcMin::execute,this);
    }
    void finish(){
        pthread_join(thread_id, NULL);
    }
};
/***
 * Calculate maximum value of data
*/
class CalcMax : public ICommand, public IRunnable
{
public:

    void * execute(void * args) override
    {
        
        if(inputs_.size() > 0){
            result_ = std::to_string(inputs_.at(inputs_.size() - 1));
        }
        return NULL;
    }
    void start(){
        pthread_create(&thread_id, NULL, (THREADFUNCPTR)&CalcMax::execute,this);
    }
    void finish(){
        pthread_join(thread_id, NULL);
    }
};
/***
 * Calculate range of data
*/
class CalcRange : public ICommand, public IRunnable
{
public:
    void * execute(void * args) override
    {
        
        if(inputs_.size()  > 0){
       
            result_ =  std::to_string((inputs_.at(inputs_.size() - 1) - inputs_.at(0)));

        }

        return NULL;
    }
    void start(){
        pthread_create(&thread_id, NULL, (THREADFUNCPTR)&CalcRange::execute,this);
    }
    void finish(){
        pthread_join(thread_id, NULL);
    }    

};
/***
 * Return Mod of data
*/
class CalcMod : public ICommand, public IRunnable
{
public:
    void * execute(void * args)  override
    {
        
        int max_count = 0;
        int element_having_max_freq;
        for (int i = 0; i < inputs_.size(); i++) {
            int count = 0;
            for (int j = 0; j < inputs_.size(); j++) {
                if (inputs_.at(i) == inputs_.at(j))
                    count++;
            }
            if (count > max_count) {
                max_count = count;
                element_having_max_freq = inputs_.at(i);
            }
        }
        result_ = std::to_string(element_having_max_freq);

        return NULL;
    }
    void start(){
        pthread_create(&thread_id, NULL, (THREADFUNCPTR)&CalcMod::execute,this);
    }
    void finish(){
        pthread_join(thread_id, NULL);
    }
};
/***
 * Calculate Median of data
*/
class CalcMedian : public ICommand, public IRunnable
{
public:
    void * execute(void * args) override
    {
        
        if(inputs_.size() % 2 == 0 && inputs_.size() != 2){
            float res = inputs_.at(inputs_.size() / 2) + inputs_.at((inputs_.size() / 2) + 1); 
            float result = res / 2;
            result_ = std::to_string(result);
        }
        else{
            float result = static_cast<float> (inputs_.at((inputs_.size() / 2)));
            result_ = std::to_string(result);
        }

        return NULL;
    }
    void start(){
        pthread_create(&thread_id, NULL, (THREADFUNCPTR)&CalcMedian::execute,this);
    }
    void finish(){
        pthread_join(thread_id, NULL);
    }
    private:
    float returnMedianHelper(std::vector<int> sliced_vector){
    auto sliced_vector_size = sliced_vector.size();
    if(sliced_vector_size % 2 == 0 && sliced_vector_size != 2){
        float res = sliced_vector.at(sliced_vector_size / 2) + sliced_vector.at((sliced_vector_size / 2) + 1); 
        float result = res / 2;
        return result;
    }
    else{
        float result = static_cast<float> (sliced_vector.at((sliced_vector_size / 2)));
        return result;
    }
}
};
/***
 * Calculate sum of data
*/
class CalcSum : public ICommand, public IRunnable
{
public:
    void * execute(void * args) override
    {
        
        int total_count = 0;
        for(auto value : inputs_){
            total_count += value;
        }
        result_ = std::to_string(total_count);

        return NULL;
    }
    void start(){
        pthread_create(&thread_id, NULL, (THREADFUNCPTR)&CalcSum::execute,this);
    }
    void finish(){
        pthread_join(thread_id, NULL);
    }
};
/***
 * Calculate average mean of data
*/
class CalcAvMean : public ICommand, public IRunnable
{
public:
    void * execute(void * args) override
    {
        
        int total = 0;
        for(auto value : inputs_){
            total += value;
        }
        float avg = static_cast<float>(total) / static_cast<float>(inputs_.size());
        result_ = std::to_string(avg);

        return NULL;
    }
    void start(){
        pthread_create(&thread_id, NULL, (THREADFUNCPTR)&CalcAvMean::execute,this);
    }
    void finish(){
        pthread_join(thread_id, NULL);
    }
};
/***
 * Calculate harmonic mean of data
*/
class CalcHarmMean : public ICommand, public IRunnable
{
public:
    void * execute(void * args) override
    {
        
        float harmonic_count = 0;
        for(auto x : inputs_){
            harmonic_count += 1.0 / x;
        }
        float harm_mean = static_cast<float>(inputs_.size()) / harmonic_count;
        result_ = std::to_string(harm_mean);

        return NULL;
    }
    void start(){
        pthread_create(&thread_id, NULL, (THREADFUNCPTR)&CalcHarmMean::execute,this);
    }
    void finish(){
        pthread_join(thread_id, NULL);
    }
};
/***
 * Calculate standart deviation of data
*/
class CalcStdDeviation : public ICommand, public IRunnable
{
public:
    void * execute(void * args) override
    {
        
        float deviation = 0;
        int total = 0;
        for(auto value : inputs_){
            total += value;
        }
        for(auto x : inputs_){
            deviation += std::pow((x - (static_cast<float>(total) / static_cast<float>(inputs_.size()))) , 2);   	
        }
        float std_deviaton = static_cast<float>(deviation) / static_cast<float>(inputs_.size() - 1);
        auto last = std::sqrt(std_deviaton);
        result_ = std::to_string(last);

        return NULL;
    }
    void start(){
        pthread_create(&thread_id, NULL, (THREADFUNCPTR)&CalcStdDeviation::execute,this);
    }
    void finish(){
        pthread_join(thread_id, NULL);
    }
};
/***
 * Returns Interquartile Range of data, slices data into two seperate vectors and uses helper function to get two medians of upper and lower part.
*/
class CalcIQR : public ICommand, public IRunnable
{
public:
    void * execute(void * args) override
    {
        
        if(inputs_.size() % 2 == 0 && inputs_.size() != 2){
            auto start = inputs_.begin();
            auto end = inputs_.begin() + (inputs_.size() / 2 - 1);
            std::vector<int> sliced_1(start, end);
            start = inputs_.begin() + (inputs_.size() / 2);
            end = inputs_.end();
            std::vector<int> sliced_2(start, end);
            auto res1 = returnMedianHelper(sliced_1);
            auto res2 = returnMedianHelper(sliced_2);
            result_ = std::to_string(res2 - res1);
            
        }
        else{
            if(inputs_.size() == 1){
                result_ = std::to_string(0); 
                return NULL;;
            }
            auto start = inputs_.begin();
            auto end = inputs_.begin() + (inputs_.size() / 2 - 1);
            std::vector<int> sliced_1(start, end);
            start = inputs_.begin() + (inputs_.size() / 2 + 1);
            end = inputs_.end();
            std::vector<int> sliced_2(start, end);
            auto res1 = returnMedianHelper(sliced_1);
            auto res2 = returnMedianHelper(sliced_2);
            result_ = std::to_string(res2 - res1);
        }

        return NULL;
    }
    void start(){
        pthread_create(&thread_id, NULL, (THREADFUNCPTR)&CalcIQR::execute,this);
    }
    void finish(){
        pthread_join(thread_id, NULL);
    }
private:
    float returnMedianHelper(std::vector<int> sliced_vector){
        auto sliced_vector_size = sliced_vector.size();
        if(sliced_vector_size % 2 == 0 && sliced_vector_size != 2){
            float res = sliced_vector.at(sliced_vector_size / 2) + sliced_vector.at((sliced_vector_size / 2) + 1); 
            float result = res / 2;
            return result;
        }
        else{
            float result = static_cast<float> (sliced_vector.at((sliced_vector_size / 2)));
            return result;
        }
    }
};


/***
 * Initialize all commands and put them into operations.
*/
class CommandInitializer{
public:
    CommandInitializer(int input)
    {

        math_service = std::make_shared<InputOutputService>();
        math_service->createRandomData(input);
        math_service->sortData();
        CalcMin* calcMin = new CalcMin;
        CalcMax* calcMax = new CalcMax;
        CalcRange* calcRange = new CalcRange;
        CalcMod* calcMod = new CalcMod;
        CalcMedian* calcMedian = new CalcMedian;
        CalcSum* calcSum = new CalcSum;
        CalcAvMean* calcAvMean = new CalcAvMean;
        CalcHarmMean* calcHarmMean = new CalcHarmMean;
        CalcStdDeviation* calcStdDeviation = new CalcStdDeviation;
        CalcIQR* calcIQR = new CalcIQR;

        operations_.insert_or_assign(0, calcMin);
        operations_.insert_or_assign(1, calcMax);
        operations_.insert_or_assign(2, calcRange);
        operations_.insert_or_assign(3, calcMod);
        operations_.insert_or_assign(4, calcMedian);
        operations_.insert_or_assign(5, calcSum);
        operations_.insert_or_assign(6, calcAvMean);
        operations_.insert_or_assign(7, calcHarmMean);
        operations_.insert_or_assign(8, calcStdDeviation);
        operations_.insert_or_assign(9, calcIQR);
        auto data = math_service->returnData();
        for(auto operation : operations_){
            operation.second->inputs_ = data;
        }
    }
    std::shared_ptr<InputOutputService> math_service;
    std::map<int, IRunnable*> getOperations(){
        return operations_;
    }
private:

    std::map<int, IRunnable*> operations_;


};

