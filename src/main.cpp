#include <iostream>
#include <commands.hpp>

int main(int argc, char* argv[]){
    if(argv[1] == nullptr){
        return 0;
    }
    int input = std::stoi(argv[1]);

    std::shared_ptr<CommandInitializer> initializer = std::make_shared<CommandInitializer>(input);
    auto operations = initializer->getOperations();
    for(auto operation: operations){
        operation.second->start();
    }
    for(auto operation: operations){
        operation.second->finish();
    }
    for(auto operation: operations){
        initializer->math_service->insertToOutputs(operation.second->result_);
    }
    initializer->math_service->createOutput("output");
    return 0;
}
