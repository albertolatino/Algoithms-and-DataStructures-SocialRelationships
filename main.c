#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct relation* list;

struct entita
{
  char name[50];
  struct entita* left;
  struct entita* right;
  struct entita* parent;
  list relations;
  int color;
};


typedef struct entita* ent;
ent nil;
//FUNZIONI PER ENTITA
ent CREATE_ENTITY(char name[]);
void RB_TREE_INSERT(ent* tree,ent e);
void RIGHT_ROTATE(ent* tree,ent x);
void LEFT_ROTATE(ent* tree,ent x);
void RB_INSERT_FIXUP(ent* tree,ent z);
void INORDER_TREE_WALK(ent tree);
ent RB_TREE_SEARCH(ent tree,char name[]);
void TRANSPLANT(ent* tree,ent u,ent v);
void RB_DELETE(ent* tree,ent z);
ent TREE_MINIMUM(ent tree);
void RB_DELETE_FIXUP(ent* tree,ent x);
ent RB_TREE_DELETE(ent* tree,ent z);
ent TREE_SUCCESSOR(ent z);
struct rel_entity
{
  struct entita* entity_pointer;
  struct rel_entity* parent;
  struct rel_entity* left;
  struct rel_entity* right;
  int color;
};

typedef struct rel_entity* relent;
relent relnil;

//FUNZIONI PER RELATION ENTITY
relent CREATE_REL_ENTITY(ent e);
void RB_REL_TREE_INSERT(relent* tree,relent e);
void RIGHT_REL_ROTATE(relent* tree,relent x);
void LEFT_REL_ROTATE(relent* tree,relent x);
void RB_REL_INSERT_FIXUP(relent* tree,relent z);
void REL_INORDER_TREE_WALK(relent tree);
relent RB_REL_TREE_SEARCH(relent tree,char name[]);
void REL_TRANSPLANT(relent* tree,relent u,relent v);
relent RB_REL_DELETE(relent* tree,relent z);
relent REL_TREE_MINIMUM(relent tree);
void RB_REL_DELETE_FIXUP(relent* tree,relent x);
relent REL_TREE_DELETE(relent* rel_tree,relent r);
relent REL_TREE_SUCCESSOR(relent rel_tree);

struct relation
{
  char relation_name[40];
  struct rel_entity* send;
  struct rel_entity* receive;
  struct relation* next;
  struct nodo* relation_pointer;
  int received;
};

struct nodo
{
  char rel_name[40];
  int max_num;
  int entities_num;
  struct rel_entity* entities;
  struct nodo* parent;
  struct nodo* left;
  struct nodo* right;
  int color;
};

typedef struct nodo* report_el;

//FUNZIONI PRE LISTA RELATIONS
list RELATION_EXIST(ent e,char relation_name[]);
list INSERISCI_IN_TESTA(list* l,char relation_name[],report_el rel_pointer);
list INSERISCI_IN_CODA(list* l,char relation_name[],report_el rel_pointer);
void REPORT_PRINT(relent tree);
void RIMUOVI(list* l,char relation_name[]);




report_el repnil;

//FUNZIONI PER REPORT
report_el CREATE_REP_RELATION(char relation_name[]);
void RB_REP_TREE_INSERT(report_el* tree,report_el e);
void RIGHT_REP_ROTATE(report_el* tree,report_el x);
void LEFT_REP_ROTATE(report_el* tree,report_el x);
void RB_REP_INSERT_FIXUP(report_el* tree,report_el z);
report_el RB_REP_TREE_SEARCH(report_el tree,char relation_name[]);
void REPORT_INORDER_TREE_WALK(report_el tree);
void REPORT_ADJUST_TREE_WALK(ent tree,report_el relation);
report_el REP_TREE_SUCCESSOR(report_el rep_tree);
report_el REP_TREE_MINIMUM(report_el tree);
void RB_REP_DELETE_FIXUP(report_el* tree,report_el x);
void REPORT_DELENT_TREE_WALK(ent tree,report_el relation);
void REP_TRANSPLANT(report_el* tree,report_el u,report_el v);
report_el RB_REP_DELETE(report_el* tree,report_el z);




int main()
{
  repnil = malloc(sizeof(struct nodo));
  repnil->parent = repnil;
  repnil->left = repnil;
  repnil->right = repnil;
  repnil->color = 1;

  nil = malloc(sizeof(struct entita));//CREO NODO NIL
  nil->parent = nil;
  nil->left = nil;
  nil->right = nil;
  //strcpy(nil->name,"nil");
  nil->color=1;

  relnil = malloc(sizeof(struct rel_entity));
  relnil->parent = relnil;
  relnil->left = relnil;
  relnil->right = relnil;
  relnil->color = 1;


  //DICHIARAZIONI VARIABILI
  char str[100];
  char* s = NULL;
  char* command=NULL;
  char*origin=NULL;
  char* destination=NULL;
  char* relation=NULL;
  ent entity,entity_tree,origin1,destination1,to_delete,origin2,destination2;
  relent rel_entity,rel_exist,rel_tree,temprel1,rel_to_delete,rel_exist1,rel_remove;
  report_el report_tree,rel_pointer;
  entity_tree = nil;
  rel_tree = relnil;
  report_tree = repnil;


  do
  {
    fgets(str,100,stdin);

    str[strlen(str)-1]=0;

    command = strtok(str," ");


    if(strcmp(command,"addent")==0)
    {

          origin = strtok(NULL," ");

        if(RB_TREE_SEARCH(entity_tree,origin)==nil)//INVECE DI FARE SEARCH E POI INSERT PUOI FARE UNA INSERT MODIFICATA CHE DOPO CHE HA CERCATO IN CASO INSERISCE
        {
            entity = CREATE_ENTITY(origin);
            RB_TREE_INSERT(&entity_tree,entity);

        }

    }

    else if(strcmp(command,"delent")==0)
    {

      int last;
      int freed = 0;
      ent r;
      list temp,tempdest,temp1;
      report_el rel,lastrep;

      origin = strtok(NULL," ");

      r = RB_TREE_SEARCH(entity_tree,origin);

        if(r != nil)
        {
            temp = r->relations;

              while(temp != NULL)
              {
                  while(temp->send != relnil)//finche di una relazione, l'entità è l'origine per qualcuno
                  {
                      tempdest = temp->send->entity_pointer->relations;//

                        while(tempdest != NULL && strcmp(tempdest->relation_name,temp->relation_name)!=0)
                          tempdest = tempdest->next;//tempdest raggiunge la relazione

                          free(RB_REL_DELETE(&(tempdest->receive),RB_REL_TREE_SEARCH(tempdest->receive,r->name)));

                          last = tempdest->received;

                          lastrep = tempdest->relation_pointer;

                          tempdest->received--;



                            if(last==lastrep->max_num)//se per quella relazione,il dest era in report
                            {
                                if(lastrep->entities_num > 1)//se però non è l'unico ad apparire in report
                                {
                                  free(RB_REL_DELETE(&(lastrep->entities),RB_REL_TREE_SEARCH(lastrep->entities,temp->send->entity_pointer->name)));//lo elimino
                                  lastrep->entities_num--;
                                }

                                  else if(lastrep->entities_num == 1)//se invece era l'unico con quel max_num per quella relation
                                  {

                                  //    lastrep->max_num=last;//se è l'unico solo lui influenza il max_num
                                      lastrep->max_num--;

                                      if(lastrep->max_num > 0)
                                      {
                                          free(RB_REL_DELETE(&(lastrep->entities),lastrep->entities));//lo elimino
                                          lastrep->entities_num--;//va a 0
                                          //devo cercare tutti quelli con max_num-1
                                          //OCCHIO
                                          REPORT_ADJUST_TREE_WALK(entity_tree,lastrep);//E SE MI AGGIUNGE L'ENTITA CHE STO RIMUOVENDO??

                                            if(lastrep->entities == relnil && lastrep->entities_num == 0)
                                            {
                                            free(RB_REP_DELETE(&(report_tree),lastrep));

                                            freed = 1;
                                            }


                                      }
                                        else if(lastrep->max_num == 0)//se lui comandava e il suo received è andato a 0
                                        {
                                          free(RB_REL_DELETE(&(lastrep->entities),lastrep->entities));//lo elimino
                                          lastrep->entities_num--;//va a 0
                                          free(RB_REP_DELETE(&(report_tree),lastrep));

                                          freed = 1;
                                        }

                                  }
                            }


                            free(RB_REL_DELETE(&(temp->send),temp->send));


                  }//while temp send != relnil,ORA ALBERO SEND è VUOTO E HO SVUOTATO PARZIALMENTE I RECEIVE DEI DESTINATARI



      if(freed == 0)//se non è stata liberata la relazione da report
      {
                    last = temp->received;
                    lastrep = temp->relation_pointer;//OCCHIO hai fatto la free di rel point

                    while(temp->receive != relnil)//svuoto la struttura receive
                      {
                        temp1 = temp->receive->entity_pointer->relations;

                          while(temp1 != NULL && strcmp(temp1->relation_name,temp->relation_name)!=0)
                            temp1 = temp1->next;

                            free(RB_REL_DELETE(&(temp1->send),RB_REL_TREE_SEARCH(temp1->send,r->name)));//rimuove il ricevente dal ramo send di origin


                            free(RB_REL_DELETE(&(temp->receive),temp->receive));//rimuove il mittente dal ramo receive di dest
                            temp->received--;
                      }




                  if(last==lastrep->max_num)//se l'entita che sto rimuovendo, per quella relazione, fa parte di report
                  {
                      if(lastrep->entities_num > 1)//se non è l'unica
                      {
                        free(RB_REL_DELETE(&(lastrep->entities),RB_REL_TREE_SEARCH(lastrep->entities,r->name)));
                        lastrep->entities_num--;
                      }

                        else if(lastrep->entities_num==1)//resetto
                        {
                          free(RB_REL_DELETE(&(lastrep->entities),lastrep->entities));//la rimuovo
                          lastrep->entities_num--;//va a 0


                            if(lastrep->max_num > 1)//se era 1 non avrebbe senso perche non esisterebbero altre entita con received rtale da metterlo in report
                            {
                                lastrep->max_num = 0;//azzero max_num,entities_num,è gia 0

                                REPORT_DELENT_TREE_WALK(entity_tree,lastrep);//OCCHIO A non prendere te stesso

                                  if(lastrep->entities == relnil && lastrep->entities_num == 0)//Vuol dire che senza quell'entità, non ci sono altre entita che ricevono quella relazione
                                  {
                                    free(RB_REP_DELETE(&(report_tree),lastrep));

                                  }


                            }

                              else if(lastrep->max_num == 1)//se era l'unica e con received = 1,la struttura va rimossa da report
                              {
                                free(RB_REP_DELETE(&(report_tree),lastrep));

                              }

                        }

                  }
      }
                if(temp->send ==relnil && temp->receive == relnil && temp->received == 0)//se dopo aver anche receive, non ce piu niente
                  RIMUOVI(&(r->relations),temp->relation_name);

                  freed = 0;

                temp = temp->next;
              }
              free(RB_TREE_DELETE(&(entity_tree),r));

          }



    }
    else if(strcmp(command,"addrel")==0)
    {


        rel_exist1 = relnil;
        rel_exist = relnil;
        list r,r1,p;

        origin = strtok(NULL," ");
        destination = strtok(NULL," ");
        relation = strtok(NULL," ");

        origin1 = RB_TREE_SEARCH(entity_tree,origin);

        if(origin1 != nil)
        destination1 = RB_TREE_SEARCH(entity_tree,destination);//cerca solo se origin esiste

          if(origin1 != nil && destination1 != nil)
          {

          //  rel_pointer = RB_REP_TREE_SEARCH(report_tree,relation);//cerco la relazione nell'albero dei report

              r = RELATION_EXIST(origin1,relation);

                if(r == NULL)
                {

                  rel_pointer = RB_REP_TREE_SEARCH(report_tree,relation);//cerco la relazione nell'albero dei report

                    if(rel_pointer==repnil)//se non esiste quella relazione nell'albero report, allora devi crearla
                    {
                      rel_pointer = CREATE_REP_RELATION(relation);//la creo
                      RB_REP_TREE_INSERT(&report_tree,rel_pointer);//la inserisco nell'albero dei report
                    }

                  p = INSERISCI_IN_CODA(&(origin1->relations),relation,rel_pointer);//creo la relation col puntatore alla relazione in report

                  rel_entity = CREATE_REL_ENTITY(destination1);

                  RB_REL_TREE_INSERT(&(p->send),rel_entity);
                }

                    else
                    {

                      if(r->receive == relnil && r->send == relnil && r->received == 0)
                      {
                        rel_pointer = RB_REP_TREE_SEARCH(report_tree,relation);//cerco la relazione nell'albero dei report

                          if(rel_pointer == repnil)
                          {
                            rel_pointer = CREATE_REP_RELATION(relation);//la creo
                            RB_REP_TREE_INSERT(&report_tree,rel_pointer);//la inserisco nell'albero dei report
                          }

                        r->relation_pointer = rel_pointer;
                      }


                      rel_exist = RB_REL_TREE_SEARCH(r->send,destination1->name);

                        if(rel_exist == relnil)
                        {
                          rel_entity = CREATE_REL_ENTITY(destination1);

                          RB_REL_TREE_INSERT(&(r->send),rel_entity);
                        }


                    }


                    r1 = RELATION_EXIST(destination1,relation);

                    if(r1 == NULL)
                    {
                      if(r==NULL)//quindi ho gia il puntatore alla rel dell'albero report
                        p = INSERISCI_IN_CODA(&(destination1->relations),relation,rel_pointer);

                      if(r != NULL)
                      p = INSERISCI_IN_CODA(&(destination1->relations),relation,r->relation_pointer);//rel_pointer era r1->relation poiner

                      rel_entity = CREATE_REL_ENTITY(origin1);

                      p->received++;

                      RB_REL_TREE_INSERT(&(p->receive),rel_entity);
                    }

                        else
                        {

                          if(r1->receive == relnil && r1->send == relnil && r1->received == 0)
                            {
                              if(r != NULL)
                              r1->relation_pointer = r->relation_pointer;

                                if(r == NULL)
                                  r1->relation_pointer = p->relation_pointer;
                            }

                          rel_exist1 = RB_REL_TREE_SEARCH(r1->receive,origin1->name);

                            if(rel_exist1 == relnil)
                            {
                              rel_entity = CREATE_REL_ENTITY(origin1);

                              r1->received++;

                              RB_REL_TREE_INSERT(&(r1->receive),rel_entity);
                            }

                        }


                        if(r1!=NULL && rel_exist==relnil && rel_exist1==relnil)//se la relazione gia esisteva nel ricevente
                        {
                            if(r1->received>r1->relation_pointer->max_num)//se questo ricevente ha superato il/i ricevente/i in report_tree
                            {
                              while(r1->relation_pointer->entities != relnil)//svuota entities di quella relazione
                                free(RB_REL_DELETE(&(r1->relation_pointer->entities),r1->relation_pointer->entities));

                                  r1->relation_pointer->entities_num = 0;

                                  RB_REL_TREE_INSERT(&(r1->relation_pointer->entities),CREATE_REL_ENTITY(destination1));//e inserisce la nuova entita

                                  r1->relation_pointer->entities_num++;

                                  r1->relation_pointer->max_num = r1->received;

                            }

                              else if(r1->received==r1->relation_pointer->max_num)//se è uguale
                              {
                                RB_REL_TREE_INSERT(&(r1->relation_pointer->entities),CREATE_REL_ENTITY(destination1));

                                r1->relation_pointer->entities_num++;

                              }

                        }

                          if(r1==NULL)//se la rel non esisteva nel ricevente ed è appena stata creata in esso
                          {
                            if(p->received>p->relation_pointer->max_num)
                            {
                              while(p->relation_pointer->entities != relnil)//in realta se è stata appena inserita received è 1;
                                free(RB_REL_DELETE(&(p->relation_pointer->entities),p->relation_pointer->entities));

                                  p->relation_pointer->entities_num = 0;

                                  RB_REL_TREE_INSERT(&(p->relation_pointer->entities),CREATE_REL_ENTITY(destination1));//e inserisce la nuova entita

                                  p->relation_pointer->entities_num++;

                                  p->relation_pointer->max_num = p->received;//cioè 1 dato che è appena stata creata
                            }

                              else if(p->received==p->relation_pointer->max_num)
                              {
                                RB_REL_TREE_INSERT(&(p->relation_pointer->entities),CREATE_REL_ENTITY(destination1));

                                p->relation_pointer->entities_num++;
                              }


                          }


          }


    }
    else if(strcmp(command,"delrel")==0)
    {
      int rifl = 0;
      list r1 = NULL;
      list r = NULL;

      origin = strtok(NULL," ");
      destination = strtok(NULL," ");
      relation = strtok(NULL," ");

      origin2 = RB_TREE_SEARCH(entity_tree,origin);//cerco origin

        if(origin2 != nil)
          destination2 = RB_TREE_SEARCH(entity_tree,destination);//se origin non esiste, è inutile cercare destination, tanto non devo fare niente

            if(origin2 != nil && destination2 != nil)//se esistono entrambe le entita
            {
                r1 = RELATION_EXIST(origin2,relation);

                  //if(r1 != NULL)//se la relazione non esiste in origin, è inutile cercarla in destination
                    r = RELATION_EXIST(destination2,relation);
            }

                if(origin2 != nil && destination2 != nil && r != NULL && r1 != NULL)
                {

                  rel_remove = RB_REL_TREE_SEARCH(r1->send,destination2->name);

                    if(rel_remove != relnil)//se la relazione esiste
                    {

                      free(RB_REL_DELETE(&(r1->send),rel_remove));



                          rel_remove = RB_REL_TREE_SEARCH(r->receive,origin2->name);//lo cerco solo perche la delete ha bisogno del puntatore senno potrei risparmiarmela

                          free(RB_REL_DELETE(&(r->receive),rel_remove));

                                //DOPO CHE HO RIMOSSO LA RELAZIONE,AGGIORNO I REPORT
                                  if(r->relation_pointer->max_num==r->received)//se destination sta nella struttura report di quella relazione
                                  {

                                      if(r->relation_pointer->entities_num > 1)//se destination non è l'unica della struttura report
                                      {
                                        rel_remove = RB_REL_TREE_SEARCH(r->relation_pointer->entities,destination2->name);
                                        free(RB_REL_DELETE(&(r->relation_pointer->entities),rel_remove));

                                        r->relation_pointer->entities_num--;
                                        r->received--;
                                      }

                                        else if(r->relation_pointer->entities_num==1)
                                        {
                                          r->received--;//diventa max_num-1,devo fare nuova ricerca per quella relazione con received==max_num-1;
                                          r->relation_pointer->max_num=r->received;

                                            if(r->relation_pointer->max_num > 0)//fai la nuova ricerca solo se il nuovo max_num-1 è > 0, perche se era l'unico con received = 1, gli altri di sicuro saranno minori e quindi sono received ==0
                                            {//devo vedere se ci sono altri riceventi di quella relazione con received = max_num-1,oltre al mio che è appena stato decrementato

                                              free(RB_REL_DELETE(&(r->relation_pointer->entities),r->relation_pointer->entities));

                                              r->relation_pointer->entities_num--;//va a 0
                                              REPORT_ADJUST_TREE_WALK(entity_tree,r->relation_pointer);

                                            }

                                              else if(r->relation_pointer->max_num==0)
                                              {
                                                rel_remove = RB_REL_TREE_SEARCH(r->relation_pointer->entities,destination2->name);
                                                free(RB_REL_DELETE(&(r->relation_pointer->entities),rel_remove));



                                                r->relation_pointer->entities_num--;//va a 0
                                                free(RB_REP_DELETE(&(report_tree),r->relation_pointer));

                                              }


                                        }
                                  }

                                    else //se invece non compariva in report, normale
                                    r->received--;

                                  if(r1==r)
                                    rifl = 1;

                                  if(r != NULL && r->receive == relnil && r->send == relnil && r->received == 0)
                                  RIMUOVI(&(destination2->relations),relation);

                                  if(r1 != NULL && r1->receive == relnil && r1->send == relnil && r1->received == 0 && rifl != 1)
                                  RIMUOVI(&(origin2->relations),relation);



                }
              }


    }
    else if(strcmp(command,"report")==0)
    {

      if(report_tree != repnil)
      {
        REPORT_INORDER_TREE_WALK(report_tree);
        printf("\n");
      }

        else
          printf("none\n");

    }


  }while(strcmp(command,"end")!=0);






  return 0;
}

ent CREATE_ENTITY(char name[])
{
  ent e;

  e = malloc(sizeof(struct entita));
  strcpy(e->name,name);
  e->parent = nil;
  e->left = nil;
  e->right = nil;
  e->relations = NULL;

  return e;
}

void RB_TREE_INSERT(ent* tree,ent e)
{
  ent x,y;

  y = nil;
  x = *tree;

  while(x != nil)
  {
    y=x;

      if(strcmp(e->name,x->name)<0)
        x = x->left;

        else
        x = x->right;
  }

  e->parent=y;

    if(y==nil)//se l'albero è vuoto, la radice dell'albero diventa il nodo inserito
        *tree = e;

        else if(strcmp(e->name,y->name)<0)
          y->left = e;

            else
            y->right = e;

      e->left = nil;
      e->right = nil;
      e->color = 0;

      RB_INSERT_FIXUP(tree,e);


}

void LEFT_ROTATE(ent* tree,ent x)
{
  ent y;

  y = x->right;
  x->right = y->left;

  if(y->left != nil)
    y->left->parent = x;

  y->parent = x->parent;

  if(x->parent==nil)
      *tree = y;


    else if(x == x->parent->left)
        x->parent->left = y;

      else
        x->parent->right = y;

  y->left = x;
  x->parent = y;


}

void RIGHT_ROTATE(ent* tree,ent x)
{
  ent y;

  y = x->left;
  x->left = y->right;

  if(y->right != nil)
    y->right->parent = x;

  y->parent = x->parent;

  if(x->parent==nil)
      *tree = y;

    else if(x == x->parent->right)
        x->parent->right = y;

      else
        x->parent->left = y;

  y->right = x;
  x->parent = y;
}

void RB_INSERT_FIXUP(ent* tree,ent z)
{

    while(z->parent->color==0)
    {
      ent y;

      if(z->parent==z->parent->parent->left)
      {
          y = z->parent->parent->right;

          if(y->color==0)
            {
              z->parent->color = 1;
              y->color = 1;
              z->parent->parent->color = 0;
              z = z->parent->parent;//QUI QUANDO RISALI, E DIVENTI LA RADICE, SE IL PADRE DELLA RADICE è NIL è UN CASINO
            }

              else
              {
                if(z == z->parent->right)
                {
                  z = z->parent;
                  LEFT_ROTATE(tree,z);

                }

              z->parent->color = 1;
              z->parent->parent->color = 0;
              RIGHT_ROTATE(tree,z->parent->parent);

            }
       }
          else
          {
            y = z->parent->parent->left;

              if(y->color==0)
              {
                z->parent->color=1;
                y->color=1;
                z->parent->parent->color=0;
                z = z->parent->parent;
              }

                else
                {
                  if(z == z->parent->left)
                  {
                    z = z->parent;
                    RIGHT_ROTATE(tree,z);
                  }

                  z->parent->color=1;
                  z->parent->parent->color=0;
                  LEFT_ROTATE(tree,z->parent->parent);
               }
            }


      }

      (*tree)->color=1;
}

void INORDER_TREE_WALK(ent tree)
{
  if(tree != nil)
  {
  INORDER_TREE_WALK(tree->left);
  printf("(%s,%d)->",tree->name,tree->color);
  INORDER_TREE_WALK(tree->right);
  }
}

relent CREATE_REL_ENTITY(ent e)
{
  relent p = malloc(sizeof(struct rel_entity));
  p->entity_pointer = e;
  p->parent = relnil;
  p->left = relnil;
  p->right = relnil;

  return p;
}

void RB_REL_TREE_INSERT(relent* tree,relent e)
{
  relent x,y;

  y = relnil;
  x = *tree;

  while(x != relnil)
  {
    y=x;

      if(strcmp(e->entity_pointer->name,x->entity_pointer->name)<0)
        x = x->left;

        else
        x = x->right;
  }

  e->parent=y;

    if(y==relnil)//se l'albero è vuoto, la radice dell'albero diventa il nodo inserito
        *tree = e;

        else if(strcmp(e->entity_pointer->name,y->entity_pointer->name)<0)
          y->left = e;

            else
            y->right = e;

      e->left = relnil;
      e->right = relnil;
      e->color=0;

     RB_REL_INSERT_FIXUP(tree,e);

}

void RIGHT_REL_ROTATE(relent* tree,relent x)
{
  relent y;

  y = x->left;
  x->left = y->right;

  if(y->right != relnil)
    y->right->parent = x;

  y->parent = x->parent;

  if(x->parent==relnil)
      *tree = y;

    else if(x == x->parent->right)
        x->parent->right = y;

      else
        x->parent->left = y;

  y->right = x;
  x->parent = y;

}

void LEFT_REL_ROTATE(relent* tree,relent x)
{
  relent y;

  y = x->right;
  x->right = y->left;

  if(y->left != relnil)
    y->left->parent = x;

  y->parent = x->parent;

  if(x->parent==relnil)
      *tree = y;


    else if(x == x->parent->left)
        x->parent->left = y;

      else
        x->parent->right = y;

  y->left = x;
  x->parent = y;
}

void RB_REL_INSERT_FIXUP(relent* tree,relent z)
{

      while(z->parent->color==0)
      {
        relent y;

        if(z->parent==z->parent->parent->left)
        {
            y = z->parent->parent->right;

            if(y->color==0)
              {
                z->parent->color=1;
                y->color=1;
                z->parent->parent->color=0;
                z = z->parent->parent;
              }

                else
                {
                  if(z == z->parent->right)
                  {
                    z = z->parent;
                    LEFT_REL_ROTATE(tree,z);

                  }

                z->parent->color=1;
                z->parent->parent->color=0;
                RIGHT_REL_ROTATE(tree,z->parent->parent);

              }
         }
            else
            {
              y = z->parent->parent->left;

                if(y->color==0)
                {
                z->parent->color=1;
                  y->color=1;
                  z->parent->parent->color=0;
                  z = z->parent->parent;
                }

                  else
                  {
                    if(z == z->parent->left)
                    {
                      z = z->parent;
                      RIGHT_REL_ROTATE(tree,z);
                    }

                    z->parent->color=1;
                    z->parent->parent->color=0;
                    LEFT_REL_ROTATE(tree,z->parent->parent);
                 }
              }


        }

        (*tree)->color=1;
}

void REL_INORDER_TREE_WALK(relent tree)
{
  if(tree != relnil)
  {
    REL_INORDER_TREE_WALK(tree->left);
    printf("%s->",tree->entity_pointer->name);
    REL_INORDER_TREE_WALK(tree->right);
  }
}

ent RB_TREE_SEARCH(ent tree,char name[])
{
  if(tree==nil || strcmp(name,tree->name)==0)
    return tree;

    if(strcmp(name,tree->name)<0)
      return RB_TREE_SEARCH(tree->left,name);

      else
        return RB_TREE_SEARCH(tree->right,name);
}

list RELATION_EXIST(ent e,char relation_name[])
{
  list trovato = NULL;
  list temp = e->relations;

    while(trovato == NULL && temp != NULL)
    {
      if(strcmp(temp->relation_name,relation_name)==0)
        trovato = temp;

        temp = temp->next;
    }

    return trovato;
}

list INSERISCI_IN_TESTA(list* l,char relation_name[],report_el rel_pointer)
{
  list p;
  p = malloc(sizeof(struct relation));
  strcpy(p->relation_name,relation_name);
  p->send = relnil;
  p->receive = relnil;
  p->received = 0;
  p->relation_pointer = rel_pointer;
  p->next = *l;
  *l = p;

  return p;
}

list INSERISCI_IN_CODA(list* l,char relation_name[],report_el rel_pointer)
{

  if(*l==NULL)
    return INSERISCI_IN_TESTA(l,relation_name,rel_pointer);

    else
    return INSERISCI_IN_CODA(&((*l)->next),relation_name,rel_pointer);
}

relent RB_REL_TREE_SEARCH(relent tree,char name[])
{
  if(tree==relnil || strcmp(name,tree->entity_pointer->name)==0)
    return tree;

    if(strcmp(name,tree->entity_pointer->name)<0)
      return RB_REL_TREE_SEARCH(tree->left,name);

      else
        return RB_REL_TREE_SEARCH(tree->right,name);
}


void REPORT_PRINT(relent tree)
{
  if(tree != relnil)
  {
  REPORT_PRINT(tree->left);
  fputs(tree->entity_pointer->name,stdout);
  fputs(" ",stdout);
  REPORT_PRINT(tree->right);
  }
}


ent TREE_MINIMUM(ent tree)
{
  while(tree->left != nil)
    tree = tree->left;

    return tree;
}

void RB_DELETE_FIXUP(ent* tree,ent x)
{
  ent w;

  while(x != *(tree) && x->color==1)
  {
      if(x == x->parent->left)
      {
        w = x->parent->right;

          if(w->color==0)
          {
            w->color=1;
            x->parent->color=0;
            LEFT_ROTATE(tree,x->parent);
            w = x->parent->right;
          }

          if(w->left->color==1 && w->right->color==1)
          {
            w->color=0;
            x = x->parent;
          }

            else
            {
              if(w->right->color==1)
              {
                w->left->color=1;
                w->color=0;
                RIGHT_ROTATE(tree,w);
                w = x->parent->right;
              }

                w->color=x->parent->color;
                x->parent->color=1;
                w->right->color=1;
                LEFT_ROTATE(tree,x->parent);
                x = *(tree);

            }
      }

          else
          {
              w = x->parent->left;

                if(w->color==0)
                {
                  w->color=1;
                  x->parent->color=0;
                  RIGHT_ROTATE(tree,x->parent);
                  w = x->parent->left;
                }

                if(w->left->color==1 && w->right->color==1)
                {
                  w->color=0;
                  x = x->parent;
                }

                  else
                  {

                    if(w->left->color==1)
                    {
                      w->right->color=1;
                      w->color=0;
                      LEFT_ROTATE(tree,w);
                      w = x->parent->left;
                    }

                    w->color=x->parent->color;
                    x->parent->color=1;
                    w->left->color=1;
                    RIGHT_ROTATE(tree,x->parent);
                    x = *(tree);
                  }

          }

  }

  x->color=1;
}

relent RB_REL_DELETE(relent* tree,relent z)
{
  int y_original_color;
  relent x,y;

  if(z->left==relnil || z->right==relnil)
    y=z;


    else
      y = REL_TREE_SUCCESSOR(z);


  y_original_color = y->color;


      if(y->left != relnil)
        x = y->left;

        else
          x = y->right;


      x->parent = y->parent;

        if(y->parent == relnil)
          *tree = x;

          else if(y == y->parent->left)
            y->parent->left = x;

            else
              y->parent->right = x;

    if(y != z)//se sono diversi li scambio
    {
      y->parent = z->parent;
      y->right = z->right;
      y->left = z->left;
      z->left->parent = y;
      z->right->parent = y;

      if(*tree != z)//se z non è la radice
      {
        if(z == z->parent->left)
          z->parent->left = y;

            else
              z->parent->right = y;
      }

    else if (*tree == z)
    {
      *tree = y;
      y->parent = relnil;
    }



      y->color = z->color;

    }

    if(y_original_color == 1)
      RB_REL_DELETE_FIXUP(tree,x);

      relnil->parent = relnil;
      relnil->left = relnil;
      relnil->right = relnil;

      return z;
}

relent REL_TREE_MINIMUM(relent tree)
{
  while(tree->left != relnil)
    tree = tree->left;

    return tree;
}

void RB_REL_DELETE_FIXUP(relent* tree,relent x)
{
  relent w;

  while(x != *(tree) && x->color==1)
  {
      if(x == x->parent->left)
      {
        w = x->parent->right;

          if(w->color==0)
          {
            w->color=1;
            x->parent->color=0;
            LEFT_REL_ROTATE(tree,x->parent);
            w = x->parent->right;
          }

          if(w->left->color==1 && w->right->color==1)
          {
            w->color=0;
            x = x->parent;
          }

            else
            {
              if(w->right->color==1)
              {
                w->left->color=1;
                w->color=0;
                RIGHT_REL_ROTATE(tree,w);
                w = x->parent->right;
              }

                w->color=x->parent->color;
                x->parent->color=1;
                w->right->color=1;
                LEFT_REL_ROTATE(tree,x->parent);
                x = *(tree);

            }
      }

          else
          {
              w = x->parent->left;

                if(w->color==0)
                {
                  w->color=1;
                  x->parent->color=0;
                  RIGHT_REL_ROTATE(tree,x->parent);
                  w = x->parent->left;
                }

                if(w->left->color==1 && w->right->color==1)
                {
                  w->color=0;
                  x = x->parent;
                }

                  else
                  {

                    if(w->left->color==1)
                    {
                      w->right->color=1;
                      w->color=0;
                      LEFT_REL_ROTATE(tree,w);
                      w = x->parent->left;
                    }

                    w->color=x->parent->color;
                    x->parent->color=1;
                    w->left->color=1;
                    RIGHT_REL_ROTATE(tree,x->parent);
                    x = *(tree);
                  }

          }

  }

  x->color=1;
}


relent REL_TREE_SUCCESSOR(relent rel_tree)
{

  relent y;

  if(rel_tree->right != relnil)
    return REL_TREE_MINIMUM(rel_tree->right);

    y = rel_tree->parent;

  while(y != relnil && rel_tree == y->right)
  {
    rel_tree = y;
    y = y->parent;
  }

  return y;
}

report_el CREATE_REP_RELATION(char relation_name[])
{
  report_el p = malloc(sizeof(struct nodo));
  p->parent = repnil;
  p->left = repnil;
  p->right = repnil;
  strcpy(p->rel_name,relation_name);
  p->entities = relnil;
  p->max_num = 0;
  p->entities_num = 0;
  return p;
}

void RB_REP_TREE_INSERT(report_el* tree,report_el e)
{
  report_el x,y;

  y = repnil;
  x = *tree;

  while(x != repnil)
  {
    y=x;

      if(strcmp(e->rel_name,x->rel_name)<0)
        x = x->left;

        else
        x = x->right;
  }

  e->parent=y;

    if(y==repnil)//se l'albero è vuoto, la radice dell'albero diventa il nodo inserito
        *tree = e;

        else if(strcmp(e->rel_name,y->rel_name)<0)
          y->left = e;

            else
            y->right = e;

      e->left = repnil;
      e->right = repnil;
      e->color=0;

     RB_REP_INSERT_FIXUP(tree,e);
}
void RIGHT_REP_ROTATE(report_el* tree,report_el x)
{
  report_el y;

  y = x->left;
  x->left = y->right;

  if(y->right != repnil)
    y->right->parent = x;

  y->parent = x->parent;

  if(x->parent==repnil)
      *tree = y;

    else if(x == x->parent->right)
        x->parent->right = y;

      else
        x->parent->left = y;

  y->right = x;
  x->parent = y;
}

void LEFT_REP_ROTATE(report_el* tree,report_el x)
{
  report_el y;

  y = x->right;
  x->right = y->left;

  if(y->left != repnil)
    y->left->parent = x;

  y->parent = x->parent;

  if(x->parent==repnil)
      *tree = y;


    else if(x == x->parent->left)
        x->parent->left = y;

      else
        x->parent->right = y;

  y->left = x;
  x->parent = y;
}

void RB_REP_INSERT_FIXUP(report_el* tree,report_el z)
{

      while(z->parent->color==0)
      {
        report_el y;

        if(z->parent==z->parent->parent->left)
        {
            y = z->parent->parent->right;

            if(y->color==0)
              {
                z->parent->color=1;
                y->color=1;
                z->parent->parent->color=0;
                z = z->parent->parent;
              }

                else
                {
                  if(z == z->parent->right)
                  {
                    z = z->parent;
                    LEFT_REP_ROTATE(tree,z);

                  }

                z->parent->color=1;
                z->parent->parent->color=0;
                RIGHT_REP_ROTATE(tree,z->parent->parent);

              }
         }
            else
            {
              y = z->parent->parent->left;

                if(y->color==0)
                {
                z->parent->color=1;
                  y->color=1;
                  z->parent->parent->color=0;
                  z = z->parent->parent;
                }

                  else
                  {
                    if(z == z->parent->left)
                    {
                      z = z->parent;
                      RIGHT_REP_ROTATE(tree,z);
                    }

                    z->parent->color=1;
                    z->parent->parent->color=0;
                    LEFT_REP_ROTATE(tree,z->parent->parent);
                 }
              }


        }

        (*tree)->color=1;
}

report_el RB_REP_TREE_SEARCH(report_el tree,char relation_name[])
{
  if(tree==repnil || strcmp(relation_name,tree->rel_name)==0)
    return tree;

    if(strcmp(relation_name,tree->rel_name)<0)
      return RB_REP_TREE_SEARCH(tree->left,relation_name);

      else
        return RB_REP_TREE_SEARCH(tree->right,relation_name);
}

void REPORT_INORDER_TREE_WALK(report_el tree)
{
  if(tree != repnil)
  {
    REPORT_INORDER_TREE_WALK(tree->left);
    fputs(tree->rel_name,stdout);
    fputs(" ",stdout);
    REPORT_PRINT(tree->entities);
    printf("%d; ",tree->max_num);
    REPORT_INORDER_TREE_WALK(tree->right);
  }

}

void REPORT_ADJUST_TREE_WALK(ent tree,report_el relation)
{
  if(tree!=nil)
  {
    REPORT_ADJUST_TREE_WALK(tree->left,relation);

    list temp = tree->relations;

    while(temp != NULL && strcmp(temp->relation_name,relation->rel_name)!=0)
      temp = temp->next;

        if(temp!=NULL)//se la relation esiste in quell entita
        {
          if(temp->received > 0 && temp->received==relation->max_num)//dato che in report_adjust entro solo se entities_num==1,di sicuro non rischio di avere 2 volte la stessa entita
            {//TREE SEARCH????

              RB_REL_TREE_INSERT(&(relation->entities),CREATE_REL_ENTITY(tree));
              relation->entities_num++;
            }
        }

    REPORT_ADJUST_TREE_WALK(tree->right,relation);

  }
}


report_el REP_TREE_SUCCESSOR(report_el rep_tree)
{
  report_el y;

  if(rep_tree->right != repnil)
    return REP_TREE_MINIMUM(rep_tree->right);

    y = rep_tree->parent;

  while(y != repnil && rep_tree == y->right)
  {
    rep_tree = y;
    y = y->parent;
  }

  return y;
}

report_el REP_TREE_MINIMUM(report_el tree)
{
    while(tree->left != repnil)
      tree = tree->left;

      return tree;
}

void RB_REP_DELETE_FIXUP(report_el* tree,report_el x)
{
  report_el w;

  while(x != *(tree) && x->color==1)
  {
      if(x == x->parent->left)
      {
        w = x->parent->right;

          if(w->color==0)
          {
            w->color=1;
            x->parent->color=0;
            LEFT_REP_ROTATE(tree,x->parent);
            w = x->parent->right;
          }

          if(w->left->color==1 && w->right->color==1)
          {
            w->color=0;
            x = x->parent;
          }

            else
            {
              if(w->right->color==1)
              {
                w->left->color=1;
                w->color=0;
                RIGHT_REP_ROTATE(tree,w);
                w = x->parent->right;
              }

                w->color=x->parent->color;
                x->parent->color=1;
                w->right->color=1;
                LEFT_REP_ROTATE(tree,x->parent);
                x = *(tree);

            }
      }

          else
          {
              w = x->parent->left;

                if(w->color==0)
                {
                  w->color=1;
                  x->parent->color=0;
                  RIGHT_REP_ROTATE(tree,x->parent);
                  w = x->parent->left;
                }

                if(w->left->color==1 && w->right->color==1)
                {
                  w->color=0;
                  x = x->parent;
                }

                  else
                  {

                    if(w->left->color==1)
                    {
                      w->right->color=1;
                      w->color=0;
                      LEFT_REP_ROTATE(tree,w);
                      w = x->parent->left;
                    }

                    w->color=x->parent->color;
                    x->parent->color=1;
                    w->left->color=1;
                    RIGHT_REP_ROTATE(tree,x->parent);
                    x = *(tree);
                  }

          }

  }

  x->color=1;
}

void REPORT_DELENT_TREE_WALK(ent tree,report_el relation)
{

  if(tree != nil)
  {
  REPORT_DELENT_TREE_WALK(tree->left,relation);

  list temp = tree->relations;

  while(temp != NULL && strcmp(temp->relation_name,relation->rel_name)!=0)
    temp = temp->next;

      if(temp != NULL)//se temp arriva all relazione desiderata
      {
        if(temp->received > 0)//per evitare strutture vuote
        {
            if(temp->received > relation->max_num)//se ho trovato una nuova entità che supera quella in report
            {

              while(relation->entities != relnil)//svuoto la vecchia
                free(RB_REL_DELETE(&(relation->entities),relation->entities));

                relation->entities_num = 0;


                RB_REL_TREE_INSERT(&(relation->entities),CREATE_REL_ENTITY(tree));
                relation->max_num = temp->received;
                relation->entities_num++;

            }

              else if(temp->received == relation->max_num)
              {
                RB_REL_TREE_INSERT(&(relation->entities),CREATE_REL_ENTITY(tree));
                relation->entities_num++;
              }
        }

      }

  REPORT_DELENT_TREE_WALK(tree->right,relation);
  }

}

void RIMUOVI(list* l,char relation_name[])
{
  list cur;
  list pre = NULL;

  cur = *l;

  while(cur != NULL)
  {
    if(strcmp(cur->relation_name,relation_name)==0)
    {
        if(cur==*l)//SE STAI RIMUOVENDO IN TESTA
        {
          *l = cur->next;
          free(cur);
        }

            else//SE STAI RIMUOVENDO IN MEZZO ALLA LISTA
            {
               pre->next = cur->next;
               free(cur);
            }
    }

    pre = cur;
    cur = cur->next;
  }

}

report_el RB_REP_DELETE(report_el* tree,report_el z)
{
  int y_original_color;
  report_el x,y;

  if(z->left==repnil || z->right==repnil)
    y=z;


    else
      y = REP_TREE_SUCCESSOR(z);


  y_original_color = y->color;


      if(y->left != repnil)
        x = y->left;

        else
          x = y->right;


      x->parent = y->parent;

        if(y->parent == repnil)
          *tree = x;

          else if(y == y->parent->left)
            y->parent->left = x;

            else
              y->parent->right = x;

    if(y != z)//se sono diversi li scambio
    {
      y->parent = z->parent;
      y->right = z->right;
      y->left = z->left;
      z->left->parent = y;
      z->right->parent = y;

      if(*tree != z)//se z non è la radice
      {
        if(z == z->parent->left)
          z->parent->left = y;

            else
              z->parent->right = y;
      }

    else if (*tree == z)
    {
      *tree = y;
      y->parent = repnil;
    }



      y->color = z->color;

    }

    if(y_original_color == 1)
      RB_REP_DELETE_FIXUP(tree,x);

      repnil->parent = repnil;
      repnil->left = repnil;
      repnil->right = repnil;

          return z;

}


ent RB_TREE_DELETE(ent* tree,ent z)
{
    int y_original_color;
    ent p,l,r;
    ent x,y;

    if(z->left==nil || z->right==nil)
      y=z;


      else
        y = TREE_SUCCESSOR(z);


   y_original_color = y->color;


        if(y->left != nil)
          x = y->left;

          else
            x = y->right;


        x->parent = y->parent;

          if(y->parent == nil)
            *tree = x;

            else if(y == y->parent->left)
              y->parent->left = x;

              else
                y->parent->right = x;

      if(y != z)//se sono diversi li scambio
      {
        y->parent = z->parent;
        y->right = z->right;
        y->left = z->left;
        z->left->parent = y;
        z->right->parent = y;

        if(*tree != z)//se z non è la radice
        {
          if(z == z->parent->left)
            z->parent->left = y;

              else
                z->parent->right = y;
        }

      else if (*tree == z)
      {
        *tree = y;
       y->parent = nil;
      }



        y->color = z->color;

      }

      if(y_original_color == 1)
        RB_DELETE_FIXUP(tree,x);

        nil->parent = nil;
        nil->left = nil;
        nil->right = nil;

      return z;
}

ent TREE_SUCCESSOR(ent z)
{
  ent y;

  if(z->right != nil)
    return TREE_MINIMUM(z->right);

    y = z->parent;

  while(y != nil && z == y->right)
  {
    z = y;
    y = y->parent;
  }

  return y;
}

relent REL_TREE_DELETE(relent* rel_tree,relent r)
{
  relent x,y;

  if(r->left==relnil || r->right==relnil)
    y=r;


    else
    y = REL_TREE_SUCCESSOR(r);




      if(y->left != relnil)
        x = y->left;

        else
          x = y->right;


      x->parent = y->parent;

        if(y->parent == relnil)
          *rel_tree = x;

          else if(y == y->parent->left)
            y->parent->left = x;

            else
              y->parent->right = x;

    if(y != r)
      r->entity_pointer = y->entity_pointer;


      RB_REL_DELETE_FIXUP(rel_tree,x);

          return y;
}
