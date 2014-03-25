#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    int rowCount=0;
    std::ifstream balanceInput;
    dataManager* data=new dataManager(this);
    QString path=data->getPath()+"bal.ssff";
    QFile file_bal(path);
    QTextStream in_bal(&file_bal);
    in_bal.setCodec("UTF-8");
    if(file_bal.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString line = in_bal.readLine();
        ui->balance->setText(line);
    }
    file_bal.close();
    double balance=0;
    if(balanceInput.is_open())
    {
        balanceInput>>balance;
        balanceInput.close();
    }

    //std::ifstream tableInput;
    ui->date->setDateTime(QDateTime::currentDateTime());
    //sprintf(fileName,"snipeStudio_%i.%i.csv",ui->date->date().month(),ui->date->date().year());
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
                qDebug()<<result;
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
    this->setWindowTitle("Snipe Studio Budget Manager");
    ui->date->setDateTime(QDateTime::currentDateTime());
    connect(ui->about,SIGNAL(clicked()),this,SLOT(help()));
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(addOperation()));
    ui->profit->setChecked(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent*)
{
    dataManager* data=new dataManager(this);
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
    file.close();
    close();
}

void Widget::help()
{
    QMessageBox* a=new QMessageBox(this);
    a->setText(tr("Snipe Studio Budget Manager\n(CopyLeft)2010-2014"));
    a->setWindowTitle(QString::fromStdString("About SSBM"));
    connect(a,SIGNAL(buttonClicked(QAbstractButton*)),a,SLOT(close()));
    a->show();
}

void Widget::addOperation()
{
    QString commentText=ui->comment->text();
    if(commentText.isEmpty())
        commentText="Default";
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

    }
}


