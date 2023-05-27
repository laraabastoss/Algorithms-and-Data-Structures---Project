#include "UcTurma.h"

UcTurma::UcTurma(std::string cuc, std::string ct): codeuc(cuc), codeturma(ct) {}

string UcTurma::getCodeuc() const {
    return codeuc;
}

string UcTurma::getCodeturma() const {
    return codeturma;
}

int UcTurma::getLotacao() const {
    return lotacao;
}

void UcTurma::setLotacao(int a) {
    lotacao = a;
}


ostream& operator<<(ostream& os, const UcTurma& uc)
{
    os << uc.codeuc << "/" << uc.codeturma;
    return os;
}

bool UcTurma::operator<(const UcTurma &s) const {
    return codeuc < s.getCodeuc();
}
