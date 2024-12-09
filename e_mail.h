#ifndef EMAIL_H
#define EMAIL_H

#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class Email {
public:
    static bool envoyerEmail(const QString &destinataire, const QString &sujet, const QString &message);

};

#endif // EMAIL_H
