#include "export.h"
#include "ui_export.h"

Export::Export(QWidget *parent, QSqlTableModel* modelOut) :
    QWidget(parent),
    ui(new Ui::Export)
{    
    ui->setupUi(this);
    ui->progressBar->hide();
    model=modelOut;
    connect(ui->save, SIGNAL(clicked()), this , SLOT(saveData()));

}

Export::~Export()
{
    delete ui;
}

void Export::saveData()
{
    ui->progressBar->show();

    int columns = model->columnCount();
    QString filename=QDir::toNativeSeparators(ui->pathLine->text()+"\\" +ui->filenameLine->text());
    QFile* file = new QFile(filename);
    file->open(QIODevice::Append);
    while(model->canFetchMore())
    {
        model->fetchMore();
    }
    int rows = model->rowCount();
    QTextStream fout(file);
    fout<<rows<<"\n";
    qDebug()<<model->rowCount();;
    ui->progressBar->setMaximum(rows);
    for(long row = 0; row<rows; row++)
    {
        ui->progressBar->setValue(row);
        QString line = "";
        for (int column = 0; column < columns; column++)
        {
          QModelIndex index = model->index(row, column);
          line+= model->data(index).toString() + ";";
        }

        fout<<line<<"\n";
    }
    file->close();
    this->close();
}


