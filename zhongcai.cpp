#include<bits/stdc++.h>
#include"field.h"
#include"hero.h"
using namespace std;
//Orig,
//Hoed,
//Seeded,
//Poted,
//Harvest

//None,
//Hoe,
//Knife,
//Pot,
//Seed
void userinteraction(Field f, Hero h) {
	auto l = f.get_state();
	auto a = h.get_tool();
	if (l == Field::Orig)
	{
		if (a == Hero::Hoe) {
			cout << "����Ӳ�" << endl;
			f.set_state(Field::Hoed);
		}			
		else
			cout << "�Ӳ�δ�����޷�����" << endl;
	}
	if (l == Field::Hoed)
	{
		if (a == Hero::Seed) {
			cout << "�ֲ�" << endl;
			f.set_state(Field::Seeded);
		}			
		else if(a == Hero::Hoe)
			cout << "���������Ӳ�" << endl;
		else if (a == Hero::Pot)
			cout << "û��ũ�����޷���ˮ" << endl;
		else if (a == Hero::Knife)
			cout << "û��ũ�����޷��ջ�" << endl;
	}
	if (l == Field::Seeded)
	{
		if (a == Hero::Pot) {
			cout << "��ˮ" << endl;
			f.set_state(Field::Poted);
		}
		else if (a == Hero::Knife)
			cout << "δ�����޷��ո�" << endl;
		else if (a == Hero::Hoe)
			cout << "���������Ӳ�" << endl;
		else if (a == Hero::Seed)
			cout << "������ռ���޷�����" << endl;
	}
	if (l == Field::Harvest)
	{
		if (a == Hero::Knife) {
			cout << "�ո�" << endl;
			f.set_state(Field::Orig);
		}			
		else if (a == Hero::Hoe)
			cout << "���������Ӳ�" << endl;
		else if (a == Hero::Pot)
			cout << "���载ˮ" << endl;
		else if (a == Hero::Seed)
			cout << "������ռ���޷�����" << endl;
	}
}
int main() {
	Field l ;
	l.set_state(Field::Hoed);
	Hero a ;
	a.set_tool(Hero::Seed);
	userinteraction(l, a);
}