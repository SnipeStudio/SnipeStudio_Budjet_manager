#include "widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
<<<<<<< HEAD
    version=tr("14.04-beta(0.0.2.8)");
=======
    version=tr("14.05-beta(0.0.3.3)");
>>>>>>> origin/linux_maste
    ui->setupUi(this);
    int rowCount=0;
    std::ifstream balanceInput;
    dataManager* data=new dataManager();
    QString path=data->getPath()+"bal.ssff";
    ui->currency->setText(data->GetCurrency());
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
    qDebug()<<balance;
    ui->balance->setNum(balance);
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
            dataTe=result.at(1);
            commentTe=result.at(2);
            typeTe=result.at(3);
            summTe=result.at(4);
            balanceTe=result.at(5);
            line = in.readLine();
            if(!dataTe.isEmpty())
            {
                rowCount++;
                ui->tableWidget->setRowCount(rowCount);
                QTableWidgetItem* dataT=new QTableWidgetItem(tr("%1").arg(dataTe));
                QTableWidgetItem* commentT=new QTableWidgetItem(tr("%1").arg(commentTe));
                QTableWidgetItem* typeT=new QTableWidgetItem(tr("%1").arg(typeTe));
                QTableWidgetItem* summT=new QTableWidgetItem(tr("%1").arg(summTe));
                QTableWidgetItem* ballT=new QTableWidgetItem(tr("%1").arg(balanceTe));
                ui->tableWidget->setItem(rowCount-1,0,dataT);
                ui->tableWidget->setItem(rowCount-1,1,commentT);
                ui->tableWidget->setItem(rowCount-1,2,typeT);
                ui->tableWidget->setItem(rowCount-1,3,summT);
                ui->tableWidget->setItem(rowCount-1,4,ballT);
                result.clear();

            }

        }
        ui->tableWidget->sortByColumn(0);
        file.close();
    }
    monthSelected=ui->date->date().month();
    yearSelected=ui->date->date().year();
    ui->monthTitle->setText(ui->date->date().longMonthName(monthSelected));
    ui->yearLabel->setNum(yearSelected);
    ui->balance->setNum(balance);
    this->setWindowTitle(tr("Snipe Studio Budget Manager"));
    ui->date->setDateTime(QDateTime::currentDateTime());
    connect(ui->about,SIGNAL(clicked()),this,SLOT(help()));
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(addOperation()));
    connect(ui->settings,SIGNAL(clicked()),this,SLOT(showSettings()));
    connect(ui->save,SIGNAL(clicked()),this,SLOT(save()));
    connect(ui->load,SIGNAL(clicked()),this,SLOT(load()));
<<<<<<< HEAD
=======
    connect(ui->nextMonth,SIGNAL(clicked()),this,SLOT(NextMonth()));
    connect(ui->PreviousMonth,SIGNAL(clicked()),this,SLOT(PrevMonth()));
>>>>>>> origin/linux_maste
    ui->profit->setChecked(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent*)
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
    QString fileNameQ=tr("%3snipeStudio_%1.%2.csv").arg(QString::number(ui->date->date().month())).arg(QString::number(ui->date->date().year())).arg(data->getPath());
    QFile file(fileNameQ);
    QTextStream out(&file);
    out.setCodec("UTF-8");
    if(file.open(QIODevice::WriteOnly))
    {
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            out<<i+1
                      <<";"<<ui->tableWidget->item(i,0)->text()
                     <<";"<<ui->tableWidget->item(i,1)->text()
                    <<";"<<ui->tableWidget->item(i,2)->text()
                   <<";"<<ui->tableWidget->item(i,3)->text()
                  <<";"<<ui->tableWidget->item(i,4)->text()
                 <<"\n";
        }
    }
    set->close();
    file.close();
    close();
}

void Widget::help()
{
    QMessageBox* a=new QMessageBox(this);
<<<<<<< HEAD
    a->setText(tr("Snipe Studio Budget Manager v.%1\nUsing QT5 in Ubuntu Linux\n(CopyLeft)2010-2014").arg(this->version));
    a->setWindowTitle(tr("About SSBM"));
    connect(a,SIGNAL(buttonClicked(QAbstractButton*)),a,SLOT(close()));
    a->show();
=======
    a->about(this,tr("About SSBM"),tr("Snipe Studio Budget Manager v.%1\nUsing QT5 in Ubuntu Linux\n2010-2014(ɔ)").arg(this->version));
    a->close();
>>>>>>> origin/linux_maste
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
    QString typeText="";
    QString data=ui->date->text();
    int count=ui->tableWidget->rowCount()+1;
    double bal=ui->balance->text().toDouble();
    if(!ui->sum->text().isEmpty())
    {
        double summ=ui->sum->text().toDouble();
        if(ui->profit->isChecked())
        {
            ui->balance->setNum(summ+bal);
            bal=summ+bal;
           typeText="+";
        }
        else
        {
            ui->balance->setNum(bal-summ);
            typeText="-";
            bal=bal-summ;
        }
        QTableWidgetItem* dataT=new QTableWidgetItem(tr("%1").arg(data));
        QTableWidgetItem* commentT=new QTableWidgetItem(tr("%1").arg(commentText));
        QTableWidgetItem* typeT=new QTableWidgetItem(tr("%1").arg(typeText));
        QTableWidgetItem* summT=new QTableWidgetItem(tr("%1").arg(summ));
        QTableWidgetItem* ballT=new QTableWidgetItem(tr("%1").arg(bal));
        ui->tableWidget->setRowCount(count);
        ui->tableWidget->setItem(count-1,0,dataT);
        ui->tableWidget->setItem(count-1,1,commentT);
        ui->tableWidget->setItem(count-1,2,typeT);
        ui->tableWidget->setItem(count-1,3,summT);
        ui->tableWidget->setItem(count-1,4,ballT);
        ui->tableWidget->sortByColumn(0);
        ui->comment->clear();
        ui->sum->clear();

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
    if(file.open(QIODevice::WriteOnly))
    {
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            out<<i+1
                      <<";"<<ui->tableWidget->item(i,0)->text()
                     <<";"<<ui->tableWidget->item(i,1)->text()
                    <<";"<<ui->tableWidget->item(i,2)->text()
                   <<";"<<ui->tableWidget->item(i,3)->text()
                  <<";"<<ui->tableWidget->item(i,4)->text()
                 <<"\n";
        }
    }
    file.close();
}

void Widget::load()
{
    {
        int rowCount=0;
        dataManager* data=new dataManager();
        QString path=data->getPath()+"bal.ssff";
        ui->currency->setText(data->GetCurrency());
<<<<<<< HEAD
=======
        ui->yearLabel->setNum(yearSelected);
>>>>>>> origin/linux_maste
        QFile file_bal(path);
        QTextStream in_bal(&file_bal);
        in_bal.setCodec("UTF-8");
        double balance;

        if(file_bal.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString line = in_bal.readLine();
            qDebug()<<line;
            balance=line.toDouble();
<<<<<<< HEAD

            file_bal.close();
        }
        else
        {
            balance=0;
        }
        ui->balance->setNum(balance);
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
                dataTe=result.at(1);
                commentTe=result.at(2);
                typeTe=result.at(3);
                summTe=result.at(4);
                balanceTe=result.at(5);
                line = in.readLine();
=======

            file_bal.close();
        }
        else
        {
            balance=0;
        }
        ui->balance->setNum(balance);
        ui->date->setDateTime(QDateTime::currentDateTime());
        QString fileNameQ=tr("%3snipeStudio_%1.%2.csv").arg(QString::number(monthSelected)).arg(QString::number(yearSelected)).arg(data->getPath());
        qDebug() << fileNameQ;
        QFile file(fileNameQ);
        ui->tableWidget->setRowCount(0);
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
                dataTe=result.at(1);
                commentTe=result.at(2);
                typeTe=result.at(3);
                summTe=result.at(4);
                balanceTe=result.at(5);
                line = in.readLine();

>>>>>>> origin/linux_maste
                if(!dataTe.isEmpty())
                {
                    rowCount++;
                    ui->tableWidget->setRowCount(rowCount);
                    QTableWidgetItem* dataT=new QTableWidgetItem(tr("%1").arg(dataTe));
                    QTableWidgetItem* commentT=new QTableWidgetItem(tr("%1").arg(commentTe));
                    QTableWidgetItem* typeT=new QTableWidgetItem(tr("%1").arg(typeTe));
                    QTableWidgetItem* summT=new QTableWidgetItem(tr("%1").arg(summTe));
                    QTableWidgetItem* ballT=new QTableWidgetItem(tr("%1").arg(balanceTe));
                    ui->tableWidget->setItem(rowCount-1,0,dataT);
                    ui->tableWidget->setItem(rowCount-1,1,commentT);
                    ui->tableWidget->setItem(rowCount-1,2,typeT);
                    ui->tableWidget->setItem(rowCount-1,3,summT);
                    ui->tableWidget->setItem(rowCount-1,4,ballT);
                    result.clear();
                }
            }
            ui->tableWidget->sortByColumn(0);
            file.close();
        }
        ui->balance->setNum(balance);
        ui->currency->setText(data->GetCurrency());
        delete data;
    }
}
<<<<<<< HEAD
=======
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
  set=new settings();
  set->show();
}
>>>>>>> origin/linux_maste
