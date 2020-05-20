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
			cout << "清除杂草" << endl;
			f.set_state(Field::Hoed);
		}			
		else
			cout << "杂草未清理无法操作" << endl;
	}
	if (l == Field::Hoed)
	{
		if (a == Hero::Seed) {
			cout << "种菜" << endl;
			f.set_state(Field::Seeded);
		}			
		else if(a == Hero::Hoe)
			cout << "无需清理杂草" << endl;
		else if (a == Hero::Pot)
			cout << "没有农作物无法浇水" << endl;
		else if (a == Hero::Knife)
			cout << "没有农作物无法收获" << endl;
	}
	if (l == Field::Seeded)
	{
		if (a == Hero::Pot) {
			cout << "浇水" << endl;
			f.set_state(Field::Poted);
		}
		else if (a == Hero::Knife)
			cout << "未成熟无法收割" << endl;
		else if (a == Hero::Hoe)
			cout << "无需清理杂草" << endl;
		else if (a == Hero::Seed)
			cout << "土地已占用无法播种" << endl;
	}
	if (l == Field::Harvest)
	{
		if (a == Hero::Knife) {
			cout << "收割" << endl;
			f.set_state(Field::Orig);
		}			
		else if (a == Hero::Hoe)
			cout << "无需清理杂草" << endl;
		else if (a == Hero::Pot)
			cout << "无需浇水" << endl;
		else if (a == Hero::Seed)
			cout << "土地已占用无法播种" << endl;
	}
}
int main() {
	Field l ;
	l.set_state(Field::Hoed);
	Hero a ;
	a.set_tool(Hero::Seed);
	userinteraction(l, a);
}