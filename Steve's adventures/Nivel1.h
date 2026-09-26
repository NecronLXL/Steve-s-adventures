#pragma once
#include "GestorNivel.h"
#include "DisenoPersonajes.h"
using namespace System;

namespace Nivel1 {

    const int LIMITE_IZQUIERDO = 1;
    const int LIMITE_DERECHO = 66;
    const int LIMITE_SUPERIOR = 2;
    const int LIMITE_INFERIOR = 17;
    const int LIMITE_MAPAS = 3;

    void generarTerreno(GestorNivel& gestor, Random^ generadorAleatorio) {
        gestor.limpiarEntidades();

        int cantidadArboles = 6;
        for (int i = 0; i < cantidadArboles; i++) {
            int x = generadorAleatorio->Next(LIMITE_IZQUIERDO + 1, LIMITE_DERECHO - 1);
            int y = generadorAleatorio->Next(LIMITE_SUPERIOR + 1, LIMITE_INFERIOR - 1);
            gestor.agregarEntidad(new Arbol(x, y));
        }

        int cantidadRocas = 4;
        for (int i = 0; i < cantidadRocas; i++) {
            int x = generadorAleatorio->Next(LIMITE_IZQUIERDO, LIMITE_DERECHO);
            int y = generadorAleatorio->Next(LIMITE_SUPERIOR, LIMITE_INFERIOR);
            gestor.agregarEntidad(new Roca(x, y));
        }

        int centroLagoX = generadorAleatorio->Next(LIMITE_IZQUIERDO + 3, LIMITE_DERECHO - 3);
        int centroLagoY = generadorAleatorio->Next(LIMITE_SUPERIOR + 2, LIMITE_INFERIOR - 2);

        gestor.agregarEntidad(new Lago(centroLagoX, centroLagoY));
        gestor.agregarEntidad(new Lago(centroLagoX + 1, centroLagoY));
        gestor.agregarEntidad(new Lago(centroLagoX, centroLagoY + 1));
        gestor.agregarEntidad(new Lago(centroLagoX + 1, centroLagoY + 1));
        gestor.agregarEntidad(new Lago(centroLagoX - 1, centroLagoY));
    }

    void fase1_1(GestorNivel& gestor, Jugador* jugador) {
        Console::BackgroundColor = ConsoleColor::DarkGreen;

        Random^ generadorAleatorio = gcnew Random();
        int mapasGenerados = 0;
        generarTerreno(gestor, generadorAleatorio);

        bool salir = false;
        while (!salir) {
            gestor.dibujarNivel();
            jugador->dibujar();

            ConsoleKey tecla = UtilidadesConsola::obtenerTecla();

            int nuevoX = jugador->obtenerX();
            int nuevoY = jugador->obtenerY();

            if (tecla == ConsoleKey::UpArrow) nuevoY = nuevoY - 1;
            else if (tecla == ConsoleKey::DownArrow) nuevoY = nuevoY + 1;
            else if (tecla == ConsoleKey::LeftArrow) nuevoX = nuevoX - 1;
            else if (tecla == ConsoleKey::RightArrow) nuevoX = nuevoX + 1;
            else if (tecla == ConsoleKey::Escape) salir = true;

            if (!salir) {
                bool fueraDeLimite = (nuevoX < LIMITE_IZQUIERDO || nuevoX > LIMITE_DERECHO || nuevoY < LIMITE_SUPERIOR || nuevoY > LIMITE_INFERIOR);

                if (fueraDeLimite) {
                    if (mapasGenerados < LIMITE_MAPAS) {
                        mapasGenerados = mapasGenerados + 1;
                        generarTerreno(gestor, generadorAleatorio);
                        jugador->establecerPosicion(34, 9);
                    }
                    else {
                        UtilidadesConsola::establecerColor(ConsoleColor::Blue);
                        UtilidadesConsola::posicionarCursor(15, 19);
                        Console::Write("este es el limite.. mejor intentare volver...");
                        UtilidadesConsola::establecerColor(ConsoleColor::Gray);
                        UtilidadesConsola::obtenerTecla();
                    }
                }
                else {
                    Entidad* obstaculo = gestor.obtenerEntidadEn(nuevoX, nuevoY);
                    if (obstaculo == nullptr) {
                        jugador->mover(nuevoX - jugador->obtenerX(), nuevoY - jugador->obtenerY());
                    }
                }
            }
        }

        Console::BackgroundColor = ConsoleColor::Black;
    }

    void fase1_2(GestorNivel& gestor, Jugador* jugador) {
    }

    void iniciar() {
        GestorNivel gestor(20, 20);
        Jugador* jesse = new Jugador(34, 9, "Jessee");

        fase1_1(gestor, jesse);
        fase1_2(gestor, jesse);

        delete jesse;
    }
}

