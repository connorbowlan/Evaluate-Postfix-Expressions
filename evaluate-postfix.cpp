#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Determines if the character is a number
bool isDigit(char c)
{
	int value = c-48;
	if(value >= 0 && value <= 9)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Returns values for operators
int getPrecedence(char op)
{
	switch(op)
	{
		case '^': return 3;
		case '*': return 2;
		case '/': return 2;
		case '+': return 1;
		case '-': return 1;
		case '(': return 0;
	}
	return -1; // If no cases match, return -1
}

int evaluate(char num1, char token, char num2)
{
	int x = num1;
	int y = num2;

	int result;
	switch(token)
	{
		case '+' : result = x + y;
			break;
		case '-' : result = x - y;
			break;
		case '*' : result = x * y;
			break;
		case '/' : result = x / y;
			break;
		case '^' : result = x ^ y;
			break;
	}
	return result;
}

// Class for stack of operators
class Stack
{
	char operators[100];
	int count;
	
public:
	// Resets the count and values of the stack up to 100 operators
	Stack()
	{
		count = 0;
		for (int i = 0; i <= 100; i++)
		{
			operators[i] = 0;
		}
	}
	
	// Checks if the stack is empty or not based off the count
	bool isEmpty()
	{
		if(count == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	// Uses getPrecedence to establish priority of operations in the equation
	bool precedence(char c)
	{
		if(getPrecedence(c) <= getPrecedence(operators[count-1]))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	// Returns the character on the top of the stack
	char top()
	{
		return operators[count-1];
	}
	
	// Adds a single operator to the stack array, then increments to the next slot with count
	void push(char x)
	{
		operators[count] = x;
		count++;
	}
	
	// Removes a single operator off the top of the stack array, then increments count back to the top
	char pop()
	{
		char temp = operators[count-1];
		count--;
		return temp;
	}
};

class postStack {
	int digits[100];
	int count;
	
public:

	bool isEmpty()
	{
		if(count == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	postStack()
	{
		count = 0;
		for (int i = 0; i <= 100; i++)
		{
			digits[i] = 0;
		}
	}
	
	int push(int x)
	{
		digits[count] = x;
		count++;
	}
	
	int pop()
	{
		char temp = digits[count-1];
		count--;
		return temp;
	}
};

// Function to condition/determine sorting of numbers and operators
void stackLine(string line)
{
	Stack stack; // Declares the use of the class
	int length = line.length(); // Finds the length of the line
	
	string postfixEquation = "";
	
	for(int i=0; i < length; i++) // Loops through every character in the line
	{
		if(line[i] != ' ') // If the character is not a space ->
		{
			if(isDigit(line[i])) // If the character is a number ->
			{
				cout << line[i]; // Print out the number
				postfixEquation += line[i];
			}
			else if(line[i] == '(') // If the character is a left parenthesis ->
			{
				stack.push(line[i]); // Push the parenthesis onto the stack
			}
			else if(line[i] == ')') // If the character is a right parenthesis ->
			{
				while(stack.top() != '(') // While the top of the stack is NOT a left parenthesis ->
				{
					if (stack.isEmpty()) {
						break;
					}
					char c = stack.pop();
					cout << c; // Print out everything but the parenthesis
					postfixEquation += c;
				}
				stack.pop(); // Pop the parenthesis from the stack
			}
			else
			{
				if(stack.isEmpty()) // If the stack is empty ->
				{
					stack.push(line[i]); // Push the current character onto the stack
				}
				else
				{
					while(!stack.isEmpty() && stack.precedence(line[i])) // If the stack is NOT empty, while the value of the operators ->
					{
						char c = stack.pop();
						cout << c; // Print the operator on the top of the stack
						postfixEquation += c;
					}
					stack.push(line[i]); // Push next character on the stack
				}
			}
		}
	}
	while(!stack.isEmpty()) // If the stack is NOT empty yet ->
	{
		char c = stack.pop();
		cout << c; // Print the rest of the stack
		postfixEquation += c;
	}
	

	postStack numbers;
	
	string equation = "235*+";
	for(int i=0; i < postfixEquation.length(); i++)
	{
		char token = postfixEquation[i];
		if(isDigit(token))
		{
			int converted = token-48;
			numbers.push(converted);
		}
		else
		{
			char num2 = numbers.pop();
			char num1 = numbers.pop();
			int result = evaluate(num1, token, num2);
			numbers.push(result);
		}
	}
	while(!numbers.isEmpty())
	{
		cout << endl;
		cout << numbers.pop();
	}

}

main()
{
	// Read in the equations from the data file
	string line;
	ifstream inData;
	inData.open("expressions.txt");
	while(getline(inData, line))
	{
		stackLine(line);
		cout << endl;
	}
	inData.close();
}
