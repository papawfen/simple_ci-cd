#include "s21_grep.h"

struct flags {
    int e, i, v, c, l, n, h, s, f, o;
}flag;

int main(int argc, char *argv[]) {
    flag.e = 0, flag.n = 0, flag.v = 0, flag.c = 0;
    flag.l = 0, flag.h = 0, flag.s = 0;
    flag.f = 0, flag.o = 0;
    int res = 0;
    char *short_options = "eivclnhsfo";
    struct option long_options[] = {
        {"--exclude", 0, NULL, 'e'},
        {"--ignore-case", 0, NULL, 'i'},
        {"--invert-match", 0, NULL, 'v'},
        {"--count", 0, NULL, 'c'},
        {"--files-with-matches", 0, NULL, 'l'},
        {"--line-number", 0, NULL, 'n'},
        {NULL, 0, NULL, 0}
    };
    while ((res = getopt_long(argc, argv, short_options, long_options, &optind)) != -1) {
        switch (res) {
            case 'e': {
                flag.e = 1;
                break;
            }
            case 'i': {
                flag.i = 1;
                break;
            }
            case 'v': {
                flag.v = 1;
                break;
            }
            case 'c': {
                flag.c = 1;
                break;
            }
            case 'l': {
                flag.l = 1;
                break;
            }
            case 'n': {
                flag.n = 1;
                break;
            }
            case 'h': {
                flag.h = 1;
                break;
            }
            case 's': {
                flag.s = 1;
                break;
            }
             case 'f': {
                flag.f = 1;
                break;
            }
            case 'o': {
                flag.o = 1;
                break;
            }
            case '?':
            default: {
                printf("unknown\n");
                break;
            }
        }
    }
    grep_flags(argc, argv);
    return 0;
}

void grep_flags(int argc, char *argv[]) {
    regex_t regex;
    int regflag = 0;
    if (flag.i == 1)
        regflag = REG_ICASE;
    int flagfiles = 0;
    int printline = regcomp(&regex, argv[optind], regflag);
    FILE *file;
    if ((argc - optind - 1) >= 2) {
        flagfiles++;
    }
    for (int i = optind + 1; i < argc; i++) {
        if ((file = fopen(argv[i], "r")) != NULL) {
            if (grep_main_flags(argv, file, &regex,
                                printline, flagfiles, i, regflag) == 0 && flag.l == 1)
                printf("%s\n", argv[i]);
            fclose(file);
        } else if (!flag.s) {
            printf("s21_grep: %s No such file or directory\n", argv[i]);
        }
    }
    regfree(&regex);
}

int grep_main_flags(char *argv[], FILE *file, regex_t *regex,
                    int printline, int flagfiles, int i, int regflag) {
    char str[4096] = "";
    FILE *file1;
    char str1[4096] = "";
    int cmp = REG_NOMATCH;
    int countlines = 0;
    int countlines1 = 1;
    if (flag.f == 1) {
        fclose(file);
        if ((file = fopen(argv[i], "r")) == NULL)
            return 1;
    }
    while (fgets(str, 4096, file) != NULL) {
        if (flag.l && !cmp)
            break;
        if (flag.f) {
            if ((file1 = fopen(argv[optind], "r")) != NULL) {
                while (fgets(str1, 4096, file1) != NULL) {
                    printline = regcomp(regex, str1, regflag);
                    cmp = regexec(regex, str, 0, NULL, 0);
                    if (cmp == 0) {
                        printf("%s", str);
                        break;
                    }
                }
                fclose(file1);
            } else if (!flag.s) {
                printf("s21_grep: %s No such file or directory\n", argv[i]);
            }
        } else {
            cmp = regexec(regex, str, 0, NULL, 0);
        }
        if (optind == 1 && !cmp) {
            if (flagfiles > 0 )
                printf("%s:%s", argv[i], str);
            else
                printf("%s", str);
        }
        if (!cmp && (flag.i || flag.s || flag.e)) {
            if (flagfiles > 0)
                printf("%s:%s", argv[i], str);
            else
                printf("%s", str);
        }
        if (cmp == REG_NOMATCH && flag.v) {
            if (flagfiles > 0)
                printf("%s:%s", argv[i], str);
            else
                printf("%s", str);
        }
        if (flag.c && printline == cmp) {
            countlines++;
        }
        if (flag.n && !cmp) {
            printf("%d:%s", countlines1, str);
        }
        if (!cmp && flag.o) {
            int place = 0;
            char *p;
            while ((p = strstr(&str[place], argv[optind])) != NULL) {
                place = (int)(p - str + 1);
                printf("%s\n", argv[optind]);
            }
        }
        if (!cmp && flag.h) {
            printf("%s", str);
        }
        countlines1++;
    }
    if (flag.c) {
        if (flagfiles > 0 )
            printf("%d\n", countlines);
        else
            printf("%d\n", countlines);
    }
    return cmp;
}
