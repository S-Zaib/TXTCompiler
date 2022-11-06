#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "Queue_Stack.h"
#include "Image_extract.h"
using namespace std;

string infixer(string expression);
string remove_spaces(string str);
bool eval_or_exp(string expression);
// + - * / ^ ( ) 
bool prcd(char op1, char op2)
{
	switch (op2)
	{
	case '(':
		if(op1 != ')')
			return false;
		return true;
		break;
	case ')':
		if (op1 != '(')
			return true;
		return false;
		break;
	}
	switch (op1)
	{
	case '(':
		return false;
		break;
	case ')':
		cout << "SUUS" << endl;
		break;
	case '-':
		if (op2 == '-')
			return true;
		return false;
		break;
	case '+':
		if (op2 == '+')
			return true;
		return false;
		break;
	case '/':
		if (op2 == '+' || op2 == '-' || op2 == '/')
			return true;
		return false;
		break;
	case '*':
		if (op2 == '+' || op2 == '-' || op2 == '*')
			return true;
		return false;
		break;
	case '^':
	case '$':
			return true;
		break;
	default:
		cout << "Wrong OPERATOR ;/";
		break;
	}
}

bool opr_check(char x)
{
	if (x == '+' || x == '-' || x == '*' || x == '/' || x == '^' || x == '$' || x == '(' || x == ')')
		return true;
	return false;
}
bool signed_exp(string expression)
{
	int count = 0, size = 0;
	for (int i = 0; expression[i] != '\0'; i++)
	{
		if (expression[i] == ' ')
			size++;
		else
			break;
	}
	for (int i = size; expression[i] != '\0'; i++)
		if (expression[i] == ' ')
			count++;
	for (int i = size; expression[i] != '\0'; i++)
	{
		if ((expression[i + 1] != '\0' && expression[i + 1] != ' ' && !opr_check(expression[i + 1])) && (expression[i] == '-' || expression[i] == '+'))
			if (count > 0)
				return true;
	}
	return false;
}

string postfixer(string expression)
{
	Stack<string> stk;
	string ans = "";
	int size = 0;
	int brkt_count = 0;
	bool isSigned = signed_exp(expression);
	string temp_exp = remove_spaces(expression);
	while (!opr_check(temp_exp[size]) && temp_exp[size] != '\0')
		size++;
	if (size > 1)
		return infixer(expression);
	size = 0;
	while (expression[size] != '\0')
	{
		string temp_str = "";
		if (expression[size] != ' ')
		{
			if (expression[size] == '(')
				brkt_count++;
			if (!opr_check(expression[size]))
				ans += expression[size];
			else if (isSigned && (expression[size] == '-' || expression[size] == '+') && expression[size + 1] != ' ' && expression[size + 1] != '\0' && !opr_check(expression[size + 1]))
			{
				temp_str += expression[size];
				size++;
				temp_str += expression[size];
				ans += temp_str;
			}
			else
			{
				while (!stk.isEmpty() && prcd(stk.peek()[0], expression[size]))
					ans += stk.pop();
				if (expression[size] != ')')
				{
					temp_str += expression[size];
					stk.push(temp_str);
				}
				else
				{
					if(stk.isEmpty())
						return "Invalid Expression!";
					stk.pop();
					brkt_count--;
				}
			}
		}
		while (expression[size + 1] == '\0' && !stk.isEmpty())
			ans += stk.pop();
		size++;
	} 
	if(brkt_count != 0)
		return "Invalid Expression!";
	return ans;
}

string reverse_str(string str)
{
	Stack<char> stk;
	string ans = "";
	for (int i = 0; str[i] != '\0'; i++)
		stk.push(str[i]);
	while (!stk.isEmpty())
		ans += stk.pop();
	return ans;
}

string prefixer(string expression)
{
	int size = 0, count = 0, opr_count = 0;
	string temp_exp = remove_spaces(expression);
	while (opr_check(temp_exp[size]) && temp_exp[size] != '\0')
	{
		opr_count++;
		size++;
	}
	while (!opr_check(temp_exp[size]) && temp_exp[size] != '\0')
	{
		size++;
		count++;
	}
	if (count > 1 && opr_count > 0)
		return infixer(expression);
	size = 0;
	expression = reverse_str(temp_exp);
	for (int i = 0; expression[i] != '\0'; i++)
	{
		if (expression[i] == '(')
			expression[i] = ')';
		else if (expression[i] == ')')
			expression[i] = '('; 
	}
	string temp = postfixer(expression);
	if(temp != "Invalid Expression!")
		return reverse_str(temp);
	return temp;
}

string num_to_str(int n)
{
	string ans = "";
	bool isSigned = false;
	if (n < 0)
	{
		isSigned = true;
		n *= -1;
	}
	while (n)
	{
		ans += (n % 10) + '0';
		n /= 10;
	}
	if (isSigned)
		ans = '-' + reverse_str(ans);
	else
		ans = reverse_str(ans);
	return ans;
}

int str_to_num(string str)
{
	int ans = 0;
	for (int i = 0; str[i] != '\0'; i++)
		if (str[i] != ' ')
			ans = ans * 10 + (str[i] - '0');
	return ans;
}

string eval_func(string num1, char opr, string num2)
{
	string ans = "";
	int n_ans;
	int n1 = 0, n2 = 0;
	bool isSigned = false;
	for (int i = 0; num1[i] != '\0'; i++)
	{
		if (num1[i] == '-')
			isSigned = true;
		else
			n1 = n1 * 10 + (num1[i] - '0');
	}
	if (isSigned)
	{
		n1 *= -1;
		isSigned = false;
	}
	for (int i = 0; num2[i] != '\0'; i++)
	{
		if (num2[i] == '-')
			isSigned = true;
		else
			n2 = n2 * 10 + (num2[i] - '0');
	}
	if (isSigned)
	{
		n2 *= -1;
		isSigned = false;
	}
	switch (opr)
	{
	case '+':
		n_ans = n1 + n2;
		break;
	case '-':
		n_ans = n1 - n2;
		break;
	case '*':
		n_ans = n1 * n2;
		break;
	case '/':
		if (n2 != 0)
			n_ans = n1 / n2;
		else
			return "Infinity, div by 0!";
		break;
	case '^':
	case '$':
		n_ans = pow(n1, n2);
		break;
	default:
		cout << "Wrong OPERATOR ;/";
		return "";
	}
	return num_to_str(n_ans);
}

bool eval_or_exp(string expression)
{
	for (int i = 0; expression[i] != '\0'; i++)
		if ((expression[i] >= 'a' && expression[i] <= 'z') || (expression[i] >= 'A' && expression[i] <= 'Z'))
			return false;
	return true;
}

string infixer(string expression)
{
	if (expression == "Invalid Expression!")
		return expression;
	Stack<string> stk;
	int size = 0, count = 0;
	string ans;
	bool prefix = false, eval = eval_or_exp(expression), isSigned = signed_exp(expression);
	if (!isSigned)
		expression = remove_spaces(expression);
	while (expression[size] != '\0')
	{
		if (!opr_check(expression[size]))
			count++;
		else if (expression[size] == '(' || expression[size] == ')')
		{
			cout << "already infix" << endl;
			if (!eval)
				return expression;
			else
				return infixer(postfixer(expression));
		}
		else
			break;
		size++;
	}
	if (count == 1)
	{
		cout << "already infix" << endl;
		if (!eval)
			return expression;
		else
			return infixer(postfixer(expression));
	}
	size = 0, count = 0;
	int opr_count = 0;
	while (expression[size+1] != '\0' && opr_check(expression[size]) && expression[size+1] == ' ')
	{
		opr_count++;
		size++;
	}
	while ((expression[size] != ' ' && !opr_check(expression[size])) || (expression[size + 1] != '\0' && expression[size + 1] != ' ' && !opr_check(expression[size + 1]) && (expression[size] == '-' || expression[size] == '+')))
	{
		size++;
		count++;
	}
	if (count > 1 && opr_count > 0)
	{
		expression = reverse_str(expression);
		prefix = true;
	}
	
	size = 0;
	while (expression[size] != '\0')
	{
		string temp_str = "";
		if (expression[size] != ' ')
		{
			if (!opr_check(expression[size]))
			{
				temp_str += expression[size];
				stk.push(temp_str);
			}
			else if(isSigned && (expression[size] == '-' || expression[size] == '+') && expression[size+1] != ' ' && expression[size + 1] != '\0' && !opr_check(expression[size+1]))
			{
				temp_str += expression[size];
				size++;
				temp_str += expression[size];
				stk.push(temp_str);
			}
			else
			{
				if (stk.isEmpty())
					return "Invalid Expression!";
				string num1 = stk.pop();
				if (stk.isEmpty())
					return "Invalid Expression!";
				string num2 = stk.pop();
				if (!eval)
				{
					temp_str += '(';
					temp_str += num2;
					temp_str += expression[size];
					temp_str += num1;
					temp_str += ')';
					stk.push(temp_str);
				}
				else
				{
					if (!prefix)
						stk.push(eval_func(num2, expression[size], num1));
					else
						stk.push(eval_func(num1, expression[size], num2));
				}
			}
		}
		size++;
	}
	ans = stk.pop();
	if (prefix && !eval)
	{
		ans = reverse_str(ans);
		for (int i = 0; ans[i] != '\0'; i++)
		{
			if (ans[i] == '(')
				ans[i] = ')';
			else if (ans[i] == ')')
				ans[i] = '(';
		}
	}
	return ans;
}

string remove_char(string str, char ch)
{
	string final_str = "";
	int count = 0;
	while(str[count] != '\0')
	{
		if (str[count] != ch)
			final_str += str[count];
		count++;
	}
	return final_str;
}

void replace_str(file_data F, string str, string str2)
{
	fstream file;
	file.open(F.filename);
	char ch;
	string check = "";
	while (!file.eof())
	{
		file.get(ch);
		if (ch == str[0])
		{
			int count = 0;
			while (str[count] != '\0')
			{
				check += ch;
				file.get(ch);
				count++;
			}
			if (check == str)
			{
				file.seekp(-count, ios::cur);
				file << str2;
			}
			check = "";
		}
	}
}

string correction(string str, char ch1, char ch2)
{
	int count = 0;
	while (str[count] != '\0')
	{
		if (str[count] == ch1)
			str[count] = ch2;
		count++;
	}
	return str;
}

string remove_spaces(string str)
{
	string nospc = "";
	for (int i = 0; str[i] != '\0'; i++)
		if (str[i] != ' ')
			nospc += str[i];
	return nospc;
}

string tag_execute(string tag, string exp)
{
	if (tag == "|post_exp|")
		return postfixer(exp);
	else if (tag == "|pre_exp|")
		return prefixer(exp);
	else if (tag == "|sol_exp|")
		return infixer(exp);
	else if (tag == "|src|")
		return num_to_str(obj_detection( remove_char( "../TXTCompiler/data" + correction(exp, 'i', 'I') + ".png", ' ')));
}

file_data parse_file(file_data F)
{
	ifstream file;
	file.open(F.filename);
	char ch;
	int file_priority;
	Stack<string> stk, stk2;
	string tag_str = "";
	file.get(ch);
	while (!file.eof())
	{
		if (ch == '|')
		{
			if (tag_str != "")
			{
				stk.push(tag_str);
				tag_str = "";
			}
			tag_str += ch;
			do
			{
				file.get(ch);
				tag_str += ch;
			} while (ch != '|');
			file.get(ch);
			stk.push(tag_str);
			tag_str = "";
		}
		else
		{
			if (ch != '\t' && ch != '\n' && ch != '\r')
				tag_str += ch;
			file.get(ch);
		}
	}
	while (!stk.isEmpty())
		stk2.push(stk.pop());
	ofstream w_file;
	F.filename += "output.txt";
	w_file.open(F.filename);
	string store_exp = "";
	bool store_mode = false;
	while (!stk2.isEmpty())
	{
		string temp = stk2.pop();
		if (temp[0] == '|' && temp[1] != '\\')
		{
			stk.push(temp);
			if (temp == "|post_exp|" || temp == "|pre_exp|" || temp == "|sol_exp|" || temp == "|src|" || temp == "|priorty|")
				store_mode = true;
			else if (temp == "|head|" || temp == "|paragraph|")
				w_file << '\n';
		}
		else if (temp[0] == '|' && temp[1] == '\\')
		{
			temp = remove_char(temp, '\\');
			if (temp == "|post_exp|" || temp == "|pre_exp|" || temp == "|sol_exp|" || temp == "|src|" || temp == "|priorty|")
			{
				store_mode = false;
				if (temp != "|priorty|")
				{
					//cout << F.filename << endl;
					//cout << endl << endl << temp << " : " << store_exp << endl;
					//string trmp = tag_execute(temp, remove_spaces(store_exp));
					string trmp = tag_execute(temp, store_exp);
					//cout << trmp << endl << endl;
					w_file << trmp << " ";

				}
				else
					F.priorty = str_to_num(store_exp);
			}
			else if (temp == "|tab|")
				w_file << '\t';
			else if (temp == "|paragraph|" || temp == "|head|")
				w_file << '\n';
			if(!stk.remove(temp))
				w_file << "\nSyntax Error: No Start tag of " << temp << " found!" << endl;
		}
		else
		{
			if (store_mode)
				store_exp += temp;
			else
			{
				store_exp = "";
				w_file << temp;
			}
		}
	}
	while (!stk.isEmpty())
		w_file << "\nSyntax Error: No Close tag of " << stk.pop() << " found!" << endl;
	file.close();
	w_file.close();
	return F;
}

void files_LRU()
{
	LRU lru(4);
	string name = "../TXTCompiler/data/Test_files/Test-", ext = ".txt";
	int file_num = 7;
	file_data files[7], temp;
	ofstream wfile;
	wfile.open("../TXTCompiler/data/Output_files/Result-1.txt", ios::app);
	for (int i = 0; i < 7; i++)
	{
		ifstream rfile;
		files[i].filename = name + char(i + 1 + '0') + ext;
		temp = parse_file(files[i]);
		files[i].filename = temp.filename;
		files[i].priorty = temp.priorty;
		rfile.open(files[i].filename);
		wfile << rfile.rdbuf();
		lru.add(files[i]);
		rfile.close();
	}
	wfile << '\n' << "LRU Results: Total Hits: " << lru.get_hits() << ", Total Faults: " << lru.get_faults() << '\n';
	wfile.close();
	lru.print();
}