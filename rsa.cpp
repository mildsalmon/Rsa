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
암호화 복호화를 동시에 진행하는 메소드
c = m^e mod n
m = c^d mod n
라는 식은 같고 변수만 매개값만 바뀌면 되므로 하나의 메소드에서 처리함
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
 p와 q를 생성해서
 n, e, d 키를 생성
 * *********************************/
Key Rsa::produce_keys()
{
	long prime1 = produce_prime();	// p
	long prime2 = produce_prime();	// q
	while (prime2 == prime1)		// p와 q는 n을 만들고 폐기해야 하기 때문에
		prime2 = produce_prime();	// 따로 저장해서 메소드 밖으로 빼지 않음

	Key key;
	long orla = produce_orla(prime1, prime2);	// 오일러 n 생성
	key.pkey = produce_pkey(prime1, prime2);	// n 생성
	key.ekey = produce_ekey(orla);				// e 생성
	key.dkey = produce_dkey(key.ekey, orla);	// d 생성
	return key;
}

/************************************
 N 키 생성
 p * q
 * *********************************/
long Rsa::produce_pkey(const long prime1, const long prime2)
{
	return prime1 * prime2;
}

/************************************
 오일러 n 생성
************************************/
long Rsa::produce_orla(const long prime1, const long prime2)
{
	return (prime1 - 1) * (prime2 - 1);
}

/************************************
 암호화 키 (공개키) e 생성
 * *********************************/
long Rsa::produce_ekey(const long orla)
{
	long ekey;
	while (true)
	{
		ekey = rand() % orla;	// 랜덤 수를 오일러 n으로 나머지 연산
		if (ekey >= 2 && produce_gcd(ekey, orla) == 1)	// e-key와 오일러 n이 서로소인지 판별
			break;
	}
	return ekey;
}

/************************************
 복호화 키 (개인키) d 생성
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
 [100, 200] 범위에서 임의의 소수 생성
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
 두 숫자의 최대 공약수 생성		
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
 소수인지 판단
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

