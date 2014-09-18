#include "widget.h"



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    sqlMan db;
    fLoad=false;
    idLoaded=0;
    version=tr("14.06-pre(0.3.9.7)");
    ui->setupUi(this);
    dataManager* data=new dataManager();
    QString path=data->getPath()+"bal.ssff";
    ui->currency->setText(data->GetCurrency());
    QFile file_bal(path);
    QTextStream in_bal(&file_bal);
    in_bal.setCodec("UTF-8");
    ui->balance->setNum(db.getBalance());
    ui->date->setDateTime(QDateTime::currentDateTime());
    monthSelected=ui->date->date().month();
    yearSelected=ui->date->date().year();
    ui->monthTitle->setText(ui->date->date().longMonthName(monthSelected));
    ui->yearLabel->setNum(yearSelected);

    this->setWindowTitle(tr("Snipe Studio Budget Manager"));
    ui->date->setDateTime(QDateTime::currentDateTime());
    connect(ui->about,SIGNAL(clicked()),this,SLOT(help()));
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(addOperation()));
    connect(ui->settings,SIGNAL(clicked()),this,SLOT(showSettings()));
    connect(ui->nextMonth,SIGNAL(clicked()),this,SLOT(NextMonth()));
    connect(ui->PreviousMonth,SIGNAL(clicked()),this,SLOT(PrevMonth()));
    ui->profit->setChecked(true);
	QSqlTableModel* model=db.getModel();
	model->setTable("operations");
   /* if(!db.dbIsOpen())
    {
        QMessageBox* a=new QMessageBox(this);
        a->about(this,tr("Error during accessing database"),tr("Can not access database"));
        a->show();
        exit(-1)
        qDebug()<<"ERROR!";
    }*/
    ui->view->setModel(model);
    ui->view->resizeColumnToContents(5);
    ui->view->setColumnWidth(3,310);
    ui->view->hideColumn(4);
    ui->view->hideColumn(0);
    ui->view->sortByColumn(0,Qt::DescendingOrder);
    ui->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->view->show();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent*)
{
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
        db.dbIsOpen();
        qDebug()<<db.getDBName();
        db.addOperation(&db,summ,commentText,side);
        QSqlTableModel* model=db.getModel();
        ui->view->setModel(model);
        ui->view->hideColumn(0);
        ui->view->resizeColumnToContents(0);
        ui->view->resizeColumnToContents(5);
        ui->view->setColumnWidth(3,200);
        ui->view->sortByColumn(0,Qt::DescendingOrder);
        ui->view->show();
        ui->balance->setNum(db.getBalance());

    }
}

void Widget::load()
{
  QTranslator translator;
  dataManager* data=new dataManager();
  qDebug()<<"translation/ssbm_"+data->getTranslation();
  translator.load(QDir::toNativeSeparators("translation/ssbm_"+data->getTranslation()));
  qApp->installTranslator(&translator);
  ui->retranslateUi(this);
  delete data;
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
    set=new settings(this);
    set->show();
}

void Widget::closeSettings()
{
    delete set;
}

void Widget::updLoad(bool load)
{
  fLoad=load;
}
