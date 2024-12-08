#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include <QString>
#include <QObject>

class historique
{
public:
    historique();
    void write(const QString &text);
    QString read();

private:
    QString mFilename;
};

#endif // HISTORIQUE_H
