# UNIVALI POLITECNICA KOBRASOL CIÊNCIA DA COMPUTAÇÃO

## ALGORITMOS E PROGRAMAÇÃO DE COMPUTADORES 2p

### TRABALHO 1 (2023/2) – MODULARIZAÇÃO / STRING / VETOR

Definição: Um determinado mercado vende vários produtos, perecíveis e não perecíveis, e o proprietário resolveu informatizá-lo. Para tal agrupou as seguintes informações sobre os produtos: nome, tipo (perecível ou não – dica usar boolean), preço de venda unitário, quantidade em estoque e data de validade. O estoque será armazenado em vetores.

O programa a ser implementado deve permitir as seguintes operações (através de menu/subrotinas):

1. **Inclusão de um novo produto** no estoque a qualquer momento da execução do programa. Antes de incluir verificar se o produto já existe no estoque (pesquisar pelo nome). Caso exista, informar "Produto já existente". Caso contrário, solicitar os demais dados ao usuário, incluir no estoque e informar “Inclusão confirmada”.
2. **Consulta de informações** de um produto, buscando-se pelo nome. Caso não exista no estoque, informar "Produto inexistente". Caso contrário, apresentar as informações do produto.
3. **Aquisição de unidades** de um determinado produto, buscando-se pelo nome. Caso não exista, informar "Produto inexistente". Caso contrário, solicitar a quantidade a ser aumentada no estoque e informar “Aquisição confirmada – quantidade atual X unidades”.
4. **Venda de determinado produto** do estoque, informando o nome. Caso não exista, informar "Produto inexistente". Caso contrário, solicitar a quantidade vendida. Se não houver estoque suficiente ou, para um produto perecível, a validade estiver ultrapassada, deve-se cancelar a venda e informar o motivo do cancelamento. Caso seja possível vender, apresentar as informações da venda (quantidade do produto, preço de venda unitário e total a pagar) e perguntar ao usuário: “Confirma venda: S(SIM) / N(NÃO)?”. Se sim, informar “Venda realizada” e dar baixa no estoque. Não é necessário armazenar as informações de todas as vendas realizadas.
5. **Relatório**: listagem de todos os produtos em ordem alfabética – todas as informações.

Além destas funcionalidades, o sistema deverá apresentar uma interface básica com controle de tela e menu. A qualquer entrada de dados deve-se realizar tratamento de dados/validação de tipo e de valor.

Serão considerados para efeitos de avaliação: i) a corretude das funcionalidades do programa, ii) a otimização do programa, iii) a utilização de modularização/parametrização das tarefas e iv) adequação da interface. Haverá desconto de 0,5 por item não apresentado/mal estruturado.

| Pontuação | Item |
| --- | --- |
| 2,0 | Validação de dados |
| 2,0 | Inclusão |
| 1,5 / item | Consulta, Aquisição, Venda, Relatório |
