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
    Store->setGeometry(292,50,300,700);
    Store->hide();
}
void Farm::set_store_veg()
{
    if (m.floor != 0) return;
    int n = fruit_list.size();
    qDebug()<<"fruit_list_size="<<n;
    QStringList keys = fruit_list.keys();
    QVector<int> price;
    for (int i=0; i<n; ++i)
    {
        price.push_back(fruit_list[keys[i]]["seed_price"]);
        keys[i] += " seed";
    }
    Store->set_store(keys, price);
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
void Farm::refresh_Character()
{
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
        }
    }
    if (field_status == 1)     // hoed
    {
        if (tool == QString("Seed")) {
            //cout << "种菜" << endl;
            field[i][j]->set_status(2);
            field[i][j]->set_bg();
            veg[i][j]->refresh(seed, this->Day, fruit_list[seed]["small_grass_day"], fruit_list[seed]["big_grass_day"], fruit_list[seed]["ripe_day"]);
            m.role.stamina -= 5;
            m.role.item.seed[seed]--;
            remove_seed();
            regenerate_Info();
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
    Day++;
    QString day_string = QString::number(Day);
    label_day->setText("This is Day " + day_string);
    m.role.stamina = 100;
    regenerate_Info();
}
void Farm::change_tool(QString t)
{
    qDebug()<<t;
    m.role.tool.name = t;
    this->parentWidget()->setFocus();
}
void Farm::change_seed(QString t)
{
    qDebug()<<t;
    m.role.seed = t;
    this->setFocus();
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
    tool->addItems(QStringList{"None", "Hoe", "Seed", "Knife"});
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
    label_day->setGeometry(20, 400, 200, 40);

    add_day = new QPushButton(infoWidget);
    add_day->setText("Add a Day");
    add_day->setStyleSheet(button_style);
    add_day->setGeometry(20, 450, 100, 40);
    connect(add_day, SIGNAL(clicked()), this, SLOT(add_day_func()));

    save = new QPushButton(infoWidget);
    save->setText("Save");
    save->setStyleSheet(button_style);
    save->setGeometry(20, 500, 100, 40);

    load = new QPushButton(infoWidget);
    load->setText("Load");
    load->setStyleSheet(button_style);
    load->setGeometry(20, 550, 100, 40);

    mainmenu = new QPushButton(infoWidget);
    mainmenu->setText("MainMenu");
    mainmenu->setStyleSheet(button_style);
    mainmenu->setGeometry(20, 600, 100, 40);

    infoWidget->setMinimumSize(300,680);
    infoWidget->setStyleSheet("color:white; border-image: url(:/now/infobg.png);");
}
void Farm::regenerate_Info(){
    QFont fontNum("Consolas",10 );
    stamina->setText(QString::number(m.role.stamina));
    money->setText(QString::number(m.role.money));
}

