#pragma once
#include "UtilidadesConsola.h"
#include <cstring>
using namespace System;

class Entidad {
protected:
    int posicionX;
    int posicionY;
    char simbolo;

public:
    Entidad(int posicionX, int posicionY, char simbolo) : posicionX(posicionX), posicionY(posicionY), simbolo(simbolo) {}
    virtual ~Entidad() {}

    virtual void actualizar() = 0;

    virtual void dibujar() const {
        UtilidadesConsola::posicionarCursor(posicionX, posicionY);
        Console::Write(simbolo);
    }

    virtual bool colisionaCon(const Entidad* otra) const {
        if (otra == nullptr) return false;
        return (posicionX == otra->obtenerX()) && (posicionY == otra->obtenerY());
    }

    int obtenerX() const { return posicionX; }
    int obtenerY() const { return posicionY; }
    char obtenerSimbolo() const { return simbolo; }
};

class Jugador : public Entidad {
private:
    char* nombre;

public:
    Jugador(int posicionX, int posicionY, const char* nombre) : Entidad(posicionX, posicionY, '@') {
        this->nombre = new char[strlen(nombre) + 1];
        strcpy_s(this->nombre, strlen(nombre) + 1, nombre);
    }

    ~Jugador() {
        delete[] nombre;
    }

    void actualizar() override {
    }

    void dibujar() const override {
        Entidad::dibujar();
    }

    void mover(int desplazamientoX, int desplazamientoY) {
    }

    void interactuar(Entidad* objetivo) {
    }

    const char* obtenerNombre() const { return nombre; }
};

class Trampa : public Entidad {
private:
    bool activada;
    int dano;

public:
    Trampa(int posicionX, int posicionY, int dano) : Entidad(posicionX, posicionY, 'X'), activada(false), dano(dano) {}

    void actualizar() override {
    }

    void dibujar() const override {
        Entidad::dibujar();
    }

    void activar() {
        activada = true;
    }

    bool estaActivada() const { return activada; }
};

class TormentaWither : public Entidad {
private:
    int salud;
    int poderDestruccion;

public:
    TormentaWither(int posicionX, int posicionY, int salud)
        : Entidad(posicionX, posicionY, 'W'), salud(salud), poderDestruccion(10) {}

    void actualizar() override {
    }

    void dibujar() const override {
        Entidad::dibujar();
    }

    void atacar(Entidad* objetivo) {
    }

    bool estaDerrotado() const { return salud <= 0; }
};
