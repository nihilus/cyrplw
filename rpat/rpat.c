/*
 * Red Plait`s flair pattern maker
 * Based on objdump from library binutils v2.9.1
 *
 * 13-IX-1999	RedPlait (redplait@gmail.com)
 * History:
 *  9-Feb-2005	RedPlait
 *	Make compatible with Binutils version 2.15 (replaced section->_raw_size
 *      with rawsize and renamed struct sec to struct bfd_section)
 *      Also added option -i for names of ignored sections
 * 17-Jul-2010  RedPlait
 *      Rebuild with minGW & binutils-2.20
 */
#include <stdio.h>
#include <stdarg.h>
#include "bfd.h"
#include "bucomm.h"
#include "getopt.h"
#include "demangle.h"
#include "llist.h"

#define	BYTES_IN_WORD	32
#include "aout/aout64.h"

/********** for list of ignored section names **********/
lnlist ign_sect = NULL;
struct ignored_section
{
  struct list list;
  const char *name;
};

void add_ignored_secname(const char *name)
{
  struct ignored_section *added;
  if ( NULL == name )
    return;
  if ( ign_sect == NULL )
   ign_sect = newllist(sizeof(struct ignored_section));
  added = (struct ignored_section *)putobj(ign_sect, ign_sect->last);
  added->name = name; // ACHTUNG - actually name stored in argv, so we don`t need to free it
}

int is_ignore_section(const char *name)
{
  struct ignored_section *iter;
  if ( NULL == name )
    return 0; // cannot detect
  if ( NULL == ign_sect )
    return 0;
  for ( iter = (struct ignored_section *)ign_sect->fist;
        iter != NULL;
        iter = (struct ignored_section *)iter->list.next
      )
   if ( !strcmp(iter->name, name) )
     return 1;
  return 0;
}

/********** for list of possible formats **********/
lnlist p_formats = NULL;
struct p_format
{
  struct list list;
  char *name;
  int ucount;
};

void free_p_formats()
{
  struct p_format *pf, *next_pf;
  if ( !p_formats )
    return;
  for ( pf = (struct p_format *)p_formats->fist;
        pf != NULL;
        pf = next_pf )
  {
    next_pf = (struct p_format *)pf->list.next;
    if ( pf->name )
      free(pf->name);
    free(pf);
  }
  free(p_formats);
}

void add_p_format(char *name)
{
  struct p_format *pf;
  if ( !name )
   return;
  if ( p_formats == NULL )
  {
    p_formats = newllist(sizeof(struct p_format));
  } else {
    for ( pf = (struct p_format *)p_formats->fist;
          pf != NULL;
          pf = (struct p_format *)pf->list.next )
    {
      if ( !strcmp(pf->name, name) )
      {
        pf->ucount++;
        return;
      }
    }
  }
  pf = (struct p_format *)putobj(p_formats, p_formats->last);
  pf->name = strdup(name);
  pf->ucount = 1;
}

void add_p_formats(char **matching)
{
  struct p_format *pf;
  if ( !*matching )
   return;
  while( *matching )
  {
    add_p_format(*matching);
    matching++;
  } 
}

void print_p_formats(FILE *fp)
{
  struct p_format *pf;
  if ( NULL == p_formats )
   return;
  fprintf(fp, "Possible formats:\n");
  for ( pf = (struct p_format *)p_formats->fist;
        pf != NULL;
        pf = (struct p_format *)pf->list.next )
  {
    fprintf(fp, "%s: %d\n", pf->name, pf->ucount);
  }
}

/**************************************************/
static char *default_target = NULL;	/* default at runtime */
static asymbol **syms = NULL;  		/* The symbol table.  */
static long symcount = 0;          	/* Number of symbols in `syms'.  */
static int do_demangle = 0;		/* Demangle names */
static int skip_z = 0;			/* Skip zeroes */

const char *noname = "(NULL)";
const char *version = "1.2";

/* FLAIR imposed restriction on max function size */
#define FLAIR_MAXLEN	0x8000
#define DEFAULT_PATLEN	32
static long pat_len = DEFAULT_PATLEN;

int is_depend = 1;	/* include reference info */
int verbose = 0;	/* verbose messaged */
int function_only = 1;	/* include info on functions only */
int public_only = 1;    /* include info on public symbols only */
FILE *out = NULL;

struct reloc_chain
{
 struct reloc_chain *next;
 char *name;
 int address; 
 int size;
 int offset; /* offset relative function but not section ! */
};

struct function_chain
{
 struct function_chain *next;
 asymbol *sym;
 struct reloc_chain *reloc;
 int offset;
 int size;
};

struct section_chain
{
 struct section_chain *next;
 struct bfd_section *section;
 struct function_chain *funcs;
 unsigned char *content;
};

extern unsigned short crc16(unsigned char *, unsigned short);

#define check_name(s)	((NULL != s) && s[0])

void
print_name(bfd *abfd,FILE *out, const char *name)
{
  char *alloc = NULL;
  if ( do_demangle ) /* Demangle the name.  */
  {
      if (bfd_get_symbol_leading_char(abfd) == name[0])
	++name;
      alloc = cplus_demangle (name, DMGL_ANSI | DMGL_PARAMS);
      if (alloc != NULL)
      {
        int i;
        for ( i = strlen(alloc); i; i-- )
         if ( ' ' == alloc[i-1] )
           alloc[i-1] = '_';
	name = alloc;    
      }
  }
  fprintf(out,"%s ",name);
  if ( NULL != alloc )
    free(alloc);
}

struct section_chain *
find_section(struct section_chain *first, struct bfd_section *s)
{
  for ( ; first != NULL; first=first->next )
  {
   if ( (NULL != first->section->name) && (NULL != s->name) && 
          !strcmp(first->section->name, s->name) )
     return first;
   if ( s == first->section )
     return first;
  }
  return NULL;
}

struct section_chain *
apply_section(bfd *abfd,struct section_chain **first, struct bfd_section *s, long section_size)
{
 struct section_chain *ptr;
 
 if ( NULL == *first )
 {
   *first = (struct section_chain *)malloc(sizeof(struct section_chain));
   (*first)->next = NULL;
   (*first)->funcs = NULL;
   (*first)->section = s;
   (*first)->content = xmalloc(section_size);
   bfd_get_section_contents(abfd,s,(PTR)(*first)->content,0,section_size);
   return *first;
 }
 for ( ptr = *first; ; ptr = ptr->next )
 {
   if ( (NULL != ptr->section->name) && (NULL != s->name) && 
          !strcmp(ptr->section->name, s->name) )
     return ptr;
   if ( s == ptr->section )
     return ptr;
   if ( NULL == ptr->next )
    break;
 }
 ptr->next = (struct section_chain *)malloc(sizeof(struct section_chain));
 ptr = ptr->next;
 ptr->next = NULL;
 ptr->funcs = NULL;
 ptr->section = s;
 ptr->content = xmalloc(section_size);
 bfd_get_section_contents(abfd,s,(PTR)ptr->content,0,section_size);
 return ptr;
}

struct reloc_chain *
free_reloc(struct reloc_chain *r)
{
  struct reloc_chain *res = NULL;
  if ( NULL == r )
    return (struct reloc_chain *)NULL;
  res = r->next;
  if ( r->name != NULL )
    free(r->name);
  free(r);
  return res;
}

void
kill_relocs(struct reloc_chain *first_r)
{
 while ( first_r != NULL )
   first_r = free_reloc(first_r);
}

void
kill_functions(struct function_chain *first)
{
  struct function_chain *ptr;
  while ( first != NULL )
  {
    ptr = first->next;
    if ( NULL != first->reloc )
     kill_relocs(first->reloc);
    free(first);
    first = ptr;
  }
}

void
kill_sections(struct section_chain *first)
{
  struct section_chain *ptr;
  while ( NULL != first )
  {
   ptr = first->next;
   if ( first->funcs )
     kill_functions(first->funcs);
   if ( NULL != first->content )
    free(first->content);
   free(first);
   first = ptr;
  }
}

struct function_chain *
insert_function(struct section_chain *s, asymbol *f)
{
 struct function_chain *prev = NULL;
 struct function_chain *ptr, *f2;
 
 for ( ptr = s->funcs; NULL != ptr; ptr=ptr->next )
 {
   if ( f->value < ptr->offset )
    break;
   prev = ptr;
 }
 /* we needed add this function before prev */
 f2 = (struct function_chain *)malloc(sizeof(struct function_chain));
 f2->sym = f;
 f2->offset = f->value;
 f2->reloc = NULL;
 f2->size = 0;
 f2->next = ptr;
 if ( prev != NULL )
  prev->next = f2;
 else
  s->funcs = f2;
 return f2;
}

struct reloc_chain *
add_reloc(struct function_chain *func, arelent *rel)
{
  struct reloc_chain *prev = NULL;
  struct reloc_chain *ptr, *r2;
  
  if ( rel->address < func->offset ||
       rel->address > (func->offset + func->size) )
   return NULL;
  for ( ptr = func->reloc; NULL != ptr; ptr = ptr->next ) 
  {
    if ( rel->address < ptr->address )
     break;
    prev = ptr;
  }
  /* we needed add new reloc before prev */
  r2 = (struct reloc_chain *)xmalloc(sizeof(struct reloc_chain));
  r2->size = rel->howto->bitsize >> 3;
  r2->address = rel->address;
  r2->offset = rel->address - func->offset;
  r2->name = NULL;
  if ( rel->sym_ptr_ptr != NULL )
  {
   int flags = (*rel->sym_ptr_ptr)->flags;
   if ( !(flags & BSF_SECTION_SYM) )
     r2->name = strdup((*rel->sym_ptr_ptr)->name);
  }
  r2->next = ptr;
  if ( prev != NULL )
   prev->next = r2;
  else
   func->reloc = r2;
  return r2; 
}

int
skip_zeros(struct section_chain *s, struct function_chain *f)
{
  int i;
  struct reloc_chain *rr;

  if ( !skip_z )
    return 0;
  for ( i = 0; i < f->size; )
  {
    if ( (f->reloc != NULL) && f->reloc->offset == i )
    {
      i += f->reloc->size;
      f->reloc = free_reloc(f->reloc);
      continue;
    }
    if ( s->content[f->offset + i] != 0    && /* just zeroes */
         s->content[f->offset + i] != 0x90    /* x86 nops    */
       )
      break;
    i++;
  }
  if ( !i )
    return 0;
  /* aha - we must shrink size and readjust relocs */
  f->size -= i;
  f->offset += i;
  for ( rr = f->reloc; rr != NULL; rr=rr->next )
  {
    rr->offset -= i;
  }
  return 0;
}

void
assign_sizes(struct section_chain *first)
{
  struct section_chain *ptr;
  struct function_chain *f, *f_ptr;
  int section_size;
  
  for ( ptr = first; NULL != ptr; ptr = ptr->next )
  {
    section_size = bfd_get_section_limit(ptr->section->owner, ptr->section);
    for ( f_ptr = ptr->funcs; NULL != f_ptr; f_ptr=f_ptr->next )
    {
      if ( NULL == f_ptr->next )
      {
        f_ptr->size = section_size - f_ptr->offset;
      } else
      {
        f_ptr->size = f_ptr->next->offset - f_ptr->offset;
      }
    }
    /* and now slowdown our appetite */
    for ( f_ptr = ptr->funcs; NULL != f_ptr; f_ptr=f_ptr->next )
    {
      if ( f_ptr->size >= FLAIR_MAXLEN )
       f_ptr->size = FLAIR_MAXLEN - 1;
    }
  }
}

void
assign_rel(struct section_chain *s, arelent *r)
{
 struct function_chain *f;
 
 for ( f = s->funcs; NULL != f; f = f->next )
 {
    if ( NULL != add_reloc(f,r) )
      return;
 }
}

int section_filter(const char *section_name, const char *symbol_name)
{
  if ( section_name == NULL )
   return 0;
  if ( !strcmp(section_name, symbol_name) )
   return 1;
  return 0;
}

void
process_file(bfd *abfd)
{
  asymbol **syms = NULL;  		/* The symbol table.  */
  char **matching;
  long storage;
  int count;
  asymbol **current;
  struct section_chain *first_s = NULL, *s;
  struct function_chain *f;
  const char *name;
  asection *a;
  struct reloc_chain *rr;
  int curr_len, up_to;
  
  if ( verbose )
    printf("Process file %s\n", bfd_get_filename(abfd) );
  if (!bfd_check_format_matches (abfd, bfd_object, &matching))
  {
      bfd_nonfatal (bfd_get_filename (abfd));
      if (bfd_get_error () == bfd_error_file_ambiguously_recognized)
      {
          add_p_formats(matching);
	  list_matching_formats (matching);
	  free (matching);
      }
      return;
  }
  if (!(bfd_get_file_flags (abfd) & HAS_SYMS))
  {
    fprintf (stderr,"No symbols in \"%s\".\n", bfd_get_filename (abfd));
    return;
  }
  storage = bfd_get_symtab_upper_bound (abfd);
  if (storage < 0)
    bfd_fatal (bfd_get_filename (abfd));
  if (storage)
   syms = (asymbol **) xmalloc (storage);
  symcount = bfd_canonicalize_symtab(abfd, syms);
  if (symcount < 0)
  {
    bfd_fatal(bfd_get_filename(abfd));
    if ( NULL != syms )
      free(syms);
    return;
  }
  if (symcount == 0)
  {
    fprintf (stderr, "%s: No symbols\n",bfd_get_filename (abfd));
    if (NULL != syms)
      free(syms);
    return;
  }
  current = syms;
  for ( count = 0; count < symcount; count++, current++ )
  {
    if ( *current )
    {
      int flags;
      long section_size;
      
      bfd *cur_bfd = bfd_asymbol_bfd(*current);
      if ( cur_bfd != NULL )
      {
        flags = (*current)->flags;
	if ( flags & BSF_WEAK ) /* I don`t need aliases */
	  continue;
        if ( verbose )
/* RP */    printf(":Name %s flags %lx, value %lx\n", 
                 (*current)->name, flags, (*current)->value );
	if ( NULL == (*current)->section )
	 continue;
	section_size = bfd_section_size(abfd,(*current)->section);
	if ( section_size <= 0 )
	 continue;
	if ( is_ignore_section((*current)->section->name) )
         continue;
        if ( section_filter((*current)->section->name, (*current)->name) )
         continue;
	s = apply_section(abfd, &first_s, (*current)->section, section_size );
	insert_function(s, *current );
      }
    }
  }
  assign_sizes(first_s);
  /* next I had to process relocations */
  for ( a = abfd->sections; a != NULL; a=a->next )
  {
    long relsize, relcount;
    arelent **relpp, **p;
    struct section_chain *apply_sec;
    
    if ( bfd_is_abs_section(a) )
     continue;
    if ( bfd_is_und_section(a) )
     continue;
    if ( bfd_is_com_section(a) )
     continue;
    if ( ! (a->flags & SEC_RELOC) )
     continue;
    relsize = bfd_get_reloc_upper_bound(abfd,a);
    if ( relsize < 0 )
     bfd_fatal(bfd_get_filename(abfd)); 
    if ( !relsize )
     continue;
    apply_sec = find_section(first_s, a);
    if ( NULL == apply_sec )
     continue;     
    if ( verbose ) 
/* RP */ printf("Reloc section name is %s\n", a->name );
    relpp = (arelent **)xmalloc(relsize);
    relcount = bfd_canonicalize_reloc(abfd,a,relpp,syms);
    if ( relcount <= 0 )
    {
      free(relpp);
      continue;
    }
    for (p=relpp; relcount && *p != (arelent *)NULL; p++, relcount-- )
    {
      arelent *q = *p;
      assign_rel(apply_sec,q);
#ifdef RP_DEBUG
/* RP */      
      if ( q->sym_ptr_ptr != NULL )
      {
        printf("Reloc: name %s vma %d, flags %lx\n",
	 (*q->sym_ptr_ptr)->name ? (*q->sym_ptr_ptr)->name : noname,
	 bfd_asymbol_value((*q->sym_ptr_ptr)),
	 (*q->sym_ptr_ptr)->flags );
      }
      printf("Reloc: addres %0lx, addend %0lx, bitsize %d\n",
       q->address, q->addend,
       q->howto->bitsize );
/* -RP- */
#endif
    }
    free(relpp);
  }
  /* main processing - I want a result ! */
  for ( s = first_s; NULL != s; s=s->next )
  {
    int flags;
    long max_f_len;
    if ( verbose )
     printf("Section: %s, size %0lx\n", 
        s->section->name ? s->section->name : noname,
        bfd_get_section_limit(s->section->owner, s->section) );
    for ( f = s->funcs; NULL != f; f=f->next )
    {
        struct reloc_chain *r;
        int dots;
        /* we must filter here - to don`t lose sizes ! */
       	if ( ! check_name(f->sym->name) )
  	  continue;
 	if ( section_filter(s->section->name, f->sym->name) )
          continue;
        flags = f->sym->flags;
	if ( public_only && (BSF_EXPORT != (flags & BSF_EXPORT)) )
	  continue;
        /* I don`t need signature on whole section and files */
	if ( (BSF_SECTION_SYM & flags) || (BSF_FILE & flags) )
	  continue;
	if ( !( !function_only ||
 	     ((flags & BSF_FUNCTION) || (flags & BSF_OBJECT)) ) 
           )
	    continue;

       	/* now we have function to produce signature */
#ifdef RP_DEBUG
	printf("Section name %s, size %d, vma = %lx\n", 
	  (*current)->section->name,
	  bfd_section_size(abfd,(*current)->section), (*current)->section->vma);
#endif
        /* dump this function and relocs if -v */
        if ( verbose )
        {
          printf("Name: %s, base %d value %0lx, flags %lx, size %0lx\n",
            bfd_asymbol_name(f->sym), bfd_asymbol_base(f->sym), 
	    bfd_asymbol_value(f->sym), f->sym->flags, f->size 
          );
	  for ( r = f->reloc; NULL != r; r=r->next )
	  {
	    printf("Reloc: name %s size %d address %0lx offset %0lx\n",
	      r->name ? r->name : noname,
	      r->size, r->address, r->offset 
            );
	  }
	}

        curr_len = skip_zeros(s,f); 
	if ( f->size < pat_len ) /* bad - we have too short functions */
	{
	  if ( verbose )
	    printf("Too short (%d bytes) - skipping...\n", f->size);
	  continue;
	} 
        max_f_len = f->size;
        /* from pat.txt:
         * Total length of a module should be < 0x8000
         */
        if ( max_f_len >= 0x8000 )
          max_f_len = 0x7fff;

	rr = f->reloc;
        up_to = ( rr != NULL ) ? rr->offset : max_f_len;
	while ( curr_len < pat_len )
	{
	  if ( curr_len < up_to )
	  {
	    fprintf(out,"%02X", s->content[curr_len++ + f->offset]);
	    continue;
	  }
	  for ( dots = 0; dots < rr->size; curr_len++, dots++ )
	  {
	    if ( !(curr_len < pat_len) )
	      break;
	    fprintf(out,"..");
	  }
	  if ( !(curr_len < pat_len) )
	    break;
	  rr = rr->next;
          up_to = ( rr != NULL ) ? rr->offset : max_f_len;
	}
	fprintf(out," ");

	/* calc crc on next block */
#ifdef RP_DEBUG	
/* RP */ fprintf(out, "curr_len %lx, up_to %lx\n", curr_len, up_to );
#endif
	if ( (up_to < curr_len) && 
             (NULL != rr) && 
             ((up_to + rr->size) > curr_len) 
           )
 	    fprintf(out,"00 0000 ");
	else
	{
	  unsigned short crc_len;
	  if ( (up_to < curr_len) && NULL != rr )
	  {
	    rr = rr->next;
            up_to = ( rr != NULL ) ? rr->offset : max_f_len;
	  } else if ( NULL == rr )
 	     up_to = max_f_len;
	  crc_len = (unsigned short)((up_to - curr_len) & 0xffff);
#ifdef RP_DEBUG
/* RP */ printf("CRC_LEN %02x", crc_len);
#endif
          /* From flair/pat.txt:
           * Maximal length of this block is 255 bytes.
           */
          if ( crc_len > 0xff )
	    crc_len = 0xff;
	  fprintf(out,"%02X %04X ", crc_len, crc16(s->content + curr_len, crc_len) );
	}

	/* public name of this function */
	fprintf(out,"%04X :0000 ", max_f_len);
        print_name(abfd,out,bfd_asymbol_name(f->sym));

        /* dump relocs */
	if ( is_depend )
	{
	  for ( r = f->reloc; NULL != r; r = r->next )
	  {
	    if ( check_name(r->name) && (r->offset < max_f_len) )
            {
	      fprintf(out,"^%04X ", r->offset);
              print_name(abfd,out,r->name);
            }
	  }
	}

	/* dump rest of function body */
	if ( up_to < curr_len )
	{
	 for ( ; (dots < rr->size) && (curr_len < max_f_len); dots++, curr_len++ )
	   fprintf(out,"..");
	 rr = rr->next;
         up_to = ( rr != NULL ) ? rr->offset : max_f_len;
	}   
#ifdef RP_DEBUG	  
/* RP */ fprintf(out,"curr_len %lx rr %p up_to %lx\n", curr_len, rr, up_to ); fflush(out);
#endif
	while ( curr_len < max_f_len )
	{
	  if ( curr_len < up_to )
	  {
	    fprintf(out,"%02X", s->content[curr_len + f->offset]);
	    curr_len++;
	    continue;
	  }
	  for ( dots = 0; 
                (dots < rr->size) && (curr_len < max_f_len); 
                curr_len++, dots++ 
              )
	      fprintf(out,"..");
	  rr = rr->next;
	  up_to = ( rr != NULL ) ? rr->offset : max_f_len;
	}
	fprintf(out,"\n");
    }
  }
  if ( NULL != syms )
    free(syms);
  kill_sections(first_s);        	
}

void
process_filez(const char *filename)
{
  bfd *file;
  bfd *arfile = (bfd *) NULL;

  file = bfd_openr (filename, default_target);
  if ( NULL == file )
  {
    bfd_nonfatal(filename);
    return;
  }
  if (bfd_check_format (file, bfd_archive) == TRUE)
  {
    bfd *last_arfile = NULL;
    for ( ; ; )
    {
      bfd_set_error (bfd_error_no_error);

      arfile = bfd_openr_next_archived_file (file, arfile);
      if (arfile == NULL)
      {
         if (bfd_get_error () != bfd_error_no_more_archived_files)
     	 {
	   bfd_nonfatal (bfd_get_filename (file));
	 }
	 break;
      }
      if ( verbose )
         printf("File: %s\n", arfile->filename);
      process_file(arfile);
      if (last_arfile != NULL)
	bfd_close(last_arfile);
      last_arfile = arfile;
    }
    if (last_arfile != NULL)
      bfd_close (last_arfile);
  }
  else
    process_file(file);
  bfd_close (file);
}

void dump_supported_formats(FILE *out)
{
 extern const bfd_target *const *bfd_target_vector;
 int t;

 fprintf(out,"Supported formats:\n");
 for ( t=0; bfd_target_vector[t]; t++ )
 {
   fprintf(out," - %s\n", bfd_target_vector[t]->name );
 }
}

void
usage(FILE *out)
{
 fprintf(stderr,"Usage: pat [-i secname] [-p pattern_len] [-o filename] [-a] file ...\n"
"\t-C Demangle names\n"
"\t-a Append to output file\n"
"\t-b Dump supported formats\n"
"\t-B List object formats and architectures supported\n"
"\t-f File format\n"
"\t-g Include all global object (not functions only)\n"
"\t-i Section name to ignore\n"
"\t-n Include non-public names\n"
"\t-o Sets output file name\n"
"\t-p Pattern length\n"
"\t-r Dont include reference to other functions\n"
"\t-v Verbose mode (useful for developers only)\n"
"\t-z Skip zeroes\n"
 );
 fprintf(stderr,"Version: %s\n", version );
 exit(3);
}

int
main(int argc, char **argv)
{
 const char *openflags[] = {
 "w",
 "a"
};
 
 int c;
 int dump_formats = 0;
 int formats_info = 0;
 int is_append = 0;
 char *outfilename = NULL;
 
 program_name = *argv;
 xmalloc_set_program_name(program_name);
 bfd_init();
 set_default_bfd_target();
 
 while( EOF != (c = getopt(argc, argv, "i:p:o:f:BCabrvgnz")) )
 {
   switch(c)
   {
     case 'B':
       formats_info = 1;
      break;
     case 'C':
       do_demangle = 1;
      break;
     case 'a': 
       is_append = 1;
      break;
     case 'b':
       dump_formats = 1;
      break;
     case 'f':
       default_target = optarg;
      break;
     case 'g':
       function_only = 0;
      break;
     case 'i':
       add_ignored_secname(optarg);
      break;
     case 'n':
       public_only = 0;
      break;
     case 'p':
       pat_len = atoi(optarg);
       if ( pat_len <= 0 )
       {
         fprintf(stderr,"Waring - pattern length has bad value, changed to %d\n",
	  DEFAULT_PATLEN );
	 pat_len = DEFAULT_PATLEN; 
       }
      break;
     case 'o':
       outfilename = optarg;
      break;
     case 'r':
       is_depend = 0;
      break;
     case 'v':
       verbose = 1;
      break;
     case 'z':
       skip_z = 1;
      break;
     default:
      usage(stdout);
   }
 }
 /* check if need just dump some info */
 if ( dump_formats )
   dump_supported_formats(stdout);
 if ( formats_info ) 
   display_info();
 if ( dump_formats || formats_info )
   return 0;

 /* check if we have some library in args */
 if ( ! (optind < argc) )
   usage(stdout);
 if ( outfilename != NULL )
 { 
   if ( NULL == (out = fopen(outfilename,openflags[is_append])) )
   {
     fprintf(stderr,"Cannot open output file %s on %s\n", 
       outfilename, openflags[is_append] );
     exit(2);  
   }
 } else
  out = stdout;  
 for ( ; optind < argc ; optind++ )
 {
   process_filez(argv[optind]);
 }
 fprintf(out,"---\n");
 if ( p_formats )
 {
   print_p_formats(stderr);
   free_p_formats();
 }
 if ( ign_sect != NULL )
  delllist(ign_sect);
 if ( out != NULL && out != stdout )
  fclose(out);
 return 0;
}
