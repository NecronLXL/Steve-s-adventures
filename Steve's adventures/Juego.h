#pragma once
#include "MenuPrincipal.h"
#include "UtilidadesConsola.h"
#include "Nivel1.h"
#include "Nivel2.h"
#include "Nivel3.h"
#include <iostream>

class Juego {
private:
    void mostrarTutorial() const {
        UtilidadesConsola::limpiarPantalla();
        std::cout << "TUTORIAL - Presiona una tecla para volver...";
        UtilidadesConsola::obtenerTecla();
    }

    void mostrarSeleccionNiveles() const {
        UtilidadesConsola::limpiarPantalla();
        std::cout << "1. Bosque de Jesse\n2. Desfiladero de Lukas\n3. Redencion de Ivor\n";

        ConsoleKey opcion = UtilidadesConsola::obtenerTecla();
        if (opcion == ConsoleKey::D1) Nivel1::iniciar();
        else if (opcion == ConsoleKey::D2) Nivel2::iniciar();
        else if (opcion == ConsoleKey::D3) Nivel3::iniciar();
    }

    void mostrarCreditos() const {
        UtilidadesConsola::limpiarPantalla();
        std::cout << "JESSE'S ADVENTURES\n\n";
        std::cout << "Hans J. Velasco\n";
        std::cout << "Stephen S. Barbaran\n";
        std::cout << "Fabritzio M. Sierra\n\n";
        std::cout << "Presiona una tecla para volver...";
        UtilidadesConsola::obtenerTecla();
    }

public:
    void ejecutar() {
        MenuPrincipal menu;
        bool salir = false;

        while (!salir) {
            OpcionMenu opcion = menu.ejecutar();

            switch (opcion) {
            case OpcionMenu::INICIO:
                Nivel1::iniciar();
                break;
            case OpcionMenu::TUTORIAL:
                mostrarTutorial();
                break;
            case OpcionMenu::NIVELES:
                mostrarSeleccionNiveles();
                break;
            case OpcionMenu::CREDITOS:
                mostrarCreditos();
                break;
            }
        }
    }
};
