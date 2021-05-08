#include <future>
#include <thread>

int functionForTask (){
    return 7;
}

int main (int argc, char** argv){

    // future from a packaged_task
    std::packaged_task<int()> taskFunction(functionForTask); // wrap the function
    std::packaged_task<int()> taskLambda([] { return 5;});
    std::future<int> f1 = taskLambda.get_future();  // get a future
    std::thread t(std::move(taskLambda)); // launch on a thread
}

