/**
  @file clientwidget.h
  @brief Déclaration de la classe Clientwidget
  @author Louis BOUGEOT
  @date 18/12/2020
  */

#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QGridLayout>
#include <QToolButton>
#include <QHostAddress>
#include <QBuffer>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class ClientWidget; }
QT_END_NAMESPACE

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private slots:

    void onQTcpSocket_connected();

    void onQTcpSocket_disconnected();

    void onQTcpSocket_error(QAbstractSocket::SocketError socketError);

    void onQTcpSocket_readyRead();

    void EnvoyerCommande(QChar commande);

    void on_pushButtonConnexion_clicked();

    void on_pushButtonUp_clicked();

    void on_pushButtonDown_clicked();

    void on_pushButtonLeft_clicked();

    void on_pushButtonRight_clicked();

private:
    Ui::ClientWidget *ui;
    /** Ma grille */
    QGridLayout *grille;
    /** Ma socket */
    QTcpSocket *socketDeDialogueAvecServeur;
    /** La taille du tableau*/
    int TAILLE = 20;

};
#endif // CLIENTWIDGET_H
