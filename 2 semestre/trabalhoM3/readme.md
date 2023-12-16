# UNIVALI POLITECNICA KOBRASOL CIÊNCIA DA COMPUTAÇÃO

## Algoritmos e Programação de Computadores – profa Fernanda Cunha

### TRABALHO 3 (M3 – 23/2)

Implemente um programa para controle de locação de veículos. Para cada veículo têm-se as informações: código, marca-modelo, placa, categoria (B-básico, I-intermediário, S-super), situação (disponível/locado), quantidade de locações. A frota de veículos será armazenada no arquivo binário FROTA.DAD.

Cada locação realizada deve ser armazenada no arquivo texto LOCADOS.TXT, e suas informações são data da locação, CPF do cliente, código do veículo, quantidade de dias da locação, situação (ativa/inativa). Cada categoria tem um valor de diária diferenciado (defina estes valores). Devoluções em atraso geram multa de 20% sobre o valor contratado mais 1% ao dia de atraso.

O programa deve permitir as seguintes operações (através de menu/subrotinas):

1. **Inclusão de veículo.** Antes de incluir efetivamente veja se o veículo já existe (pesquise por placa). Caso exista, emita mensagem de erro. Se não existir, cadastre o veículo, grave-o no respectivo arquivo e emita mensagem de sucesso.
2. **Locação de veículo.** Liste os veículos disponíveis conforme a categoria desejada pelo cliente. Caso não exista nenhum veículo, emita mensagem de erro e cancele o processo. Escolha o veículo a ser locado e atualize suas informações em FROTA.DAD. Gere a locação, grave-a no respectivo arquivo e emita mensagem de sucesso.
3. **Devolução de veículo locado** (busca por CPF do cliente). Caso não exista locação, emita mensagem de erro. Se existir, verifique se a data da devolução for em atraso, apresente mensagem referente a multa juntamente com o valor total a pagar. Atualize a situação do veículo em FROTA.DAD e atualize para inativa a locação em LOCADOS.TXT.
4. **Relatório** – listagem de veículos para devolução na data de “hoje” (pega do sistema ou via leitura).

A qualquer entrada de dados deve-se realizar tratamento de dados/validação (tipo/valor). O sistema deverá apresentar uma interface básica, com menu e controle de rolamento de tela.

Serão considerados para efeitos de avaliação: i) a corretude das funcionalidades do programa, ii) a otimização do programa, iii) a utilização de modularização/parametrização das tarefas e iv) adequação da interface. Haverá desconto de 0,5 por item não apresentado/mal estruturado.

| Valor | Item |
| --- | --- |
| 1,5 | Programa principal (main) |
| 1,5 | Relatório |
| 2,0 p/item | Inclusão, Locação |
| 3,0 | Devolução |
