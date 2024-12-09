#include "historique.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>

historique::historique() : mFilename("C:\\Users\\MSI\\Desktop\\Atelier_Connexion (3)\\Atelier_Connexion\\historique\\historique.txt")
{
}

void historique::write(const QString &text)
{
    QFile mFile(mFilename);
    if (!mFile.open(QFile::Append | QFile::Text))
    {
        qDebug() << "Impossible d'ouvrir le fichier";
        return;
    }

    QDateTime datetime = QDateTime::currentDateTime();
    QString date = datetime.toString();
    date += " ";

    QTextStream out(&mFile);
    out << date << text << "\n";

    mFile.flush();
    mFile.close();
}

QString historique::read()
{
    QFile mFile(mFilename);
    if (!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Impossible d'ouvrir le fichier";
        return "";
    }

    QTextStream in(&mFile);
    QString text = in.readAll();

    mFile.close();
    return text;
}



