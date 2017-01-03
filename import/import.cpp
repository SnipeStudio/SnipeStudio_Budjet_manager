#include "import.h"
#include "ui_import.h"

Import::Import(QWidget *parent, sqlMan* sqlManOut) :
    QDialog(parent),
    ui(new Ui::Import)
{
    ui->setupUi(this);
    ui->progressBar->hide();
    sqlManager=sqlManOut;
    connect(ui->buttonBox,SIGNAL(accepted()),this, SLOT(saveData()));
    connect(ui->select, SIGNAL(clicked()), this, SLOT(selectFile()));
}

Import::~Import()
{
    delete ui;
}

void Import::saveData()
{
    ui->progressBar->show();
    QString filename=QDir::toNativeSeparators(ui->filenameLine->text());
    QFile* file = new QFile(filename);
    file->open(QIODevice::ReadOnly);
    QTextStream fin(file);
    int rows = 0;
    int row = 0;
    fin>>rows;
    ui->progressBar->setMaximum(rows);
    ui->progressBar->setValue(row);
    while (!fin.atEnd())
    {
       QString line = fin.readLine();
       if(line.isEmpty())
           continue;
       QStringList list = line.split(';');
       QDateTime dateTime = QDateTime::fromString(list[1],"dd-MM-yyyy hh:mm:ss");
       double summ = list[2].toDouble();
       QString comment = list[3];
       bool side = list.at(5).toInt();
       sqlManager->addOperation(summ, comment,side,dateTime);
       sqlManager->addOperation(summ, comment,side,dateTime);
       row++;
    }
    file->close();
    this->close();
}

void Import::selectFile()
{
    dataManager* data = new dataManager();
    QFileDialog* selectFileDialog = new QFileDialog(this);
    selectFileDialog->setOption(QFileDialog::DontUseNativeDialog);
    selectFileDialog->setDirectory(data->getPath());
    if(selectFileDialog->exec())
    {
        QString file = selectFileDialog->selectedFiles()[0];
        ui->filenameLine->setText(file);
    }
    delete data;
}
