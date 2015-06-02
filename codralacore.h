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

#ifndef HEADER_CODRALACORE_H
#define HEADER_CODRALACORE_H

/* Contient le coeur du programme */

#include <QtWidgets>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "citydata.h"

class CodralaCore:public QMainWindow
{
Q_OBJECT

public:
    CodralaCore();

public slots:
    void ouvrirFenetreCreaOR();
    void comparerCpVille(const QString &);

private:
    // Splash

    QSplashScreen screen;

    // Fenêtre principale

    int CodralaMenu(); // Fonction générant les menus du logiciel

    QMdiArea *zoneGestOR = NULL;

    // Menu

    QMenu *menuFichier = NULL;
    QMenu *menuEdition = NULL;
    QMenu *menuOutils  = NULL;
    QMenu *menuAide    = NULL;

    QMenu   *menuNouveau  = NULL;
    QAction *actionCreaOR = NULL;

    QAction *actionQuitter = NULL;

    // Fenêtre de création d'Ordre de Réparation

    int CodralaCreaORWin(); //Création de la fenêtre de création d'Ordre de réparation

    QMdiSubWindow *fenetreCreaOR = NULL;

    QWidget *widgetCreaOR = NULL;
    QVBoxLayout *layoutCreaOR = NULL;

    QTabWidget *ongletsCreaOR = NULL;

    // Onglet client
    QWidget *ongletClient = NULL;

    QFormLayout *layoutInformationClient = NULL;

    QVector<CData> infoVille;
    int lireVille();

    QLineEdit *nom        = NULL;
    QLineEdit *prenom     = NULL;
    QLineEdit *adresse    = NULL;
    QLineEdit *codePostal = NULL;
    QComboBox *ville      = NULL;
    QLineEdit *numFix     = NULL;
    QLineEdit *numMob     = NULL;
    QLineEdit *email      = NULL;

    // Onglet véhicule
    QWidget *ongletVehicule = NULL;

    QFormLayout *layoutInformationVehicule = NULL;

    int lireMarque();

    QComboBox *marque    = NULL;
    QLineEdit *modele    = NULL;
    QLineEdit *vin       = NULL;
    QLineEdit *immat     = NULL;
    QLineEdit *dateMeC   = NULL;
    QLineEdit *cylindree = NULL;
    QLineEdit *puissance = NULL;


};

#endif

