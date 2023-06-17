#include <stdio.h>

#include "queue.h" // contem funções uteis para filas
#include "proc.h"  // possui as funções dos processos
#include "stats.h" // possui as funções de estatisticas 
#include "utils.h" // possui funções uteis 

// Utilizando as variáveis globais definidas no 'main'
extern struct queue * ready;    // fila de aptos
extern struct queue * ready2;   // segunda fila de aptos
extern struct queue * blocked;  // fila de bloqueados
extern struct queue * finished; // fila de finalizados
// NOTE: essa fila de finalizados é utilizada apenas para
// as estatisticas finais

// variavel global que indica o tempo maximo que um processo pode executar ao todo
extern int MAX_TIME;

struct proc * scheduler(struct proc * current)
{
    struct proc *selected;
    double probability;

    // Para tratar o caso do início do sistema, quando nao tem ninguem rodando
    if (current != NULL)
    {
        // Verificando o estado em que o processo executando está
        switch (current->state)
        {
            // Caso esteja 'apto' é porque saiu por preempção
            case READY:
                // Adiciona ao fim da fila de aptos
                if (current->queue == 1) {
                    enqueue(ready, current);
                } else {
                    enqueue(ready2, current);
                }
                // Realizando as estatisticas para o processo que entra na fila de
                // aptos
                count_ready_in(current);
                break;
            // Caso o processo tenha saído como 'bloqueado', é porque fez uma E/S
            case BLOCKED:
                // Adicionando no final da fila de bloqueados
                enqueue(blocked, current);

                // Realizando as estatisticas para o processo que entra na fila de
                // bloqueados
                count_blocked_in(current);
                break;
            // Caso o processo tenha finalizado, estado 'finished'
            case FINISHED:
                // Adicionando-o na fila de finalizados
                enqueue(finished, current);

                // Realizando as estatisticas para o processo que entra na fila de
                // finalizados
                count_finished_in(current);
                break;
            default:
                printf("@@ ERRO no estado de saída do processo %d\n", current->pid);
        }
    }

    // Estratégia de seleção de um novo processo para executar

    // Se as filas de aptos estão vazias, nao há o que fazer
    if (isempty(ready) && isempty(ready2))
    {
        return NULL;
    }

    // Neste ponto, é a estrategia do algoritmo é implementada para selecionar
    // um processo

    // Estratégia para o PRIO STATIC:
    // printf(" FILA READY ANTES\n");
    // printqueue(ready);

    probability = make_rand(100);

    if (probability < 80 && !isempty(ready)) {
        // 80% de probabilidade - Selecionar processo da primeira fila (ready)
        selected = dequeue(ready);
    } else if (!isempty(ready2)) {
        // 20% de probabilidade - Selecionar processo da segunda fila (ready2)
        selected = dequeue(ready2);
    }

    // printf(" FILA READY DEPOIS\n");
    // printqueue(ready);

    // Verifica de qual fila o processo foi selecionado, e faz o seu devido
    // tratamento
    count_ready_out(selected);

    // Alterando o estado do processo selecionado para executando
    selected->state = RUNNING;

    // Retornando o processo selecionado
    return selected;
}
