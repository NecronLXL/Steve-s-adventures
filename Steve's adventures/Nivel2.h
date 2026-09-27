#pragma once
#include "GestorNivel.h"
#include "DisenoPersonajes.h"

namespace Nivel2 {

    void fase2_1(GestorNivel& gestor) {
    }

    void fase2_2(GestorNivel& gestor) {
    }

    void iniciar() {
        GestorNivel gestor(20, 20);
        Jugador* lukas = new Jugador(0, 0, "Lukass");
        gestor.agregarEntidad(lukas);

        fase2_1(gestor);
        fase2_2(gestor);
    }
 }
