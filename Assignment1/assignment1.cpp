#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<double> x_list;
    vector<double> y_list;
    double x_sum = 0.0, x_avg, y_sum = 0.0, y_avg;  
    int group = 0;  // Initialize the data group counter
    double a, b;
    char answer;
    double classify;

    do{
        vector<double> nums;
        double num;

        cout << "enter how many group n: ";
        int n;  // Add a new variable to store the number of data points
        cin >> n;  

        // Read 2n data points based on n (each point contains x and y)
        cout << "enter " << 2*n << " group:";
        for(int i = 0; i < 2*n; i++){  
            cin >> num;
            nums.push_back(num);
        }

        //  Parse x and y, grouping every two elements into a pair (x, y)。

        bool input_valid = true;  
        for(int i = 0; i < nums.size(); i += 2){
            double x = nums[i];
            double y = nums[i + 1];  

            if(x < 0 || y < 0){  
                // Check if both x and y are negative numbers at the same time
                cout << " x and y couldn't be negative number" << endl;
                input_valid = false;
                break;
            }

            x_list.push_back(x);
            y_list.push_back(y);
            x_sum += x;
            y_sum += y;
            group++;
        }

        if(!input_valid){  
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        // Calculate the average (ensure that the group is not zero)
        if(group > 0){
            x_avg = x_sum / group;
            y_avg = y_sum / group;
        }else{
            cout << "Wrong" << endl;
            continue;
        }

        // Calculate the linear regression coefficients a and b
        double atop = 0.0;
        double adown = 0.0;
        for(int i = 0; i < group; i++){  
            double xDiff = x_list[i] - x_avg;
            double yDiff = y_list[i] - y_avg;
            atop += xDiff * yDiff;
            adown += xDiff * xDiff;
        }

        if(adown == 0){  
            cout << "the value of x couldn't be similar" << endl;
            continue;
        }
        a = atop / adown;
        b = y_avg - a * x_avg;

        cout << " y = " << a << "x + " << b << endl;

        // Classify and output the results。
        for(int i = 0; i < group; i++){
            classify = a * x_list[i] + b;
           
            if(y_list[i] > classify){
                cout << "(" << x_list[i] << "," << y_list[i] << ") is class1" << endl;
            }else{
                cout << "(" << x_list[i] << "," << y_list[i] << ") is class0" << endl;
            }
        }

        cout << "Continue?(Y/N): ";
        cin >> answer;
        cin.ignore(1000, '\n');

    }while(answer == 'Y' || answer == 'y');  

    cout << "end" << endl;  
    return 0;
}
