#include "email.h"
#include <QtCore>
#include <QtNetwork>

bool Email::envoyerEmail(const QString &destinataire, const QString &sujet, const QString &message)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    // URL du serveur SMTP
    QNetworkRequest request;
    request.setUrl(QUrl("smtp://smtp.gmail.com:587"));  // Utilisez le serveur SMTP approprié
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Corps du message
    QByteArray data;
    data.append("Subject: " + sujet.toUtf8() + "\r\n");
    data.append("To: " + destinataire.toUtf8() + "\r\n");
    data.append("Content-Type: text/plain; charset=\"utf-8\"\r\n\r\n" + message.toUtf8());

    // Identifiants SMTP
    QString user = "destinataire@gmail.com";  // Remplacez par votre adresse email
    QString password = ""; // Remplacez par votre mot de passe (ou un mot de passe spécifique à l'application)

    QByteArray auth = "Basic " + QByteArray(QString("%1:%2").arg(user).arg(password).toUtf8().toBase64());
    request.setRawHeader("Authorization", auth);

    // Envoi de la requête
    QNetworkReply *reply = manager->post(request, data);

    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "Erreur lors de l'envoi de l'email : " << reply->errorString();
        } else {
            qDebug() << "Email envoyé avec succès!";
        }
        reply->deleteLater();
    });

    return true;  // Retourne true si l'email est bien envoyé
}

