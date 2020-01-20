#pragma once
#include<stack>
#include<iostream>
#include<math.h>
using namespace std;

int weight(char op) {
	int w;
	switch (op) {
	case'+':w = 2; break;
	case'-':w = 2; break;
	case'*':
	case'/':w = 1; break;
	case '^': w = 0; break;
	default:w = -1; break;
	}
	return w;
}

void translate(char* exp, char* result) {
	stack<char> st;
	int n = strlen(exp);
	//int j = -1;
	int j = 0;
	int i = 0;
	st.push('(');


	while (i < n) {
		if (exp[i] >= '0' && exp[i] <= '9' || exp[i]>='a' && exp[i]<='z') {
			result[j++] = exp[i];
		}
		else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/'|| exp[i] == '^') {
			while ( (weight(st.top()) <= weight(exp[i])) && st.top()!='(') {
				result[j++] = st.top();
				st.pop();
			}
			st.push(exp[i]);
		}
		else if (exp[i] =='(') {
			st.push(exp[i]);
		}
		else if (exp[i] == ')') {
			while (st.top() != '(') {
				result[j++] = st.top();
				st.pop();
			}
			st.pop();
		}
		i++;
	}

	while (st.top() != '(') {
		result[j++] = st.top();
		st.pop();
	}
	st.pop();
	result[j++] = '\0';
}

int value(char* result) {
	stack<int> st;
	int i = 0;
	int n = strlen(result);
	int a, b;
	int val;
	char op;
	while (i < n) {
		if (result[i] >= '0' && result[i] <= '9') {
			st.push(result[i] - '0');
		}
		else if (result[i] == '+' || result[i] == '-' || result[i] == '*' || result[i] == '/' || result[i] == '^') {
			a = st.top();
			st.pop();
			b = st.top();
			st.pop();
			op = result[i];
			
			switch (op) {
			case'+': val = a + b; break;
			case'-':val = a - b; break;
			case'*':val = a * b; break;
			case'/':val = a / b; break;
			case'^':val = (int)pow(a, b); break;
			}
			st.push(val);
		}
		i++;
	}

	int res = st.top();
	st.pop();
	return res;
}

int main() {
	char s[200];
	cout << "s: "; cin >> s; 
	char s1[200];
	translate(s, s1); 
	cout << value(s1) << endl; 
	return 0;
}