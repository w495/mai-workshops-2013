#include <stdio.h>

int main() {
    int i, k;
    char *c;
    long pos;
    char buf[30];
    char command;
    FILE *fp;
    int lang;

    if ((fp = fopen("vaca.dat", "r")) == NULL) {
        perror("vac.dat");
        return 1;
    }
    lang = -1;
    while (lang == -1) {
        puts("\n ENTER THE LANG(1/2/3):");
        scanf(" %c", &command);
        if (command == '1')
            lang = 1;
        else if (command == '2')
            lang = 2;
        else if (command == '3')
            lang = 3;;
    }
    while (1) {
        c = buf;
        puts("ENTER A NUMBER ( 0 - code ):");
        scanf("%d", &k);
        if (k == 0) {
            fclose(fp);
            return 0;
        }
        pos = (k - 1) * 32 + 2 + lang * 10;
        fseek(fp, pos, SEEK_SET);
        for (i = 0; i <= 9; i++)
            *c++ = getc(fp);
        *c = '\0';
        printf("%d->%s\n", k, buf);
    }

    fclose(fp);
    return 0;
}
