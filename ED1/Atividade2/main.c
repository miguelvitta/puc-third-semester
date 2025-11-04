//Integrantes: Aimê Couto, Miguel Vitta, Victor Hugo Alves
#include "list.h"

int main(){
    FILE * f1 = fopen("arq.txt", "r");

    int window, id, qtd;

    Queue fila = create_queue();
    
    while(fscanf(f1, "%d %d %d", &window, &id, &qtd)>0){
        add(&fila, id, window, qtd, 0);
    }

    fclose(f1);

    FILE * f2 = fopen("output.txt", "w+");

    int current_window = 1;
    while (!is_queue_empty(&fila)) {
        int control_add = 0;
        int control_process = 0;
        while(control_process == 0 && control_add == 0) {
            Node* temp = get_front(&fila);
            if (temp->creation_window > current_window && control_process == 0 && temp->added == 1) {
                temp->progress++;
                fprintf(f2, "Janela: %d | ESCALONAMENTO | Process ID: %d | Progresso: %d/%d\n", current_window, id, temp->progress, temp->qtd_windows);
                control_process = 1;
            }
            if (temp->creation_window > current_window && control_add == 0 && temp->added == 0) {
                fprintf(f2, "Janela: %d | NOVO PROCESSO | Process ID: %d | Janelas necessárias: %d\n", current_window, id, temp->qtd_windows);
                control_process = 1;
            }
            if (temp->progress != temp->qtd_windows) {
                temp = remove_queue(&fila);
                add(&fila, temp->id, temp->creation_window, temp->qtd_windows, temp->progress);
            }
            else {
                temp = remove_queue(&fila);
            }
        }
        current_window++;
    }

    fclose(f2);
    
    return 0;
}