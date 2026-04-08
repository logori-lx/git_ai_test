// 请设计一个简单的机器人类体系：
// 1. 抽象基类 Robot：
//   - 成员：name（名称）、battery（电量 0~100）
//   - 纯虚函数：void perform_task() — 不同机器人执行不同行为
//   - 虚析构函数
// 2. 派生出两个具体类：
//   - IndustrialRobot：perform_task() 输出搬运信息，消耗 20 电量
//   - ServiceRobot：perform_task() 输出服务信息，消耗 10 电量
//   - 电量不足时输出提示，不执行任务
// 3. 在 main 中：
//   - 用基类指针数组（或 vector<Robot*>）管理不同机器人
//   - 遍历调用 perform_task()，体现运行时多态
#include<string>
#include<vector>
#include<iostream>
using namespace std;
class Robot{
    public:
    Robot(){
        this->battery = 100;
    }
    Robot(double battery){
        this->battery = battery;
    }
    virtual ~Robot(){}
    std::string name;
    double battery;
    virtual void perform_task();
};
class IndustrialRobot : public Robot{
    public:
    ~IndustrialRobot() override{};
    IndustrialRobot(double battery) : Robot(){
        this->battery = battery;
    }
    void perform_task() override{
        if(this->battery <= 20){
            std::cout << "low battery!" << std::endl;
            return;
        }
        this->battery -= 20;
        std::cout << "IndustrialRobot" << "battery: " << this->battery << std::endl;
    };
};
class ServiceRobot : public Robot{
    public:
    ~ServiceRobot()override{};
    ServiceRobot(double battery) : Robot(){
        this->battery = battery;
    }
    void perform_task() override{
        if(this->battery <= 10){
            std::cout << "low battery!" << std::endl;
            return;
        }
        this->battery -= 10;
        std::cout << "ServiceRobot " << "battery: " << this->battery << std::endl;
    }
};

int main(){
    IndustrialRobot* r1 = new IndustrialRobot(100);
    ServiceRobot* r2 = new ServiceRobot(100);
    vector<Robot *> arr{r1, r2};
    for(auto &robot : arr){
        robot->perform_task();
    }
    delete r1;
    delete r2;
}


