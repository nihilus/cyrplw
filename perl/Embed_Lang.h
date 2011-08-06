#ifndef EMBED_LANG_H
# define EMBED_LANG_H	"Interface for embedded language"

class Embed_Language
{
 public:
  virtual ~Embed_Language()	{}
  virtual int Init() = 0;
  virtual int ParseScript(char *) = 0;
  virtual int RunScript(char *) = 0;
  virtual void *get_true_interpretor() = 0;
};

#endif /* EMBED_LANG_H */
