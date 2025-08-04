# Explicação do Programa de Gerenciamento de Notas

Este programa em C++ gerencia informações de alunos, disciplinas e notas em uma escola, permitindo cadastrar alunos e disciplinas, lançar notas, calcular médias e consultar informações. Ele utiliza arquivos de texto para armazenar dados e possui uma interface de menu interativa. Abaixo, explico cada parte do código de forma simples e prática.

---

## 1. **Estruturas e Bibliotecas**

### Bibliotecas Incluídas
O programa usa as seguintes bibliotecas padrão do C++:
- `<fstream>`: Para leitura e escrita em arquivos.
- `<iomanip>`: Para formatar a saída (como números com duas casas decimais).
- `<iostream>`: Para entrada e saída de dados no console.
- `<string>`: Para manipulação de strings.
- `<vector>`: Para listas dinâmicas (vetores que crescem conforme necessário).

### Estruturas de Dados
- **`Aluno`**: Armazena informações de um aluno:
  - `nome`: Nome do aluno.
  - `matricula`: Código único do aluno.
  - `turma`: Turma à qual o aluno pertence.
- **`Disciplina`**: Armazena informações de uma disciplina:
  - `nome`: Nome da disciplina.
  - `codigo`: Código único da disciplina.

### Constantes
- `MAX_ALUNOS` (100): Limite máximo de alunos no sistema.
- `MAX_DISCIPLINAS` (20): Limite máximo de disciplinas no sistema.

---

## 2. **Funções de Validação**

### `validarEntradaString`
- **O que faz**: Garante que o usuário insira uma string não vazia.
- **Como funciona**: Exibe uma mensagem (prompt), lê a entrada com `getline` e verifica se está vazia. Se estiver, pede novamente.
- **Exemplo**: Usada para ler nome, matrícula ou turma sem aceitar entradas em branco.

### `validarNota`
- **O que faz**: Garante que o usuário insira uma nota válida (número entre 0 e 10).
- **Como funciona**: Lê a entrada como string, converte para número com `stod` e verifica se está no intervalo correto. Se inválida, pede novamente.
- **Exemplo**: Usada ao lançar notas para garantir que sejam números válidos.

---

## 3. **Funções de Cadastro**

### `cadastrarAluno`
- **O que faz**: Adiciona um novo aluno à lista e ao arquivo `alunos.txt`.
- **Como funciona**:
  - Pede nome, matrícula e turma usando `validarEntradaString`.
  - Adiciona o aluno ao vetor `alunos` (um `vector<Aluno>`).
  - Salva os dados no arquivo `alunos.txt` no formato `nome;matricula;turma`.
- **Exemplo**: Se o usuário cadastra "João Silva", matrícula "123", turma "A", o arquivo recebe a linha `João Silva;123;A`.

### `cadastrarDisciplina`
- **O que faz**: Adiciona uma nova disciplina à lista e ao arquivo `disciplinas.txt`.
- **Como funciona**:
  - Pede nome e código da disciplina usando `validarEntradaString`.
  - Adiciona a disciplina ao vetor `disciplinas` (um `vector<Disciplina>`).
  - Salva os dados no arquivo `disciplinas.txt` no formato `nome;codigo`.
- **Exemplo**: Para a disciplina "Matemática" com código "MAT01", o arquivo recebe `Matemática;MAT01`.

---

## 4. **Carregamento de Dados**

### `carregarDados`
- **O que faz**: Lê dados dos arquivos `alunos.txt`, `disciplinas.txt` e `notas.txt` para carregar no programa.
- **Como funciona**:
  - **Alunos**: Lê cada linha de `alunos.txt`, separa os campos (nome, matrícula, turma) pelo delimitador `;` e adiciona ao vetor `alunos`.
  - **Disciplinas**: Lê cada linha de `disciplinas.txt`, separa nome e código pelo `;` e adiciona ao vetor `disciplinas`.
  - **Notas**: Lê `notas.txt`, onde cada linha contém as notas de um aluno separadas por `;`, e preenche a matriz `notas` (um array bidimensional `double[MAX_ALUNOS][MAX_DISCIPLINAS]`).
- **Exemplo**: Se `alunos.txt` tem `João Silva;123;A`, o vetor `alunos` ganha um `Aluno` com esses dados.

---

## 5. **Lançamento de Notas**

### `lancarNotas`
- **O que faz**: Associa uma nota a um aluno em uma disciplina e salva no arquivo `notas.txt`.
- **Como funciona**:
  - Pede a matrícula do aluno e o código da disciplina.
  - Busca o índice do aluno no vetor `alunos` e da disciplina no vetor `disciplinas`.
  - Se ambos existem, pede a nota com `validarNota` e armazena na matriz `notas[alunoIdx][discIdx]`.
  - Salva todas as notas no arquivo `notas.txt`, com cada linha representando as notas de um aluno separadas por `;`.
- **Exemplo**: Para o aluno com matrícula "123" na disciplina "MAT01" com nota 8.5, a matriz `notas` é atualizada e o arquivo `notas.txt` reflete a mudança.

---

## 6. **Cálculo de Médias**

### `calcularMedias`
- **O que faz**: Calcula a média geral de cada aluno e salva o relatório no arquivo `relatorio.txt`.
- **Como funciona**:
  - Para cada aluno, soma todas as notas válidas (maiores que 0) e divide pelo número de notas.
  - Exibe a média no console e escreve no arquivo `relatorio.txt` no formato `Aluno: nome - Média Geral: valor`.
- **Exemplo**: Se João tem notas 8.0 e 7.0, a média é 7.5, e o relatório mostra `Aluno: João Silva - Média Geral: 7.50`.

---

## 7. **Consultas**

### `consultarNotasAluno`
- **O que faz**: Mostra todas as notas de um aluno específico.
- **Como funciona**:
  - Pede a matrícula do aluno e busca seu índice no vetor `alunos`.
  - Exibe o nome do aluno e suas notas para cada disciplina, usando a matriz `notas`.
- **Exemplo**: Para o aluno "João Silva", mostra algo como `Matemática: 8.00`, `Português: 7.00`.

### `consultarNotasDisciplina`
- **O que faz**: Mostra as notas de todos os alunos em uma disciplina específica.
- **Como funciona**:
  - Pede o código da disciplina e busca seu índice no vetor `disciplinas`.
  - Exibe o nome da disciplina e as notas de cada aluno, usando a matriz `notas`.
- **Exemplo**: Para a disciplina "MAT01", mostra algo como `João Silva: 8.00`, `Maria Souza: 9.00`.

---

## 8. **Função Principal (`main`)**

- **O que faz**: Controla o fluxo do programa com um menu interativo.
- **Como funciona**:
  - Inicializa os vetores `alunos` e `disciplinas` e a matriz `notas` (zerada).
  - Define os nomes dos arquivos: `alunos.txt`, `disciplinas.txt`, `notas.txt` e `relatorio.txt`.
  - Carrega os dados existentes com `carregarDados`.
  - Exibe um menu com 7 opções:
    1. Cadastrar aluno.
    2. Cadastrar disciplina.
    3. Lançar notas.
    4. Calcular médias.
    5. Consultar notas de um aluno.
    6. Consultar notas de uma disciplina.
    7. Sair.
  - Usa um laço `do-while` para repetir o menu até o usuário escolher "Sair" (opção 7).
- **Exemplo**: O usuário escolhe "1", cadastra um aluno, e o menu reaparece para novas ações.

---

## 9. **Funcionamento Geral**

- **Entrada/Saída**: O programa interage com o usuário via console, usando `cout` para exibir mensagens e `cin`/`getline` para ler entradas.
- **Armazenamento**: Usa arquivos de texto para persistência de dados:
  - `alunos.txt`: Lista de alunos.
  - `disciplinas.txt`: Lista de disciplinas.
  - `notas.txt`: Matriz de notas.
  - `relatorio.txt`: Relatório de médias.
- **Estrutura**: O programa é modular, com funções específicas para cada tarefa, facilitando manutenção e expansão.
- **Validação**: Garante entradas válidas com `validarEntradaString` e `validarNota`, evitando erros.

---

## 10. **Exemplo de Uso**

1. O usuário inicia o programa e vê o menu.
2. Escolhe "1" para cadastrar um aluno (ex.: "João Silva", matrícula "123", turma "A").
3. Escolhe "2" para cadastrar uma disciplina (ex.: "Matemática", código "MAT01").
4. Escolhe "3" para lançar a nota 8.5 para João na Matemática.
5. Escolhe "4" para calcular a média de João (8.50, já que só tem uma nota).
6. Escolhe "5" para ver todas as notas de João ou "6" para ver todas as notas de Matemática.
7. Escolhe "7" para sair.

---

Este programa é uma solução prática para gerenciar notas escolares, com uma interface simples e armazenamento persistente em arquivos. Ele pode ser expandido para incluir mais funcionalidades, como edição de dados ou relatórios mais detalhados.