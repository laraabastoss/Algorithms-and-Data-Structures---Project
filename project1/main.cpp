#include <string>
#include "GestaoHorario.h"

using namespace std;

int main() {

    std::map<int, string> uc_names;
    uc_names.insert(pair<int, string>(1, "Algebra Linear e Geometria Analitica"));
    uc_names.insert(pair<int, string>(2, "Analise Matematica I"));
    uc_names.insert(pair<int, string>(3, "Fundamentos da Programacao"));
    uc_names.insert(pair<int, string>(4, "Fundamentos de Sistemas Computacionais"));
    uc_names.insert(pair<int, string>(5, "Matematica Discreta"));
    uc_names.insert(pair<int, string>(6, "Arquitetura de Computadores"));
    uc_names.insert(pair<int, string>(7, "Analise Matematica II"));
    uc_names.insert(pair<int, string>(8, "Fisica I"));
    uc_names.insert(pair<int, string>(9, "Programacao"));
    uc_names.insert(pair<int, string>(10, "Teoria da Computacao"));
    uc_names.insert(pair<int, string>(11, "Algoritmos e Estruturas de Dados"));
    uc_names.insert(pair<int, string>(12, "Bases de Dados"));
    uc_names.insert(pair<int, string>(13, "Fisica II"));
    uc_names.insert(pair<int, string>(14, "Laboratorio de Desenho e Teste de Software"));
    uc_names.insert(pair<int, string>(15, "Sistemas Operativos"));
    uc_names.insert(pair<int, string>(16, "Desenho de Algoritmos"));
    uc_names.insert(pair<int, string>(17, "Engenharia de Software"));
    uc_names.insert(pair<int, string>(18, "Laboratorio de Computadores"));
    uc_names.insert(pair<int, string>(19, "Linguagens e Tecnologias Web"));
    uc_names.insert(pair<int, string>(20, "Metodos Estatisticos"));
    uc_names.insert(pair<int, string>(21, "Fundamentos de Seguranca Informatica"));
    uc_names.insert(pair<int, string>(22, "Interacao Pessoa Computador"));
    uc_names.insert(pair<int, string>(23, "Laboratorio de Bases de Dados e Aplicacoes Web"));
    uc_names.insert(pair<int, string>(24, "Programacao Funcional e em Logica"));
    uc_names.insert(pair<int, string>(25, "Redes de Computadores"));
    uc_names.insert(pair<int, string>(26, "Compiladores"));

    int seconds, minutes, hours;
    string str;

    GestaoHorario gestao;
    string path = "../CSV/";
    gestao.lerFicheiros(path);

    /// opens the terminal with the respective menu, each option will call the necessary functions
    ///
    /// O(n^3)

    string up,uccode,classcode;
    int opcao, opt;
    Student estudanteinvalido("");
    Student estudante;

    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
        mudar_estudante: ;
        cout << endl << "Insira o seu Up: ";
        cin >> up;
        if (gestao.findStudent(up) == estudanteinvalido) {
            cout << "Insira um Up valido" << endl;
            goto mudar_estudante;
        }
        else {
            estudante = gestao.findStudent(up);
        };

    terminal: ;
    while(true) {
        gestao.processarPedidos(false);
        estudante = gestao.findStudent(up);
        cout << "---------------------------------------------------------------------------------------------------------------------"
        << endl << "1 - Ver perfil do aluno " << endl << "2 - Pedidos " << endl<< "3 - Ver Turmas " << endl << "4 - Mudar de estudante" << endl << "5 - Sair" << endl << endl;
        cout << "Escolha uma opcao : ";
        cin >> opcao;
        cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
        cout << endl;
        switch (opcao) {
            case 1:
                cout << "Nome:" << estudante.getName() << endl << endl << "Numero UP:" << estudante.getCode() << endl
                     << endl;
                cout << endl << "-----------" << endl << "| Horario |" << endl << "-----------" << endl;
                for (UcTurma uc: estudante.getUcturma()) {
                    for (TurmaH th: gestao.getTurmas()) {
                        if (th.getUcturma() == uc) {
                            string uc_code = uc.getCodeuc();
                            auto it = uc_names.find(stoi(uc_code.substr(6)));
                            cout << endl << it->second << " - " << uc << " :" << endl;
                            for (Bloco b: th.getBlocos()) {
                                cout << b << endl;
                            }
                        }
                    }
                }
                cout << endl;
                gestao.processarPedidos(false);
                estudante = gestao.findStudent(up);
                break;
            case 2:
                cout
                        << "---------------------------------------------------------------------------------------------------------------------" << endl
                        << "1 - Inscrever nova uc" << endl
                        << "2 - Trocar de turma numa uc" << endl
                        << "3 - Trocar de turma em todas as ucs " << endl
                        << "4 - Anular uc" << endl
                        << "5 - Ver estado atual dos meus pedidos" << endl
                        << "6 - Tempo restante ate processar os pedidos" << endl
                        << "7 - Forcar o processo de pedidos" << endl << endl;
                cout << "Escolha uma opcao : ";
                cin >> opt;
                cout
                        << "---------------------------------------------------------------------------------------------------------------------"
                        << endl;
                cout << endl;
                switch (opt) {
                    case 1: {
                        cout << endl << "Insira agora os dados da uc a que se pretende inscrever" << endl
                        << "Codigo da Unidade Curricular:";
                        cin >> uccode;
                        gestao.guardarPedidos (up, uccode, "possivel");
                        gestao.processarPedidos(false);
                        estudante = gestao.findStudent(up);
                        goto terminal;
                    }

                    case 2: {
                        cout << endl << "Insira agora os dados para a nova turma para a qual pretende trocar" << endl
                        << "Codigo da Unidade Curricular:";
                        cin >> uccode;
                        cout << "Codigo da Turma: ";
                        cin >> classcode;
                        gestao.guardarPedidos(up, uccode, classcode);
                        gestao.processarPedidos(false);
                        estudante = gestao.findStudent(up);
                        goto terminal;
                    }
                    case 3:{
                        cout << endl << "Insira agora os dados para a nova turma para a qual pretende trocar" << endl;
                        cout << "Codigo da Turma: ";
                        cin >> classcode;
                        for (UcTurma uc : gestao.getUcturmas()){
                            if ( uc.getCodeturma() == classcode ){
                                gestao.guardarPedidos(up,uc.getCodeuc(),uc.getCodeturma());
                            }
                        }
                        gestao.processarPedidos(false);
                        estudante = gestao.findStudent(up);
                        goto terminal;
                    }
                    case 4: {
                        cout << endl << "Insira agora os dados da uc que pretende anular" << endl;
                        cout << "Codigo da Unidade Curricular: ";
                        cin >> uccode;
                        gestao.guardarPedidos(up, uccode, "");
                        gestao.processarPedidos(false);
                        estudante = gestao.findStudent(up);
                        goto terminal;
                    }

                    case 5: {
                        queue<Pedido> listaespera = gestao.getListaespera();
                        queue<Pedido> listarecusados = gestao.getListarecusados();
                        queue<Pedido> listaaceites = gestao.getListaaceites();
                        int i = 1;
                        while (!listaespera.empty()) {
                            Pedido pedido = listaespera.front();
                            if (pedido.getStudent() == estudante) {
                                if (pedido.getUc().getCodeturma() == ""){
                                    cout << "Pedido " << i << " - " << pedido.getEstado() << " - Anular cadeira "
                                         << pedido.getUc().getCodeuc() << endl;
                                }
                                else if (pedido.getUc().getCodeturma() == "possivel"){
                                    cout << "Pedido " << i << " - " << pedido.getEstado() << " - Inscrever na cadeira "
                                         << pedido.getUc().getCodeuc() << endl;
                                }
                                else {
                                    cout << "Pedido " << i << " - " << pedido.getEstado() << " - Mudar para turma "
                                         << pedido.getUc() << endl;
                                }
                                i++;
                            }
                            listaespera.pop();
                        }
                        while (!listarecusados.empty()) {
                            Pedido pedido = listarecusados.front();
                            if (pedido.getStudent() == estudante) {
                                if (pedido.getUc().getCodeturma() == ""){
                                    cout << "Pedido " << i << " - " << pedido.getEstado() << " - Anular cadeira "
                                         << pedido.getUc().getCodeuc() << endl;
                                }
                                else if (pedido.getUc().getCodeturma() == "possivel"){
                                    cout << "Pedido " << i << " - " << pedido.getEstado() << " - Inscrever na cadeira "
                                         << pedido.getUc().getCodeuc() << endl;
                                }
                                else {
                                    cout << "Pedido " << i << " - " << pedido.getEstado() << " - Mudar para turma "
                                         << pedido.getUc() << endl;
                                }
                                i++;
                            }
                            listarecusados.pop();
                        }
                        while (!listaaceites.empty()) {
                            Pedido pedido = listaaceites.front();
                            if (pedido.getStudent() == estudante) {
                                if (pedido.getUc().getCodeturma() == ""){
                                    cout << "Pedido " << i << " - " << pedido.getEstado() << " - Anular cadeira "
                                    << pedido.getUc().getCodeuc() << endl;
                                }
                                else if (pedido.getUc().getCodeturma() == "possivel"){
                                    cout << "Pedido " << i << " - " << pedido.getEstado() << " - Inscrever na cadeira "
                                         << pedido.getUc().getCodeuc() << endl;
                                }
                                else {
                                    cout << "Pedido " << i << " - " << pedido.getEstado() << " - Mudar para turma "
                                    << pedido.getUc() << endl;
                                }
                                i++;
                            }
                            listaaceites.pop();
                        }
                        gestao.processarPedidos(false);
                        estudante = gestao.findStudent(up);
                        goto terminal;
                    }
                    case 6: {
                        //storing total seconds
                        time_t total_seconds = time(0);

                        //getting values of seconds, minutes and hours
                        struct tm *ct = localtime(&total_seconds);

                        seconds = ct->tm_sec;
                        minutes = ct->tm_min;
                        hours = ct->tm_hour;

                        int totaltime = hours * 3600 + minutes * 60 + seconds;
                        int timeleft = 86400 - totaltime;

                        cout << "Tempo restante ate todos os pedidos serem processados - " << timeleft / 3600 << ":"
                             << (timeleft % 3600) / 60 << ":" << (timeleft % 3600) % 60 << endl << endl;
                        gestao.processarPedidos(false);
                        estudante = gestao.findStudent(up);
                        goto terminal;
                    }
                    case 7: {
                        gestao.processarPedidos(true);
                        estudante = gestao.findStudent(up);
                        gestao.listagem();
                        goto terminal;
                    }
                    default:
                        cout << "Insira uma opcao valida !!!" << endl;
                        gestao.processarPedidos(false);
                        estudante = gestao.findStudent(up);
                        goto terminal;
                }
            case 3: {
                cout << "Insira o codigo da uc: ";
                string uc, turma;
                cin >> uc;
                cout<<endl;
                cout << "Insira a turma: ";
                cin >> turma;
                cout<<endl;
                UcTurma ucturma= UcTurma(uc, turma);
                set<Student> alunosnaturma;
                for (Student student : gestao.getEstudantes()){
                    for (UcTurma uct : student.getUcturma()){
                        if (ucturma==uct){
                            alunosnaturma.insert(student);
                            break;
                        }
                    }
                }
                if (alunosnaturma.size()==0) {
                    cout<<"Nao ha alunos inscristos nesta turma nesta uc"<<endl;
                    gestao.processarPedidos(false);
                    estudante = gestao.findStudent(up);
                    goto terminal;
                }
                cout << "lotacao: " << alunosnaturma.size() << endl << endl;
                for (Student student : alunosnaturma){
                    cout<<student.getName()<<" - "<<student.getCode()<<endl;
                }
                for (TurmaH turmah : gestao.getTurmas()){
                    if (ucturma == turmah.getUcturma()){
                        cout << endl << "-----------" << endl << "| Horario |" << endl << "-----------" << endl;
                        string uc_code = ucturma.getCodeuc();
                        auto it = uc_names.find(stoi(uc_code.substr(6)));
                        cout << endl << it->second << " - " << uc << " :" << endl;
                        for (Bloco b: turmah.getBlocos()) {
                            cout << b << endl;
                        }
                        break;
                    }
                }
                gestao.processarPedidos(false);
                estudante = gestao.findStudent(up);
                goto terminal;
            }
            case 4:
                gestao.processarPedidos(false);
                estudante = gestao.findStudent(up);
                goto mudar_estudante;
            case 5:
                gestao.processarPedidos(false);
                estudante = gestao.findStudent(up);
                gestao.listagem();
                goto exit_loop;
            default:
                cout << "Insira uma opcao valida !!!" << endl;
                gestao.processarPedidos(false);
                estudante = gestao.findStudent(up);
                break;
        }
    }
    gestao.processarPedidos(false);
    estudante = gestao.findStudent(up);
    gestao.listagem();
    goto terminal;
    exit_loop: ;


    /// -----------------------------------------------------------------------
}
