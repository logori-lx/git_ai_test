#include<iostream>
#include<mutex>
#include<queue>
#include<condition_variable>
#include<functional>
#include<thread>
class ThreadPool{
    public:
    ThreadPool(size_t num_threads) : stop_(false){
        for(int i = 0; i < num_threads; i++){
            workers_.emplace_back([this](){
                while(true){
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex_);
                        cv_.wait(lock, [this](){
                            return stop_ || !task_queue_.empty();
                        });
                        if(stop_ && task_queue_.empty()){
                            return;
                        }
                        task = std::move(task_queue_.front());
                        task_queue_.pop();
                    }
                    task();
                }
            });
        }
    }
    template<class F, typename... Args>
    void enqueue(F&& f, Args&&...args){
        auto task = [f, args...](){
            f(args...);
        };
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            if(stop_){
                throw std::runtime_error("Thread pool has been stopped!");
            }
            task_queue_.emplace(task);
        }
        cv_.notify_one();
    }
    ~ThreadPool(){
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            stop_ = true;
        }
        cv_.notify_all();
        for(auto &worker : workers_){
            worker.join();
        }
    }
    private:
    bool stop_;
    std::queue<std::function<void()>> task_queue_;
    std::vector<std::thread> workers_;
    std::mutex queue_mutex_;
    std::condition_variable cv_;
};
void simple_task(int i){
    std::cout << "hello " << i << std::endl;
}
void simple_task2(std::string i){
    std::cout << "hello " << i << std::endl;
}
int main(void){
    ThreadPool threadpool(10);
    threadpool.enqueue(simple_task, 1);
    threadpool.enqueue(simple_task2,"hello");
}