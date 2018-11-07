#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "IniFile.h"

#define LINE_LENGTH_MAX 4096

typedef struct IniFileKeyValue
{
	char *name;
	char *value;
	struct IniFileKeyValue *next;
} INI_FILE_KEY_VALUE;

typedef struct IniFileSection
{
	char *name;
	INI_FILE_KEY_VALUE *firstValue;
	struct IniFileSection *next;
} INI_FILE_SECTION;

struct IniFile
{
	INI_FILE_SECTION *firstSection;
};

INI_FILE* IniFile_Init(void)
{
	INI_FILE *file;
	INI_FILE_SECTION *section;

	section = malloc(sizeof(INI_FILE_SECTION));
	memset(section, 0, sizeof(INI_FILE_SECTION));
	section->name = _strdup("");

	file = malloc(sizeof(INI_FILE));
	memset(file, 0, sizeof(INI_FILE));
	file->firstSection = section;

	return file;
}

INI_FILE_SECTION* IniFile_LoadSection(char *buf)
{
	int len;

	len = strlen(buf);
	if (len > 2 && buf[0] == '[' && buf[len - 1] == ']')
	{
		INI_FILE_SECTION *section;

		section = malloc(sizeof(INI_FILE_SECTION));
		memset(section, 0, sizeof(INI_FILE_SECTION));

		buf[len - 1] = '\0';
		section->name = _strdup(buf + 1);

		return section;
	}

	return NULL;
}

INI_FILE_KEY_VALUE* IniFile_LoadKeyValue(char *buf)
{
	char *delim;

	delim = strchr(buf, '=');
	if (delim && delim != buf)
	{
		INI_FILE_KEY_VALUE *value;

		*delim++ = '\0';
		for (; *delim && isspace(*delim); delim++);

		value = malloc(sizeof(INI_FILE_KEY_VALUE));
		memset(value, 0, sizeof(INI_FILE_KEY_VALUE));

		value->name = _strdup(buf);
		value->value = _strdup(delim);

		return value;
	}

	return NULL;
}

void IniFile_LoadContents(INI_FILE *ini, FILE *fp)
{
	INI_FILE_SECTION *current;
	char buf[LINE_LENGTH_MAX];

	current = ini->firstSection;
	while (fgets(buf, LINE_LENGTH_MAX, fp))
	{
		int len;
		INI_FILE_SECTION *section;
		INI_FILE_KEY_VALUE *value;

		len = strlen(buf);

		if (len <= 0)
			continue;

		if (buf[len - 1] == '\n')
			buf[--len] = '\0';

		if (len == 0)
			continue;

		if ((section = IniFile_LoadSection(buf)))
		{
			INI_FILE_SECTION **target;

			for (target = &ini->firstSection; *target; target = &(*target)->next);
			*target = section;
			current = section;
		}
		else if ((value = IniFile_LoadKeyValue(buf)))
		{
			INI_FILE_KEY_VALUE **target;

			for (target = &current->firstValue; *target; target = &(*target)->next);
			*target = value;
		}
	}
}

INI_FILE* IniFile_Load(const char *file)
{
	INI_FILE *ini;
	FILE *fp;

	fp = fopen(file, "r");
	if (!fp)
		return NULL;

	ini = IniFile_Init();
	IniFile_LoadContents(ini, fp);
	fclose(fp);

	return ini;
}

INI_FILE_KEY_VALUE* IniFile_ReleaseKeyValue(INI_FILE_KEY_VALUE *keyValue)
{
	INI_FILE_KEY_VALUE *next;

	free(keyValue->name);
	free(keyValue->value);

	next = keyValue->next;
	free(keyValue);

	return next;
}

INI_FILE_SECTION* IniFile_ReleaseSection(INI_FILE_SECTION *section)
{
	INI_FILE_KEY_VALUE *value;
	INI_FILE_SECTION *next;

	for (value = section->firstValue; value; value = IniFile_ReleaseKeyValue(value));

	next = section->next;
	free(section->name);
	free(section);

	return next;
}

void IniFile_Release(INI_FILE *file)
{
	INI_FILE_SECTION *section;

	for (section = file->firstSection; section; section = IniFile_ReleaseSection(section));

	free(file);
}

const char* IniFile_Value(INI_FILE *file, const char *section, const char *key)
{
	INI_FILE_SECTION *s;

	for (s = file->firstSection; s; s = s->next)
	{
		if (strcmp(s->name, section) == 0)
		{
			INI_FILE_KEY_VALUE *kv;

			for (kv = s->firstValue; s; s = s->next)
			{
				if (strcmp(kv->name, key) == 0)
				{
					return kv->value;
				}
			}

			return NULL;
		}
	}

	return NULL;
}
