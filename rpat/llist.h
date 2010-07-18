/***********************************************************************
 * ����� ������� ��� ����������� ���������� ���������� ������ �������� *
 ***********************************************************************/
# ifndef _LLIST_H
# define _LLIST_H

#if __cplusplus
extern "C" {
#endif

struct list {  /* ������ ��������� ������������ �������� � ���� ��� */
               /* ����������� �� � �������� ������ � ��� ������ */
               /* ��������� �� ���������� � ����������� ������� ������ */
    struct list   *prev, *next;
};

struct llist { /* ��������� ���������� �������. � ��� ������ ��������� */
                 /* �� ������ - fist, ��������� - last, ������� - curr */
          /* �������� ������, � ����� ����� ��������� - all � �� ����� - sz */
    struct list   *fist, *last, *curr;
    unsigned int all;
    unsigned long sz;
};

typedef struct llist *lnlist; /* ��������� �� ��������� ���������� ������� */
typedef struct list *object;  /* ��������� �� ������� ������ !!! */

/* ������� ������� ����������� ��������� ��� ������� �������� ������ */
lnlist   newllist(unsigned long sz);

/* ������� ������� ���� ������� ������� */
/* ������ tail ��������� � main � ���������� ����� �������� after, ���
 * ���� �� ���������� ����������� ��������� - ��� �������� ���������
 * ������� �� ������� tail 
 * ������������ ����� ����� ��������� � ������ main
 */
int merge_lists(lnlist main, lnlist tail, object after);

/* ������� �������� ������ � ��. ������ */
/* ���������� ������ ���������� ������� */
void  *putobj(lnlist llst, object after);

/* ������� ������� ��������� �������� ������� ������ �� ��������� ������ */
/* ���������� ��������� �� ������� ������ */
void  *succobj(lnlist llst);

/* ������� ������� ��������� �������� ������� ������ �� ���������� ������ */
/* ���������� ��������� �� ������� ������ */
void  *predobj(lnlist llst);

/* ��������� ������� ������ �� ��. ������ */
/* ������ ������ ������ ���������� ������� */
void  delobj(object obj, lnlist llst);

/* ������� �������� ������ �� �������� ������ */
object cut_obj(lnlist l,object obj);

/* ������� ��������� ������� obj ����� ��������� to */
void insert_obj(lnlist l,object to,object obj);

/* ��������� ����������� ������ �� ���. ������� ��������� */
void  delllist(lnlist llst);

/* ������� ������� ������� �������� ������ */
void clear_llist(lnlist, void (*)(object));

/* ������� �������� �������� �������� ������ */
void fast_delllist(lnlist, void (*)(object));
void fast_delete(object , void (*)(object));

void *cycle_succobj(lnlist l);
void *cycle_predobj(lnlist l);
/* ���������� ������ two � �������� ��� ����� �������� one. ���� one is *
 * NULL ,������ ����� ������� � ������ ������ */
void  remove_obj(lnlist l, object one, object two);

/* ������ ������� ��� ������� �������� ������ */
void  swap_obj(lnlist l, object one, object two);

/* ���������� �������� ������ l �� ������� function */
void sort_list(lnlist l,int (*function)(object a,object b));

/* ���������� ���������� ����� ��������  obj */
int get_curr(lnlist l,object obj);

/* ������������� ������� ������� � ���������� ������� n */
object set_curr(lnlist l,int n);

/* ������ ������ ������ - �������. */
# define resetobj(llst)   ((llst)->curr = (llst)->fist)
# define fistobj(llst)   ((llst)->fist) /* ������ ������ ������ */
# define lastobj(llst)   ((llst)->last) /* ��������� ������ ������ */
# define currobj(llst)   ((llst)->curr) /* ������� ������ ������ */
# define allobj(llst)    ((llst)->all)  /* ����� �������� � ������ */

#if __cplusplus
};
#endif

# endif
