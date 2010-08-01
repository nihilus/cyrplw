/***********************************************************************
 * Набор функций для обеспечения построения связанного списка объектов *
 ***********************************************************************/
# ifndef _LLIST_H
# define _LLIST_H

#if __cplusplus
extern "C" {
#endif

struct list {  /* данную структуру пользователь включает в свою для */
               /* подключения ее к связному списку в нее входят */
               /* указатели на предыдущий и последующий объекты списка */
    struct list   *prev, *next;
};

struct llist { /* структура управления списком. в нее входят указатели */
                 /* на первый - fist, последний - last, текущий - curr */
          /* элементы списка, а также число элементов - all и их рамер - sz */
    struct list   *fist, *last, *curr;
    unsigned int all;
    unsigned long sz;
};

typedef struct llist *lnlist; /* указатель на структуру управления списком */
typedef struct list *object;  /* указатель на элемент списка !!! */

/* функция создает управляющую структуру для ведения связного списка */
lnlist   newllist(unsigned long sz);

/* функция слияния двух связных списков */
/* список tail сливается с main и помещается после элемента after, при
 * этом не происходит копирование элементов - они остаются физически
 * связаны со списком tail 
 * Возвращается общее число элементов в списке main
 */
int merge_lists(lnlist main, lnlist tail, object after);

/* функция момещает объект в св. список */
/* помещенный объект становится текущим */
void  *putobj(lnlist llst, object after);

/* функция смещает указатель текущего объекта списка на следующий объект */
/* возвращает указатель на текущий объект */
void  *succobj(lnlist llst);

/* функция смещает указатель текущего объекта списка на предыдущий объект */
/* возвращает указатель на текущий объект */
void  *predobj(lnlist llst);

/* процедура удаляет объект из св. списка */
/* первый объект списка становится текущим */
void  delobj(object obj, lnlist llst);

/* функция вырезает объект из связного списка */
object cut_obj(lnlist l,object obj);

/* функция вставляет элемент obj перед элементом to */
void insert_obj(lnlist l,object to,object obj);

/* процедура освобождает память от упр. списком структуры */
void  delllist(lnlist llst);

/* функция быстрой очистки связного списка */
void clear_llist(lnlist, void (*)(object));

/* функция быстрого удаления связного списка */
void fast_delllist(lnlist, void (*)(object));
void fast_delete(object , void (*)(object));

void *cycle_succobj(lnlist l);
void *cycle_predobj(lnlist l);
/* перемещает объект two и помещает его перед объектом one. Если one is *
 * NULL ,объект будет помещен в начало списка */
void  remove_obj(lnlist l, object one, object two);

/* меняет местами два объекта связного списка */
void  swap_obj(lnlist l, object one, object two);

/* сортировка связного списка l по функции function */
void sort_list(lnlist l,int (*function)(object a,object b));

/* возвращает порядковый номер элемента  obj */
int get_curr(lnlist l,object obj);

/* устанавливает текущим элемент с порядковым номером n */
object set_curr(lnlist l,int n);

/* первый объект списка - текущий. */
# define resetobj(llst)   ((llst)->curr = (llst)->fist)
# define fistobj(llst)   ((llst)->fist) /* первый объект списка */
# define lastobj(llst)   ((llst)->last) /* последний объект списка */
# define currobj(llst)   ((llst)->curr) /* текущий объект списка */
# define allobj(llst)    ((llst)->all)  /* число объектов в списке */

#if __cplusplus
};
#endif

# endif
