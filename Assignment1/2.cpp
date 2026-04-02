#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> nums;
    vector<int> x_list;
    vector<int> y_list;
    int num;
    double x_sum = 0.0, x_avg, y_sum = 0.0, y_avg;  // 初始化累加变量，避免随机值影响计算
    int group = 0;  // 初始化数据组数计数器
    double a, b;
    char answer;
    double classify;

    do{
        // 清空上一轮的数据，避免新旧数据混杂
        nums.clear();
        x_list.clear();
        y_list.clear();
        x_sum = 0.0;
        y_sum = 0.0;
        group = 0;

        cout << "enter how many group n: ";
        int n;  // 新增变量存储数据点数量
        cin >> n;  // 先读取数据点数量

        // 根据n读取2n个数据（每个点包含x和y）
        cout << "enter" << 2*n << "group:";
        for(int i = 0; i < 2*n; i++){  // 用n控制输入数量，避免无限输入
            cin >> num;
            nums.push_back(num);
        }

        // 解析x和y，每两个元素一组（x,y）
        bool input_valid = true;  // 标记输入是否有效
        for(int i = 0; i < nums.size(); i += 2){
            int x = nums[i];
            int y = nums[i + 1];  // 修复：取i+1作为y值（原i+2错误）

            if(x < 0 || y < 0){  // 同时检查x和y是否为负数
                cout << "couldn't be negative number" << endl;
                input_valid = false;
                break;
            }

            x_list.push_back(x);
            y_list.push_back(y);
            x_sum += x;
            y_sum += y;
            group++;
        }

        if(!input_valid){  // 输入无效时跳过后续计算
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        // 计算平均值（确保group不为0）
        if(group > 0){
            x_avg = x_sum / group;
            y_avg = y_sum / group;
        }else{
            cout << "Wrong" << endl;
            continue;
        }

        // 计算线性回归系数a和b（移到所有数据读取完成后计算，原逻辑重复计算）
        double atop = 0.0;
        double adown = 0.0;
        for(int i = 0; i < group; i++){  // 修复：初始化i=0（原未初始化）
            double xDiff = x_list[i] - x_avg;
            double yDiff = y_list[i] - y_avg;
            atop += xDiff * yDiff;
            adown += xDiff * xDiff;
        }

        if(adown == 0){  // 避免除零错误
            cout << "the value of x couldn't be similar" << endl;
            continue;
        }
        a = atop / adown;
        b = y_avg - a * x_avg;

        cout << " y = " << a << "x + " << b << endl;

        // 分类并输出结果
        for(int i = 0; i < group; i++){
            classify = a * x_list[i] + b;
            // 修复：坐标输出添加逗号，格式为(x,y)
            if(y_list[i] > classify){
                cout << "(" << x_list[i] << "," << y_list[i] << ") is class1" << endl;
            }else{
                cout << "(" << x_list[i] << "," << y_list[i] << ") is class0" << endl;
            }
        }

        cout << "Continue?(Y/N): ";
        cin >> answer;
        // 清除输入缓冲区，避免残留字符影响下次输入
        cin.ignore(1000, '\n');

    }while(answer == 'Y' || answer == 'y');  // 修复：循环条件改为判断answer，原语法错误

    cout << "end" << endl;  // 移到循环外，统一处理结束逻辑
    return 0;
}
