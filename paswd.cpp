/*
 * Ľ�� ������ͨ��ѧ �����������ƣ�C++����һ�� �����ϰ
 * https://www.icourse163.org/course/XJTU-46006?tid=47003
 * �����������������룬�������£�
 * ��1���������ʽ����ѡ���������룻����Сд��ĸ������룻���ִ�д��ĸ������룻
 *   ���ִ�Сд��ĸ������ܣ����֡���Сд��ĸ�������ַ��� ! @ # $ % &��������롣
 * ��2��������������ĳ��ȣ���λ��������4λ��5λ��6λ�ȡ�
 * ��3���趨������ʽ�����볤�Ⱥ󣬿������ɶ������룬ֱ���û�ȷ���˳���
 *   �����˳����򣬻����Լ���ѡ��������ʽ�ͳ��ȣ����������롣
 * ��4�����������ļ���Ӳ��
 * �汾��2.0
 *  �ϲ�������ַ������ɺ����ͺϸ��жϺ�����randomTemp()�У�
 *  ������randomTemp()���Ը��ӡ�
 * �汾��3.0
 * 	�����main�������������ļ��������ļ�����password.exe���������ն�ʹ�������в������á�
 * 	�磺 	password
 * 		password -5 -6 -7 -0
 * 		password /4 /5 -3 /1
 * 		password -5 -6 -7 -0
 * 		password -5 -6
 * 	����	password asdfg �ȵȡ�
 */

#include <iostream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <fstream>
using namespace std;

class PasswordsWork {
public:
	PasswordsWork();						// �޲ι��캯���� ����ģʽ��
	PasswordsWork(int, int, int, int);// ���ι��캯��������ģʽ�� ����λ���� ���ɼ���, �Ƿ񱣴�1/0���� ��ģʽ��
private:
	void makePasswords();					// ��������ĺ���
	void randomTemp();						// ��������ַ���
	void print();							// ����̨�������s
	bool writeFile();						// ���������ļ���Ӳ��

	/* ���ݳ�Ա */
	int mode;					// ������ʽ
	int length;					// ���볤��
	int number;					// ���������
	vector<char> password;		// �洢number�����������(����length*number)
	vector<char> temp;			// ��ʱ����һ������(����length)
};

/*
 * �޲ι��캯���� ����ģʽ��
 */
PasswordsWork::PasswordsWork() {
	srand((int) time(0));
	cout << "*** ����������ɳ��� ***" << endl;
	while (true) {
		cout << "�����ģʽ��" << endl;
		cout << "  1���������룻" << endl;
		cout << "  2������Сд��ĸ������룻" << endl;
		cout << "  3�����ִ�д��ĸ������룻" << endl;
		cout << "  4�����ִ�Сд��ĸ������룻" << endl;
		cout << "  5�����֡���Сд��ĸ�������ַ��� ! @ # $ % &��������롣" << endl;
		cout << "����������Ҫ������ģʽ(1~5)��";
		cin >> mode;
		if (mode < 1 || mode > 5) {
			mode = 5;
		}
		cout << "����������Ҫ�����볤�ȣ�";
		cin >> length;
		if (length < 4) {
			length = 4;
		}
		cout << "����������Ҫ���ɼ������룺";
		cin >> number;
		if (number < 1) {
			number = 1;
		}
		password.clear();
		temp.clear();
		makePasswords();
		print();
		cout << "�������ɳɹ���" << endl;
		cout << "����Ҫ����������(y/n):";
		char yes;
		cin >> yes;
		if (yes == 'y' || yes == 'Y') {
			if (writeFile()) {
				cout << "�����ѱ��浽��ǰĿ¼��" << endl;
			} else {
				cout << "��Ǹ���ļ�д��ʧ�ܣ�" << endl;
			}
		}
		cout << "������������(c)�����˳�(q)����c/q����";
		char quit;
		cin >> quit;
		if (quit == 'q' || quit == 'Q') {
			break;
		}
	}
}

/*
 * ���ι��캯��������ģʽ�� ����λ���� ���ɼ���, �Ƿ񱣴�1(����)/0�������棩���� ��ģʽ��
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
	cout << "�������ɳɹ���" << endl;
	if (flag) {
		if (writeFile()) {
			cout << "�����ѱ��浽��ǰĿ¼��" << endl;
		} else {
			cout << "��Ǹ���ļ�д��ʧ�ܣ�" << endl;
		}
	}
}

/*
 * ��������ĺ���
 */
void PasswordsWork::makePasswords() {
	for (int i = 0; i < number; i++) {
		randomTemp();
		password.insert(password.end(), temp.begin(), temp.end());
	}
}

/*
 * ��������ַ���
 * �������ʽ��
 *	1���������룻
 *	2������Сд��ĸ������룻
 *	3�����ִ�д��ĸ������룻
 *	4�����ִ�Сд��ĸ������룻
 *	5�����֡���Сд��ĸ�������ַ��� ! @ # $ % &��������롣
 */
void PasswordsWork::randomTemp() {
	char c, special[7] = { '!', '@', '#', '$', '%', '&', '*' };
	bool digit_flag, lowercase_flag, capital_flag, special_flag;
	int key;
	while (true) {
		temp.clear();
		digit_flag = lowercase_flag = capital_flag = special_flag = false;
		for (int i = 0; i < length; i++) {
			if (mode == 1) {		// 1���������룻
				key = 1;
			} else if (mode == 3) {	// 3�����ִ�д��ĸ������룻
				key = rand() % 2 == 0 ? 1 : 3;
			} else if (mode == 4) {		// 4�����ִ�Сд��ĸ������룻
				key = rand() % 3 + 1;
			} else {					// 2 �� 5 �����
				key = rand() % mode + 1;
			}
			switch (key) {			// ע�� key ��  mode ����һһ��Ӧ��ϵ
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
		if (mode == 1) {			// temp����Ҫ��ʱwhileѭ������
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
 * ����̨���
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
 * д�����ļ���Ӳ��
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
		cout << "�ļ�д��ʧ�ܣ�" << endl;
		ret = false;
	}

	return ret;
}

int charToInt(const char *);	// char* ת�� int�������ˡ�-������/���ȷ��ź���ĸ��

int main(int argc, const char * argv[]) {
	if (argc == 1) {		// �޲ι��캯���� ����ģʽ��
		PasswordsWork pass;
	} else {	// ���ι��캯��������ģʽ�� ����λ���� ���ɼ���, �Ƿ񱣴�1(����)/0�������棩���� ��ģʽ��
		int temp[4] = { 0 };
		for (int i = 0; i < 4 && (i + 1) < argc; i++) {
			temp[i] = charToInt(argv[i + 1]);
		}
		PasswordsWork pass(temp[0], temp[1], temp[2], temp[3]);
	}

	return 0;
}

/*
 *  char* ת�� int�������ˡ�-������/���ȷ��ź���ĸ��
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
