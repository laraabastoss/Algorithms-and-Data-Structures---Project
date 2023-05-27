#include "GestaoHorario.h"


set<Student> GestaoHorario::getEstudantes() const{
    return estudantes;
}

vector<TurmaH> GestaoHorario::getTurmas() const{
    return turmas;
}

list<UcTurma> GestaoHorario::getUcturmas() const{
    return ucturmas;
}

void GestaoHorario::lerFicheiros(std::string path){

    ifstream infile(path + "students_classes.csv");
    string line;
    Student estudanteatual("","");

    getline(infile,line); // Skip First Line

    // Ler students_classes.csv

    while(getline(infile,line)){

        bool adicionar = true;

        istringstream iss(line);
        string substring;
        vector<string> substrings{};

        while(getline(iss, substring, ',')){
            substrings.push_back(substring);
        }

        UcTurma uc(substrings[2],substrings[3]);

        if (estudanteatual.getCode() != substrings[0]){

            if (estudanteatual.getName() != ""){
                estudantes.insert(estudanteatual);
            }
            estudanteatual = Student(substrings[0],substrings[1]);
        }

        if (estudanteatual.getName() != ""){
            for (auto it = ucturmas.begin(); it != ucturmas.end(); it++){
                if (uc == *it){
                    it->setLotacao(it->getLotacao()+1);
                    adicionar = false;
                }
            }
            if (adicionar) ucturmas.push_back(uc);
            estudanteatual.addUcturma(uc);
        }

    }

    estudantes.insert(estudanteatual);

    ifstream infile2(path + "classes.csv");
    getline(infile2,line);
    int i = 0;

    while(getline(infile2,line)){

        istringstream iss(line);
        string substring;
        vector<string> substrings{};

        while(getline(iss, substring, ',')){
            substrings.push_back(substring);
        }

        bool add = true;
        UcTurma uc(substrings[1],substrings[0]);
        Bloco bloco(substrings[2], substrings[3], substrings[4],substrings[5]);
        TurmaH turma(uc);

        for(TurmaH &h : turmas){
            if ( h.getUcturma() == uc){
                h.addBlock(bloco);
                add = false;
                break;
            }
        }

        if (add){
            turma.addBlock(bloco);
            turmas.push_back(turma);
        }
    }

}

void GestaoHorario::guardarPedidos(string up, string uc, string classcode){


    UcTurma turma(uc,classcode);
    bool ver = true;

    for (UcTurma uct : ucturmas){
        if (uct == turma){
            turma = uct;
        }
    }

    Student estudante(up);


    auto it = estudantes.find(estudante);

    if (it != estudantes.end()){

        estudante = *it;
    }
    else{
        ver = false;
    }

    if (ver) {
        Pedido pedido(estudante,turma);
        pedido.setEstado("Em espera");
        listaespera.push(pedido);
    }


}

void GestaoHorario::processarPedidos(bool forcado) {
    int seconds, minutes, hours;

    if (!forcado) {
        time_t total_seconds = time(0);
        //getting values of seconds, minutes and hours
        struct tm *ct = localtime(&total_seconds);

        seconds = ct->tm_sec;
        minutes = ct->tm_min;
        hours = ct->tm_hour;
    }

    else { minutes = 0; hours = 0;}


    if (hours == 0 && minutes == 0) {
        while (listaespera.size() > 0) {
            Pedido pedido = listaespera.front();
            listaespera.pop();
            bool control = false;
            UcTurma antiga;

            auto it = estudantes.find(pedido.getStudent());
            Student estudante = *it;

            if(pedido.getUc().getCodeturma() == "possivel"){
                bool existe = false;
                for (UcTurma uct : estudante.getUcturma()){
                    if (uct.getCodeuc() == pedido.getUc().getCodeuc()){
                        existe = true;
                        break;
                    }
                }
                if (existe){
                    pedido.setEstado("Recusado - O aluno ja se encontra inscrito a esta cadeira");
                    listarecusados.push(pedido);
                    continue;
                }
                for (UcTurma uct : ucturmas){
                    if (uct.getCodeuc() == pedido.getUc().getCodeuc()) {
                        control = true;
                        break;
                    }
                }
                if (!control){
                    pedido.setEstado("Recusado - O codigo da uc a que o aluno se pretende inscrever nao e valido");
                    listarecusados.push(pedido);
                }


                bool p = false;
                for (UcTurma turma : ucturmas){
                    bool imp = false;
                    if (turma.getLotacao() >= 26) continue;
                    if (pedido.getUc().getCodeuc() == turma.getCodeuc()){
                        for (UcTurma &turma2 : ucturmas) {
                            if (!(turma2 == turma) && turma2.getCodeuc() == turma.getCodeuc()){
                                if (abs(turma2.getLotacao() - turma.getLotacao() + 1) > 4) {
                                    imp = true;
                                    break;
                                }
                            }
                        }
                    }
                    if (imp) {
                        break;
                    }

                    TurmaH turmah3 = TurmaH(turma);
                    for (TurmaH t: turmas) {
                        if (turmah3 == t) {
                            t.setUcTurma(turmah3.getUcturma());
                            turmah3 = t;
                            break;
                        }
                    }
                    list<Bloco> h_novaucturma = turmah3.getBlocos();

                    for (UcTurma uct: pedido.getStudent().getUcturma()) {
                        TurmaH turmah2 = TurmaH(uct);
                        for (TurmaH t: turmas){
                            if (turmah2 == t) {
                                turmah2 = t;
                            }
                        }
                        for (Bloco bloco: turmah2.getBlocos()) {
                            if (bloco.getTipo() == "T") continue;
                            for (Bloco bloco2: h_novaucturma) {
                                if (bloco2.getTipo() == "T") continue;
                                if (bloco.getDiaSemana() == bloco2.getDiaSemana() && (bloco.getHoraInicio() < bloco2.getHoraFim() || bloco2.getHoraInicio() < bloco.getHoraFim())) {
                                    imp = true;
                                }
                            }
                        }
                    }
                    if (imp) continue;

                    for (UcTurma &ucturma: ucturmas) {
                        if (ucturma == turma) {
                            ucturma.setLotacao(ucturma.getLotacao() + 1);
                        }
                    }

                    Student estudanteatual = pedido.getStudent();
                    UcTurma nova = turma;
                    estudanteatual.addUcturma(nova);
                    auto it = estudantes.find(estudanteatual);
                    estudantes.erase(it);
                    estudantes.insert(estudanteatual);
                    pedido.setEstado("Aceite");
                    listaceites.push(pedido);
                    p = true;
                    break;
                }
                if (!p) {
                    pedido.setEstado("Recusado - nao foi possivel inscrever o aluno em nenhuma das turmas da uc pretendida");
                    listarecusados.push(pedido);
                }
                continue;
            }

            else if (pedido.getUc().getCodeturma() == ""){
                bool existe = false;
                for (UcTurma uct : estudante.getUcturma()){
                    if (uct.getCodeuc() == pedido.getUc().getCodeuc()) {
                        antiga = uct;
                        existe = true;
                        break;
                    }
                }
                if (!existe){
                    pedido.setEstado("Recusado - O aluno nao se encontra inscrito na cadeira em questao");
                    listarecusados.push(pedido);
                }
                else {
                    for (UcTurma uct: ucturmas) {
                        if (uct.getCodeuc() == pedido.getUc().getCodeuc()) {
                            uct.setLotacao(uct.getLotacao() - 1);
                            break;
                        }
                    }
                    Student estudanteatual = pedido.getStudent();
                    estudanteatual.removeUcturma(antiga);
                    estudantes.erase(it);
                    estudantes.insert(estudanteatual);
                    pedido.setEstado("Aceite");
                    listaceites.push(pedido);
                }
                continue;
            }

            for (UcTurma uct : ucturmas){
                if (uct == pedido.getUc()) {
                    control = true;
                    break;
                }
            }
            if (!control){
                pedido.setEstado("Recusado - A turma indicada nao existe para a uc pretendida");
                listarecusados.push(pedido);
            }


            for (UcTurma uct: estudante.getUcturma()) {
                if (uct.getCodeuc() == pedido.getUc().getCodeuc()) {
                    antiga = uct;
                }
            }

            if(antiga.getCodeuc() == pedido.getUc().getCodeuc() && antiga.getCodeturma() == pedido.getUc().getCodeturma()){
                pedido.setEstado("Recusado - Na uc em questao o estudante ja se encontra inscrito na turma pretendida");
                listarecusados.push(pedido);
                control = false;
            }


            if (antiga.getCodeuc() == "") {
                pedido.setEstado("Recusado - O estudante nao esta inscrito nessa uc");
                listarecusados.push(pedido);
                control = false;
            }

            if (control) {
                for (UcTurma &turma: ucturmas) {
                    if (pedido.getUc() == turma) {
                        for (UcTurma &turma2: ucturmas) {
                            if (!(turma2 == turma) && !(turma2 == antiga) && turma2.getCodeuc() == turma.getCodeuc()) {
                                if (abs(turma2.getLotacao() - turma.getLotacao() + 1) > 4 ||
                                    abs(turma2.getLotacao() - antiga.getLotacao() - 1) > 4) {
                                    pedido.setEstado(
                                            "Recusado - A aceitacao do pedido cria desequilibrio nas turmas desta UC");
                                    listarecusados.push(pedido);
                                    control = false;
                                    break;

                                }
                            }
                            if (turma2 == antiga) {
                                if (abs(turma2.getLotacao() - 1 - turma.getLotacao() + 1) > 4) {
                                    pedido.setEstado(
                                            "Recusado - A aceitacao do pedido cria desequilibrio nas turmas desta UC.");
                                    listarecusados.push(pedido);
                                    control = false;
                                    break;
                                }
                            }
                        }
                        if (turma.getLotacao() >= 26) {
                            pedido.setEstado("Recusado - A turma nao possui vagas.");
                            listarecusados.push(pedido);
                            control = false;
                            break;
                        }
                    }
                }
            }

            if (control) {
                TurmaH turmah3 = TurmaH(pedido.getUc());
                for (TurmaH t: turmas) {
                    if (turmah3 == t) {
                        t.setUcTurma(turmah3.getUcturma());
                        turmah3 = t;
                        break;
                    }
                }
                list<Bloco> h_novaucturma = turmah3.getBlocos();
                for (UcTurma uct: pedido.getStudent().getUcturma()) {
                    if (uct.getCodeuc() != pedido.getUc().getCodeuc()) {
                        TurmaH turmah2 = TurmaH(uct);
                        for (TurmaH t: turmas) {
                            if (turmah2 == t) turmah2 = t;
                        }
                        for (Bloco bloco: turmah2.getBlocos()) {
                            if (bloco.getTipo() == "T") continue;
                            for (Bloco bloco2: h_novaucturma) {
                                if (bloco2.getTipo() == "T") continue;
                                if (bloco.getDiaSemana() == bloco2.getDiaSemana() &&
                                    (bloco.getHoraInicio() < bloco2.getHoraFim() ||
                                     bloco2.getHoraInicio() < bloco.getHoraFim())) {
                                    pedido.setEstado(
                                            "Recusado - A mudanca de turma não e compativel com o horario do aluno.");
                                    listarecusados.push(pedido);
                                    control = false;
                                    break;

                                }
                            }
                            if (!control) break;
                        }
                    }
                    if (!control) break;
                }
            }

            if (control) {
                for (UcTurma &ucturma: ucturmas) {
                    if (ucturma == antiga) {
                        ucturma.setLotacao(ucturma.getLotacao() - 1);
                    }

                    if (ucturma == pedido.getUc()) {
                        ucturma.setLotacao(ucturma.getLotacao() + 1);
                    }
                }

                Student estudanteatual = pedido.getStudent();
                estudanteatual.removeUcturma(antiga);
                UcTurma nova = pedido.getUc();
                estudanteatual.addUcturma(nova);
                auto it = estudantes.find(estudanteatual);
                estudantes.erase(it);
                estudantes.insert(estudanteatual);
                pedido.setEstado("Aceite");
                listaceites.push(pedido);

            }
        }
    }

}

Student GestaoHorario::findStudent(std::string up) const {
    Student temp(up);

    auto it = estudantes.find(temp);

    if (it != estudantes.end()){
        return *it;
    }
    else{

        return Student("");
    }
}

queue<Pedido> GestaoHorario::getListaespera() const {
    return listaespera;
}

queue<Pedido> GestaoHorario::getListarecusados() const {
    return listarecusados;
}

queue<Pedido> GestaoHorario::getListaaceites() const {
    return listaceites;
}

void GestaoHorario::listagem() const{
    ofstream File("student_classes.csv");
    File<<"StudentCode,StudentName,UcCode,ClassCode"<<endl;
    for (Student student: estudantes){
        for (UcTurma ucturma:student.getUcturma()){
            File<<student.getCode()<<","<<student.getName()<<","<<ucturma.getCodeuc()<<","<<ucturma.getCodeturma()<<endl;
        }
    }
}