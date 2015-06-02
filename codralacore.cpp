/*     Copyright (C) 2015 Le Dévic Trystan

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. */

#include "codralacore.h"

CodralaCore::CodralaCore()
{
    screen.setPixmap(QPixmap(":/img/splash"));
    screen.show();
    qApp->processEvents();

    // Initialisation des QWidget
    screen.showMessage("Chargement de la zone de travail", Qt::AlignLeft | Qt::AlignBottom);
    zoneGestOR = new QMdiArea;

    // Création de la zone de travail
    setCentralWidget(zoneGestOR);

    // Création des menus
    screen.showMessage("Chargement des menus", Qt::AlignLeft | Qt::AlignBottom);
    if(CodralaMenu() != 0x000)
        qApp->quit();

    // Lecture ville
    screen.showMessage("Chargement des villes", Qt::AlignLeft | Qt::AlignBottom);
    if(lireVille() != 0x000)
        qApp->quit();

    screen.finish(this);
}

CodralaCore::CodralaMenu()
{
    menuFichier = menuBar()->addMenu("&Fichier");
    if(menuFichier == NULL)
        return 0x001;
    //Nouveau
    menuNouveau = menuFichier->addMenu("Nouveau");
    if(menuNouveau == NULL)
        return 0x002;
    // Nouveau Ordre de Réparation
    actionCreaOR = new QAction("Ordre de Réparation", this);
    if(actionCreaOR == NULL)
        return 0x003;
    connect(actionCreaOR, SIGNAL(triggered()), this, SLOT(ouvrirFenetreCreaOR()));
    menuNouveau->addAction(actionCreaOR);

    menuFichier->addSeparator();

    //Quitter
    actionQuitter = new QAction("&Quitter", this);
    if(actionQuitter == NULL)
        return 0x004;
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    menuFichier->addAction(actionQuitter);


    menuEdition = menuBar()->addMenu("&Edition");
    if(menuEdition == NULL)
        return 0x005;


    menuOutils = menuBar()->addMenu("&Outils");
    if(menuOutils == NULL)
        return 0x006;


    menuAide = menuBar()->addMenu("&?");
    if(menuAide == NULL)
        return 0x007;

    return 0x000;
}

CodralaCore::lireVille()
{
    QFile csvVille(":/csv/cityData");
    qDebug("Chargement villes");
    if(csvVille.exists() == true)
        qDebug("Le fichier peu être ouvert");
    else
        qDebug("Le fichier ne peu être ouvert");

    if(csvVille.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::Unbuffered))
    {
        qDebug("Chargement fichier");
        QTextStream flux(&csvVille);
        CData lectLigne;

        while(!flux.atEnd())
        {
            QString ligne;
            QStringList infoCsv;
            ligne = flux.readLine();
            infoCsv = ligne.split(";");

            //screen.showMessage("Chargement ville: " + infoCsv.at(1), Qt::AlignLeft | Qt::AlignBottom);

            lectLigne.setCP(infoCsv.at(2));
            lectLigne.setVille(infoCsv.at(1));

            infoVille.resize(infoVille.size()+1);
            infoVille.insert((infoVille.size()-1), lectLigne);

            lectLigne.clear();
        }
        csvVille.close();


    }
    else
    {
        qDebug("Erreur ouverture ville");
        qDebug() << csvVille.error();
        return 0x001;
    }

    return 0x000;
}

int CodralaCore::lireMarque()
{
    QFile csvMarque(":/csv/marque");
    qDebug("Chargement Marque");
    if(csvMarque.exists() == true)
        qDebug("Le fichier peu être ouvert");
    else
        qDebug("Le fichier ne peu être ouvert");

    if(csvMarque.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::Unbuffered))
    {
        qDebug("Chargement fichier");
        QTextStream flux(&csvMarque);
        while(!flux.atEnd())
        {
            QString ligne;
            ligne = flux.readLine();

            marque->addItem(ligne);
        }
        csvMarque.close();
    }
    return 0x000;
}

CodralaCore::CodralaCreaORWin()
{
    widgetCreaOR = new QWidget;
    if(widgetCreaOR == NULL)
        return 0x019;
    ongletsCreaOR = new QTabWidget(widgetCreaOR);
    if(ongletsCreaOR == NULL)
        return 0x020;
    
    // Client

    ongletClient = new QWidget;
    if(ongletClient == NULL)
        return 0x008;


    nom = new QLineEdit;
    if(nom == NULL)
        return 0x009;

    prenom = new QLineEdit;
    if(prenom == NULL)
        return 0x010;

    adresse = new QLineEdit;
    if(adresse == NULL)
        return 0x011;

    codePostal = new QLineEdit;
    if(codePostal == NULL)
        return 0x012;
    connect(codePostal, SIGNAL(textChanged(const QString &)), this, SLOT(comparerCpVille(const QString &)));

    ville = new QComboBox;
    if(ville == NULL)
        return 0x013;

    numFix = new QLineEdit;
    if(numFix == NULL)
        return 0x014;

    numMob = new QLineEdit;
    if(numMob == NULL)
        return 0x015;

    email = new QLineEdit;
    if(email == NULL)
        return 0x016;

    layoutInformationClient = new QFormLayout;
    if(layoutInformationClient == NULL)
        return 0x017;

    layoutInformationClient->addRow("Nom", nom);
    layoutInformationClient->addRow("Prénom", prenom);
    layoutInformationClient->addRow("Adresse", adresse);
    layoutInformationClient->addRow("Code Postal", codePostal);
    layoutInformationClient->addRow("Ville", ville);
    layoutInformationClient->addRow("Fixe", numFix);
    layoutInformationClient->addRow("Mobile", numMob);
    layoutInformationClient->addRow("Email", email);

    ongletClient->setLayout(layoutInformationClient);

    // Véhicule

    ongletVehicule = new QWidget;
    if(ongletVehicule == NULL)
        return 0x022;

    marque = new QComboBox;
    if(marque == NULL)
        return 0x023;
    lireMarque();

    modele = new QLineEdit;
    if(modele == NULL)
        return 0x024;

    vin = new QLineEdit;
    if(vin == NULL)
        return 0x025;
    vin->setMaxLength(17);

    immat = new QLineEdit;
    if(immat == NULL)
        return 0x026;

    dateMeC = new QLineEdit;
    if(dateMeC == NULL)
        return 0x027;

    cylindree = new QLineEdit;
    if(cylindree == NULL)
        return 0x028;

    puissance = new QLineEdit;
    if(puissance == NULL)
        return 0x029;

    layoutInformationVehicule = new QFormLayout;
    if(layoutInformationVehicule == NULL)
        return 0x030;

    layoutInformationVehicule->addRow("Marque",marque);
    layoutInformationVehicule->addRow("Modèle",modele);
    layoutInformationVehicule->addRow("VIN",vin);
    layoutInformationVehicule->addRow("Immatriculation",immat);
    layoutInformationVehicule->addRow("Date 1ère Mise en Circulation",dateMeC);
    layoutInformationVehicule->addRow("Cylindrée (P.1)",cylindree);
    layoutInformationVehicule->addRow("Puissance (P.2)",puissance);

    ongletVehicule->setLayout(layoutInformationVehicule);



    // Final
    layoutCreaOR = new QVBoxLayout;
    if(layoutCreaOR == NULL)
        return 0x021;
    layoutCreaOR->addWidget(ongletsCreaOR);

    ongletsCreaOR->addTab(ongletClient, "Client");
    ongletsCreaOR->addTab(ongletVehicule, "Véhicule");
    widgetCreaOR->setLayout(layoutCreaOR);

    fenetreCreaOR = zoneGestOR->addSubWindow(widgetCreaOR);
    fenetreCreaOR->setWindowTitle("Création d'ordre de réparation");
    widgetCreaOR->show();

    return 0x000;
}

void CodralaCore::ouvrirFenetreCreaOR()
{
    CodralaCreaORWin();
}

void CodralaCore::comparerCpVille(const QString &)
{
    ville->clear();
    int i = 0;
    while(i < infoVille.size())
    {
        if((infoVille.at(i).getCP()).compare(codePostal->text()) == 0)
                ville->addItem(infoVille.at(i).getVille());
        i++;
    }
}
