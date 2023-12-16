#include <iostream>
#include <stdlib.h>
#include <windows.h>
using namespace std;

typedef struct{
    string horario;
    string paciente;
    string tipo;
    char retorno;
}Agenda;

typedef struct{
    string diaSemana;
    string data;
    Agenda agendaDia[7];
    int numeroAgendados;
}Semana;
bool ehBissexto(int ano);

int compararDataHora(string , string );
string calcularProximaData(int& , int& , int& );
void ordenarVetorAgenda(Agenda [], int , int );
void ordenarSubVetores(Agenda [], int , int , int );
void novaConsulta(Semana []);
bool validaInt(string);
bool validaString(string);
bool validaData(int , int, int );
bool validaHorario(int, int);
int diaSemana(int, int, int);
void novaSemana(Semana [], int &);
void relatorioSemanal(Semana []);
void relatorioDia(Semana[]);
void relatorioSemanalRecursivo(Semana [], int );
void relatorioDiaRecursivo(Semana [], int , string ) ;
void exclusaoHorarioRecursivo(Semana [], int, string, string, int);
void exclusaoConsultaRecursiva(Semana [], int , string , string );
void moverElementoRecursivo(Agenda [], int , int );
void exclusaoConsulta(Semana semana[]);
bool continuar(string);
void agendadosRecursivo(Semana, Agenda [], int , int );
bool validaDataSistema(string, int &, int &, int & );
bool validaHoraSistema(string , int & , int & );
bool procuraData(Semana [], string );
bool procuraHora(Semana [],string , int, int);
bool procuraHoraExclui(Semana [], string, string);
void logo();
bool verificaDisponibilidade(Semana [], string);
int main()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX fonte;

    fonte.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    fonte.nFont = 0;
    fonte.dwFontSize.X = 10; // Largura da fonte
    fonte.dwFontSize.Y = 20; // Altura da fonte
    lstrcpyW(fonte.FaceName, L"Consolas"); // Nome da fonte
    fonte.FontFamily = 54;
    fonte.FontWeight = 400;

    if (!SetCurrentConsoleFontEx(h, 0, &fonte)) {
        printf("SetCurrentConsoleFontEx () falhou: %d\\n", GetLastError());
        return -1;
    }
    system("color 1F");
    setlocale(LC_ALL, "portuguese");
    string respostaStr,d,pesquisa, enter;
    Semana semana[5];
    int tamanho = 0;
    bool semanaRegistrada = false;
    while (true){
        string respostaStr;

do {
    system("clear || cls");
    logo();
    cout << "============== Menu Principal ==============" << endl;
    cout << "|      1. Inicialização de nova semana     |" << endl;
    cout << "|      2. Inclusão de nova consulta        |" << endl;
    cout << "|      3. Exclusão de consulta             |" << endl;
    cout << "|      4. Relatório do dia                 |" << endl;
    cout << "|      5. Relatório Semanal                |" << endl;
    cout << "|      0. Sair                             |" << endl;
    cout << "============================================" << endl;
    cout << "Escolha Uma Opção: ";
    cout << endl;

    getline(cin, respostaStr);

    if(respostaStr.size() == 1){
        if(isdigit(respostaStr[0])){
            if(validaInt(respostaStr)){
                if(stoi(respostaStr) >= 0 && stoi(respostaStr) <= 5){
                    break;
                }
            }
        }
    }
    do{
        cout << "Digite uma opção válida" << endl;
        cout << "Aperte enter para continuar: "<<endl;
        getline(cin, enter);
        if(enter.empty()){
            break;
        }
    }while(true);

} while (true);

int resposta = stoi(respostaStr);
        switch (resposta)
        {
        case 1:
            system("clear || cls");
            novaSemana(semana, tamanho);
            semanaRegistrada = true;
            break;
        case 2:
            system("clear || cls");
            if(semanaRegistrada){
                novaConsulta(semana);
            }else{
                cout<<"você precisa registrar uma semana!!"<<endl;
            }

            break;
        case 3:
            system("clear || cls");
            if(semanaRegistrada){
                exclusaoConsulta(semana);
            }else{
                cout<<"você precisa registrar uma semana!!"<<endl;
            }
            break;
        case 4:
            system("clear || cls");
            if(semanaRegistrada){
                relatorioDia(semana);
            }else{
                cout<<"você precisa registrar uma semana!!"<<endl;
            }
            break;
        case 5:
            system("clear || cls");
            if(semanaRegistrada){
                relatorioSemanalRecursivo(semana, 0);
            }else{
                cout<<"você precisa registrar uma semana!!"<<endl;
            }
            break;
        case 0:
            cout << "Saindo do programa. Até logo!" << endl;
            return 0;
        default:
            cout << "Opção inválida. Tente novamente." << endl;
            break;
        }

          system("pause");
    }
    return 0;
}

bool validaString(string teste){
    if (teste != ""){
        for (int i = 0; i < teste.size(); i++){
            if (!isalpha(teste[i]) && teste[i] != ' '){
                return false;
            }
        }
    }
    else{
        return false;
    }
    return true;
}

bool validaInt(string teste){
    for (int i = 0; i < teste.size(); i++){
        if (isalpha(teste[i])){
            return false;
        }
        else if (i == 0){
            if (!isdigit(teste[0]) && teste[0] != '-')
            {
                return false;
            }
        }
        else if (!isdigit(teste[i])){
            return false;
        }
    }
    return true;
}

bool validaData(int dia, int mes, int ano) {
    if (ano < 0) {
        return false;
    }

    if (mes < 1 || mes > 12) {
        return false;
    }

    int diasNoMes;

    if (mes == 2) {
        if (ehBissexto(ano)) {
            diasNoMes = 29;
        } else {
            diasNoMes = 28;
        }
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        diasNoMes = 30;
    } else {
        diasNoMes = 31;
    }

    if (dia < 1 || dia > diasNoMes) {
        return false;
    }

    return true;
}
bool validaHorario(int hora, int minuto){
    if(hora > 7 && hora < 12){
        if(hora == 8 && minuto > 29 && minuto < 61){
            return true;
        }else if(hora == 12 && minuto == 0 ){
            return true;
        }else if(hora > 8 && hora < 12 && minuto >= 0 && minuto < 61){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}
int diaSemana(int mes, int ano, int dia){
   if(mes == 01 ){
        mes = 13;
        ano = ano - 1;
   }

   if(mes == 02 ){
   	mes = 14;
        ano = ano - 1;

   }

   int formula = dia + 2*mes + (3*(mes+1)/5) + ano + ano/4 - ano/100 + ano/400 + 2;
   int dia_semana = formula % 7;

   if (mes == 13){
   	 mes = 1;
   	 ano = ano+1;
   }
   if (mes == 14){
   	 mes = 2;
   	 ano = ano +1;
   }


   switch(dia_semana){
   	 case 0:

	        return 0;
	 break;

	 case 1:

		    return 1;
	 break;

	 case 2:

		    return 2;
	 break;

	 case 3:

			return 3;
	 break;

	 case 4:

		 	return 4;
	 break;

	 case 5:

			return 5;
	 break;

	 case 6:

		   	return 6;
	 break;

   }

}

int compararDataHora(string dataHora1, string dataHora2) {

    string hora1 = dataHora1.substr(0);
    string hora2 = dataHora2.substr(0);

    if (hora1 < hora2) {
        return -1;
    } else if (hora1 > hora2) {
        return 1;
    }

    return 0;
}

void ordenarSubVetores(Agenda dia[], int esquerda, int meio, int direita) {
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    Agenda L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = dia[esquerda + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = dia[meio + 1 + j];
    }

    int i = 0, j = 0, k = esquerda;
    while (i < n1 && j < n2) {
        if (compararDataHora(L[i].horario, R[j].horario) <= 0) {
            dia[k] = L[i];
            i++;
        } else {
            dia[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        dia[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        dia[k] = R[j];
        j++;
        k++;
    }
}

void ordenarVetorAgenda(Agenda dia[], int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        ordenarVetorAgenda(dia, esquerda, meio);
        ordenarVetorAgenda(dia, meio + 1, direita);

        ordenarSubVetores(dia, esquerda, meio, direita);
    }
}

void ordenarVetorAgenda(Agenda dia[], int n) {
    ordenarVetorAgenda(dia, 0, n - 1);
}


void novaSemana(Semana semana[], int &tamanho) {
    logo();
    int dia, mes, ano;
    string data;
    bool comeco = false;

    do{
        do{
            cout << "Data inicial da semana (dd/mm/aaaa): ";
            getline(cin, data);
        }while(!validaDataSistema(data, dia, mes, ano));
        if(diaSemana(mes, ano, dia) != 2){
            cout<< "Esse dia não é um dia de começo de semana"<<endl;
        }else{
            comeco = true;
            break;
        }
    }while(true);

    for (int i = 0; i < 5; i++) {
        semana[i].data = data;
        semana[i].diaSemana = diaSemana(mes, ano, dia);
        semana[i].numeroAgendados = 0;
        tamanho += 1;
        data = calcularProximaData(dia, mes, ano);
    }
    cout<< "Semana registrada com sucesso!!"<<endl;
}


void novaConsulta(Semana semana[]){
    system("clear || cls");
    logo();
    int dia, mes, ano, hora, minuto;
    string data, horario;
    do{
        do{
            do{
                cout << "Data da consulta (dd/mm/aaaa): ";
                getline(cin, data);
            }while(!validaDataSistema(data, dia, mes, ano));
        }while(!procuraData(semana, data));
        if(!verificaDisponibilidade(semana, data)){
            cout << "Não existe mais horario para consultas nesse dia, por favor seleciona outro dia" << endl;
            if(!continuar("Consultando outro dia? ")){
                main();
            }else{
                novaConsulta(semana);
            }
        }
    }while(!verificaDisponibilidade(semana, data));


    do{
        do{
            cout << "Horário da Consulta (hh:mm): ";
            getline(cin, horario);
        }while(!validaHoraSistema(horario, hora, minuto));
    }while(!procuraHora(semana,data, hora, minuto));


    for(int i = 0; i < 5; i++){
        if(semana[i].data == data){
           string paciente, tipo;
            char retorno;
            do{
                cout << "Nome: ";
                getline(cin, paciente);
            }while(!validaString(paciente));
            do{
                cout << "Tipo (particular ou convenio): ";
                getline(cin, tipo);
            }while(!validaString(tipo) || (tipo != "particular" && tipo != "convenio"));
            do{
                cout << "Retorno (S/(Sim) Ou N/(Não)): ";
                string charAux;
                getline(cin, charAux);
                if(charAux.size() == 1){
                    if(toupper(charAux[0]) == 'S' || toupper(charAux[0]) == 'N'){
                        retorno = charAux[0];
                        break;
                    }else{
                        cout << "Digite s ou n" << endl;
                    }
                }else{
                    cout << "Digite s ou n" << endl;
                }
            }while(true);
             Agenda a;
             a.horario = horario;
             a.paciente = paciente;
             a.tipo = tipo;
             a.retorno = retorno;
             semana[i].agendaDia[(semana[i].numeroAgendados)] = a;
             semana[i].numeroAgendados += 1;
        }
    }

}


bool ehBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}


string calcularProximaData(int& dia, int& mes, int& ano) {
    int diasNoMes;

    if (mes == 2) {

        if (ehBissexto(ano)) {
            diasNoMes = 29;
        } else {
            diasNoMes = 28;
        }
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        diasNoMes = 30;
    } else {
        diasNoMes = 31;
    }

    dia++;
    if (dia > diasNoMes) {
        dia = 1;
        mes++;
        if (mes > 12) {
            mes = 1;
            ano++;
        }
    }

    string novaData = to_string(dia) + "/" + to_string(mes) + "/" + to_string(ano);
    return novaData;
}
void exclusaoConsulta(Semana semana[]){
    system("clear || cls");
    logo();
    int dia, mes, ano, hora, minuto;
    string data, horario;

    do{
        do{
            cout << "Data da consulta a ser excluida (dd/mm/aaaa): ";
            getline(cin, data);
        }while(!validaDataSistema(data, dia, mes, ano));
    }while(!procuraData(semana, data));
    do{
        cout << "Horário da Consulta a ser excluida (hh:mm): ";
        getline(cin, horario);
    }while(!validaHoraSistema(horario, hora, minuto));
    if(procuraHoraExclui(semana, horario, data)){
        exclusaoConsultaRecursiva(semana, 0,  data,  horario);
    }else{
        if(continuar("a exclusão")){
            exclusaoConsulta(semana);
        }
    }

}

void relatorioDia(Semana semana[]){
    system("clear || cls");
    logo();
    string data;
    bool teste = false;
    int dia, mes, ano;

    do{
        do{
            cout << "Relatorio do dia (dd/mm/aaaa): ";
            getline(cin, data);
        }while(!validaDataSistema(data, dia, mes, ano));
    }while(!procuraData(semana, data));

    relatorioDiaRecursivo(semana, 0, data);

    if(!continuar("Relatorio Dia")){

    }else{
        relatorioDia(semana);
    }
}

bool continuar(string teste){
    do{
        string resposta;
        cout << "Deseja continuar " << teste << " ? Sim(s) ou Nao(n): ";
        getline(cin, resposta);
        if(resposta.size() == 1){
           if(toupper(resposta[0]) == 'S'){
                return true;
            }else if(toupper(resposta[0]) == 'N'){
                return false;
            }else{
                cout << "Por favor digite S ou N" << endl;
            }
        }else{
            cout << "Por favor digite S ou N" << endl;
        }

    }while(true);
}

void exclusaoConsultaRecursiva(Semana semana[], int i, string data, string horario) {
    if (i < 5) {
        if (semana[i].data == data) {
            int j = 0;
            exclusaoHorarioRecursivo(semana, i, data, horario, j);
        } else {
            exclusaoConsultaRecursiva(semana, i + 1, data, horario);
        }
    } else {
        cout << "Não existe consulta nessa data ou horario para exclusão" << endl;
    }
}

void moverElementoRecursivo(Agenda agendaDia[], int k, int numeroAgendados) {
    if (k < numeroAgendados - 1) {
        agendaDia[k] = agendaDia[k + 1];
        moverElementoRecursivo(agendaDia, k + 1, numeroAgendados);
    }
}

void exclusaoHorarioRecursivo(Semana semana[], int i, string data, string horario, int j) {
    if (j < semana[i].numeroAgendados) {
        if (semana[i].agendaDia[j].horario == horario) {
            moverElementoRecursivo(semana[i].agendaDia, j, semana[i].numeroAgendados);
            semana[i].numeroAgendados--;
            return;
        }
        exclusaoHorarioRecursivo(semana, i, data, horario, j + 1);
    } else {
        exclusaoConsultaRecursiva(semana, i + 1, data, horario);
    }
}



void relatorioDiaRecursivo(Semana semana[], int i, string data) {
    if (i < 5) {
        if (semana[i].data == data) {
            cout << semana[i].data << endl;
            switch (i){
                case 0:
                    cout << "2af:" << endl;
                    break;
                case 1:
                    cout << "3af:" << endl;
                    break;
                case 2:
                    cout << "4af:" << endl;
                    break;
                case 3:
                    cout << "5af:" << endl;
                    break;
                case 4:
                    cout << "6af:" << endl;
                    break;
            }
            if(semana[i].numeroAgendados == 0){
                cout << "Não a consultas nesse dia" << endl;
            }else{
                 ordenarVetorAgenda(semana[i].agendaDia, semana[i].numeroAgendados);
                agendadosRecursivo(semana[i], semana[i].agendaDia, 0, semana[i].numeroAgendados);
            }
            return;
        }
        relatorioDiaRecursivo(semana, i + 1, data);
    } else {
        cout << "Essa data não existe na Agenda" << endl;
    }
}
void agendadosRecursivo(Semana semana, Agenda a[], int i, int tamanho) {
    if (i < tamanho) {
        cout << semana.agendaDia[i].horario << endl;
        cout << semana.agendaDia[i].paciente << endl;
        cout << semana.agendaDia[i].tipo << endl;
        cout << semana.agendaDia[i].retorno << endl;
        cout<< "-------------------------"<<endl;
        return agendadosRecursivo(semana, a, i + 1, tamanho);
    }
}
void relatorioSemanalRecursivo(Semana semana[], int i) {

    if (i < 5) {
            if(i == 0){
                logo();
            }
            cout << semana[i].data << endl;
            switch (i){
                case 0:
                    cout << "2af:" << endl;
                    break;
                case 1:
                    cout << "3af:" << endl;
                    break;
                case 2:
                    cout << "4af:" << endl;
                    break;
                case 3:
                    cout << "5af:" << endl;
                    break;
                case 4:
                    cout << "6af:" << endl;
                    break;
            }
            if(semana[i].numeroAgendados == 0){
                cout << "Não a consultas nesse dia" << endl;
                cout<< endl;
                return relatorioSemanalRecursivo(semana, i + 1);
            }else{
                ordenarVetorAgenda(semana[i].agendaDia, semana[i].numeroAgendados);
                agendadosRecursivo(semana[i], semana[i].agendaDia, 0, semana[i].numeroAgendados);
                return relatorioSemanalRecursivo(semana, i + 1);
            }

    }
}

bool validaDataSistema(string data, int & dia, int & mes, int & ano){
    if (data.size() == 10) {
        string d = data.substr(0, 2);
        string m = data.substr(3, 2);
        string a = data.substr(6, 4);
        if(validaInt(d) && validaInt(m) && validaInt(a) && data[2] == '/' && data[5] == '/'){
            int diaAux = stoi(d);
            int mesAux = stoi(m);
            int anoAux = stoi(a);
            if(validaData(diaAux, mesAux, anoAux)){
                dia = diaAux;
                mes = mesAux;
                ano = anoAux;
                return true;
            }else{
                cout << "Dia Invalido" << endl;
                return false;
            }

        }else{
            cout << "Dia Invalido" << endl;
            return false;
        }
    }else{
        cout << "Dia Invalido" << endl;
        return false;
    }
}

bool validaHoraSistema(string horario, int & hora, int & minuto){
    if (horario.size() == 5) {
        string h = horario.substr(0, 2);
        string m = horario.substr(3, 2);
        if(validaInt(h) && validaInt(m) && horario[2] == ':'){
            int horaAux = stoi(h);
            int minutoAux = stoi(m);
            if(validaHorario(horaAux, minutoAux)){
                hora = horaAux;
                minuto = minutoAux;
                return true;
            }else{
                cout << "Consultas das 08:30 - 12:00" << endl;
                return false;
            }

        }else{
            cout << "Hora Invalido" << endl;
            return false;
        }
    }else{
        cout << "Hora Invalido" << endl;
        return false;
    }
}

bool procuraData(Semana semana[], string data){
    bool dataBool = false, horaBool = false;
    for(int i = 0; i < 5; i++){
        if(semana[i].data == data){
                return true;
        }
    }
    if(!dataBool){
        cout << "Data não pertence a semana, semana: " << semana[0].data << " - " << semana[4].data << endl;
        return false;
    }
}

bool procuraHora(Semana semana[], string data, int hora, int minuto){
    for(int i = 0; i < 5; i++){
        if(semana[i].data == data){
            for(int j = 0; j < semana[i].numeroAgendados; j++ ){
                string horaAux = semana[i].agendaDia[j].horario.substr(0, 2);
                string minAux = semana[i].agendaDia[j].horario.substr(3, 5);

                int horario = (hora*60 + minuto) - (stoi(horaAux)*60 + stoi(minAux));
                if(horario < 30 && horario > -30){
                    cout << "Horário indisponível" << endl;
                    return false;
                }
            }
        }

    }
    return true;
}

bool procuraHoraExclui(Semana semana[], string hora, string data){
    for(int i = 0; i < 5; i++){
        if(semana[i].data == data){
            for(int j = 0; j < semana[i].numeroAgendados; j++ ){

                if(hora == semana[i].agendaDia[j].horario){
                    return true;
                }
            }
        }

    }
    cout << "Não existe consulta nesse horario para excluir" << endl;
    return false;
}

void logo(){
    cout << "  ____ _ _       _       \n";
    cout << " / ___| (_)_ __ (_)_ __  \n";
    cout << "| |   | | | '_ \\| | '_ \\ \n";
    cout << "| |___| | | | | | | | | |\n";
    cout << "|_____|_|_|_| |_|_|_| |_|\n";
}

bool verificaDisponibilidade(Semana semana[], string data){
    for(int i = 0; i < 5; i++){
        if(semana[i].data == data){
            if(semana[i].numeroAgendados == 7){
                return false;
            }
        }
    }
    return true;
}
