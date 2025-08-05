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
