#include "Bloco.h"

Bloco::Bloco(string ds, string hi, string du, string ti): diasemana(ds), horainicio(hi), duracao(du), tipo(ti) {}

string Bloco::getDiaSemana() const{
    return diasemana;
}
string Bloco::getHoraInicio() const{
    return horainicio;
}
string Bloco::getDuracao() const{
    return duracao;
}
string Bloco::getTipo() const{
    return tipo;
}

ostream& operator<<(ostream& os, const Bloco& bloco)
{
    os << bloco.diasemana << " - " << "From " << bloco.horainicio << " to " << bloco.getHoraFim() << " - " << bloco.tipo;
    return os;
}

string Bloco::getHoraFim() const{
    int hi = stoi(horainicio);
    int du = stoi(duracao);
    return to_string(hi + du );

}