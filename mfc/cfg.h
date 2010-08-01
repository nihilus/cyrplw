#ifndef CFG_H
# define CFG_H

#include <stdio.h>

class Cfg
{
  public:
    Cfg(char *);
    virtual ~Cfg();
    int read();
    virtual void parse(char *, char *)
    {
    }
  protected:
    char *read_string(int &size);
    char *my_read_string();
    void process(char *);

    int alloced;
    char *ptr;
    FILE *fp;
    int ida_len;
    const char *ida_dir;
    char *m_name;
    int m_name_len;
};
#endif /* CFG_H */