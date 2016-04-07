#include "widget.h"



Widget::Widget(QWidget *parent, logger *log_ptr) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    lockBool=false;
    if(log_ptr!=0)
    {
       loging=log_ptr;
    }
    else
    {
        loging = new logger();
    }
    if (QFile::exists(QDir::toNativeSeparators("./lockfile"))) {
        this->close();
    } else {
         QFile lock(QDir::toNativeSeparators("./lockfile"));
         lock.open(QIODevice::Append);
         lock.close();
         lockBool=true;
    }
    db=new sqlMan();
    fLoad=false;
    idLoaded=0;
    version=tr(VER_FILEVERSION_STR);
    loging->debugM("Initialize user interface");
    ui->setupUi(this);
    dataManager* data=new dataManager();
    QString path=data->getPath()+"bal.ssff";
    loging->debugM(QString("Setting DataPath:%1").arg(data->getPath()));
    ui->currency->setText(data->GetCurrency());
    loging->debugM(QString("Setting Currency:%1").arg(data->GetCurrency()));
    loging->debugM("Processing balance");
    QFile file_bal(path);
    QTextStream in_bal(&file_bal);
    in_bal.setCodec("UTF-8");
    ui->balance->setNum(db->getBalance());
    loging->debugM("Done");
    ui->date->setDateTime(QDateTime::currentDateTime());
    this->setWindowTitle(tr("Snipe Studio Budget Manager"));
    ui->date->setDateTime(QDateTime::currentDateTime());
    loging->debugM("Activating Slots");
    connect(ui->about,SIGNAL(clicked()),this,SLOT(help()));
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(addOperation()));
    connect(ui->settings,SIGNAL(clicked()),this,SLOT(showSettings()));
    connect(ui->view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editTrigger(QModelIndex)));
    connect(ui->resetTime,SIGNAL(clicked(bool)),this,SLOT(resetTime()));
    loging->debugM("Done");
    loging->debugM("Activating shortcuts");
    keyEnter = new QShortcut(this);
    keyEnter->setKey(Qt::Key_Return);
    keyDelete=new QShortcut(this);
    keyDelete->setKey(Qt::Key_Delete);
    connect(keyEnter,SIGNAL(activated()),this,SLOT(addOperation()));
    connect(keyDelete,SIGNAL(activated()),this,SLOT(deleteEntry()));
    loging->debugM("Done");
    updateDatabase();
}

Widget::~Widget()
{

}

bool Widget::initDatabase(sqlMan* db)
{
  loging->debugM("Get into database initialization");
  QSqlTableModel* model=db->getModel();
  model->setTable("operations");
  if(db->dbIsOpen())
    {
      QMessageBox* dbOpenError=new QMessageBox(this);
      loging->errorM("Error in Db Loading. There are some shit happens during database loading");
      dbOpenError->warning(this, "Error in Db Loading", "There are some shit happens during database loading");
      dbOpenError->exec();
    }
  updateDatabase();
  loging->debugM("Database initialized succesfully");
}

void Widget::help()
{
    loging->debugM("About message called");
    QMessageBox* helpMb=new QMessageBox(this);
    helpMb->about(this,tr("About SSBM"),tr("Snipe Studio Budget Manager v.%1\nUsing QT5\n%2\n%3").arg(this->version).arg(VER_LEGALCOPYRIGHT_STR).arg(VER_LEGALTRADEMARKS1_STR));
    helpMb->close();
}


void Widget::addOperation()
{
    loging->debugM("AddOperatuion called");
    QString commentText=ui->comment->text();
    const QChar delimiter=(uchar)'.';
    bool summDigits=true;
    if(!ui->sum->text().isEmpty())
      {
      for(int i=0;i<ui->sum->text().length();i++)
      {
        if(!ui->sum->text().at(i).isDigit()&&!(ui->sum->text().at(i)=='.')&&!(ui->sum->text().at(i)==','))
          {
           summDigits=false;
           }
        if((ui->sum->text().at(i)=='.')||(ui->sum->text().at(i)==','))
          {
           ui->sum->setText(ui->sum->text().replace(i,1,delimiter));
           }
        }
      }
    if((commentText.isEmpty()&&ui->sum->text().isEmpty())||!summDigits)
      {
        loging->warningM("Invalid summ value or comment text has been entered");
        loging->warningM("Comment Text:" + commentText);
        loging->warningM("Value:" + ui->sum->text());
        QMessageBox* a=new QMessageBox(this);
        a->setText("Invalid summ value");
        a->show();
        return;
      }
    if(commentText.isEmpty())
        commentText=tr("Default");
    QString data=ui->date->text();
    if(!ui->sum->text().isEmpty())
    {
        bool side=false;
        double summ=ui->sum->text().toDouble();
        if(ui->profit->isChecked())
        {
           side=true;
        }
        else
        {
            side=false;
        }
        idLoaded++;
        if(!side)
        {
            summ*=-1;
        }
        QDateTime time=ui->date->dateTime();
        db->dbIsOpen();
        db->addOperation(db,summ,commentText,side,time);
        this->ui->sum->clear();
        this->updateDatabase();

    }
}

void Widget::load()
{
    loging->debugM("load called");
    QTranslator translator;
    dataManager* data=new dataManager();
    translator.load(QDir::toNativeSeparators("translation/ssbm_"+data->getTranslation()+".qm"));
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
    delete data;
}


void Widget::showSettings()
{
    loging->debugM("showSettings called");
    //db->init();
    set=new settings(this,loging,db);
    connect(set,SIGNAL(finished(int)),this,SLOT(updateDatabase()));
    set->show();
}

void Widget::closeSettings()
{
    loging->debugM("closeSettings called");

    delete set;
}

void Widget::editTrigger(QModelIndex index)
{
    QVector<QString> data;
    int col_count=ui->view->model()->columnCount();

    for(int i = 0 ; i<col_count;i++)
   {
        data.push_back(ui->view->model()->index(index.row(),i).data().toString());
    }
    editdialog = new editentry(this,loging,&data,db);
    connect(editdialog,SIGNAL(finished(int)),this,SLOT(updateDatabase()));
    editdialog->show();
}

void Widget::updateDatabase()
{
    QSqlTableModel* model=db->getModel();
    ui->view->setModel(model);
    ui->view->hideColumn(0);
    ui->view->hideColumn(4);
    ui->view->hideColumn(5);
    ui->view->resizeColumnsToContents();
    ui->view->sortByColumn(0,Qt::DescendingOrder);
    ui->view->sortByColumn(0,Qt::DescendingOrder);
    ui->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->view->horizontalHeader()->setStretchLastSection(true);
    ui->view->show();
    ui->view->selectRow(0);

    ui->balance->setText(QString::number(db->getBalance(),'f',2));
    QPalette* palette = new QPalette();
    if(db->getBalance()>=0)
    {
        palette->setColor(QPalette::WindowText,Qt::black);
    }
    else
    {
        palette->setColor(QPalette::WindowText,Qt::red);
    }

    ui->balance->setPalette(*palette);
}

void Widget::resetTime()
{
    ui->date->setDateTime(QDateTime::currentDateTime());
}

void Widget::deleteEntry()
{
    int selectedIndex = ui->view->model()->index(ui->view->currentIndex().row(),0).data().toInt();
    db->deleteOperation(selectedIndex);
    updateDatabase();
}

void Widget::closeEvent(QCloseEvent *event)
{
    if(lockBool)
    {
        QFile::remove(QDir::toNativeSeparators("./lockfile"));
    }
    loging->infoM(QString("Deinitialization of %1").arg(VER_PRODUCTNAME_STR));
    loging->debugM("Closing SSBM");
    delete ui;
    delete loging;
}
