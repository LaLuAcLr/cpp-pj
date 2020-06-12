#include "Farm.h"

Farm::Farm(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(1140, 680);
    init_farm();
}

void Farm::init_farm()
{
    Day = 1;
    init_fruit();
    init_sp();
    init_pickhead();
    init_rod();

    MainLayout = new QHBoxLayout(this);
    MainLayout->setContentsMargins(0, 0, 0, 0);
    MainLayout->setSpacing(0);

    init_mapWidget();
    init_infowidget();

    MainLayout->addWidget(mapWidget);
    MainLayout->addWidget(infoWidget);

    MapLayout = new QGridLayout(mapWidget);
    MapLayout->setContentsMargins(0, 0, 0, 0);
    MapLayout->setSpacing(1);

    sound=new QMediaPlayer(this);//背景音乐
    sound->setMedia(QUrl("qrc:/bgm/addaday.mp3"));
    sound->setVolume(100);

    init_map();
    init_Character();
    init_store();
    init_dialogue();
    init_GetitemWin();
}

QJsonObject read_item(const QString & item_file) {
    QFile file(item_file);
    if(!file.open(QIODevice::ReadOnly))
        qDebug() << "read json file failed";
    QByteArray ba = file.readAll();
    QJsonParseError e;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(ba, &e);
    file.close();
    return jsonDoc.object();
}

void Farm::init_fruit()
{
    QJsonObject fruit = read_item(":/save.json").value("vegetable").toObject();
    QStringList keys = fruit.keys();
    foreach(QString key, keys)
    {
        QHash<QString, int> t;
        QJsonObject subobj = fruit.value(key).toObject();
        t.insert("value", subobj["value"].toInt());
        t.insert("seed_price", subobj["seed_price"].toInt());
        QJsonObject days = subobj["days"].toObject();
        t.insert("ripe_day", days["ripe"].toInt());
        t.insert("big_grass_day", days["big_grass"].toInt());
        t.insert("small_grass_day", days["small_grass"].toInt());
        fruit_list.insert(key, t);
    }
    m.initialseed(keys);
}
void Farm::init_pickhead()
{
    QJsonObject pick = read_item(":/save.json").value("pickhead").toObject();
    QStringList keys = pick.keys();
    foreach(QString key, keys)
    {
        QJsonObject subobj = pick.value(key).toObject();
        pickhead_list.insert(key, subobj["price"].toInt());
    }
}

void Farm::init_sp()
{
    QJsonObject sp = read_item(":/save.json").value("sp").toObject();
    QStringList keys = sp.keys();
    foreach(QString key, keys)
    {
        QJsonObject subobj = sp.value(key).toObject();
        sp_list.insert(key, subobj["price"].toInt());
    }
}

void Farm::init_rod()
{
    QJsonObject rod = read_item(":/save.json").value("rod").toObject();
    QStringList keys = rod.keys();
    foreach(QString key, keys)
    {
        QJsonObject subobj = rod.value(key).toObject();
        rod_list.insert(key, subobj["price"].toInt());
    }
}

void Farm::init_mapWidget()
{
    mapWidget = new QWidget();
    mapWidget->setMinimumSize(840, 680);
    QPixmap farm_img = QPixmap(m.MapFloor[m.floor]).scaled(mapWidget->size());
    QPalette pal(mapWidget->palette());
    pal.setBrush(QPalette::Background, QBrush(farm_img));
    mapWidget->setPalette(pal);
    mapWidget->setAutoFillBackground(true);
}

void Farm::init_store()
{
    Store=new StoreWidget(this);
    set_store_veg();
    Store->setGeometry(292,50,350,700);
    Store->hide();
}
void Farm::set_store_veg()
{
    if (m.floor != 0) return;
    int n = fruit_list.size();
    QStringList keys = fruit_list.keys();
    QVector<int> price;
    for (int i=0; i<n; ++i)
    {
        price.push_back(fruit_list[keys[i]]["seed_price"]);
        keys[i] += " seed";
        keys[i] = "buy " + keys[i];
    }
    Store->set_store(keys, price);
}
void Farm::set_store_pickhead()
{
    if (m.floor != 1) return;
    int n = pickhead_list.size();
    QStringList keys = pickhead_list.keys();
    QVector<int> price;
    for (int i=0; i<n; ++i)
    {
        price.push_back(pickhead_list[keys[i]]);
        keys[i] = "upgrade to " + keys[i] + " pick";
    }
    QStringList wanted_keys;
    QVector<int> wanted_price;
    if (m.role.item.tool["Pickhead"] == 3)
    {
        wanted_keys += "You have the best pick";
        wanted_price.push_back(0);
    }
    else {
        wanted_keys += keys[2-m.role.item.tool["Pickhead"]];     // Good, Better, Best
        wanted_price.push_back(price[2-m.role.item.tool["Pickhead"]]);
    }
    n = sp_list.size();
    QStringList new_keys = sp_list.keys();
    for (int i=0; i<n; ++i)
    {
        price.push_back(sp_list[new_keys[i]]);
        new_keys[i] = "buy " + new_keys[i];
    }
    int t[4] = {1, 3, 0, 2};    // jewel, spoon, jade, ring
    if (m.role.item.sp == 4)
    {
        wanted_keys += "You've got everything";
        wanted_price.push_back(0);
    }
    else {
        wanted_keys += new_keys[t[m.role.item.sp]];
        wanted_price.push_back(price[t[m.role.item.sp]]);
    }
    Store->set_store(wanted_keys, wanted_price);
}
void Farm::set_store_rod()
{
    if (m.floor != 3) return;
    int n = rod_list.size();
    QStringList keys = rod_list.keys();
    QVector<int> price;
    for (int i=0; i<n; ++i)
    {
        price.push_back(rod_list[keys[i]]);
        keys[i] = "upgrade to " + keys[i] + " rod";
    }
    QStringList wanted_keys;
    QVector<int> wanted_price;
    if (m.role.item.tool["Rod"] == 3)
    {
        wanted_keys += "You have the best rod";
        wanted_price.push_back(0);
    }
    else {
        wanted_keys += keys[2-m.role.item.tool["Rod"]];     // Good, Better, Best
        wanted_price.push_back(price[2-m.role.item.tool["Rod"]]);
    }
    Store->set_store(wanted_keys, wanted_price);
}
void Farm::set_princess()
{
    m.map[7][12][12] = 24 + m.role.item.sp;
    set_message("You give the princess a gift");
    start_msgtimer();
    qDebug()<<m.map[7][12][12]<<"princess";
    win();
}
void Farm::win()
{
    if (m.map[7][12][12] == 28) // win
    {
        m.map[7][12][12] = 1;
        set_message("You Win! Play more or Quit");
        start_msgtimer();
        m.map[5][11][11] = 27;
    }
}
void Farm::init_dialogue()
{
    dialogue=new Dialogue(this);
    dialogue->setGeometry(30,450,780,352);
    dialogue->hide();
}
void Farm::init_GetitemWin()
{
    GetitemTimer=new QTimer(this);
    connect(GetitemTimer,SIGNAL(timeout()),this,SLOT(GetitemWinshow()));
    GetitemNum = 0;
    //显示获得物品信息
    GetitemsShow=new QLabel(this);
    GetitemsShow->setGeometry(20,310,800,100);//居中
    GetitemsShow->setStyleSheet("color:white;background-color:black;");
    GetitemsShow->setAlignment(Qt::AlignCenter);
    QFont font("Consolas" ,12, 75);
    GetitemsShow->setFont(font);
    GetitemsShow->hide();
}
void Farm::init_map()
{
    int i, j;
    for (i=0;i<17;++i)
    {
        for (j=0;j<15;++j)
        {
            map[i][j] = new QLabel();
            map[i][j]->setAlignment(Qt::AlignCenter);
            map[i][j]->setFixedSize(56, 40);

            if(m.map[m.floor][i][j]>=10&&m.map[m.floor][i][j]<20)
                map[i][j]->setStyleSheet(m.TerrainString[m.map[m.floor][i][j]-10]);
            else if(m.map[m.floor][i][j]>=20&&m.map[m.floor][i][j]<30)
            {
                QPixmap t = QPixmap(m.NPC_pic[m.map[m.floor][i][j]-20][0]).scaled(56, 40, Qt::KeepAspectRatio);
                map[i][j]->setPixmap(t);
            }
            else if(m.map[m.floor][i][j]>=50)
            {
                QPixmap t = QPixmap(":/now/portal1.png").scaled(28, 40, Qt::KeepAspectRatio);
                map[i][j]->setPixmap(t);
            }
            MapLayout->addWidget(map[i][j],i,j);
        }
    }
    for (i=0;i<10;++i)
    {
        for (j=0;j<10;++j)
        {
            field[i][j] = new Field();
            field[i][j]->setFixedSize(56, 40);
            veg[i][j] = new Veg();
            veg[i][j]->setFixedSize(56, 40);
            if (m.map[m.floor][i+4][j+4] == 2)
            {
                MapLayout->addWidget(field[i][j], i+4, j+4);
                MapLayout->addWidget(veg[i][j], i+4, j+4);
                connect(add_day, SIGNAL(clicked()), this, SLOT(update_veg()));
            }
        }
    }
}

void Farm::reset_field(QJsonArray json_field)
{
    for (auto i=0;i<10;++i)
    {
        for (auto j=0;j<10;++j)
        {
            field[i][j]->set_status(json_field[i].toArray()[j].toInt());
            field[i][j]->set_bg();
        }
    }
}
void Farm::reset_veg(QJsonArray json_veg)
{
    for (auto i=0;i<10;++i)
    {
        for (auto j=0;j<10;++j)
        {
            auto tmp_name = json_veg[i].toArray()[j].toObject()["name"].toString();
            auto tmp_plant_day = json_veg[i].toArray()[j].toObject()["plant_day"].toInt();
            if (tmp_plant_day == -1) continue;
            veg[i][j]->refresh(tmp_name,tmp_plant_day, fruit_list[tmp_name]["small_grass_day"], fruit_list[tmp_name]["big_grass_day"], fruit_list[tmp_name]["ripe_day"]);
            veg[i][j]->update_pic(Day);
        }
    }
}
void Farm::reset_day(int json_day)
{
    Day = json_day;
    QString day_string = QString::number(Day);
    label_day->setText("This is Day " + day_string);
    regenerate_Info();
}
void Farm::change_dic(int n, int x, int y)
{
    map[x][y]->hide();
    QPixmap t = QPixmap(m.NPC_pic[m.map[m.floor][x][y]-20][n]).scaled(56, 40, Qt::KeepAspectRatio);
    map[x][y]->setPixmap(t);
    map[x][y]->show();
}
void Farm::GetitemWinshow()
{
    if(GetitemNum==0)
    {
        GetitemsShow->setText(get_message());
        GetitemsShow->show();
        GetitemNum++;
    }
    else if(GetitemNum<=10)//控制显示时间
    {
        GetitemNum++;
    }
    else
    {
        GetitemNum=0;
        GetitemTimer->stop();
        GetitemsShow->hide();
    }
}
void Farm::update_veg()
{
    for (int i=0;i<10;++i)
    {
        for (int j=0;j<10;++j)
        {
            bool flg;
            flg = veg[i][j]->update_pic(this->Day);
            if (flg)
            {
                field[i][j]->set_status(3);
                field[i][j]->set_bg();
            }
        }
    }

}
void Farm::init_Character()
{
    Character = new character(mapWidget);
    Character->move(m.y*56, m.x*40);
}
void Farm::regenarate_Character()
{
    Character->move(m.y*56, m.x*40);
    Character->raise();
}
void Farm::restart_Character()
{
    Character->move(1*56, 3*40);
    Character->turn_direction(1);
    Character->raise();
}
void Farm::restart_farm()
{
    Day = 1;
    init_sp();
    init_rod();
    init_fruit();
    init_pickhead();
    m.restart();
    //init_store();
    restart_field();
    regenarate_Map();
    regenerate_Info();
    restart_Character();
}
void Farm::restart_field()
{
    for(int i=0; i<10; ++i)
    {
        for(int j=0; j<10; ++j)
        {
            field[i][j]->restart();
            veg[i][j]->restart();
        }
    }
}
void Farm::refresh_Character_Load(QJsonObject role)
{
    m.x = role.value("pos_x").toInt();
    m.y = role.value("pos_y").toInt();
    m.floor = role.value("floor").toInt();
    regenarate_Map();
    Character->move(m.y*56, m.x*40);
    Character->turn_direction(1);
}
void Farm::regenarate_Map()
{
    mapWidget->hide();
    QPixmap farm_img = QPixmap(m.MapFloor[m.floor]).scaled(mapWidget->size());
    QPalette pal(mapWidget->palette());
    pal.setBrush(QPalette::Background, QBrush(farm_img));
    mapWidget->setPalette(pal);
    mapWidget->setAutoFillBackground(true);
    mapWidget->show();
    int i, j;
    for (i=0;i<17;++i)
    {
        for (j=0;j<15;++j)
        {
            map[i][j]->hide();
        }
    }
    for (i=0;i<17;++i)
    {
        for (j=0;j<15;++j)
        {
            map[i][j] = new QLabel();
            map[i][j]->setAlignment(Qt::AlignCenter);
            map[i][j]->setFixedSize(56, 40);

            if(m.map[m.floor][i][j]>=10&&m.map[m.floor][i][j]<20)
                map[i][j]->setStyleSheet(m.TerrainString[m.map[m.floor][i][j]-10]);
            else if(m.map[m.floor][i][j]>=20&&m.map[m.floor][i][j]<30)
            {
                QPixmap t = QPixmap(m.NPC_pic[m.map[m.floor][i][j]-20][0]).scaled(56, 40, Qt::KeepAspectRatio);
                map[i][j]->setPixmap(t);
            }
            else if(m.map[m.floor][i][j]>=50)
            {
                QPixmap t = QPixmap(":/now/portal1.png").scaled(28, 40, Qt::KeepAspectRatio);
                map[i][j]->setPixmap(t);
            }
            MapLayout->addWidget(map[i][j],i,j);
        }
    }
    if (m.floor==0) show_field();
    else hide_field();
    regenarate_Character();
}
void Farm::interact_field(int i, int j)
{
    auto field_status = field[i][j]->get_status();
    auto tool = m.role.tool.name;
    auto seed = m.role.seed;
    auto isRipe = veg[i][j]->get_isRipe();
    if (m.role.stamina == 0) return;
    if (field_status == 0)     // orig
    {
        if (tool == QString("Hoe")) {
            //cout << "清除杂草" << endl;
            field[i][j]->set_status(1);
            field[i][j]->set_bg();
            m.role.stamina -= 5;
            regenerate_Info();
            sound->stop();
            sound->setMedia(QUrl("qrc:/bgm/farm1.mp3"));
            sound->play();
        }
    }
    if (field_status == 1)     // hoed
    {
        if (tool == QString("Seed") && m.role.seed != "") {
            //cout << "种菜" << endl;
            field[i][j]->set_status(2);
            field[i][j]->set_bg();
            veg[i][j]->refresh(seed, this->Day, fruit_list[seed]["small_grass_day"], fruit_list[seed]["big_grass_day"], fruit_list[seed]["ripe_day"]);
            m.role.stamina -= 5;
            m.role.item.seed[seed]--;
            remove_seed();
            regenerate_Info();
            sound->stop();
            sound->setMedia(QUrl("qrc:/bgm/farm2.mp3"));
            sound->play();
        }
    }
    if (isRipe) // ripe
    {
        if (tool == QString("Knife")) {
            QString msg = QString("You've got one ") + veg[i][j]->get_name().toLower();
            set_message(msg);
            start_msgtimer();
            m.role.money += fruit_list[veg[i][j]->get_name()]["value"];
            m.role.stamina -= 5;
            regenerate_Info();
            field[i][j]->set_status(0);
            field[i][j]->set_bg();
            veg[i][j]->restart();
            check_money();
            sound->stop();
            sound->setMedia(QUrl("qrc:/bgm/farm3.mp3"));
            sound->play();
        }
    }
    check_stamina();
}
void Farm::check_stamina()
{
    if(m.role.stamina == 0) {
        set_message("You are too tired to work!");
        start_msgtimer();
    }
}
void Farm::check_money()
{
    if (m.role.money <= 0) {
        set_message("You are out of money!");
        start_msgtimer();
        Store->setChooseEnable = false;
    }
    else
        Store->setChooseEnable = true;
}
void Farm::out_of_money()
{
    set_message("You are out of money!");
    start_msgtimer();
}
void Farm::show_field()
{
    int i, j;
    for (i=0;i<10;++i)
    {
        for (j=0;j<10;++j)
        {
            veg[i][j]->show();
            field[i][j]->show();
        }
    }
}
void Farm::hide_field()
{
    int i, j;
    for (i=0;i<10;++i)
    {
        for (j=0;j<10;++j)
        {
            veg[i][j]->hide();
            field[i][j]->hide();
        }
    }
}
void Farm::add_day_func()
{
    if(m.map[m.floor][m.x][m.y]==0)
    {
        Day++;
        m.role.stamina = 100;
        regenerate_Info();
        sound->stop();
        sound->setMedia(QUrl("qrc:/bgm/addaday.mp3"));
        sound->play();
    }
    else
    {
        set_message("You can't sleep outside your room");
        start_msgtimer();
    }
}
void Farm::change_tool(QString t)
{
    qDebug()<<t;
    if (!dialogue->isHidden()) dialogue->setFocus();
    else if (!Store->isHidden()) Store->setFocus();
    else this->setFocus();
    m.role.tool.name = t;
    m.role.tool.level = m.role.item.tool[t];
}
void Farm::change_seed(QString t)
{
    qDebug()<<t;
    if (!dialogue->isHidden()) dialogue->setFocus();
    else if (!Store->isHidden()) Store->setFocus();
    else this->setFocus();
    m.role.seed = t;
}
void Farm::add_seed()
{
    QStringList keys = m.role.item.seed.keys();
    foreach (auto key, keys)
        if (m.role.item.seed[key] != 0 && seed->findText(key) == -1)
            seed->addItem(key);
}
void Farm::remove_seed()
{
    QStringList keys = m.role.item.seed.keys();
    int t;
    foreach (auto key, keys)
        if (m.role.item.seed[key] == 0 && (t=seed->findText(key)) != -1)
            seed->removeItem(t);
}
void Farm::init_infowidget()
{
    infoWidget = new QWidget(this);
    QFont fontLabel("Consolas", 12);
    QFont fontNum("Consolas", 10);
    QFont fontName("Consolas", 10);
    QString button_style="QPushButton{border-image:url(:/now/labelbg.png);color:white;border-radius:10px;}"
                         "QPushButton:hover{border-image:url(:/now/PushButtonhoverbg.png); color: black;}"
                         "QPushButton:pressed{border-image:url(:/now/PushButtonPressbg.png);}";

    avatar = new QLabel(infoWidget);
    avatar->setStyleSheet("border-image:url(:/now/man.png);");
    avatar->setGeometry(20, 20, 40, 40);

    name = new QLabel(infoWidget);
    name->setFont(fontName);
    name->setText(m.role.name);
    name->setStyleSheet("border-image: url(:/now/labelbg.png);");
    name->setGeometry(150, 30, 100, 40);

    label_stamina = new QLabel(infoWidget);
    label_stamina->setFont(fontLabel);
    label_stamina->setText("Stamina:");
    label_stamina->setStyleSheet("border-image: url(:/now/labelbg.png);");
    label_stamina->setGeometry(20, 70, 100, 40);

    label_money = new QLabel(infoWidget);
    label_money->setFont(fontLabel);
    label_money->setText("Money:");
    label_money->setStyleSheet("border-image: url(:/now/labelbg.png);");
    label_money->setGeometry(20, 110, 100, 40);

    label_tool = new QLabel(infoWidget);
    label_tool->setFont(fontLabel);
    label_tool->setText("Tool:");
    label_tool->setStyleSheet("border-image: url(:/now/labelbg.png);");
    label_tool->setGeometry(20, 150, 100, 40);

    label_seed = new QLabel(infoWidget);
    label_seed->setFont(fontLabel);
    label_seed->setText("Seed:");
    label_seed->setStyleSheet("border-image: url(:/now/labelbg.png);");
    label_seed->setGeometry(20, 190, 100, 40);

    stamina = new QLabel(infoWidget);
    stamina->setFont(fontNum);
    stamina->setStyleSheet("border-image: url(:/now/labelbg.png);");
    stamina->setText(QString::number(m.role.stamina));
    stamina->setGeometry(150, 70, 40, 40);

    money = new QLabel(infoWidget);
    money->setFont(fontNum);
    money->setStyleSheet("border-image: url(:/now/labelbg.png);");
    money->setText(QString::number(m.role.money));
    money->setGeometry(150, 110, 40, 40);

    tool = new QComboBox(infoWidget);
    tool->addItems(QStringList{"None", "Hoe", "Seed", "Knife", "Pickhead", "Rod"});
    tool->setStyleSheet("border-image: url(:/now/labelbg.png);");
    tool->setGeometry(150, 160, 100, 20);
    connect(tool, SIGNAL(currentTextChanged(QString)), this, SLOT(change_tool(QString)));

    seed = new QComboBox(infoWidget);
    seed->setStyleSheet("border-image: url(:/now/labelbg.png);");
    seed->setGeometry(150, 200, 100, 20);
    connect(seed, SIGNAL(currentTextChanged(QString)), this, SLOT(change_seed(QString)));

    label_day = new QLabel(infoWidget);
    label_day->setFont(fontLabel);
    label_day->setStyleSheet("border-image: url(:/now/labelbg.png);");
    QString day_string = QString::number(Day);
    label_day->setText("This is Day " + day_string);
    label_day->setGeometry(20, 450, 200, 40);

    add_day = new QPushButton(infoWidget);
    add_day->setText("Add a Day");
    add_day->setFont(fontLabel);
    add_day->setStyleSheet(button_style);
    add_day->setGeometry(20, 500, 100, 40);
    connect(add_day, SIGNAL(clicked()), this, SLOT(add_day_func()));

    save = new QPushButton(infoWidget);
    save->setText("Save");
    save->setFont(fontLabel);
    save->setStyleSheet(button_style);
    save->setGeometry(20, 550, 100, 40);
    connect(save, SIGNAL(clicked()), this, SLOT(save_func()));

    mainmenu = new QPushButton(infoWidget);
    mainmenu->setText("MainMenu");
    mainmenu->setFont(fontLabel);
    mainmenu->setStyleSheet(button_style);
    mainmenu->setGeometry(20, 600, 100, 40);

    infoWidget->setMinimumSize(300,680);
    infoWidget->setStyleSheet("color:white; border-image: url(:/now/infobg.png);");
}
void Farm::regenerate_Info(){
    QFont fontNum("Consolas",10 );
    name->setText(m.role.name);
    stamina->setText(QString::number(m.role.stamina));
    money->setText(QString::number(m.role.money));
    QString day_string = QString::number(Day);
    label_day->setText("This is Day " + day_string);
}

void Farm::regenerate_Info_Load(QJsonObject role){
    m.role.name = role.value("name").toString();
    m.role.stamina = role.value("stamina").toInt();
    m.role.money = role.value("money").toInt();
    auto tmp_seed = role.value("item").toObject().value("seed").toObject();
    for (auto i = tmp_seed.begin();i != tmp_seed.end(); ++i) {
        m.role.item.seed[i.key()] = i.value().toInt();
        qDebug() << i.key() << i.value().toInt();
    }

    //test seed
    QStringList keys = m.role.item.seed.keys();
    foreach (auto key, keys)
        if (m.role.item.seed[key] != 0 && seed->findText(key) == -1)
            seed->addItem(key);
    // for tool
    /*
    auto tmp_tool = role.value("item").toObject().value("tool").toObject();
    for (auto i = tmp_tool.begin();i != tmp_tool.end(); ++i) {
        m.role.item.tool[i.key()] = i.value().toInt();
    }
    */
    m.role.item.sp = role.value("item").toObject().value("sp").toInt();
    QFont fontNum("Consolas",10 );
    name->setText(m.role.name);
    stamina->setText(QString::number(m.role.stamina));
    money->setText(QString::number(m.role.money));
}

void Farm::save_func() {
    qDebug() << "try to open file!";
    QFile save_js_file(QApplication::applicationDirPath() + "/json/save.json");
    if(!save_js_file.open(QIODevice::WriteOnly)) {
        qDebug() << "File open failed!";
    } else {
        qDebug() <<"File open successfully!";
    }

    QJsonDocument save_doc;
    QJsonObject save_obj;


    save_obj["days"] = Day;


    QJsonArray json_field;
    for(auto i = 0; i < 10; ++i)
    {
        QJsonArray field_rol;
        for(auto j = 0; j < 10; ++j) {
            field_rol.append(field[i][j]->get_status());
        }
        json_field.append(field_rol);
    }
    save_obj["field"] = json_field;

    QJsonArray json_veg;
    for(auto i = 0; i < 10; ++i)
    {
        QJsonArray veg_rol;
        for(auto j = 0; j < 10; ++j) {
            QJsonObject veg_status;
            veg_status["name"] = veg[i][j]->get_name();
            veg_status["plant_day"] = veg[i][j]->get_plant_day();
            veg_rol.append(veg_status);
        }
        json_veg.append(veg_rol);
    }
    save_obj["veg"] = json_veg;

    QJsonObject json_role;
    json_role["name"] = m.role.name;
    json_role["money"] = m.role.money;
    json_role["stamina"] = m.role.stamina;
    json_role["pos_x"] = m.x;
    json_role["pos_y"] = m.y;
    json_role["floor"] = m.floor;
    QJsonObject json_item;
    json_item["sp"] = m.role.item.sp;
    QJsonObject json_seed;
    for (auto i = m.role.item.seed.begin(); i != m.role.item.seed.end(); ++i) {
        json_seed[i.key()] = i.value();
    }
    json_item["seed"] = json_seed;
    QJsonObject json_tool;
    for (auto i = m.role.item.tool.begin(); i != m.role.item.tool.end(); ++i) {
        json_tool[i.key()] = i.value();
    }
    json_item["tool"] = json_tool;
    json_role["item"] = json_item;
    save_obj["role"] = json_role;


    save_doc.setObject(save_obj);
    save_js_file.write(save_doc.toJson(QJsonDocument::Indented));
    save_js_file.close();
}
