#include "cmp_persistence.h"
#include "cmp_pickup_ammo.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "engine.h"
#include "../game.h"
using namespace std;
using namespace sf;

void LoadFileComponent::update(double dt)
{
}

string LoadFileComponent::LoadFile(string fileToRead)
{
	string output;
	char c;
	ifstream loadFile;
	string path4;
	path4 = getenv("appdata");
	path4 += "\\" + fileToRead;
	loadFile.open(path4.c_str());
	if (loadFile.is_open())
	{
		while (loadFile.get(c))
		{
			output += c;
		}
	}
	else
	{
		//cout << "No file";
	}

	loadFile.close();
	return output;
}

LoadFileComponent::LoadFileComponent(Entity* p)
	: Component(p) {}


void SaveFileComponent::update(double dt)
{
}

void SaveFileComponent::SaveFile(string level)
{
	string path1;
	ofstream saveFile;

	path1 = getenv("appdata");
	////cout << "appdata=" << path << endl;
	path1 += "\\ZombieHouseSaveFile.txt";
	////cout << "path=" << path << endl;
	saveFile.open(path1.c_str());
	if (saveFile.is_open())
	{
		saveFile << level;
	}
	

	ofstream levelFile;
	string path2;
	path2 = getenv("appdata");
	path2 += "\\Level" + level + ".dat";
	levelFile.open(path2.c_str());
	if (levelFile.is_open())
	{
		levelFile << zombieKillCount << "," << ammoPickupCount;
	}
	

	ofstream ammoFile;
	string path3;
	path3 = getenv("appdata");
	path3 += "\\ammo.dat";
	levelFile.open(path3.c_str());
	ammoFile.open(path3);
	if (ammoFile.is_open())
	{
		if (auto pl = _player.lock())
		{
			auto ammo = pl->GetCompatibleComponent<PickupAmmoComponent>().at(0);
			string p_ammo;
			string smg_ammo;
			string shotgun_ammo;
			if (ammo->getAmmo("pistol") < 10)
			{
				p_ammo = "0" + to_string(ammo->getAmmo("pistol"));
			}
			else
			{
				p_ammo = to_string(ammo->getAmmo("pistol"));
			}
			if (ammo->getAmmo("smg") < 10)
			{
				smg_ammo = "0" + to_string(ammo->getAmmo("smg"));
			}
			else
			{
				smg_ammo = to_string(ammo->getAmmo("smg"));
			}
			if (ammo->getAmmo("smg") < 10)
			{
				shotgun_ammo = "0" + to_string(ammo->getAmmo("shotgun"));
			}
			else
			{
				shotgun_ammo = to_string(ammo->getAmmo("shotgun"));
			}
			ammoFile << p_ammo << "," << smg_ammo << "," << shotgun_ammo;
		}
		
	}
	saveFile.close();
	levelFile.close();
	ammoFile.close();
}

SaveFileComponent::SaveFileComponent(Entity * p)
	: Component(p), _player(_parent->scene->ents.find("player")[0]) {}
