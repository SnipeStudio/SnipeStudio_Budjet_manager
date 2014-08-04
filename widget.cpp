#include "widget.h"



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
   sqlMan* db=new sqlMan("ssbm.db");
    fLoad=false;
    idLoaded=0;
    version=tr("14.06-pre(0.3.9.7)");
    ui->setupUi(this);
    int rowCount=0;
    std::ifstream balanceInput;
    dataManager* data=new dataManager();
    QString path=data->getPath()+"bal.ssff";
    ui->currency->setText(data->GetCurrency());
    QFile file_bal(path);
    QTextStream in_bal(&file_bal);
    in_bal.setCodec("UTF-8");
    ui->balance->setNum(db->getBalance());
    ui->date->setDateTime(QDateTime::currentDateTime());
    QString fileNameQ=tr("%3snipeStudio_%1.%2.csv").arg(QString::number(ui->date->date().month())).arg(QString::number(ui->date->date().year())).arg(data->getPath());
    qDebug() << fileNameQ;
    QFile file(fileNameQ);
    QString dataTe,commentTe,typeTe,summTe,balanceTe;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        in.setCodec(QTextCodec::codecForName("UTF-8"));
        QString line = in.readLine();
        QStringList result;
        while (!line.isNull())
        {
            line.remove(QRegExp("//[\\W\\w]{0,}"));
            result.append(line.split(QString(';')));
            qDebug()<<result.count();
            if(result.count()==6)
              {
            idLoaded=result.at(0).toLong();
            dataTe=result.at(1);
            commentTe=result.at(2);
            typeTe=result.at(3);
            summTe=result.at(4);
            balanceTe=result.at(5);
              }
            line = in.readLine();
            if(!dataTe.isEmpty())
            {
                rowCount++;
                result.clear();

            }

        }
        file.close();
    }
    monthSelected=ui->date->date().month();
    yearSelected=ui->date->date().year();
    ui->monthTitle->setText(ui->date->date().longMonthName(monthSelected));
    ui->yearLabel->setNum(yearSelected);

    this->setWindowTitle(tr("Snipe Studio Budget Manager"));
    ui->date->setDateTime(QDateTime::currentDateTime());
    connect(ui->about,SIGNAL(clicked()),this,SLOT(help()));
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(addOperation()));
    connect(ui->settings,SIGNAL(clicked()),this,SLOT(showSettings()));
    connect(ui->save,SIGNAL(clicked()),this,SLOT(save()));
    connect(ui->load,SIGNAL(clicked()),this,SLOT(load()));
    connect(ui->nextMonth,SIGNAL(clicked()),this,SLOT(NextMonth()));
    connect(ui->PreviousMonth,SIGNAL(clicked()),this,SLOT(PrevMonth()));
    ui->profit->setChecked(true);
    set=new settings(this);
    db->model=new QSqlTableModel(0,db->sdb);
    db->model->setTable("operations");

    if(!(db->model->select()))
    {
        qDebug()<<"ERROR!";
    }
    db->model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->view->setModel(db->model);
    ui->view->resizeColumnToContents(0);
    ui->view->resizeColumnToContents(5);
    ui->view->setColumnWidth(3,200);
    ui->view->hideColumn(0);
   // ui->view->hideRow(0);
    ui->view->sortByColumn(0,Qt::DescendingOrder);
    ui->view->show();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent*)
{
    set->window()->show();
    set->window()->close();

    dataManager* data=new dataManager();

    QString path=data->getPath()+"bal.ssff";
    QFile file_bal(path);
    QTextStream out_bal(&file_bal);
    out_bal.setCodec("UTF-8");
    if(file_bal.open(QIODevice::WriteOnly))
    {
        out_bal<<ui->balance->text().toDouble();
    }
    file_bal.close();
    QString fileNameQ=tr("%3snipeStudio_%1.%2.csv").arg(QString::number(ui->date->date().month())).arg(QString::number(ui->date->date().year())).arg(data->getPath());
    QFile file(fileNameQ);
    QTextStream out(&file);
    out.setCodec("UTF-8");
    if(file.open(QIODevice::WriteOnly))
    {
    }
    //delete set;
    set->close();
    delete data;
    file.close();
    close();
}

void Widget::help()
{
    QMessageBox* a=new QMessageBox(this);
    a->about(this,tr("About SSBM"),tr("Snipe Studio Budget Manager v.%1\nUsing QT5 in Ubuntu Linux\n2010-2014(ɔ)").arg(this->version));
    a->close();
}

void Widget::addOperation()
{
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
        QMessageBox* a=new QMessageBox(this);
        a->setText("Invalid summ value");
        a->show();
        return;
      }
    if(commentText.isEmpty())
        commentText=tr("Default");
    bool side=false;
    QString data=ui->date->text();

    if(!ui->sum->text().isEmpty())
    {
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
        qDebug()<<db->sdb.databaseName();
        db->addOperation(db,summ,commentText,side);
        ui->view->setModel(db->model);
        ui->view->hideColumn(0);
        ui->view->resizeColumnToContents(0);
        ui->view->resizeColumnToContents(5);
        ui->view->setColumnWidth(3,200);
        //ui->view->hideRow(0);
        ui->view->sortByColumn(0,Qt::DescendingOrder);
        ui->view->show();
        ui->balance->setNum(db->getBalance());

    }
}

void Widget::save()
{
    dataManager* data=new dataManager();

    QString path=data->getPath()+"bal.ssff";
    QFile file_bal(path);
    QTextStream out_bal(&file_bal);
    out_bal.setCodec("UTF-8");
    if(file_bal.open(QIODevice::WriteOnly))
    {
        out_bal<<ui->balance->text().toDouble();
    }
    file_bal.close();
    QString fileNameQ=tr("%3snipeStudio_%1.%2.csv").arg(QString::number(monthSelected)).arg(QString::number(ui->date->date().year())).arg(data->getPath());
    QFile file(fileNameQ);
    QTextStream out(&file);
    out.setCodec("UTF-8");
    ulong count=0;
    if(file.open(QIODevice::WriteOnly))
    {
    }
    file.close();
    QMessageBox* a=new QMessageBox(this);
    if(count!=0)
      {
        a->setText("All your data are saved");
      }
    else
      {
        a->setText("Nothing to be saved");
      }
    a->show();
}

void Widget::load()
{
    {

    fLoad=false;
    QPushButton* ok=new QPushButton(tr("&ok"));
    QPushButton* cancel=new QPushButton(tr("&cancel"));
    QMessageBox* load=new QMessageBox();
    load->setText(tr("Are you sure to force load. Data may be lost"));
    load->addButton(ok,QMessageBox::AcceptRole);
    load->addButton(cancel,QMessageBox::RejectRole);
    connect(load,SIGNAL(accepted()),this,SLOT(updLoad(true);));
    connect(load,SIGNAL(rejected()),this,SLOT(updLoad(false);));
    load->show();
    if(fLoad==true)
      {
        dataManager* data=new dataManager();
        QString path=data->getPath()+"bal.ssff";
        ui->currency->setText(data->GetCurrency());
        ui->yearLabel->setNum(yearSelected);
        QFile file_bal(path);
        QTextStream in_bal(&file_bal);
        in_bal.setCodec("UTF-8");
        double balance;

        if(file_bal.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString line = in_bal.readLine();
            qDebug()<<line;
            balance=line.toDouble();

            file_bal.close();
        }
        else
        {
            balance=0;
        }
        db->getBalance();
        ui->balance->setNum(balance);
        ui->date->setDateTime(QDateTime::currentDateTime());
        QString fileNameQ=tr("%3snipeStudio_%1.%2.csv").arg(QString::number(monthSelected)).arg(QString::number(yearSelected)).arg(data->getPath());
        qDebug() << fileNameQ;
        QFile file(fileNameQ);

        QString dataTe,commentTe,typeTe,summTe,balanceTe,idTe;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            file.close();
        }

        ui->balance->setNum(balance);
        ui->currency->setText(data->GetCurrency());
        delete data;
      }
    }
}

void Widget::NextMonth()
{
  monthSelected++;
  if(monthSelected>12)
    {
      monthSelected=1;
      yearSelected++;
    }
  ui->monthTitle->setText(ui->date->date().longMonthName(monthSelected));
  qDebug()<<monthSelected<<" "<<yearSelected;
  this->load();
}
void Widget::PrevMonth()
{
  monthSelected--;
  if(monthSelected<1)
    {
      monthSelected=12;
      yearSelected--;
    }
  ui->monthTitle->setText(ui->date->date().longMonthName(monthSelected));
  qDebug()<<monthSelected<<" "<<yearSelected;
  this->load();
}

void Widget::showSettings()
{
  set->show();
}
void Widget::updLoad(bool load)
{
  fLoad=load;
}
