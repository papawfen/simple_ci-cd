#include "s21_cat.h"

struct flags {
    int b, e, n, s, t, v, T, E;
}flag;

int main(int argc, char *argv[]) {
    flag.b = 0, flag.e = 0, flag.n = 0, flag.s = 0, flag.t = 0;
    flag.v = 0, flag.T = 0, flag.E = 0;
    int res = 0, option_index = 0;
    char *short_options = "benstETv";
    struct option long_options[] = {
        {"number-nonblank", 0, NULL, 'b'},
        {"show-ends", 0, NULL, 'E'},
        {"number", 0, NULL, 'n'},
        {"squeeze-blank", 0, NULL, 's'},
        {"show-tabs", 0, NULL, 'T'},
        {"show-nonprinting", 0, NULL, 'v'},
        {NULL, 0, NULL, 0}
    };
    while ((res = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (res) {
            case 'b': {
                flag.b = 1;
                break;
            }
            case 'e': {
                flag.e = 1;
                flag.v = 1;
                break;
            }
            case 'n': {
                flag.n = 1;
                break;
            }
            case 's': {
                flag.s = 1;
                break;
            }
            case 't': {
                flag.t = 1;
                flag.v = 1;
                break;
            }
            case 'v': {
                flag.v = 1;
                break;
            }
             case 'E': {
                flag.E = 1;
                break;
            }
             case 'T': {
                flag.T = 1;
                break;
            }
            case '?':
            default: {
                printf("unknown option\n");
                break;
            }
        }
    }
    cat_flags(argc, argv);
    return 0;
}

void cat_flags(int argc, char *argv[]) {
    FILE *file;
    int flag_emptyline = 0;
    for (int i = optind; i < argc; i++) {
        if ((file = fopen(argv[i], "r")) != NULL) {
            char str[4096] = "";
            int k = 1;
            int k1 = 0;
            while (fgets(str, 4096, file) != NULL) {
                char dest[4096] = "";
                if (flag.v == 1) {
                    k1 = 0;
                    for (int k = 0; str[k] != '\n'; k++) {
                        if (str[k] >= 1 && str[k] <= 31 && str[k] != 9 && str[k] != 10) {
                            dest[k1] = '^';
                            k1++;
                            dest[k1] = str[k] + 64;
                        } else if (str[k] == 127) {
                            dest[k1] = '^';
                            k1++;
                            dest[k1] = str[k] - 64;
                        } else if ((unsigned char)str[k] > 127 && (unsigned char)str[k] < 160) {
                            dest[k1] = 'M';
                            k1++;
                            dest[k1] = str[k] - 64;
                        } else if ((unsigned char)str[k] >= 160) {
                            dest[k1] = '^';
                            k1++;
                            dest[k1] = '@';
                        } else {
                            dest[k1] = str[k];
                        }
                        k1++;
                    }
                    strcpy(str, dest);
                    str[strlen(str)] = '\n';
                }
                if (flag.t == 1 || flag.T == 1) {
                    k1 = 0;
                    for (int k = 0; str[k] != '\n'; k++) {
                        if (str[k] == '\t') {
                            dest[k1] = '^';
                            k1++;
                            dest[k1] = 'I';
                        } else {
                            dest[k1] = str[k];
                        }
                        k1++;
                    }
                    strcpy(str, dest);
                    str[strlen(str)] = '\n';
                }
                if (flag.e == 1 || flag.E == 1) {
                    for (int ek = 0; ; ek++) {
                        if (str[ek] == '\n') {
                            str[ek] = '$';
                            str[ek + 1] = '\n';
                            break;
                        }
                    }
                }
                if (flag.s == 1) {
                    if (flag_emptyline == 0 && (str[0] == '\n' || (str[0] == '$' && str[1] == '\n'))) {
                        printf("%s", str);
                        flag_emptyline = 1;
                    } else if (str[0] != '\n' && (str[0] != '$' && str[1] != '\n')) {
                        flag_emptyline = 0;
                    }
                }
                if (flag.b == 1) {
                    if (str[0] != '\n' && str[0] != '$') {
                        printf("%6d\t%s", k, str);
                        k++;
                    } else if (flag_emptyline == 0) {
                        printf("%s", str);
                    }
                } else if (flag.n == 1 && flag_emptyline == 0) {
                    printf("%6d\t%s", k, str);
                    k++;
                } else if (flag_emptyline == 0) {
                    printf("%s", str);
                }
                memset(str, 0, 4096);
            }
            fclose(file);
        } else {
            printf("s21_cat: %s No such file or directory\n", argv[i]);
        }
    }
}
