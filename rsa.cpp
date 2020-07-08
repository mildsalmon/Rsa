#include "rsa.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <bitset>
#include <iostream>

using namespace std;

Rsa::Rsa()
{
}

Rsa::~Rsa()
{
}
/***********************************************************************
��ȣȭ ��ȣȭ�� ���ÿ� �����ϴ� �޼ҵ�
c = m^e mod n
m = c^d mod n
��� ���� ���� ������ �Ű����� �ٲ�� �ǹǷ� �ϳ��� �޼ҵ忡�� ó����
***********************************************************************/
long Rsa::endecrypt(const long msg, const long key, const long pkey)
{
	long msg_des = 1;
	long root = msg;
	long index = key;
	while (index)
	{
		//cout << bitset<32>(index) << endl;
		if (index & 1) {
			msg_des = (msg_des * root) % pkey;
			//cout << "msg_des : " << msg_des << endl;
		}
		index >>= 1;
		//cout << "b root : " << root << endl;
		root = (root * root) % pkey;
		//cout << "a root : " << root << endl;
	}
	return msg_des;
}


/************************************
 p�� q�� �����ؼ�
 n, e, d Ű�� ����
 * *********************************/
Key Rsa::produce_keys()
{
	long prime1 = produce_prime();	// p
	long prime2 = produce_prime();	// q
	while (prime2 == prime1)		// p�� q�� n�� ����� ����ؾ� �ϱ� ������
		prime2 = produce_prime();	// ���� �����ؼ� �޼ҵ� ������ ���� ����

	Key key;
	long orla = produce_orla(prime1, prime2);	// ���Ϸ� n ����
	key.pkey = produce_pkey(prime1, prime2);	// n ����
	key.ekey = produce_ekey(orla);				// e ����
	key.dkey = produce_dkey(key.ekey, orla);	// d ����
	return key;
}

/************************************
 N Ű ����
 p * q
 * *********************************/
long Rsa::produce_pkey(const long prime1, const long prime2)
{
	return prime1 * prime2;
}

/************************************
 ���Ϸ� n ����
************************************/
long Rsa::produce_orla(const long prime1, const long prime2)
{
	return (prime1 - 1) * (prime2 - 1);
}

/************************************
 ��ȣȭ Ű (����Ű) e ����
 * *********************************/
long Rsa::produce_ekey(const long orla)
{
	long ekey;
	while (true)
	{
		ekey = rand() % orla;	// ���� ���� ���Ϸ� n���� ������ ����
		if (ekey >= 2 && produce_gcd(ekey, orla) == 1)	// e-key�� ���Ϸ� n�� ���μ����� �Ǻ�
			break;
	}
	return ekey;
}

/************************************
 ��ȣȭ Ű (����Ű) d ����
 * *********************************/
long Rsa::produce_dkey(const long ekey, const long orla)
{
	long dkey = orla / ekey;
	while (true)
	{
		if (((dkey * ekey) % orla) == 1)
			break;
		else 
			++dkey;
	}
	return dkey;
}

/************************************
 [100, 200] �������� ������ �Ҽ� ����
 * *********************************/
long Rsa::produce_prime()
{
	long prime = 0;
	srand(time(0));
	while (true)
	{
		prime = rand() % 100 + 100;
		if (is_prime(prime))
			break;
	}
	return prime;
}

/************************************
 �� ������ �ִ� ����� ����		
 * *********************************/
long Rsa::produce_gcd(const long a, const long b)
{
	long dividend = a;
	long divisor = b;
	long residual = dividend % divisor;
	while (residual)
	{
		dividend = divisor;
		divisor = residual;
		residual = dividend % divisor;
	}
	return divisor;
}

/************************************
 �Ҽ����� �Ǵ�
 * *********************************/
bool Rsa::is_prime(const long digit)
{
	int tmp = 2;
	while (tmp < digit)
		if (!(digit % tmp++))
			break;

	if (tmp == digit)
		return true;
	return false;
}

