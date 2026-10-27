//
// Created by Mathias Carolino on 26/10/26.
//
#include <iostream>
#include <string>
using namespace std;

struct Conteudo {
    string texto;
    Conteudo* proximo;
};

struct Disciplina {
    string nome;
    int creditos;
    Conteudo* conteudos;
    Disciplina* proxima;
};

struct Aluno {
    string nome;
    string cpf;
    int idade;
    string matricula;
    Disciplina* disciplinas;
    Aluno* proximo;
};

Aluno* buscarAluno(Aluno* inicio, string matricula) {
    Aluno* aux = inicio;

    while (aux != NULL) {
        if (aux->matricula == matricula) {
            return aux;
        }
        aux = aux->proximo;
    }
    return NULL;
}

Disciplina* buscarDisciplina(Disciplina* inicio, string nome) {
    Disciplina* aux = inicio;

    while (aux != NULL) {
        if (aux->nome == nome) {
            return aux;
        }
        aux = aux->proxima;
    }
    return NULL;
}

void apagarConteudos(Conteudo*& inicio) {
    while (inicio != NULL) {
        Conteudo* aux = inicio;
        inicio = inicio->proximo;
        delete aux;
    }
}

void apagarDisciplinas(Disciplina*& inicio) {
    while (inicio != NULL) {
        Disciplina* aux = inicio;
        inicio = inicio->proxima;
        apagarConteudos(aux->conteudos);
        delete aux;
    }
}

void enfileirar(Aluno*& inicio, Aluno*& fim) {
    Aluno* novo = new Aluno;

    cout << "Nome: ";
    getline(cin >> ws, novo->nome);
    cout << "CPF: ";
    getline(cin >> ws, novo->cpf);
    cout << "Idade: ";
    cin >> novo->idade;
    cout << "Matricula: ";
    getline(cin >> ws, novo->matricula);

    if (buscarAluno(inicio, novo->matricula) != NULL) {
        cout << "Ja tem aluno com essa matricula!\n";
        delete novo;
        return;
    }

    novo->disciplinas = NULL;
    novo->proximo = NULL;

    if (inicio == NULL) {
        inicio = novo;
        fim = novo;
    } else {
        fim->proximo = novo;
        fim = novo;
    }
    cout << "Aluno entrou na fila!\n";
}

void desenfileirar(Aluno*& inicio, Aluno*& fim) {
    if (inicio == NULL) {
        cout << "Fila vazia!\n";
        return;
    }

    Aluno* aux = inicio;
    inicio = inicio->proximo;

    if (inicio == NULL) {
        fim = NULL;
    }

    cout << "Removendo: " << aux->nome << endl;
    apagarDisciplinas(aux->disciplinas);
    delete aux;
}

void mostrarPrimeiro(Aluno* inicio) {
    if (inicio == NULL) {
        cout << "Fila vazia!\n";
        return;
    }
    cout << "Primeiro: " << inicio->nome << endl;
    cout << "Matricula: " << inicio->matricula << endl;
}

void listarFila(Aluno* inicio) {
    if (inicio == NULL) {
        cout << "Fila vazia!\n";
        return;
    }

    Aluno* aux = inicio;
    while (aux != NULL) {
        cout << aux->nome << " - " << aux->matricula << endl;
        aux = aux->proximo;
    }
}

void adicionarDisciplina(Aluno* inicio) {
    string matricula;
    cout << "Matricula do aluno: ";
    getline(cin >> ws, matricula);

    Aluno* aluno = buscarAluno(inicio, matricula);
    if (aluno == NULL) {
        cout << "Aluno nao encontrado!\n";
        return;
    }

    Disciplina* nova = new Disciplina;
    cout << "Nome da disciplina: ";
    getline(cin >> ws, nova->nome);

    if (buscarDisciplina(aluno->disciplinas, nova->nome) != NULL) {
        cout << "Essa disciplina ja existe!\n";
        delete nova;
        return;
    }

    cout << "Quantidade de creditos: ";
    cin >> nova->creditos;
    nova->conteudos = NULL;
    nova->proxima = NULL;

    if (aluno->disciplinas == NULL) {
        aluno->disciplinas = nova;
    } else {
        Disciplina* aux = aluno->disciplinas;
        while (aux->proxima != NULL) {
            aux = aux->proxima;
        }
        aux->proxima = nova;
    }
    cout << "Disciplina adicionada!\n";
}

void removerDisciplina(Aluno* inicio) {
    string matricula, nome;
    cout << "Matricula do aluno: ";
    getline(cin >> ws, matricula);

    Aluno* aluno = buscarAluno(inicio, matricula);
    if (aluno == NULL) {
        cout << "Aluno nao encontrado!\n";
        return;
    }

    cout << "Disciplina para remover: ";
    getline(cin >> ws, nome);

    Disciplina* atual = aluno->disciplinas;
    Disciplina* anterior = NULL;

    while (atual != NULL && atual->nome != nome) {
        anterior = atual;
        atual = atual->proxima;
    }

    if (atual == NULL) {
        cout << "Disciplina nao encontrada!\n";
        return;
    }

    if (anterior == NULL) {
        aluno->disciplinas = atual->proxima;
    } else {
        anterior->proxima = atual->proxima;
    }

    apagarConteudos(atual->conteudos);
    delete atual;
    cout << "Disciplina removida!\n";
}

void listarDisciplinas(Aluno* inicio) {
    string matricula;
    cout << "Matricula do aluno: ";
    getline(cin >> ws, matricula);

    Aluno* aluno = buscarAluno(inicio, matricula);
    if (aluno == NULL) {
        cout << "Aluno nao encontrado!\n";
        return;
    }

    Disciplina* aux = aluno->disciplinas;
    if (aux == NULL) {
        cout << "Esse aluno nao tem disciplinas.\n";
        return;
    }

    while (aux != NULL) {
        cout << aux->nome << " - " << aux->creditos << " creditos\n";
        aux = aux->proxima;
    }
}

void adicionarConteudo(Aluno* inicio) {
    string matricula, nome;
    cout << "Matricula do aluno: ";
    getline(cin >> ws, matricula);

    Aluno* aluno = buscarAluno(inicio, matricula);
    if (aluno == NULL) {
        cout << "Aluno nao encontrado!\n";
        return;
    }

    cout << "Nome da disciplina: ";
    getline(cin >> ws, nome);

    Disciplina* disciplina = buscarDisciplina(aluno->disciplinas, nome);
    if (disciplina == NULL) {
        cout << "Disciplina nao encontrada!\n";
        return;
    }

    Conteudo* novo = new Conteudo;
    cout << "Novo conteudo: ";
    getline(cin >> ws, novo->texto);
    novo->proximo = NULL;

    if (disciplina->conteudos == NULL) {
        disciplina->conteudos = novo;
    } else {
        Conteudo* aux = disciplina->conteudos;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        aux->proximo = novo;
    }
    cout << "Conteudo adicionado!\n";
}

void removerConteudo(Aluno* inicio) {
    string matricula, nome, texto;
    cout << "Matricula do aluno: ";
    getline(cin >> ws, matricula);

    Aluno* aluno = buscarAluno(inicio, matricula);
    if (aluno == NULL) {
        cout << "Aluno nao encontrado!\n";
        return;
    }

    cout << "Nome da disciplina: ";
    getline(cin >> ws, nome);

    Disciplina* disciplina = buscarDisciplina(aluno->disciplinas, nome);
    if (disciplina == NULL) {
        cout << "Disciplina nao encontrada!\n";
        return;
    }

    cout << "Conteudo para remover: ";
    getline(cin >> ws, texto);

    Conteudo* atual = disciplina->conteudos;
    Conteudo* anterior = NULL;

    while (atual != NULL && atual->texto != texto) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        cout << "Conteudo nao encontrado!\n";
        return;
    }

    if (anterior == NULL) {
        disciplina->conteudos = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    delete atual;
    cout << "Conteudo removido!\n";
}

void listarConteudos(Aluno* inicio) {
    string matricula, nome;
    cout << "Matricula do aluno: ";
    getline(cin >> ws, matricula);

    Aluno* aluno = buscarAluno(inicio, matricula);
    if (aluno == NULL) {
        cout << "Aluno nao encontrado!\n";
        return;
    }

    cout << "Nome da disciplina: ";
    getline(cin >> ws, nome);

    Disciplina* disciplina = buscarDisciplina(aluno->disciplinas, nome);
    if (disciplina == NULL) {
        cout << "Disciplina nao encontrada!\n";
        return;
    }

    Conteudo* aux = disciplina->conteudos;
    if (aux == NULL) {
        cout << "Sem conteudos nessa disciplina.\n";
        return;
    }

    while (aux != NULL) {
        cout << "- " << aux->texto << endl;
        aux = aux->proximo;
    }
}

void listarTudo(Aluno* inicio) {
    if (inicio == NULL) {
        cout << "Nenhum aluno na fila!\n";
        return;
    }

    Aluno* aluno = inicio;
    while (aluno != NULL) {
        cout << "\nAluno: " << aluno->nome << endl;
        cout << "CPF: " << aluno->cpf << endl;
        cout << "Idade: " << aluno->idade << endl;
        cout << "Matricula: " << aluno->matricula << endl;

        Disciplina* disciplina = aluno->disciplinas;
        if (disciplina == NULL) {
            cout << "  Sem disciplinas.\n";
        }

        while (disciplina != NULL) {
            cout << "  Disciplina: " << disciplina->nome << endl;
            cout << "  Creditos: " << disciplina->creditos << endl;

            Conteudo* conteudo = disciplina->conteudos;
            if (conteudo == NULL) {
                cout << "    Sem conteudos.\n";
            }

            while (conteudo != NULL) {
                cout << "    - " << conteudo->texto << endl;
                conteudo = conteudo->proximo;
            }
            disciplina = disciplina->proxima;
        }
        aluno = aluno->proximo;
    }
}

void quantidadeAlunos(Aluno* inicio) {
    int quantidade = 0;
    Aluno* aux = inicio;
    while (aux != NULL) {
        quantidade++;
        aux = aux->proximo;
    }
    cout << "Alunos na fila: " << quantidade << endl;
}

void limparFila(Aluno*& inicio, Aluno*& fim) {
    while (inicio != NULL) {
        Aluno* aux = inicio;
        inicio = inicio->proximo;
        apagarDisciplinas(aux->disciplinas);
        delete aux;
    }
    fim = NULL;
}

