#include <iostream>
#include <conio.h>
#include <quadmath.h>
using namespace std;


__float128 StringToFloat128(string& s)
{
    return strtoflt128(s.c_str(), NULL);/*we convert our string to float128
    c_str() is needed because the founction came from C and cannot work with string itself.
    So, it converts our string s into C-string. NULL is needed, because we can
    check what was the final symbol of converting. We do not need that.*/
}

void printFloat128(__float128& value) {
    char buffer[128];
    quadmath_snprintf(buffer, sizeof(buffer), "%.30Qg", value);/*quadmath_snprintf is a powerful function
    proposed by Gemini :). It takes buffer to paste here the text with the size of buffer,
    "%.30Qg" - means that we want 30 signs of decimal part, we work with the type Quad (Q)
    g - clever mode, function can to outpot either decimal part or with the help of e.
    Value is the number we are printing.*/
    cout << buffer;
}

int main()
{
    
    string input1{""},input2{""};
    __float128 number1{0.0}, number2{0.0};     
    char operation;               
    bool isValidOperation{true};     
    __float128 result{0.0};
    char choice{'y'};              
    do
    {
        isValidOperation = true;
        cout << "\t\t\t=== Ultra 128-bit Calculator ===" << endl;
        cout << "Enter first number: ";
        cin >> input1;
        number1 = StringToFloat128 (input1);
        cout << "Enter second number: ";
        cin >> input2;
        number2 = StringToFloat128 (input2);
        cout << "Enter an operator (+, -, *, /) or type:\n1 for addition, 2 for subtraction, 3 for multiplication, 4 for division: ";
        cin >> operation;

        switch (operation)
        {
            case '+':
            case '1':
                result = number1 + number2;
                cout << "\nOperation: " << input1 << " + " << input2 << endl;
                break;

            case '-':
            case '2':
                result = number1 - number2;
                cout << "\nOperation: " << input1 << " - " << input2 << endl;
                break;

            case '*':
            case '3':
                result = number1 * number2;
                cout << "\nOperation: " << input1 << " * " << input2 << endl;
                break;

            case '/':
            case '4':
                
                if (number2 == 0)
                {
                    cout << "\nError: Division by zero is not allowed!" << endl;
                    isValidOperation = false;
                }
                else
                {
                    result = number1/ number2;
                    cout << "\nOperation: " << input1 << " / " << input2 << endl;
                }
                break;

            default:
                
                cout << "\nError: Invalid operator entered!" << endl;
                isValidOperation = false;
                break;
        }

        
        if (isValidOperation)
        {
            cout << "Result: " ;
            printFloat128(result);
        }
        else
        {
            cout << "Calculation could not be performed." << endl;
        }
        cout<< "\nDo you want to perform another calculation? (y/n): ";
        cin >> choice;


    } while (choice == 'y' || choice == 'Y');
    

    cout << "\nThank you for your interest!\nPress any key to exit...";
    getch();

    return 0;
}