#ifndef ARIA_LIB_ARGUMENT_H
#define ARIA_LIB_ARGUMENT_H

#define ARG_OPT_LIMIT 50
#define ARG_POS_LIMIT 50

typedef enum {
	ARGT_INT,
	ARGT_STR,
	ARGT_BOOL,
} ArgumentType;

typedef struct {
	char *abbr_flag;
	char *flag;
	ArgumentType type;
	void *val;
} ArgumentOption;

typedef struct {
	ArgumentOption opt[ARG_OPT_LIMIT];
	char *pos[ARG_POS_LIMIT];
	int opt_count;
	int pos_count;
} Arguments;

#endif
