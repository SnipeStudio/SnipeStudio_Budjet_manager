#include "editentry.h"
#include "ui_editentry.h"


editentry::editentry(QWidget *parent, logger* log, QVector<QString> *data,sqlMan* db) :
    QDialog(parent),
    ui(new Ui::editentry)
{
    ui->setupUi(this);
    log_ptr=log;
    database = db;
    index=data->at(0).toInt();
    dt=QDateTime::fromString(data->at(1),"dd-MM-yyyy hh:mm:ss");
    summ=data->at(2).toDouble();
    comment=data->at(3);
    ui->dateTimeEdit->setDateTime(dt);
    ui->lineSumm->setText(QString::number(summ));
    ui->lineEditComment->setText(comment);
    if(summ>0)
    {
        ui->radioButtonProfit->click();
    }
    else
    {
        ui->radioButtonExpense->click();
    }
}

editentry::~editentry()
{
    delete ui;
}

void editentry::on_cancel_clicked()
{
    this->close();
}

void editentry::on_deleteOp_clicked()
{
    database->deleteOperation(index);
    this->close();
}

void editentry::on_confirmChanges_clicked()
{
    const QChar delimiter=(uchar)'.';
    bool summDigits=true;
    if(!ui->lineSumm->text().isEmpty())
      {
      for(int i=0;i<ui->lineSumm->text().length();i++)
      {
        if(!ui->lineSumm->text().at(i).isDigit()&&!(ui->lineSumm->text().at(i)=='.')&&!(ui->lineSumm->text().at(i)==','))
          {
           summDigits=false;
           }
        if((ui->lineSumm->text().at(i)=='.')||(ui->lineSumm->text().at(i)==','))
          {
           ui->lineSumm->setText(ui->lineSumm->text().replace(i,1,delimiter));
           }
        }
      }
    if((ui->lineEditComment->text().isEmpty()&&ui->lineSumm->text().isEmpty())||!summDigits)
      {
        QMessageBox* a=new QMessageBox(this);
        a->setText("Invalid summ value");
        a->show();
        return;
      }
    if(ui->lineEditComment->text().isEmpty())
        ui->lineEditComment->setText(tr("Default"));
        bool side=false;
        if(ui->radioButtonProfit->isChecked())
        {
           side=true;
        }
        else
        {
            side=false;
        }

        QDateTime time=ui->dateTimeEdit->dateTime();
        if(!side)
        {
            database->updateEntry(database,index,(-1)*ui->lineSumm->text().toDouble(),ui->lineEditComment->text(),side,time);
        }
        else
        {
            database->updateEntry(database,index,ui->lineSumm->text().toDouble(),ui->lineEditComment->text(),side,time);
        }
        this->close();
}
