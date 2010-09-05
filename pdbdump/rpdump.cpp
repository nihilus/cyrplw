#include "hierarchy.h"
#include <string.h>

void fix_mfc(CPdb *pdb)
{
   struct pdb_class *pc = pdb->find_class("IUnknown");
   if ( pc )
    pc->add_method(_strdup("long __stdcall QueryInterface(struct _GUID&, void**)"), 0, true);
}

int main(int argc, char **argv)
{
   int do_fix = 0;
   if ( argc > 2 && argv[1][0] == '-' && argv[1][1] == 'f' && !argv[1][2] )
   {
     argc--;
     argv++;
     do_fix = 1;
   }
   if ( argc != 2 )
   {
     fprintf(stderr, "Syntax: rpdump <RPD filename>\n");
     return 1;
   }
   FILE *fp = fopen(argv[1], "rb");
   if ( fp == NULL )
   {
     fprintf(stderr, "Cannot open file '%s'\n", argv[1]);
     return 2;
   }
   CPdb pdb;
   pdb.read(fp);
   if ( do_fix )
    fix_mfc(&pdb);
   pdb.dump(stdout);
   fclose(fp);
   if ( do_fix )
   {
     fp = fopen(argv[1], "wb");
     if ( fp )
     {
       pdb.write(fp);
       fclose(fp);
     }
   }
   return 0;
}