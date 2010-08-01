/***********************************************************************
 * Набор функций для обеспечения построения связанного списка объектов *
 ***********************************************************************/

#ifndef _STDLIB_H_
# include <stdlib.h>
#endif

#ifndef _LLIST_H
# include "llist.h"
#endif

lnlist newllist(unsigned long sz)
{
    lnlist l;

    if (l = (lnlist)malloc(sizeof(struct llist))) {
	l->all = 0;
	l->fist = l->last = l->curr = NULL;
        l->sz = sz;
    } else
        abort();
    return l;
}

void *putobj(lnlist l,object to)
{
  object obj;
  if ((obj = (object)calloc(1, l->sz)) == NULL ) abort();
  if ( 0 == l->all++ ) { l->fist = l->last = l->curr = obj;
			 obj->prev = obj->next = NULL; }
  else insert_obj(l,to,obj);
  return obj;
}

void  *succobj(lnlist l)
{
    if (l->curr->next != NULL )
        return (l->curr = l->curr->next);
    else
	return NULL;
}

void *cycle_succobj(lnlist l)
{
    if (l->curr->next != NULL )
       return (l->curr = l->curr->next);
    else /* последний элемент списка */
       return (l->curr = l->fist); /* вернем первый */
}

void  *predobj(lnlist l)
{
    if (l->curr->prev != NULL )
        return (l->curr = l->curr->prev);
    else
	return NULL;
}

void *cycle_predobj(lnlist l)
{
    if (l->curr->prev != NULL )
       return (l->curr = l->curr->prev);
    else
       return (l->curr = l->last); /* иначе - вернем последний элемент */
}

void  delobj(object obj, lnlist l)
{
    cut_obj(l,obj); /* супермодерн */
    l->all -= 1;
    free(obj);
}

void  delllist(lnlist l)
{
    l->curr = l->fist;
    while (l->all)
      delobj(currobj(l), l);
    free(l);
  return;
}

void clear_llist(lnlist l, void (*curr_del)(object))
{
  if ( fistobj(l) )
   fast_delete(fistobj(l), curr_del);
  l->all = 0;
  fistobj(l) = lastobj(l) = NULL;
  return;
}

void fast_delete(object a, void (*curr_del)(object))
{ 
  if ( a->next != NULL ) fast_delete(a->next, curr_del);
  (*curr_del)(a);
  return;
}

void fast_delllist(lnlist l, void (*curr_del)(object))
{ 
  if ( fistobj(l) != NULL ) fast_delete(fistobj(l),curr_del);
  free(l);
  return;
}

object cut_obj(lnlist l,object obj)
{
  /* вырезает объект obj из связного списка */
 if ( currobj(l) == obj )
     currobj(l) = ( obj->next != NULL ) ? obj->next : obj->prev;
 if ( obj->next != NULL )
      obj->next->prev = ( obj->prev != NULL ) ? obj->prev : NULL ;
 if ( obj->prev != NULL )
      obj->prev->next = ( obj->next != NULL ) ? obj->next : NULL ;
 if ( obj->prev == NULL ) fistobj(l) = obj->next;
 if ( obj->next == NULL ) lastobj(l) = obj->prev;
 obj->next = obj->prev = NULL;
 return obj;
}

void insert_obj(lnlist l,object to,object obj)
{
  /* вставляет obj после to */
 if ( fistobj(l) == NULL )
 {
   fistobj(l) = lastobj(l) = obj;
   obj->next = obj->prev = NULL;
   return;
 }
 if ( to == NULL ) /* вставить в начало списка */
  {
   fistobj(l)->prev = obj;
   obj->next = fistobj(l);
   obj->prev = NULL;
   fistobj(l) = obj;
  } else {
	  obj->prev = to;
	  if ( to->next == NULL ) lastobj(l) = obj;
	   else to->next->prev = obj;
	  obj->next = to->next;
	  to->next = obj;
	 }
}

void remove_obj(lnlist l,object o1,object o2)
{ 
   /* вырезать и вставить объект o2 после объекта o1 */
 if (o1 == o2) return;
 cut_obj(l,o2);
 insert_obj(l,o1,o2);
}

void swap_obj(lnlist l,object o1,object o2)
{
 object t_prev = o1->prev;
 object t_next = o1->next;
 if ( o1 == o2 )
	return;
 if ( NULL != t_prev )
  t_prev->next = o2;
 else
  l->fist = o2;
 if ( NULL != t_next )
  t_next->prev = o2;
 else
  l->last = o2;
 o1->prev = o2->prev;
 o1->next = o2->next;
 if ( o1->prev != NULL )
  o1->prev->next = o1;
 else
  l->fist = o1;
 if ( o1->next != NULL )
  o1->next->prev = o1;
 else
  l->last = o1;

 if ( o2 == t_prev )
  o2->prev = o1;
 else
  o2->prev = t_prev;
 if ( o2 == t_next )
  o2->next = o1;
 else
  o2->next = t_next;
}

void sort_list(lnlist l, int (*function)(object a,object b))
/* function должна возвращать 1, если объект b нужно поставить перед
   объетом a , и 0 в противном случае */
{
 object ptr,tmp,next_obj;
 int function_return=0;

 for ( ptr=fistobj(l); ptr!=NULL ; ptr=next_obj )
 {
   function_return = 0;
   next_obj = ptr->next;
   for( tmp=fistobj(l); tmp!=ptr && (!function_return); tmp=tmp->next )
	if ( function_return=(*function)(tmp,ptr) )
		remove_obj(l,tmp->prev,ptr);
 }
}

int get_curr(lnlist l,object o)
{
 register int count=1;
 object ptr;
 if ( currobj(l) == NULL ) return 0; /* нет объектов - первый */
 for ( ptr = fistobj(l) ; ptr != o && ptr!= NULL ; count++ )
       ptr = ptr->next;
 return ( ptr == NULL ) ? -1 : count;
}

object set_curr(lnlist l,int pos)
{
 object obj;
 int all = l->all;
 if (!all) return (currobj(l) = NULL);
 if ( !pos ) return (currobj(l) = fistobj(l));
 if ( pos > all ) return (currobj(l) = lastobj(l));
 if ( (all>>1) > pos )
  for ( obj=lastobj(l) ; all != pos ; all-- )
	obj = obj->prev;
 else 
 { 
	all = 1;
  for ( obj=fistobj(l) ; all != pos ; all++ )
	obj = obj->next; 
 }
 return (currobj(l)=obj);
}

int
merge_lists(lnlist main, lnlist tail, object after)
{
  if ( NULL == tail || !tail->all )
   return main->all;
  if ( after == main->last ) /* place after last element */
  {
    after->next = tail->fist;
    tail->fist->prev = after;
    main->last = tail->last;
  } else if ( after == NULL ) /* insert in begin of list */
  {
    main->fist->prev = tail->last;
    tail->last->next = main->fist;
    main->fist = tail->fist;    
  } else { /* insert somewhere in middle of list */
    after->next->prev = tail->last;
    tail->last->next = after->next;
    after->next = tail->fist;
    tail->fist->prev = after;
  }
  tail->all += tail->all;
  return main->all;
}