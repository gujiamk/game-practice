#include "PhotoDV.h"

PhotoDV* picdv = getPhtoDv();

Point camera(0, 0);

int view(std::string name)
{
    if (name == "grass")
    {
        return GRASS;
    }
    else if (name == "tree")
    {
        return TREE;
    }
    else if (name == "house")
    {
        return HUOSE;
    }
    else if (name == "cityroad")
    {
        return ROAD;
    }
    else if (name == "ss")
    {
        return SS;
    }
    else
    {
        std::cout << "没有此图片!" << std::endl;
        return 0;
    }
}

void print_word(const std::string& text, Point leftpoint,int size,bool isfix)
{
    if (!isfix)
    {
        leftpoint=FixPoint()(leftpoint);
    }

    settextcolor(WHITE);
    setbkcolor(BLACK);
    settextstyle(size,0,"微软雅黑");
    outtextxy(leftpoint.first, leftpoint.second, text.c_str());
}
void print_word(const std::string& text, int x, int y,int size, bool isfix)
{
    Point leftpoint(x, y);
    if (!isfix)
    {
        leftpoint = FixPoint()(x, y);
        isfix=true;
    }
    print_word(text, leftpoint, size, isfix);
}

PhotoDV::PhotoDV()
{
    
    std::ifstream ifs(mansRoad, std::ios::in);
    if (!ifs.is_open())
    {
        std::cout << "打开文件失败" << std::endl;
    }

    std::string picname, picpath;
    while (ifs >> picname >> picpath)
    {
        IMAGE *pic = new IMAGE;
        if (picpath == "=")
        {
            ifs>>picpath;
        }
        loadimage(pic, picpath.c_str(),step,step);
        picres.insert(std::make_pair(picname, pic));
    }
    ifs.close();

}

void PhotoDV::savemap(std::vector<std::vector<int>>& map)
{

    int x = 0;
    std::cout << "是否保存编辑地图？" << std::endl;
    std::cin >> x;
    if (x != 1) return;

    std::ofstream ofs;
    ofs.open(maproad, std::ios::out | std::ios::trunc);

    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            ofs << map[i][j] << " ";
        }
        ofs << "\n";
    }

    ofs.close();
    std::cout << "保存成功" << std::endl;
    return;
}

void PhotoDV::loadmap(std::vector<std::vector<int>>& map)
{ 
    std::ifstream ifs;
    ifs.open(maproad,std::ios::in);

    if (!ifs.is_open())
    {
        std::cout << "载入地图失败" << std::endl;
    }

    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            ifs >> map[i][j];
        }
    }

    ifs.close();
}

void PhotoDV::operator()(const std::string& name, const Point* const camera,int x,int y)
{
    auto it = picres.find(name);

    if (it != picres.end())
    {
        Point point = FixPoint()(x, y,camera);
        putimage(point.first, point.second, this->picres[name]);
    }
    
    return;
}

void PhotoDV::operator()(const std::string& name, int x, int y)
{
    auto it = picres.find(name);

    if (it != picres.end())
    {
        Point point = FixPoint()(x, y, camera);
        putimage(point.first, point.second, this->picres[name]);
    }

    return;
}

PhotoDV* getPhtoDv()
{
    return new PhotoDV();
}

void PhotoDV::Edit_map()
{
    initgraph(WIDTH, HEIGHT, SHOWCONSOLE);
    Point camera(0, 0);

    std::vector<std::vector<int>> map(stepx, std::vector<int>(stepy, 0));

    this->loadmap(map);

    setfillcolor(BLACK);
    setlinecolor(WHITE);

    cleardevice();

    ExMessage msg{ 0 };
    std::string name;

    BeginBatchDraw();

    while (msg.vkcode != VK_SPACE)
    {
        cleardevice();
        for (int i = 0; i < WIDTH; i += step)
        {
            line(i, 0, i, HEIGHT);
        }
        for (int i = 0; i < HEIGHT; i += step)
        {
            line(0, i, WIDTH, i);
        }

        for (int i = camera.first; i < camera.first + 25; i++)
        {
            for (int j = camera.second; j < camera.second + 20; j++)
            {
                if (map[i][j] == GRASS)
                {
                    this->operator()("grass", i, j);
                }
                else if (map[i][j] == TREE)
                {
                    this->operator()("tree", i, j);
                }
                else if (map[i][j] == HUOSE)
                {
                    this->operator()("house", i, j);
                }
                else if (map[i][j] == ROAD)
                {
                    this->operator()("cityroad", i, j);
                }
                else if (map[i][j] == SS)
                {
                    this->operator()("ss", i, j);
                }
            }
        }
        FlushBatchDraw();

        getmessage(&msg, EX_KEY| EX_MOUSE);
        if (msg.message == WM_KEYDOWN)
        {
            switch (msg.vkcode)
            {
            case VK_LEFT:
                if (camera.first > 0)
                    camera.first--;
                break;
            case VK_RIGHT:
                if (camera.first < 25)
                    camera.first++;
                break;
            case VK_UP:
                if (camera.second > 0)
                    camera.second--;
                break;
            case VK_DOWN:
                if (camera.second < 20)
                    camera.second++;
                break;
            case VK_TAB:
                std::cout << "请输入图片名称:";
                std::cin >> name;
                break;
            case VK_SPACE:

                break;
            default:
                break;
            }

            std::cout<<"当前相机坐标:"<<camera.first<<"|"<<camera.second<<std::endl;

        }
        else if (msg.message == WM_LBUTTONDOWN)
        {
            int x = msg.x, y = msg.y;

            x=x/step;
            y=y/step;

            std::cout << "图片坐标:"<<x<<"|"<<y<<std::endl;

            map[x+camera.first][y+camera.second] = view(name);;
        }

    }

    this->savemap(map);


}

void PhotoDV::draw_on_map(std::string name,const Point* point, const Point* camera)
{
    Point p = FixPoint()(point, camera);

    auto it = picres.find(name);

    if (it != picres.end())
    {
        putimage(p.first, p.second, this->picres[name]);
    }

    return;


}

PhotoDV::~PhotoDV()
{
    for (std::map<std::string, IMAGE*>::iterator it = picres.begin(); it != picres.end(); it++)
    {
        if (it->second != nullptr)
        {
            delete it->second;
            it->second = nullptr;
        }
    }
    picres.clear();
}