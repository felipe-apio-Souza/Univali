#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <algorithm>

#define MAX 100
using namespace std;

bool validaInt(string);
bool validaFloat(string);
bool validaString(string);
bool validaData(string);
void inclusao(string[MAX], bool[MAX], float[MAX], int[MAX], string[MAX], int&);
void consulta(string[MAX], bool[MAX], float[MAX], int[MAX], string[MAX], int&, string);
void aquisicao(string[MAX], bool[MAX], float[MAX], int[MAX], string[MAX], int&, string);
bool existe(string[MAX], string, int);
void venda(string[MAX], bool[MAX], float[MAX], int[MAX], string[MAX], int&, string, string);
void relatorio(string[MAX], bool[MAX], float[MAX], int[MAX], string[MAX], int&);
bool comparaData(string, string);

int main()
{
    setlocale(LC_ALL, "portuguese");
    string nome[MAX], data[MAX],respostaStr,enter = "",d,pesquisa;
    bool tipo[MAX];
    float preco[MAX];
    int quantidade[MAX],limite = 0;

    do
    {
        cout << "Digite A Data atual:" << endl;
        getline(cin, d);
    } while (!validaData(d));

    while (true)
    {
string respostaStr;

do {
    system("clear || cls");
    cout << "===== Menu Principal =====" << endl;
    cout << "|      1. Inclusão       |" << endl;
    cout << "|      2. Consulta       |" << endl;
    cout << "|      3. Aquisição      |" << endl;
    cout << "|      4. Venda          |" << endl;
    cout << "|      5. Relatório      |" << endl;
    cout << "|      0. Sair           |" << endl;
    cout << "==========================" << endl;
    cout << "Escolha Uma Opção: ";
    cout << endl;

    getline(cin, respostaStr);

    if (!respostaStr.empty() && (!validaInt(respostaStr) || stoi(respostaStr) < 0 || stoi(respostaStr) > 5)) {
        cout << "Digite uma opção válida" << endl;
        cout << "Aperte enter para continuar: "<<endl;
        getline(cin, enter);
        } else if (respostaStr.empty()) {
        respostaStr = "9";
    }
} while (!respostaStr.empty() && (!validaInt(respostaStr) || stoi(respostaStr) < 0 || stoi(respostaStr) > 5));

int resposta = stoi(respostaStr);
        switch (resposta)
        {
        case 1:
            system("clear || cls");
            inclusao(nome, tipo, preco, quantidade, data, limite);
            break;
        case 2:
            system("clear || cls");
            cout << "Digite o nome do produto (sem pontuações): " <<endl;
            getline(cin, pesquisa);
            consulta(nome, tipo, preco, quantidade, data, limite, pesquisa);
            break;
        case 3:
            system("clear || cls");
            cout << "Digite o nome do produto: ";
            getline(cin, pesquisa);
            aquisicao(nome, tipo, preco, quantidade, data, limite, pesquisa);
            break;
        case 4:
            system("clear || cls");
            cout << "Digite o nome do produto: ";
            getline(cin, pesquisa);
            venda(nome, tipo, preco, quantidade, data, limite, pesquisa, d);
            break;
        case 5:
            system("clear || cls");
            relatorio(nome, tipo, preco, quantidade, data, limite);
            break;
        case 0:
            cout << "Saindo do programa. Até logo!" << endl;
            return 0;
        default:
            cout << "Opcao inválida. Tente novamente." << endl;
            break;
        }
        if (resposta != 4)
        {
            cout << "Aperte enter para continuar !!!" << endl;
            cin.ignore();
        }
        else
        {
            cout << "Aperte enter para continuar !!!" << endl;
            cin.ignore();
            cin.get();
        }
    }
    return 0;
}

void consulta(string nome[MAX], bool tipo[MAX], float preco[MAX], int quantidade[MAX], string data[MAX], int& limite, string pesquisa)
{
    string pesquisaTeste = "";
    for (int i = 0; i < pesquisa.size(); i++)
    {
        pesquisaTeste += tolower(pesquisa[i]);
    }
    int pesquisaInt = 0;
    for (int i = 0; i < limite; i++)
    {
        string nomeTeste = "";
        for (int j = 0; j < nome[i].size(); j++)
        {
            nomeTeste += tolower(nome[i][j]);
        }
        if (pesquisaTeste == nomeTeste)
        {
            cout << "Nome Do Produto: " << nome[i] << endl;
            if (tipo[i] == 1)
            {
                cout << "É Perecível" << endl;
                cout << "Data De Validade: " << data[i] << endl;
            }
            else
            {
                cout << "Não É Perecível" << endl;
            }
            cout << "Preço do produto R$: " << preco[i] << endl;
            cout << "Quantidade: " << quantidade[i] << endl;
            pesquisaInt += 1;
        }
    }
    if (pesquisaInt == 0)
    {
        cout << "Nenhum Resultado correspondente" << endl;
    }
}

bool existe(string nome[MAX], string n, int limite) {
    string nTeste = "";
    for(int i = 0; i < n.size(); i++){
        nTeste += tolower(n[i]);
    }

    for(int i = 0; i < limite; i++){
        string nomeTeste = "";
        for(int j = 0; j < nome[i].size(); j++){
            nomeTeste += tolower(nome[i][j]);
        }
        if(nTeste == nomeTeste){
            return true;
        }
    }
    return false;
}


void inclusao(string nome[MAX], bool tipo[MAX], float preco[MAX], int quantidade[MAX], string data[MAX], int& limite)
{
    bool continuar = true;
    do
    {

        string n;
        do
        {
            cout << "Digite O Nome Do Produto (sem acento): ";
            getline(cin, n);

            if(existe(nome, n, limite)){
                cout << "O Produto Já Existe "<<endl;
            }

        } while (!validaString(n) || existe(nome, n, limite));


        bool t;
        string tInt;
        do
        {
            cout << "Digite 0-(Se O Alimento Não For Perecível) Ou 1-(Se o alimento for perecível): ";
            cin >> tInt;
        } while (!validaInt(tInt) || (tInt != "1" && tInt != "0"));

        t = (tInt == "1");

        float p;
        string pString;
        do
        {
            cout << "Qual O Preço Do Produto? ";
            cin >> pString;
        } while (!validaFloat(pString) || stof(pString) <= 0);

        p = stof(pString);

        int q;
        string qString;
        do
        {
            cout << "Quantas Unidades Do produto? ";
            cin >> qString;
        } while (!validaInt(qString) || stoi(qString) <= 0);
        q = stoi(qString);

        string validade;
        if (t == true)
        {
            do
            {
                cout << "Validade Do Produto (DD/MM/AAAA)? ";
                cin >> validade;
            } while (!validaData(validade));
        }
        else
        {
            validade = "00/00/0000";
        }

        nome[limite] = n;
        tipo[limite] = t;
        preco[limite] = p;
        quantidade[limite] = q;
        data[limite] = validade;
        limite += 1;

        string c;
        do
        {
            cout << "Deseja Adicionar Mais Um Produto? 1 - (Sim) ou 0 - (Não): ";
            cin >> c;
            cin.ignore();
        } while (!validaInt(c) || (c != "0" && c != "1"));

        if (c == "0")
        {
            continuar = false;
        }
        system("clear || cls");
    } while (continuar);
}

bool validaInt(string teste)
{
    for (int i = 0; i < teste.size(); i++)
    {
        if (isalpha(teste[i]))
        {
            return false;
        }
        else if (i == 0)
        {
            if (!isdigit(teste[0]) && teste[0] != '-')
            {
                return false;
            }
        }
        else if (!isdigit(teste[i]))
        {
            return false;
        }
    }

    return true;
}

bool validaFloat(string teste)
{
    for (int i = 0; i < teste.size(); i++)
    {
        if (isalpha(teste[i]))
        {
            return false;
        }
        else if (i == 0)
        {
            if (!isdigit(teste[0]) && teste[0] != '-')
            {
                return false;
            }
        }
        else if (teste[0] == '-')
        {
            if (!isdigit(teste[1]))
            {
                return false;
            }
        }
        else if (!isdigit(teste[i]) && teste[i] != '.')
        {
            return false;
        }
    }

    return true;
}

bool validaString(string teste)
{
    if (teste != "")
    {
        for (int i = 0; i < teste.size(); i++)
        {
            if (!isalpha(teste[i]) && teste[i] != ' ')
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}

bool validaData(string data)
{
    string dia = "", mes = "", ano = "";
    int contador = 0;
    if (data.size() != 10)
    {
        return false;
    }
    for (int i = 0; i < data.size(); i++)
    {
        if (contador == 2 || contador == 5)
        {
            if (data[i] != '/')
            {
                return false;
            }
        }
        else if (!isdigit(data[i]))
        {
            return false;
        }
        contador += 1;
    }

    for (int i = 0; i < 10; i++)
    {
        if (i < 2)
        {
            dia += data[i];
        }
        else if (i > 2 && i < 5)
        {
            mes += data[i];
        }
        else if (i > 5 && i < 10)
        {
            ano += data[i];
        }
    }

    int d = stoi(dia);
    int m = stoi(mes);
    int a = stoi(ano);

    if (d < 1 || d > 30)
    {
        return false;
    }
    if (m < 0 || m > 12)
    {
        return false;
    }
    if (a < 1990)
    {
        return false;
    }
    return true;
}

void aquisicao(string nome[MAX], bool tipo[MAX], float preco[MAX], int quantidade[MAX], string data[MAX], int& limite, string pesquisa)
{
    string pesquisaTeste = "";
    for (int i = 0; i < pesquisa.size(); i++)
    {
        pesquisaTeste += tolower(pesquisa[i]);
    }
    int pesquisaInt = 0;
    for (int i = 0; i < limite; i++)
    {
        string nomeTeste = "";
        for (int j = 0; j < nome[i].size(); j++)
        {
            nomeTeste += tolower(nome[i][j]);
        }
        if (pesquisaTeste == nomeTeste)
        {
            int qtd;
            string qtdString;
            do
            {
                cout << "Quantas Unidades Você Quer Aumentar?" << endl;
                cin >> qtdString;
                if(!validaInt(qtdString) || stoi(qtdString) < 0){
                    cout << "número inválido !!"<<endl;
                }
            } while (!validaInt(qtdString) || stoi(qtdString) < 0);

            qtd = stoi(qtdString);
            quantidade[i] += qtd;

            pesquisaInt += 1;
            cin.ignore();
        }
    }
    if (pesquisaInt == 0)
    {
        cout << "Produto Inexistente" << endl;
    }else{
        cout << "Aquisição feita com sucesso "<<endl;
    }
}

void venda(string nome[MAX], bool tipo[MAX], float preco[MAX], int quantidade[MAX], string data[MAX], int& limite, string pesquisa, string d){
    string pesquisaTeste = "";
    for(int i = 0; i < pesquisa.size(); i++){
        pesquisaTeste += tolower(pesquisa[i]);
    }
    int pesquisaInt = 0;
    for(int i = 0; i < limite; i++){
        string nomeTeste = "";
        bool repeteTemp;
        for(int j = 0; j < nome[i].size(); j++){
            nomeTeste += tolower(nome[i][j]);
        }
        if(pesquisaTeste == nomeTeste){
            string qtdString;
            do{
                cout << "Quantas Unidades Você Quer Vender?" << endl;
                cin >> qtdString;
            }while(!validaInt(qtdString) || stoi(qtdString) <= 0 || stoi(qtdString) > quantidade[i]);
            if(tipo[i] == 1){
                if(!comparaData(data[i], d)){
                    cout << "Quantidade: " << stoi(qtdString) << endl;
                    cout << "Preco Unitário: " << preco[i] << endl;
                    cout << "Total A Pagar: " << (preco[i]*stoi(qtdString)) << endl;
                    string testando;

                    do{
                        cout << "Confirmar venda? Sim - s ou Não - n" << endl;
                        cin >> testando;
                        if(testando != "s" && testando != "n"){
                            repeteTemp = true;
                        }else{
                            repeteTemp = false;
                        }
                    }while(!validaString(testando) || repeteTemp == true);
                    if(testando == "s"){
                        int qtd = stoi(qtdString);
                        quantidade[i] -= qtd;
                        cout << "Venda Feita Com Sucesso" << endl;
                    }else{
                        cout << "Venda cancelada" << endl;
                    }


                }else{
                    cout << "Produto Vencido" << endl;
                }
            }else{

                cout << "Quantidade: " << stoi(qtdString) << endl;
                cout << "Preço Unitário: " << preco[i] << endl;
                cout << "Total a pagar: " << (preco[i]*stoi(qtdString)) << endl;
                string testando;
                do{
                    cout << "Confirmar venda? Sim - s OU Nao - n" << endl;
                    cin >> testando;
                    if(testando != "s" && testando != "n"){
                        repeteTemp = true;
                    }else{
                        repeteTemp = false;
                    }
                }while(!validaString(testando) || repeteTemp == true);
                if(testando == "s"){
                    int qtd = stoi(qtdString);
                    quantidade[i] -= qtd;
                    cout << "Venda Feita Com Sucesso" << endl;
                }else{
                    cout << "Venda cancelada" << endl;
                }
            }


            pesquisaInt += 1;
        }
    }
    if(pesquisaInt == 0){
        cout << "Produto Inexistente" << endl;
    }
}

bool comparaData(string data, string dataF)
{
    int dia = stoi(data.substr(0, 2));
    int mes = stoi(data.substr(3, 2));
    int ano = stoi(data.substr(6, 4));

    int diaF = stoi(dataF.substr(0, 2));
    int mesF = stoi(dataF.substr(3, 2));
    int anoF = stoi(dataF.substr(6, 4));

    if (anoF < ano)
    {
        return false;
    }
    else if (anoF > ano)
    {
        return true;
    }

    if (mesF < mes)
    {
        return false;
    }
    else if (mesF > mes)
    {
        return true;
    }

    if (diaF < dia)
    {
        return false;
    }

    return true;
}

void relatorio(string nome[MAX], bool tipo[MAX], float preco[MAX], int quantidade[MAX], string data[MAX], int& limite) {
    string ordenado[MAX];
    int teste = 0;
    int iOrdenado = 0;

    while (iOrdenado < limite) {
        string primeiro = "";
        int temp = -1;

        for (int i = 0; i < limite; i++) {
            bool encontrado = false;

            for (int j = 0; j < iOrdenado; j++) {
                if (ordenado[j] == nome[i]) {
                    encontrado = true;
                    break;
                }
            }

            if (!encontrado) {
                if (primeiro.empty() || nome[i] < primeiro) {
                    primeiro = nome[i];
                    temp = i;
                }
            }
        }

        if (temp != -1) {
            ordenado[iOrdenado] = primeiro;
            iOrdenado++;
        }
    }

    for (int i = 0; i < iOrdenado; i++) {
        int temp = -1;
        for (int j = 0; j < limite; j++) {
            if (ordenado[i] == nome[j]) {
                temp = j;
                break;
            }
        }

        if (temp != -1) {
            cout << "Nome Do Produto: " << nome[temp] << endl;
            if (tipo[temp] == 1) {
                cout << "É Perecível" << endl;
                cout << "Data De Validade: " << data[temp] << endl;
            } else {
                cout << "Não É Perecível" << endl;
            }
            cout << "Preço do produto R$: " << preco[temp]  << endl;
            cout << "Quantidade: " << quantidade[temp] << endl;
            cout << "------------------------------------" << endl;
            teste += 1;
        }
    }
    if(teste == 0){
        cout << "Nenhum Produto Registrado" << endl;

    }
}

