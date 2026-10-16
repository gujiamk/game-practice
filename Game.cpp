#include "Game.h"

Game::Game()
{
    this->map = std::vector<std::vector<int>>(stepx, std::vector<int>(stepy, 0));
    this->camera = new Point(0, 0);

    this->login();

    if (!this->loadgame()) exit(0);
}

Game::Game(const Game& Game)
{
    this->player = new Chara(*Game.player);
    this->camera = new Point(*Game.camera);
    this->isnewone = Game.isnewone;
}

Game::~Game()
{
    if (this->player != nullptr)
    {
        delete this->player;
        this->player = nullptr;
    }

    if (this->camera != nullptr)
    {
        delete this->camera;
        this->camera = nullptr;
    }
}

Game& Game::operator=(const Game& game)
{
    if(this->player != nullptr) delete this->player;
    this->player = new Chara(*game.player);

    this->camera = new Point(game.camera->first, game.camera->second);
    this->isnewone = game.isnewone;

    return *this;
}

Game* getGame()
{
    return new Game();
}

void Game::create_chara()
{
    std::string name;
    std::cout << "正在创建角色请输入角色名称：";
    std::cin >> name;

    std::ofstream ofs(Chara_info, std::ios::out|std::ios::app);

    if (!ofs.is_open())
    {
        std::cout<<"无法打开相关文件，正在搜索相关文件！"<<std::endl;
        std::ifstream ifs(maproad, std::ios::in);
        if (!ifs.is_open())
        {
            std::cout<<"未找到角色档案文件，并检测到重要地图文件已经丢失，请检查资源完整性！"<<std::endl;
            exit(0);
        }
        std::cout<<"unknow erra!"<<std::endl;
        exit(0);
    }

    ofs << name << " " << "12 10 100 10 2\n";
    ofs.close();
    std::cout << "角色创建成功！" << std::endl;
    this->player = new Chara();

    return;
}

void Game::login()
{
    std::ifstream ifs(Chara_info, std::ios::in);
    if (!ifs.is_open())
    {
        std::cout << "未找到角色档案文件，正在创建角色档案文件！" << std::endl;
        this->create_chara();
        this->isnewone = true;
        ifs.close();
    }
    else
    {
        std::string name;
        Point point;
        int health;
        int attack;
        int defense;

        ifs >> name >> point.first >> point.second >> health >> attack >> defense;

        this->player = new Chara(name, point, health, attack, defense);
        ifs.close();
        this->isnewone = false;

        std::cout << "登录成功！" << std::endl;
    }
}

void Game::welconme()
{
    std::string word1 = "欢迎游玩0.1版本目前仅完成了地图和存档和交互功能";
    std::string word2 = "遗憾的是，我们并未创建npc所以目前交互功能还不能体验";
    std::string word3 = "你现在可以自由探索这个世界(按住键盘的上下左右可以进行移动，ESC键即可退出游戏)";
    std::string word4 = "请按空格键开始游戏";
    print_word(word1, 0, 0, 40);
    print_word(word2, 0, 60, 40);
    print_word(word3, 0, 120, 40);
    print_word(word4, 0, 180, 40);

    flushmessage();
    ExMessage msg{ 0 };
    while (msg.vkcode != VK_SPACE)
    {
        getmessage(&msg, EX_KEY);
    }
    this->isnewone = false;

}

bool Game::loadgame()
{
    std::ifstream ifs;
    ifs.open(maproad, std::ios::in);

    if (!ifs.is_open())
    {
        std::cout << "载入地图失败" << std::endl;
        return false;
    }

    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            ifs >> this->map[i][j];
        }
    }
    ifs.close();

    ifs.open(Game_info, std::ios::in);
    if (!ifs.is_open())
    {
        std::cout << "载入游戏信息失败" << std::endl;
        return false;
    }
    ifs>>this->camera->first>>this->camera->second;
    ifs.close();


    std::cout << "载入游戏信息成功" << std::endl;
    return true;
}

void Game::savegame()
{
    std::ofstream ofs(Game_info, std::ios::out|std::ios::trunc);
    if (!ofs.is_open())
    {
        std::cout << "保存游戏信息失败" << std::endl;
        return;
    }
    ofs << this->camera->first << " " << this->camera->second << std::endl;
    ofs.close();

    ofs.open(Chara_info, std::ios::out|std::ios::trunc);
    if (!ofs.is_open())
    {
        std::cout << "保存角色信息失败" << std::endl;
        return;
    }
    ofs << this->player;
    ofs.close();
    std::cout << "保存游戏信息成功" << std::endl;
}

void Game::run()
{
    initgraph(WIDTH, HEIGHT, SHOWCONSOLE);
    bool is=this->isnewone;
    if (this->isnewone)
    {
        this->welconme();
    }

    flushmessage();
    setfillcolor(BLACK);
    setlinecolor(WHITE);

    cleardevice();

    ExMessage msg{ 0 };
    std::string name;

    BeginBatchDraw();

    while (msg.vkcode != VK_ESCAPE)
    {
        cleardevice();

        for (int i = camera->first; i < camera->first + 25; i++)
        {
            for (int j = camera->second; j < camera->second + 20; j++)
            {
                if (this->map[i][j] == GRASS)
                {
                    (*picdv)("grass", this->camera, i, j);
                }
                else if (this->map[i][j] == TREE)
                {
                    (*picdv)("tree", this->camera, i, j);
                }
                else if (this->map[i][j] == HUOSE)
                {
                    (*picdv)("house", this->camera, i, j);
                }
                else if (this->map[i][j] == ROAD)
                {
                    (*picdv)("cityroad", this->camera, i, j);
                }
                else if (this->map[i][j] == SS)
                {
                    (*picdv)("ss", this->camera, i, j);
                }
            }
        }
        this->player->draw_self(this->camera);
        FlushBatchDraw();

        getmessage(&msg, EX_KEY | EX_MOUSE);
        if (msg.message == WM_KEYDOWN)
        {
            switch (msg.vkcode)
            {
            case VK_LEFT:
                this->player->move(map, this->camera, VK_LEFT);
                break;
            case VK_RIGHT:
                this->player->move(map, this->camera, VK_RIGHT);
                break;
            case VK_UP:
                this->player->move(map, this->camera, VK_UP);
                break;
            case VK_DOWN:
                this->player->move(map,this->camera,VK_DOWN);
                break;
            case VK_TAB:
                
                break;
            case VK_ESCAPE:

                break;
            default:
                break;
            }

        }
        else if (msg.message == WM_LBUTTONDOWN)
        {
            int x = msg.x, y = msg.y;

            x = x / step;
            y = y / step;

            std::cout << "图片坐标:" << x << "|" << y << std::endl;

        }

    }
    EndBatchDraw();

    closegraph();

    this->savegame();
}