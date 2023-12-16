#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

typedef struct{
    int codigo;
    char marcaModelo[50], placa[50];
    char situacao;
    char categoria;
    int quantidadeLocacoes;
}Veiculo;
typedef struct{
    char dataLocacao[50] , cpfCliente[50];
    int codigoVeiculo, quantidadeDias;
    bool situacao;
}Locacao;

Veiculo criaVeiculo();
bool validaInt(string);
bool validaString(string);
bool verificaPlaca(string&) ;
void insereVeiculo();
void verificaSeExiste();
void locacaoVeiculo();
Locacao criaLocacao(Veiculo);
bool validaData(string);
bool validaCpf(string);
bool ehBissexto(int);
bool comparaCpf(string , string );
int calcularDiferenca(string , string );
void cobranca(string , int , int );
void devolucaoVeiculo();
string adicionaDias(string , int );
void relatorio();
string cpfSemPontos(string );
string placaMaiuscula(string);
int main()
{
    setlocale(LC_ALL, "portuguese");
    string respostaStr,d,pesquisa, enter;

    verificaSeExiste();
    while (true){
        string respostaStr;

do {
    system("clear || cls");
    cout << "============== Menu Principal ==============" << endl;
    cout << "|      1. Inclusao de Veiculo              |" << endl;
    cout << "|      2. Locacao de Veiculo               |" << endl;
    cout << "|      3. Devolucao de Veiculo Locado      |" << endl;
    cout << "|      4. Relatorio                        |" << endl;
    cout << "|      0. Sair                             |" << endl;
    cout << "============================================" << endl;
    cout << "Escolha Uma Opcao: ";
    cout << endl;

    getline(cin, respostaStr);

    if(respostaStr.size() == 1){
        if(isdigit(respostaStr[0])){
            if(validaInt(respostaStr)){
                if(stoi(respostaStr) >= 0 && stoi(respostaStr) <= 4){
                    break;
                }
            }
        }
    }
    do{
        cout << "Digite uma opcao valida" << endl;
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
            insereVeiculo();
            cin.ignore();
            break;
        case 2:
            system("clear || cls");
            locacaoVeiculo();
            cin.ignore();
            break;
        case 3:
            system("clear || cls");
            devolucaoVeiculo();
            cin.ignore();
            break;
        case 4:
            system("clear || cls");
            relatorio();
            cin.ignore();
            break;
        case 0:
            cout << "Saindo do programa. Ate logo!" << endl;
            return 0;
        default:
            cout << "Opcao invalida. Tente novamente." << endl;
            break;
        }

          system("pause");
    }
    return 0;
}

bool validaInt(string teste){
    for (unsigned int i = 0; i < teste.size(); i++){
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
bool validaString(string teste){
    if (teste != ""){
        for (unsigned int i = 0; i < teste.size(); i++){
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

bool verificaPlaca(string& placa) {
    if (placa.size() == 7 || placa.size() == 8) {
        if (placa.size() == 8) {
            for (int i = 0; i < 3; ++i) {
                if (!isalpha(placa[i]) || !isupper(placa[i])) return false;
            }
            if (placa[3] != '-') return false;
            for (int i = 4; i < 8; ++i) {
                if (!isdigit(placa[i])) return false;
            }
            return true;
        }else {
            for (int i = 0; i < 3; ++i) {
                if (!isalpha(placa[i]) || !isupper(placa[i])) return false;
            }
            if (!isdigit(placa[3])) return false;
            if (!isalpha(placa[4]) || !isupper(placa[4])) return false;
            for (int i = 5; i < 7; ++i) {
                if (!isdigit(placa[i])) return false;
            }
            return true;
        }
    }
    return false;
}

void insereVeiculo(){
    fstream arq("FROTA.DAD", ios::binary | ios::in | ios::out);
    system("clear || cls");
    cout << "Caso Ja Exista Algum Veiculo Cadastrado Com essa Placa de Carro o Sistema Ira Barrar na hora de Finalizar" << endl;
    if(arq.is_open()){
        Veiculo vC = criaVeiculo();
        Veiculo vI;
        bool teste = true;
        bool primeiro = true;
        int c;
        while(arq.read((char*)(&vI), sizeof(Veiculo))){
            primeiro = false;
            c = vI.codigo;
            if(string(vI.placa) == string(vC.placa)){
                teste = false;
                break;
            }
        }

        if(teste){
            arq.clear();
            arq.seekp(0, ios::end);
            if(primeiro){
                vC.codigo = 1;
            }else{
                vC.codigo = c+1;
            }

            arq.write((const char*)(&vC), sizeof(Veiculo));
        }else{
            cout << "Ja existe Veiculo com essa placa cadastrado" << endl;
            string r;
            do{
                do{
                    cout << "Deseja R-Retornar ao menu ou C-Cadastrar outro veiculo: "; cin >> r; cout << endl;
                }while(r.size() != 1);
                r = toupper(r[0]);
            }while(r[0]!='R' && r[0]!='C');

            if(r[0] == 'C'){
                insereVeiculo();
            }
        }
    }else{
        cout << "Nao foi possivel abrir o arquivo"<<endl;
    }
    arq.close();
}

Veiculo criaVeiculo(){
    Veiculo v;
    string marcaModelo, placa;
    char categoria; //B, I ou S

    do{
        cout << "Digite a placa do Veiculo (formato antigo ou novo): "; cin >> placa; cout << endl;
        placa = placaMaiuscula(placa);
        if(!verificaPlaca(placa)){
            cout << "placa no formato errado, digite novamente: " << endl;
        }
    }while(!verificaPlaca(placa));

    cin.ignore();
    do{
        cout << "Digite a Marca-Modelo: "; getline(cin, marcaModelo); cout << endl;
        if(marcaModelo == "" || marcaModelo.size() < 2){
            cout << "Minimo 2 caracteres para o nome" << endl;
        }
    }while(marcaModelo == "" || marcaModelo.size() < 2);

    do{
        cout << "Qual categoria o Veiculo pertence B-Basico , I-Intermediario ou S-Super: "; cin >> categoria; cout << endl;
    }while(toupper(categoria) != 'B' && toupper(categoria) != 'I' && toupper(categoria) != 'S');
    cout << placaMaiuscula(placa) << endl;
    v.categoria = toupper(categoria);
    v.situacao = 'D';
    strcpy(v.marcaModelo, marcaModelo.c_str());
    strcpy(v.placa, placa.c_str());
    v.quantidadeLocacoes = 0;
    return v;
}


void verificaSeExiste(){
    fstream arq("FROTA.DAD", ios::in | ios::binary);
    fstream arqTxt("LOCADOS.TXT", ios::in | ios::out | ios::app);
    if(!arq.is_open()) {
        arq.open("FROTA.DAD", ios::out | ios::binary);
    }
    if(!arqTxt.is_open()) {
        arqTxt.open("c", ios::in | ios::out | ios::app);
    }
    arq.close();
    arqTxt.close();
}


void locacaoVeiculo(){
    fstream arq("FROTA.DAD", ios::binary | ios::in | ios::out);
    char categoria;
    bool teste = false;
    do{
        cout << "Digite a categoria do Veiculo a ser alocado: (S-Super, I-Intermediario, B-Basico): "; cin >> categoria; cout << endl;
        categoria = toupper(categoria);
        if(toupper(categoria)!='S' && toupper(categoria)!='I' && toupper(categoria)!='B'){
            cout << "Categoria Invalida" << endl;
        }
    }while(toupper(categoria)!='S' && toupper(categoria)!='I' && toupper(categoria)!='B');
    if(arq.is_open()){
        Veiculo v;
        while(arq.read((char*)(&v), sizeof(Veiculo))){

            if(v.categoria == toupper(categoria) && v.situacao == 'D'){
                teste = true;
                cout << "--------------------------------------------------------" << endl;
                cout << "Codigo: " << v.codigo << endl;
                cout << "Placa: " << v.placa << endl;
                cout << "Marca/Modelo: " << v.marcaModelo << endl;
                cout << "Quantidade de Locacoes: " << v.quantidadeLocacoes << endl;
                cout << "--------------------------------------------------------" << endl;
            }
        }
        if(teste){
            string placa;
            cout << "Digite a placa do veiculo que voce se interessou (formato antigo ou novo): "; cin >> placa; cout << endl;
            placa = placaMaiuscula(placa);
            arq.clear();
            arq.seekg(0, ios::beg);
            bool locou = false;
            while(arq.read((char*)(&v), sizeof(Veiculo))){
                if(v.placa == placa && v.categoria == categoria && v.situacao == 'D'){
                    locou = true;
                    v.quantidadeLocacoes += 1;
                    v.situacao = 'I';
                    arq.seekp(-sizeof(Veiculo), ios::cur);
                    arq.write((const char*)(&v), sizeof(Veiculo));
                    Locacao locacao = criaLocacao(v);
                    string aux;
                    aux = string(locacao.cpfCliente) + " - " + string(locacao.dataLocacao) +  " - " + to_string(locacao.quantidadeDias) + " - " + to_string(locacao.codigoVeiculo) + " - " + "A";
                    ifstream arqTxt("LOCADOS.TXT");
                    if(arqTxt.is_open()){
                        string linha = "", l;
                        while(getline(arqTxt, l)){
                            linha += l + "\n";
                        }
                        linha += aux + "\n";
                        ofstream arqTxtOut("LOCADOS.TXT");
                        if(arqTxtOut.is_open()){
                            arqTxtOut << linha;
                        }else{
                            cout << "Nao foi possivel salvar os dados" << endl;
                        }
                        arqTxtOut.close();
                        cout << "Locacao Feita" << endl;
                    }else{
                        cout << "Nao foi possivel abrir o arquivo TXT"<<endl;
                    }
                    arqTxt.close();
                    break;
                }
            }
            if(!locou){
                cout << "Sem carros para Locar com essa placa" << endl;
            }
        }else{
            cout << "Nenhum carro para alocar nessa categoria" << endl;
        }


    }else{
        cout << "Nao foi possivel abrir o arquivo"<<endl;
    }
    arq.close();
}

Locacao criaLocacao(Veiculo v){
    Locacao l;
    string data, cpf, quantidadeDias;

    do{
        cout << "Digite a data: "; cin >> data; cout << endl;
        if(!validaData(data)){
            cout << "Data no formato errado, digite novamente: " << endl;
        }
    }while(!validaData(data));

    cin.ignore();
    do{
        cout << "Digite Um CPF Real e no formato xxx.xxx.xxx-xx ou xxxxxxxxxxx: "; cin >> cpf; cout << endl;
        if(!validaCpf(cpf)){
            cout << "Digite um CPF real valido" << endl;
        }
    }while(!validaCpf(cpf));
    cpf = cpfSemPontos(cpf);
    do{
        do{
            cout << "Quantidade de dias: "; cin >> quantidadeDias; cout << endl;
            if(!validaInt(quantidadeDias)){
                cout << "Digite um inteiro" << endl;
            }
        }while(!validaInt(quantidadeDias));
        if(stoi(quantidadeDias)<=0){
            cout << "Minimo 1 dia de alocacao" << endl;
        }
    }while(stoi(quantidadeDias) <= 0);


    l.quantidadeDias = stoi(quantidadeDias);
    l.codigoVeiculo = v.codigo;
    strcpy(l.dataLocacao, data.c_str());
    strcpy(l.cpfCliente, cpf.c_str());
    l.situacao = 'A';
    return l;
}

bool validaCpf(string cpf) {
    if(cpf.size() == 11 || cpf.size() == 14) {
        string aux;
        if(cpf.size() == 14) {
            aux = cpf.substr(0,3) + cpf.substr(4,3) + cpf.substr(8,3) +  cpf.substr(12,2);  //xxx.xxx.xxx-xx
        } else {
            aux = cpf;
        }
        if(validaInt(aux)) {
            int sum1 = 0, sum2 = 0;
            for(int i = 0; i < 9; i++) {
                sum1 += (aux[i] - '0') * (10 - i);
                sum2 += (aux[i] - '0') * (11 - i);
            }
            sum2 += (aux[9] - '0') * 2;
            int check1, check2;
            if(sum1 % 11 < 2) {
                check1 = 0;
            } else {
                check1 = 11 - sum1 % 11;
            }
            if(sum2 % 11 < 2) {
                check2 = 0;
            } else {
                check2 = 11 - sum2 % 11;
            }
            return check1 == (aux[9] - '0') && check2 == (aux[10] - '0');
        }
    }
    return false;
}

bool validaData(string data) {
    int dia, mes, ano;
    if(data.size() == 10){
        dia =stoi(data.substr(0,2));
        mes =stoi(data.substr(3,2));
        ano =stoi(data.substr(6,4));
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
    }else{
        return false;
    }

}

bool ehBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

void devolucaoVeiculo(){
    fstream arq("FROTA.DAD", ios::binary | ios::in | ios::out);
    fstream arqTxt("LOCADOS.TXT", ios::in | ios::out | ios::app);
    string cpf;
    do{
        cout << "Digite Um CPF Real e no formato xxx.xxx.xxx-xx ou xxxxxxxxxxx: "; cin>>cpf;cout<<endl;
        if(!validaCpf(cpf)){
            cout << "Digite um CPF real valido" << endl;
        }
    }while(!validaCpf(cpf));
    cpf = cpfSemPontos(cpf);

    if(arqTxt.is_open() && arq.is_open()){
        string linha="", aux;
        string cpfAux="";
        while(getline(arqTxt, aux)){
            if(aux[aux.size()-1] == 'A'){
                for(unsigned int i = 0; i<aux.size();i++){
                    if(aux[i]!=' '){
                        cpfAux+=aux[i];
                    }else{
                        break;
                    }
                }
                if(comparaCpf(cpfAux, cpf)){
                    linha += aux + "\n";
                }
                cpfAux = "";
            }


        }
        if(linha != ""){
            cout << "Carros registrados no seu nome: " << endl;
            cout << linha << endl;
            string placa;
            do{
                cout << "Digite a placa do carro para devolucao (formato antigo ou novo): "; cin >> placa ;cout << endl;
                placa = placaMaiuscula(placa);
                if(!verificaPlaca(placa)){
                    cout << "Placa Invalida, Tente Novamente" << endl;
                }
            }while(!verificaPlaca(placa));
            Veiculo v;
            bool achou = false;
            while(arq.read((char *)(&v), sizeof(v))){
                if(v.placa == placa){
                    string auxLinha, codigoCarro = "", dataLocacao = "", qtdDias = "";
                    int contaTraco=0;
                    for(unsigned int i = 0; i < linha.size(); i++){
                        if(linha[i] == '-'){
                            contaTraco+=1;
                        }
                        if(contaTraco == 2 && linha[i] != '-' && linha[i] != ' '  ){
                            qtdDias += linha[i];
                        }
                        if(contaTraco == 3 && linha[i] != '-' && linha[i] != ' ' ){
                            codigoCarro += linha[i];
                        }
                        if(contaTraco == 1 && linha[i] != '-' && linha[i] != ' ' ){
                            dataLocacao += linha[i];
                        }
                        if(contaTraco == 4){
                            if(stoi(codigoCarro) == v.codigo){
                                achou = true;
                                break;
                            }
                        }
                        if(linha[i] == '\n'){
                            contaTraco=0;
                            codigoCarro = "";
                            dataLocacao="";
                        }
                    }
                    if(achou){
                        string dataDevolucao;
                        do{
                            do{
                                cout << "Digite a data de devolacao: xx/xx/xxxx = "; cin >> dataDevolucao; cout << endl;
                                if(!validaData(dataDevolucao)){
                                    cout << "Digite uma data valida"<<endl;
                                }
                            }while(!validaData(dataDevolucao));
                            if(calcularDiferenca(dataLocacao, dataDevolucao) <= 0){
                                cout << "A data para devolucao é invalida, necessario ser pelo menos um dia de a mais" << endl;
                            }
                        }while(calcularDiferenca(dataLocacao, dataDevolucao) <= 0);
                       int diferenca = calcularDiferenca(dataLocacao, dataDevolucao);
                       switch (v.categoria){
                        case 'S':
                            cobranca(qtdDias, diferenca, 1500);
                            break;
                        case 'I':
                            cobranca(qtdDias, diferenca, 800);
                            break;
                        case 'B':
                            cobranca(qtdDias, diferenca, 200);
                            break;
                       }

                       v.situacao = 'D';
                       arq.seekp(-sizeof(Veiculo), ios::cur);
                       arq.write((const char*)(&v), sizeof(Veiculo));


                        string linhaAux, novoTexto = "";
                        string cpfVerifica = "";
                        string codigoCarroVerifica = "";
                        int conta = 0;
                        arqTxt.clear();
                        arqTxt.seekg(0, ios::beg);
                        while(getline(arqTxt, linhaAux)){
                            if(linhaAux[linhaAux.size()-1] == 'A'){
                                cpfVerifica = "";
                                for(unsigned int i = 0; i<linhaAux.size();i++){
                                    if(linhaAux[i] == '-'){
                                        conta +=1;
                                    }
                                    if(conta == 3 && linhaAux[i]!=' ' && linhaAux[i]!='-'){
                                        codigoCarroVerifica+=linhaAux[i];
                                    }
                                    if(linhaAux[i]!=' ' && conta == 0){
                                        cpfVerifica+=linhaAux[i];
                                    }
                                }

                                if(comparaCpf(cpfVerifica, cpf)){
                                    if(stoi(codigoCarroVerifica) == v.codigo){
                                        string teste = linhaAux.substr(0, linhaAux.size()-1);
                                        teste += 'I';
                                        novoTexto += teste;
                                        novoTexto += '\n';
                                    }else{
                                        novoTexto += linhaAux;
                                        novoTexto += '\n';
                                    }
                                }else{
                                    novoTexto += linhaAux;
                                    novoTexto += '\n';
                                }

                            }else{
                                novoTexto += linhaAux;
                                novoTexto += '\n';
                            }

                        conta=0;
                        cpfVerifica = "";
                        codigoCarroVerifica = "";
                        }
                    arqTxt.close();
                    ofstream a("LOCADOS.TXT");
                    a << novoTexto;
                    a.close();


                    break;

                    }

                }
            }
            if(!achou){
                cout << "Você nao possui nenhum carro com essa placa em situacao Ativa" << endl;
            }


        }else{
            cout << "Nao existe carros no seu CPF" << endl;
        }
    }else{
        cout << "ERRO AO ABRIR OS ARQUIVOS. TENTE NOVAMENTE" << endl;
    }

    arqTxt.close();
    arq.close();
}

bool comparaCpf(string cpf1, string cpf2){
    string auxCpf1 = "";
    string auxCpf2 = "";

    for(unsigned int i = 0; i < cpf1.size(); i++){
        if(isdigit(cpf1[i])){
            auxCpf1 += cpf1[i];
        }
    }

    for(unsigned int i = 0; i < cpf2.size(); i++){
        if(isdigit(cpf2[i])){
            auxCpf2 += cpf2[i];
        }
    }

    return auxCpf1 == auxCpf2;
}


int calcularDiferenca(string data1, string data2) {
    int dias1 = stoi(data1.substr(0, 2));
    int dias2 = stoi(data2.substr(0, 2));
    int mes1 = stoi(data1.substr(3, 2));
    int mes2 = stoi(data2.substr(3, 2));
    int ano1 = stoi(data1.substr(6, 4));
    int ano2 = stoi(data2.substr(6, 4));

    int diasPorMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int auxDias1 = dias1;
    int auxDias2 = dias2;
    for (int i=0; i<mes1 - 1; i++)
        auxDias1 += diasPorMes[i];
    for (int i=0; i<mes2 - 1; i++)
        auxDias2 += diasPorMes[i];

    for (int i=0; i<ano1; i++) {
        if (ehBissexto(i)) {
            auxDias1 += 366;
        } else {
            auxDias1 += 365;
        }
    }
    for (int i=0; i<ano2; i++) {
        if (ehBissexto(i)) {
            auxDias2 += 366;
        } else {
            auxDias2 += 365;
        }
    }

    return auxDias2 - auxDias1;
}


void cobranca(string qtdDias, int diferenca, int diaria){
    if(stoi(qtdDias) > diferenca){
        cout << "Devolucao Antes do Prazo" <<  endl;
        float total = diferenca*diaria;
        cout << "Total a pagar: " << to_string(total) << endl;
    }else if(stoi(qtdDias) == diferenca){
        cout << "Devolucao No Prazo" <<  endl;
        float total = stoi(qtdDias)*diaria;
        cout << "Total a pagar: " << to_string(total) << endl;
    }else{
        float total = stoi(qtdDias)*diaria;
        float multa = total * 0.2;
        float multaDiaria = total * 0.01 * (diferenca - stoi(qtdDias));
        float totalF = total+multa+multaDiaria;
        cout << "Total a pagar: \nTotal (Se entregasse no prazo) = " << to_string(total) << "\nMulta = " << to_string(multa) << "\nMulta por dia de Atraso = " << to_string(multaDiaria) << endl;
        cout << "Total a pagar = " << to_string(totalF) << endl;

    }

}

void relatorio(){
    string data;
    do{
        cout << "-Relatorio Lista Carros Devolucao-" << endl;
        cout << "Digite a Data de Devolucao: "; cin >> data; cout << endl;
        if(!validaData(data)){
            cout << "Data no formato invalido" << endl;
        }
    }while(!validaData(data));

    ifstream arqTxt("LOCADOS.TXT");
    ifstream arq("FROTA.DAD", ios::binary);

    if(arqTxt.is_open() && arq.is_open()){
        string linha, dataLocacao="", qtdDias="", codigoCarro = "";
        bool teste = true;

        while(getline(arqTxt, linha)){
            int conta = 0;
            if(linha[linha.size()-1] == 'A'){
                for(unsigned int i = 0; i < linha.size(); i++){
                    if(conta == 2 && linha[i] != '-' && linha[i] != ' ' ){
                        qtdDias += linha[i];
                    }
                    if(conta == 3 && linha[i] != '-' && linha[i] != ' ' ){
                        codigoCarro += linha[i];
                    }
                    if(conta == 1 && linha[i] != '-' && linha[i] != ' ' ){
                        dataLocacao += linha[i];
                    }
                    if(linha[i]=='-'){
                        conta += 1;
                    }
                }
                conta = 0;
                string dataDevolucao = adicionaDias(dataLocacao, stoi(qtdDias));
                cout << "DATA DE DEVOLUCAO = " << dataDevolucao << endl;
                if(dataDevolucao == data){
                    Veiculo v;
                    while(arq.read((char*)(&v), (sizeof(Veiculo)))){
                        if(v.codigo == stoi(codigoCarro) && v.situacao == 'I'){
                            teste = false;
                            cout << "--------------------------------------------------------" << endl;
                            cout << "Codigo: " << v.codigo << endl;
                            cout << "Placa: " << v.placa << endl;
                            cout << "Marca/Modelo: " << v.marcaModelo << endl;
                            cout << "Quantidade de Locacoes: " << v.quantidadeLocacoes << endl;
                            cout << "--------------------------------------------------------" << endl;
                        }
                    }
                    arq.clear();
                    arq.seekg(0, ios::beg);
                }
            }
            dataLocacao="",qtdDias=""; codigoCarro = "";
        }
        if(teste){
            cout << "Nao tem nenhum veiculo para devolucao na Data " << data << endl;
        }

    }else{
        cout << "Nao foi possivel abrir o arquivo" << endl;
    }


    arqTxt.close();
    arq.close();
}

string adicionaDias(string data, int dias) {
    int dia = stoi(data.substr(0, 2));
    int mes = stoi(data.substr(3, 2));
    int ano = stoi(data.substr(6, 4));

    dia += dias;

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

    while (dia > diasNoMes) {
        dia -= diasNoMes;
        mes++;
        if (mes > 12) {
            mes = 1;
            ano++;
        }
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
    }

    string diaStr;
    if (dia < 10) {
        diaStr = "0" + to_string(dia);
    } else {
        diaStr = to_string(dia);
    }

    string mesStr;
    if (mes < 10) {
        mesStr = "0" + to_string(mes);
    } else {
        mesStr = to_string(mes);
    }

    string anoStr = to_string(ano);

    return diaStr + "/" + mesStr + "/" + anoStr;
}

string placaMaiuscula(string placa){
    string p = "";
    for(unsigned int i = 0; i < placa.size(); i++){
        if(isalpha(placa[i])){
            p += toupper(placa[i]);
        }else{
            p += placa[i];
        }

    }
    return p;
}

string cpfSemPontos(string cpf) {
    string result = "";
    for (unsigned int i = 0; i < cpf.size(); i++) {
        if (isdigit(cpf[i])) {
            result += cpf[i];
        }
    }
    return result;
}
