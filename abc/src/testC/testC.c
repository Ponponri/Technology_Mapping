#include "base/main/main.h"
#include <stdio.h>
#include <string.h>
#include "testC.h"

ABC_NAMESPACE_IMPL_START

double delayInv[4][2];
double powerInv[4];
double delayNand[4][2];
double powerNand[4];

int TestC_FirstFunction(Abc_Ntk_t * pNtk);
int TestC_Part1(Abc_Ntk_t * pNtk);
int TestC_Part2(Abc_Ntk_t * pNtk, int argc, char **argv);
int TestC_Hw2(Abc_Ntk_t * pNtk);

// Test

int TestC_FirstFunctionAbc(Abc_Frame_t * pAbc){
    Abc_Ntk_t *pNtk;
    int result;
    pNtk = Abc_FrameReadNtk(pAbc);

    if(pNtk == NULL){
        Abc_Print(-1, "Test_FirstFunctionAbc: Getting the target network fails.\n");
        return 0;
    }

    result = TestC_FirstFunction(pNtk);

    return result;
}

int TestC_FirstFunction(Abc_Ntk_t * pNtk){
    if(!Abc_NtkIsStrash(pNtk)){
        Abc_Print(-1, "TestC_FirstFunction: This command is only application to strashed networks.\n");
        return 0;
    }

    Abc_Print(1, "The network %s has:\n", Abc_NtkName(pNtk));
    Abc_Print(1, "\t- %d primary inputs;\n", Abc_NtkPiNum(pNtk));
    Abc_Print(1, "\t- %d primary outputs;\n", Abc_NtkPoNum(pNtk));
    Abc_Print(1, "\t- %d nodes;\n", Abc_NtkNodeNum(pNtk));
    return 1;

}

// hw2
struct node* init_graph(Abc_Ntk_t *pNtk){
    Abc_Obj_t * current_obj;
    Abc_Obj_t * pre_obj;
    Abc_Obj_t * post_obj;
    struct node* head=NULL;
    struct node* end=NULL;
    struct node* current=NULL;
    struct node* tmp=NULL;
    struct node* previous=NULL;
    struct list* current_list=NULL;
    struct list* previous_list=NULL;
    int count = 0;
    char node_name[MAX_SIZE];
    // init head
    head = malloc(sizeof(struct node));
    strcpy(head->name,"head");
    head->id = count++;
    head->type = -2;
    head->next = NULL;
    head->last = NULL;
	head->pre = NULL;
	head->post = NULL;
    // init end
    end = malloc(sizeof(struct node));
    strcpy(end->name,"end");
    end->type = -2;
    end->next = NULL;
    end->last = NULL;
	end->pre = NULL;
	end->post = NULL;

    // init pi
    // printf("\t-pi\n");
    for(int i=0;i<Abc_NtkPiNum(pNtk);i++){
        current_obj = Abc_NtkPi(pNtk,i);
        current = malloc(sizeof(struct node));
        strcpy(current->name,Abc_ObjName(current_obj));
        current->id = count++;
        current->type = 0;

        current->next = NULL;
        current->last = NULL;
        current->pre = NULL;
        current->post = NULL;
        // next
        if(i == 0){
            head->next = current;
            current->last = head;
            previous = current;
        }
        else{
            previous->next = current;
            current->last = previous;
            previous = current;
        }
        // pre
        current_list = malloc(sizeof(struct list));
        current_list->next = NULL;
        current_list->nextNode = head;
        current->pre = current_list;
        // head post
        if(head->post == NULL){
            current_list = malloc(sizeof(struct list));
            current_list->next = NULL;
            current_list->nextNode = current;
            head->post = current_list;
        }
        else{
            current_list = head->post;
            while(current_list != NULL){
                previous_list = current_list;
                current_list = current_list->next;
            }
            current_list = malloc(sizeof(struct list));
            current_list->next = NULL;
            current_list->nextNode = current;
            previous_list->next = current_list;
        }
    }
    // init internal node
    // printf("\t-internal\n");
    for(int i=0;i<Abc_NtkObjNum(pNtk);i++){
        current_obj = Abc_NtkObj(pNtk,i);
        if(Abc_ObjIsPi(current_obj) == 0 && Abc_ObjIsPo(current_obj) == 0){
            // inv
            for(int j=0;j<Abc_ObjFaninNum(current_obj);j++){
                pre_obj = Abc_ObjFanin(current_obj,j);
                tmp = NULL;
                // pre_obj is not pi
                if(Abc_ObjIsPi(pre_obj) == 0){
                    if(j == 0 && current_obj->fCompl0 == 0){
                        current = malloc(sizeof(struct node));
                        strcpy(current->name,Abc_ObjName(current_obj));
                        strcat(current->name,"_inv0");

                        current->id = count++;
                        current->type = 1;
                        current->next = NULL;
                        current->last = NULL;
                        current->pre = NULL;
                        current->post = NULL;
                        // next
                        previous->next = current;
                        current->last = previous;
                        previous = current;
                        // pre
                        current_list = malloc(sizeof(struct list));
                        current_list->next = NULL;
                        tmp = head;
                        while(tmp != NULL){
                            strcpy(node_name,Abc_ObjName(pre_obj));
                            strcat(node_name,"_nand");
                            if(strcmp(tmp->name,node_name)==0){
                                break;
                            }
                            tmp = tmp->next;
                        }
                        current_list->nextNode = tmp;
                        current->pre = current_list;
                    }
                    else if(j == 1 && current_obj->fCompl1 == 0){
                        current = malloc(sizeof(struct node));
                        strcpy(current->name,Abc_ObjName(current_obj));
                        strcat(current->name,"_inv1");

                        current->id = count++;
                        current->type = 1;
                        current->next = NULL;
                        current->last = NULL;
                        current->pre = NULL;
                        current->post = NULL;
                        // next
                        previous->next = current;
                        current->last = previous;
                        previous = current;
                        // pre
                        current_list = malloc(sizeof(struct list));
                        current_list->next = NULL;
                        tmp = head;
                        while(tmp != NULL){
                            strcpy(node_name,Abc_ObjName(pre_obj));
                            strcat(node_name,"_nand");
                            if(strcmp(tmp->name,node_name)==0){
                                break;
                            }
                            tmp = tmp->next;
                        }
                        current_list->nextNode = tmp;
                        current->pre = current_list;
                    }
                }
                // pre_obj is pi
                else if(Abc_ObjIsPi(pre_obj) == 1){
                    if(j == 0 && current_obj->fCompl0 == 1){
                        current = malloc(sizeof(struct node));
                        strcpy(current->name,Abc_ObjName(current_obj));
                        strcat(current->name,"_inv0");

                        current->id = count++;
                        current->type = 1;
                        current->next = NULL;
                        current->last = NULL;
                        current->pre = NULL;
                        current->post = NULL;
                        // next 
                        previous->next = current;
                        current->last = previous;
                        previous = current;
                        // pre
                        current_list = malloc(sizeof(struct list));
                        current_list->next = NULL;
                        tmp = head;
                        while(tmp != NULL){
                            strcpy(node_name,Abc_ObjName(pre_obj));
                            if(strcmp(tmp->name,node_name)==0){
                                break;
                            }
                            tmp = tmp->next;
                        }
                        current_list->nextNode = tmp;
                        current->pre = current_list;
                    }
                    else if(j == 1 && current_obj->fCompl1 == 1){
                        current = malloc(sizeof(struct node));
                        strcpy(current->name,Abc_ObjName(current_obj));
                        strcat(current->name,"_inv1");

                        current->id = count++;
                        current->type = 1;
                        current->next = NULL;
                        current->last = NULL;
                        current->pre = NULL;
                        current->post = NULL;
                        // next 
                        previous->next = current;
                        current->last = previous;
                        previous = current;
                        // pre
                        current_list = malloc(sizeof(struct list));
                        current_list->next = NULL;
                        tmp = head;
                        while(tmp != NULL){
                            strcpy(node_name,Abc_ObjName(pre_obj));
                            if(strcmp(tmp->name,node_name)==0){
                                break;
                            }
                            tmp = tmp->next;
                        }
                        current_list->nextNode = tmp;
                        current->pre = current_list;
                    }
                }
                // pre-post
                if(tmp != NULL){
                    if(tmp->post == NULL){
                        current_list = malloc(sizeof(struct list));
                        current_list->next = NULL;
                        current_list->nextNode = current;
                        tmp->post = current_list;
                    }
                    else{
                        current_list = malloc(sizeof(struct list));
                        current_list->next = NULL;
                        current_list->nextNode = current;
                        previous_list = tmp->post;
                        while(previous_list->next != NULL){
                            previous_list = previous_list->next;
                        }
                        previous_list->next = current_list;
                    }     
                }

                
            }
            //nand
            current = malloc(sizeof(struct node));
            strcpy(current->name,Abc_ObjName(current_obj));
            strcat(current->name,"_nand");
            current->id = count++;
            current->type = 2;

            current->next = NULL;
            current->last = NULL;
            current->pre = NULL;
            current->post = NULL;
            // next
            previous->next = current;
            current->last = previous;
            previous = current;
            // pre
            for(int j=0;j<Abc_ObjFaninNum(current_obj);j++){
                pre_obj = Abc_ObjFanin(current_obj,j); 
                current_list = malloc(sizeof(struct list));
                current_list->next = NULL;
                tmp = NULL;
                if(Abc_ObjIsPi(pre_obj) == 0){
                    if(j == 0 && current_obj->fCompl0 == 0){
                        tmp = head;
                        while(tmp != NULL){
                            strcpy(node_name,Abc_ObjName(current_obj));
                            strcat(node_name,"_inv0");
                            if(strcmp(tmp->name,node_name) == 0){
                                break;
                            }
                            tmp = tmp->next;
                        }
                    }
                    else if(j == 0 && current_obj->fCompl0 == 1){
                        tmp = head;
                        while(tmp != NULL){
                            strcpy(node_name,Abc_ObjName(pre_obj));
                            strcat(node_name,"_nand");
                            if(strcmp(tmp->name,node_name) == 0){
                                break;
                            }
                            tmp = tmp->next;
                        }
                    }
                    else if(j == 1 && current_obj->fCompl1 == 0){
                        tmp = head;
                        while(tmp != NULL){
                            strcpy(node_name,Abc_ObjName(current_obj));
                            strcat(node_name,"_inv1");
                            if(strcmp(tmp->name,node_name) == 0){
                                break;
                            }
                            tmp = tmp->next;
                        }
                    }
                    else if(j == 1 && current_obj->fCompl1 == 1){
                        tmp = head;
                        while(tmp != NULL){
                            strcpy(node_name,Abc_ObjName(pre_obj));
                            strcat(node_name,"_nand");
                            if(strcmp(tmp->name,node_name) == 0){
                                break;
                            }
                            tmp = tmp->next;
                        }
                    }
                }
                else if(Abc_ObjIsPi(pre_obj) == 1){
                    if(j == 0 && current_obj->fCompl0 == 1){
                        tmp = head;
                        while(tmp != NULL){
                            strcpy(node_name,Abc_ObjName(current_obj));
                            strcat(node_name,"_inv0");
                            if(strcmp(tmp->name,node_name) == 0){
                                break;
                            }
                            tmp = tmp->next;
                        }
                    }
                    else if(j == 0 && current_obj->fCompl0 == 0){
                        tmp = head;
                        while(tmp != NULL){
                            strcpy(node_name,Abc_ObjName(pre_obj));
                            if(strcmp(tmp->name,node_name) == 0){
                                break;
                            }
                            tmp = tmp->next;
                        }
                    }
                    else if(j == 1 && current_obj->fCompl1 == 1){
                        tmp = head;
                        while(tmp != NULL){
                            strcpy(node_name,Abc_ObjName(current_obj));
                            strcat(node_name,"_inv1");
                            if(strcmp(tmp->name,node_name) == 0){
                                break;
                            }
                            tmp = tmp->next;
                        }
                    }
                    else if(j == 1 && current_obj->fCompl1 == 0){
                        tmp = head;
                        while(tmp != NULL){
                            strcpy(node_name,Abc_ObjName(pre_obj));
                            if(strcmp(tmp->name,node_name) == 0){
                                break;
                            }
                            tmp = tmp->next;
                        }
                    }
                }
                
                current_list->nextNode = tmp;

                if(j == 0){
                    current->pre = current_list;
                    previous_list = current_list;
                }
                else{
                    previous_list->next = current_list;
                    previous_list = current_list;
                }
                // pre-post
                if(tmp->post == NULL){
                    current_list = malloc(sizeof(struct list));
                    current_list->next = NULL;
                    current_list->nextNode = current;
                    tmp->post = current_list;
                }
                else{
                    current_list = malloc(sizeof(struct list));
                    current_list->next = NULL;
                    current_list->nextNode = current;
                    previous_list = tmp->post;
                    while(previous_list->next != NULL){
                        previous_list = previous_list->next;
                    }
                    previous_list->next = current_list;
                }

            }
        }
    }
    
    // init po
    // printf("\t-po\n");
    for(int i=0;i<Abc_NtkPoNum(pNtk);i++){
        current_obj = Abc_NtkPo(pNtk,i);
        // printf("po\n");
        for(int j=0;j<Abc_ObjFaninNum(current_obj);j++){
            pre_obj = Abc_ObjFanin(current_obj,j);
            // pre_obj is not pi
            tmp = NULL;
            if(Abc_ObjIsPi(pre_obj) == 0){
                if(j == 0){
                    current = malloc(sizeof(struct node));
                    strcpy(current->name,Abc_ObjName(current_obj));
                    if(current_obj->fCompl0 == 0){
                        current->type = 1;
                    }
                    else if(current_obj->fCompl0 == 1){
                        current->type = -1;
                    }
                    
                    current->id = count++;
                    current->next = NULL;
                    current->last = NULL;
                    current->pre = NULL;
                    current->post = NULL;
                    // next
                    previous->next = current;
                    current->last = previous;
                    previous = current;
                    // pre
                    current_list = malloc(sizeof(struct list));
                    current_list->next = NULL;
                    tmp = head;
                    while(tmp != NULL){
                        strcpy(node_name,Abc_ObjName(pre_obj));
                        strcat(node_name,"_nand");
                        if(strcmp(tmp->name,node_name)==0){
                            break;
                        }
                        tmp = tmp->next;
                    }
                    current_list->nextNode = tmp;
                    current->pre = current_list;
                    // pre-post
                    
                    if(tmp->post == NULL){
                        current_list = malloc(sizeof(struct list));
                        current_list->next = NULL;
                        current_list->nextNode = current;
                        tmp->post = current_list;
                    }
                    else{
                        current_list = malloc(sizeof(struct list));
                        current_list->next = NULL;
                        current_list->nextNode = current;
                        previous_list = tmp->post;
                        while(previous_list->next != NULL){
                            previous_list = previous_list->next;
                        }
                        previous_list->next = current_list;
                    }
                    
                    // post
                    current_list = malloc(sizeof(struct list));
                    current_list->next = NULL;
                    current_list->nextNode = end;
                    current->post = current_list;

                }
                else if(j == 1){
                    current = malloc(sizeof(struct node));
                    strcpy(current->name,Abc_ObjName(current_obj));
                    if(current_obj->fCompl0 == 0){
                        current->type = 1;
                    }
                    else if(current_obj->fCompl0 == 1){
                        current->type = -1;
                    }

                    current->id = count++;
                    current->next = NULL;
                    current->last = NULL;
                    current->pre = NULL;
                    current->post = NULL;
                    // next 
                    previous->next = current;
                    current->last = previous;
                    previous = current;
                    // pre
                    current_list = malloc(sizeof(struct list));
                    current_list->next = NULL;
                    tmp = head;
                    while(tmp != NULL){
                        strcpy(node_name,Abc_ObjName(pre_obj));
                        strcat(node_name,"_nand");
                        if(strcmp(tmp->name,node_name)==0){
                            break;
                        }
                        tmp = tmp->next;
                    }
                    current_list->nextNode = tmp;
                    current->pre = current_list;
                    // pre-post

                    if(tmp->post == NULL){
                        current_list = malloc(sizeof(struct list));
                        current_list->next = NULL;
                        current_list->nextNode = current;
                        tmp->post = current_list;
                    }
                    else{
                        current_list = malloc(sizeof(struct list));
                        current_list->next = NULL;
                        current_list->nextNode = current;
                        previous_list = tmp->post;
                        while(previous_list->next != NULL){
                            previous_list = previous_list->next;
                        }
                        previous_list->next = current_list;
                    }
                    
                    // post
                    current_list = malloc(sizeof(struct list));
                    current_list->next = NULL;
                    current_list->nextNode = end;
                    current->post = current_list;

                }
            }
            // pre_obj is pi
            else if(Abc_ObjIsPi(pre_obj) == 1){
                if(j == 0){
                    current = malloc(sizeof(struct node));
                    strcpy(current->name,Abc_ObjName(current_obj));
                    if(current_obj->fCompl0 == 0){
                        current->type = -1;
                    }
                    else if(current_obj->fCompl0 == 1){
                        current->type = 1;
                    }

                    current->id = count++;
                    current->next = NULL;
                    current->last = NULL;
                    current->pre = NULL;
                    current->post = NULL;
                    // next 
                    previous->next = current;
                    current->last = previous;
                    previous = current;
                    // pre
                    current_list = malloc(sizeof(struct list));
                    current_list->next = NULL;
                    tmp = head;
                    while(tmp != NULL){
                        strcpy(node_name,Abc_ObjName(pre_obj));
                        // strcat(node_name,"_nand");
                        if(strcmp(tmp->name,node_name)==0){
                            break;
                        }
                        tmp = tmp->next;
                    }
                    current_list->nextNode = tmp;
                    current->pre = current_list;
                    //pre-post

                    if(tmp->post == NULL){
                        current_list = malloc(sizeof(struct list));
                        current_list->next = NULL;
                        current_list->nextNode = current;
                        tmp->post = current_list;
                    }
                    else{
                        current_list = malloc(sizeof(struct list));
                        current_list->next = NULL;
                        current_list->nextNode = current;
                        previous_list = tmp->post;
                        while(previous_list->next != NULL){
                            previous_list = previous_list->next;
                        }
                        previous_list->next = current_list;
                    }
                    
                    // post
                    current_list = malloc(sizeof(struct list));
                    current_list->next = NULL;
                    current_list->nextNode = end;
                    current->post = current_list;
                }
                else if(j == 1){
                    current = malloc(sizeof(struct node));
                    strcpy(current->name,Abc_ObjName(current_obj));
                    if(current_obj->fCompl0 == 0){
                        current->type = -1;
                    }
                    else if(current_obj->fCompl0 == 1){
                        current->type = 1;
                    }

                    current->id = count++;
                    current->next = NULL;
                    current->last = NULL;
                    current->pre = NULL;
                    current->post = NULL;
                    // next 
                    previous->next = current;
                    current->last = previous;
                    previous = current;
                    // pre
                    current_list = malloc(sizeof(struct list));
                    current_list->next = NULL;
                    tmp = head;
                    while(tmp != NULL){
                        strcpy(node_name,Abc_ObjName(pre_obj));
                        // strcat(node_name,"_nand");
                        if(strcmp(tmp->name,node_name)==0){
                            break;
                        }
                        tmp = tmp->next;
                    }
                    current_list->nextNode = tmp;
                    current->pre = current_list;
                    // pre-post

                    if(tmp->post == NULL){
                        current_list = malloc(sizeof(struct list));
                        current_list->next = NULL;
                        current_list->nextNode = current;
                        tmp->post = current_list;
                    }
                    else{
                        current_list = malloc(sizeof(struct list));
                        current_list->next = NULL;
                        current_list->nextNode = current;
                        previous_list = tmp->post;
                        while(previous_list->next != NULL){
                            previous_list = previous_list->next;
                        }
                        previous_list->next = current_list;
                    }
                    
                    // post
                    current_list = malloc(sizeof(struct list));
                    current_list->next = NULL;
                    current_list->nextNode = end;
                    current->post = current_list;
                }
            }
        }

        // end pre    
        // printf("end pre\n");
        if(end->pre == NULL){
            current_list = malloc(sizeof(struct list));
            current_list->next = NULL;
            current_list->nextNode = current;
            end->pre = current_list;
        }
        else{
            current_list = end->pre;
            while(current_list->next != NULL){
                current_list = current_list->next;
            }
            previous_list = current_list;
            current_list = malloc(sizeof(struct list));
            current_list->next = NULL;
            current_list->nextNode = current;
            previous_list->next = current_list;
        }

        // end
        // printf("end\n");
        if(i == Abc_NtkPoNum(pNtk)-1){
            current->next = end;
            end->last = current;
        }
    }

    end->id = count;
    return head;
}

void compute_delayAndPower(struct node* head){
    struct node* current=NULL;
    struct node* previous=NULL;
    struct list* current_list;

    int fout_num;
    double min_delay;
    int min_delay_inx;

    current = head;
    while(current != NULL){
        current->arrival = -1;
        current->require = MAX_SIZE*1000;
        if(current->type == 1){
            current_list = current->post;
            fout_num = 0;
            while(current_list != NULL){
                fout_num += 1;
                current_list = current_list->next;
            }
            min_delay = MAX_SIZE*100;
            for(int i=0;i<4;i++){
                current->delay[i] = delayInv[i][0] + delayInv[i][1]*fout_num;
                current->power[i] = powerInv[i];
                if(current->delay[i] < min_delay){
                    min_delay = current->delay[i];
                    min_delay_inx = i;
                }
            }
            current->select = min_delay_inx;
        }
        else if(current->type == 2){
            current_list = current->post;
            fout_num = 0;
            while(current_list != NULL){
                fout_num += 1;
                current_list = current_list->next;
            }
            min_delay = MAX_SIZE*100;
            for(int i=0;i<4;i++){
                current->delay[i] = delayNand[i][0] + delayNand[i][1]*fout_num;
                current->power[i] = powerNand[i];
                if(current->delay[i] < min_delay){
                    min_delay = current->delay[i];
                    min_delay_inx = i;
                }
            }
            current->select = min_delay_inx;
        }
        else{
            for(int i=0;i<4;i++){
                current->delay[i] = 0;
                current->power[i] = 0;
            }
            current->select = 0;
        }
        current = current->next;
    }

}

void compute_arrival(struct node* head){
    struct node* current;
    struct list* current_list;
    head->arrival = 0;
    current = head;
    while(current != NULL){
        current_list = current->post;
        while(current_list != NULL){
            if(current_list->nextNode->type == -2 || current_list->nextNode->type == -1 || current_list->nextNode->type == 0){
                if(current_list->nextNode->arrival < current->arrival){
                    current_list->nextNode->arrival = current->arrival;
                }
            }
            else{
                // if(current_list->nextNode->arrival < current->arrival + current->delay[current->select]){
                //     current_list->nextNode->arrival = current->arrival + current->delay[current->select];
                // }
                if(current_list->nextNode->arrival < current->arrival + current_list->nextNode->delay[current_list->nextNode->select]){
                    current_list->nextNode->arrival = current->arrival + current_list->nextNode->delay[current_list->nextNode->select];
                }
            }

            current_list = current_list->next;
        }
        if(strcmp(current->name,"end") == 0){
            current->require = current->arrival;
            break;
        }
        current = current->next;
    }

}
void compute_arrival0(struct node* head){
    struct node* current;
    struct list* current_list;
    double max_delay;
    int flag=0;
    int count=0;
    while(flag==0){
        printf("count:%d\n",count);
        count++;
        flag=1;
        current = head->next;
        while(current != NULL){
            // printf("node:%s\n",current->name);
            max_delay = 0;
            current_list = current->pre;
            while(current_list != NULL){
                // printf("list:%s\n",current_list->nextNode->name);
                if(current_list->nextNode->arrival == -1){
                    flag = 0;
                }
                if(current_list->nextNode->arrival > max_delay){
                    max_delay = current_list->nextNode->arrival;
                }
                current_list = current_list->next;
            }
            // printf("node:%s\n",current->name);
            current->arrival = max_delay + current->delay[current->select];

            if(strcmp(current->name,"end") == 0){
                current->require = current->arrival;
                break;
            }
            current = current->next;
        }
    }
}
void compute_require0(struct node* head){
    struct node* current;
    struct list* current_list;
    current = head;
    while(current->next != NULL){
        current = current->next;
    }

    while(current != NULL){
        current_list = current->pre;
        if(current->require != MAX_SIZE*1000){
            while(current_list != NULL){

                if(current_list->nextNode->require > current->require - current->delay[current->select]){
                    current_list->nextNode->require = current->require - current->delay[current->select];
                }
                current_list = current_list->next;
            }
        }

        if(strcmp(current->name,"head") == 0){
            break;
        }
        current = current->last;
    } 
}
void compute_require(struct node* head){
    struct node* current;
    struct list* current_list;
    double min;
    double min_delay;
    double tmp_delay;
    current = head;
    while(current->next != NULL){
        current = current->next;
    }
    // printf("last node:%s\n",current->name);
    current = current->last;
    while(current != NULL){
        // printf("node:%s\n",current->name);
        min_delay = MAX_SIZE*100;
        // min_delay = 0;
        current_list = current->post;
        while(current_list != NULL){
            // printf("list:%s\n",current_list->nextNode->name);
            if(current_list->nextNode->type == -2 || current_list->nextNode->type == -1){
                tmp_delay = current_list->nextNode->require;
            }
            else{
                tmp_delay = current_list->nextNode->require - current_list->nextNode->delay[current_list->nextNode->select];
                // tmp_delay = current_list->nextNode->require - current->delay[current->select];
            }
            // tmp_delay = current_list->nextNode->require;
            if(tmp_delay < min_delay){
                min_delay = tmp_delay;
                min = current_list->nextNode->require - current_list->nextNode->delay[current_list->nextNode->select];
            }
            current_list = current_list->next;
        }
        current->require = min_delay;
        // if(current->arrival>min_delay){
        //     current->require = current->arrival;
        // }
        // else{
        //     current->require = min_delay;
        // }
        

        if(strcmp(current->name,"home") == 0){
            break;
        }
        current = current->last;
    }
}

double compute_power(struct node* head){
    struct node* current;
    double sum = 0;
    current = head;
    while(current != NULL){
        sum += current->power[current->select];
        current = current->next;
    }
    return sum;
}

double compute_delay(struct node* head){
    struct node* current;
    double total_delay = 0;
    compute_arrival(head);
    current = head;
    while(current->next != NULL){
        current = current->next;
    }
    if(strcmp(current->name,"end") == 0){
        total_delay = current->arrival;
    }
    return total_delay;
}


void show_node(struct node* head){
    struct node* current;
    struct list* current_list;
    current = head;
    while(current != NULL){
        printf("name:%s, id:%d, type:%d\n",current->name,current->id,current->type);
        printf("\t- pre:");
        current_list = current->pre;
        while(current_list != NULL){
            printf("%s ",current_list->nextNode->name);
            current_list = current_list->next;
        }
        printf("\n");
        printf("\t- post:");
        current_list = current->post;
        while(current_list != NULL){
            printf("%s ",current_list->nextNode->name);
            current_list = current_list->next;
        }
        printf("\n");
        printf("\t- delay:");
        for(int i=0;i<4;i++){
            printf("%lf ",current->delay[i]);
        }
        printf("\n");
        printf("\t- power:");
        for(int i=0;i<4;i++){
            printf("%lf ",current->power[i]);
        }
        printf("\n");
        printf("\t- select:");
        printf("%d",current->select);
        printf("\n");
        printf("\t- arrival:");
        printf("%lf",current->arrival);
        printf("\n");
        printf("\t- require:");
        printf("%lf",current->require);
        printf("\n");
        current = current->next;
    }

    printf("power:%lf\n",compute_power(head));
    printf("delay:%lf\n",compute_delay(head));
}

int isValid(struct node* head){
    struct node * current;
    current = head;
    while(current != NULL){
        if(current->require - current->arrival < -0.000001){
            return 0;
        }
        current = current->next;
    }
    return 1;
}
void optimize(struct node * head){
    struct node * current;
    struct node * best;
    double max_slack;
    double min_power;
    double less_power;
    int tmp;
    int count = 1;
    int flag;
    int less_inx;

    current = head;
    max_slack = 0;
    flag = 1;
    while(flag == 1){
        current = head;
        max_slack = 0;
        while(current != NULL){
            if((current->type == 1 || current->type == 2) && current->pre != NULL){
                if(current->require - current->arrival > max_slack){
                    min_power = MAX_SIZE;
                    for(int i=0;i<4;i++){
                        if(current->power[i] < min_power){
                            min_power = current->power[i];
                        }
                    }
                    if(min_power < current->power[current->select]){
                    // if(current->select != 1){
                        best = current;
                        max_slack = current->require - current->arrival;                    
                    }
                }
            }
            current = current->next;
        }

        less_power = best->power[1];
        less_inx = 1;
        for(int i=0;i<4;i++){
            if(best->power[best->select] > best->power[i] && less_power <= best->power[best->select] &&  less_power <= best->power[i]){
                less_power = best->power[i];
                less_inx = i;
            }
            else if(best->power[best->select] > best->power[i] && less_power >= best->power[best->select] &&  less_power >= best->power[i]){
                less_power = best->power[best->select];
                less_inx = i;
            }
            else if(best->power[best->select] < best->power[i] && less_power >= best->power[best->select]){
                less_power = best->power[best->select];
                less_inx = i;
            }
        }

        if(best->delay[less_inx] - best->delay[best->select] < max_slack){
            tmp = best->select;
            best->select = less_inx;
            // best->select = 1;
            compute_arrival(head);
            compute_require(head);
            if(isValid(head) == 0){
                best->select = tmp;
                flag = 0;
            }
        }
        else{
            flag = 0;
        }
        // printf("max_slack:%lf\n",max_slack);
        // printf("max_slack_node:%s\n",best->name);
    }
    // printf("max_slack:%lf\n",max_slack);
    // printf("max_slack_node:%s\n",best->name);
}
void save_result(char * network_name, struct node *head, double org_power){
    FILE * fp;
    struct node * current;
    compute_arrival(head);
    compute_require(head);
    strcat(network_name,".mbench");
    fp = fopen (network_name, "w+");
    fprintf(fp, "# Initial delay:%lf\n", compute_delay(head));
    fprintf(fp, "# Original power:%lf\n", org_power);
    fprintf(fp, "# Optimized power:%lf\n", compute_power(head));
    current = head->next;
    while(current != NULL){
        if(current->pre != NULL){
            if(strcmp(current->pre->nextNode->name,"head") == 0){
                fprintf(fp, "INPUT(%s)\n", current->name);
        }
        }
        if(current->post != NULL){
            if(strcmp(current->post->nextNode->name,"end") == 0){
                fprintf(fp, "OUTPUT(%s)\n", current->name);
            }
        }
        current = current->next;
    }
    current = head->next;
    while(current != NULL){
        if(current->type == -1 && current->pre != NULL){
            if(current->require-current->arrival < 0.000001 && current->require-current->arrival > -0.000001){
                fprintf(fp, "%s = BUF(%s) \t\t# %lf \n", current->name, current->pre->nextNode->name, 0.000000);
            }
            else{
                fprintf(fp, "%s = BUF(%s) \t\t# %lf \n", current->name, current->pre->nextNode->name, current->require-current->arrival);
            }
        }
        if(current->type == 1 && current->pre != NULL){
            if(current->require-current->arrival < 0.000001 && current->require-current->arrival > -0.000001){
                fprintf(fp, "%s = INV%d(%s) \t\t# %lf \n", current->name, current->select+1, current->pre->nextNode->name, 0.000000);

            }
            else{
                fprintf(fp, "%s = INV%d(%s) \t\t# %lf \n", current->name, current->select+1, current->pre->nextNode->name, current->require-current->arrival);

            }
        }
        if(current->type == 2 && current->pre != NULL && current->pre->next != NULL){
            if(current->require-current->arrival < 0.000001 && current->require-current->arrival > -0.000001){
                fprintf(fp, "%s = NAND%d(%s,%s) \t\t# %lf \n", current->name, current->select+1, current->pre->nextNode->name,current->pre->next->nextNode->name, 0.000000);
            }
            else{
                fprintf(fp, "%s = NAND%d(%s,%s) \t\t# %lf \n", current->name, current->select+1, current->pre->nextNode->name,current->pre->next->nextNode->name, current->require-current->arrival);
            }
        }
        current = current->next;
    }
    fclose(fp);
}

void read_lib(){
    char *lib_name = LIB_NAME;
    FILE *fp;  
    char buff[255];
    fp = fopen(lib_name, "r");  
    int type=0;
    int count1=0;
    int counti=-1;
    int countn=-1;

    while(fscanf(fp, "%s", buff)!=EOF){  
        if(buff[0]=='i' || buff[0]=='I'){
            type = 1;
            count1 = 0;
            counti++;
            if(counti>=4){
                continue;
            }
            
            // printf("\n");
        }
        if(buff[0]=='n' || buff[0]=='N'){
            type = 2;
            count1 = 0;
            countn++;
            if(countn>=4){
                continue;
            }
            
            // printf("\n");
        }
        
        if(type == 1){
            switch(count1){
                case 2:
                    delayInv[counti][0] = atof(buff);
                    break;
                case 3:
                    delayInv[counti][1] = atof(buff);
                    break;
                case 5:
                    powerInv[counti] = atof(buff);
                    break;
                default:
                    break;
            }
        }
        else if(type == 2){
            switch(count1){
                case 2:
                    delayNand[countn][0] = atof(buff);
                    break;
                case 3:
                    delayNand[countn][1] = atof(buff);
                    break;
                case 5:
                    powerNand[countn] = atof(buff);
                    break;
                default:
                    break;
            }
        }
        
        count1++;
        // printf("%s-", buff );  
        
    
    }  
    fclose(fp);  
}

int TestC_Hw2Abc(Abc_Frame_t * pAbc){
    Abc_Ntk_t *pNtk;
    int result;
    pNtk = Abc_FrameReadNtk(pAbc);

    if(pNtk == NULL){
        Abc_Print(-1, "Test_FirstFunctionAbc: Getting the target network fails.\n");
        return 0;
    }

    result = TestC_Hw2(pNtk);

    return result;
}

int TestC_Hw2(Abc_Ntk_t * pNtk){
    if(!Abc_NtkIsStrash(pNtk)){
        Abc_Print(-1, "TestC_FirstFunction: This command is only application to strashed networks.\n");
        return 0;
    }



    // delayInv[0][0] = 0.28; delayInv[0][1] = 0.72;
    // delayInv[1][0] = 1.03; delayInv[1][1] = 2.64;
    // delayInv[2][0] = 0.47; delayInv[2][1] = 1.20;
    // delayInv[3][0] = 0.82; delayInv[3][1] = 2.10;
    // powerInv[0] = 20.92; 
    // powerInv[1] = 1; 
    // powerInv[2] = 2.75; 
    // powerInv[3] = 19.25; 

    // delayNand[0][0] = 0.56; delayNand[0][1] = 1.44;
    // delayNand[1][0] = 2.31; delayNand[1][1] = 5.95;
    // delayNand[2][0] = 1.16; delayNand[2][1] = 3.00;
    // delayNand[3][0] = 1.79; delayNand[3][1] = 4.61;
    // powerNand[0] = 25.76; 
    // powerNand[1] = 1.4; 
    // powerNand[2] = 10.82; 
    // powerNand[3] = 25.38; 

    Abc_Obj_t * current_obj;
    Abc_Obj_t * pre_obj;
    struct node *head;
    double org_power;
    printf("network name:%s\n",Abc_NtkName(pNtk));
    printf("read_lib\n");
    read_lib();
    printf("init\n");
    head = init_graph(pNtk);
    printf("compute_delayAndPower\n");
    compute_delayAndPower(head);
    printf("compute_arrival\n");
    compute_arrival(head);
    printf("compute_require\n");
    compute_require(head);
    org_power = compute_power(head);
    printf("power:%lf\n",org_power);
    printf("delay:%lf\n",compute_delay(head));
    // printf("show_node\n");
    // show_node(head);
    printf("isValid:%d\n",isValid(head));
    printf("optimize\n");
    optimize(head);
    printf("power:%lf\n",compute_power(head));
    printf("delay:%lf\n",compute_delay(head));
    printf("isValid:%d\n",isValid(head));
    save_result(Abc_NtkName(pNtk),head,org_power);
    printf("done\n");
    printf("--------------------\n\n");
    // Abc_Print(1, "<< ------END------ >>\n");
    
    return 1;

}

// part 1
int TestC_Part1Abc(Abc_Frame_t * pAbc){
    Abc_Ntk_t *pNtk;
    int result;
    pNtk = Abc_FrameReadNtk(pAbc);

    if(pNtk == NULL){
        Abc_Print(-1, "Test_FirstFunctionAbc: Getting the target network fails.\n");
        return 0;
    }

    result = TestC_Part1(pNtk);

    return result;
}

int TestC_Part1(Abc_Ntk_t * pNtk){
    if(!Abc_NtkIsStrash(pNtk)){
        Abc_Print(-1, "TestC_FirstFunction: This command is only application to strashed networks.\n");
        return 0;
    }
    Abc_Obj_t * current_obj;
    Abc_Obj_t * pre_obj;
    // Abc_Obj_t * post_obj;
    Abc_Print(1, "<< Print Each Obj - >>\n");
    Abc_Print(1, "ID\tName\tType\tLevel\n");
    Abc_Print(1, "---------------------\n");

    // Abc_Print(1, "The network %s has:\n", Abc_NtkName(pNtk));
    // Abc_Print(1, "\t- %d Spec;\n", Abc_NtkSpec(pNtk));
    // Abc_Print(1, "\t- %d Abc_NtkObjNum;\n", Abc_NtkObjNum(pNtk));
    for(int i=0;i<Abc_NtkObjNum(pNtk);i++){
        current_obj = Abc_NtkObj(pNtk,i);
        // Abc_Print(1, "\t------------\n");
        Abc_Print(1, "\nId:\t%d,\t\t", Abc_ObjId(current_obj));
        Abc_Print(1, "Name\t%s,\t\t", Abc_ObjName(current_obj));
        Abc_Print(1, "Type\t%d,\t\t", Abc_ObjType(current_obj));
        Abc_Print(1, "Level\t%d,", Abc_ObjLevel(current_obj));



        // Abc_Print(1, "\tFanin:\n");
        for(int j=0;j<Abc_ObjFaninNum(current_obj);j++){
            pre_obj = Abc_ObjFanin(current_obj,j);
            // Abc_Print(1, "\t- %d Abc_ObjId;\n", Abc_ObjId(pre_obj));
            Abc_Print(1, "\tFiName\t%s, ", Abc_ObjName(pre_obj));
            // current_obj->pNtk->vPhases;
            // Abc_Print(1, "\tFiPhase\t%d, ", Abc_ObjFaninPhase(pre_obj,j));
            if(j==0)
                Abc_Print(1, "\tFiPhase\t%x, ", current_obj->fCompl0);
            if(j==1)
                Abc_Print(1, "\tFiPhase\t%x, ", current_obj->fCompl1);
        }

    }
    
    Abc_Print(1, "\n<< ------END------ >>\n");

    return 1;

}

// part 2

void dfs_root(Abc_Obj_t * pObj, int* isRoot);
void dfs_tree(Abc_Ntk_t * pNtk, int* isTree, int id);

int TestC_Part2Abc(Abc_Frame_t * pAbc, int argc, char **argv){
    Abc_Ntk_t *pNtk;
    int result;
    pNtk = Abc_FrameReadNtk(pAbc);

    if(pNtk == NULL){
        Abc_Print(-1, "Test_FirstFunctionAbc: Getting the target network fails.\n");
        return 0;
    }

    result = TestC_Part2(pNtk,argc,argv);

    return result;
}

int TestC_Part2(Abc_Ntk_t * pNtk, int argc, char **argv){
    if(!Abc_NtkIsStrash(pNtk)){
        Abc_Print(-1, "TestC_FirstFunction: This command is only application to strashed networks.\n");
        return 0;
    }

    Abc_Print(1, "\n<< ------ANDTREE------ >>\n");
    int num;
    if(argc>=3 && strcmp(argv[1],"-S")==0){
        num = atoi(argv[2]);
    }
    else{
        num = 5;
    }

    int isRoot[Abc_NtkObjNum(pNtk)];

    for(int i=0;i<Abc_NtkObjNum(pNtk);i++){
        isRoot[i] = 0;
    }
    Abc_Obj_t * current_obj;
    Abc_Obj_t * pre_obj;

    for(int i=0;i<Abc_NtkPoNum(pNtk);i++){
        current_obj = Abc_NtkPo(pNtk,i);
        dfs_root(current_obj, isRoot);
        isRoot[Abc_ObjId(current_obj)] = 0;
        for(int i=0;i<Abc_ObjFaninNum(current_obj);i++){
            pre_obj = Abc_ObjFanin(current_obj,i);
            isRoot[Abc_ObjId(pre_obj)] = 1;
        }
    }
    for(int i=0;i<Abc_NtkPiNum(pNtk);i++){
        current_obj = Abc_NtkPi(pNtk,i);
        isRoot[Abc_ObjId(current_obj)] = 0;
    }
    // for(int i=0;i<Abc_NtkObjNum(pNtk);i++){
    //     Abc_Print(1, "Id_%d: %d\n",i,isRoot[i]);
    // }
    
    int isTree[Abc_NtkObjNum(pNtk)];
    int isLeave[Abc_NtkObjNum(pNtk)];
    int count0,count1;
    for(int i=0;i<Abc_NtkObjNum(pNtk);i++){
        if(isRoot[i] == 1){
            for(int i=0;i<Abc_NtkObjNum(pNtk);i++){
                isTree[i] = 0;
            }
            dfs_tree(pNtk,isTree,i);
            // Abc_Print(1,"\n----------------\n");
            // Abc_Print(1,"Id:%d\n",i);
            // for(int i=0;i<Abc_NtkObjNum(pNtk);i++){
            //     Abc_Print(1, "%d\t",isTree[i]);
            // }
            // Abc_Print(1, "\n");
            count0 = 0;
            count1 = 0;
            for(int i=0;i<Abc_NtkObjNum(pNtk);i++){
                isLeave[i] = 0;
            }
            for(int i=0;i<Abc_NtkObjNum(pNtk);i++){
                if(isTree[i] == 1){
                    count0+=1;
                    isLeave[i] = 1;
                    current_obj = Abc_NtkObj(pNtk,i);
                    for(int j=0;j<Abc_ObjFaninNum(current_obj);j++){
                        if(j==0){
                            pre_obj = Abc_ObjFanin0(current_obj);
                            isLeave[Abc_ObjId(pre_obj)] = 1;
                        }
                        else if(j==1){
                            pre_obj = Abc_ObjFanin1(current_obj);
                            isLeave[Abc_ObjId(pre_obj)] = 1;
                        }
                        
                    }
                }
            }
            for(int i=0;i<Abc_NtkObjNum(pNtk);i++){
                if(isLeave[i] == 1){
                    count1+=1;
                }
            }

            if(count1-count0 >= num && count1-count0>1){
                Abc_Print(1,"\n%d",count1-count0);
                // Abc_Print(1,"\tc0:%d, c1:%d",count0,count1);
                for(int i=0;i<Abc_NtkObjNum(pNtk);i++){
                    if(isTree[i] == 1){
                        Abc_Print(1,"\t%s",Abc_ObjName(Abc_NtkObj(pNtk,i)));
                    }
                }
            }
            

        }
    }
    Abc_Print(1, "\n<< ------END------ >>\n");
    return 1;

}

void dfs_tree(Abc_Ntk_t * pNtk, int* isTree, int id){
    int flag0;
    int cnt;
    Abc_Obj_t * current_obj;
    Abc_Obj_t * pre_obj;
    current_obj = Abc_NtkObj(pNtk,id);
    // Abc_Print(1, "\nId:%d",Abc_ObjId(current_obj));
    flag0 = 1;
    for(int i=0;i<Abc_ObjFaninNum(current_obj);i++){
        pre_obj = Abc_ObjFanin(current_obj,i);
        // Abc_Print(1, "\tfanin:%d",Abc_ObjId(pre_obj));
        cnt=0;
        for(int i=0;i<Abc_NtkObjNum(pNtk);i++){
            cnt+=isTree[i];
        }
        if(Abc_ObjFanoutNum(current_obj)>1 && cnt>0){
            flag0 = 0;
        }
        if(i==0){
            if(current_obj->fCompl0 == 1)
                flag0 = 0;
        }
        else if(i==1){
            if(current_obj->fCompl1 == 1)
                flag0 = 0;
        }
    }
    if(flag0 == 1 && Abc_ObjFaninNum(current_obj)>0){
        isTree[id] = 1;
        // Abc_Print(1, "\tadd");
        for(int i=0;i<Abc_ObjFaninNum(current_obj);i++){
            pre_obj = Abc_ObjFanin(current_obj,i);
            if((i==0 && current_obj->fCompl0 == 0) || (i==1 && current_obj->fCompl1 == 0)){
                dfs_tree(pNtk,isTree,Abc_ObjId(pre_obj));
            }

        }
        
    }
    
    
}

void dfs_root(Abc_Obj_t * pObj, int* isRoot){
    Abc_Obj_t * pre_obj;
    Abc_Obj_t * pre_obj0;
    Abc_Obj_t * pre_obj1;
    for(int i=0;i<Abc_ObjFaninNum(pObj);i++){
        pre_obj = Abc_ObjFanin(pObj,i);
        if(Abc_ObjFanoutNum(pObj)!=1){
            isRoot[Abc_ObjId(pObj)] = 1;
        }
        if(i==0){
            isRoot[Abc_ObjId(pre_obj)] = pObj->fCompl0;
            pre_obj0 = Abc_ObjFanin(pObj,i);
        }
        if(i==1){
            isRoot[Abc_ObjId(pre_obj)] = pObj->fCompl1;
            pre_obj1 = Abc_ObjFanin(pObj,i);
            if( pObj->fCompl0 == 1 && pObj->fCompl1 == 0){
                isRoot[Abc_ObjId(pre_obj1)] = 1;
            }
            if( pObj->fCompl0 == 0 && pObj->fCompl1 == 1){
                isRoot[Abc_ObjId(pre_obj0)] = 1;
            }
        }
        dfs_root(pre_obj,isRoot);
    }
}


ABC_NAMESPACE_IMPL_END