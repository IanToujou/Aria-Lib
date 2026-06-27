#include "../include/argument.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Initializes the argument struct. Required to use argument parsing.
 *
 * @param args A pointer to the argument struct.
 */
void arg_init(Arguments *args) {
	args->opt_count = 0;
	args->pos_count = 0;
}

/**
 * Adds a new argument to the argument struct.
 *
 * @param args A pointer to the argument struct.
 * @param abbr_flag The abbreviated name of the flag.
 * @param flag The full name of the flag.
 * @param type The type of value this argument holds.
 * @param val A pointer to the value itself.
 */
void arg_add(Arguments *args, const char *abbr_flag, const char *flag, const ArgumentType type, void *val) {
	if (args->opt_count >= ARG_OPT_LIMIT) {
		fprintf(stderr, "Argument parsing failed: Too many options.");
		exit(1);
	}
	ArgumentOption *opt = &args->opt[args->opt_count++];
	opt->abbr_flag = abbr_flag ? strdup(abbr_flag) : NULL;
	opt->flag = flag ? strdup(flag) : NULL;
	opt->type = type;
	opt->val = val;
}

/**
 * Parses the arguments from the command line to the argument struct.
 *
 * @param args A pointer to the argument struct.
 * @param argc The argument count from the main function.
 * @param argv The argument vector from the main function.
 */
void arg_parse(Arguments *args, const int argc, char *argv[]) {
	for (int i = 1; i < argc; i++) {
		char *arg = argv[i];
		int matched = 0;
		for (int j = 0; j < args->opt_count; j++) {
			const ArgumentOption *opt = &args->opt[j];
			if ((opt->abbr_flag && strcmp(arg, opt->abbr_flag) == 0) ||
				(opt->flag && strcmp(arg, opt->flag) == 0)) {
				matched = 1;
				if (opt->type == ARGT_BOOL) {
					*(int *)opt->val = 1;
				} else if (i + 1 < argc) {
					if (opt->type == ARGT_INT) {
						*(int *)opt->val = atoi(argv[++i]);
					} else if (opt->type == ARGT_STR) {
						*(char **)opt->val = argv[++i];
					}
				} else {
					fprintf(stderr, "Option %s requires a value.\n", arg);
					exit(1);
				}
				break;
			}
		}
		if (!matched) {
			if (args->pos_count < ARG_POS_LIMIT) {
				args->pos[args->pos_count++] = arg;
			} else {
				fprintf(stderr, "Too many positional arguments.\n");
				exit(1);
			}
		}
	}
}

/**
 * Print the usage of saved arguments in the argument struct.
 *
 * @param args A pointer to the argument struct.
 */
void arg_print(const Arguments *args) {
	printf("Usage:\n");
	for (int i = 0; i < args->opt_count; i++) {
		const ArgumentOption *opt = &args->opt[i];
		printf("%s, %s\n", opt->abbr_flag ? opt->abbr_flag : "",
			   opt->flag ? opt->flag : "");
	}
}

/**
 * Free the argument struct.
 *
 * @param args A pointer to the argument struct.
 */
void arg_free(Arguments *args) {
	for (int i = 0; i < args->opt_count; i++) {
		ArgumentOption *opt = &args->opt[i];
		if (opt->abbr_flag) {
			free(opt->abbr_flag);
			opt->abbr_flag = NULL;
		}
		if (opt->flag) {
			free(opt->flag);
			opt->flag = NULL;
		}
	}
	args->opt_count = 0;
	args->pos_count = 0;
}