#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Aluno {
  string nome;
  a;
  string matricula;
  string turma;
};

struct Disciplina {
  string nome;
  string codigo;
};

const int MAX_ALUNOS = 100;
const int MAX_DISCIPLINAS = 20;

string validarEntradaString(const string &prompt) {
  string entrada;
  do {
    cout << prompt;
    getline(cin, entrada);
    if (entrada.empty()) {
      cout << "Entrada inválida! Por favor, insira um valor não vazio.\n";
    }
  } while (entrada.empty());
  return entrada;
}

double validarNota(const string &prompt) {
  double nota;
  string entrada;
  bool valido = false;
  do {
    cout << prompt;
    getline(cin, entrada);
    try {
      nota = stod(entrada);
      if (nota >= 0 && nota <= 10) {
        valido = true;
      } else {
        cout << "Nota deve estar entre 0 e 10!\n";
      }
    } catch (...) {
      cout << "Entrada inválida! Insira um número.\n";
    }
  } while (!valido);
  return nota;
}

void cadastrarAluno(vector<Aluno> &alunos, const string &arquivo) {
  Aluno novoAluno;
  novoAluno.nome = validarEntradaString("Nome do aluno: ");
  novoAluno.matricula = validarEntradaString("Matrícula do aluno: ");
  novoAluno.turma = validarEntradaString("Turma do aluno: ");

  alunos.push_back(novoAluno);

  ofstream outFile(arquivo, ios::app);
  if (outFile.is_open()) {
    outFile << novoAluno.nome << ";" << novoAluno.matricula << ";"
            << novoAluno.turma << "\n";
    outFile.close();
    cout << "Aluno cadastrado com sucesso!\n";
  } else {
    cout << "Erro ao abrir arquivo " << arquivo << "\n";
  }
}

void cadastrarDisciplina(vector<Disciplina> &disciplinas,
                         const string &arquivo) {
  Disciplina novaDisciplina;
  novaDisciplina.nome = validarEntradaString("Nome da disciplina: ");
  novaDisciplina.codigo = validarEntradaString("Código da disciplina: ");

  disciplinas.push_back(novaDisciplina);

  ofstream outFile(arquivo, ios::app);
  if (outFile.is_open()) {
    outFile << novaDisciplina.nome << ";" << novaDisciplina.codigo << "\n";
    outFile.close();
    cout << "Disciplina cadastrada com sucesso!\n";
  } else {
    cout << "Erro ao abrir arquivo " << arquivo << "\n";
  }
}


void carregarDados(const string &arquivoAlunos,
                   const string &arquivoDisciplinas, const string &arquivoNotas,
                   vector<Aluno> &alunos, vector<Disciplina> &disciplinas,
                   double notas[][MAX_DISCIPLINAS]) {
  
  ifstream inAlunos(arquivoAlunos);
  string linha;
  while (getline(inAlunos, linha)) {
    Aluno aluno;
    size_t pos = 0;
    pos = linha.find(";");
    aluno.nome = linha.substr(0, pos);
    linha.erase(0, pos + 1);
    pos = linha.find(";");
    aluno.matricula = linha.substr(0, pos);
    aluno.turma = linha.substr(pos + 1);
    alunos.push_back(aluno);
  }
  inAlunos.close();

  
  ifstream inDisciplinas(arquivoDisciplinas);
  while (getline(inDisciplinas, linha)) {
    Disciplina disciplina;
    size_t pos = linha.find(";");
    disciplina.nome = linha.substr(0, pos);
    disciplina.codigo = linha.substr(pos + 1);
    disciplinas.push_back(disciplina);
  }
  inDisciplinas.close();

  
  ifstream inNotas(arquivoNotas);
  for (int i = 0; i < alunos.size() && getline(inNotas, linha); i++) {
    size_t pos = 0;
    for (int j = 0; j < disciplinas.size(); j++) {
      size_t nextPos = linha.find(";", pos);
      if (nextPos == string::npos)
        break;
      notas[i][j] = stod(linha.substr(pos, nextPos - pos));
      pos = nextPos + 1;
    }
  }
  inNotas.close();
}


void lancarNotas(vector<Aluno> &alunos, vector<Disciplina> &disciplinas,
                 double notas[][MAX_DISCIPLINAS], const string &arquivo) {
  string matricula = validarEntradaString("Matrícula do aluno: ");
  int alunoIdx = -1;
  for (int i = 0; i < alunos.size(); i++) {
    if (alunos[i].matricula == matricula) {
      alunoIdx = i;
      break;
    }
  }

  if (alunoIdx == -1) {
    cout << "Aluno não encontrado!\n";
    return;
  }

  string codDisciplina = validarEntradaString("Código da disciplina: ");
  int discIdx = -1;
  for (int i = 0; i < disciplinas.size(); i++) {
    if (disciplinas[i].codigo == codDisciplina) {
      discIdx = i;
      break;
    }
  }

  if (discIdx == -1) {
    cout << "Disciplina não encontrada!\n";
    return;
  }

  notas[alunoIdx][discIdx] = validarNota("Nota: ");

  ofstream outFile(arquivo);
  if (outFile.is_open()) {
    for (int i = 0; i < alunos.size(); i++) {
      for (int j = 0; j < disciplinas.size(); j++) {
        outFile << fixed << setprecision(2) << notas[i][j];
        if (j < disciplinas.size() - 1)
          outFile << ";";
      }
      outFile << "\n";
    }
    outFile.close();
    cout << "Nota lançada com sucesso!\n";
  } else {
    cout << "Erro ao abrir arquivo " << arquivo << "\n";
  }
}

void calcularMedias(vector<Aluno> &alunos, vector<Disciplina> &disciplinas,
                    double notas[][MAX_DISCIPLINAS], const string &arquivo) {
  ofstream outFile(arquivo, ios::app);
  if (!outFile.is_open()) {
    cout << "Erro ao abrir arquivo " << arquivo << "\n";
    return;
  }

  cout << "\nRelatório de Médias\n";
  outFile << "Relatório de Médias\n";

  for (int i = 0; i < alunos.size(); i++) {
    double soma = 0;
    int count = 0;
    for (int j = 0; j < disciplinas.size(); j++) {
      if (notas[i][j] > 0) {
        soma += notas[i][j];
        count++;
      }
    }
    double media = count > 0 ? soma / count : 0;
    cout << "Aluno: " << alunos[i].nome << " - Média Geral: " << fixed
         << setprecision(2) << media << "\n";
    outFile << "Aluno: " << alunos[i].nome << " - Média Geral: " << fixed
            << setprecision(2) << media << "\n";
  }
  outFile.close();
}

void consultarNotasAluno(vector<Aluno> &alunos, vector<Disciplina> &disciplinas,
                         double notas[][MAX_DISCIPLINAS]) {
  string matricula = validarEntradaString("Matrícula do aluno: ");
  int alunoIdx = -1;
  for (int i = 0; i < alunos.size(); i++) {
    if (alunos[i].matricula == matricula) {
      alunoIdx = i;
      break;
    }
  }

  if (alunoIdx == -1) {
    cout << "Aluno não encontrado!\n";
    return;
  }

  cout << "\nNotas do aluno " << alunos[alunoIdx].nome << ":\n";
  for (int j = 0; j < disciplinas.size(); j++) {
    cout << disciplinas[j].nome << ": " << fixed << setprecision(2)
         << notas[alunoIdx][j] << "\n";
  }
}

void consultarNotasDisciplina(vector<Aluno> &alunos,
                              vector<Disciplina> &disciplinas,
                              double notas[][MAX_DISCIPLINAS]) {
  string codDisciplina = validarEntradaString("Código da disciplina: ");
  int discIdx = -1;
  for (int i = 0; i < disciplinas.size(); i++) {
    if (disciplinas[i].codigo == codDisciplina) {
      discIdx = i;
      break;
    }
  }

  if (discIdx == -1) {
    cout << "Disciplina não encontrada!\n";
    return;
  }

  cout << "\nNotas da disciplina " << disciplinas[discIdx].nome << ":\n";
  for (int i = 0; i < alunos.size(); i++) {
    cout << alunos[i].nome << ": " << fixed << setprecision(2)
         << notas[i][discIdx] << "\n";
  }
}

int main() {
  vector<Aluno> alunos;
  vector<Disciplina> disciplinas;
  double notas[MAX_ALUNOS][MAX_DISCIPLINAS] = {0};

  const string arquivoAlunos = "alunos.txt";
  const string arquivoDisciplinas = "disciplinas.txt";
  const string arquivoNotas = "notas.txt";
  const string arquivoRelatorio = "relatorio.txt";

  carregarDados(arquivoAlunos, arquivoDisciplinas, arquivoNotas, alunos,
                disciplinas, notas);

  int opcao;
  do {
    cout << "\nSistema de Gerenciamento de Notas\n";
    cout << "1. Cadastrar Aluno\n";
    cout << "2. Cadastrar Disciplina\n";
    cout << "3. Lançar Notas\n";
    cout << "4. Calcular Médias\n";
    cout << "5. Consultar Notas de Aluno\n";
    cout << "6. Consultar Notas de Disciplina\n";
    cout << "7. Sair\n";
    cout << "Escolha uma opção: ";
    cin >> opcao;
    cin.ignore();

    switch (opcao) {
    case 1:
      cadastrarAluno(alunos, arquivoAlunos);
      break;
    case 2:
      cadastrarDisciplina(disciplinas, arquivoDisciplinas);
      break;
    case 3:
      lancarNotas(alunos, disciplinas, notas, arquivoNotas);
      break;
    case 4:
      calcularMedias(alunos, disciplinas, notas, arquivoRelatorio);
      break;
    case 5:
      consultarNotasAluno(alunos, disciplinas, notas);
      break;
    case 6:
      consultarNotasDisciplina(alunos, disciplinas, notas);
      break;
    case 7:
      cout << "Saindo...\n";
      break;
    default:
      cout << "Opção inválida!\n";
    }
  } while (opcao != 7);

  return 0;
}