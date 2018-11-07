#ifndef INI_FILE_H
#define INI_FILE_H

typedef struct IniFile INI_FILE;

INI_FILE* IniFile_Load(const char *file);
void IniFile_Release(INI_FILE *file);
const char* IniFile_Value(INI_FILE *file, const char *section, const char *key);

#endif
