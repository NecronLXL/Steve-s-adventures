#pragma once
#include "DisenoPersonajes.h"
#include "UtilidadesConsola.h"

class GestorNivel {
private:
    static const int MAXIMO_ENTIDADES = 50;

    Entidad** entidades;
    int filas;
    int columnas;
    int cantidadEntidades;

public:
    GestorNivel(int filas, int columnas) : filas(filas), columnas(columnas), cantidadEntidades(0) {
        entidades = new Entidad*[MAXIMO_ENTIDADES];
    }

    ~GestorNivel() {
        limpiarEntidades();
        delete[] entidades;
    }

    void agregarEntidad(Entidad* entidad) {
        if (entidad == nullptr || cantidadEntidades >= MAXIMO_ENTIDADES) return;
        entidades[cantidadEntidades] = entidad;
        cantidadEntidades++;
    }

    void eliminarEntidad(Entidad* entidad) {
        for (int i = 0; i < cantidadEntidades; i++) {
            if (entidades[i] == entidad) {
                delete entidades[i];
                for (int j = i; j < cantidadEntidades - 1; j++) {
                    entidades[j] = entidades[j + 1];
                }
                cantidadEntidades--;
                return;
            }
        }
    }

    void actualizarNivel() {
        for (int i = 0; i < cantidadEntidades; i++) entidades[i]->actualizar();
    }

    void dibujarNivel() const {
        UtilidadesConsola::limpiarPantalla();
        for (int i = 0; i < cantidadEntidades; i++) entidades[i]->dibujar();
    }

    void verificarColisiones() {
        for (int i = 0; i < cantidadEntidades; i++) {
            for (int j = i + 1; j < cantidadEntidades; j++) {
                if (entidades[i]->colisionaCon(entidades[j])) {
                }
            }
        }
    }

    Entidad* obtenerEntidadEn(int x, int y) const {
        for (int i = 0; i < cantidadEntidades; i++) {
            if (entidades[i]->obtenerX() == x && entidades[i]->obtenerY() == y) return entidades[i];
        }
        return nullptr;
    }

    void limpiarEntidades() {
        for (int i = 0; i < cantidadEntidades; i++) {
            delete entidades[i];
            entidades[i] = nullptr;
        }
        cantidadEntidades = 0;
    }
};
