/*
 * 慕课 西安交通大学 计算机程序设计（C++）第一期 编程练习
 * https://www.icourse163.org/course/XJTU-46006?tid=47003
 * 密码程序，生成随机密码，功能如下：
 * （1）密码的形式可以选择：数字密码；数字小写字母混合密码；数字大写字母混合密码；
 *   数字大小写字母混合秘密；数字、大小写字母、特殊字符（ ! @ # $ % &）混合密码。
 * （2）可以设置密码的长度（即位数），如4位、5位、6位等。
 * （3）设定密码形式、密码长度后，可以生成多组密码，直到用户确认退出。
 *   但不退出程序，还可以继续选择密码形式和长度，再生成密码。
 * （4）保存密码文件到硬盘
 * 版本：2.0
 *  合并了随机字符串生成函数和合格判断函数到randomTemp()中，
 *  代价是randomTemp()稍显复杂。
 * 版本：3.0
 * 	完成了main函数，编译后的文件（假设文件名：password.exe）可以在终端使用命令行参数调用。
 * 	如： 	password
 * 		password -5 -6 -7 -0
 * 		password /4 /5 -3 /1
 * 		password -5 -6 -7 -0
 * 		password -5 -6
 * 	甚至	password asdfg 等等。
 */

#include <iostream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <fstream>
using namespace std;

class PasswordsWork {
public:
	PasswordsWork();						// 无参构造函数， 互动模式。
	PasswordsWork(int, int, int, int);// 带参构造函数（生成模式， 密码位数， 生成几组, 是否保存1/0）， 简单模式。
private:
	void makePasswords();					// 生成密码的函数
	void randomTemp();						// 生成随机字符串
	void print();							// 控制台输出密码s
	bool writeFile();						// 保存密码文件到硬盘

	/* 数据成员 */
	int mode;					// 密码形式
	int length;					// 密码长度
	int number;					// 密码的组数
	vector<char> password;		// 存储number组密码的向量(长度length*number)
	vector<char> temp;			// 临时保存一组密码(长度length)
};

/*
 * 无参构造函数， 互动模式。
 */
PasswordsWork::PasswordsWork() {
	srand((int) time(0));
	cout << "*** 随机密码生成程序 ***" << endl;
	while (true) {
		cout << "密码的模式：" << endl;
		cout << "  1、数字密码；" << endl;
		cout << "  2、数字小写字母混合密码；" << endl;
		cout << "  3、数字大写字母混合密码；" << endl;
		cout << "  4、数字大小写字母混合密码；" << endl;
		cout << "  5、数字、大小写字母、特殊字符（ ! @ # $ % &）混合密码。" << endl;
		cout << "请输入您需要的密码模式(1~5)：";
		cin >> mode;
		if (mode < 1 || mode > 5) {
			mode = 5;
		}
		cout << "请输入您需要的密码长度：";
		cin >> length;
		if (length < 4) {
			length = 4;
		}
		cout << "请输入您需要生成几组密码：";
		cin >> number;
		if (number < 1) {
			number = 1;
		}
		password.clear();
		temp.clear();
		makePasswords();
		print();
		cout << "密码生成成功！" << endl;
		cout << "您需要保存密码吗？(y/n):";
		char yes;
		cin >> yes;
		if (yes == 'y' || yes == 'Y') {
			if (writeFile()) {
				cout << "密码已保存到当前目录！" << endl;
			} else {
				cout << "抱歉！文件写入失败！" << endl;
			}
		}
		cout << "继续生成密码(c)还是退出(q)？（c/q）：";
		char quit;
		cin >> quit;
		if (quit == 'q' || quit == 'Q') {
			break;
		}
	}
}

/*
 * 带参构造函数（生成模式， 密码位数， 生成几组, 是否保存1(保存)/0（不保存））， 简单模式。
 */
PasswordsWork::PasswordsWork(int mode, int length, int number, int flag) {
	srand((int) time(0));
	if (mode < 1 || mode > 5) {
		this->mode = 5;
	} else {
		this->mode = mode;
	}
	if (length < 4) {
		this->length = 4;
	} else {
		this->length = length;
	}
	if (number < 1 || number > 100) {
		this->number = 7;
	} else {
		this->number = number;
	}
	password.clear();
	temp.clear();
	makePasswords();
	print();
	cout << "密码生成成功！" << endl;
	if (flag) {
		if (writeFile()) {
			cout << "密码已保存到当前目录！" << endl;
		} else {
			cout << "抱歉！文件写入失败！" << endl;
		}
	}
}

/*
 * 生成密码的函数
 */
void PasswordsWork::makePasswords() {
	for (int i = 0; i < number; i++) {
		randomTemp();
		password.insert(password.end(), temp.begin(), temp.end());
	}
}

/*
 * 生成随机字符串
 * 密码的形式：
 *	1、数字密码；
 *	2、数字小写字母混合密码；
 *	3、数字大写字母混合密码；
 *	4、数字大小写字母混合密码；
 *	5、数字、大小写字母、特殊字符（ ! @ # $ % &）混合密码。
 */
void PasswordsWork::randomTemp() {
	char c, special[7] = { '!', '@', '#', '$', '%', '&', '*' };
	bool digit_flag, lowercase_flag, capital_flag, special_flag;
	int key;
	while (true) {
		temp.clear();
		digit_flag = lowercase_flag = capital_flag = special_flag = false;
		for (int i = 0; i < length; i++) {
			if (mode == 1) {		// 1、数字密码；
				key = 1;
			} else if (mode == 3) {	// 3、数字大写字母混合密码；
				key = rand() % 2 == 0 ? 1 : 3;
			} else if (mode == 4) {		// 4、数字大小写字母混合密码；
				key = rand() % 3 + 1;
			} else {					// 2 及 5 的情况
				key = rand() % mode + 1;
			}
			switch (key) {			// 注意 key 和  mode 不是一一对应关系
			case 1:
				c = '0' + rand() % 10;
				digit_flag = true;
				break;
			case 2:
				c = 'a' + rand() % 26;
				lowercase_flag = true;
				break;
			case 3:
				c = 'A' + rand() % 26;
				capital_flag = true;
				break;
			default:
				c = special[rand() % 7];
				special_flag = true;
			}
			temp.push_back(c);
		}
		if (mode == 1) {			// temp符合要求时while循环出口
			break;
		} else if (mode == 2 && digit_flag && lowercase_flag) {
			break;
		} else if (mode == 3 && digit_flag && capital_flag) {
			break;
		} else if (mode == 4 && digit_flag && lowercase_flag && capital_flag) {
			break;
		} else if (digit_flag && lowercase_flag && capital_flag
				&& special_flag) {
			break;
		}
	}
}

/*
 * 控制台输出
 */
void PasswordsWork::print() {
	vector<char>::iterator it = password.begin();
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < length; j++) {
			cout << *it++ << ' ';
		}
		cout << endl;
	}
}

/*
 * 写密码文件到硬盘
 */
bool PasswordsWork::writeFile() {
	bool ret = true;
	static int n = 0;
	char fileName[20] = "passwords-x.txt";
	fileName[10] = 'a' + n++;
	if (n > 25) {
		n = 0;
	}
	ofstream fw(fileName);
	if (fw) {
		vector<char>::iterator it = password.begin();
		for (int i = 0; i < number; i++) {
			for (int j = 0; j < length; j++) {
				fw << *it++;
			}
			fw << endl;
		}
		fw.close();
	} else {
		cout << "文件写入失败！" << endl;
		ret = false;
	}

	return ret;
}

int charToInt(const char *);	// char* 转换 int，屏蔽了‘-’、‘/’等符号和字母。

int main(int argc, const char * argv[]) {
	if (argc == 1) {		// 无参构造函数， 互动模式。
		PasswordsWork pass;
	} else {	// 带参构造函数（生成模式， 密码位数， 生成几组, 是否保存1(保存)/0（不保存））， 简单模式。
		int temp[4] = { 0 };
		for (int i = 0; i < 4 && (i + 1) < argc; i++) {
			temp[i] = charToInt(argv[i + 1]);
		}
		PasswordsWork pass(temp[0], temp[1], temp[2], temp[3]);
	}

	return 0;
}

/*
 *  char* 转换 int，屏蔽了‘-’、‘/’等符号和字母。
 */
int charToInt(const char * str) {
	int num = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] >= '0' && str[i] <= '9') {
			num *= 10;
			num += str[i] - '0';
		}
	}

	return num;
}
