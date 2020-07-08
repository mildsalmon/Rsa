#include "rsa.h"
#include <iostream>

using namespace std;

int main(void)
{
	Rsa rsa;
	Key key = rsa.produce_keys();
	cout << "=====================================" << endl;
	cout << "암호화 후 얻은 키는 다음과 같습니다."<< endl;
	cout << "n 키 : " << key.pkey << endl;
	cout << "암호화 키 (공개키) : " << key.ekey << endl;
	cout << "암호 해독 키 (개인키) : " << key.dkey << endl;
	cout << "=====================================\n" << endl;
	long msg;
	cout << "암호화할 정보를 입력하십시오 (숫자, 너무 클 수 없음) : ";
	cin >> msg;
	cout << "\n=====================================" << endl;
	long msg_des = rsa.endecrypt(msg, key.ekey, key.pkey);
	cout << "암호화된 정보는 다음과 같습니다 : " << msg_des << endl;
	msg_des = rsa.endecrypt(msg_des, key.dkey, key.pkey);
	cout << "암호 해독된 메시지는 다음과 같습니다 : " << msg_des << endl;
	cout << "=====================================" << endl;
	return 0;
}
