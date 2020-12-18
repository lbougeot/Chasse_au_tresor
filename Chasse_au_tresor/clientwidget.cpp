/**
  @file clientwidget.cpp
  @brief implémentation de la classe Clientwidget
  @author Louis BOUGEOT
  @date 18/12/2020
  */

#include "clientwidget.h"
#include "ui_ClientCrawler.h"

ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    socketDeDialogueAvecServeur = new QTcpSocket;
    grille = new QGridLayout;

    /** Connection entre mes signaux et les slots */

    connect(socketDeDialogueAvecServeur, &QTcpSocket::connected, this, &ClientWidget::onQTcpSocket_connected);
    connect(socketDeDialogueAvecServeur, &QTcpSocket::disconnected, this, &ClientWidget::onQTcpSocket_disconnected);
    connect(socketDeDialogueAvecServeur, &QTcpSocket::readyRead, this, &ClientWidget::onQTcpSocket_readyRead);
    connect(socketDeDialogueAvecServeur, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &ClientWidget::onQTcpSocket_error);

    /** Construction de mon tableau */

    for (int ligne=0; ligne < TAILLE; ligne++)
    {
        for (int colonne=0; colonne<TAILLE;colonne++)
        {
            QToolButton *b=new QToolButton();
            grille->addWidget(b,ligne,colonne,1,1);
        }

    }

    //PLacement sur la grille des objets présents sur ui
    //les labels
    grille->addWidget(ui->labelAdresseServeur,TAILLE,0,1,5);
    grille->addWidget(ui->labelNumeroPort,TAILLE,6,1,5);
    grille->addWidget(ui->labelDistance,TAILLE+3,0,1,5);
    grille->addWidget(ui->labelInformations,TAILLE+3,12,1,5);
    //les QLineEdit adresse et port
    grille->addWidget(ui->lineEditAdresseServeur,TAILLE+1,0,1,5);
    grille->addWidget(ui->spinBoxPortServeur,TAILLE+1,6,1,5);
    //les QPushButton connexion et quitter
    grille->addWidget(ui->pushButtonConnexion,TAILLE+2,0,1,5);
    grille->addWidget(ui->pushButtonQuitter,TAILLE+2,6,1,5);
    //les QPushButton fleches
    grille->addWidget(ui->pushButtonUp,TAILLE,15,1,1);
    grille->addWidget(ui->pushButtonLeft,TAILLE+1,14,1,1);
    grille->addWidget(ui->pushButtonRight,TAILLE+1,16,1,1);
    grille->addWidget(ui->pushButtonDown,TAILLE+2,15,1,1);
    //distance et informations
    grille->addWidget(ui->lcdNumberDistance,TAILLE+3,6,1,5);
    this->setLayout(grille);



}

ClientWidget::~ClientWidget()
{
    delete ui;
    delete grille;
    delete socketDeDialogueAvecServeur;
}



void ClientWidget::onQTcpSocket_connected()
{
     qDebug() << this << "Connectée";
     ui->spinBoxPortServeur->setEnabled(false);
     //placer une case noir quand on est connecté
     grille->itemAtPosition(8,5)->widget()->setStyleSheet("background-color:black");
     ui->pushButtonConnexion->setText("Deconnection");
     ui->labelInformations->setText("start");
}

void ClientWidget::onQTcpSocket_disconnected()
{
    ui->spinBoxPortServeur->setEnabled(true);
     qDebug() << this << "Déconnectée";
}

void ClientWidget::onQTcpSocket_error(QAbstractSocket::SocketError socketError)
{
    qDebug() << this << "Erreur";
}

void ClientWidget::onQTcpSocket_readyRead()
{

    quint16 taille=0;
    QString message;
    if(socketDeDialogueAvecServeur->bytesAvailable() >= (qint64)taille)
    {
        QDataStream in(socketDeDialogueAvecServeur);
        in >> taille;

        if(socketDeDialogueAvecServeur->bytesAvailable() >= (qint64)taille)
        {
            in>>message;
        }
    }

}

void ClientWidget::EnvoyerCommande(QChar commande)
{

    /*
    // A voir
    quint16 taille=0;
    //float montant = ui->lineEditMontant->text().toInt();

    if(ui->pushButtonUp){
        quint16 taille=0;
        QChar commande='U';
        QBuffer tampon;
        tampon.open(QIODevice::WriteOnly);
        QDataStream out(&tampon);
        out<<taille<<commande;
        taille=tampon.size()-sizeof(taille);
        tampon.seek(0);
        out<<taille;
        socketDeDialogueAvecServeur->write(tampon.buffer());
    }
    else if (ui->pushButtonDown) {
        quint16 taille=0;
        QChar commande='D';
        QBuffer tampon;
        tampon.open(QIODevice::WriteOnly);
        QDataStream out(&tampon);
        out<<taille<<commande;
        taille=tampon.size()-sizeof(taille);
        tampon.seek(0);
        out<<taille;
        socketDeDialogueAvecServeur->write(tampon.buffer());
    }
    else if(ui->pushButtonLeft){
        quint16 taille=0;
        QChar commande='L';
        QBuffer tampon;
        tampon.open(QIODevice::WriteOnly);
        QDataStream out(&tampon);
        out<<taille<<commande;
        taille=tampon.size()-sizeof(taille);
        tampon.seek(0);
        out<<taille;
        socketDeDialogueAvecServeur->write(tampon.buffer());;
    }
    else if(ui->pushButtonRight){
        quint16 taille=0;
        QChar commande='R';
        QBuffer tampon;
        tampon.open(QIODevice::WriteOnly);
        QDataStream out(&tampon);
        out<<taille<<commande;
        taille=tampon.size()-sizeof(taille);
        tampon.seek(0);
        out<<taille;
        socketDeDialogueAvecServeur->write(tampon.buffer());
    }
    */

}


void ClientWidget::on_pushButtonConnexion_clicked()
{
    /*
    QString IP = ui->lineEditAdresseServeur->text();
    quint16 port = ui->spinBoxPortServeur->text().toInt();

    socketDeDialogueAvecServeur->connectToHost(IP, port, QIODevice::ReadWrite, QAbstractSocket::AnyIPProtocol);
    */

    if(ui->pushButtonConnexion->text()=="Connexion"){
        QHostAddress adresse(ui->lineEditAdresseServeur->text());
        socketDeDialogueAvecServeur->connectToHost(adresse,ui->spinBoxPortServeur->text().toUInt());
        ui->pushButtonConnexion->setText("Deconnection");
    }else{
        socketDeDialogueAvecServeur->disconnectFromHost();
        ui->pushButtonConnexion->setText("Connexion");
    }

}

void ClientWidget::on_pushButtonUp_clicked()
{

    quint16 taille=0;
    QChar commande='U';
    QBuffer tampon;
    tampon.open(QIODevice::WriteOnly);
    QDataStream out(&tampon);
    out<<taille<<commande;
    taille=tampon.size()-sizeof(taille);
    tampon.seek(0);
    out<<taille;
    socketDeDialogueAvecServeur->write(tampon.buffer());


}

void ClientWidget::on_pushButtonDown_clicked()
{
    quint16 taille=0;
    QChar commande='D';
    QBuffer tampon;
    tampon.open(QIODevice::WriteOnly);
    QDataStream out(&tampon);
    out<<taille<<commande;
    taille=tampon.size()-sizeof(taille);
    tampon.seek(0);
    out<<taille;
    socketDeDialogueAvecServeur->write(tampon.buffer());
}

void ClientWidget::on_pushButtonLeft_clicked()
{
    quint16 taille=0;
    QChar commande='L';
    QBuffer tampon;
    tampon.open(QIODevice::WriteOnly);
    QDataStream out(&tampon);
    out<<taille<<commande;
    taille=tampon.size()-sizeof(taille);
    tampon.seek(0);
    out<<taille;
    socketDeDialogueAvecServeur->write(tampon.buffer());
}

void ClientWidget::on_pushButtonRight_clicked()
{
    quint16 taille=0;
    QChar commande='R';
    QBuffer tampon;
    tampon.open(QIODevice::WriteOnly);
    QDataStream out(&tampon);
    out<<taille<<commande;
    taille=tampon.size()-sizeof(taille);
    tampon.seek(0);
    out<<taille;
    socketDeDialogueAvecServeur->write(tampon.buffer());
}
