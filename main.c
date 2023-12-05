#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 20
#define MAX_NAME_LENGTH 50
#define MAX_LOCATION_LENGTH 50
#define MAX_OBSERVATION_LENGTH 100

// Definição da estrutura para um registro no diário
typedef struct {
    char data[11]; // Formato: dd/mm/aaaa
    char horario[6]; // Formato: hh:mm
    char nome[MAX_NAME_LENGTH];
    char local[MAX_LOCATION_LENGTH];
    int duracao; // em minutos
    char observacao[MAX_OBSERVATION_LENGTH];
} Registro;

// Estrutura de nó para lista encadeada
typedef struct Node {
    Registro data;
    struct Node *next;
} Node;

// Definição da estrutura para o usuário
typedef struct {
    char senha[MAX_PASSWORD_LENGTH];
} Usuario;

// Protótipos de funções
void menuPrincipal(Usuario *usuario, Node **listaRegistros);
void adicionarRegistro(Node **listaRegistros);
void listarRegistros(Node *listaRegistros);
void editarRegistro(Node *listaRegistros);
void removerRegistro(Node **listaRegistros);
void editarSenha(Usuario *usuario);
int validarSenha(Usuario usuario);
void buscarRegistro(Node *listaRegistros);

int main() {
    
    
    // Inicialização do usuário
    Usuario usuario;
    strcpy(usuario.senha, "senha123"); // Senha padrão

    // Inicialização da lista encadeada de registros
    Node *listaRegistros = NULL;

    // Verifica a senha antes de entrar no sistema
    if (!validarSenha(usuario)) {
        printf("Senha incorreta. Encerrando o programa.\n");
        return 1;
    }

    // Menu principal
    menuPrincipal(&usuario, &listaRegistros);

    // Libera a memória alocada dinamicamente para a lista encadeada
    Node *current = listaRegistros;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}

void menuPrincipal(Usuario *usuario, Node **listaRegistros) {
    int opcao;

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Adicionar novo registro\n");
        printf("2. Listar registros\n");
        printf("3. Editar registro\n");
        printf("4. Remover registro\n");
        printf("5. Buscar registro\n");  
        printf("6. Editar senha\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarRegistro(listaRegistros);
                break;
            case 2:
                listarRegistros(*listaRegistros);
                break;
            case 3:
                editarRegistro(*listaRegistros);
                break;
            case 4:
                removerRegistro(listaRegistros);
                break;
            case 5:
                buscarRegistro(*listaRegistros);
                break;
            case 6:
                editarSenha(usuario);
                break;
            case 7:
                printf("Saindo do programa. Ate logo!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 7);
}

void adicionarRegistro(Node **listaRegistros) {
    // Aloca espaço para um novo nó
    Node *novoRegistro = (Node *)malloc(sizeof(Node));

    // Preenche os dados do novo registro
    printf("\n=== Adicionar Novo Registro ===\n");
    printf("Data (dd/mm/aaaa): ");
    scanf("%s", novoRegistro->data.data);
    printf("Horario (hh:mm): ");
    scanf("%s", novoRegistro->data.horario);
    printf("Nome: ");
    scanf("%s", novoRegistro->data.nome);
    printf("Local: ");
    scanf("%s", novoRegistro->data.local);
    printf("Duracao (minutos): ");
    scanf("%d", &novoRegistro->data.duracao);
    printf("Observacao: ");
    scanf("%s", novoRegistro->data.observacao);

    // Adiciona o novo nó à lista
    novoRegistro->next = *listaRegistros;
    *listaRegistros = novoRegistro;
}

void listarRegistros(Node *listaRegistros) {
    if (listaRegistros == NULL) {
        printf("Nenhum registro encontrado.\n");
    } else {
        printf("\n=== Listagem de Registros ===\n");
        int i = 1;
        while (listaRegistros != NULL) {
            printf("Registro %d:\n", i++);
            printf("Data: %s\n", listaRegistros->data.data);
            printf("Horario: %s\n", listaRegistros->data.horario);
            printf("Nome: %s\n", listaRegistros->data.nome);
            printf("Local: %s\n", listaRegistros->data.local);
            printf("Duracao: %d minutos\n", listaRegistros->data.duracao);
            printf("Observacao: %s\n", listaRegistros->data.observacao);
            printf("\n");
            listaRegistros = listaRegistros->next;
        }
    }
}

void editarRegistro(Node *listaRegistros) {
    int numeroRegistro;

    if (listaRegistros == NULL) {
        printf("Nenhum registro disponivel para edicao.\n");
        return;
    }

    // Lista os registros disponíveis
    listarRegistros(listaRegistros);

    // Solicita o número do registro a ser editado
    printf("Digite o numero do registro a ser editado: ");
    scanf("%d", &numeroRegistro);

    // Encontra o registro na posição desejada
    Node *current = listaRegistros;
    int i = 1;
    while (i < numeroRegistro && current != NULL) {
        current = current->next;
        i++;
    }

    // Verifica se o número do registro é válido
    if (current == NULL) {
        printf("Numero de registro invalido.\n");
        return;
    }

    // Solicita a edição dos dados
    printf("\n=== Editar Registro ===\n");
    printf("Data (dd/mm/aaaa): ");
    scanf("%s", current->data.data);
    printf("Horario (hh:mm): ");
    scanf("%s", current->data.horario);
    printf("Nome: ");
    scanf("%s", current->data.nome);
    printf("Local: ");
    scanf("%s", current->data.local);
    printf("Duracao (minutos): ");
    scanf("%d", &current->data.duracao);
    printf("Observacao: ");
    scanf("%s", current->data.observacao);
}

void removerRegistro(Node **listaRegistros) {
    int numeroRegistro;

    if (*listaRegistros == NULL) {
        printf("Nenhum registro disponivel para remocao.\n");
        return;
    }

    // Lista os registros disponíveis
    listarRegistros(*listaRegistros);

    // Solicita o número do registro a ser removido
    printf("Digite o numero do registro a ser removido: ");
    scanf("%d", &numeroRegistro);

    // Encontra o registro na posição desejada
    Node *current = *listaRegistros;
    Node *previous = NULL;
    int i = 1;
    while (i < numeroRegistro && current != NULL) {
        previous = current;
        current = current->next;
        i++;
    }

    // Verifica se o número do registro é válido
    if (current == NULL) {
        printf("Numero de registro invalido.\n");
        return;
    }

    // Remove o nó da lista
    if (previous == NULL) {
        // O registro a ser removido é o primeiro da lista
        *listaRegistros = current->next;
    } else {
        // O registro a ser removido não é o primeiro da lista
        previous->next = current->next;
    }

    // Libera a memória do nó removido
    free(current);
}

void buscarRegistro(Node *listaRegistros) {
    char nomeBusca[MAX_NAME_LENGTH];
    printf("\n=== Buscar Registro ===\n");
    printf("Digite o nome a ser buscado: ");
    scanf("%s", nomeBusca);

    Node *current = listaRegistros;
    int encontrados = 0;

    while (current != NULL) {
        if (strcmp(current->data.nome, nomeBusca) == 0) {
            printf("Registro encontrado:\n");
            printf("Data: %s\n", current->data.data);
            printf("Horario: %s\n", current->data.horario);
            printf("Nome: %s\n", current->data.nome);
            printf("Local: %s\n", current->data.local);
            printf("Duracao: %d minutos\n", current->data.duracao);
            printf("Observacao: %s\n", current->data.observacao);
            printf("\n");
            encontrados++;
        }
        current = current->next;
    }

    if (encontrados == 0) {
        printf("Nenhum registro encontrado para o nome '%s'.\n", nomeBusca);
    }
}

void editarSenha(Usuario *usuario) {
    char novaSenha[MAX_PASSWORD_LENGTH];
    char senhaAtual[MAX_PASSWORD_LENGTH];

    // Solicita a senha atual para verificar a autenticidade do usuário
    printf("\n=== Editar Senha ===\n");
    printf("Digite a senha atual: ");
    scanf("%s", senhaAtual);

    // Verifica se a senha atual está correta
    if (strcmp(senhaAtual, usuario->senha) != 0) {
        printf("Senha atual incorreta. A senha não foi alterada.\n");
        return;
    }

    // Solicita a nova senha
    printf("Digite a nova senha: ");
    scanf("%s", novaSenha);

    // Atualiza a senha
    strcpy(usuario->senha, novaSenha);

    printf("Senha alterada com sucesso.\n");

    // Solicita a senha novamente para continuar
    if (!validarSenha(*usuario)) {
        printf("Senha incorreta. Encerrando o programa.\n");
        exit(1); // Encerra o programa
    }

}

int validarSenha(Usuario usuario) {
    char senhaDigitada[MAX_PASSWORD_LENGTH];

    printf("Digite a senha de acesso: ");
    scanf("%s", senhaDigitada);

    return strcmp(senhaDigitada, usuario.senha) == 0;
}
