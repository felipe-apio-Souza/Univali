# UNIVALI POLITECNICA Ciência da Computação – Algoritmos e Programação 2p

## TRABALHO M2 (23/2) – REGISTROS/STRUCTS + RECURSIVIDADE – LINGUAGEM C++

Desenvolva o protótipo de uma agenda semanal de consultas para um médico. As informações são organizadas por dia da semana, e para cada dia tem-se a data atual (dia, mês, ano e dia da semana), e as consultas, cujas informações são horário (hora, minuto), paciente, tipo (particular/convênio), se é consulta de retorno (sim/não). Utilize um ou mais tipos estruturados para representar estas informações.

A agenda semanal deve ser armazenada em um vetor, organizada de 2af a 6af, por data/hora. O número máximo de consultas diárias é 7, e a quantidade de consultas diárias deve ser controlada. Uma consulta dura 30min, e o período de atendimento é matutino (8h30 as 12h). Pode-se também tratar se é/não feriado (data indisponível para consultas).

Um exemplo possível de organização da agenda seria:


16/10/2023 2af … 17/10/2023 3af … 18/10/2023 4af … 19/10/2023 5af … 20/10/2023 6af …


Ilustrando a agenda de 2af acima:


16/10/2022 2af 8h30 Fulano particular S 10h00 Beltrano convênio N 10h30 Cicrano convênio S … … … …


Ou pode ser numa única estrutura:


16/10/2023 2af 8h30 Fulano particular S 16/10/2023 2af 10h00 Beltrano convênio N 16/10/2023 2af 10h30 Cicrano convênio S 17/10/2023 3af … … 20/10/2023 6af


O programa a ser implementado deve permitir as seguintes operações (através de menu/subrotinas):

- **Inicialização de nova semana** a qualquer momento da execução do programa. Antes de inicializar o vetor de consultas solicite confirmação do usuário. Caso positivo, peça a data inicial da semana (no caso do exemplo 16/10/2023) e informe “Agenda inicializada”. Deve-se tratar uma possível virada de mês durante a semana (3af 31/10/2023 e 4af 01/11/2023).
- **Inclusão de nova consulta** a qualquer momento da execução do programa, solicitando uma data. Se a data estiver fora da agenda semanal emita aviso de erro. Caso contrário, mostre os horários disponíveis. Caso não tenha nenhum horário disponível, informar "Data indisponível – tente outra data". Caso tenha, escolha o horário, solicite os demais dados, e informe “Consulta incluída”.
- **Exclusão de consulta**, buscando-se pela data/hora. Caso não exista, informar "Consulta inexistente". Caso contrário, deve ser feita a exclusão física desta consulta e informar "Consulta excluída".
- **Relatório 1**: mostrar consultas em uma determinada data, com todas as suas informações. Se a data estiver fora da agenda semanal deve-se emitir aviso de erro. Caso não se tenha consultas, gerar relatório com mensagem informativa.
- **Relatório 2**: agenda semanal, com todas as suas informações – também informar se não tem consultas.

Subrotina(s) auxiliar(es): pesquisa e ordenação deverão ser implementadas de forma recursiva.

A qualquer entrada de dados deve-se realizar tratamento de dados/validação (tipo/valor). O sistema deverá apresentar uma interface básica, com menu e controle de rolamento de tela.

Serão considerados para efeitos de avaliação: i) a corretude das funcionalidades do programa, ii) a otimização do programa, iii) a utilização de modularização/parametrização das tarefas e iv) adequação da interface. Haverá desconto de 0,5 por item não apresentado/mal estruturado.

| Valor | Item |
| --- | --- |
| 1,5 p/item | pesquisa recursiva e ordenação recursiva |
| 1,0 p/item | tipo(s) estruturado(s), main, inicialização, inclusão, exclusão, relatorio1 e relatorio2 |
