#include <iostream>
#include <string>
using namespace std;

// Função para validar entrada string (não vazia)
string validarEntradaString(const string &prompt)
{
  string entrada;
  do
  {
    cout << prompt;
    getline(cin, entrada);
    if (entrada.empty())
    {
      cout << "Entrada inválida! Por favor, insira um valor não vazio.\n";
    }
  } while (entrada.empty());
  return entrada;
}

// Função para validar nota entre 0 e 10
double validarNota(const string &prompt)
{
  double nota;
  string entrada;
  bool valido = false;
  do
  {
    cout << prompt;
    getline(cin, entrada);
    try
    {
      nota = stod(entrada);
      if (nota >= 0 && nota <= 10)
      {
        valido = true;
      }
      else
      {
        cout << "Nota deve estar entre 0 e 10!\n";
      }
    }
    catch (...)
    {
      cout << "Entrada inválida! Insira um número.\n";
    }
  } while (!valido);
  return nota;
}

// Função para limpar a tela (Windows ou Linux/Mac)
void limparTela()
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Função para imprimir texto centralizado no terminal
void imprimirCentralizado(const string &texto, int largura = 50)
{
  int espacos = (largura - (int)texto.size()) / 2;
  if (espacos < 0)
    espacos = 0;
  cout << string(espacos, ' ') << texto << "\n";
}
#include <vector>
#include <fstream>
#include <iomanip>

struct Aluno
{
  string nome;
  string matricula;
  string turma;
};

struct Disciplina
{
  string nome;
  string codigo;
};

const int MAX_ALUNOS = 100;
const int MAX_DISCIPLINAS = 20;

// Cadastrar aluno e salvar no arquivo
void cadastrarAluno(vector<Aluno> &alunos, const string &arquivo)
{
  limparTela();
  imprimirCentralizado("Cadastro de Aluno");

  Aluno novoAluno;
  novoAluno.nome = validarEntradaString("Nome do aluno: ");
  novoAluno.matricula = validarEntradaString("Matrícula do aluno: ");
  novoAluno.turma = validarEntradaString("Turma do aluno: ");

  alunos.push_back(novoAluno);

  ofstream outFile(arquivo, ios::app);
  if (outFile.is_open())
  {
    outFile << novoAluno.nome << ";" << novoAluno.matricula << ";" << novoAluno.turma << "\n";
    cout << "\nAluno cadastrado com sucesso!\n";
    outFile.close();
  }
  else
  {
    cout << "\nErro ao abrir arquivo " << arquivo << "\n";
  }
  cout << "Pressione ENTER para continuar...";
  cin.ignore();
}

// Cadastrar disciplina e salvar no arquivo
void cadastrarDisciplina(vector<Disciplina> &disciplinas, const string &arquivo)
{
  limparTela();
  imprimirCentralizado("Cadastro de Disciplina");

  Disciplina novaDisciplina;
  novaDisciplina.nome = validarEntradaString("Nome da disciplina: ");
  novaDisciplina.codigo = validarEntradaString("Código da disciplina: ");

  disciplinas.push_back(novaDisciplina);

  ofstream outFile(arquivo, ios::app);
  if (outFile.is_open())
  {
    outFile << novaDisciplina.nome << ";" << novaDisciplina.codigo << "\n";
    cout << "\nDisciplina cadastrada com sucesso!\n";
    outFile.close();
  }
  else
  {
    cout << "\nErro ao abrir arquivo " << arquivo << "\n";
  }
  cout << "Pressione ENTER para continuar...";
  cin.ignore();
}

// Carregar dados dos arquivos para os vetores e matriz de notas
void carregarDados(const string &arquivoAlunos, const string &arquivoDisciplinas,
                   const string &arquivoNotas, vector<Aluno> &alunos,
                   vector<Disciplina> &disciplinas, double notas[][MAX_DISCIPLINAS])
{

  alunos.clear();
  disciplinas.clear();

  ifstream inAlunos(arquivoAlunos);
  string linha;
  while (getline(inAlunos, linha))
  {
    Aluno aluno;
    size_t pos = linha.find(";");
    aluno.nome = linha.substr(0, pos);
    linha.erase(0, pos + 1);

    pos = linha.find(";");
    aluno.matricula = linha.substr(0, pos);
    aluno.turma = linha.substr(pos + 1);

    alunos.push_back(aluno);
  }
  inAlunos.close();

  ifstream inDisciplinas(arquivoDisciplinas);
  while (getline(inDisciplinas, linha))
  {
    Disciplina disciplina;
    size_t pos = linha.find(";");
    disciplina.nome = linha.substr(0, pos);
    disciplina.codigo = linha.substr(pos + 1);

    disciplinas.push_back(disciplina);
  }
  inDisciplinas.close();

  ifstream inNotas(arquivoNotas);
  for (int i = 0; i < (int)alunos.size() && getline(inNotas, linha); i++)
  {
    size_t pos = 0;
    for (int j = 0; j < (int)disciplinas.size(); j++)
    {
      size_t nextPos = linha.find(";", pos);
      if (nextPos == string::npos)
        nextPos = linha.size();

      string strNota = linha.substr(pos, nextPos - pos);
      try
      {
        notas[i][j] = stod(strNota);
      }
      catch (...)
      {
        notas[i][j] = 0;
      }
      pos = nextPos + 1;
    }
  }
  inNotas.close();
}
