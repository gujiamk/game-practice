#include "Chara.h"

Chara::Chara():Object()
{
    this->health = new int(100);
    this->attack = new int(10);
    this->defense = new int(2);
}

Chara::Chara(std::string name):Object()
{
    this->health = new int(100);
    this->attack = new int(10);
    this->defense = new int(2);

    std::ifstream ifs(Chara_info,std::ios::in);
    if (!ifs.is_open())
    {
        std::cout<<"加载人物档案时未能找到相关文件，你可咨询开发者解决！"<<std::endl;
        exit(0);
    }

    while (ifs >> *this->name >> *this->health
        >> *this->attack >> *this->defense)
    {
        if (name == *this->name) break;
    
    }

    ifs.close();
    if (name != *this->name)
    {
        std::cout<<"未找到该人物档案！"<<std::endl;
    }
    else std::cout<<"加载人物档案成功！"<<std::endl;

}

Chara::Chara(const std::string& name, const Point& point,int health, int attack, int defense):Object(name, point)
{
    this->health = new int(health);
    this->attack = new int(attack);
    this->defense = new int(defense);
}

Chara::Chara(const Chara& player):Object(*player.name, *player.Self_Point)
{
    this->health = new int(*player.health);
    this->attack = new int(*player.attack);
    this->defense = new int(*player.defense);
}

Chara& Chara::operator=(const Chara& player)
{
    if(this->name!=nullptr) delete this->name;
    this->name = new std::string(*player.name);

    if (this->Self_Point != nullptr) delete this->Self_Point;
    this->Self_Point = new Point(*player.Self_Point);

    if (this->health != nullptr) delete this->health;
    this->health = new int(*player.health);

    if (this->attack != nullptr) delete this->attack;
    this->attack = new int(*player.attack);

    if (this->defense != nullptr) delete this->defense;
    this->defense = new int(*player.defense);

    return *this;
}

std::ofstream& operator<<(std::ofstream& out, const Chara* const chara)
{
    out << *chara->name << " " 
        << chara->Self_Point->first << " "
        << chara->Self_Point->second << " "
        << *chara->health << " "
        << *chara->attack << " "
        << *chara->defense<< std::endl;
    return out;
}

void Chara::draw_self(const Point* const camera)
{
    std::string pic = "ss";
    picdv->draw_on_map(pic, this->Self_Point, camera);
}

void Chara::move(std::vector<std::vector<int>> map,Point* const camera, BYTE vkcode)
{
    switch (vkcode)
    {
    case VK_UP:
        if (this->Self_Point->second == 0) return;
        break;

    case VK_DOWN:
        if (this->Self_Point->second == stepy-1) return;
        break;
    case VK_LEFT:
        if (this->Self_Point->first == 0) return;
        break;
    case VK_RIGHT:
        if (this->Self_Point->first == stepx-1) return;
        break;
    }


    switch (vkcode)
    {
    case VK_UP:
        if (map[this->Self_Point->first][this->Self_Point->second - 1] == GRASS ||
            map[this->Self_Point->first][this->Self_Point->second - 1] == ROAD)
        {
            if (this->Self_Point->second - camera->second == 10 && camera->second > 0) camera->second--;
            this->Self_Point->second--;
        }
        break;

    case VK_DOWN:
        if (map[this->Self_Point->first][this->Self_Point->second + 1] == GRASS ||
            map[this->Self_Point->first][this->Self_Point->second + 1] == ROAD)
        {
            if (this->Self_Point->second - camera->second == 10 && camera->second < stepy/2) camera->second++;
            this->Self_Point->second++;

        }
        break;
    case VK_LEFT:
        if (map[this->Self_Point->first - 1][this->Self_Point->second] == GRASS ||
            map[this->Self_Point->first - 1][this->Self_Point->second] == ROAD)
        {
            if (this->Self_Point->first - camera->first == 12 && camera->first > 0) camera->first--;
            this->Self_Point->first--;

        }
        break;
    case VK_RIGHT:
        if (map[this->Self_Point->first + 1][this->Self_Point->second] == GRASS ||
            map[this->Self_Point->first + 1][this->Self_Point->second] == ROAD)
        {
            if (this->Self_Point->first - camera->first == 12 && camera->first < stepx/2) camera->first++;
            this->Self_Point->first++;

        }
        break;
    }
}

void Chara::func()
{

}

Chara::~Chara()
{
	if (this->health != nullptr)
	{
		delete this->health;
        this->health = nullptr;
	}

	if (this->attack != nullptr)
	{
        delete this->attack;
        this->attack = nullptr;
	}

    if (this->defense != nullptr)
    {
        delete this->defense;
        this->defense = nullptr;
    }
}