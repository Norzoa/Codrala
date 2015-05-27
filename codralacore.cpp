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
    // Initialisation des QWidget
    zoneGestOR = new QMdiArea;

    // Création de la zone de travail
    setCentralWidget(zoneGestOR);

    // Création des menus
    if(CodralaMenu() != 0x000)
        qApp->quit();
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

CodralaCore::CodralaCreaORWin()
{
    widgetCreaOR = new QWidget;
    if(widgetCreaOR == NULL)
        return 0x019;
    ongletsCreaOR = new QTabWidget(widgetCreaOR);
    if(ongletsCreaOR == NULL)
        return 0x020;

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

    ville = new QLineEdit;
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

    layoutClient = new QVBoxLayout;
    if(layoutClient == NULL)
        return 0x018;

    //layoutClient->addLayout(layoutInformationClient);

    ongletClient->setLayout(layoutInformationClient);

    // Final
    layoutCreaOR = new QVBoxLayout;
    if(layoutCreaOR == NULL)
        return 0x21;
    layoutCreaOR->addWidget(ongletsCreaOR);

    ongletsCreaOR->addTab(ongletClient, "Client");
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
