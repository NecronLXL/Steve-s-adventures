#pragma once
#include "MenuPrincipal.h"
#include "UtilidadesConsola.h"
#include "Nivel1.h"
#include "Nivel2.h"
#include "Nivel3.h"
#include <iostream>
#include <string>
using namespace std;
using namespace System;

class Juego {
private:
    void mostrarTutorial() const {
        UtilidadesConsola::limpiarPantalla();
        string mensaje = "TUTORIAL - Presiona una tecla para volver...";
        cout << mensaje;
        UtilidadesConsola::obtenerTecla();
    }

    void mostrarSeleccionNiveles() const {
        UtilidadesConsola::limpiarPantalla();
        cout << "1. Bosque de Jesse\n2. Desfiladero de Lukas\n3. Redencion de Ivor\n";

        ConsoleKey opcion = UtilidadesConsola::obtenerTecla();
        if (opcion == ConsoleKey::D1) Nivel1::iniciar();
        else if (opcion == ConsoleKey::D2) Nivel2::iniciar();
        else if (opcion == ConsoleKey::D3) Nivel3::iniciar();
    }

    void mostrarCreditos() const {
        UtilidadesConsola::limpiarPantalla();
        string titulo = "JESSE'S ADVENTURES";
        cout << titulo << "\n\n";
        cout << "Hans J. Velasco\n";
        cout << "Stephen S. Barbaran\n";
        cout << "Fabritzio M. Sierra\n\n";
        cout << "Presiona una tecla para volver...";
        UtilidadesConsola::obtenerTecla();
    }

public:
    void ejecutar() {
        MenuPrincipal menu;
        bool salir = false;

        while (!salir) {
            int opcion = menu.ejecutar();

            switch (opcion) {
            case 0:
                Nivel1::iniciar();
                break;
            case 1:
                mostrarTutorial();
                break;
            case 2:
                mostrarSeleccionNiveles();
                break;
            case 3:
                mostrarCreditos();
                break;
            }
        }
    }
};

