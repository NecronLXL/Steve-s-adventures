#pragma once
#include "GestorNivel.h"
#include "DisenoPersonajes.h" 

namespace Nivel3 {

    void fase3_1(GestorNivel& gestor) {
    }

    void fase3_2(GestorNivel& gestor) {
    }

    void iniciar() {
        GestorNivel gestor(20, 20);
        Jugador* ivor = new Jugador(0, 0, "Ivorr");
        TormentaWither* wither = new TormentaWither(10, 10, 100);
        gestor.agregarEntidad(ivor);
        gestor.agregarEntidad(wither);

        fase3_1(gestor);
        fase3_2(gestor);
    }
}
