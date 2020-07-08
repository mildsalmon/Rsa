#include "rsa.h"
#include <iostream>

using namespace std;

int main(void)
{
	Rsa rsa;
	Key key = rsa.produce_keys();
	cout << "=====================================" << endl;
	cout << "��ȣȭ �� ���� Ű�� ������ �����ϴ�."<< endl;
	cout << "n Ű : " << key.pkey << endl;
	cout << "��ȣȭ Ű (����Ű) : " << key.ekey << endl;
	cout << "��ȣ �ص� Ű (����Ű) : " << key.dkey << endl;
	cout << "=====================================\n" << endl;
	long msg;
	cout << "��ȣȭ�� ������ �Է��Ͻʽÿ� (����, �ʹ� Ŭ �� ����) : ";
	cin >> msg;
	cout << "\n=====================================" << endl;
	long msg_des = rsa.endecrypt(msg, key.ekey, key.pkey);
	cout << "��ȣȭ�� ������ ������ �����ϴ� : " << msg_des << endl;
	msg_des = rsa.endecrypt(msg_des, key.dkey, key.pkey);
	cout << "��ȣ �ص��� �޽����� ������ �����ϴ� : " << msg_des << endl;
	cout << "=====================================" << endl;
	return 0;
}
